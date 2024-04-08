#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void LooseIDOptHFMVA(){

  TString LabelForWeb = "HNL_LeptonFakeRate_TEST";

  vector<TString> eras =  {"2017"};//, "2017", "2018"};
  vector<TString> EtaBins = {"Eta1","Eta2","Eta3"};

  vector<TString> ShiftVals = {};
  vector<double>  Shifts;  
  for (unsigned int ishift = 0 ; ishift < 150; ishift++){
    double shiftEl = -1.0 + double(ishift)*0.01;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
    Shifts.push_back(shiftEl);
  }

  vector<TString> BkgType = {"TT"};//,"Top","MC"};

  for(auto Bkg : BkgType){
    
    TString ID="MuMu_HNL_ID";
    for (auto year : eras){
      for (auto EtaBin : EtaBins){
	
	vector<double>  vLFRates;
	vector<double>  vHFRates;
	
	for(auto ShiftVal : ShiftVals){
	  
	  HNLPlotter Plotter("HNL_LeptonFakeRate");
	  Plotter.SetupPlotter(year,"","HNL_LeptonFakeRate");
	  Plotter.DoDebug=false;
	  Plotter.CopyToWebsite = true;
	  
	  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/MCFakes__/HNL_LeptonFakeRate_"+Bkg+".root";
	  
	  Plotter.XaxisMin = 10;
	  Plotter.XaxisMax = 80;
	  
	  TH1D *hist_LF_Loose          = Plotter.ConstructHist(path,"MCFakeOpt/MVATop_"+ShiftVal + "/LF_"+EtaBin  + "_"+ID+"_Loose");
	  TH1D *hist_LF_Tight          = Plotter.ConstructHist(path,"MCFakeOpt/MVATop_"+ShiftVal + "/LF_"+EtaBin  + "_"+ID+"_Tight");
	  
	  TH1D *hist_HF_Loose          = Plotter.ConstructHist(path,"MCFakeOpt/MVATop_"+ShiftVal + "/HF_"+EtaBin  + "_"+ID+"_Loose");
	  TH1D *hist_HF_Tight          = Plotter.ConstructHist(path,"MCFakeOpt/MVATop_"+ShiftVal + "/HF_"+EtaBin  + "_"+ID+"_Tight");
	  
	  hist_LF_Tight->Divide(hist_LF_Loose);
	  hist_HF_Tight->Divide(hist_HF_Loose);
	  
	  double chi2 = hist_LF_Tight->Chi2Test(hist_HF_Tight,"CHI2 WW");
	  
	  hist_LF_Tight->GetYaxis()->SetTitle("Fake Rates");
	  //hist_LF_Tight->GetXaxis()->SetTitle(PtTypeString);
	  
	  vLFRates.push_back(hist_LF_Tight->GetBinContent(2));
	  vHFRates.push_back(hist_HF_Tight->GetBinContent(2));
	  
	  TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
	  //Plotter.SaveHists({hist_LF_Tight,hist_HF_Tight}, {"LF " + PtTypeString +" " + EtaBin, "HF " + PtTypeString +" " + EtaBin}, Bkg+"_HNL_LeptonFakeRateIDOpt_"+ShiftVal+"_"+"_"+EtaBin, LabelForWeb, {Chi2Label});
	  
	  //cout << "LFRAte = " << hist_LF_Tight->GetBinContent(2) << " HFRate = " << hist_HF_Tight->GetBinContent(2) << " ratio = " << hist_LF_Tight->GetBinContent(2)  / hist_HF_Tight->GetBinContent(2) << endl;
	}
	
	cout << "Bkg= " << Bkg << endl;
	cout << year << " Eta bin= " << EtaBin << endl;
	for(int i=0; i< vLFRates.size(); i++){
	  cout << "Shift " << ShiftVals[i] << " LFRAte = " <<  vLFRates[i] << " HFRate = "  <<  vHFRates[i] << " Ratio = " << vLFRates[i]/ vHFRates[i] << endl;
	}
      }
    }
  }
  
  return;
}

