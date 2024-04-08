#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void TrileptonControlRegion2(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMuMu"};//,"MuE"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotterTESTVV");
      //// change def
      Plotter.DoDebug=false;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter","/VV_VR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      
      Plotter.samples_to_use = {"Conv","Prompt","NonPrompt"};
      //      Plotter.ScaleSample("TTLL_powheg",0.95);
      
      Plotter.HistPath= { "ChannelCutFlow/HNTightV2"};


      //			   "HNL_OS_Z_TwoLepton_CR/RegionPlots_"+channel+"/HNL_ULID_2017",
      //			   "HNL_OS_Z_TwoLepton_CR/RegionPlots_"+channel+"/DefaultPOGTight"};

      Plotter.RegionType = {"VV CRs"};
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup

      Plotter.AddHist("SelectedControlRegions"  ,""  , "int",    {1.}, 0, 20);
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      Plotter.Summary();
    }
  }
  
  
  return;
}

