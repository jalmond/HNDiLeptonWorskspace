#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void CFRatePlotterTemplate(TString year, TString LabelForWeb, TString VarName, TString axislabel, int rb);

void CFRatePlotter(){
  
  vector<TString> Eras = {"2016a", "2016b", "2017", "2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};                                                                                                                         
  TString LabelForWeb = "CFRateEta_2024_Mar27";
  
  for (auto year: Eras){
    //CFRatePlotterTemplate(year,LabelForWeb, "CFrate_MVA","el MVA",1);
    //CFRatePlotterTemplate(year,LabelForWeb, "CFratePt_mEta","el Pt",1);
    //CFRatePlotterTemplate(year,LabelForWeb, "CFratePt_pEta","el Pt",1);
    //CFRatePlotterTemplate(year,LabelForWeb, "CFrate_IP","el IP",1);
    CFRatePlotterTemplate(year,LabelForWeb, "CFrate","el #eta_{SC}",1);
    // CFRatePlotterTemplate(year,LabelForWeb, "CFrate_Eta_Ptlt50","el #eta_{SC} (p_T < 50 GeV)",2);
    //CFRatePlotterTemplate(year,LabelForWeb, "CFrate_Eta__Ptgt50","el #eta_{SC} (p_T > 50 GeV)",2);
  }

}

void CFRatePlotterTemplate(TString era, TString LabelForWeb, TString VarName, TString axislabel, int rebin){
  
  TString PtLabel = "";
  TString year = (era.Contains("16")) ? "2016" : era;
  
  TString ID = "HNL_ULID_"+year;
  HNLPlotter Plotter("HNL_Lepton_ChargeFlip");
  Plotter.SetupPlotter(year,"","HNL_Lepton_ChargeFlip");
  Plotter.CopyToWebsite = true;
  
  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_ChargeFlip/"+era+"/Rates/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";
  
    cout << path << endl;
    vector<TH1D*> hists;
      
    TH1D *hist_Numerator     = Plotter.ConstructHist(path, ID+PtLabel+"/"+VarName+"/Num");
    TH1D *hist_Denominator   = Plotter.ConstructHist(path, ID+PtLabel+"/"+VarName+"/Denom");
    hist_Numerator->Rebin(rebin);
    hist_Denominator->Rebin(rebin);
    hist_Numerator->GetXaxis()->SetTitle(axislabel);
    hist_Numerator->GetYaxis()->SetTitle("CF_{Rates}");
    hist_Numerator->GetYaxis()->SetRangeUser(0.00001,1.);
    hist_Numerator->Divide(hist_Denominator);
    hists.push_back(hist_Numerator);


    //    TH1D *hist_Numerator_HNTightV2     = Plotter.ConstructHist(path, "HNTightV2"+PtLabel+"/"+VarName+"/Num");
    //    TH1D *hist_Denominator_HNTightV2   = Plotter.ConstructHist(path, "HNTightV2"+PtLabel+"/"+VarName+"/Denom");
    //hist_Numerator_HNTightV2->Rebin(rebin);
    //hist_Denominator_HNTightV2->Rebin(rebin);

    //hist_Numerator_HNTightV2->Divide(hist_Denominator_HNTightV2);
    //hists.push_back(hist_Numerator_HNTightV2);

    TH1D *hist_Numerator_POG     = Plotter.ConstructHist(path, "POGTight"+PtLabel+"/"+VarName+"/Num");
    TH1D *hist_Denominator_POG   = Plotter.ConstructHist(path, "POGTight"+PtLabel+"/"+VarName+"/Denom");
    hist_Numerator_POG->Rebin(rebin);
    hist_Denominator_POG->Rebin(rebin);
    hist_Numerator_POG->Divide(hist_Denominator_POG);
    hists.push_back(hist_Numerator_POG);


    //Plotter.DrawEfficiency(  hists  , {"QCD "+EtaBin+" MVA < 0.2"}, "BB_FakeRate_QCD",    LabelForWeb);

    Plotter.SetLogY=true;
    Plotter.SaveHists(hists, {"MVA_ULID", "POG_T(TC+IP)", "POG_T"}, "HNL_Lepton_ChargeFlip_"+VarName+"_"+ID+"_DYMC_"+era, LabelForWeb, {year});
    
}

