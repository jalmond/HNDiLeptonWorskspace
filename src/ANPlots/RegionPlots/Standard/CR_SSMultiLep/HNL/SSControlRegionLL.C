#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label, TString flag,TString InputList);



void SSControlRegionLL(){

  TString DATE = "May31";
  vector<TString> Eras =  {"2016preVFP","2016postVFP","2017","2018","Run2"};


  vector<TString> DiLepReg = {"HNL_HighMassSR1_LowMW_TwoLepton_CR","HNL_HighMassSR1_NJETCut_TwoLepton_CR","HNL_HighMassSR1_noZVeto_TwoLepton_CR","HNL_HighMassSR1_TauVeto_TwoLepton_CR", "HNL_HighMassSR1BJet_TwoLepton_CR","HNL_HighMassBJetZ_TwoLepton_CR","HNL_HighMassZPeakNP_TwoLepton_CR","HNL_HighMassSR2_NJETCut_TwoLepton_CR","HNL_HighMassSR2_TauVeto_TwoLepton_CR", "HNL_HighMassSR3_TwoLepton_CR", "HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassSR2_TwoLepton_CR","HNL_HighMassSR3LowJet_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_WpWpNP_TwoLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2"};


  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR","HNL_WZ_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR","HNL_WZVBF_ThreeLepton_CR","HNL_WZVBF2_ThreeLepton_CR","HNL_WZB_ThreeLepton_CR","HNL_WZ_SR1_ThreeLepton_CR""HNL_WG_ThreeLepton_CR"};

  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR","HNL_ZZ_FourLepton_CR","HNL_ZZ_SR1_FourLepton_CR","HNL_ZZVBF_FourLepton_CR"};


  SSControlRegionJob(DATE,2, Eras, "LL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv","chargeflip"} , DiLepReg , "HNL_ControlRegion_SSCRPlots","SSMultiLep" ,"List3");
  //SSControlRegionJob(DATE,3, Eras, "LLL", {"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"},TriLepReg, "HNL_ControlRegion_SSCRPlots", "LLL","List3");
  //SSControlRegionJob(DATE,4, Eras, "LLLL",{"WZ_SS","ZZ_SS","WW_SS","Top_SS","Other_SS","NonPrompt","Conv"}, QuadLepReg, "HNL_ControlRegion_SSCRPlots", "SSMultiLep","List3");

}

void SSControlRegionJob(TString  DateTag, int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString flag,TString InputList){

  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,flag, Bkgs,ir, InputList);

}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region,TString InputList){

  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      for (auto ID : Dirs) system("python PrintBackgrounds.py -f "+Flag+" -e "+year+" -r "+Region+" -i " + ID + "  -c "+channel+" -d "+ DateFileTag  + " -a HNL_ControlRegion_Plotter -p "+PlotterTag + " -l " + InputList );

      
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
      
      //// AK8 
      Plotter.AddAK8();
      Plotter.AddVBF();
      Plotter.AddMisc();
      Plotter.AddMass(nlep);
      Plotter.AddLepton(nlep);

      /*Plotter.AddHist("AK8/AK8J_Tagger_particleNet_WvsQCD" ,"PNET WvsQCD", "",{2},0,1};
	Plotter.AddHist("AK8/AK8J_Mass/l1J" ,"m_{l_{1}J} GeV", "GeV", {10},0.,4000.);
      Plotter.AddHist("AK8/AK8J_Mass/l2J" ,"m_{l_{2}J} GeV", "GeV", {10},0.,4000.);
      Plotter.AddHist("AK8/AK8J_Mass/llJ" ,"m_{llJ} GeV", "GeV", {10},0.,4000.);
      Plotter.AddHist("AK8/AK8J_Eta" ,"#eta AK8", "int", {2},-3.,3.);

      Plotter.AddHist("VBF/Lead_MJJ","m_{JJ} GeV","GeV", {500,1200,1700,3000},0,3000};
      Plotter.AddHist("VBF/Lead_zeppenfeld","zeppenfeld","int", {2},0,10};
      Plotter.AddHist("VBF/MaxDEtaJets_MJJ","#Delta (#eta) JJ","int", {2},0,5};
      Plotter.AddHist("DeltaR/dR_ll" ,"#DeltaR_{LL}"  , "", {2.}, 0, 5);
      Plotter.AddHist("DeltaPhi/dPhi_lep1_lep2" ,"#Delta#phi_{LL}"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 6);
      Plotter.AddHist("NObj/N_BJ"  ,"NJ4"  , "",    {1.}, 0, 4);
      Plotter.AddHist("Mass/M_ll"  ,"M_{ll}"  , "GeV",    {2.}, 0, 400);
      Plotter.AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {500,1200,1700,3000}, 0, 3000);
      Plotter.AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {500,1200,1700,3000}, 0, 3000);
      Plotter.AddHist("Leptons/Lep_1_pt" ,"P^{1}_{T} GeV" , "GeV", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200); 
      Plotter.AddHist("Leptons/Lep_2_pt" ,"P^{2}_{T} GeV" , "GeV", {0.,15.,21.,30.,42., 60.,100., 200.}, 0, 200);                                                                                                         
      Plotter.AddHist("Leptons/Lepton_pt" ,"P^{1}_{T} " , "int", {0.,15.,20.,30.,40., 60.,100.,250., 500.}, 10, 500);
      Plotter.AddHist("Leptons/Lepton_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
      */
      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

