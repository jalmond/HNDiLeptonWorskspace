#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void HNL_SignalEfficiencyTight(){

  TString analysername="HNL_SignalEfficiency";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    vector<TString> samples = GetFullSignalList("HNL_SignalEfficiency_"); //{"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};
    
    //vector<TString> samples =  {"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};           
    
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
	
	TString Hist_DenLoose = DirName+LepType+"_ptbinned_"+EtaBin+"_POGLoose";
	TString Hist_HNLID= DirName+LepType+"_ptbinned_"+EtaBin+"_HNL_UL_2017";
	TString Hist_HNLV2= DirName+LepType+"_ptbinned_"+EtaBin+"_HNTightV2";

	if(1){

	  TH1D* hNumL        = GetHist(File_sample,Hist_DenLoose);
	  TH1D* hNumHNLID        = GetHist(File_sample,Hist_HNLID);
	  TH1D* hNumHNLV2        = GetHist(File_sample,Hist_HNLV2);

	  
	  FormatHist(hNumL,1,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");
	  FormatHist(hNumHNLID,1,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");
	  FormatHist(hNumHNLV2,1,-999,10,1000., GetHistColor(3),1, "P_{T} GeV","Events ");

	  
	  double LooseMVAInt = hNumL->Integral(0.,hNumL->GetNbinsX()+1 );
          double HNLInt = hNumHNLID->Integral(0.,hNumHNLID->GetNbinsX()+1 );
	  double HNLV2Int = hNumHNLV2->Integral(0.,hNumHNLV2->GetNbinsX()+1 );

	  
          double EffHNL = 100*HNLInt/LooseMVAInt;
          double EffHNLV2 = 100*HNLV2Int/LooseMVAInt;
	  
          TH1D* hHNLIDR =  GetRatioHist(hNumHNLID,hNumL);
          TH1D* hHNLV2IDR =  GetRatioHist(hNumHNLV2,hNumL);
	  
          TH1D* hHNLCompR =  GetRatioHist(hHNLV2IDR,hHNLIDR);

	  
	  TLegend *legend = MakeLegend(0.7, 0.45, 0.8, 0.7,0.035);
          legend->AddEntry(hNumHNLID,"HNL MVA","l");
	  legend->AddEntry(hNumHNLV2,"HNTightV2 ","l");

	  gPad->Update();
	  
	  //DrawLatex(era);
	  //CMS_lumi(c1,4,0);

	  hHNLV2IDR->SetMaximum(1.05);
	  hHNLV2IDR->SetMinimum(0.5);
	  hHNLV2IDR->GetYaxis()->SetNdivisions(6,5,0);
	  hHNLV2IDR->GetYaxis()->SetTitle("Efficiency ID (vs POG Loose)");

	  hist_axis(hHNLV2IDR);
	  hHNLV2IDR->Draw("hist");
	  
	  hHNLIDR->Draw("histsame");

	  legend->Draw();

	  TString labelV2 = "HNTightV2 Eff. = "+TString(to_string(EffHNLV2))+"%";
	  TString labelMVA = "MVA ID Eff. = "+TString(to_string(EffHNL))+"%";
          DrawLatexWithLabel(era,labelV2,0.65,0.18);
          DrawLatexWithLabel(era,labelMVA,0.65,0.28);

	  c1_down->cd();
	  
	  hist_axis(hHNLV2IDR,hHNLCompR);                                                                                                                                                                            
	  hHNLCompR->Draw("hist");

	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_MVALoose_V2";
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  c1->SaveAs(save_png);
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"TightV3");
	}
	
	
	File_sample->Close();
	delete File_sample;
      }
    }
  }
    
  
  return;
}

