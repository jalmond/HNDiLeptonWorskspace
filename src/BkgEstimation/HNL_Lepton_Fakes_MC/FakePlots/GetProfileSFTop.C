#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void GetProfileSFTop(){
  
  vector<TString> Eras = {"2017"};//,"2017","2018"};

  TString LabelForWeb = "HNL_GetProfileSFMC";

  //  vector<TString> EtaBins = {"HF_BB","LF_BB","HF_EC","LF_EC" };//"EB1","EB2","EE1","EE2"};
  //  vector<TString> PtBins = {"_Pt1_", "_Pt2_","_Pt3_","_Pt4_"};
  vector<TString> PtBins = {""};
  //  vector<TString> EtaBins = {"LF1_BB","LF2_BB","LF3_BB","LF4_BB","LF4_BB","LF5__BB","HF1_BB","HF2_BB","HF3_BB","HF4_BB"};
  vector<TString> EtaBins = {"BB", "EC"};

  //FakeCRCentral_MVA_LF1_BB_PtPartonUncorr
  vector<TString> LooseIDs {"MuMu_HNL_LooseID__MC"};
  for (auto year : Eras){
    for( auto EtaBin : EtaBins){
      for( auto PtBin : PtBins){
	for( auto LooseID : LooseIDs){
	  HNLPlotter Plotter("HNL_LeptonFakeRatesMC");
	  Plotter.SetupPlotter(year,"","HNL_LeptonFakeRatesMC");
	  Plotter.CopyToWebsite = true;
	  
	  TString MCString = "MC";
	  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRateMC/"+year+"/Standard__/HNL_LeptonFakeRateMC_SkimTree_FakeEventSkimBDT_TTLJ_powheg.root";
	  cout << path << endl;      
	  vector<TProfile*> hists;
	  
	  TFile* file = new TFile(path);
	  cout << "MCProfile/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr" << endl;
	  TProfile* dataProf   = (TProfile*) file->Get("MCProfile/"+LooseID+"/FakeCR"+PtBin+"Central_MVA_"+EtaBin+"_PtPartonUncorr");
	  dataProf->GetXaxis()->SetTitle("MVA Score");
	  dataProf->GetYaxis()->SetTitle("Average p^{parton}_T");
	  dataProf->GetYaxis()->SetRangeUser(0, 100);
	  
	  hists.push_back(dataProf);
	  
	  Plotter.default_y_min = 0;
	  Plotter.default_y_max = 100;
	  
	  if(year=="2016")Plotter.SaveProfile(0.72,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "Top_"+LooseID+MCString+"_"+EtaBin+PtBin+"_"+year, LabelForWeb, {});
	  else  Plotter.SaveProfile(0.64,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "Top_"+LooseID+MCString+"_"+EtaBin+PtBin+"_"+year, LabelForWeb, {});
	}
      }
    }
  }
  
  return;
}

