#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void TrileptonControlRegion(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMuMu"};

  for (auto year : eras){
    for (auto channel : channels){
      HNLPlotter Plotter("HNL_ControlRegionPlotter24_LLL");
	//// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion_Plotter","/LLL_CR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      
      //Plotter.samples_to_use = {"ttbar_ll","DY","VV_incl"};
      
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      Plotter.HistPath= {"HNL_ZG_ThreeLepton_CR/HNL_ULID/MuMuMu/RegionPlots_MuMuMu",
			 "HNL_WZ_ThreeLepton_CR/HNL_ULID/MuMuMu/RegionPlots_MuMuMu"};
      
      Plotter.RegionType = {"ZG CR","WZ CR"};
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("SKEvent/Ev_PuppiMET_T1ULxyCorr" ,  "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 50}, 0, 50);
      
      //      Plotter.AddHist("M_ll" ,"MLL"  , "GeV", {2.}, 0, 400);
      //Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Leptons/Lep_1_pt" ,"LPT1" , "GeV", {5.}, 20, 200);
      //Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "GeV", {5.}, 10, 200);
      //Plotter.AddHist("Leptons/Lep_3_pt" ,"LPT3" , "GeV", {5.}, 10, 200);
      //Plotter.AddHist("Leptons/Lep_1_eta" ,"Eta" , "", {10.}, -3, 3);
      //Plotter.AddHist("Leptons/Lep_2_eta" ,"Eta" , "", {10.}, -3, 3);
      //Plotter.AddHist("Leptons/Lep_3_eta" ,"Eta" , "", {10.}, -3, 3);
      
      ////// Make list and run plotting
      Plotter.DrawStackCutFlowWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      //Plotter.Summary();
    
    }
  }
  
  
  return;
}

