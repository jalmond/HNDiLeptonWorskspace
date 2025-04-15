#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void OSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void OSControlRegionNLO(){

  TString DATE = "Jan29";
  vector<TString> Eras =  {"2017"};
  

  vector<TString> DiLepReg = {"HNL_OS_Z_TwoLepton_CR",
			      "HNL_OS_Z_HighPt_TwoLepton_CR",
			      "HNL_OS_Z_TwoLepton_NoSF_CR",
			      "HNL_OS_Z_TwoLepton_UnCorr_CR"};

  OSControlRegionJob(DATE,2, Eras, "MuMu",{"DY","DYTauTau","VV_incl","ttbar","NonPrompt","Conv"} , DiLepReg , "HNL_ControlRegion_OSCRPlots_NLO", "List3","OS");

 
}

void OSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {"HNL_ULIDv2"};//, "HNTightV2"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      //for (auto ID : Dirs) system("python PrintNTUP.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag);
    

      //if(year == "Run2"){//
      //for (auto ID : Dirs) system("python PrintBackgrounds_Run2.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      // }
      //else {
      for (auto ID : Dirs) system("python PrintBackgrounds_AN.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      // }
      HNLRegionPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;
      Plotter.RatioRange = 1.3;
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_DileptonBDT", "HNL_ControlRegion_Plotter","/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::LOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      //      Plotter.AddMass(nlep,Region);
      Plotter.AddMisc(Region);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

