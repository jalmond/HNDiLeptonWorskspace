#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TLatex.h"
#include "TKey.h"
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include "TString.h"
#include "TSystem.h"

#include <sstream>      // std::stringstream

void setTDRStyle();
bool CheckFile(TFile* f);
bool CheckHist(TH2* h);


void MakeFRFileEE_pt(TString year,TString dataset="Electron"){

  
  TString path= "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/"+year+"/FakeRateHN_SkimTree_HNFake_"+dataset+".root";
  TString mcpath= "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/"+year+"/FakeRateHN_SkimTree_HNFake_MC.root";
  
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "FakeRate13TeV_pt_el_"+year+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> jetpt = {"40","30","20"};

  std::vector<TString> fakes40;

  //  fakes40.push_back("passMVAID_noIso_WP90V16");
  //  fakes40.push_back("passPOGTight_TTrig_HNTC");

  fakes40.push_back("HNTightV1");
  fakes40.push_back("HNTight2016");
  fakes40.push_back("HN2016");
  fakes40.push_back("HN2016RelaxedIP");
  fakes40.push_back("HN2017");
  fakes40.push_back("HN2017RelaxedIP");
  fakes40.push_back("HN2018");
  fakes40.push_back("HN2018RelaxedIP");
  
  /*
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNMediumV1
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNMediumV2
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNMediumV3
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNTight2016
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNTightV1
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNTightV2
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNTightV3
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_HNTightV4
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passMVAID_iso_WP80
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passMVAID_iso_WP90
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passMVAID_noIso_WP80
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passMVAID_noIso_WP90
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passMediumID
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passTightID
hadd Target path: /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/FakeRateHN/2018/FakeRateHN_SkimTree_HNFake_MC.root:/SingleTightElJet_matched_passTightID_nocc

   */

  double ptbinscone[10] = { 6.,10., 15.,20.,30.,40.,50.,  60., 100.,200.};
  
  //Float_t ptbinscone[9] = { 10., 15.,20.,30.,40.,50.,  60., 200.};
  Float_t etabins2[5] = { 0.,0.8,  1.479, 2.,  2.5};

  //  Float_t etabins[4] = {0., 0.8, 1.5, 2.5};
  //TH2D* h = new TH2D("SS_auxFake_etaptcone","SS_auxFake_etaptcone", 7., ptbinscone, 4 , etabins2);
  //TH1D* h1 = new TH1D("SS_auxFake_eatcone","SS_auxFake_ptcone", 4 , etabins2);
  //TH1D* h2 = new TH1D("SS_auxFake_ptcone","SS_auxFake_ptcone", 7., ptbinscone);

  
  for(unsigned int i=0; i < fakes40.size(); i++){

    for(auto j : jetpt){
      
      
      TString denom = "LooseElFakeRateHN_EE_" +fakes40[i] +"_"+j+"_pt_eta";
      TString num   = "TightElFakeRateHN_EE_" +fakes40[i] +"_"+j+"_pt_eta";

      //    return;
      TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
      TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());
      TH2D* h_mcpt_num= (TH2D*)fmc->Get(num.Data());
      TH2D* h_mcpt_denom= (TH2D*)fmc->Get(denom.Data());
      
      CheckHist(h_pt_denom);
      CheckHist(h_pt_num);
      TString name = fakes40[i] ;
      
      TH2D* eff_rate = (TH2D*)h_pt_num->Clone((name+"_pt_AwayJetPt"+j).Data());
      eff_rate->Add(h_mcpt_num,-1.);
      TH2D* hratedenom = (TH2D*)h_pt_denom->Clone((name +"_denom").Data());
      hratedenom->Add(h_mcpt_denom,-1.);
      
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      
      eff_rate->Write();

    }
  }
  
  return;
}
  
  
  
bool CheckFile(TFile* f ){
    bool file_exist = true;
    if(!f){
      cout << "File " << f->GetName() << " does not exist. Exiting " << endl;
      file_exist = false;
    }
    
    return file_exist;
}

