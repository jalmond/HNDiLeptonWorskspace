#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       


void FakeRatePlotterDataEra(){
  
  vector<TString> Eras = {"2016","2017","2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString EtaBin = "";
  TString sVAR = "Muon [AJ30]";
  TString LabelForWeb = "HNL_LeptonFakeRates_2024_FakeRates_Era_EXOJX_Haneol";

  vector<TString> Flavour = {""};
  vector<TString> Vars = {""};
  
  
  vector<TString> IDs = {"HNL_ULID_FO_v1","HNL_ULID_FO_v2","HNL_ULID_FO_v3"};
  for( auto ID : IDs){
    for(auto flav : Flavour){
      for( auto  var : Vars){
	HNLPlotter Plotter("HNL_Lepton_FakeRate");
	Plotter.SetupPlotter("","","HNL_Lepton_FakeRate");
	Plotter.CopyToWebsite = true;
	Plotter.Hist_YAxis_MaxScale = 2;
	vector<TH1D*> hists;	
	vector<TString> LEG;	
	for( auto  Era : Eras){

	
	TString pathData="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+Era+"/RunRates__/HNL_Lepton_FakeRate_Data_FakeMuon.root";
	TString pathPrompt="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+Era+"/RunRates__/HNL_Lepton_FakeRate_MC.root";
	

	
	TString VAR = "PtParton_"+EtaBin+"AJ";
	
	TString VAR30 = "AwayJet pT > 30";
	

	TString NUM = "PtParton/Fake_PtParton_TightMuMu_"+ID+"_"+Era+"MuMu_AJ30_pt"+EtaBin+"";
	TString DENOM= "PtParton/Fake_PtParton_LooseMuMu_"+ID+"_"+Era+"MuMu_AJ30_pt"+EtaBin+"";

	
	TH1D *hist_Numerator     = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_TightMuMu_"+ID+"_"+Era+"MuMu_AJ30_pt"+EtaBin+"");
	TH1D *hist_Denominator   = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_LooseMuMu_"+ID+"_"+Era+"MuMu_AJ30_pt"+EtaBin+"");
	

	
	///// Set up axis 
	  hist_Numerator->GetYaxis()->SetTitle("Fake Rates");
	  hist_Numerator->GetXaxis()->SetRangeUser(0,59);
	  hist_Numerator->GetYaxis()->SetRangeUser(0,1);
	  hist_Numerator->GetXaxis()->SetTitle("Pt Parton [times SF]");
	  
	  ///// Setup MC hist for prompt sub
	  TH1D *hist_NumeratorPrompt     = Plotter.ConstructHist(pathPrompt,   NUM);
	  TH1D *hist_DenominatorPrompt   = Plotter.ConstructHist(pathPrompt,   DENOM);
	  
	  
	  /// Subtract Prompt      
	  hist_Numerator->Add(hist_NumeratorPrompt,-1);
	  hist_Denominator->Add(hist_DenominatorPrompt,-1);
	  hist_Numerator->Divide(hist_Denominator);
	  
	  hists.push_back(hist_Numerator);
	  LEG.push_back(Era);
	}

        TString VAR = "PtParton"+EtaBin+"_AJ30";

        TString sVAR = "Muon Channel";
	Plotter.SaveHists(hists, LEG , "Muon_FR_ID_"+ID+"_"+VAR+EtaBin, LabelForWeb, {sVAR});
	  
      
      }
    }
  }
  return;
}

