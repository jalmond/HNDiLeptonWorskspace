#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void GetProfileSFEl(){
  
  vector<TString> Eras = {"2016","2017","2018"};

  TString LabelForWeb = "HNL_GetProfileSF_El_PostJanJetX_Jan31";
  TString Analyzer = "HNL_Lepton_FakeRate";
  TString Plot_Name = "FakeCRCentral_AJ40_MVA_PtPartonUncorr";


  for (auto year : Eras){

    
    vector<TString> Bins = {"EE_HNL_ULID_FO_v0_"+year+"DATA",
                            "EE_HNL_ULID_FO_v1_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v1_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v1_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v2_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v2_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v2_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v3_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v3_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v3_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v4_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v4_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v4_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v5_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v5_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v5_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v6_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v6_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v6_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v7_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v7_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v7_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v8_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v8_b_"+year+"DATA",
                            "EE_HNL_ULID_FO_v8_c_"+year+"DATA",
                            "EE_HNL_ULID_FO_v9_a_"+year+"DATA",
                            "EE_HNL_ULID_FO_v9_b_"+year+"DATA"};

    vector<TString> EtaBins = {"BB","EC"};
    
    for( auto EtaBin : EtaBins){
      for( auto Bin : Bins){
	
	HNLPlotter Plotter(Analyzer);
	Plotter.SetupPlotter(year,"",Analyzer);
	Plotter.CopyToWebsite = true;

	TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/"+Analyzer+"/"+year+"/CheckProfileEE__/"+Analyzer+"_Data_EG.root";
	
	vector<TProfile*> hists;
	
	TFile* file = new TFile(path);
	
	//Bin = Bin.ReplaceAll("_DATA","_"+year+"DATA");

	TProfile* dataProf   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_"+EtaBin+"_PtPartonUncorr");
	dataProf->GetXaxis()->SetTitle("MVA Score");
	dataProf->GetYaxis()->SetTitle("Average p^{parton}_T");
	dataProf->GetYaxis()->SetRangeUser(0, 100);
	
	hists.push_back(dataProf);
	
	Plotter.default_y_min = 0;
	Plotter.default_y_max = 100;
	
	TString SF ="-999";

	if(year == "2016" && EtaBin.Contains("BB")) SF= Plotter.SaveProfile(0.25, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});	
	if(year == "2016" && EtaBin.Contains("EC")) SF= Plotter.SaveProfile(0.4, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2017" && EtaBin.Contains("BB")) SF= Plotter.SaveProfile(0.4, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2017" && EtaBin.Contains("EC")) SF= Plotter.SaveProfile(0.45, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2018" && EtaBin.Contains("BB")) SF= Plotter.SaveProfile(0.4, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2018" && EtaBin.Contains("EC")) SF= Plotter.SaveProfile(0.5, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	
	TString EtaLabel = (EtaBin.Contains("BB")) ?  " && Lep.IsBB() " : " && Lep.IsEC() ";

	TString IDPrefix = Bin;
	IDPrefix=IDPrefix.ReplaceAll(year+"DATA","");
	
	TString outline = "if(DataYear == "+year;
	outline+=" && !IsMuon "+EtaLabel+"&& (LooseID == \""+IDPrefix + "\"+GetYearString())) return "+SF+";";

	cout <<  outline << endl;

	
      }
    }
  }
  
  return;
}

