#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void SSControlRegionEE(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"EE"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("HNL_ControlRegionPlotter1611EE");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegionPlotter","/SS_CR");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir
      Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      
      ///Plotter.ScaleSample("WZ_pythia",0.95);

      vector<TString> Dirs = {  "HNTightV2",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ40",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ40",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ40",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ40",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtCorr_AJ40",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton_AJ40",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton2p0_AJ40",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_Pt_AJ40",

                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ30",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtCorr_AJ30",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton_AJ30",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton2p0_AJ30",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_Pt_AJ30",

                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FO_BDTFlavour_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv2_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv3_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv4_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv5_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULID_FOv6_Standard_Pt_AJ60",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtCorr_AJ60",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton_AJ60",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_PtParton2p0_AJ60",
                                "HNL_ULID_HNL_ULLID_FOv3_Standard_Pt_AJ60"};




      vector<TString> HPaths,RegionTypes;
      //for(auto id : Dirs) HPaths.push_back( "HNL_SSPresel_TwoLepton/"+channel+"/"+id+"/RegionPlots_"+channel);
      //for(auto id : Dirs) HPaths.push_back( "HNL_HighMassNP_TwoLepton_CR/"+channel+"/"+id+"/RegionPlots_"+channel);    
      for(auto id : Dirs) HPaths.push_back( "HNL_HighMassBJet_TwoLepton_CR/"+channel+"/"+id+"/RegionPlots_"+channel);    
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_",""));                   

      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      //Plotter.HistPath= {"HNL_HighMassCR2_TwoLepton_CR/RegionPlots_"+channel+"/HNL"};                                         
      //Plotter.RegionType = {"CR2"};    

      //Plotter.HistPath= {"HNL_HighMassSR3_TwoLepton_CR/RegionPlots_"+channel+"/HNL"}; 
      //Plotter.RegionType = {"CR3"};
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "GeV", {4.}, 10, 200);
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

