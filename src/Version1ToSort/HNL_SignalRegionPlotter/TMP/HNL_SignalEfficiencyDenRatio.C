#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void HNL_SignalEfficiencyDenRatio(){

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
	c1->Draw();
	c1->cd();
	

	TPad *c1_up;
	TPad *c1_down;
	c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
	c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

	canvas_margin(c1, c1_up, c1_down);

	c1_up->Draw();
	c1_down->Draw();
	c1_up->cd();


	TFile* File_sample = GetFile("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+sample+".root");
	
	TString LepType = "Muon";
	TString DirName="SignalRecoMuMu/";
	
	TString Hist_Den = DirName+LepType+"_pt_"+EtaBin+"_NoCut";
	TString Hist_DenLoose = DirName+LepType+"_pt_"+EtaBin+"_POGLoose";
	TString Hist_DenMedium = DirName+LepType+"_pt_"+EtaBin+"_POGMedium";
	TString Hist_DenMVA = DirName+LepType+"_pt_"+EtaBin+"_MV";

	TH1D* hDen        = GetHist(File_sample,Hist_Den);
	hDen->GetXaxis();
	//hist_axis(hDen);
	TH1D* hNumL        = GetHist(File_sample,Hist_DenLoose);
	TH1D* hNumM        = GetHist(File_sample,Hist_DenMedium);
	TH1D* hNumMVA        = GetHist(File_sample,Hist_DenMVA);
	//hist_axis(hNumL);
	//hist_axis(hNumM);
	
	if(1){
	  
	  
	  FormatHist(hDen,2,-999,10,1000., kBlue,1, "P_{T} GeV","Events ");
	  FormatHist(hNumL,2,-999,10,1000., kRed,1, "P_{T} GeV","Events ");
	  FormatHist(hNumM,2,-999,10,1000., kBlack,1, "P_{T} GeV","Events ");
	  
	  hDen->Draw("hist");
	  hNumL->Draw("histsame");
	  hNumM->Draw("histsame");
	  
	  double LooseMVAInt = hNumL->Integral(0.,hNumL->GetNbinsX()+1 );
	  double MediumMVAInt = hNumM->Integral(0.,hNumM->GetNbinsX()+1 );

	  double EffMedium = MediumMVAInt/LooseMVAInt;
	  
	  TLegend *legend = MakeLegend(0.7, 0.55, 0.8, 0.75,0.03);
	  legend->AddEntry(hDen,"All leptons","l");
	  legend->AddEntry(hNumL,"POG Loose","l");
	  legend->AddEntry(hNumM,"POG Medium","l");
	  legend->Draw();
	  gPad->Update();
	  
	  //DrawLatex(era);
	  TString label = "Medium Eff. = "+TString(to_string(EffMedium));
	  DrawLatexWithLabel(era,label,0.25,0.68);
	  //CMS_lumi(c1,4,0);

	  c1_down->cd();
	  
          TH1D* hLooseR =  GetRatioHist(hNumL,hDen);
          TH1D* hMediomR =  GetRatioHist(hNumM,hNumL);

	  hLooseR->SetMaximum(1.5);
	  hLooseR->SetMinimum(0.5);
	  hLooseR->GetYaxis()->SetNdivisions(6,5,0);
	  hLooseR->GetYaxis()->SetTitle("#frac{IDCut}{NoID}");

	  hLooseR->Draw("hist");
	  hist_axis(hDen,hLooseR);
	  
	  hMediomR->Draw("histsame");

	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_MVALoose_AllLeptonPt";
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  //c1->SetLogx();                                                                                                                                                                                                                                                        
	  
	  cout << " Saving 1" << endl;
	  c1->SaveAs(save_png);
	  cout << " Saving 2" << endl;
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"DenFixedRatio");
	}
	
	
	File_sample->Close();
	delete File_sample;
      }
    }
  }
    
  
  return;
}

