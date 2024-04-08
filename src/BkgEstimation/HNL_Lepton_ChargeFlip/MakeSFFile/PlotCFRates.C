#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void PlotCFRates(){

  TString LabelForWeb = "HNL_ChargeFlip_2023_Oct_Rates";

  vector<TString> eras =  {"2018", "2016b", "2017", "2018"};
  vector<TString> EtaBins = {"EtaRegion1","EtaRegion2","EtaRegion3","EtaRegion4","EtaRegion5","EtaRegion6","EtaRegion7","EtaRegion8","EtaRegion9"};

  for (auto era : eras){
    TString year = era;
    if(year.Contains("16")) year = "2016";
    for (auto EtaBin : EtaBins){
      
      HNLPlotter Plotter("HNL_ChargeFlipRates");
      Plotter.SetupPlotter(era,"","HNL_ChargeFlip");
      Plotter.DoDebug=false;
      Plotter.CopyToWebsite = true;
      //Plotter.SetLogY=true;
      //      Plotter.Hist_YAxis_MaxScale=100;

      TString path="HNL_CF_Electron_"+era+"_Rates.root";
    
      TH1D *hist_CF1             = Plotter.ConstructHist(path,"CFRate_Pt_"+EtaBin+"_POGTight");
      TH1D *hist_CF2             = Plotter.ConstructHist(path,"CFRate_Pt_"+EtaBin+"_TopHN");
      TH1D *hist_CF3             = Plotter.ConstructHist(path,"CFRate_Pt_"+EtaBin+"_HNL_ULID_"+year);
      hist_CF1->GetYaxis()->SetTitle("Rate");
      hist_CF1->GetXaxis()->SetTitle("p_{T} GeV");
      
      TString sEtaBin = "#eta < 0.8";
      if(EtaBin == "EtaRegion2") sEtaBin ="0.8 < #eta < 1.2";
      if(EtaBin == "EtaRegion3") sEtaBin ="1.2 < #eta < 1.442";
      if(EtaBin == "EtaRegion4") sEtaBin ="1.556 < #eta < 1.9";
      if(EtaBin == "EtaRegion5") sEtaBin ="1.9 < #eta < 2.1";
      if(EtaBin == "EtaRegion6") sEtaBin ="2.1 < #eta < 2.2";
      if(EtaBin == "EtaRegion7") sEtaBin ="2.2 < #eta < 2.3";
      if(EtaBin == "EtaRegion8") sEtaBin ="2.3 < #eta < 2.4";
      if(EtaBin == "EtaRegion9") sEtaBin ="2.4 < #eta < 2.5";

      Plotter.SaveHists({hist_CF1,hist_CF2,hist_CF3}, {"POGTight","TopHN","HNL_ULID_"+year}, "CF_Rates_"+era+"_"+EtaBin, LabelForWeb, {sEtaBin});
    }
  }
  
  return;
}

