#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void OSAK8ControlRegion(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"MuMu"};//, "EE","EMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegion_Plotter2024");
      //// change def
      Plotter.DoDebug=false;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_DileptonBDT", "HNL_ControlRegionPlotter","/OS_VR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir

      Plotter.samples_to_use = {"ttbar_ll","DY","OSOther","NonPrompt"};
      //      Plotter.ScaleSample("DYJets",0.9);

      Plotter.HistPath= {  "HNL_OS_ZAK8_TwoLepton_CR/RegionPlots_"+channel+"/TopHN",
                           "HNL_OS_TopAK8_TwoLepton_CR/RegionPlots_"+channel+"/TopHN"};




      Plotter.RegionType = {"OS(Z) CR","Top CR"};
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("Ev_PuppiMET_T1ULxyCorr" ,                     "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("M_ll" ,"MLL"  , "GeV", {2.}, 0, 400);
      Plotter.AddHist("N_AK4Jets"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Lep_1_pt" ,"LPT1" , "GeV", {1.}, 20, 400);
      Plotter.AddHist("Lep_2_pt" ,"LPT2" , "GeV", {1.}, 10, 200);
      Plotter.AddHist("Lep_1_eta" ,"LEta1" , "GeV", {1.}, -3, 3);
      Plotter.AddHist("Lep_2_eta" ,"LEta2" , "GeV", {1.}, -3, 3);

      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

