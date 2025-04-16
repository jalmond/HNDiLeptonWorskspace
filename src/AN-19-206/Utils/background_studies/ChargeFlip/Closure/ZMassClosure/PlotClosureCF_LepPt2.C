#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(TString sbin, TString binning,HNLPlotter Plotter,TString ID, TString Era, TString DateTag, TString Method, TString Indir, TString HistString,TString LabelForOutPut,vector<double> vrebin);

void PlotClosureCF_LepPt2(){

  HNLPlotter Plotter("ClosureTest_AN_Oct7");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;

  vector<TString> Eras = {"2016","2016a","2016b","2017","2018"};
  for(auto era : Eras) {
    TString year = (era.Contains("16")) ? "2016" : era;
    
    RunClosure("Bin3","InvPtEta3", Plotter, "HNL_ULID", era, "Oct7","PBS","HNL_ChargeFlip_Closure_Z", "Separate_BinnedShift", "Closure_ElectronCF_Z_Lep2" ,  {20,25,30,40,50,60,70,80,90,100,150,200,300,400,500});
    //RunClosure(Plotter, "passHEEPID_v1", era, "Oct1","PBS","HNL_ChargeFlip_Closure_Z", "Separate_BinnedShift", "Closure_ElectronCF_Z" ,  {30,40,50,60,70,80,90,100,150,200,300,500});
    //RunClosure(Plotter, "passHEEPID_v2", era, "Sep16","PBS","HNL_ChargeFlip_Closure_Z", "Separate_BinnedShift", "Closure_ElectronCF_Z" ,  {25,30,40,50,60,70,80,90,100,150,200,300,500});
    //RunClosure(Plotter, "passHEEPID_v3", era, "Sep16","PBS","HNL_ChargeFlip_Closure_Z", "Separate_BinnedShift", "Closure_ElectronCF_Z" ,  {25,30,40,50,60,70,80,90,100,150,200,300,500});
    //RunClosure(Plotter, "HNL_ULID", era, "Sep16","CS","HNL_ChargeFlip_Closure_Z", "Separate_ConstShift","Closure_ElectronCF_Z" ,  {25,30,40,50,60,70,80,90,100,150,200,300,500});
    //RunClosure(Plotter, "HNL_ULID_"+year, era, "May8","PBS","HNL_ChargeFlip_Closure_Z", "Paired_BinnedShift", "Closure_ElectronCF_Z" ,  {25,30,40,50,60,70,80,90,100,150,200,300,500});
    //RunClosure(Plotter, "HNL_ULID_"+year, era, "May8","CS","HNL_ChargeFlip_Closure_Z", "Paired_ConstShift","Closure_ElectronCF_Z" ,  {25,30,40,50,60,70,80,90,100,150,200,300,500});


  }
  
}

