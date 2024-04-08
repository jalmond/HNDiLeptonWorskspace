#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void GetProfileSFEl_Plot(){
  
  vector<TString> Eras = {"2017"};

  TString LabelForWeb = "HNL_GetProfileSFElNov19";

  vector<TString> Bins = {"EE_HNL_LooseID_DATA",
			  "EE_HNL_LooseID_v2_DATA",
			  "EE_HNL_LooseID_v3_DATA",
			  "EE_HNL_LooseID_v4_DATA",
			  "EE_HNL_LooseID_v5_DATA",
			  "EE_HNL_LooseID_v6_DATA",
			  "EE_HNL_LooseID_v7_DATA"};


  vector<TString> EtaBins = {"BB","EC"};
  
  for (auto year : Eras){
    for( auto Bin : Bins){
      for( auto EtaBin : EtaBins){
	HNLPlotter Plotter("HNL_LeptonFakeRates");
	Plotter.SetupPlotter(year,"","HNL_LeptonFakeRates");
	Plotter.CopyToWebsite = true;
	
	TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/CheckProfileEE__/HNL_LeptonFakeRate_Data_EG.root";
	
	vector<TProfile*> hists;
	
	TFile* file = new TFile(path);
	cout << "DATAProfile/"+Bin+"/FakeCRCentral_MVA_"+EtaBin+"_PtPartonUncorr" << endl;
	TProfile* dataProf   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_Inclusive_MVA_"+EtaBin+"_PtPartonUncorr");
	dataProf->GetXaxis()->SetTitle("Lepton MVA_{NP}");
	dataProf->GetYaxis()->SetTitle("Average p^{cone}_{T}");
	dataProf->GetYaxis()->SetRangeUser(0, 100);
	
	hists.push_back(dataProf);

        TProfile* dataProf2   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_Inclusive_MVA_"+EtaBin+"_PtParton");

	hists.push_back(dataProf2);

	Plotter.default_y_min = 0;
	Plotter.default_y_max = 100;
	
	if(year == "2016" && EtaBin.Contains("BB")) Plotter.SaveProfile(0.25, hists, {"Uncorrected PtParton", "Corrected PtParton"},  "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2016" && EtaBin.Contains("EC")) Plotter.SaveProfile(0.4, hists, {"Uncorrected PtParton", "Corrected PtParton"} , "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2017" && EtaBin.Contains("BB")) Plotter.SaveProfile(0.4, hists, {"Uncorrected PtParton", "Corrected PtParton"} , "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {"WP (0.4)", "Flavour Electron","Correction factor = 0.689"});
	if(year == "2017" && EtaBin.Contains("EC")) Plotter.SaveProfile(0.45, hists, {"Uncorrected PtParton", "Corrected PtParton"},  "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {"WP (0.45)", "Flavour Electron","Correction factor = 0.631"});
	if(year == "2018" && EtaBin.Contains("BB")) Plotter.SaveProfile(0.4, hists, {"Uncorrected PtParton", "Corrected PtParton"} , "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	if(year == "2018" && EtaBin.Contains("EC")) Plotter.SaveProfile(0.5, hists, {"Uncorrected PtParton", "Corrected PtParton"} , "MeasurementRegion_QCD_"+EtaBin+Bin+"_"+year, LabelForWeb, {});
	
	
      }
    }
  }
  
  return;
}

