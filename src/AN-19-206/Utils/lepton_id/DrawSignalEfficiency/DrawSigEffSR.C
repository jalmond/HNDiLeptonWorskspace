#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString filepath);

void DrawSigEff(){
  
  DrawConfig("May12","MuMu","2016preVFP", "DY");
  DrawConfig("May12","MuMu","2016postVFP", "DY");
  DrawConfig("May12","MuMu","2017", "DY");
  DrawConfig("May12","MuMu","2018","DY");

}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString filepath){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter("SignalIDEfficiency");
    Plotter.SetupPlotter(year,"",Flavour+"_ID_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";

    TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+era+"/SIG/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DY_MN";
    //vector<double> MassesD = {100,200,500,1000,2000};

    vector<TString> MassesS = {"85","90", "95","100", "125", "150","200", "250","1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};

    //TH1D* h_eff_DY =  new TH1D ("h_"+flavour+"eff","h_"+flavour+"eff",MassesD.size(),0,double(MassesD.size()));

    TString ID = "HNL_ULID";

    double massesD[24];
    massesD[0] = 85;
    massesD[1] = 90;
    massesD[2] = 95;
    massesD[3] = 100;
    massesD[4] = 125;
    massesD[5] = 150;
    massesD[6] = 200;
    massesD[7] = 250;
    massesD[8] = 300;
    massesD[9] = 400;
    massesD[10] = 500;
    massesD[11] = 600;
    massesD[12] = 700;
    massesD[13] = 800;
    massesD[14] = 950;
    massesD[15] = 1000;
    massesD[16] = 1100;
    massesD[17] = 1200;
    massesD[18] = 1300;
    massesD[19] = 1500;
    massesD[20] = 1700;
    massesD[21] = 2000;
    massesD[22] = 2000;
    massesD[23] = 3000;

    double vEffSR1[24];
    double vEffSR2[24];
    double vEffSR3[24];
    double vEffPre[24];
    for(unsigned int i = 0 ; i < MassesS.size() ; i++){
      TString path_mass = path + MassesS[i] + ".root";
      cout << "path_mass = " << path_mass << endl;
      TH1D *hist_Denom       = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour +"/ChannelDependant_Inclusive");
      cout << hist_Denom << endl;

      TH1D *hist_NumPresel     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_Presel");
      
      TH1D *hist_NumSR1     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_SR1");
      cout << hist_NumSR1 << endl;

      TH1D *hist_NumSR2     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_SR2");
      cout << hist_NumSR2 << endl;


      TH1D *hist_NumSR3     = Plotter.ConstructHist(path_mass,"ChannelCutFlow/"+ID+"/"+Flavour+"/ChannelDependant_SR3_BDT");
      cout << hist_NumSR3 << endl;
      cout << "ChannelCutFlow/"+ID+"/"+Flavour +"/ChannelDependant_Inclusive" << endl;
      cout << hist_Denom->Integral() << endl;

      double EffPre = (hist_NumPresel) ?  100*hist_NumPresel->Integral() / hist_Denom->Integral() : 0;
      double EffSR1 = (hist_NumSR1) ?  100*hist_NumSR1->Integral() / hist_Denom->Integral() : 0;
      double EffSR2 = (hist_NumSR2) ?   100*hist_NumSR2->Integral() / hist_Denom->Integral() : 0;
      double EffSR3 = (hist_NumSR3) ?   100*hist_NumSR3->Integral() / hist_Denom->Integral() : 0;
      cout << EffSR1 << endl;
      vEffPre[i] = EffPre;
      vEffSR1[i] = EffSR1;
      vEffSR2[i] = EffSR2;
      vEffSR3[i] = EffSR3;
    }
    
    TGraphAsymmErrors *gPre = new TGraphAsymmErrors(5,massesD , vEffPre);
    TGraphAsymmErrors *gSR1 = new TGraphAsymmErrors(5,massesD , vEffSR1);
    TGraphAsymmErrors *gSR2 = new TGraphAsymmErrors(5,massesD , vEffSR2);
    TGraphAsymmErrors *gSR3 = new TGraphAsymmErrors(5,massesD , vEffSR3);

    Plotter.draw_SignalEff_canvas(gSR1,gSR2,gSR3,  Flavour+"_DYEff",year,"DY_"+year);
    
  }
  
  return;
}



