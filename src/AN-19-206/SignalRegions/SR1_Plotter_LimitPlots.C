#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLSRPlotter.cc"


void SR1_Plotter_LimitPlots(){

  TString DATE = "Oct11";
  vector<TString> eras = {"Run2"};
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      HNLSRPlotter Plotter(PlotterTag+"SR1_Plotter");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;

      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_SignalRegion_Plotter","/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      //      Plotter.ScaleSample("WZ",);
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      

      Plotter.BasicSetup(HNLSRPlotter::NoLOGY, HNLSRPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("LimitBins/MuonSR1"  ,"Search Region"  , "",    {1}, 0, 2000);
      
      Plotter.signal_mass = {700};
      Plotter.signal_scale = {0.1};

      TString V2 = "#||{V_{N#mu}}^{2}";                                                                                                                                       
      Plotter.signal_leg = {"m_{N} = 700 GeV, "+V2+"=0.1"};
      Plotter.signal_color = {kBlue};
      Plotter.signal_string = {"DYVBF_MN700"};

      
      ////// Make list and run plotting
      Plotter.DrawStackPlots();
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

