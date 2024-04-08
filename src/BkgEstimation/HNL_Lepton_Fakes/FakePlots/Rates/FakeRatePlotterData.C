#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       


void FakeRatePlotterData(){
  
  vector<TString> Eras = {"2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "HNL_LeptonFakeRates_2024_FakeRates";

  vector<TString> Flavour = {""};
  vector<TString> Vars = {""};
  
  for (auto Era : Eras){
    
    vector<TString> IDs = {"HNL_ULID_FO_v1_"+Era};
    for( auto ID : IDs){
      for(auto flav : Flavour){
	for( auto  var : Vars){
	  HNLPlotter Plotter("HNL_Lepton_FakeRate");
	  Plotter.SetupPlotter(Era,"","HNL_Lepton_FakeRate");
	  Plotter.CopyToWebsite = true;
	  
	  TString pathData="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+Era+"/RunRates__/HNL_Lepton_FakeRate_Data_FakeMuon.root";
	  TString pathPrompt="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+Era+"/RunRates__/HNL_Lepton_FakeRate_MC.root";
	  
	  vector<TH1D*> hists;
	  
	  TString VAR = "PtParton_BB_AJ";

	  TString VAR25 = "PtParton AJ25";
	  TString VAR30 = "PtParton AJ30";
	  TString VAR40 = "PtParton AJ40";
	  TString sVAR = "(Barrel) Muon Channel";
	  TString NUM = "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ30_pt_BB";
	  TString DENOM= "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ30_pt_BB";

          TString NUM25 = "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ25_pt_BB";
          TString DENOM25= "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ25_pt_BB";
	  
          TString NUM40 = "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ40_pt_BB";
          TString DENOM40= "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ40_pt_BB";


	  TH1D *hist_Numerator     = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ30_pt_BB");
	  TH1D *hist_Denominator   = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ30_pt_BB");
	  
	  // 25
          TH1D *hist_Numerator25     = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ25_pt_BB");
          TH1D *hist_Denominator25   = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ25_pt_BB");

	  // 40 
          TH1D *hist_Numerator40     = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_TightMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ40_pt_BB");
          TH1D *hist_Denominator40   = Plotter.ConstructHist(pathData,      "PtParton/Fake_PtParton_LooseMuMu_HNL_ULID_FO_v1_"+Era+"MuMu_AJ40_pt_BB");


	  ///// Set up axis 
	  hist_Numerator->GetYaxis()->SetTitle("Fake Rates");
	  hist_Numerator->GetYaxis()->SetRangeUser(0,1);
	  
	  //hist_Numerator->GetXaxis()->SetRangeUser(0, 2.5);
	  //hist_Numerator->GetXaxis()->SetTitle("Lep #eta");
	  
	  ///// Setup MC hist for prompt sub
	  TH1D *hist_NumeratorPrompt     = Plotter.ConstructHist(pathPrompt,   NUM);
	  TH1D *hist_DenominatorPrompt   = Plotter.ConstructHist(pathPrompt,   DENOM);
	  
          TH1D *hist_NumeratorPrompt25     = Plotter.ConstructHist(pathPrompt,   NUM25);
          TH1D *hist_DenominatorPrompt25   = Plotter.ConstructHist(pathPrompt,   DENOM25);
	  
	  TH1D *hist_NumeratorPrompt40     = Plotter.ConstructHist(pathPrompt,   NUM40);
          TH1D *hist_DenominatorPrompt40   = Plotter.ConstructHist(pathPrompt,   DENOM40);

	  
	  /// Subtract Prompt      
	  hist_Numerator->Add(hist_NumeratorPrompt,-1);
	  hist_Denominator->Add(hist_DenominatorPrompt,-1);
	  hist_Numerator->Divide(hist_Denominator);
	  
	  hist_Numerator25->Add(hist_NumeratorPrompt25,-1);
          hist_Denominator25->Add(hist_DenominatorPrompt25,-1);
          hist_Numerator25->Divide(hist_Denominator25);

	  hist_Numerator40->Add(hist_NumeratorPrompt40,-1);
          hist_Denominator40->Add(hist_DenominatorPrompt40,-1);
          hist_Numerator40->Divide(hist_Denominator40);

	  hists.push_back(hist_Numerator);
	  hists.push_back(hist_Numerator25);
	  hists.push_back(hist_Numerator40);
	  
	  
	  //Plotter.DrawEfficiency(  hists  , {""+ID+"",""+ID+" [noSub]"}, "Fake_Data_"+ID+"",    LabelForWeb);
	  
	  Plotter.SaveHists(hists, {VAR25, VAR30,VAR40}, "Muon_FR_"+VAR+"_"+Era, LabelForWeb, {sVAR});
	  
	}
      }
    }
  }
  return;
}

