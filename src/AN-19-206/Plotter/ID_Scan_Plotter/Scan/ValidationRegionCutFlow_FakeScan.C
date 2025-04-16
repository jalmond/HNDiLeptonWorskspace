#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLScanPlotter.cc"
#include "HNLScanPlotter.cc"                                                                       

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag);


void ValidationRegionCutFlow_FakeScan(){

  RunFunction("April19",{"2016preVFP", "2016postVFP","2017","2018","Run2"}, {"EE","MuMu"}, "HNL_ControlRegion_Summary_FakeScan_BB","ScanFakes_BB");

  
}
void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag){


  for (auto year : eras){
    for (auto channel : channels){
      
      HNLScanPlotter Plotter(PlotterTag+"_"+channel);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;
      Plotter.RunScan=true;
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion","/"+Flag);
      if(channel == "MuMu")Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      else Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      Plotter.ScaleSample("ttbar_ll",0.95);


      TString DefaultHistName = "ChannelCutFlow/HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ30/"+channel;
      vector<TString> AJetPt = {"AJ30","AJ40"};
      TString Year = (year.Contains("2016")) ? "2016" : year;
      vector<TString> FakeIDs = {  "HNL_ULID_FO_v1_a",
				   "HNL_ULID_FO_v1_b",
				   "HNL_ULID_FO_v1_c",
				   "HNL_ULID_FO_v2_a",
				   "HNL_ULID_FO_v2_b",
				   "HNL_ULID_FO_v2_c",
				   "HNL_ULID_FO_v3_a",
				   "HNL_ULID_FO_v3_b",
				   "HNL_ULID_FO_v3_c",
				   "HNL_ULID_FO_v4_a",
				   "HNL_ULID_FO_v4_b",
				   "HNL_ULID_FO_v4_c",
				   "HNL_ULID_FO_v5_a",
				   "HNL_ULID_FO_v5_b",
				   "HNL_ULID_FO_v5_c",
				   "HNL_ULID_FO_v6_a",
				   "HNL_ULID_FO_v6_b",
				   "HNL_ULID_FO_v6_c",
				   "HNL_ULID_FO_v7_a",
				   "HNL_ULID_FO_v7_b",
				   "HNL_ULID_FO_v7_c",
				   "HNL_ULID_FO_v8_a",
				   "HNL_ULID_FO_v8_b",
				   "HNL_ULID_FO_v8_c",
				   "HNL_ULID_FO_v9_a",
				   "HNL_ULID_FO_v9_b",
				   "HNL_ULID_FO_v0",
				   "HNL_ULID_FO_v9_c"};

      vector<TString> FakeParam = {"PtParton","Pt","PtCorr"};
      vector<TString> Dirs;
      for(auto id : FakeIDs) {
	for(auto ij : AJetPt){
	  for(auto ik : FakeParam){
	  
	    Dirs.push_back( "ChannelCutFlow/HNL_ULID_"+id+"_Standard_"+ik+"_"+ij+"/"+channel);
	  }
	}
      }     
					       

      vector<TString> RTypes;
      for(auto i : Dirs) RTypes.push_back("");
      Plotter.RegionType = RTypes;
      Plotter.HistPath= Dirs;
      Plotter.BasicSetup(HNLScanPlotter::LOGY, HNLScanPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      Plotter.AddCutFlow("SS_SelectedControlRegions" );    
      ////// Make list and run plotting
      Plotter.DrawScanCutFlowWithData(DefaultHistName);

    }
  }
  
  
  return;
}

