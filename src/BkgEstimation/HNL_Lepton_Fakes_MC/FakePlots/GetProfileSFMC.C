#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void GetProfileSFMCProcess(TString Era, TString Sample);

void GetProfileSFMC(){

  
  GetProfileSFMCProcess("2016preVFP","TTLJ");
  GetProfileSFMCProcess("2016postVFP","TTLJ");
  GetProfileSFMCProcess("2017","TTLJ");
  GetProfileSFMCProcess("2018","TTLJ");

  GetProfileSFMCProcess("2016preVFP","QCD");
  GetProfileSFMCProcess("2016postVFP","QCD");
  GetProfileSFMCProcess("2017","QCD");
  GetProfileSFMCProcess("2018","QCD");


}

void GetProfileSFMCProcess(TString Era, TString Sample){
    
  vector<TString> Eras = {Era};


  map<TString, TString> mapSF;

  TString sEra = Era;
  if(Era == "2016preVFP") sEra = "2016";
  if(Era == "2016postVFP") sEra = "2016";


  TString LabelForWeb = "HNL_GetProfileSFMC_July14_Muon";

  vector<TString> EtaBins = {"BB","EC"};

  //FakeCRCentral_MVA_LF1_BB_PtPartonUncorr
  vector<TString> LooseIDs {  "MuMu_HNL_ULID_FO_v0_"+sEra+"_MC",
                              "MuMu_HNL_ULID_FO_v1_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v2_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v3_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v4_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v5_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v6_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v7_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v8_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v9_a_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v1_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v2_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v3_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v4_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v5_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v6_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v7_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v8_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v9_b_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v1_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v2_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v3_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v4_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v5_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v6_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v7_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v8_c_"+sEra+"_MC",
      "MuMu_HNL_ULID_FO_v9_c_"+sEra+"_MC",};


//"MuMu_HNL_LooseID_FO_"+sEra+"_MC"};
  //MuMu_HNL_ULID_FO_v6_a_2018_MC

  for (auto year : Eras){

    for( auto EtaBin : EtaBins){
      for( auto LooseID : LooseIDs){
	HNLPlotter Plotter("HNL_LeptonFakeRatesMC");
	Plotter.SetupPlotter(year,"","HNL_LeptonFakeRatesMC");
	Plotter.CopyToWebsite = true;
	
	TString MCString = Sample;
	TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfile__/HNL_LeptonFakeRateMC_Top.root";
	if(Sample == "QCD"){
	  path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfile__/HNL_LeptonFakeRateMC_QCD.root";                                                                       
	}
	
	cout << path << endl;      

	vector<TProfile*> hists;
	
	TFile* file = new TFile(path);
	cout << "MCProfile/"+LooseID+"/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr" << endl;
	TProfile* dataProf   = (TProfile*) file->Get("MCProfile/"+LooseID+"/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr");
	dataProf->GetXaxis()->SetTitle("MVA Score");
	dataProf->GetYaxis()->SetTitle("Average p^{parton}_T");
	dataProf->GetYaxis()->SetRangeUser(0, 100);
	
	hists.push_back(dataProf);
	
	Plotter.default_y_min = 0;
	Plotter.default_y_max = 100;
	
	
	if(year.Contains("2016")) mapSF [year + "_"+EtaBin + "_"+LooseID+"_"+Sample] = Plotter.SaveProfile(0.72,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});
	else   mapSF [year + "_"+EtaBin + "_"+LooseID + "_"+Sample] = Plotter.SaveProfile(0.64,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});
      }
      
    }
  }
  
  for(auto i : mapSF) {
    TString first = i.first;
    TString second = i.second;
    first = first.ReplaceAll("_BB"," BB");
    first = first.ReplaceAll("_EC"," EC");
    first = first.ReplaceAll("_MuMu"," MuMu");
    first = first.ReplaceAll("_MC_"," MC ");
    first = first.ReplaceAll("_DATA_"," DATA ");
    
    cout << first << "   " << second << endl;

  }
  return;
}

