#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

void PrintEnergyCFShift(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.2;

  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;
    for(auto etabin :  {"BB"}){
      //EnergyCFShiftProccessor(Plotter, "HNTightV2", era,etabin, "HNL_ChargeFlip_EnergyShift");
      //EnergyCFShiftProccessor(Plotter, "POGTight", era,etabin, "HNL_ChargeFlip_EnergyShift");
      //     EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift");
      vector<TString> HistStrings = {"_PtBin1" ,"_PtBin2", "_PtBin3", "_PtBin4","_PtBin5"};
      //for(auto HistString : HistStrings)	EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin+HistString, "HNL_ChargeFlip_EnergyShift");
      for(auto HistString : HistStrings)	EnergyCFShiftProccessor(Plotter, "POGTight", era, etabin+HistString, "HNL_ChargeFlip_EnergyShift");
    }
    return;
  }
}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  cout << " " << endl;
  cout << "HistString =" << HistString << endl;


  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString pathCF="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/EnergyShift/HNL_Lepton_ChargeFlip_BDT_CF.root";
  TString pathPrompt="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/EnergyShift/HNL_Lepton_ChargeFlip_BDT_Prompt.root";

  vector<TString> ShiftVals = {};
  for (unsigned int ishift = 0 ; ishift < 150; ishift++){
    double shiftEl = 1.05 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  vector <double> Arraychi2;
  vector<TString> ShiftS;
  double MinChi2=99999999;

   				   
  for(auto ShiftVal : ShiftVals){

    TH1D *hist_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/"+HistString+"_CF");
    TH1D *hist_PromptScaled   = Plotter.ConstructHist(pathPrompt,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal);

    cout << ID+"/EnergyShift/"+HistString+"_CF" << hist_CF << endl;
    cout <<ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal << hist_PromptScaled << endl;
    cout << hist_CF->Integral() << " " << hist_PromptScaled ->Integral() << endl;
    hist_CF->Scale(1./hist_CF->Integral());
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());

    hist_CF->Chi2Test(hist_PromptScaled,"p WW");
    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2 WW");
    
    Arraychi2.push_back(chi2);
    if(chi2 < MinChi2) MinChi2=chi2;

    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
    cout << "ShiftVal " << ShiftVal << " Chi2 =  " << chi2 << endl;
  }

  cout << "HistString =" << HistString << endl;
  cout << "Min chi2 = " << MinChi2 << endl;
  for(unsigned int i=0; i < ShiftVals.size(); i++){
    if( MinChi2 == Arraychi2[i] ) cout << ShiftVals[i] << " " << Arraychi2[i] << " --- MINUMUM" << endl;
    else cout << ShiftVals[i] << " " << Arraychi2[i] << endl;
  }


  return;
}

