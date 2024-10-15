#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);



void HtoZZ_Emu(){

  TString DATE = "Aug20";
  vector<TString> Eras =  {"2016preVFP","2016postVFP","2017","2018"};


  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR","HNL_ZZ_FourLepton_CR"};

  SSControlRegionJob(DATE,4, Eras, "EMuLL", {"ZZ","ZX","HtoZZ","Other"},QuadLepReg, "HNL_HtoZZ", "List3"); 

		     
}

void SSControlRegionJob(TString  DateTag, int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList){

  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,"LLLL/", Bkgs,ir, InputList);

}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){

  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HtoZZ"};
      
      //// Run Yield print code                                                                                                                                                                                                                                                        
      for (auto ID : Dirs) system("python PrintBackgrounds.py -f LLLL -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_HtoZZ -p "+PlotterTag + " -l " + InputList );
      
      HNLRegionPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_HtoZZ", "/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      //      Plotter.ScaleSample("ConvDY",2);
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/LLLL" );
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup

      Plotter.AddMisc();
      Plotter.AddMass(nlep);
      Plotter.AddLepton(nlep);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

