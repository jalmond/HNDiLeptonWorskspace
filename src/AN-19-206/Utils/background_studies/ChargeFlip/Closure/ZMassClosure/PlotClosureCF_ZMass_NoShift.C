#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(TString Era,TString DateTag,HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(TString sbin, TString binning, HNLPlotter Plotter,TString ID, TString Era, TString DateTag, TString Method, TString Indir, TString HistString,TString LabelForOutPut,vector<double> vrebin);

void PlotClosureCF_ZMass_NoShift(){

  HNLPlotter Plotter("ClosureTest_AN_Oct8");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  
  vector<TString> Eras = {"2016","2016a","2016b","2017","2018"};
  for(auto era : Eras) {
    TString year = (era.Contains("16")) ? "2016" : era;


    RunClosure("Bin3","InvPtEta3", Plotter, "HNL_ULID", era, "Oct8","CS","HNL_ChargeFlip_Closure_ZMass_NoShift", "Paired_ConstShift", "Closure_ElectronCF_ZMass_NoShift" ,  {50,60,70,80,85,90,95,100,110,120.,125.,130});
    RunClosure("Bin3","InvPtEta3", Plotter, "HNL_ULID", era, "Oct8","PBS","HNL_ChargeFlip_Closure_ZMass_NoShift", "Separate_BinnedShift", "Closure_ElectronCF_ZMass_NoShift" ,  {50,60,70,80,85,90,95,100,110,120.,125.,130});
       
  }
  
}

void RunClosure(TString Bin, TString Binning, HNLPlotter Plotter,TString ID, TString Era, TString  DateTag, TString Method, TString HistString, TString Indir,TString LabelForOutPut,vector<double> vrebin){
  
  HistString=HistString + "_"+Method+"_"+ Indir;
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString HistLab = "PBSExtrap";
  if(Method == "CS") HistLab = "CS";

  /// path to merged input file TT+DY  
  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/ClosureTest/"+DateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTreeBDT_Closure.root";
  cout << path << endl;

  /// Setup Input SS 
  TH1D *hist_mass_CF             = Plotter.ConstructHist(path,ID+"/ZMass/SS", vrebin);
  
  TH1D *hist_Prompt_NoShift      = Plotter.ConstructHist(path,ID+"/NoShift_"+Bin+"/CFRate_"+Binning+"_NoS_Central_"+ID+"/ZMass/OS_Weighted_EnergyShift" , vrebin);
  
  hist_mass_CF->GetYaxis()->SetTitle("Events");
  hist_mass_CF->GetXaxis()->SetTitle("m_{ll} GeV ");
 
  SaveHistogram(Era,DateTag, Plotter,{hist_mass_CF,hist_Prompt_NoShift}, {"SS Observed","OS*R_{CF} Predicted [no shift]","Pred Up","Pred Down"}, ID+"_CF_Closure_"+HistString+"_"+Method+"_"+Era, LabelForOutPut+"_"+Bin, {});
 
  return;
}

