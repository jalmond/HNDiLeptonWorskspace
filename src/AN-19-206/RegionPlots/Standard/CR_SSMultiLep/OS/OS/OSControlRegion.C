#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void OSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void OSControlRegion(){

  TString DATE = "Feb11";
  vector<TString> Eras = {"2017"}; 

  //{"2016","2017","2018"};
  

  TString Label_sel[] = {
    "_NoCorr_DefaultWeight",
    "_NoCorr_TriggerSF",
    "_NoCorr_TriggerSF_RecoSF",
    "_NoCorr_TriggerSF_RecoSF_IDSF",
    "_NoCorr_TriggerSF_RecoSF_IDSF_3bin",
    "_Corr1_DefaultWeight",
    "_Corr1_TriggerSF",
    "_Corr1_TriggerSF_RecoSF",
    "_Corr1_TriggerSF_RecoSF_IDSF",
    "_Corr1_TriggerSF_RecoSF_IDSF_3bin",
    "_Corr2_DefaultWeight",
    "_Corr2_TriggerSF",
    "_Corr2_TriggerSF_RecoSF",
    "_Corr2_TriggerSF_RecoSF_IDSF",
    "_Corr2_TriggerSF_RecoSF_IDSF_3bin",
    "_Corr3_DefaultWeight",
    "_Corr3_TriggerSF",
    "_Corr3_TriggerSF_RecoSF",
    "_Corr3_TriggerSF_RecoSF_IDSF",
    "_Corr3_TriggerSF_RecoSF_IDSF_3bin",
  };

  vector<TString> DiLepReg;
  
  for (int i = 0; i < 20; ++i) {
    DiLepReg.push_back("HNL_OS_FullMass_"+Label_sel[i]+"TwoLepton_CR");
    DiLepReg.push_back("HNL_OS_Z_"+Label_sel[i]+"TwoLepton_CR");
  }
  
  
  OSControlRegionJob(DATE,2, Eras, "MuMu",{"DYJetsMerged","DYTauTau","VV_incl","ttbar","NonPrompt","Conv"} , DiLepReg , "HNL_ControlRegion_OSCRPlots_FullWeights", "List3","OS");
  DiLepReg = {"HNL_OS_Top_TwoLepton_CR","HNL_OS_Top2b_TwoLepton_CR"};
  OSControlRegionJob(DATE,2, Eras, "MuMu",{"DYJetsMerged","DYTauTau","VV_incl","ttbar","NonPrompt","Conv"} , DiLepReg , "HNL_ControlRegion_OSCRPlots_TopWeights", "List3","OS");


 
}

void OSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {"HNL_ULIDv2","HNL_ULIDv2_PtBinnedDY"};//, "HNTightV2"};

      for (auto ID : Dirs) system("python PrintBackgrounds_AN.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );

      
      HNLRegionPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;
      Plotter.ScaleSample("DYJetsMerged",1.027);
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_DileptonBDT", "HNL_ControlRegion_Plotter","/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      Plotter.ScaleSample("DYMerged",1.027);      
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      

      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, "OS"+channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      //      Plotter.AddMass(nlep,Region);
      Plotter.AddMisc(Region);
      //      Plotter.AddLepton(Region);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

