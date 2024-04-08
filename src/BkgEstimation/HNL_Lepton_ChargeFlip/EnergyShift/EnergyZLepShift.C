#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyZLepShift(){

  TString LabelForWeb = "HNL_ChargeFlip_2023_Oct1v3";

  vector<TString> eras =  {"2016a"};//,"2016b","2017","2018"};
  vector<TString> EtaBins = {"EC","BB"};
  vector<TString> LepHists = {"Pt","Eta"};
  vector<TString> IDs = {"POGTight"};//,"HNL_ULID_2017","HNTightV2","TopHN"};
  vector<TString>  HistNames = {"EnergyShift","ZEnergyShift"};
  vector<TString> PtTypes = {"CFRate_PtInv"};

  vector<TString> ShiftVals = {};

  for (unsigned int ishift = 0 ; ishift < 50; ishift++){
    double shiftEl = 1.0 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
    ShiftVals.push_back(shift_string+"_sloped");
  }
  ShiftVals.push_back("SingleElShift");
  ShiftVals.push_back("AverageSingleEl");


  //OS_EC_Weighted_ZEnergyShift_Eta1  
  map<double, TString> Chi2Results;
  for (auto year : eras){

    for(auto ID : IDs){
      
      for (auto EtaBin : EtaBins){
	for(auto ShiftVal : ShiftVals){
	  for(auto histname : HistNames){
	    for(auto LepHist :LepHists ){
	      for(auto PtType : PtTypes){
		
		if(0){
		  if(histname == "ZEnergyShift" && ShiftVal.Contains("SingleElShift")) continue;
		  if(histname == "EnergyShift" && !ShiftVal.Contains("SingleElShift")) continue;
		  HNLPlotter Plotter("HNL_ChargeFlip_ZShift_Lep");
		  Plotter.SetupPlotter(year,"","HNL_ChargeFlip");
		  Plotter.DoDebug=true;
		  Plotter.CopyToWebsite = true;
		  
		  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+year+"/ShiftZ/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShiftZ.root";
		  cout << path << endl;
		  TString SSLep = "LepEta";
		  if(LepHist=="Pt") SSLep = "LepPt";
		  
		  
		  TH1D *hist_SS             = Plotter.ConstructHist(path,ID+PtType+"/Z/SS_"+EtaBin+"_"+SSLep);
		  TH1D *hist_OS   = Plotter.ConstructHist(path,ID+PtType+"/Z/OS_"+EtaBin+  "_Weighted_"+histname+"_"+LepHist+"_"+ShiftVal);
		  cout << ID+PtType+"/Z/SS_"+EtaBin +"_"+SSLep<< endl;
		  //POGTightCFRate_Pt/Z/OS_  EC        _Weighted_ZEnergyShift_Eta1
		  cout << ID+PtType+"/Z/OS_"+EtaBin+  "_Weighted_"+histname+"_"+LepHist+"_"+ShiftVal << endl;
		  cout << hist_OS << endl;
		  hist_SS->Scale(1./hist_SS->Integral());
		  hist_OS->Scale(1./hist_OS->Integral());
		  hist_SS->Chi2Test(hist_OS,"p WW");
		  
		  double chi2 = hist_SS->Chi2Test(hist_OS,"CHI2 WW");
		  Chi2Results[chi2] = "CF_Z_"+LepHist+"_"+ID+"_"+histname+"_"+ShiftVal+"_"+EtaBin+PtType;
		  hist_SS->GetXaxis()->SetTitle("");
		  
		  TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
		  Plotter.SaveHists({hist_SS,hist_OS}, {"CF " + EtaBin, "OS Weigthed"}, "CF_Z_"+LepHist+"_"+ID+"_"+histname+"_"+ShiftVal+"_"+EtaBin+PtType, LabelForWeb, {Chi2Label});
		  
		}

		if(1){
		  
                  if(histname == "ZEnergyShift" && ShiftVal.Contains("SingleElShift")) continue;
                  if(histname == "EnergyShift" && !ShiftVal.Contains("SingleElShift")) continue;
                  HNLPlotter Plotter("HNL_ChargeFlip_ZShift_Mass");
		  
		  Plotter.SetupPlotter(year,"","HNL_ChargeFlip");
		  Plotter.DoDebug=true;
		  Plotter.CopyToWebsite = true;
		  
		  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+year+"/ShiftZ/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShiftZ.root";
		  cout << path << endl;

		  TH1D *hist_SS             = Plotter.ConstructHist(path,ID+PtType+"/ZMass/SS_"+EtaBin);
		  TH1D *hist_OS   = Plotter.ConstructHist(path,ID+PtType+"/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal);
		  
		  cout << ID+PtType+"/ZMass/OS_"+EtaBin+  "_Weighted_"+histname+"_"+ShiftVal ;
		  hist_SS->Scale(1./hist_SS->Integral());
		  hist_OS->Scale(1./hist_OS->Integral());
		  hist_SS->Chi2Test(hist_OS,"p WW");
		  
		  double chi2 = hist_SS->Chi2Test(hist_OS,"CHI2 WW");
		  Chi2Results[chi2] =  "CF_ZMass_"+ID+"_"+histname+"_"+ShiftVal+"_"+EtaBin+PtType;
		  
		  hist_SS->GetYaxis()->SetTitle("Events");
		  hist_SS->GetXaxis()->SetTitle("Z Mass");
		  
		  TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
		  //Plotter.SaveHists({hist_SS,hist_OS}, {"CF " + EtaBin, "OS Weigthed"}, "CF_ZMass_"+ID+"_"+histname+"_"+ShiftVal+"_"+EtaBin+PtType, LabelForWeb, {Chi2Label});
		  cout << "Chi2 " << chi2 << endl;
		}
	      }

	    }
	  }
	}
      }	
    }
  }
  for(auto Chi2Result :Chi2Results) cout << Chi2Result.second << " --> " << Chi2Result.first << endl;
  
  return;
}

