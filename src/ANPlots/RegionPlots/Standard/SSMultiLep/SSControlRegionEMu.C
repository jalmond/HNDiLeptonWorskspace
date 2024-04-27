#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, TString Region);
void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Regions, TString Label);


void SSControlRegionEMu(){
  SSControlRegionJob("April26", {"2018"}, "EMu", {"HNL_HighMassSSZPeak_TwoLepton_CR","HNL_HighMassSR3_TwoLepton_CR"   ,"HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassSR2_TwoLepton_CR","HNL_HighMassSR3LowJet_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_WpWpNP_TwoLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2","HNL_HighMass1Jet_TwoLepton_CR"}, "HNL_ControlRegion_SSCRPlots");
  
  SSControlRegionJob("April26", {"2018"}, "EMuL", {"HNL_TopNP_ThreeLepton_CR","HNL_WZ_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR","HNL_WZ2_ThreeLepton_CR","HNL_WZB_ThreeLepton_CR"}, "HNL_ControlRegion_SSCRPlots");
  SSControlRegionJob("April26", {"2018"}, "EMuLL", {"HNL_ZZLoose_FourLepton_CR","HNL_ZZ_FourLepton_CR"}, "HNL_ControlRegion_SSCRPlots");

}

void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Regions, TString Label){
  
  //ing> Regions = {"HNL_HighMassSR3_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassCR2_TwoLepton_CR","HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR"};
  
  for (auto ir : Regions)    RunFunction(DateTag,Eras, {Channel}, Label,"SSMultiLep",ir);                                                      
  
  
}


void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,TString Region){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      for (auto ID : Dirs) system("python PrintNTUP.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag);
      
      HNLRegionPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;

      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion_Plotter","/"+Flag);

      if(channel == "MuMu")Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      else  if(channel == "EE") Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      else  Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Mass/M_ll"  ,"M_{ll}"  , "GeV",    {2.}, 0, 200);
      Plotter.AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2000);
       Plotter.AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200);                                                                                                                                              
      //if(channel == "EE")Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {15,20,30.,40., 60.,100, 200}, 10, 200);
      //      else Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {10.,15.,20.,30.,40., 60.,100., 200.}, 0, 200);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

