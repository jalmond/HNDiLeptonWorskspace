#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList);


void SSControlRegion_HNTightV2(){
  
  TString DATE = "May10";
  vector<TString> Eras =  {"2016postVFP","2016preVFP","2017","2018"};
  Eras =  {"2017"};
  vector<TString> DiLepReg = {"HNL_HighMassSR3_TwoLepton_CR", "HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassSR2_TwoLepton_CR","HNL_HighMassSR3LowJet_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_WpWpNP_TwoLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2","HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassSSZPeak_TwoLepton_CR"};
  vector<TString> DiLepRegEE = {"HNL_HighMassSR3_TwoLepton_CR", "HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassSR2_TwoLepton_CR","HNL_HighMassSR3LowJet_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_WpWpNP_TwoLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2","HNL_HighMass1Jet_TwoLepton_CR","HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassSSZPeak_HighPtHighEta_TwoLepton_CR"};

  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR","HNL_WZ_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR","HNL_WZ2_ThreeLepton_CR"};
  vector<TString> QuadLepReg ={"HNL_ZZ_FourLepton_CR"};
  
  //SSControlRegionJob(DATE, Eras, "MuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"} ,    DiLepReg , "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //SSControlRegionJob(DATE, Eras, "MuMuMu", {"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"},      TriLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //SSControlRegionJob(DATE, Eras, "MuMuMuMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");

  // SSControlRegionJob(DATE, Eras, "EE",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv","chargeflip"} , DiLepRegEE , "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //  SSControlRegionJob(DATE, Eras, "EMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"} , DiLepRegEE , "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  SSControlRegionJob(DATE, Eras, "EMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"} , DiLepRegEE , "HNL_ControlRegion_SSCRPlots_OtherID", "List3");
  // SSControlRegionJob(DATE, Eras, "EEE", {"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"},      TriLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //SSControlRegionJob(DATE, Eras, "EEEE",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");

  //SSControlRegionJob(DATE, Eras, "EMu",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"} ,    DiLepReg , "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //SSControlRegionJob(DATE, Eras, "EMuL", {"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"},      TriLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");
  //SSControlRegionJob(DATE, Eras, "EMuLL",{"WZ_SS","ZZ_SS","WW_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots_PromptSplit_HNTightV2", "List3");


}

void SSControlRegionJob(TString  DateTag,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList){
  
  for (auto ir : Regions)    RunFunction(DateTag,Eras, {Channel}, Label,"SSMultiLep", Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = { "HNTightV2"};

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
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 6);
      Plotter.AddHist("NObj/N_BJ"  ,"NJ4"  , "",    {1.}, 0, 4);
      Plotter.AddHist("Mass/M_ll"  ,"M_{ll}"  , "GeV",    {2.}, 0, 400);
      Plotter.AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2000);
      Plotter.AddHist("SKEvent/Ev_MET2_ST"  ,"MET^{2}/S_{T}"  , "GeV",    {2.}, 0, 50);
      Plotter.AddHist("Leptons/Lep_1_pt" ,"LPT1" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200); 
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200); 
      Plotter.AddHist("Leptons/Leps_eta" ,"LEta" , "int", {2},-2.5,2.5);
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

