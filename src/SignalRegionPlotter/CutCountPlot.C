#include "Riostream.h"
#include "TGraph.h"
#include <vector>


#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"

#include "TString.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
void setTDRStyle();
bool IsPathExist(const std::string &s);

void CutCountPlot(){

  setTDRStyle();
  TString input_path="/Users/john/Type1/MergedFiles/";
  // input_path="/data6/Users/jalmond/SKFlatOutput//Run2Legacy_v4/"
  // Make S  B binned plots

  vector <TString> samples;

  samples.push_back("100");
  samples.push_back("200");
  //samples.push_back("300");
  samples.push_back("400");
  //samples.push_back("500");
  samples.push_back("600");
  samples.push_back("700");
  samples.push_back("800");
  samples.push_back("900");
  samples.push_back("1000");
  samples.push_back("1100");
  samples.push_back("1200");
  samples.push_back("1500");

  vector<TString> masses = samples;
  vector<TString> SR;
  SR.push_back("SR1");
  SR.push_back("SR2");
  SR.push_back("SR3");
  SR.push_back("SR4");

  vector<TString> Years;
  Years.push_back("2016");
  Years.push_back("2017");
  Years.push_back("2018");
  vector <TString> channel;
  channel.push_back("MuMu");
  channel.push_back("EE");
  vector<TString> muIDs;
  muIDs.push_back("HNTightV1");
  muIDs.push_back("HNTightV2");
  muIDs.push_back("POGTightWithTightIso");

  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");
  for(unsigned int y = 0 ; y < Years.size(); ++y){
   for(unsigned int j = 0 ; j < SR.size(); ++j){
    for(unsigned int k = 0 ; k < channel.size(); ++k){

      TString channel_lab = "MuMu";
      if ( channel[k].Contains("EE") ) channel_lab = "EE";

      TString _y = Years[y];
      
      vector<TString> IDs;
      if ( channel[k].Contains("EE") ) IDs = elIDs;
      else IDs =   muIDs;

      for(unsigned int l = 0 ; l < IDs.size(); l++){
        TString ID = IDs[l];
        TString _sr = SR[j];
        TString sign = "same_sign";
        TString _sign = "Signal__";
        if(_sr == "SR3") { _sr = "SR1"; sign = "opposite_sign"; _sign = "SignalOS__"; }
        if(_sr == "SR4") { _sr = "SR2"; sign= "opposite_sign"; _sign = "SignalOS__";}

	sign = "_"+sign;
	
	TString label_h = _y+_sr+"_"+channel_lab +"_highmass"+sign +"_nevent_HNtypeI_JA_"+channel_lab+"_" + ID;
	TH1D* this_hist_sig = new TH1D(label_h+"SIG" , label_h+"SIG", masses.size(), 0, masses.size());

	TH1D* this_hist_prompt = new TH1D(label_h+"P" , label_h+"P", masses.size(), 0, masses.size());
	TH1D* this_hist_cf = new TH1D(label_h +"C", label_h+"C", masses.size(), 0, masses.size());
	TH1D* this_hist_fake = new TH1D(label_h +"F", label_h+"F", masses.size(), 0, masses.size());
	
	
	for(unsigned int i = 0 ; i < masses.size(); ++i){
	  
          TString im = samples.at(i);
          this_hist_sig->GetXaxis()->SetBinLabel(i+1,im);
        }

	

	
	TString path16= input_path+"/2016/SIG/";
	TString path= input_path+_y ;
	TFile * file_s = new TFile((path16+"/HNtypeI_JA_HN_Schannel_"+channel[k]+"_100_nlo.root").Data());
	TFile * file_c = new TFile((path16+"/HNtypeI_JA_HN_Combinedchannel_"+channel[k]+"_100_nlo.root").Data());
	TFile * file_prompt = new TFile((path+"/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root").Data());
	TFile * file_cf = new TFile((path+"/HNtypeI_JA_SkimTree_SSNonIso_CF.root").Data());
	TString fake_s="HNtypeI_JA_SkimTree_SSNonIso_FakeMM.root";
	if ( channel[k].Contains("EE") ) fake_s="HNtypeI_JA_SkimTree_SSNonIso_FakeEE.root";

	cout << "Signal : " << path16+"/HNtypeI_JA_HN_Schannel_"+channel[k]+"_100_nlo.root" << endl;
	cout << "Fake : " << path+"/"+fake_s << endl;
	cout << "Prompt : " << path+"/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root" << endl;
	TFile * file_fake = new TFile((path+"/"+fake_s).Data());
	  
	for(unsigned int i = 0 ; i < masses.size(); ++i){

	  TString im = samples.at(i);	
	  TString histname =  _sr + "_"+channel_lab + "_mn"+im+sign+"/"+_sr+"_"+channel_lab +"_mn"+im+sign +"_nevent_HNtypeI_JA_"+channel_lab+"_" + ID +"_";
	  
	  cout << histname << endl;
	  TH1* h_nsig =   (TH1F*)file_s->Get((histname));
	  TH1* h_nprompt =   (TH1F*)file_prompt->Get((histname));
	  TH1* h_ncf =   (TH1F*)file_cf->Get((histname));
	  TH1* h_nfake =   (TH1F*)file_fake->Get((histname));
	  if (h_ncf) 	    this_hist_cf->Fill(im, h_ncf->Integral());
	  if(h_nsig)this_hist_sig->Fill(im, h_nsig->Integral());
	  if(h_nprompt)this_hist_prompt->Fill(im, h_nprompt->Integral());
	  
	  if(h_nfake)this_hist_fake->Fill(im, h_nfake->Integral());
	  if(h_nsig)cout << h_nsig->Integral() << endl;
	  if(h_nprompt)cout << h_nprompt->Integral() << endl;
	  if(h_nfake)cout << h_nfake->Integral() << endl;
	}
	
	
	//=== Draw canvas                   
	
	unsigned int outputWidth = 1200;
	unsigned int outputHeight = 1200;
	
	
	TCanvas* c1 = new TCanvas((_y+_sr+"_"+channel_lab +"_highmass"+sign +"_nevent_HNtypeI_JA_"+channel_lab+"_" + ID), _sr+"_"+channel_lab +"_highmass"+sign +"_nevent_HNtypeI_JA_"+channel_lab+"_" + ID, outputWidth,outputHeight);
	
	c1->cd();
	gPad->SetLogz(1);
	
	
	
	this_hist_sig->SetLineColor(kBlack);
	this_hist_sig->SetLineWidth(2.);
	this_hist_prompt->SetFillColor(kGreen);
	this_hist_fake->SetFillColor(870);
	this_hist_cf->SetFillColor(kCyan);
	
	THStack *hs = new THStack(_sr+"_"+channel_lab +"_highmass"+sign +"_nevent_HNtypeI_JA_"+channel_lab+"_" + ID,"");
	hs->Add(this_hist_prompt);
	hs->Add(this_hist_fake);
	hs->Add(this_hist_cf);

	TLegend* legendH;
	legendH = new TLegend(0.25, 0.8, 0.5, 0.95);
	legendH->SetFillColor(kWhite);
	legendH->SetTextSize(0.03);
	legendH->SetBorderSize(0);
	legendH->SetTextFont(42);

	
	legendH->AddEntry(this_hist_sig, "m_{N} = 100 GeV","l");
	legendH->AddEntry(this_hist_prompt,"Prompt","f");
	legendH->AddEntry(this_hist_cf,"Charge Flip","f");
	legendH->AddEntry(this_hist_fake,"Fake","f");
	legendH->Draw();
	this_hist_sig->GetYaxis()->SetRangeUser(0., this_hist_prompt->GetMaximum()*1.2);
	this_hist_sig->Draw("hist");
	hs->Draw("histsame");
	
	//	if(!IsPathExist(str"Plots/"+_sr))  gSystem->mkdir("Plots/"+_sr);
	
	//system("mkdir Plots/)
	c1->SaveAs("Plots/"+_y+"/"+ channel_lab + "/" + _sr +  "/"+ID +"_SignalBackground.pdf");
	
      }// IDsq
    }
   }
  }
}



