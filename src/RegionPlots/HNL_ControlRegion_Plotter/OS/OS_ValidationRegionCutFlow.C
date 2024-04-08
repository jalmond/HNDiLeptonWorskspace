#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void OS_ValidationRegionCutFlow(){

  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"EMu"};

  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotterTEST");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_DileptonBDT", "HNL_ControlRegionPlotter","/OS_VR");
      Plotter.samples_to_use = {"Conv","ttbar_ll","DY","VV_incl","NonPrompt"};
      Plotter.ScaleSample("ttbar_ll",0.95);
      Plotter.RegionType = {""};
      Plotter.HistPath= { "ChannelCutFlow/HNTightV2"};
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      Plotter.AddCutFlow("SelectedControlRegions" );    
      ////// Make list and run plotting
      Plotter.DrawStackCutFlowWithData();
    }
  }
  
  
  return;
}

