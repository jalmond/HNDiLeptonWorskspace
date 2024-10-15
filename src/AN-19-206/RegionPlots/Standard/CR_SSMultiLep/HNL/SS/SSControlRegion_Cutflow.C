#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void SSControlRegion_Cutflow(){

  TString DATE = "Oct11";
  vector<TString> Eras =  {"Run2"};

  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR","HNL_WG_ThreeLepton_CR", "HNL_WZB_ThreeLepton_CR", "HNL_WZVBF2_ThreeLepton_CR" , "HNL_WZVBF_ThreeLepton_CR", "HNL_WZ_HighPt_ThreeLepton_CR", "HNL_WZ_SR1_ThreeLepton_CR", "HNL_WZ_SR3_ThreeLepton_CR", "HNL_ZG_ThreeLepton_CR", "HNL_ZNPEl_ThreeLepton_CR", "HNL_ZNPMu_ThreeLepton_CR","HNL_ZG_HighPt_ThreeLepton_CR"};

  TriLepReg = {"HNL_WZ_SR1_ThreeLepton_CR", "HNL_WZ_SR3_ThreeLepton_CR" ,"HNL_WZVBF_ThreeLepton_CR","HNL_WZVBF2_ThreeLepton_CR"};

  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR", "HNL_ZZVBF_FourLepton_CR","HNL_ZZ_FourLepton_CR","HNL_ZZ_HighPt_FourLepton_CR","HNL_ZZ_SR1_FourLepton_CR"};


  //  SSControlRegionJob(DATE,4, Eras, "MuMuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List1","LLL");
  SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List2","LLL");
  SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List4","LLL");

  //SSControlRegionJob(DATE,4, Eras, "EEEE",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "EEE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List1","LLL");
  SSControlRegionJob(DATE,3, Eras, "EEE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List2","LLL");
  SSControlRegionJob(DATE,3, Eras, "EEE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "EEE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List4","LLL");

  //SSControlRegionJob(DATE,4, Eras, "EMuLL",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "EMuL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List1","LLL");
  SSControlRegionJob(DATE,3, Eras, "EMuL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List2","LLL");
  SSControlRegionJob(DATE,3, Eras, "EMuL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  SSControlRegionJob(DATE,3, Eras, "EMuL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List4","LLL");

  //SSControlRegionJob(DATE,4, Eras, "LLLL",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3","LLL");
  // SSControlRegionJob(DATE,3, Eras, "LLL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , TriLepReg , "HNL_ControlRegion_SSCRPlots", "List3","LLL");

 
}

void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  
  Label = Label+"_"+InputList;
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      //for (auto ID : Dirs) system("python PrintNTUP.py -f SSMultiLep -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag);
      
      for (auto ID : Dirs) cout << "python PrintBackgrounds_Run2.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList << endl;
      for (auto ID : Dirs) system("python PrintBackgrounds_Run2.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      

      
    }
  }
  
  
  return;
}

