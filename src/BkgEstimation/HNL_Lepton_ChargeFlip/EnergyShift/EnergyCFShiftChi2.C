#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void EnergyCFShiftChi2(){

  TString LabelForWeb = "HNL_ChargeFlip_2023_TEST";

  vector<TString> eras =  {"2018"};//, "2016b", "2017", "2018"};
  vector<TString> EtaBins = {"BB","EE1","EE2"};
  vector<TString> HistStrings = {"_Pt1", "_Pt2" ,"_Pt3", "_Pt4", "_Pt5"};
  vector<TString> ShiftVals = {};

  for (unsigned int ishift = 0 ; ishift < 15; ishift++){
    double shiftEl = 1.05 - double(ishift)*0.01;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  vector<TString> IDs = {"POGTight"};//, "HNTightV2"};
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      int ih=0;
      for (auto HistString : HistStrings){
	ih++;
	if(EtaBin.Contains("BB") && (ih > 3)) continue;
	

	vector <TGraph*> vgr;
	vector<TString> labels;
	
	HNLPlotter Plotter("HNL_ChargeFlipChi2");
	Plotter.SetupPlotter(year,"","HNL_ChargeFlip");
	Plotter.DoDebug=false;
	Plotter.CopyToWebsite = true;
	
	TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ChargeFlip/"+year+"/Shift/HNL_ChargeFlip_SkimTree_DileptonBDT_MCShift.root";

	for(auto ID : IDs){	
	  
	  TH1D *hist_CF             = Plotter.ConstructHist(path,ID + "/EnergyShift/"+EtaBin+HistString+"_CF");
	  hist_CF->Scale(1./hist_CF->Integral());
	  //	  hist_CF->Rebin(4);
	  //hist_CF->GetXaxis()->SetRangeUser(-0.2, 0.2);
	  vector <double> Arraychi2,ArraykolS;
	  
	  for(auto ShiftVal : ShiftVals){
	    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID + "/EnergyShift/"+EtaBin+HistString+"_PromptShifted_"+ShiftVal);
	    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());
	    //hist_PromptScaled->Rebin(4);
	    //	    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2, 0.2);
	    
	    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2"); 
	    Arraychi2.push_back(chi2);
	  }
	  
	  double minChi2 = 999999;
	  TString minChi2St="";
	  int ng = Arraychi2.size();
	  double x_1[ng], y_1[ng];
	  
	  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {
	    if(Arraychi2[i]  < minChi2){
	      minChi2 = Arraychi2[i];
	      minChi2St = ShiftVals[i];
	    }
	    double xi = 1.05 - double(i) * 0.01;
	    x_1[i]  = xi;
	    y_1[i]  = Arraychi2[i];
	    //	    cout << " ShiftVals " << ShiftVals[i] << " chi2 = " << Arraychi2[i] << endl;
	  }
	  
	  TGraph *gr1 = new TGraph(ng, x_1,y_1);
	  vgr.push_back(gr1);
	  labels.push_back(ID + ": MinChi2 = "+minChi2St);
	  cout << ID + "/EnergyShift/"+EtaBin+HistString + " Min chi2 = " << minChi2St << " " << minChi2 << endl;
	}
	
	Plotter.LatexTextLabel_Size=0.025;
	TString Pt_Eta_Reg = "";
	if(EtaBin.Contains("BB")){
	  if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 50";
          if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 50 < Pt < 200";
          if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 200 < Pt ";

	}
	else{
	  if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 30";
	  if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 30 < Pt < 50";
	  if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 50 < Pt < 75";
	  if(HistString.Contains("Pt4")) Pt_Eta_Reg+= " 75 < Pt < 100";
	  if(HistString.Contains("Pt5")) Pt_Eta_Reg+= " 100 < Pt ";
	}
	if(EtaBin.Contains("BB")) Pt_Eta_Reg+= " BB";
	if(EtaBin.Contains("EE1")) Pt_Eta_Reg+= " EE1";
	if(EtaBin.Contains("EE2")) Pt_Eta_Reg+= " EE2";
	//	labels.push_back(Pt_Eta_Reg);
	Plotter.LatexTextLabel_Y=0.95;
	Plotter.Draw_Graph(vgr, {Pt_Eta_Reg}, IDs[0]+"_CF_EnergyShift_Chi2"+HistString+"_"+EtaBin, LabelForWeb, labels);
	
      }
    }
  }
  
  return;
}

