#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void CFRateProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString Xlabel, TString LabelForOutPut);

void Plot_ElCFRates(){

  HNLPlotter Plotter("ChargeMisIDRates");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  //  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;


  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;

    //CFRateProccessor(Plotter, "HNL_ULID_"+year, era,"CFrate_Eta", "#eta_{SC}", "HNL_ChargeFlip_rate_basic");
    CFRateProccessor(Plotter, "HNL_ULID_"+year, era,"CFratePt", "el p_{T} [GeV]", "HNL_ChargeFlip_rate_basic");
    
  }
}

void CFRateProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString Xlabel, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");
  
  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/Rates/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";

  TH1D *hist_CF_N           = Plotter.ConstructHist(path,ID+"/"+HistString+"/Num");
  TH1D *hist_CF_D           = Plotter.ConstructHist(path,ID+"/"+HistString+"/Denom");
  
  hist_CF_N->GetYaxis()->SetTitle("Q_{el} CF Rate");
  hist_CF_N->GetXaxis()->SetTitle(Xlabel);

  hist_CF_N->Divide(hist_CF_N,hist_CF_D,1.,1.,"cl=0.683 b(1,1) mode");
  


  TString pathNoShift="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/RatesNoShift/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";

  TH1D *hist_NoShift_CF_N           = Plotter.ConstructHist(pathNoShift,ID+"/"+HistString+"/Num");
  TH1D *hist_NoShift_CF_D           = Plotter.ConstructHist(pathNoShift,ID+"/"+HistString+"/Denom");

  hist_NoShift_CF_N->GetYaxis()->SetTitle("Q_{el} CF Rate");
  hist_NoShift_CF_N->GetXaxis()->SetTitle(Xlabel);

  hist_NoShift_CF_N->Divide(hist_NoShift_CF_N,hist_NoShift_CF_D,1.,1.,"cl=0.683 b(1,1) mode");


  SaveHistogram( Plotter,{hist_CF_N,hist_NoShift_CF_N}, {ID +" E_{shifted}", ID + " No E_{shift}"}, ID+"_CF_Rate_"+HistString, LabelForOutPut, {}, "");
  


  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError){
 

 
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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*plotter.Hist_YAxis_MaxScale;
  }
  hist_axis(hist_empty);

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

  hist_empty->Draw("histsame");
  if(drawError)hist_empty->Draw("histsameE0");



  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    if(drawError)hists[i]->Draw("histsameE0");
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

  for(unsigned int il =0 ; il < scales.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, scales[il]);

  if(plotter.SetLogY)c1->SetLogy();
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