void RunClosure(TString sbin, TString binning,HNLPlotter Plotter,TString ID, TString Era, TString  DateTag, TString Method, TString HistString, TString Indir,TString LabelForOutPut,vector<double> vrebin){
  
  HistString=HistString + "_"+Method+"_"+ Indir;
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString HistLab = "PBSExtrap";
  if(Method == "CS") HistLab = "CS";
  
  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/ClosureTest/"+DateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTreeBDT_Closure.root";
  cout << path << endl;
  TH1D *hist_mass_CF             = Plotter.ConstructHist(path,ID+"/Z/SS_Lepton2Pt", vrebin);
  
  TH1D *hist_Prompt              = Plotter.ConstructHist(path,ID+"/"+Indir+"_"+sbin+"/CFRate_"+binning+"_"+HistLab+"_Central_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt", vrebin);
  TH1D *hist_PromptUp              = Plotter.ConstructHist(path,ID+"/"+Indir+"Up_"+sbin+"/CFRate_"+binning+"_"+HistLab+"_PSigma_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt", vrebin);
  TH1D *hist_PromptDown              = Plotter.ConstructHist(path,ID+"/"+Indir+"Down_"+sbin+"/CFRate_"+binning+"_"+HistLab+"_MSigma_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt", vrebin);
  TH1D *hist_PromptStatUp              = Plotter.ConstructHist(path,ID+"/Separate_BinnedStatUp_"+sbin+"/CFRate_"+binning+"_"+HistLab+"_SystUp_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt", vrebin);
  TH1D *hist_PromptStatDown              = Plotter.ConstructHist(path,ID+"/Separate_BinnedStatDown_"+sbin+"/CFRate_"+binning+"_"+HistLab+"_SystDown_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt", vrebin);
  
  
  TH1D *hist_Prompt_NoShift      = Plotter.ConstructHist(path,ID+"/NoShift_"+sbin+"/CFRate_"+binning+"_NoS_Central_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt" , vrebin);
  double scale = 1;
  hist_Prompt->Scale(scale);
  hist_PromptUp->Scale(scale);
  hist_PromptDown->Scale(scale);
  hist_Prompt_NoShift->Scale(scale);

  cout << hist_mass_CF << " " << hist_Prompt << " " << hist_Prompt_NoShift << endl; 
  cout << hist_PromptUp << " " << hist_PromptDown << "  " << hist_PromptStatUp  << " " << hist_PromptStatDown << endl;
  

  cout << ID+"/Seperate_BinnedStatUp/CFRate_"+binning+"_"+HistLab+"_Central_"+ID+"/Z/OS_Weighted_EnergyShift_Lepton2Pt " << endl;
  hist_PromptUp->SetLineStyle(4);
  hist_PromptDown->SetLineStyle(4);
  hist_PromptUp->SetLineColor(kBlack);
  hist_PromptDown->SetLineColor(kBlack);
  
  hist_mass_CF->GetYaxis()->SetTitle("Events");
  hist_mass_CF->GetXaxis()->SetTitle("p_{T} GeV ");
 

  cout << "Integrals " << Era << endl;
  cout << "Obs = " << hist_mass_CF->Integral() << endl;
  cout << "Pred = " << hist_Prompt->Integral() << endl;
  cout << "Pred [no shift] = " << hist_Prompt_NoShift->Integral() << endl;

  Double_t err;
  Double_t hint = hist_mass_CF->IntegralAndError(0,hist_mass_CF->GetNbinsX()+1, err);

  cout << "SF = " << hist_mass_CF->Integral() / hist_Prompt->Integral()  << " + / - " <<  err / hist_Prompt->Integral() << endl;
  SaveHistogram( Plotter,{hist_mass_CF,hist_Prompt,hist_Prompt_NoShift,hist_PromptUp,hist_PromptDown,hist_PromptStatUp,hist_PromptStatDown}, {"SS Observed", "OS*R_{CF} Predicted","OS*R_{CF} Predicted [no shift]","Pred Up","Pred Down"}, ID+"_CF_Closure_"+HistString+"_"+Method+"_"+Era, LabelForOutPut+"_"+sbin, {Method});
  

  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);
  
  
  TH1D* hist_default = hists[0];
  
  TLegend *lg = new TLegend(0.55, 0.7, 0.93, 0.85);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);
  
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
  
  for(auto i : hists) {
  if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*1.5;
}
  hist_axis(hist_empty, hist_default);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale*1.2);

  //  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);
  
  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors(hist_empty);
  gr_data->SetLineWidth(2.0);
  gr_data->SetMarkerSize(0.);
  gr_data->SetMarkerColor(kBlack);
  gr_data->SetLineColor(kBlack);
  hist_empty->Draw("phistsame");
  gr_data->Draw("p0same");

  lg->AddEntry(gr_data, legname[0],"lp");
  

  for(int i=1 ; i < 3; i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }
  
  


  //  for(int i=1; i < tmp_Cent->GetNbinsX()+1; i++){
  //
  // tmp_Cent->SetBinContent(i, (tmp_Up->GetBinContent(i) +tmp_Down->GetBinContent(i))/2.);
  // tmp_Cent->SetBinError(i, (fabs(tmp_Up->GetBinContent(i) -tmp_Down->GetBinContent(i)))/2.);
  //}
  
  TH1D *tmp_Cent = (TH1D *)hists[1]->Clone();
  TH1D *tmp_Up = (TH1D *)hists[3]->Clone();
  TH1D *tmp_Down = (TH1D *)hists[4]->Clone();
  TH1D *tmp_SUp = (TH1D *)hists[5]->Clone();
  TH1D *tmp_SDown = (TH1D *)hists[6]->Clone();
  for(int i=1; i < tmp_Cent->GetNbinsX()+1; i++){
    cout << "Bin " << i <<" tmp_Cent = " << tmp_Cent->GetBinContent(i) << " tmp_SUp->GetBinContent(i)  = " << tmp_SUp->GetBinContent(i)  << "  tmp_SDown->GetBinContent(i) =" << tmp_SDown->GetBinContent(i) <<  " tmp_Up->GetBinContent(i) = " << tmp_Up->GetBinContent(i) << " tmp_Down->GetBinContent(i) =" <<tmp_Down->GetBinContent(i) <<  endl;
    double ErrUp1 = (tmp_Up->GetBinContent(i) > tmp_Down->GetBinContent(i)) ? tmp_Up->GetBinContent(i) : tmp_Down->GetBinContent(i);
    double ErrDown1 = (tmp_Up->GetBinContent(i) > tmp_Down->GetBinContent(i)) ? tmp_Down->GetBinContent(i) : tmp_Up->GetBinContent(i);
    double ErrStatUp1 = (tmp_SUp->GetBinContent(i) > tmp_SDown->GetBinContent(i)) ? tmp_SUp->GetBinContent(i) : tmp_SDown->GetBinContent(i);
    double ErrStatDown1 = (tmp_SUp->GetBinContent(i) > tmp_SDown->GetBinContent(i)) ? tmp_SDown->GetBinContent(i) : tmp_SUp->GetBinContent(i);

    cout << "ErrUp1 = " << ErrUp1 << " ErrDown1 = " << ErrDown1 << " ErrStatUp1 = " << ErrStatUp1 << " ErrStatDown1 = " <<ErrStatDown1 << endl;
    double BinVal = tmp_Cent->GetBinContent(i);
    if(ErrUp1 <= BinVal) ErrUp1 = 0;
    else ErrUp1 = ErrUp1 - BinVal;
    if(ErrStatUp1 <= BinVal) ErrStatUp1= 0;
    else ErrStatUp1= ErrStatUp1 - BinVal;

    if(ErrDown1 >= BinVal) ErrDown1= 0;
    else ErrDown1=  BinVal - ErrDown1;
    if(ErrStatDown1 >= BinVal) ErrStatDown1= 0;
    else ErrStatDown1= BinVal - ErrStatDown1 ;

    double ErrUp = sqrt(ErrUp1*ErrUp1 + ErrStatUp1*ErrStatUp1 + 0.0225*hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i));
    double ErrDown = sqrt(ErrDown1*ErrDown1 + ErrStatDown1*ErrStatDown1+ 0.0225*hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i));

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
  tmp_Cent->Draw("sameE2");

  lg->AddEntry(tmp_Cent, "Shift Uncer.","f");

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
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.85-0.05*il, Labels[il]);

  if(plotter.SetLogY)c1->SetLogy();

  c1_down->cd();

  TH1D *tmp_ratio_point = (TH1D *)hist_default->Clone();
  tmp_ratio_point->Divide(hists[1]);
  tmp_ratio_point->GetYaxis()->SetRangeUser(0.,2.);
  tmp_ratio_point->GetYaxis()->SetTitle("Obs/Pred");

  tmp_ratio_point->Draw("phist");

  TGraphAsymmErrors *grr_data = new TGraphAsymmErrors(tmp_ratio_point);
  grr_data->SetLineWidth(2.0);
  grr_data->SetMarkerSize(0.);
  //  grr_data->SetMarkerColor(kBlack);                                                                                                                                                        
  // grr_data->SetLineColor(plotter.GetColor(1));
  grr_data->Draw("p0same");


  TH1D *tmp_ratio_err = (TH1D *)tmp_ratio_point->Clone();
  for(int i=1; i < tmp_ratio_err->GetNbinsX()+1; i++){
    tmp_ratio_err->SetBinContent(i, 1);
    tmp_ratio_err->SetBinError(i, 0.15);
  }
  tmp_ratio_err->SetMarkerColorAlpha(kAzure-9, 0);
  tmp_ratio_err->SetFillStyle(3013);
  tmp_ratio_err->SetFillColor(kBlack);
  tmp_ratio_err->SetLineColor(0);
  tmp_ratio_err->Draw("sameE2");
  
  TLine* Line1 = new TLine(tmp_ratio_err->GetXaxis()->GetXmin(),1,tmp_ratio_err->GetXaxis()->GetXmax(),1);
  Line1->Draw();
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
