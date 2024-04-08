#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void GetProfileSFMCProcess(TString Era, TString EtaBin, TString Sample);

void GetProfileSFEl(){

  GetProfileSFMCProcess("2017", "EB1", "TTLJ");
  GetProfileSFMCProcess("2017", "EB2", "TTLJ");
  GetProfileSFMCProcess("2017", "EE1", "TTLJ");
  GetProfileSFMCProcess("2017", "EE2", "TTLJ");

  GetProfileSFMCProcess("2017", "EB1", "QCD");
  GetProfileSFMCProcess("2017", "EB2", "QCD");
  GetProfileSFMCProcess("2017", "EE1", "QCD");
  GetProfileSFMCProcess("2017", "EE2", "QCD");
}

void GetProfileSFMCProcess(TString Era, TString EtaBin, TString Sample){
    
  vector<TString> Eras = {Era};

  TString LabelForWeb = "HNL_GetProfileSFMC_Jan24_Electron";

  vector<TString> EtaBins = {EtaBin};

  //FakeCRCentral_MVA_LF1_BB_PtPartonUncorr
  vector<TString> LooseIDs {"EE_HNL_LooseID_FO_v1_MC",
      "EE_HNL_LooseID_FO_v2_MC",
      "EE_HNL_LooseID_FO_v1_DJ1_MC",
      "EE_HNL_LooseID_FO_v1_DJ2_MC",
      "EE_HNL_LooseID_FO_v1_DJ3_MC",
      "EE_HNL_LooseID_FO_v1_DJ4_MC"};

  double MVACut = -1;
  if(EtaBin.Contains("EB")&& Era == "2016") MVACut = 0.25;
  if(EtaBin.Contains("EB")&& Era == "2017") MVACut = 0.4;
  if(EtaBin.Contains("EB")&& Era == "2018") MVACut = 0.4;
  if(EtaBin.Contains("EE") && Era == "2016") MVACut = 0.4;
  if(EtaBin.Contains("EE") && Era == "2017") MVACut = 0.45;
  if(EtaBin.Contains("EE") && Era == "2018") MVACut = 0.5;

  
  for (auto year : Eras){
    for( auto EtaBin : EtaBins){
      for( auto LooseID : LooseIDs){
	HNLPlotter Plotter("HNL_LeptonFakeRatesMC");
	Plotter.SetupPlotter(year,"","HNL_LeptonFakeRatesMC");
	Plotter.CopyToWebsite = true;
	
	TString MCString = Sample;
	TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfileEE__/HNL_Lepton_FakeRate_MC_SkimTree_FakeEventSkimBDT_TTLJ_powheg.root";
	if(Sample == "QCD"){
	  path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfileEE__/HNL_LeptonFakeRateMC_QCD.root";                                                            
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
	
	
	Plotter.SaveProfile(MVACut,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});

      }
      
    }
  }
  
  return;
}

