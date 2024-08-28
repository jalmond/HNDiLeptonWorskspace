#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLSRPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSSignalRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);


void SR3_Plotter_LimitPlots(){

  TString DATE = "May12";
  vector<TString> Eras =  {"2016postVFP","2017","2018"};
  Eras =  {"Run2"};
  vector<TString> Reg ={"LimitExtraction"};
  
  //  SSSignalRegionJob(DATE, Eras, "MuMu",{"Prompt","NonPrompt","Conv"} , Reg , "HNL_SignalRegion_SSCRPlots", "List3");
  SSSignalRegionJob(DATE, Eras, "MuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , Reg , "HNL_SignalRegion_SSCRPlots_LimitExtraction", "List3");
  SSSignalRegionJob(DATE, Eras, "EE",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv","chargeflip"} , Reg , "HNL_SignalRegion_SSCRPlots_LimitExtraction", "List3");
  

}

void SSSignalRegionJob(TString  DateTag,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList){
  
  for (auto ir : Regions)    RunFunction(DateTag,Eras, {Channel}, Label,"", Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      for (auto ID : Dirs) system("python PrintBackgrounds.py  -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_SignalRegion_Plotter -p "+PlotterTag + " -l " + InputList );
      
      HNLSRPlotter Plotter(PlotterTag+"SR_Plotter");
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
      

      Plotter.BasicSetup(HNLSRPlotter::LOGY, HNLSRPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("LimitBins/MuonSR3"  ,"Search Region"  , "",    {1}, 0, 2000);
      Plotter.AddHist("LimitBins/ElectronSR3"  ,"Search Region"  , "",    {1}, 0, 2000);
      
      Plotter.signal_mass = {1000};
      Plotter.signal_scale = {20};

      TString V2 = "#||{V_{N#mu}}^{2}";                                                                                                                                       
      Plotter.signal_leg = {"m_{N} = 1000 GeV, "+V2+"=20"};
      Plotter.signal_color = {kRed};
      Plotter.signal_string = {"DYVBF_MN1000"};

      
      ////// Make list and run plotting
      Plotter.DrawStackPlots();
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

