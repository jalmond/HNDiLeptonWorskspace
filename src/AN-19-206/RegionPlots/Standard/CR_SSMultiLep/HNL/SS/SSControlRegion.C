#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLRegionPlotter.cc"

void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);
void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void SSControlRegion(){

  TString DATE = "Mar27";
  vector<TString> Eras =  {"2017"};// ,"2016preVFP" ,"2017","2018","Run2"};
  
  vector<TString> DiLepReg = {"PassCR1_MET", "PassCR1_BJet", "PassCR2_BJet","PassCR2_MET","PassCR3_MET_HighJet","PassCR3_BJet_HighJet","HNL_HighMassSSZPeak_AK4_TwoLepton_CR","HNL_HighMassSSZPeak_AK8_TwoLepton_CR","NoWeight_PassCR1"};


  

  //  for(auto iflav : {"LL","MuMu","EE","EMu"}){
  for(auto iflav : {"EE","EMu"}){
    SSControlRegionJob(DATE,2, Eras, iflav, {"WZ_Alt","qqZZ","ggZZ","WW_SS","Top","Other_SS","NonPrompt","Conv","chargeflip"} , DiLepReg , "HNL_ControlRegion_SSCRPlots_List1", "List1","SSMultiLep__");
    SSControlRegionJob(DATE,2, Eras, iflav,{"WZ","qqZZ","ggZZ","WW_SS","Top","Other_SS","NonPrompt","Conv","chargeflip"} , DiLepReg , "HNL_ControlRegion_SSCRPlots_List3", "List3","SSMultiLep__");
  }
 
}

void SSControlRegionJob(TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  
  for (auto ir : Regions)    RunFunction(DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = { "HNL_ULIDv2", "HNTightV2", "HNL_ULIDv2_AK8Loose","POGTight"};

      //// Run Yield print code                                                                                                                                                                                                                                                              
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
      

      Plotter.AddHist("MainPlots/Lepton_1_pt" ,"P^{1}_{T} GeV" , "GeV", {0, 20., 50.,75.,100.,125., 200.,500}, 0, 500);
      Plotter.AddHist("MainPlots/Lepton_2_pt" ,"P^{2}_{T} GeV" , "GeV", {0.,10.,15., 25.,30,40,50,75,100., 200.}, 0, 200);

      Plotter.AddHist("Leptons/Lep_1_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
      Plotter.AddHist("Leptons/Lep_2_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);

      Plotter.AddHist("Leptons/SumQ" ,"Sum Charge" , "int", {1},-5,5);

      Plotter.AddHist("Mass/DiJet_M_l1jj"  ,"M_{l1W}"  , "GeV",    {0,150,200,300,400,600,2000}, 0, 2000);
      Plotter.AddHist("Mass/DiJet_M_lljj"  ,"M_{llW}"  , "GeV",    {0,150,200,300,400,600,2000}, 0, 2000);
      Plotter.AddHist("DeltaR/dR_ll" ,"#DeltaR_{LL}"  , "", {5.}, 0, 5);
      Plotter.AddHist("DeltaPhi/dPhi_lep1_lep2" ,"#Delta#phi_{LL}"  , "", {5.}, 0, 5);
      Plotter.AddHist("DiLepton/ll_Pt" ,"Z Pt"  , "", {2.}, 0, 500);

      Plotter.AddHist("Standard/N_AK4J"  ,"N_{AK4J}"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Standard/N_AK4J_30"  ,"N_{AK4J}"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Standard/N_AK4J_tau"  ,"N_{AK4J}"  , "",    {1.}, 0, 10);

      Plotter.AddHist("Standard/Ev_MET"  ,"Ev_MET"  , "",    {2.}, 0, 400);
      Plotter.AddHist("Standard/M_ll"  ,"M_{ll}"  , "GeV",    {2},0,500);
      
      Plotter.AddHist("NObj/N_BJet"  ,"N_{BJ}"  , "",    {1.}, 0, 4);
      Plotter.AddHist("NObj/N_tau"  ,"N_{tau}"  , "",    {1.}, 0, 4);
      Plotter.AddHist("AK4Jets/Jet_eta"  ,"Jet Eta"  , "",    {5.}, -5, 5);
      Plotter.AddHist("AK4Jets/Jet_pt"  ,"Jet Pt"  , "",    {1.}, 0, 200);

      Plotter.AddHist("AK8/AK8J_Mass/l1J"  ,"Jet Eta"  , "",    {2.}, 0, 1000);
      Plotter.AddHist("AK8/AK8J_Mass/llJ"  ,"Jet Eta"  , "",    {2.}, 0, 1000);
      Plotter.AddHist("AK8/AK8J_Eta"  ,"Jet Eta"  , "",    {1.}, -5, 5);
      Plotter.AddHist("AK8/AK8J_Eta"  ,"Jet Eta"  , "",    {1.}, -5, 5);
      Plotter.AddHist("AK8/AK8J_Tagger_particleNet_WvsQCD"  ,"Jet Pt"  , "",    {2.}, 0, 1);

      Plotter.AddHist("MainPlots/Ev_MET2_ST"  ,"MET^{2}/S_{T}","GeV",  {0,5,10,15,20,30,40,50,75,100}, 0, 100);
      Plotter.AddHist("MainPlots/HT_PT1","H_{T}/p^{lep_{1}}_{T} GeV", "GeV", {0,2,3,4,5,10},0, 10);
      Plotter.AddHist("MainPlots/L_T","L_{T}  GeV", "GeV", {0,50,100,200,500,1000},0, 1000);

      Plotter.AddHist("VBF/Lead_MJJ"  ,""  , "",    {1.}, 0, 3000);
      Plotter.AddHist("VBF/Lead_zeppenfeld"  ,""  , "",    {1.}, 0, 2);

      
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
      
      
    }
  }
  
  
  return;
}

