#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SSControlRegionEERun(TString Era, TString FlagDir, TString WebPageName);

void CFValSSControlRegionEE(){
  
  TString WebPageName="HNL_ControlRegionPlotter_EE_2024_02_CFValidation_BB";

  SSControlRegionEERun("2016preVFP", "/ScanFakesBB",WebPageName);
  SSControlRegionEERun("2016postVFP", "/ScanFakesBB",WebPageName);
  SSControlRegionEERun("2017", "/ScanFakesBB",WebPageName);
  SSControlRegionEERun("2018", "/ScanFakesBB",WebPageName);

  WebPageName="HNL_ControlRegionPlotter_EE_2024_02_CFValidation_EC";

  SSControlRegionEERun("2016preVFP", "/ScanFakesEC",WebPageName);
  SSControlRegionEERun("2016postVFP", "/ScanFakesEC",WebPageName);
  SSControlRegionEERun("2017", "/ScanFakesEC",WebPageName);
  SSControlRegionEERun("2018", "/ScanFakesEC",WebPageName);

}

void SSControlRegionEERun(TString Era,TString FlagDir, TString WebPageName){

  vector<TString> eras =  {Era};

  vector<TString> channels = {"EE"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter(WebPageName);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion",FlagDir);
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      
      //Plotter.ScaleSample("CF",0.8);


      vector<TString> Dirs = { "HNL_ULID_HNL_ULID_FO_v9_c_Standard_PtParton_AJ30"};



      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMass1Jet_TwoLepton_CR/"+id+"/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id);

      


      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("Mass/M_ll" ,"M_ll" , "", {1.}, 0, 200);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Leptons/Lep_1_pt" ,"LPT1" , "GeV", {0.,5.,10.,20.,40.,60.,100.,200}, 0, 200);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "GeV", {0.,5.,10.,20.,40.,60.,100.,200}, 0, 200);
      Plotter.AddHist("Leptons/Lep_1_eta" ,"LETa1" , "", {5.}, -3, 3);
      Plotter.AddHist("Leptons/Lep_2_eta" ,"LETa2" , "", {5.}, -3, 3);


      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

