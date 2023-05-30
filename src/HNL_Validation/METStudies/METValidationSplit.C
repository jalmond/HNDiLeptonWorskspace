#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void METValidationSplit(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2018"};
  vector<TString> channels = {"MuMu","EMu"};
  
  for (auto year : eras){
    for (auto channel : channels){
      
      HNLPlotter Plotter("METValidationSplit");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = true;
      
      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_Dilepton", "HNL_Validation");
      ///Plotter.infilepath = .... if inut file is not in Mergeddir

      Plotter.samples_to_use = {"ttbar","DY","VV_incl"};
      Plotter.HistPath= { channel+"/POG_UL/RegionPlots_BJetCR_BTagSF",
			  channel+"/POG_UL/RegionPlots_ZPeak_BTagSF",
			  channel+"/POG_UL/RegionPlots_ZPeakPt50_BTagSF"};

      Plotter.RegionType = {"BJetCR","ZCR","ZCR(P_{T}>50)"};
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup
      Plotter.AddHist("METPt_PuppiT1xyULCorr" ,                     "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1xyULCorr_propsmear" ,           "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1xyULCorr_SmearJet_propsmear" ,  "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1xyULCorr_SmearMuon_propsmear" , "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1" ,                             "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1_propsmear" ,                   "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1xyCorr" ,                       "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_PuppiT1xyCorr_propsmear" ,             "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1" ,                                  "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1_propsmear" ,                        "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1xyCorr" ,                            "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1xyCorr_propsmear" ,                  "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1xyULCorr" ,                          "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);
      Plotter.AddHist("METPt_T1xyULCorr_propsmear" ,                "MET" , "GeV", {0.,8., 16., 24., 32., 40., 48., 56., 64., 72., 80., 100}, 0, 200);

      Plotter.AddHist("METPhi_PuppiT1xyULCorr" ,                    "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1xyULCorr_propsmear" ,          "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1xyULCorr_SmearJet_propsmear" , "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1xyULCorr_SmearMuon_propsmear" ,"METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1" ,                            "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1_propsmear" ,                  "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1xyCorr" ,                      "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_PuppiT1xyCorr_propsmear" ,            "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1" ,                                 "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1_propsmear" ,                       "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1xyCorr" ,                           "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1xyCorr_propsmear" ,                 "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1xyULCorr" ,                         "METPhi" , "", {1.}, -3.2, 3.2);
      Plotter.AddHist("METPhi_T1xyULCorr_propsmear" ,               "METPhi" , "", {1.}, -3.2, 3.2);

      Plotter.AddHist("LLMass" ,"MLL"  , "GeV", {2.}, 0, 400);
      Plotter.AddHist("NJets"  ,"NJ4"  , "",    {1.}, 0, 10);
      Plotter.AddHist("NBJets" ,"NBJ"  , "",    {1.}, 0, 4);
      Plotter.AddHist("nPV"    ,"nPv"  , "",    {1.}, 0, 100);
      Plotter.AddHist("Lep1Pt" ,"LPT1" , "GeV", {1.}, 20, 400);
      Plotter.AddHist("Lep2Pt" ,"LPT2" , "GeV", {1.}, 10, 200);

      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      //Plotter.DrawStackPlots();
      Plotter.make_cutflow("NJets");
      Plotter.Summary();
    }
  }
  
  
  return;
}

