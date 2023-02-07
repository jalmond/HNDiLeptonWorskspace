
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"


void HNL_SignalEfficiencyLoose(){

  TString analysername="HNL_SignalEfficiency";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){
    
    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    vector<TString> samples = {"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};
    
    
    for(auto sample : samples){
    
      vector<TString> EtaBins = {"BB","EB","EE"};
  
      for( auto EtaBin: EtaBins){
	
	//TCanvas* c1 = MakeCanvas("",sample);
	TString canvasname= sample+"_"+EtaBin;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	TFile* File_sample = GetFile("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+sample+".root");
	
	TString LepType = "Muon";
	TString DirName="SignalRecoMuMu/";
	
	TString Hist_Den = DirName+LepType+"_pt_"+EtaBin+"_NoCut";
	TString Hist_MVALoose = DirName+LepType+"_pt_"+EtaBin+"_MVALoose";
	TString Hist_M = DirName+LepType+"_pt_"+EtaBin+"_POGMedium";

      
	TH1D* hDen        = GetHist(File_sample,Hist_Den);
	TH1D* hNum        = GetHist(File_sample,Hist_MVALoose);
	TH1D* hNum2        = GetHist(File_sample,Hist_M);
	
	
	
	if(1){
	  
	  TH1D* hNumRLoose =  GetRatioHist(hNum,hDen);
	  TH1D* hNumR =  GetRatioHist(hNum2,hDen);

	  FormatHist(hNumR,1,-999,10,1000., kBlue,1, "P_{T} GeV",LepType +" Efficiency [%]");
	  FormatHist(hNumRLoose,1,-999,10,1000., kBlack,1, "P_{T} GeV",LepType +" Efficiency [%]");

	  hNumR->Draw("histE");
	  hNumRLoose->Draw("histsame");
	  
	  TLegend *legend = MakeLegend(0.6, 0.25, 0.7, 0.45,0.03);
	  legend->AddEntry(hNumR,"Eff. HNL_POGMedium","l");
	  legend->AddEntry(hNumRLoose,"Eff. LooseMVA","l");

	  legend->Draw();
	  gPad->Update();
	  
	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_MVALoose_efficiency";
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  c1->SetLogx();                                                                                                                                                                                                                                                        
	  
	  cout << " Saving 1" << endl;
	  c1->SaveAs(save_png);
	  cout << " Saving 2" << endl;
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"MVALoose");
	}
	
	
	File_sample->Close();
	delete File_sample;
      }
    }
  }
    
  
  return;
}

