#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void Draw_Graph(HNLPlotter plotter, TString Era,vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat);

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

TString dateTag = "Sep16";

void PlotEnergyCF_Graph(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;
  
  for(auto era : {""}){
    
    vector <TString> HistStrings = {"BB"};

    for(auto HistString : HistStrings ) EnergyCFShiftProccessor(Plotter, "HNL_ULID", era,HistString, "AN-19-206_HNL_ChargeFlip_InclusiveBinned_EnergyShift");
   
  }

}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  Plotter.RebinX    = 1;
  Plotter.Normalise = 1;
    
  TString HistName = HistString;

  const Int_t nBB = 5;
  
  Double_t pt_2016[nBB]   = {25.,47.5,60, 85, 150}; 
  Double_t pt_2017[nBB]   = {27, 49.5,62, 87,152}; 
  Double_t pt_2018[nBB]   = {29.,51.5,64, 89, 154}; 
  Double_t exl[nBB] = {0,0,0,0,0};
  Double_t exh[nBB] = {0,0,0,0,0};  
  Double_t eyh[nBB] = {0.002,0.002,0.002,0.002,0.002};

  Double_t y_2016[nBB]   = {0.96, 0.975, 0.985, 0.99, 0.998};
  Double_t eyl_2016[nBB] = {0.023,0.012,0.008,0.008,0.003};

  Double_t y_2017[nBB]   = {0.959, 0.973, 0.985, 0.987, 0.998};
  Double_t eyl_2017[nBB] = {0.029,0.012,0.0128,0.006,0.003};

  Double_t y_2018[nBB]   = {0.953, 0.975, 0.981, 0.989, 0.995};
  Double_t eyl_2018[nBB] = {0.022,0.015,0.008,0.009,0.003};

  auto gr1_2016 = new TGraphAsymmErrors(nBB,pt_2016,y_2016,exl,exh,eyl_2016,eyh);
  auto gr1_2017 = new TGraphAsymmErrors(nBB,pt_2016,y_2017,exl,exh,eyl_2017,eyh);
  auto gr1_2018 = new TGraphAsymmErrors(nBB,pt_2016,y_2018,exl,exh,eyl_2018,eyh);
  
  //  gr1->SetTitle("TGraphAsymmErrors Example");
  gr1_2016->SetMarkerColor(4);
  gr1_2016->SetMarkerStyle(21);
  gr1_2016->Draw("ALP");

  TString dirName = LabelForOutPut;

  Plotter.thiscut_plotpath = Plotter.plotpath+"/"+ dirName;
  Plotter.mkdir(Plotter.thiscut_plotpath);

  TLegend *lg= new TLegend(Plotter.Legend_X1,Plotter.Legend_Y1,Plotter.Legend_X2,Plotter.Legend_Y2);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.025);

  TCanvas* c1 = new TCanvas(HistName, "", Plotter.Canvas_X, Plotter.Canvas_Y);
  c1->Draw();
  c1->cd();

  if(Plotter.SetLogY)c1->SetLogy();

  canvas_margin(c1);


  TH1D *hist_empty = (TH1D*)gr1_2016->GetHistogram();
  hist_empty->SetName("DUMMY_FOR_AXIS");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();
  double Ymax = hist_empty->GetMaximum();

  hist_empty->GetYaxis()->SetTitle(Plotter.YAxisTitle);
  hist_empty->GetXaxis()->SetTitle(Plotter.XAxisTitle);
  //  hist_empty->GetYaxis()->SetRangeUser(Plotter.default_y_min+0.01, Ymax*Plotter.Hist_YAxis_MaxScale);
  hist_empty->GetYaxis()->SetRangeUser(0.9, Ymax*Plotter.Hist_YAxis_MaxScale);
  hist_axis(hist_empty);

  hist_empty->Draw("histsame");

  gr1_2016 -> SetFillColor(45);
  gr1_2016->SetLineWidth(3.0);
  gr1_2016->SetMarkerColor(kBlack);
  gr1_2016->SetMarkerStyle(22);
  gr1_2016->SetMarkerSize(1.5);
  gr1_2016->SetLineColor(kRed);
  gr1_2016->Draw("plsame");

  gr1_2017->SetLineWidth(3.0);
  gr1_2017->SetMarkerColor(kBlack);
  gr1_2017->SetMarkerStyle(21);
  gr1_2017->SetMarkerSize(1.5); 
  gr1_2017->SetLineColor(kGreen+4);
  gr1_2017->Draw("psame");

  gr1_2018->SetLineWidth(3.0);
  gr1_2018->SetMarkerColor(kBlack);
  gr1_2018->SetMarkerStyle(23);
  gr1_2018->SetMarkerSize(1.5);
  gr1_2018->SetLineColor(kBlue);
  gr1_2018->Draw("psame");

  lg->AddEntry(gr1_2016, "BB 2016", "pl");
  lg->AddEntry(gr1_2017, "BB 2017", "pl");
  lg->AddEntry(gr1_2018, "BB 2018", "pl");
  

  hist_empty->GetYaxis()->SetRangeUser(0.9, 1.2);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(Plotter.LatexTextLabel_Size);

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(Plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(Plotter.LatexTextCMS_X,Plotter.LatexTextCMS_Y, Plotter.LatexTextCMS);
  latex_Lumi.SetTextSize(Plotter.LatexTextLabel_Size);
  if(Era=="2016preVFP")latex_Lumi.DrawLatex(0.7, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(Era=="2016postVFP")latex_Lumi.DrawLatex(0.7, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(Era=="2016") latex_Lumi.DrawLatex(0.7, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(Era=="2017") latex_Lumi.DrawLatex(0.7, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(Era=="2018") latex_Lumi.DrawLatex(0.7, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(Era=="Run2") latex_Lumi.DrawLatex(0.7, 0.96, "137.9 fb^{-1} (13 TeV)");

  //  lg->SetNColumns(2);                                                                                                                                                                                                                
  lg->Draw();

  //  for(unsigned int il =0 ; il < tlat.size(); il++) latex_result.DrawLatex(Plotter.LatexTextLabel_X, Plotter.LatexTextLabel_Y-0.1 - 0.05*(il), tlat[il]);


  c1->SaveAs(Plotter.thiscut_plotpath+"/"+HistName+".png");
  c1->SaveAs(Plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << Plotter.syncpath <<  " TamsaOutput/Plots/" << endl;


}
