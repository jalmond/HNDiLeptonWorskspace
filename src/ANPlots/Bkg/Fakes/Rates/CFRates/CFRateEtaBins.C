#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void CFRateEtaBinsIndiv(TString etabin);

void CFRateEtaBins(){
  CFRateEtaBinsIndiv("EtaRegion1");
  CFRateEtaBinsIndiv("EtaRegion2");
  CFRateEtaBinsIndiv("EtaRegion3");
  CFRateEtaBinsIndiv("EtaRegion4");
  CFRateEtaBinsIndiv("EtaRegion5");
  CFRateEtaBinsIndiv("EtaRegion6");
  CFRateEtaBinsIndiv("EtaRegion7");
  CFRateEtaBinsIndiv("EtaRegion8");
  CFRateEtaBinsIndiv("EtaRegion9");

}

void CFRateEtaBinsIndiv(TString etabin){
  
  vector<TString> Eras = {"2017"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "CFRateEta_2023_AN";

  for (auto Era : Eras){

    TString year = Era.Contains("16") ? "2016" : Era;

    TString ID = "HNL_ULID_"+year;
    HNLPlotter Plotter("HNL_Lepton_ChargeFlip");
    Plotter.SetupPlotter(year,"","HNL_Lepton_ChargeFlip");
    Plotter.CopyToWebsite = true;
    
    TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_ChargeFlip/"+year+"/Rates/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";
    
   
    vector<TH1D*> hists;

    cout << path << ID+"/CFrate/Num" << endl;
    TH1D *hist_eta1_Numerator     = Plotter.ConstructHist(path, ID+"/CFrate/"+etabin+"_Num");
    TH1D *hist_eta1_Denominator   = Plotter.ConstructHist(path, ID+"/CFrate/"+etabin+"_Denom");

    cout << hist_eta1_Numerator->Integral() << " " << hist_eta1_Denominator->Integral() << endl;

    hist_eta1_Numerator->GetXaxis()->SetTitle("Electron 1/p_{T} (GeV)");
    
    hist_eta1_Numerator->GetYaxis()->SetTitle("CF_{Rates}");
    hist_eta1_Numerator->GetYaxis()->SetRangeUser(0.000001,0.01);
    hist_eta1_Numerator->GetXaxis()->SetRangeUser(0.002,0.1);
    hist_eta1_Numerator->Divide(hist_eta1_Denominator);
    hists.push_back(hist_eta1_Numerator);
    
    TH1D *hist3_eta1_Numerator     = Plotter.ConstructHist(path, "POGTight/CFrate/"+etabin+"_Num");
    TH1D *hist3_eta1_Denominator   = Plotter.ConstructHist(path, "POGTight/CFrate/"+etabin+"_Denom");


    hist3_eta1_Numerator->Divide(hist3_eta1_Denominator);
    hists.push_back(hist3_eta1_Numerator);


    
    Plotter.SetLogY=true;
    Plotter.SaveHists(hists, {"MVA_ULID","POGT (TC+IP)", "POGT"}, "HNL_Lepton_ChargeFlip_"+ID+"_DATA_"+etabin, LabelForWeb, {},true);
    
  }
  
  return;
}

