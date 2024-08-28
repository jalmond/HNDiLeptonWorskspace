#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString filepath);

void DrawSigEffSR1(){
  
  DrawConfig("May12","EE","2016preVFP", "HNLvsHNTight");
  DrawConfig("May12","EE","2016postVFP", "HNLvsHNTight");
  DrawConfig("May12","EE","2017", "HNLvsHNTight");
  DrawConfig("May12","EE","2018","HNLvsHNTight");

}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString filepath){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter("SignalIDEfficiency");
    Plotter.SetupPlotter(year,"",Flavour+"_ID_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";

    TString pathDY="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+era+"/SIG/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYVBF_MN";
    TString pathSSWW="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+era+"/SIG/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWW_MN";
    
    
    vector<TString> MassesDYS = {"85","90", "95","100", "125", "150","200", "250","300", "400", "500", "600", "700", "800", "900", "1000",  "1100", "1200","1300", "1500", "1700", "2000"};

    vector<TString> MassesVBFS = {"500", "600", "700",  "800", "900", "1000", "1100", "1200", "1300","1500", "1700",  "2000", "2500", "3000", "5000", "7500","10000","15000","20000"}; 


    TString ID = "HNL_ULID";

    int nDY = 22;
    int nVBF = 20;
    double MassesDYD[nDY];
    MassesDYD[0] = 85;
    MassesDYD[1] = 90;
    MassesDYD[2] = 95;
    MassesDYD[3] = 100;
    MassesDYD[4] = 125;
    MassesDYD[5] = 150;
    MassesDYD[6] = 200;
    MassesDYD[7] = 250;
    MassesDYD[8] = 300;
    MassesDYD[9] = 400;
    MassesDYD[10] = 500;
    MassesDYD[11] = 600;
    MassesDYD[12] = 700;
    MassesDYD[13] = 800;
    MassesDYD[14] = 900;
    MassesDYD[15] = 1000;
    MassesDYD[16] = 1100;
    MassesDYD[17] = 1200;
    MassesDYD[18] = 1300;
    MassesDYD[19] = 1500;
    MassesDYD[20] = 1700;
    MassesDYD[21] = 2000;

    double massesVBFD[nVBF];
    massesVBFD[0] = 500;
    massesVBFD[1] = 600;
    massesVBFD[2] = 700;
    massesVBFD[3] = 800;
    massesVBFD[4] = 900;
    massesVBFD[5] = 1000;
    massesVBFD[6] = 1100;
    massesVBFD[7] = 1200;
    massesVBFD[8] = 1300;
    massesVBFD[9] = 1500;
    massesVBFD[10] = 1700;
    massesVBFD[11] = 2000;
    massesVBFD[12] = 2500;
    massesVBFD[13] = 3000;
    massesVBFD[14] = 5000;
    massesVBFD[15] = 7500;
    massesVBFD[16] = 10000;
    massesVBFD[17] = 15000;
    massesVBFD[18] = 20000;
    massesVBFD[19] = 25000;


    double vEffPreDY[nDY];
    double vEffPreVBF[nVBF];
    double vEffPreDY2[nDY];
    double vEffPreVBF2[nVBF];

    for(unsigned int i = 0 ; i < MassesDYS.size() ; i++){
      TString path_mass = pathDY + MassesDYS[i] + ".root";
      
      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour +"/ChannelDependant_Inclusive");

      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_SR1");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPreDY[i] = EffPre;
      cout << "DY " << MassesDYS[i] << " Eff = " << EffPre << endl;
    }

    for(unsigned int i = 0 ; i < MassesDYS.size() ; i++){
      TString path_mass = pathDY + MassesDYS[i] + ".root";

      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/MuMu/ChannelDependant_Inclusive");

      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/MuMu/ChannelDependant_SR1");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPreDY2[i] = EffPre;
    }
    

    for(unsigned int i = 0 ; i < MassesVBFS.size() ; i++){
      TString path_mass = pathSSWW + MassesVBFS[i] + ".root";

      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour +"/ChannelDependant_Inclusive");
      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_SR1");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPreVBF[i] = EffPre;
      cout << "SSWW " << massesVBFD[i] << " Eff = " << EffPre << endl;
    }
    for(unsigned int i = 0 ; i < MassesVBFS.size() ; i++){
      TString path_mass = pathSSWW + MassesVBFS[i] + ".root";

      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/MuMu/ChannelDependant_Inclusive");
      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/MuMu/ChannelDependant_SR1");

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      vEffPreVBF2[i] = EffPre;
      cout << "SSWW " << massesVBFD[i] << " Eff = " << EffPre << endl;
    }
    TGraphAsymmErrors *gPreDY = new TGraphAsymmErrors(nDY,MassesDYD , vEffPreDY);
    TGraphAsymmErrors *gPreSSWW = new TGraphAsymmErrors(nVBF,massesVBFD , vEffPreVBF);
    TGraphAsymmErrors *gPreDYMu = new TGraphAsymmErrors(nDY,MassesDYD , vEffPreDY2);
    TGraphAsymmErrors *gPreSSWWMu = new TGraphAsymmErrors(nVBF,massesVBFD , vEffPreVBF2);


    Plotter.draw_SignalEff_canvas(gPreDY,gPreSSWW,gPreDYMu,gPreSSWWMu,  Flavour+"_MuMu_DYEff",year,"HNL_ULID_ID_SR1_"+year);
    
  }
  
  return;
}



