#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SS__ValidationRegionCutFlow(){

  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMu"};

  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotter_SSCR");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter","/SS_CR");
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      Plotter.ScaleSample("ttbar_ll",0.95);


      
      vector<TString> Dirs = {  "ChannelCutFlow/"+channel+"/HNTightV2/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_PtParton_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_Pt_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ40/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ30/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ30/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_PtParton_AJ30/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_Pt_AJ30/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ30/"+channel,      
                                "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ30/"+channel};

      Dirs = {                                 "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_PtParton_AJ30/"+channel,
					       "ChannelCutFlow/"+channel+"/HNL_ULID_HNL_ULID_FO_Standard_Pt_AJ30/"+channel,


      vector<TString> RTypes;
      for(auto i : Dirs) RTypes.push_back("");
      Plotter.RegionType = RTypes;
      Plotter.HistPath= Dirs;
      Plotter.BasicSetup(HNLPlotter::LOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      Plotter.AddCutFlow("SS_SelectedControlRegions" );    
      ////// Make list and run plotting
      Plotter.DrawStackCutFlowWithData();
    }
  }
  
  
  return;
}

