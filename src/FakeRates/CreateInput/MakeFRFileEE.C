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

void MakeFRFile(TString year,bool rmMC,TString dataset="EE");
TString DoubleToString(double d);


void MakeFRFileEE(){
  MakeFRFile("2016preVFP",true,"EE");
  MakeFRFile("2016postVFP", true,"EE");
  MakeFRFile("2017",true,"EE");
  MakeFRFile("2018",true,"EE");

}

void MakeFRFile(TString year, bool rmMC,TString dataset="EE"){


  
  TString path= "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_FakeRate/"+year+"/HNL_FakeRate_SkimTree_HNFake_data_"+dataset+".root";
  TString mcpath= "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_FakeRate/"+year+"/HNL_FakeRate_SkimTree_HNFake_MC.root";


    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "FakeRate13TeV_el_"+year+"_mva.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  
  std::vector<TString> IDs;
  vector<TString> vTrig = {"LooseTrig_"};//,"TightTrig_"};                                                                                                                 
  vector<TString> vConv = {"","ConvBEC_"};
  vector<TString> vCC = {"CCBEC_"};
  vector<TString> vMVAB;
  vector<TString> vMVAEC;
  for(unsigned int imva=0 ; imva < 70 ; imva++){
    double mva_d= -0.5 + double(imva)*0.02;
    TString mvaST = DoubleToString(mva_d);

    vMVAB.push_back("MVAB"+mvaST+"_");
  }
  for(unsigned int imva=0 ; imva < 85 ; imva++){
    double mva_d= -0.8 + imva*0.02;
    TString mvaST = DoubleToString(mva_d);

    vMVAEC.push_back("MVAEC"+mvaST+"_");
  }

  for(auto iTrig : vTrig){
    for(auto iConv : vConv){
      for(auto iCC : vCC){
	for(auto iMVAB : vMVAB) IDs.push_back(iTrig+iConv+iCC+iMVAB+"MVAECneg0p8_ISOB0p15_ISOEC0p15_DXYB1EC1");
	for(auto iMVAEC : vMVAEC) IDs.push_back(iTrig+iConv+iCC+iMVAEC+"MVABneg0p5_ISOB0p15_ISOEC0p15_DXYB1EC1");
	IDs.push_back(iTrig+iConv+iCC+"POGT_ISOB0p15_ISOEC0p15_DXYB1EC1");
	IDs.push_back(iTrig+iConv+iCC+"POGM_ISOB0p15_ISOEC0p15_DXYB1EC1");
	IDs.push_back(iTrig+iConv+iCC+"POGTNoIso_ISOB0p15_ISOEC0p15_DXYB1EC1");
	IDs.push_back(iTrig+iConv+iCC+"POGMNoIso_ISOB0p15_ISOEC0p15_DXYB1EC1");
      }
    }
  }

  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    
    TString denom = "Fake_LooseEE_El_" +IDs[i] +"_EE_40_ptcone_eta";
    TString num   = "Fake_TightEE_El_" +IDs[i] +"_EE_40_ptcone_eta";
    

    TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());
    TH2D* h_mcpt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_mcpt_denom= (TH2D*)fmc->Get(denom.Data());

    if (!h_pt_num){

      cout << path << endl;
      cout << mcpath << endl;

      cout << num << endl;
      cout << denom << endl;
      cout << "FakeRate\t Fake_TightEE_El_" +IDs[i] +"_EE_40 ptcone_eta"  << "\t" << "central " << outfile << endl;
      
      cout << h_pt_num << " " << h_pt_denom << endl;
      cout << h_mcpt_num << " " << h_mcpt_denom << endl;
    }
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TString name = IDs[i] ;

    TH2D* eff_rate = (TH2D*)h_pt_num->Clone((name+"_ptcone_eta_AwayJetPt40").Data());

    /*cout << "Data -MC bins " << endl;
    for(int x = 1 ; x < eff_rate->GetNbinsX()+1 ; x++){
      for(int y = 1 ; y < eff_rate->GetNbinsY()+1 ; y++){
	cout << "-----------------------" << endl;

        cout << x << " : " << y << " " << eff_rate->GetBinContent(x,y) << endl;
	cout << x << " : " << y << " " << h_mcpt_num->GetBinContent(x,y) << endl;
	cout << "DY: " << x << " : " << y << " " << h_DYpt_num->GetBinContent(x,y) << endl;
	cout << "Top: " <<   x << " : " << y << " " << h_Tpt_num->GetBinContent(x,y) << endl;
	cout << "W:"  << x << " : " << y << " " << h_Wpt_num->GetBinContent(x,y) << endl;
	
      }
      }*/

    if(rmMC)eff_rate->Add(h_mcpt_num,-1.);
    TH2D* hratedenom = (TH2D*)h_pt_denom->Clone((name +"_denom").Data());
    if(rmMC)hratedenom->Add(h_mcpt_denom,-1.);
    
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    
    
    cout << "-----------------------------------------------------" << endl;
    cout << name << endl;
    for(int x = 1 ; x < eff_rate->GetNbinsX()+1 ; x++){
      for(int y = 1 ; y < eff_rate->GetNbinsY()+1 ; y++){
	cout << x << " : " << y << " " << eff_rate->GetBinContent(x,y) << endl;

      }
    }
    cout << "-----------------------------------------------------" << endl;

    eff_rate->Write();
    


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


TString DoubleToString(double d){

  std::string str = std::to_string (d);
  str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
  str.erase ( str.find_last_not_of('.') + 1, std::string::npos );

  TString ts_str = TString(str);
  ts_str = ts_str.ReplaceAll(".","p");
  ts_str = ts_str.ReplaceAll("-","neg");

  return ts_str;

  
}
