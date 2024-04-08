#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void GetProfileSFMCProcess(TString Era, TString Sample);

void GetProfileSFMC(){

  GetProfileSFMCProcess("2017","TTLJ");
  GetProfileSFMCProcess("2017","QCD");

}

void GetProfileSFMCProcess(TString Era, TString Sample){
    
  vector<TString> Eras = {Era};

  TString LabelForWeb = "HNL_GetProfileSFMC_Jan24_Muon";

  vector<TString> EtaBins = {"BB","EC"};

  //FakeCRCentral_MVA_LF1_BB_PtPartonUncorr
  vector<TString> LooseIDs {"MuMu_HNL_LooseID_FO_v1_MC",
      "MuMu_HNL_LooseID_FO_v2_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ1_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ2_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ3_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ4_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ5_MC",
      "MuMu_HNL_LooseID_FO_v1_DJ6_MC"};

  for (auto year : Eras){
    for( auto EtaBin : EtaBins){
      for( auto LooseID : LooseIDs){
	HNLPlotter Plotter("HNL_LeptonFakeRatesMC");
	Plotter.SetupPlotter(year,"","HNL_LeptonFakeRatesMC");
	Plotter.CopyToWebsite = true;
	
	TString MCString = Sample;
	TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfile__/HNL_Lepton_FakeRate_MC_SkimTree_FakeEventSkimBDT_TTLJ_powheg.root";
	if(Sample == "QCD"){
	  path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfile__/HNL_LeptonFakeRateMC_QCD.root";                                                                       
	}
	
	cout << path << endl;      

	vector<TProfile*> hists;
	
	TFile* file = new TFile(path);
	cout << "MCProfile/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr" << endl;
	TProfile* dataProf   = (TProfile*) file->Get("MCProfile/"+LooseID+"/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr");
	dataProf->GetXaxis()->SetTitle("MVA Score");
	dataProf->GetYaxis()->SetTitle("Average p^{parton}_T");
	dataProf->GetYaxis()->SetRangeUser(0, 100);
	
	hists.push_back(dataProf);
	
	Plotter.default_y_min = 0;
	Plotter.default_y_max = 100;
	
	
	if(year=="2016")Plotter.SaveProfile(0.72,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});
	else  Plotter.SaveProfile(0.64,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});
      }
      
    }
  }
  
  return;
}

