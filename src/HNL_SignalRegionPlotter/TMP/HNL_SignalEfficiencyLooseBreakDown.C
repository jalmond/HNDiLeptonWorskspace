#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void HNL_SignalEfficiencyLooseBreakDown(){

  TString analysername="HNL_SignalEfficiency";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    //vector<TString> samples = GetFullSignalList("HNL_SignalEfficiency_"); //{"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};

    vector<TString> samples =  {"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};           
    
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
	TString Hist_Cut1 = DirName+LepType+"_ptbinned_"+EtaBin+"_MVALooseCut1";
	TString Hist_Cut2 = DirName+LepType+"_ptbinned_"+EtaBin+"_MVALooseCut2";
	TString Hist_Cut3 = DirName+LepType+"_ptbinned_"+EtaBin+"_MVALooseCut3";
	TString Hist_Cut4= DirName+LepType+"_ptbinned_"+EtaBin+"_MVALooseCut4";
	TString Hist_MVALoose= DirName+LepType+"_ptbinned_"+EtaBin+"_MVALoose";
	TString Hist_HNLID= DirName+LepType+"_ptbinned_"+EtaBin+"_HNL_TopMVA_MM";

	if(1){

	  TH1D* hNumL        = GetHist(File_sample,Hist_DenLoose);
	  TH1D* hNumCut1        = GetHist(File_sample,Hist_Cut1);
	  TH1D* hNumCut2        = GetHist(File_sample,Hist_Cut2);
	  TH1D* hNumCut3        = GetHist(File_sample,Hist_Cut3);
	  TH1D* hNumCut4        = GetHist(File_sample,Hist_Cut4);
	  TH1D* hNumMVA        = GetHist(File_sample,Hist_MVALoose);
	  TH1D* hNumHNLID        = GetHist(File_sample,Hist_HNLID);

	  
	  FormatHist(hNumL,1,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");
	  FormatHist(hNumCut1,1,-999,10,1000., GetHistColor(1),1, "P_{T} GeV","Events ");
	  FormatHist(hNumCut2,1,-999,10,1000., GetHistColor(2),1, "P_{T} GeV","Events ");
	  FormatHist(hNumCut3,1,-999,10,1000., GetHistColor(3),1, "P_{T} GeV","Events ");
	  FormatHist(hNumCut4,1,-999,10,1000., GetHistColor(4),1, "P_{T} GeV","Events ");
	  FormatHist(hNumMVA,1,-999,10,1000., GetHistColor(5),9, "P_{T} GeV","Events ");
	  FormatHist(hNumHNLID,1,-999,10,1000., GetHistColor(0),9, "P_{T} GeV","Events ");

	  
	  double LooseMVAInt = hNumL->Integral(0.,hNumL->GetNbinsX()+1 );
	  double MVAInt = hNumMVA->Integral(0.,hNumMVA->GetNbinsX()+1 );
          double HNLInt = hNumHNLID->Integral(0.,hNumHNLID->GetNbinsX()+1 );
	  
	  double EffMedium = 100*MVAInt/LooseMVAInt;
          double EffHNL = 100*HNLInt/LooseMVAInt;
	  
	  TH1D* hCut1 =  GetRatioHist(hNumCut1,hNumL);
          TH1D* hCut2 =  GetRatioHist(hNumCut2,hNumL);
          TH1D* hCut3 =  GetRatioHist(hNumCut3,hNumL);
          TH1D* hCut4 =  GetRatioHist(hNumCut4,hNumL);
          TH1D* hMediumR =  GetRatioHist(hNumMVA,hNumL);
          TH1D* hHNLIDR =  GetRatioHist(hNumHNLID,hNumL);

	  
	  TLegend *legend = MakeLegend(0.7, 0.45, 0.8, 0.7,0.035);
	  legend->AddEntry(hNumL,"POG Loose","l");
	  legend->AddEntry(hNumCut1,"Loose+Iso","l");
	  legend->AddEntry(hNumCut2,"Loose+SIP","l");
	  legend->AddEntry(hNumCut3,"Loose+DXY","l");
	  legend->AddEntry(hNumCut4,"Loose+DZ","l");
	  legend->AddEntry(hNumMVA,"MVA+Medium","l");
          legend->AddEntry(hNumHNLID,"HNL MVA","l");

	  gPad->Update();
	  
	  //DrawLatex(era);
	  //CMS_lumi(c1,4,0);



	  hMediumR->SetMaximum(1.05);
	  hMediumR->SetMinimum(0.5);
	  hMediumR->GetYaxis()->SetNdivisions(6,5,0);
	  hMediumR->GetYaxis()->SetTitle("Efficiency ID (vs POG Loose)");

	  hist_axis(hMediumR);
	  hMediumR->Draw("hist");
	  
	  hCut1->Draw("histsame");
	  hCut2->Draw("histsame");
	  hCut3->Draw("histsame");
	  hCut4->Draw("histsame");
	  hHNLIDR->Draw("histsame");

	  legend->Draw();

	  TString labelMedium = "Medium Eff. = "+TString(to_string(EffMedium))+"%";
	  TString labelMVA = "MVA ID Eff. = "+TString(to_string(EffHNL))+"%";
          DrawLatexWithLabel(era,labelMedium,0.25,0.68);
          DrawLatexWithLabel(era,labelMVA,0.25,0.58);

	  c1_down->cd();
	  
	  hist_axis(hMediumR,hNumL);                                                                                                                                                                            
          hNumL->Draw("hist");
          hNumCut1->Draw("histsame");
          hNumCut2->Draw("histsame");
          hNumCut3->Draw("histsame");
          hNumCut4->Draw("histsame");
          hNumMVA->Draw("histsame");
	  hNumHNLID->Draw("histsame");

	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_MVALoose_Breakdown";
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  c1->SaveAs(save_png);
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"BreakDown");
	}
	
	
	File_sample->Close();
	delete File_sample;
      }
    }
  }
    
  
  return;
}

