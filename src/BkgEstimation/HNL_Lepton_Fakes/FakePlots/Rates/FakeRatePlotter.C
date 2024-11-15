#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       


void FakeRatePlotter(){
  
  vector<TString> Eras = {"2017"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "HNL_LeptonFakeStudy_2024_FakeRates";

  vector<TString> EtaBins = {"BB","EC"};
  for (auto year : Eras){
    for( auto EtaBin : EtaBins){
      HNLPlotter Plotter("HNL_LeptonFakeStudy");
      Plotter.SetupPlotter(year,"","HNL_LeptonFakeStudy");
      Plotter.CopyToWebsite = true;
      
      TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonFakeStudy/"+year+"/QCD.root";  
      TString pathTT="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonFakeStudy/"+year+"/TT.root";  
      
      vector<TH1D*> hists;
    
      TH1D *hist_Numerator     = Plotter.ConstructHist(path,
						       "Fakerates/TightEl_"+EtaBin+"_pt");
      
      TH1D *hist_Denominator   = Plotter.ConstructHist(path,
						       "Fakerates/LooseEl_"+EtaBin+"_pt");
      
      hist_Numerator->GetYaxis()->SetTitle("Fake Rates");
      hist_Numerator->GetYaxis()->SetRangeUser(0,0.6);
      hist_Numerator->GetXaxis()->SetRangeUser(0,99);
      hist_Numerator->Divide(hist_Denominator);
      hists.push_back(hist_Numerator);
      
      TH1D *hist_TT_Numerator     = Plotter.ConstructHist(pathTT,
                                                       "/TightEl_"+EtaBin+"_pt");

      TH1D *hist_TT_Denominator   = Plotter.ConstructHist(pathTT,
                                                       "Fakerates/LooseEl_"+EtaBin+"_pt");

      hist_TT_Numerator->Divide(hist_TT_Denominator);

      //Plotter.DrawEfficiency(  hists  , {"QCD "+EtaBin+" MVA < 0.2"}, "BB_FakeRate_QCD",    LabelForWeb);
      hists.push_back(hist_TT_Numerator);

      Plotter.SaveHists(hists, {"QCD "+EtaBin+" MVA < 0.2","Top "+EtaBin+" MVA < 0.2"}, "MeasurementRegion_QCD_TT_"+EtaBin+"_"+year, LabelForWeb, {});


      
  
    }
  }
  
  return;
}

