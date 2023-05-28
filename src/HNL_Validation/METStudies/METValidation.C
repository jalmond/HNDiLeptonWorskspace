#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void METValidation(){

    vector<TString> eras =  {"2018"};
  vector<TString> channels = {"EMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("METValidation");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_Dilepton", "HNL_Validation");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir

      Plotter.samples_to_use = {"Prompt"};
      Plotter.HistPath= { channel+"/POG_UL/RegionPlots_BJetCR_BTagSF",
			  channel+"/POG_UL/RegionPlots_ZPeakPt50_BTagSF"};

      Plotter.RegionType = {"BJetCR","ZCR"};
      
      Plotter.BasicSetup(-1., true, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("METPt_PuppiT1xyULCorr" ,           "MET" , "GeV", 2, 0, 200, 100000);
      Plotter.AddHist("METPt_PuppiT1xyULCorr_propsmear" , "MET" , "GeV", 2, 0, 200);
      
      ////// Make list and run plotting
      //Plotter.DrawStackPlotsWithData();
      Plotter.DrawStackPlots();
      Plotter.make_cutflow("NJets");
      Plotter.Summary();
      return;
      
    }
  }
  
  
  return;
}

