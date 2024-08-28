#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLSRPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSSignalRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);


void SR1_Plotter(){

  TString DATE = "May12";
  vector<TString> Eras =  {"2016postVFP","2017","2018"};
  Eras =  {"2018"};
  vector<TString> Reg ={"Preselection"};
  
  //  SSSignalRegionJob(DATE, Eras, "MuMu",{"Prompt","NonPrompt","Conv"} , Reg , "HNL_SignalRegion_SSCRPlots", "List3");
  SSSignalRegionJob(DATE, Eras, "MuMu",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"} , Reg , "HNL_SignalRegion_SSCRPlots_PromptSplit", "List3");
  

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
      

      Plotter.BasicSetup(HNLSRPlotter::NoLOGY, HNLSRPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("Mass/DiJet_M_l1jj"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("Mass/DiJet_M_lljj"  ,"M_{llW}"  , "GeV",    {0,500,625,750}, 0, 2000);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200); 
      Plotter.AddHist("SKEvent/Ev_MET2_ST"  ,"MET^{2}/S_{T}"  , "GeV",    {2.}, 0, 20);
      Plotter.AddHist("AK8/AK8J_Tagger_particleNet_WvsQCD" ,"PNET WvsQCD", "",{2},0,1);

      Plotter.signal_mass = {1000};
      Plotter.signal_string = {"DYVBF_MN1000"};

      
      ////// Make list and run plotting
      Plotter.DrawStackPlots();
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

