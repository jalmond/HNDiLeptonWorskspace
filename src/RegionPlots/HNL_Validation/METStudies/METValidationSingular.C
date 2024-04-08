#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void METValidationSingular(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2018"};
  vector<TString> channels = {"MuMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("METValidationSingular");
      //// change def
      Plotter.DoDebug=true;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_Dilepton", "HNL_Validation");

      ///// HISTs Setup
      Plotter.SetupDefaultHist("Prompt",channel+"/POG_UL/RegionPlots_ZPeakPt50_BTagSF/METPt_PuppiT1xyULCorr" , "METPt_PuppiT1xyULCorr", "MET PuppiT1xyUL", "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80.,90., 100.,200.}, 0, 200);
      Plotter.SetupComparisonHist("Prompt",channel+"/POG_UL/RegionPlots_ZPeakPt50_BTagSF/METPt_PuppiT1xyULCorr_propsmear","METPt_PuppiT1xyULCorr_propsmear","MET PuppiT1xyUL Smeared");
      
      ////// Make list and run plotting
      Plotter.DrawComparisonPlots();
      
    }
  }
  
  
  return;
}

