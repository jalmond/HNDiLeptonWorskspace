#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SS__ValidationRegionCutFlow(){

  vector<TString> eras =  {"2016", "2017", "2018"};
  vector<TString> channels = {"MuMu"};

  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegion_SSCR_ScanFakes_Muon");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      Plotter.DrawRatioLegend=false;
      Plotter.RatioRange=1.2;
      Plotter.DrawSmallLegend=true;
      Plotter.RunScan=true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion","/ScanFakes");
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      
      vector<TString> Dirs = { 
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v1_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v1_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v1_c_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v2_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v2_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v2_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v3_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v3_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v3_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v4_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v4_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v4_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v5_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v5_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v5_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v6_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v6_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v6_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v7_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v7_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v7_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v8_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v8_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v8_c_Standard_PtParton_AJ30/"+channel,

	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v9_a_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v9_b_Standard_PtParton_AJ30/"+channel,
	"ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v9_c_Standard_PtParton_AJ30/"+channel};

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