void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);

  tdrStyle->SetEndErrorSize(2);
  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);
  
  //For the date:
  
  //For the fit/function:
tdrStyle->SetOptFit(1);
 tdrStyle->SetFitFormat("5.4g");
tdrStyle->SetFuncColor(2);
tdrStyle->SetFuncStyle(1);
tdrStyle->SetFuncWidth(1);

//For the date:
tdrStyle->SetOptDate(0);

// For the statistics box:
tdrStyle->SetOptFile(0);
tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
tdrStyle->SetStatColor(kWhite);
tdrStyle->SetStatFont(42);
tdrStyle->SetStatFontSize(0.025);
tdrStyle->SetStatTextColor(1);
tdrStyle->SetStatFormat("6.4g");
tdrStyle->SetStatBorderSize(1);
tdrStyle->SetStatH(0.1);
tdrStyle->SetStatW(0.15);

// Margins:
tdrStyle->SetPadTopMargin(0.05);
tdrStyle->SetPadBottomMargin(0.1);
tdrStyle->SetPadLeftMargin(0.14);
tdrStyle->SetPadRightMargin(0.04);

// For the Global title:

tdrStyle->SetOptTitle(0);
tdrStyle->SetTitleFont(42);
tdrStyle->SetTitleColor(1);
tdrStyle->SetTitleTextColor(1);
tdrStyle->SetTitleFillColor(10);
tdrStyle->SetTitleFontSize(0.05);

// For the axis titles:
tdrStyle->SetTitleColor(1, "XYZ");
tdrStyle->SetTitleFont(42, "XYZ");
tdrStyle->SetTitleSize(0.05, "XYZ");
tdrStyle->SetTitleXOffset(0.8);
tdrStyle->SetTitleYOffset(1.25);

// For the axis labels:
tdrStyle->SetLabelColor(1, "XYZ");
tdrStyle->SetLabelFont(42, "XYZ");
tdrStyle->SetLabelOffset(0.007, "XYZ");
tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:
tdrStyle->SetAxisColor(1, "XYZ");
tdrStyle->SetStripDecimals(kTRUE);
tdrStyle->SetTickLength(0.03, "XYZ");
tdrStyle->SetNdivisions(510, "XYZ");
tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
tdrStyle->SetPadTickY(1);

// Change for log plots:
tdrStyle->SetOptLogx(0);
tdrStyle->SetOptLogy(0);
tdrStyle->SetOptLogz(0);

// Postscript options:
tdrStyle->SetPaperSize(20.,20.);

tdrStyle->SetHatchesLineWidth(5);
tdrStyle->SetHatchesSpacing(0.05);

tdrStyle->cd();



}
