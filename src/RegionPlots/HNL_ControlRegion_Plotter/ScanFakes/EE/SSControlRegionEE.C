#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SSControlRegionEERun(TString Era);

void SSControlRegionEE(){

  SSControlRegionEERun("2018");
}

void SSControlRegionEERun(TString Era){

  vector<TString> eras =  {Era};

  vector<TString> channels = {"EE"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      //HNLPlotter Plotter("HNL_ControlRegionPlotter_EE_2024_02_FAKESCAN");
      HNLPlotter Plotter("HNL_ControlRegionPlotter_EE_2024_02_CFValidation");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion","/ScanFakesBB");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      
      //Plotter.ScaleSample("CF",0.8);


      vector<TString> Dirs = {
        "HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v1_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v1_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v1_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v2_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v2_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v2_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v3_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v3_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v3_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v4_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v4_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v4_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v5_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v5_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v5_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v6_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v6_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v6_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v7_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v7_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v7_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v8_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v8_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v8_c_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v9_a_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v9_b_Standard_PtParton_AJ30",
        "HNL_ULID_HNL_ULID_FO_v9_c_Standard_PtParton_AJ30"};



      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassSR1_TwoLepton_CR/"+id+"/"+channel); 
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassCR2_TwoLepton_CR/"+id+"/"+channel); 
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassSR3_TwoLepton_CR/"+id+"/"+channel); 
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassNP_TwoLepton_CR/"+channel+"/"+id+"/RegionPlots_"+channel);                                        
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassBJet_TwoLepton_CR/"+id+"/"+channel);                                                              
      for(auto id : Dirs) HPaths.push_back( "HNL_SSPresel_TwoLepton/"+id+"/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id);
      for(auto id : Dirs) RegionTypes.push_back( id);
      for(auto id : Dirs) RegionTypes.push_back( id);
      for(auto id : Dirs) RegionTypes.push_back( id);
      for(auto id : Dirs) RegionTypes.push_back( id);
      for(auto id : Dirs) RegionTypes.push_back( id);

      HPaths.clear();
      RegionTypes.clear();
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMass1Jet_TwoLepton_CR/"+id+"/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id);

      


      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      //Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("Mass/M_ll" ,"M_ll" , "", {1.}, 0, 200);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "GeV", {0.,5.,10.,20.,40.,60.,100.,200}, 0, 200);
      Plotter.AddHist("Leptons/Lep_2_eta" ,"LETa2" , "", {5.}, -3, 3);


      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

