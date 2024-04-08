#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void GetProfileSF(){
  
  TString Analyzer = "HNL_Lepton_FakeRate";
  TString Plot_Name = "FakeCRCentral_AJ40_MVA_PtPartonUncorr";


  vector<TString> Eras = {"2016","2017","2018"};

  TString LabelForWeb = "HNL_GetProfileSF_Muon_PostJanJetX_Jan31";
  for (auto year : Eras){

    vector<TString> Bins = {"MuMu_HNL_ULID_FO_v0_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v9_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v9_b_"+year+"DATA"};
    //"MuMu_HNL_ULID_FO_v9_c_"+year+"DATA"};
        
    for( auto Bin : Bins){
      HNLPlotter Plotter(Analyzer);
      Plotter.SetupPlotter(year,"",Analyzer);
      Plotter.CopyToWebsite = true;
      
      TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/"+Analyzer+"/"+year+"/CheckProfile__/"+Analyzer+"_Data_Muon.root";
      
      vector<TProfile*> hists;
    

      //MuMu_HNL_LooseID_FO_v1_2018DATA
      Bin = Bin.ReplaceAll("_DATA","_"+year+"DATA");
      TFile* file = new TFile(path);
      TProfile* dataProf   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtPartonUncorr");
      dataProf->GetXaxis()->SetTitle("MVA Score");
      dataProf->GetYaxis()->SetTitle("Average p^{parton}_T");
      dataProf->GetYaxis()->SetRangeUser(0, 100);
      
      hists.push_back(dataProf);
      
      Plotter.default_y_min = 0;
      Plotter.default_y_max = 100;
      TString SF ="-999";
      if(year == "2016") SF=Plotter.SaveProfile(0.72, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+Bin+"_"+year, LabelForWeb, {});
      else SF=Plotter.SaveProfile(0.64, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCD_"+Bin+"_"+year, LabelForWeb, {});
      
      
      TString IDPrefix = Bin;
      IDPrefix=IDPrefix.ReplaceAll(year+"DATA","");
      
      TString outline = "if(DataYear == "+year;
      outline+=" && IsMuon && (LooseID == \""+IDPrefix + "\"+GetYearString())) return "+SF+";";
      
      cout <<  outline << endl;
      
    }
  }
  
  return;
}

