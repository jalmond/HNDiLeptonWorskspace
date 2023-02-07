#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"


void HNL_SignalEfficiencyDen(){

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
	
	TCanvas* c1 = MakeCanvas("",sample+"_"+EtaBin);
	canvas_margin(c1);
	TString canvasname= sample+"_"+EtaBin;

	//TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	TFile* File_sample = GetFile("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+sample+".root");
	
	TString LepType = "Muon";
	TString DirName="SignalRecoMuMu/";
	
	TString Hist_Den = DirName+LepType+"_pt_"+EtaBin+"_NoCut";
	TString Hist_DenLoose = DirName+LepType+"_pt_"+EtaBin+"_POGLoose";
	TString Hist_DenMedium = DirName+LepType+"_pt_"+EtaBin+"_POGMedium";
      
	TH1D* hDen        = GetHist(File_sample,Hist_Den);
	//hist_axis(hDen);
	TH1D* hDenL        = GetHist(File_sample,Hist_DenLoose);
	TH1D* hDenM        = GetHist(File_sample,Hist_DenMedium);
	
	
	if(1){
	  
	  
	  FormatHist(hDen,1,-999,10,1000., kBlue,1, "P_{T} GeV","Events ");
	  FormatHist(hDenL,1,-999,10,1000., kRed,1, "P_{T} GeV","Events ");
	  FormatHist(hDenM,1,-999,10,1000., kCyan,1, "P_{T} GeV","Events ");
	  
	  hDen->Draw("histE");
	  hDenL->Draw("histsame");
	  hDenM->Draw("histsame");
	  
	  TLegend *legend = MakeLegend(0.7, 0.55, 0.8, 0.75,0.03);
	  legend->AddEntry(hDen,"All leptons","l");
	  legend->AddEntry(hDenL,"POG Loose","l");
	  legend->AddEntry(hDenM,"POG Medium","l");
	  legend->Draw();
	  gPad->Update();
	  
	  DrawLatex(era);

	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_MVALoose_AllLeptonPt";
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  //c1->SetLogx();                                                                                                                                                                                                                                                        
	  
	  cout << " Saving 1" << endl;
	  c1->SaveAs(save_png);
	  cout << " Saving 2" << endl;
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"Den");
	}
	
	
	File_sample->Close();
	delete File_sample;
      }
    }
  }
    
  
  return;
}

