#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyZShiftPrintChi2Individual(TString a, TString b);

void EnergyZShiftPrintChi2(){
  EnergyZShiftPrintChi2Individual("2016a","BB");
  EnergyZShiftPrintChi2Individual("2016a","EC");

  EnergyZShiftPrintChi2Individual("2016b","BB");
  EnergyZShiftPrintChi2Individual("2016b","EC");

  EnergyZShiftPrintChi2Individual("2017","BB");
  EnergyZShiftPrintChi2Individual("2017","EC");


  EnergyZShiftPrintChi2Individual("2018","BB");
  EnergyZShiftPrintChi2Individual("2018","EC");

}

void EnergyZShiftPrintChi2Individual(TString era, TString EtaBin){

  TString LabelForWeb = "HNL_ChargeFlip_2023Oct_ZMass";

  vector<TString> eras =  {era};
  vector<TString> EtaBins = {EtaBin};
  vector<TString>  HistNames = {"ZEnergyShift"};
  vector<TString> ShiftVals = {};

  map<TString,TString> Results;
  for (unsigned int ishift = 0 ; ishift < 50; ishift++){
    double shiftEl = 1.0 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
    ShiftVals.push_back(shift_string+"_sloped");
  }
  ShiftVals.push_back("SingleElShift");
  ShiftVals.push_back("AverageSingleEl");

  for(auto is : ShiftVals ) cout << "--> " << is << endl;


  for (auto era : eras){
    TString year = era;
    if (era.Contains("2016")) year = "2016";
    
    vector<TString> IDs = {"POGTight"};//,"HNL_ULID_"+year,"HNTightV2","TopHN"};

    for(auto ID : IDs){
      for (auto EtaBin : EtaBins){
	for(auto histname : HistNames){
	  
	  map<double,TString> Arraychi2;
	  for(auto ShiftVal : ShiftVals){
	    cout << histname << " " << ShiftVal << endl;
	    if(histname == "EnergyShift"  &  !ShiftVal.Contains("SingleElShift")) continue;
	    if(histname == "ZEnergyShift" &  ShiftVal.Contains("SingleElShift")) continue;

	    HNLPlotter Plotter("HNL_ChargeFlip_ZShift");
	    Plotter.SetupPlotter(era,"","HNL_ChargeFlip");
	    Plotter.DoDebug=true;
	    Plotter.CopyToWebsite = true;
	    
	    TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+era+"/ShiftZ/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShiftZ.root";
	    
	    TH1D *hist_SS             = Plotter.ConstructHist(path,ID+"CFRate_PtInv/ZMass/SS_"+EtaBin);

	    cout << path << endl;
	    cout << ID+"CFRate_Pt/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal << endl;
	    TH1D *hist_OS   = Plotter.ConstructHist(path,ID+"CFRate_PtInv/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal);
	    
	    hist_SS->Scale(1./hist_SS->Integral());
	    hist_OS->Scale(1./hist_OS->Integral());
	    hist_SS->Chi2Test(hist_OS,"p WW");
	    
	    double chi2 = hist_SS->Chi2Test(hist_OS,"CHI2");
	    Arraychi2[chi2] = EtaBin+  "_Weighted_"+histname+"_"+ShiftVal;
	    
	    hist_SS->GetYaxis()->SetTitle("Cut Efficiency");
	    hist_SS->GetXaxis()->SetTitle("Reco - Gen / Gen");
	    
	  }
	  cout  << histname+"_"+EtaBin << "Chi2:  " << endl;	  
	  int nMap=0;
	  for(auto i : Arraychi2){
	    if(nMap==0) Results[era+"_"+ID+"_"+EtaBin] = i.second; 
	    cout << era << " " << EtaBin << " " << i.first << " " << i.second << endl;
	    nMap++;
	  }
	}
      }
    }	
  }
  for(auto i : Results)             cout << i.first << " " << i.second << endl;  
  return;
}

