#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"

void METValidationYield(){
  
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
      
      // Set Plotting style
      setTDRStyle();
      gStyle->SetPalette(1);
      
      Plotter.map_sample_string_to_list["Prompt"] = {"Prompt"};
      Plotter.map_sample_string_to_legendinfo["Prompt"] = make_pair("Prompt", kGreen);
      Plotter.samples_to_use = {"Prompt"};
      Plotter.histpath= { channel+"/POG_UL/RegionPlots_TopCR_BTagSF"};
      ///RegionPlots_ZPeakPt50_BTagSF"};
      Plotter.LeptonChannels = {21};
      Plotter.RegionType = {0};
      Plotter.UseLogy = {-1};
      Plotter.drawratio = {"true"};
      Plotter.drawdata = {"true"};
      Plotter.histname= { "NJets"};
      Plotter.x_title = {"NJets"};
      Plotter.units = {""};
      Plotter.Rebins = {1};
      Plotter.Xmins = {0};
      Plotter.Xmaxs = {5};
      Plotter.Ymaxs = {100000};
      
      Plotter.make_bkglist();
      Plotter.draw_hist();

      return;
      
    }
  }
  
  
  return;
}

