#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString DateTag, TString Method, TString binning, TString binTag, TString HistString,TString LabelForOutPut,vector<double> vrebin);

void PlotClosureCF_LeptonPt_Eta(){

  HNLPlotter Plotter("ClosureTest");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  
  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;


    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","PBS","Binning1",    "_w_pbs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","PBS","Binning3",    "_w_pbs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","PBS","BinningEta",  "_w_pbs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","PBS","BinningEta2", "_w_pbs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","PBS","BinningEta3", "_w_pbs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","CS","Binning1",    "_w_cs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","CS","Binning3",    "_w_cs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","CS","BinningEta",  "_w_cs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","CS","BinningEta2", "_w_cs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","CS","BinningEta3", "_w_cs","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});
    
    RunClosure(Plotter, "HNL_TC1_ULID_"+year, era, "May8","DYTop_PBS","Binning3",    "_w_pbs_DYTop","HNL_ChargeFlip_Closure_LeptonEta", "Closure_ElectronCF" ,  {5});


  }
  
}

void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString  DateTag,TString Method, TString binning, TString binTag, TString HistString, TString LabelForOutPut,vector<double> vrebin){
  
  HistString=HistString + "_"+Method + "_"+binning;
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/ClosureTest/"+DateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTreeBDT_Closure.root";
  cout << path << endl;
  TH1D *hist_mass_CF             = Plotter.ConstructHist(path,ID+"/Closure/CF_LepEta", vrebin);
  TH1D *hist_Prompt              = Plotter.ConstructHist(path,ID+"/Closure_"+Method+"/NonCF_Fitted_"+binning+"_LepEta_"+binTag, vrebin);
  TH1D *hist_Prompt_NoShift      = Plotter.ConstructHist(path,ID+"/Closure_NoShift/NonCF_Fitted_"+binning+"_LepEta__w_nos", vrebin);

  cout << hist_mass_CF << " " << hist_Prompt << " " << hist_Prompt_NoShift << endl; 


  cout << ID+"/Closure_NoShift/NonCF_Fitted_"+binning+"_LeptonEta__w_nos" << endl;
  hist_Prompt_NoShift->SetLineStyle(4);

  hist_mass_CF->GetYaxis()->SetTitle("Events");
  hist_mass_CF->GetXaxis()->SetTitle("el #eta ");
 

  cout << "Integrals " << Era << endl;
  cout << "Obs = " << hist_mass_CF->Integral() << endl;
  cout << "Pred = " << hist_Prompt->Integral() << endl;
  cout << "Pred [no shift] = " << hist_Prompt_NoShift->Integral() << endl;
  
  SaveHistogram( Plotter,{hist_mass_CF,hist_Prompt,hist_Prompt_NoShift}, {"SS Observed", "OS*R_{CF} Predicted","OS*R_{CF} Predicted [no shift]"}, ID+"_CF_Closure_"+HistString+"_"+Method+"_"+Era, LabelForOutPut, {Method});
  

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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*1.2;
  }
  hist_axis(hist_empty, hist_default);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale*1.4);

  //  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

  hist_empty->Draw("histsame");
  hist_empty->Draw("sameE");

  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }
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
  tmp_ratio_point->GetYaxis()->SetRangeUser(0.6,1.4);
  tmp_ratio_point->GetYaxis()->SetTitle("Obs/Pred");

  tmp_ratio_point->Draw("hist");


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
