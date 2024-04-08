#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SSControlRegionMVA(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotter1611");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter","/SS_CR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      ///Plotter.ScaleSample("WZ_pythia",0.95);
      vector<TString> Dirs = {	"HNTightV2",
				"HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ40",  
				"HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ40",
				"HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ40",
				"HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ40",   
				"HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ40",  
				"HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ40",
				"HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ40",
				"HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ40",  
				"HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ40",  
				"HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ40", 
				"HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ40", 
				"HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ40",   
				"HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ40",  
				"HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ40",  
				"HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ40",  
				"HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ40",   
				"HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ40",
				"HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ40",
				"HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ40",  
				"HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ40",
				"HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ40",
				"HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ40",
				"HNL_ULID_HNL_ULID_FOv7_Standard_PtCorr_AJ40",
				"HNL_ULID_HNL_ULID_FOv7_Standard_PtParton_AJ40",
				"HNL_ULID_HNL_ULID_FOv7_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_Pt_AJ40",

				"HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_Pt_AJ30",

				"HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv7_Standard_Pt_AJ60"};


      vector<TString> HPaths,RegionTypes;
      //for(auto id : Dirs) HPaths.push_back( "HNL_SSPresel_TwoLepton/"+channel+"/"+id+"/LeptonMVARegionPlots_"+channel);
      //for(auto id : Dirs) HPaths.push_back( "HNL_HighMassNP_TwoLepton_CR/"+channel+"/"+id+"/LeptonMVARegionPlots_"+channel);                                                                                         
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassBJet_TwoLepton_CR/"+channel+"/"+id+"/LeptonMVARegionPlots_"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_",""));                   
      //for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_",""));                   
      //for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_",""));                   

      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("Lepton__lep1_mva_Mu_Fake_QCD_BvsC_v5" ,"MVA" , "", {2.}, -1, 1);
      Plotter.AddHist("Lepton__lep1_mva_Mu_Fake_QCD_LFvsHF_v5" ,"MVA" , "", {2.}, -1, 1);
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

