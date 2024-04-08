#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyCFShiftChi2Merged(){

  TString LabelForWeb = "HNL_ChargeFlip_2023_TEST";

  vector<TString> eras =  {"2016a", "2016b", "2017", "2018"};
  vector<TString> EtaBins = {"BB","EE1","EE2"};
  vector<TString> HistStrings = {"_Pt1", "_Pt2" ,"_Pt3", "_Pt4", "_Pt5"};
  vector<TString> ShiftVals = {};

  for (unsigned int ishift = 0 ; ishift < 150; ishift++){
    double shiftEl = 1.05 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  for (auto era : eras){

    TString year = era;
    if(year.Contains("16")) year = "2016";
    vector<TString> IDs = {"POGTight"};//"POGTight","HNL_ULID_"+year , "TopHN","HNTightV2"};
    for(auto ID : IDs){	
      
      for (auto EtaBin : EtaBins){
	
	vector <TGraph*> vgr;
	vector<TString> labels;
	
	HNLPlotter Plotter("HNL_ChargeFlipChi2Merged");
	Plotter.SetupPlotter(era,"","HNL_ChargeFlip");
	Plotter.DoDebug=false;
	Plotter.CopyToWebsite = true;
	
	int ih=0;
	for (auto HistString : HistStrings){
	  ih++;
	  if(EtaBin.Contains("BB") && (ih > 3)) continue;

	  
	  cout << " --> HistString " << HistString << " EtaBin " << EtaBin << " ID " << ID << " Era " << era << endl;
	  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+era+"/Shift/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShift.root";


	  Plotter.XaxisMin  = -1.;
	  Plotter.XaxisMax  = 1.;
	  Plotter.RebinX    = 1;
	  Plotter.Normalise = 1;
	  TH1D *hist_CF             = Plotter.ConstructHist(path,ID + "/EnergyShift/"+EtaBin+HistString+"_CF");

	  vector <double> Arraychi2,ArraykolS;
	  double MaxChi2=0;
	  for(auto ShiftVal : ShiftVals){
	    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID + "/EnergyShift/"+EtaBin+HistString+"_PromptShifted_"+ShiftVal);

	    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2 WW"); 
	    Arraychi2.push_back(chi2);
	    if(chi2 > MaxChi2) MaxChi2=chi2;

	  }
	  
	  double minChi2 = 999999;
	  TString minChi2St="";
	  int ng = Arraychi2.size();
	  double x_1[ng], y_1[ng];
	  
	  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {
	    if(Arraychi2[i]  < minChi2){
	      minChi2 = Arraychi2[i];
	      minChi2St = ShiftVals[i];
	      if(minChi2St.Contains("1p")) minChi2St = "1";
	    }
	    double xi = 1.05 - double(i) * 0.001;
	    x_1[i]  = xi;
	    y_1[i]  = Arraychi2[i]/MaxChi2;
	    //	    cout << " ShiftVals " << ShiftVals[i] << " chi2 = " << Arraychi2[i] <<  " "  << minChi2St << endl;
	  }

	  TGraph *gr1 = new TGraph(ng, x_1,y_1);
	  vgr.push_back(gr1);
	  
	  Plotter.LatexTextLabel_Size=0.025;
	  
	  TString Pt_Eta_Reg = "";
	  if(EtaBin.Contains("BB")){
	    if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 50";
            if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 30 < Pt < 150";
            if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 150 < Pt" ;

	  }
	  else{
	    if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 30";
	    if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 30 < Pt < 50";
	    if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 50 < Pt < 75";
	    if(HistString.Contains("Pt4")) Pt_Eta_Reg+= " 75 < Pt < 100";
	    if(HistString.Contains("Pt5")) Pt_Eta_Reg+= " 100 < Pt ";
	  }	  
	  if(EtaBin.Contains("BB")) Pt_Eta_Reg+= " EB";
	  if(EtaBin.Contains("EE1")) Pt_Eta_Reg+= " EE1";
	  if(EtaBin.Contains("EE2")) Pt_Eta_Reg+= " EE2";
	  labels.push_back(ID +" " +Pt_Eta_Reg + ": MinChi2 = "+minChi2St);

	}
	Plotter.LatexTextLabel_Y=0.95;
	Plotter.Legend_X1=0.2;
	Plotter.Legend_X2=0.6;
	Plotter.Legend_Y1=0.7;
	Plotter.Legend_Y2=0.9;
	Plotter.XAxisTitle="Energy Shift (Prompt -> CF)";
	Plotter.YAxisTitle="min #chi ^{2} [norm]";
	Plotter.LatexTextLabel_X=0.8;
	Plotter.LatexTextLabel_Y=0.9;
	Plotter.Draw_Graph(vgr, labels, era+"_"+ID + "_CF_EnergyShift_Chi2_MERGED_"+EtaBin, LabelForWeb, {"EtaBin : " +EtaBin});
      }
      
    }
  }
  
  return;
}

