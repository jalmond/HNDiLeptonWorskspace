#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void SSControlRegion(){

  TString DATE = "Oct9";
  vector<TString> Eras =  {"2016postVFP","2017","2018","2016preVFP","Run2"};
  Eras =  {"Run2"};

  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR","HNL_WG_ThreeLepton_CR", "HNL_WZB_ThreeLepton_CR", "HNL_WZVBF2_ThreeLepton_CR" , "HNL_WZVBF_ThreeLepton_CR", "HNL_WZ_HighPt_ThreeLepton_CR", "HNL_WZ_SR1_ThreeLepton_CR", "HNL_WZ_SR3_ThreeLepton_CR", "HNL_ZG_ThreeLepton_CR", "HNL_ZNPEl_ThreeLepton_CR", "HNL_ZNPMu_ThreeLepton_CR","HNL_ZG_HighPt_ThreeLepton_CR"};

  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR", "HNL_ZZVBF_FourLepton_CR","HNL_ZZ_FourLepton_CR","HNL_ZZ_HighPt_FourLepton_CR","HNL_ZZ_SR1_FourLepton_CR"};

  
  //SSControlRegionJob(DATE,4, Eras, "MuMuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  //SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");

  //SSControlRegionJob(DATE,4, Eras, "EEEE",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  // SSControlRegionJob(DATE,3, Eras, "EEE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");

  // SSControlRegionJob(DATE,4, Eras, "EMuLL",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  //SSControlRegionJob(DATE,3, Eras, "EMuL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");

  
  SSControlRegionJob(DATE,4, Eras, "LLLL",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "LLL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");

 
}

void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};//, "HNTightV2"};
      if(Region.Contains("WG")) Dirs = {  "HNL_ULID" , "HNTightV2"};
      //// Run Yield print code                                                                                                                                                                                                                                                        
      //for (auto ID : Dirs) system("python PrintNTUP.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag);
    

      if(year == "Run2"){
	for (auto ID : Dirs) system("python PrintBackgrounds_Run2.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      }
      else {
	for (auto ID : Dirs) system("python PrintBackgrounds_AN.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      }
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
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddAK8(Region);
      Plotter.AddVBF(Region);
      Plotter.AddMisc(Region);
      Plotter.AddMass(nlep,Region);
      Plotter.AddLepton(nlep,Region);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

