#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       


void FakeRatePlotterDataElectron(){
  
  vector<TString> Eras = {"2017"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "HNL_LeptonFakeRates_Electron_2023_FakeRates_Sep25v2";

  vector<TString> IDs = {"HNL_ULID_2017","HNTightV2"};
  vector<TString> Vars = {"pt","pt_BB","pt_EC","eta_fine"};
  vector<TString> Flavour = {"","LF_","HFB_","HFC_"};
  for (auto year : Eras){
    for( auto ID : IDs){
      for(auto flav : Flavour){
	for( auto  var : Vars){
	  HNLPlotter Plotter("HNL_LeptonFakeRate");
	  Plotter.SetupPlotter(year,"","HNL_LeptonFakeRate");
	  Plotter.CopyToWebsite = true;
	  
	  TString pathData="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/HNL_LeptonFakeRate_SkimTree_HNFakeBDT_Data.root";
	  TString pathPrompt="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/HNL_LeptonFakeRate_SkimTree_HNFakeBDT_Prompt.root";
	  
	  vector<TH1D*> hists;
	  cout << "Fake_TightEE_"+ID+"_EE_40_"+flav+var << endl;
	  TH1D *hist_Numerator     = Plotter.ConstructHist(pathData,      "Fake_TightEE_"+ID+"_EE_40_"+flav+var);
	  TH1D *hist_Denominator   = Plotter.ConstructHist(pathData,      "Fake_LooseEE_"+ID+"_EE_40_"+flav+var);
	  
	  ///// Set up axis 
	  hist_Numerator->GetYaxis()->SetTitle("Fake Rates");
	  hist_Numerator->GetYaxis()->SetRangeUser(0,0.6);
	  
	  if(var.Contains("pt")){
	    if (flav.Contains("HF")){
	      hist_Numerator->GetXaxis()->SetRangeUser(10,60);
	      hist_Numerator->GetYaxis()->SetRangeUser(0,0.1);
	    }
	    else{
	      hist_Numerator->GetXaxis()->SetRangeUser(10,99);
	    }
	    hist_Numerator->GetXaxis()->SetTitle("Lep p_{T} (GeV)");
	  }
	  if(var == "eta_fine"){
	    hist_Numerator->GetXaxis()->SetRangeUser(0, 2.5);
	    hist_Numerator->GetXaxis()->SetTitle("Lep #eta");
	  }
	  
	  ///// Setup MC hist for prompt sub
	  TH1D *hist_NumeratorPrompt     = Plotter.ConstructHist(pathPrompt,   "Fake_TightEE_"+ID+"_EE_40_"+flav+var);
	  TH1D *hist_DenominatorPrompt   = Plotter.ConstructHist(pathPrompt,   "Fake_LooseEE_"+ID+"_EE_40_"+flav+var);
	  
	  TH1D * NoSubtractionN = (TH1D*)hist_Numerator->Clone("N");
	  TH1D * NoSubtractionD = (TH1D*)hist_Denominator->Clone("D");
	  NoSubtractionN->Divide(NoSubtractionD);
	  
	  /// Subtract Prompt      
	  hist_Numerator->Add(hist_NumeratorPrompt,-1);
	  hist_Denominator->Add(hist_DenominatorPrompt,-1);
	  hist_Numerator->Divide(hist_Denominator);
	  
	  hists.push_back(hist_Numerator);
	  hists.push_back(NoSubtractionN);
	  
	  //Plotter.DrawEfficiency(  hists  , {""+ID+"",""+ID+" [noSub]"}, "Fake_Data_"+ID+"",    LabelForWeb);
	  
	  TString FlavTag = "";
	  if(flav != ""){
	    FlavTag = " " + flav +" ";
	    FlavTag = FlavTag.ReplaceAll("_","");
	  }
	  Plotter.SaveHists(hists, {""+ID+" "+FlavTag,""+ID+" [noSub]"}, "Electron_FR_"+ID+"_"+var+flav, LabelForWeb, {});
	  
	}
      }
    }
  }
  return;
}

