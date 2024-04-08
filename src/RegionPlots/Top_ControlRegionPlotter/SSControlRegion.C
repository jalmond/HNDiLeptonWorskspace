#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SSControlRegion(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("Top_ControlRegionPlotter2024_01");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "Top_ControlRegionPlotter","/SS_CR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      
      ///Plotter.ScaleSample("WZ_pythia",0.95);

      vector<TString> Dirs = {  //"HNTightV2"};
	//"HNL_ULID"};
	"TopHN"};


      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( "Top_SSBJet_TwoLepton_CR/"+channel+"/"+id+"/RegionPlots_"+channel);    
      for(auto id : Dirs) HPaths.push_back( "Top_SS1Jet_TwoLepton_CR/"+channel+"/"+id+"/RegionPlots_"+channel);    
      for(auto id : Dirs) RegionTypes.push_back(id);
      for(auto id : Dirs) RegionTypes.push_back(id);


      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      //Plotter.HistPath= {"HNL_HighMassSR3_TwoLepton_CR/RegionPlots_"+channel+"/HNL"}; 
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("Mass/M_ll" ,"M_LL"  , "", {2.}, 0, 200);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "GeV", {4.}, 10, 200);
      Plotter.AddHist("Leptons/Leps_eta" ,"LEta" , "GeV", {1.}, -2.5, 2.5);
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

