#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyCFShift(){

  TString LabelForOutPut = "HNL_ChargeFlip_2023_OctTEST";

  vector<TString> eras =  {"2018"};//, "2016b", "2017", "2018"};
  vector<TString> EtaBins = {"BB","EE1","EE2"};
  vector<TString> HistStrings = {"_Pt1" ,"_Pt2", "_Pt3", "_Pt4","_Pt5"};
  vector<TString> ShiftVals = {};

  for (unsigned int ishift = 0 ; ishift < 25; ishift++){
    double shiftEl = 1.0 - double(ishift)*0.002;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  vector<TString> IDs = {"HNTightV2"};
  for (auto year : eras){
    for (auto EtaBin : EtaBins){

      int ih=0;
      for (auto HistString : HistStrings){
        ih++;
        if(EtaBin.Contains("BB") && (ih > 3)) continue;

	for(auto ShiftVal : ShiftVals){
	  
	  HNLPlotter Plotter("HNL_ChargeFlipResponse");
	  Plotter.SetupPlotter(year,"","HNL_ChargeFlip");
	  Plotter.DoDebug=false;
	  Plotter.CopyToWebsite = false;
	  
	  
	  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+year+"/Shift/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShift.root";
	  
	  for(auto ID : IDs){

	    Plotter.XaxisMin = -0.2;
	    Plotter.XaxisMax = 0.2;
	    cout << ID+"/EnergyShift/"+EtaBin+HistString+"_CF" << endl;
	    TH1D *hist_CF             = Plotter.ConstructHist(path,ID+"/EnergyShift/"+EtaBin+HistString+"_CF");
	    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID+"/EnergyShift/"+EtaBin+HistString+"_PromptShifted_"+ShiftVal);
	    
	    hist_CF->Scale(1./hist_CF->Integral());
	    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());
	    
	    hist_CF->Chi2Test(hist_PromptScaled,"p WW");
	    
	    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2 WW");
	    
	    hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
	    hist_CF->GetXaxis()->SetTitle("Reco - Gen / Gen");
	    
	    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
	    Plotter.SaveHists({hist_CF,hist_PromptScaled}, {"CF "+HistString+" " + EtaBin, "OS Weigthed"}, ID+"_CF_EnergyShift_"+ShiftVal+"_"+HistString+"_"+EtaBin, LabelForOutPut, {Chi2Label});
	  }
	}
      }	
    }
  }
  
  return;
}

