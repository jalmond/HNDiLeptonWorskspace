#include "TFile.h"
#include "TH2.h"
#include "TTree.h"
#include <iostream>
#include <TStyle.h>

#include <vector>
#include "TSystem.h"

void PrintHistBins(TH2* h, TString label);

void setTDRStyle();
bool CheckFile(TFile* f);
bool CheckHist(TH2* h);

void make_promptrate_mu(int era){

  TString s_era = "2017";
  TString year = "2017";
  TString dataset="Muon";

  TDirectory* origDir = gDirectory;

  if(era == 0) {    s_era="2016preVFP"; year = "2016";}
  else if(era == 1) { s_era="2016postVFP"; year = "2016";}
  else if(era == 2) { s_era="2017"; year = "2017";}
  else if(era == 3) { s_era="2018"; year = "2018";}
  else return;
    
  TString ENV_FILE_PATH= (getenv("FILE_MERGED_PATH"));
  TString skim_name    = "";
  TString analyzername = "FakeRateHN";
  TString data_path=  ENV_FILE_PATH + "/"+analyzername+"/"+s_era+"/"+analyzername+"_"+skim_name+"data_"+dataset+".root";

  cout << data_path << endl;
  /// Set Plotting style
  setTDRStyle();   gStyle->SetPalette(1);
    
  TString outfile = "rootfiles/HNL_PromptRate_UnPrescaled_Muon_"+s_era+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  
  std::vector<TString> electron_ids ={                                    "HNTightV1",
				      "HNTightV2",
                                      "HNTight_17028",
                                      "POGTightWithTightIso"};

  TFile * fdata = new TFile(data_path);
  
  /// Set Plotting style
  setTDRStyle();  gStyle->SetPalette(1);
    

  std::vector<TString> ptlabel = {"ptcone_eta","pt_eta","ptcone_ptfix_eta"};
 
  double ptbinscone[10] = { 6.,10., 15.,20.,30.,40.,50.,  60., 100.,200.};
  Float_t etabins2[5] = { 0.,0.8,  1.479, 2.,  2.5};
  
  for(auto i : electron_ids){
            
    TString denom = "Prompt_LooseMuMu_" + i +"_MuMu_TZ_ptcone_eta";
    TString num   = "Prompt_TightMuMu_" + i +"_MuMu_TZ_ptcone_eta";
    cout << denom << " " << num << endl;
    TH2F* hist_pt_num    = (TH2F*)fdata->Get(num.Data()  );
    TH2F* hist_pt_denom  = (TH2F*)fdata->Get(denom.Data());
    
    CheckHist(hist_pt_denom);        CheckHist(hist_pt_num);
    
    TString name = i+"_ptcone_eta_UnPrescaled";
    
    TH2F* file_fake_rate = (TH2F*)hist_pt_num->Clone((name).Data());
    
    TH2F* hratedenom = (TH2F*)hist_pt_denom->Clone((name +"_denom").Data());
    
    file_fake_rate->Divide(file_fake_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    
    hist_pt_num->Divide(hist_pt_denom);
    
    fout->cd();
    
    file_fake_rate->Write();
    origDir->cd();
  }
  
  return;
}


void PrintHistBins(TH2* h, TString label){
  
  for(unsigned int ibinx=1; ibinx < h->GetNbinsX()+1; ibinx++){
    cout << "-------------------------------- " << endl;
    for(unsigned int ibiny=1; ibiny < h->GetNbinsY()+1; ibiny++){
      
      cout << label <<  " : xbin  [" << h->GetXaxis()->GetBinLowEdge(ibinx) << " - " << h->GetXaxis()->GetBinLowEdge(ibinx+1) << "]  ybin  [" <<  h->GetYaxis()->GetBinLowEdge(ibiny) << " - " << h->GetYaxis()->GetBinLowEdge(ibiny+1)  << " ] value = "  << h->GetBinContent(ibinx,ibiny)<< endl;
    }
  }
  
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