void SaveHistogram(TString Era,TString DateTag,HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.2, 0.4, 0.325, 0.6);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size*1.1);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();

  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);



  if(plotter.SetLogY)c1->SetLogy();
  //  canvas_margin(c1);
  canvas_margin(c1, c1_up, c1_down);

  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();


  TH1D *hist_empty= (TH1D*)hist_default->Clone();

  hist_empty->SetName("DUMMY_FOR_AXIS");

  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();

  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  for(int i = 0 ; i < 2; i++) {
    if(hists[i]->GetMaximum() > YmaxScale) YmaxScale = hists[i]->GetMaximum();
  }
  hist_axis(hist_empty, hist_default);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale*1.1);

  //  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);
  hist_empty->SetLineColor(kBlack);
  //hist_empty->Draw("histsame");
  //hist_empty->Draw("sameE");
  
  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors(hist_empty);
  gr_data->SetLineWidth(2.0);
  gr_data->SetMarkerSize(0.);
  gr_data->SetMarkerColor(kBlack);
  gr_data->SetLineColor(kBlack);
  hist_empty->Draw("phistsame");
  gr_data->Draw("p0same");
  
  lg->AddEntry(gr_data, legname[0],"lp");


  for(int i=1 ; i < 2; i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }

  TH1D *tmp_Cent = (TH1D *)hists[1]->Clone();
  
  for(int i=1; i < tmp_Cent->GetNbinsX()+1; i++){
  
    double ErrUp = sqrt(0.0225*hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i));
    double ErrDown = sqrt(0.0225*hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i));
    
    double BinVal = hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i);
    double NewValUp = BinVal + ErrUp;
    double NewValDown = BinVal - ErrDown;
    double NewVal = (NewValUp +NewValDown)/2.;
    double NewErr = (ErrUp + ErrDown) / 2;
    tmp_Cent->SetBinContent(i, NewVal);
    tmp_Cent->SetBinError(i, NewErr);
    cout << "Bin " << i << " NewErr = " << NewErr << " CENT = " << NewVal <<  " obs = " << hists[0]->GetBinContent(i) << " tmp_Cent " << tmp_Cent->GetBinContent(i) <<endl;
    cout << "Perc. err = " << NewErr/NewVal << endl;
  }
  
  tmp_Cent->SetMarkerColorAlpha(kAzure-9, 0);
  tmp_Cent->SetFillStyle(3013);
  tmp_Cent->SetFillColor(kBlack);
  tmp_Cent->SetLineColor(0);
  //  tmp_Cent->Draw("sameE2");

  //  lg->AddEntry(tmp_Cent, "Shift+Stat Uncer.","f");

  lg->Draw();

  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *gr3 = new TGraph(2, x_1, y_1);
  gr3->Draw("same");


  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  latex_Lumi.SetTextSize(plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);
  if(Era=="2016a")latex_Lumi.DrawLatex(0.72, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(Era=="2016b")latex_Lumi.DrawLatex(0.72, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(Era=="2016") latex_Lumi.DrawLatex(0.72, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(Era=="2017") latex_Lumi.DrawLatex(0.72, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(Era=="2018") latex_Lumi.DrawLatex(0.72, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(Era=="Run2") latex_Lumi.DrawLatex(0.72, 0.96, "137.9 fb^{-1} (13 TeV)");

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.85-0.05*il, Labels[il]);

  if(plotter.SetLogY)c1->SetLogy();

  c1_down->cd();

  TH1D *tmp_ratio_point = (TH1D *)hist_default->Clone();
  tmp_ratio_point->SetLineColor(plotter.GetColor(1));
  tmp_ratio_point->SetLineWidth(3.);

  tmp_ratio_point->Divide(hists[1]);
  tmp_ratio_point->GetYaxis()->SetRangeUser(0.0,2);
  tmp_ratio_point->GetYaxis()->SetTitle("Obs/Pred");

  tmp_ratio_point->Draw("phist");
  TGraphAsymmErrors *grr_data = new TGraphAsymmErrors(tmp_ratio_point);
  grr_data->SetLineWidth(2.0);
  grr_data->SetMarkerSize(0.);
  //  grr_data->SetMarkerColor(kBlack);
  grr_data->SetLineColor(plotter.GetColor(1));
  grr_data->Draw("p0same");


  TH1D *tmp_ratio_err = (TH1D *)tmp_Cent->Clone();
  for(int i=1; i < tmp_Cent->GetNbinsX()+1; i++){
    double ErrValUp = tmp_ratio_err->GetBinContent(i)+tmp_ratio_err->GetBinError(i);
    double ErrValDown = tmp_ratio_err->GetBinContent(i)-tmp_ratio_err->GetBinError(i);
    double RErrValUp = ErrValUp / hists[1]->GetBinContent(i);
    double RErrValDown = ErrValDown / hists[1]->GetBinContent(i);
    
    double New_R_val = (RErrValUp+RErrValDown)/2.;
    double New_R_err = (RErrValUp-RErrValDown)/2.;
    
    tmp_ratio_err->SetBinError(i,tmp_ratio_err->GetBinError(i) / tmp_ratio_err->GetBinContent(i));
    tmp_ratio_err->SetBinContent(i,1);
  }
  tmp_ratio_err->SetMarkerColorAlpha(kAzure-9, 0);
  tmp_ratio_err->SetFillStyle(3013);
  tmp_ratio_err->SetFillColor(kBlack);
  tmp_ratio_err->SetLineColor(0);
  tmp_ratio_err->Draw("sameE2");

  TLine* Line1 = new TLine(tmp_ratio_err->GetXaxis()->GetXmin(),1,tmp_ratio_err->GetXaxis()->GetXmax(),1);
  Line1->Draw();

  cout << "Saving " + plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf" << endl;
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
