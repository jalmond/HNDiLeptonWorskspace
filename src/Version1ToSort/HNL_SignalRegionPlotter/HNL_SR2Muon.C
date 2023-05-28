#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void HNL_SR2Muon(){

  TString analysername="HNL_SignalRegionPlotter";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    TString histname="HToLepPt1";                                                                                                    
    
    TString Histname="MuMu/MVAUL_UL/RegionPlots_PassSR2/"+histname;

    TString canvasname= Histname;
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800)    ;
    canvas_margin(c1);
    c1->cd();
    
    TString pre="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_SignalRegionPlotter/";
    TFile* File_sampleNP = GetFile(pre+"/"+era+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_NonPrompt.root");
    TFile* File_sampleConv = GetFile(pre+"/"+era+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Conv.root");
    TFile* File_samplePrompt = GetFile(pre+"/"+era+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Prompt.root");
    
	
    TH1D* hNP       = GetHist(File_sampleNP,Histname);
    TH1D* hConv       = GetHist(File_sampleConv,Histname);
    TH1D* hPrompt       = GetHist(File_samplePrompt,Histname);
    
    TFile* File_sampleBkg = GetFile(pre+"/"+era+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Bkg.root");
    TFile* File_sampleSignal1000 = GetFile(pre+"/"+era+"/SIGMerged/HNL_SignalRegionPlotter_Type1_SS_M1000.root");
    
    TH1D* hBkg       = GetHist(File_sampleBkg,Histname);

    TH1D* hSig1000       = GetHist(File_sampleSignal1000,Histname);
    
    FormatHist(hBkg,5,-999,0,10.,0,1, "H_{T}/P_{T}","Events / Bin ");
    hBkg->SetLineColor(kRed);
    hBkg->SetLineWidth(2);
    hBkg->SetFillColor(kOrange);
    hBkg->SetFillStyle(3354);
    
    FormatHist(hSig1000,5,-999, 0,10., GetHistColor(0),9, "P_{T} GeV","Events / GeV");

    TLegend *legend = MakeLegend(0.6, 0.55, 0.8, 0.7,0.025);
    legend->AddEntry(hBkg,"SS Bkg.","f");
    legend->AddEntry(hSig1000,"Signal (m_{N}=1 TeV |V|=0.1)","l");
    
    gPad->Update();
    
    //DrawLatex(era);
    //CMS_lumi(c1,4,0);
    
    hBkg->GetYaxis()->SetRangeUser(0., 20.);
    hBkg->Draw("hist");

    hSig1000->Scale(0.1);
    hSig1000->Draw("histsame");

    legend->Draw();

    TString label = "SR2 Muon Channel";
    DrawLatexWithLabel(era,label,0.65,0.88);
    gPad->Update();

    
    TString outpath = output + "/"+era+histname;

    TString save_pdf= outpath+".pdf";
    TString save_png= outpath+".png";
    
    c1->SaveAs(save_png);
    c1->SaveAs(save_pdf);
    
    SaveAndCopyLXPLUS(c1,outpath,analysername,"SR2MuMu");
    
    
  }
    
  
  return;
}

