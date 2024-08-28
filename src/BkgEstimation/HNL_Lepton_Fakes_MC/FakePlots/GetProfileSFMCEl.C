#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void GetProfileSFMCElProcess(TString Era, TString Sample);

void GetProfileSFMCEl(){
  
  
  
  GetProfileSFMCElProcess("2016preVFP","TTLJ");
  GetProfileSFMCElProcess("2016postVFP","TTLJ");
  GetProfileSFMCElProcess("2017","TTLJ");
  GetProfileSFMCElProcess("2018","TTLJ");



  GetProfileSFMCElProcess("2016preVFP","QCD");
  GetProfileSFMCElProcess("2016postVFP","QCD");
  GetProfileSFMCElProcess("2017","QCD");
  GetProfileSFMCElProcess("2018","QCD");


}

void GetProfileSFMCElProcess(TString Era, TString Sample){
    
  vector<TString> Eras = {Era};


  map<TString, TString> mapSF;


  TString sEra = Era;
  if(Era == "2016preVFP") sEra = "2016";
  if(Era == "2016postVFP") sEra = "2016";


  TString LabelForWeb = "HNL_GetProfileSFMCEl_July14_EGamma";

  vector<TString> EtaBins = {"EB1","EB2","EE1","EE2"};

  //FakeCRCentral_MVA_LF1_BB_PtPartonUncorr
  vector<TString> LooseIDs {  
      "EE_HNL_ULID_FO_v0_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v1_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v2_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v3_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v4_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v5_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v6_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v7_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v8_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v9_a_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v1_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v2_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v3_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v4_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v5_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v6_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v7_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v8_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v9_b_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v1_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v2_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v3_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v4_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v5_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v6_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v7_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v8_c_"+sEra+"_MC",
      "EE_HNL_ULID_FO_v9_c_"+sEra+"_MC"};


  for (auto year : Eras){

    for( auto EtaBin : EtaBins){


      double MVACut = -1;
      if(EtaBin.Contains("EB")&& Era.Contains("2016")) MVACut = 0.25;
      if(EtaBin.Contains("EB")&& Era == "2017") MVACut = 0.4;
      if(EtaBin.Contains("EB")&& Era == "2018") MVACut = 0.4;
      if(EtaBin.Contains("EE") && Era.Contains("2016")) MVACut = 0.4;
      if(EtaBin.Contains("EE") && Era == "2017") MVACut = 0.45;
      if(EtaBin.Contains("EE") && Era == "2018") MVACut = 0.5;
      for( auto LooseID : LooseIDs){
	HNLPlotter Plotter("HNL_LeptonFakeRatesMC");
	Plotter.SetupPlotter(year,"","HNL_LeptonFakeRatesMC");
	Plotter.CopyToWebsite = true;
	
	TString MCString = Sample;
	TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfileEE__/HNL_LeptonFakeRateMC_Top.root";
	if(Sample == "QCD"){
	  path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_FakeRate_MC/"+year+"/CheckProfileEE__/HNL_LeptonFakeRateMC_QCD.root";                                                                       
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

	mapSF [year + "_"+EtaBin + "_"+LooseID+"_"+Sample] =Plotter.SaveProfile(MVACut,hists, {MCString+" "+EtaBin, "Data - Prompt Fake "+EtaBin}, "MeasurementRegion_"+LooseID+MCString+"_"+EtaBin+"_"+year, LabelForWeb, {});
	
      }
      
    }
  }

  for(auto i : mapSF) {
    TString first = i.first;
    TString second = i.second;
    first = first.ReplaceAll("_EB1"," EB1");
    first = first.ReplaceAll("_EB2"," EB2");
    first = first.ReplaceAll("_EE1"," EE1");
    first = first.ReplaceAll("_EE2"," EE2");
    first = first.ReplaceAll("_EE"," EE");
    first = first.ReplaceAll("_MC_"," MC ");
    first = first.ReplaceAll("_DATA_"," DATA ");

    cout << first << "   " << second << endl;

  }

  
  return;
}

