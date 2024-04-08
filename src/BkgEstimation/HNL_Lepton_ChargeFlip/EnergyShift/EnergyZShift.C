#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyZShift(){

  TString LabelForWeb = "HNL_ChargeFlip_2023Oct_ZMass";

  vector<TString> eras =  {"2016a"};
  vector<TString> EtaBins = {"EC","BB"};
  vector<TString>  HistNames = {"EnergyShift","ZEnergyShift"};
  vector<TString> ShiftVals = {};

  for (unsigned int ishift = 0 ; ishift < 50; ishift++){
    double shiftEl = 1.0 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
    ShiftVals.push_back(shift_string+"_sloped");
  }
  ShiftVals.push_back("SingleElShift");
  ShiftVals.push_back("AverageSingleEl");

  for (auto era : eras){
    for (auto EtaBin : EtaBins){
      for(auto ShiftVal : ShiftVals){
	for(auto histname : HistNames){

	  TString year = era;
	  if (era.Contains("2016")) year = "2016";

	  vector<TString> IDs = {"POGTight","HNL_ULID_"+year,"HNTightV2","TopHN"};
	  for(auto ID : IDs){
	    
	    if(histname == "EnergyShift"  &  ShiftVal != "SingleElShift") continue;
	    
	    HNLPlotter Plotter("HNL_ChargeFlip_ZShift");
	    Plotter.SetupPlotter(era,"","HNL_ChargeFlip");
	    Plotter.DoDebug=true;
	    Plotter.CopyToWebsite = true;
	    
	    TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+era+"/ShiftZ/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShiftZ.root";
	    
	    TH1D *hist_SS             = Plotter.ConstructHist(path,ID+"CFRate_Pt/ZMass/SS_"+EtaBin);

	    cout << ID+"CFRate_Pt/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal << endl;
	    TH1D *hist_OS   = Plotter.ConstructHist(path,ID+"CFRate_Pt/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal);
	    
	    hist_SS->Scale(1./hist_SS->Integral());
	    hist_OS->Scale(1./hist_OS->Integral());
	    hist_SS->Chi2Test(hist_OS,"p WW");
	    
	    double chi2 = hist_SS->Chi2Test(hist_OS,"CHI2 WW");
	    
	    hist_SS->GetYaxis()->SetTitle("Cut Efficiency");
	    hist_SS->GetXaxis()->SetTitle("Reco - Gen / Gen");
	    
	    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
	    //Plotter.SaveHists({hist_SS,hist_OS}, {"CF " + EtaBin, "OS Weigthed"}, "CF_ZMass_"+ID+"_"+histname+"_"+ShiftVal+"_"+EtaBin, LabelForWeb, {Chi2Label});
	    cout  << histname+"_"+ShiftVal+"_"+EtaBin << "Chi2Label = " << Chi2Label << endl;
	  }
	}
      }	
    }
  }
  
  return;
}

