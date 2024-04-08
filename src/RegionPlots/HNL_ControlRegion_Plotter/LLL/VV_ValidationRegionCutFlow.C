#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void VV_ValidationRegionCutFlow(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {""};

  for (auto year : eras){
    for (auto channel : channels){
      for (auto WZ  :WZs ){
	HNLPlotter Plotter("HNL_ControlRegionPlotter0923v3_"+WZ);
	//// change def
	Plotter.DoDebug=true;
	Plotter.MergeZeroBins = false;
	Plotter.CopyToWebsite = true;
	
	//// Setup plotter
	Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter");
	///Plotter.infilepath = .... if inut file is not in Mergeddir
	
	//Plotter.samples_to_use = {"ttbar_ll","DY","VV_incl"};
	
	Plotter.samples_to_use = {"Prompt","NonPrompt",WZ};
	Plotter.HistPath= {"HNL_WZ_ThreeLepton_CR/RegionPlots_"+channel+"/HNTightV2",                                                                                                            
			   "HNL_WZ_ThreeLepton_CR/RegionPlots_"+channel+"/HNL_ULID_2017"};
	
	Plotter.RegionType = {"WZ CR","ZZ CR"};
	
	Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
	
	///// HISTs Setup
	//Plotter.AddHist("Ev_PuppiMET_T1ULxyCorr" ,                     "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
	// Plotter.AddHist("M_ll" ,"MLL"  , "GeV", {2.}, 0, 400);
	//Plotter.AddHist("N_AK4Jets"  ,"NJ4"  , "",    {1.}, 0, 10);
	//Plotter.AddHist("Lep_1_pt" ,"LPT1" , "GeV", {1.}, 20, 400);
	//Plotter.AddHist("Lep_2_pt" ,"LPT2" , "GeV", {1.}, 10, 200);
	//Plotter.AddHist("Lep_3_pt" ,"LPT3" , "GeV", {1.}, 10, 200);
	//Plotter.AddHist("Lep_1_eta" ,"Eta" , "", {4.}, -3, 3);
	//Plotter.AddHist("Lep_2_eta" ,"Eta" , "", {4.}, -3, 3);
	//Plotter.AddHist("Lep_3_eta" ,"Eta" , "", {4.}, -3, 3);
	
	Plotter.AddCutFlow("ChannelCutFlow/HNTightV2/SelectedControlRegions" );    
	
	////// Make list and run plotting
	Plotter.DrawStackCutFlowWithData();
	//Plotter.make_cutflow("N_AK4Jets");
	//Plotter.Summary();
      }
    }
  }
  
  
  return;
}

