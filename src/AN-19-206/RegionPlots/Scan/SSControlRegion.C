#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLScanPlotter.cc"

void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, TString Region);

void SSControlRegion(){

  TString  DateTag = "April20";
  vector<TString> Channels = {"EE"};
  vector<TString> Eras = {"Run2","2016preVFP", "2016postVFP","2017","2018"};

  if(0){
    // TEST CODE
    RunFunction(DateTag,{"2018"}, Channels, "HNL_ControlRegion_SSCRPlots_Inclusive","ScanFakes_Inclusive","HNL_HighMassNP_TwoLepton_CR");
    return ;
  }

  vector<TString> Regions = {"HNL_SSPresel_TwoLepton", "HNL_HighMassSR3_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassCR2_TwoLepton_CR","HNL_HighMassBJet_TwoLepton_CR","HNL_HighMassNP_TwoLepton_CR"};
  Regions = {"HNL_HighMassBJet_TwoLepton_CR"};
  for (auto ir : Regions){
    RunFunction(DateTag,Eras, Channels, "HNL_ControlRegion_SSCRPlots_Inclusive","ScanFakes_Inclusive",ir); 
    RunFunction(DateTag,Eras, Channels, "HNL_ControlRegion_SSCRPlots_Barrel","ScanFakes_BB",ir); 
    RunFunction(DateTag,Eras, Channels, "HNL_ControlRegion_SSCRPlots_Endcap","ScanFakes_EC",ir);                                                      
  }
  
  if(0){
    TString Region = "HNL_HighMass1Jet_TwoLepton_CR";
    RunFunction(DateTag,Eras, {"EE"}, "HNL_ControlRegion_SSCRPlots_Inclusive","ScanFakes_Inclusive",Region); 
    RunFunction(DateTag,Eras, {"EE"}, "HNL_ControlRegion_SSCRPlots_Barrel","ScanFakes_BB",Region); 
    RunFunction(DateTag,Eras, {"EE"}, "HNL_ControlRegion_SSCRPlots_Endcap","ScanFakes_EC",Region); 
  }

}


void RunFunction(TString DateFileTag,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,TString Region){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLScanPlotter Plotter(PlotterTag+"_"+channel);
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.RunScan = true;
      Plotter.DateFileTag = DateFileTag;

      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion","/"+Flag);
      ///Plotter.infilepath = .... if inut file is not in Mergeddir

      if(channel == "MuMu")Plotter.samples_to_use = {"Prompt","NonPrompt","Conv"};
      else Plotter.samples_to_use = {"Prompt","NonPrompt","Conv","chargeflip"};
      
      TString DefaultHistName = "HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ30/"+channel;
      vector<TString> AJetPt = {"AJ30","AJ40"};
      TString Year = (year.Contains("2016")) ? "2016" : year;
      if(channel == "EE") AJetPt.push_back("AJ25");
      vector<TString> FakeIDs = {  "HNL_ULID_FO_v1_a",
                                   "HNL_ULID_FO_v1_b",
                                   "HNL_ULID_FO_v1_c",
                                   "HNL_ULID_FO_v2_a",
                                   "HNL_ULID_FO_v2_b",
                                   "HNL_ULID_FO_v2_c",
                                   "HNL_ULID_FO_v3_a",
                                   "HNL_ULID_FO_v3_b",
                                   "HNL_ULID_FO_v3_c",
                                   "HNL_ULID_FO_v4_a",
                                   "HNL_ULID_FO_v4_b",
                                   "HNL_ULID_FO_v4_c",
                                   "HNL_ULID_FO_v5_a",
                                   "HNL_ULID_FO_v5_b",
                                   "HNL_ULID_FO_v5_c",
                                   "HNL_ULID_FO_v6_a",
                                   "HNL_ULID_FO_v6_b",
                                   "HNL_ULID_FO_v6_c",
                                   "HNL_ULID_FO_v7_a",
                                   "HNL_ULID_FO_v7_b",
                                   "HNL_ULID_FO_v7_c",
                                   "HNL_ULID_FO_v8_a",
                                   "HNL_ULID_FO_v8_b",
                                   "HNL_ULID_FO_v8_c",
                                   "HNL_ULID_FO_v9_a",
                                   "HNL_ULID_FO_v9_b",
                                   "HNL_ULID_FO_v0",
                                   "HNL_ULID_FO_v9_c"};

      vector<TString> FakeParam = {"PtParton","Pt"};
      vector<TString> Dirs;
      for(auto id : FakeIDs) {
        for(auto ij : AJetPt){
          for(auto ik : FakeParam){
	                Dirs.push_back( "HNL_ULID_"+id+"_Standard_"+ik+"_"+ij+"/"+channel);
          }
        }
      }

      

      vector<TString> HPaths,RegionTypes,vDefaultHistName;
      for(auto id : Dirs){ 
	HPaths.push_back( Region+"/"+id);
	vDefaultHistName.push_back( Region+"/"+DefaultHistName);
      }
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      Plotter.DefaultHists= vDefaultHistName;
      
      
      Plotter.BasicSetup(HNLScanPlotter::NoLOGY, HNLScanPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      //Plotter.AddHist("DeltaR/dR_ll" ,"dR_LL"  , "", {2.}, 0, 5);
      Plotter.AddHist("NObj/N_AK4J"  ,"NJ4"  , "",    {1.}, 0, 10);
      //Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {10,15,20,30.,40., 60.,100, 200}, 10, 200);                                                                                                                  
      //if(channel == "EE")Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {10,15,20,30.,40., 60.,100, 200}, 10, 200);
      //else Plotter.AddHist("Leptons/Lep_2_pt" ,"LPT2" , "int", {10.,15.,20.,30.,40., 60.,100., 200.}, 0, 200);
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.make_cutflow("N_AK4Jets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

