#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void LLL_ValidationRegionCutFlowMuMu(){

  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMu"};

  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotter_LLL");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter","/LLL_CR");
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      Plotter.ScaleSample("ttbar_ll",0.95);
      Plotter.ScaleSample("Prompt",0.95);


      //      Plotter.HistPath= { "ChannelCutFlow/"+channel+"/HNTightV2/"+channel};

      vector<TString> Dirs = {  "ChannelCutFlow/"+channel+"/HNTightV2/"+channel,      
				"ChannelCutFlow/"+channel+"/HNL_ULID/"+channel};




      vector<TString> RTypes;
      for(auto i : Dirs) RTypes.push_back("");
      Plotter.RegionType = RTypes;
      Plotter.HistPath= Dirs;
      Plotter.BasicSetup(HNLPlotter::LOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      Plotter.AddCutFlow("LLL_SelectedControlRegions" );    
      ////// Make list and run plotting
      Plotter.DrawStackCutFlowWithData();
    }
  }
  
  
  return;
}

