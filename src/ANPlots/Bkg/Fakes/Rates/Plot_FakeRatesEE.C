#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH2D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void FakeRateProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString Xlabel, TString LabelForOutPut);

void Plot_FakeRatesEE(){

  HNLPlotter Plotter("FakeIDRates");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  //  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;


  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;

    //FakeRateProccessor(Plotter, "HNL_ULID_"+year, era,"Fakerate_Eta", "#eta_{SC}", "HNL_ChargeFlip_rate_basic");
    FakeRateProccessor(Plotter, "HNL_ULID_"+year, era,"HNL_ULID_2017_ptparton_eta_HNL_ULID_FO_v0_AJ30;1", "el p_{T} [GeV]", "HNL_Fake_rate_basic");
    
  }
}

void FakeRateProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString Xlabel, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_FakeRate");
  
  TString path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/2017/FakeRate/DataFR/ElFR/FR_EGamma_2017_HNL_ULID_PtParton_v5.root";

  TH2D *hist_F           = Plotter.Construct2DHist(path,HistString);
  
  hist_F->GetYaxis()->SetTitle("abs(#eta)");
  hist_F->GetXaxis()->SetTitle(Xlabel);

  //  hist_F_N->Divide(hist_CF_N,hist_CF_D,1.,1.,"cl=0.683 b(1,1) mode");

  SaveHistogram( Plotter,{hist_F}, {ID }, ID+"_F_Rate_"+HistString, LabelForOutPut, {}, "");
  


  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH2D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH2D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

  TH2D *hist_empty= (TH2D*)hist_default->Clone();

  hist_empty->SetName("DUMMY_FOR_AXIS");


  double Ymin = plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  for(auto i : hists) {
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*plotter.Hist_YAxis_MaxScale;
  }
  hist_axis(hist_empty);

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

  hist_empty->Draw("textcolz");

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

  for(unsigned int il =0 ; il < scales.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, scales[il]);

  if(plotter.SetLogY)c1->SetLogy();
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