bool CheckHist(TH2* h ){
  bool hist_exist = true;
  if(!h){
    cout << "No histogram with name " << h->GetName() << endl;
    hist_exist= false;
  }
  return hist_exist;
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
    // tdrStyle->SetPadBorderSize(Width_t size = 1);
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
    // tdrStyle->SetHistFillColor(1);
    // tdrStyle->SetHistFillStyle(0);
    tdrStyle->SetHistLineColor(1);
    tdrStyle->SetHistLineStyle(0);
    tdrStyle->SetHistLineWidth(1);
    // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
    // tdrStyle->SetNumberContours(Int_t number = 20);
    tdrStyle->SetEndErrorSize(2);
    //  tdrStyle->SetErrorMarker(20);
    //  tdrStyle->SetErrorX(0.);

    tdrStyle->SetMarkerStyle(20);

    //For the fit/function:
    tdrStyle->SetOptFit(1);
    tdrStyle->SetFitFormat("5.4g");
    tdrStyle->SetFuncColor(2);
    tdrStyle->SetFuncStyle(1);
    tdrStyle->SetFuncWidth(1);

    //For the date:
    tdrStyle->SetOptDate(0);
    // tdrStyle->SetDateX(Float_t x = 0.01);

    // tdrStyle->SetDateY(Float_t y = 0.01);

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
    // tdrStyle->SetStatStyle(Style_t style = 1001);
    // tdrStyle->SetStatX(Float_t x = 0);
    // tdrStyle->SetStatY(Float_t y = 0);

    // Margins:
    tdrStyle->SetPadTopMargin(0.05);
    tdrStyle->SetPadBottomMargin(0.12);
    tdrStyle->SetPadLeftMargin(0.12);
    tdrStyle->SetPadRightMargin(0.1);

    // For the Global title:

    tdrStyle->SetOptTitle(0);
    tdrStyle->SetTitleFont(42);
    tdrStyle->SetTitleColor(1);
    tdrStyle->SetTitleTextColor(1);
    tdrStyle->SetTitleFillColor(10);
    tdrStyle->SetTitleFontSize(0.05);
    // tdrStyle->SetTitleH(0); // Set the height of the title box
    // tdrStyle->SetTitleW(0); // Set the width of the title box
    // tdrStyle->SetTitleX(0); // Set the position of the title box
    // tdrStyle->SetTitleY(0.985); // Set the position of the title box
    // tdrStyle->SetTitleStyle(Style_t style = 1001);
    // tdrStyle->SetTitleBorderSize(2);

    // For the axis titles:

    tdrStyle->SetTitleColor(1, "XYZ");
    tdrStyle->SetTitleFont(42, "XYZ");
    tdrStyle->SetTitleSize(0.06, "XYZ");
    // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    // tdrStyle->SetTitleYSize(Float_t size = 0.02);
    tdrStyle->SetTitleXOffset(0.9);
    tdrStyle->SetTitleYOffset(1.4);
    // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset


    // For the axis labels:

    tdrStyle->SetLabelColor(1, "XYZ");
    tdrStyle->SetLabelFont(42, "XYZ");
    tdrStyle->SetTitleSize(0.06, "XYZ");
    // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    // tdrStyle->SetTitleYSize(Float_t size = 0.02);
    tdrStyle->SetTitleXOffset(0.9);
    tdrStyle->SetTitleYOffset(1.4);
    // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

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


    // tdrStyle->SetLineScalePS(Float_t scale = 3);
    // tdrStyle->SetLineStyleString(Int_t i, const char* text);
    // tdrStyle->SetHeaderPS(const char* header);
    // tdrStyle->SetTitlePS(const char* pstitle);

    // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
    // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
    // tdrStyle->SetPaintTextFormat(const char* format = "g");
    // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
    // tdrStyle->SetTimeOffset(Double_t toffset);
    // tdrStyle->SetHistMinimumZero(kTRUE);

    tdrStyle->cd();

  }
