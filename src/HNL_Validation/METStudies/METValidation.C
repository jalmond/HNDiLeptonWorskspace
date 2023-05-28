#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"

void METValidation(){
  
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"EMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("METValidation");
      Plotter.DoDebug=true;
      Plotter.SetSkim("SkimTree_Dilepton");
      Plotter.SetAnalyser("HNL_Validation");
      Plotter.SetEra(year);
      Plotter.SetupPlotter();
      
      //Plotter.map_sample_string_to_list["Prompt"] = {"Prompt"};
      //Plotter.map_sample_string_to_legendinfo["Prompt"] = make_pair("Prompt", kGreen);
      Plotter.samples_to_use = {"Prompt"};

      Plotter.HistPath= { channel+"/POG_UL/RegionPlots_BJetCR_BTagSF",
			  channel+"/POG_UL/RegionPlots_ZPeakPt50_BTagSF"};

      Plotter.RegionType = {"BJetCR","ZPeakPt50"};

      Plotter.LeptonChannel(channel);
      Plotter.UseLogyAll(-1.);
      Plotter.DrawRatioAll(true);
      Plotter.DrawDataAll(true);

      ///// HISTs
      Plotter.histname= { "METPt_PuppiT1xyULCorr","METPt_PuppiT1xyULCorr_propsmear"};
      Plotter.x_title = {"#slash{E}_{T}^{miss} [GeV]","#slash{E}_{T}^{miss} [GeV]"};
      Plotter.units = {"GeV","GeV"};
      Plotter.Rebins = {2,2};
      Plotter.Xmins = {0,0};
      Plotter.Xmaxs = {200,200};
      Plotter.Ymaxs = {100000,100000};
      
      Plotter.make_bkglist();
      Plotter.draw_hist();

      return;
      
    }
  }
  
  
  return;
}

