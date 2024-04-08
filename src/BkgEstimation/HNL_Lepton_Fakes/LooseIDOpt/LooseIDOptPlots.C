#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void LooseIDOptPlots(){

  TString LabelForWeb = "HNL_LeptonFakeRate_TEST";

  vector<TString> eras =  {"2016"};//, "2017", "2018"};
  vector<TString> EtaBins = {"Eta1","Eta2","Eta3"};

  vector<TString> BkgType = {"QCD"};//,"Top","MC"};
  vector<TString> histnames = {"MVA","ISO","QCD_LFvsHF","QCD_BvsC","BScore","CvsB","CvsL","PtRatio","PtRel"};
  for(auto Bkg : BkgType){
    
    TString ID="MuMu_HNL_ID";
    for (auto year : eras){
      for (auto EtaBin : EtaBins){
	
	for(auto histname :histnames){
	  HNLPlotter Plotter("HNL_LeptonFakeRate");
	  Plotter.SetupPlotter(year,"","HNL_LeptonFakePlots");
	  Plotter.DoDebug=false;
	  Plotter.CopyToWebsite = true;
	  
	  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/MCFakes__/HNL_LeptonFakeRate_"+Bkg+".root";
	  
	  //Plotter.XaxisMin = 10;
	  //Plotter.XaxisMax = 80;
	  //MCFakeOpt/Inclusive/MVA_
	  TH1D *hist_LF_Loose          = Plotter.ConstructHist(path,"MCFakeOpt/Inclusive/"+histname+"_LF_"+EtaBin  + "_"+ID+"_Loose");
	  TH1D *hist_HF_Loose          = Plotter.ConstructHist(path,"MCFakeOpt/Inclusive/"+histname+"_HF_"+EtaBin  + "_"+ID+"_Loose");
	  hist_LF_Loose->Scale(1./hist_LF_Loose->Integral());
	  hist_HF_Loose->Scale(1./hist_HF_Loose->Integral());
	  
	  
	  //hist_LF_Loose->GetYaxis()->SetTitle("Fake Rates");
	  //hist_LF_Tight->GetXaxis()->SetTitle(PtTypeString);
	  
	  Plotter.SaveHists({hist_LF_Loose,hist_HF_Loose}, {"LF "+ EtaBin, "HF "  + EtaBin}, Bkg+histname+"_HNL_LeptonFakeRateID_"+"_"+EtaBin, LabelForWeb, {""});
	}
      }
    }
  }
  
  return;
}

