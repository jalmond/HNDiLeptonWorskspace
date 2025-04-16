#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunPlotter(HNLPlotter Plotter,TString ID, TString Era,TString LabelForOutPut);

void Plot_Nvtx_Fake(){

  HNLPlotter Plotter("Fake_Lepton");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;


  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era; 
    RunPlotter(Plotter, "HNL_ULID", era, "Fake_Lepton_Nvtx");
  }
  
  
}

void RunPlotter(HNLPlotter Plotter,TString ID, TString Era, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_Fake_vtx");

  TString path= "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+Era+"/FakeRate/NvtxSF/FakeRateNVtx13TeV_"+Era+".root";

  
  TH1D *hist_mu8             = Plotter.ConstructHist(path,"HLT_Mu8_TrkIsoVVL_v",{1});
  TH1D *hist_mu17             = Plotter.ConstructHist(path,"HLT_Mu17_TrkIsoVVL_v",{1});
  
  ifstream f(path.Data());
  if(!f.good()) {
    cout << "Path " << path << " does not exist " << endl;
    return;
  }
  if(!hist_mu8){
    cout << "HLT_Mu8_TrkIsoVVL_v missing" << endl;
    return;
  }
  if(!hist_mu17){
    cout << "HLT_Mu17_TrkIsoVVL_v missing" << endl;
    return;
  }

  hist_mu8->SetLineColor(kRed);
  hist_mu17->SetLineColor(kBlue);

  hist_mu8->GetXaxis()->SetRangeUser(0,50);
  hist_mu17->GetXaxis()->SetRangeUser(0,50);

  //  hist_mu8->SetLineStyle(4);
  hist_mu8->GetYaxis()->SetTitle("Correction");
  hist_mu8->GetXaxis()->SetTitle("N_{vtx}");
 

  SaveHistogram( Plotter,{hist_mu8,hist_mu17}, {"HLT_Mu8","HLT_Mu17"}, Era+"_FakeLepton_NvtxCorr", LabelForOutPut,{});
  

  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

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
  hist_axis(hist_empty);

  hist_empty->GetYaxis()->SetRangeUser(0,5);

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

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

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, Labels[il]);

  if(plotter.SetLogY)c1->SetLogy();
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
