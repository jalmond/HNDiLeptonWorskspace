#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);


void SSControlRegionLL(){

  TString DATE = "April27";
  vector<TString> Eras =  {"Run2"};

  vector<TString> TriLepReg ={"HNL_WZ_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR"};
  vector<TString> QuadLepReg ={"HNL_ZZ_FourLepton_CR"};
  
  
  SSControlRegionJob(DATE, Eras, "LLL", {"Prompt3","NonPrompt","Conv"},TriLepReg, "HNL_ControlRegion_SSCRPlots_PromptSF", "List3");
  SSControlRegionJob(DATE, Eras, "LLLL",{"Prompt3","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots_PromptSF", "List3");

}

void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList){
  
  for (auto ir : Regions)    RunFunction(DateTag,Eras, {Channel}, Label,"SSMultiLep", Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      //for (auto ID : Dirs) system("python PrintNTUP.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag);
      for (auto ID : Dirs) system("python PrintBackgrounds.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      
      HNLRegionPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;

      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion_Plotter","/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/LL",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 6);
      Plotter.AddHist("NObj/N_BJ"  ,"NJ4"  , "",    {1.}, 0, 4);
      Plotter.AddHist("Mass/M_ll"  ,"M_{ll}"  , "GeV",    {2.}, 0, 200);
      Plotter.AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("Leptons/Lep_1_pt" ,"LPT1" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200);                                                                                                               Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200);                                                                                                               Plotter.AddHist("Leptons/Leps_pt" ,"LPT" , "int", {0.,15.,20.,30.,40., 60.,100.,250., 500.}, 10, 500);
      Plotter.AddHist("Leptons/Leps_eta" ,"LEta" , "int", {2},-2.5,2.5);

      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

