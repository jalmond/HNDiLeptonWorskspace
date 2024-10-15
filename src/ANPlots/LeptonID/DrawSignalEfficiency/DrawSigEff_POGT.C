#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString filepath);

void DrawSigEff_POGT(){
  
  //  DrawConfig("May12","MuMu","2016preVFP", "HNLvsPOGTight");
  //DrawConfig("May12","MuMu","2016postVFP", "HNLvsPOGTight");
  //DrawConfig("May12","MuMu","2017", "HNLvsPOGTight");
  DrawConfig("Aug30","EE","2018","HNLvsPOGTight");

}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString filepath){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter("SignalIDEfficiency");
    Plotter.SetupPlotter(year,"",Flavour+"_ID_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";

    TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+era+"/SIG/HNL_SignalRegion_Plotter_TT_HeavyN-El_2L_MN";
    
    
    vector<TString> Masses = {"20","40","50","60","70","85","95"};


    TString ID = "TopHN";

    int nTop2L = 7;
    double MassesTop[nTop2L];
    MassesTop[0] = 20;
    MassesTop[1] = 40;
    MassesTop[2] = 50;
    MassesTop[3] = 60;
    MassesTop[4] = 70;
    MassesTop[5] = 85;
    MassesTop[6] = 95;


    double vEffPre[nTop2L];
    double vEffPre2[nTop2L];


    for(unsigned int i = 0 ; i < nTop2L ; i++){
      TString path_mass = path + MassesTop[i] + ".root";
      
      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour +"/ChannelDependant_Inclusive");
      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_Presel");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPre[i] = EffPre;
      cout << "DY " << MassesTop[i] << " Eff = " << EffPre << endl;
    }
    for(unsigned int i = 0 ; i < nTop2L  ; i++){
      TString path_mass = path + MassesTop[i] + ".root";

      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/POGTight/"+Flavour +"/ChannelDependant_Inclusive");

      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/POGTight/"+Flavour+"/ChannelDependant_Presel");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPre2[i] = EffPre;
      cout << "DY " << MassesTop[i] << " Eff = " << EffPre << endl;
    }
    

    TGraphAsymmErrors *gPre = new TGraphAsymmErrors(nTop2L,MassesTop , vEffPre);
    TGraphAsymmErrors *gPre2 = new TGraphAsymmErrors(nTop2L,MassesTop , vEffPre2);

    Plotter.draw_SignalEff_canvas(gPre,gPre2,  Flavour+"_DYEff",year,"HNTop_"+year);
    
  }
  
  return;
}



