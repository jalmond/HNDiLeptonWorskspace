#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);


void SSControlRegion(){

  TString DATE = "May31";
  vector<TString> Eras =  {"2016postVFP","2017","2018","2016preVFP"};
  Eras =  {"2016preVFP","2016postVFP","2017","2018"};
  
  vector<TString> DiLepReg = {"HNL_HighMassSR3_TwoLepton_CR", "HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassSR2_TwoLepton_CR","HNL_HighMassSR3LowJet_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_WpWpNP_TwoLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2"};

  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR","HNL_WZ_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR","HNL_WZ2_ThreeLepton_CR"};
  TriLepReg ={"HNL_ZG_ThreeLepton_CR"};

  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR","HNL_ZZ_FourLepton_CR"};
  
  //SSControlRegionJob(DATE, Eras, "MuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"} , DiLepReg , "HNL_ControlRegion_SSCRPlots", "List3");


  SSControlRegionJob(DATE, 2,Eras, "MuMu", {"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"},DiLepReg, "HNL_ControlRegion_SSCRPlots", "List3");

  //  SSControlRegionJob(DATE, Eras, "MuMuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "List3");

  //SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","ConvV1"} , TriLepReg , "HNL_ControlRegion_SSCRPlots_ConvV1", "List3");
  //SSControlRegionJob(DATE,3, Eras, "MuMuMu", {"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","ConvV4"},TriLepReg, "HNL_ControlRegion_SSCRPlots_ConvV4", "List3");

  // SSControlRegionJob(DATE,3, Eras, "MuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","ConvGENTV1"} , TriLepReg , "HNL_ControlRegion_SSCRPlots_ConvGENTV1", "List3");
  //SSControlRegionJob(DATE,3, Eras, "MuMuMu", {"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","ConvGENTV4"},TriLepReg, "HNL_ControlRegion_SSCRPlots_ConvGENTV4", "List3");

  


}

void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList){
  
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,"SSMultiLep", Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
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
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLRegionPlotter::NoLOGY, HNLRegionPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddAK8();
      Plotter.AddVBF();
      Plotter.AddMisc();
      Plotter.AddMass(nlep);
      Plotter.AddLepton(nlep);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

