#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH2D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void setTDRStyle2() ;

void RateIndiv(TString era, TString versionID, TString AJ);

void nominal_rate_EE(){

  for (auto Era : {"2018","2017","2016preVFP","2016postVFP"}){
    
    for (auto Version :  {"v0","v1_a","v2_a","v3_a","v4_a","v5_a","v6_a","v7_a","v8_a","v9_a"}){
      for (auto  AJ : {"AJ40"}){
	RateIndiv(Era,Version,AJ);
      }
    }
  }
}

void RateIndiv(TString _Era,TString versionID, TString AJ){
  
  TString LabelForWeb = "FRate_2024_EGamma_ANv1";

  for (auto Era : {_Era}){

    TString year = Era;
    if(year == "2016preVFP") Era = "2016";
    if(year == "2016postVFP") Era = "2016";
    

    TString path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/FakeRate/DataFR/ElFR/MainFiles/FR_EGamma_"+Era+"_HNL_ULID_PtParton_v5.root";
    if(year == "2016preVFP") path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/FakeRate/DataFR/ElFR/MainFiles/FR_EGamma_2016a_HNL_ULID_PtParton_v5.root";
    if(year == "2016postVFP") path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/FakeRate/DataFR/ElFR/MainFiles/FR_EGamma_2016b_HNL_ULID_PtParton_v5.root";

    TFile* file = new TFile(path);

    
    TString ID = "HNL_ULID";
    HNLPlotter Plotter("HNL_Lepton_Fake");
    Plotter.SetupPlotter(year,"","HNL_Lepton_Fake");
    Plotter.CopyToWebsite = true;
    
    cout << "Accessing file " << path << endl;
    ifstream f(path.Data());
    if(!f.good()) {
      cout << "No File found..." << endl;
      return;
    }
   
    vector<TH2D*> hists;

    //TH2D *hist_eta     = Plotter.Construct2DHist(path, "HNL_ULID_FO_"+Era+"_ptparton_etaBinning2_HNL_ULID_"+versionID+"_"+AJ+"_FR_cent");

    //==== get histogram                                                                                                                                                                                                                                                                                                              
    //HNL_ULID_2016_ptparton_eta_HNL_ULID_FO_v8_c_AJ40_El12;1                             
    TH2D* hist_eta = (TH2D*)file->Get("HNL_ULID_"+Era+"_ptparton_eta_HNL_ULID_FO_"+versionID+"_"+AJ+"_El12");
				      //"HNL_ULID_2018_ptparton_etaBinning2_HNL_ULID_FO_v0_AJ40_FR_cent");
                                    //
    cout << hist_eta << endl;    
    if(!hist_eta) {
      cout<< "Error in HNL_ULID_"+Era+"_ptparton_etaBinning2_HNL_ULID_FO_"+versionID+"_"+AJ+"_FR_cent" << endl;
    }
    
    hist_eta->GetXaxis()->SetTitle("p^{parton}_{T} (GeV)");
    hist_eta->GetYaxis()->SetTitle("Fake Rates ");
    
    hists.push_back(hist_eta);

    Plotter.SetLogY=false;
    TString Label = Era+"_"+versionID+"_"+AJ ;

    if(year == "2016preVFP"&&versionID=="v9_a")     SaveHistogram(Plotter, hists, {year,""}, "HNL_Lepton_Fake_"+ID+"_"+versionID+AJ+"_DATA", LabelForWeb, {Label});
    if(year == "2016postVFP"&&versionID=="v9_a")     SaveHistogram(Plotter, hists, {year,""}, "HNL_Lepton_Fake_"+ID+"_"+versionID+AJ+"_DATA", LabelForWeb, {Label});
    if(year == "2017"&&versionID=="v9_a")     SaveHistogram(Plotter, hists, {year,""}, "HNL_Lepton_Fake_"+ID+"_"+versionID+AJ+"_DATA", LabelForWeb, {Label});
    if(year == "2018"&&versionID=="v9_a")     SaveHistogram(Plotter, hists, {year,""}, "HNL_Lepton_Fake_"+ID+"_"+versionID+AJ+"_DATA", LabelForWeb, {Label});
    
    SaveHistogram(Plotter, hists, {year,versionID}, "HNL_Lepton_Fake_"+ID+"_"+versionID+AJ+"_DATA", LabelForWeb, {Label});
    
  }
  
  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH2D*>hists, vector<TString> legname,  TString HistName, TString dirName, vector<TString> Labels){



  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  cout << plotter.thiscut_plotpath << endl;
  plotter.mkdir(plotter.thiscut_plotpath);

  TH2D* hist_default = hists[0];

  //const char * format = (char*)'4.3f';
  //  gStyle->SetPaintTextFormat((char*)'4.1f');

  TCanvas* c1 = new TCanvas(HistName, "Data fake rate map for " + legname[0] + " electrons ID "+legname[1],1100, 800);

  c1->Draw();
  c1->cd();

  c1->SetTopMargin( 0.1);
  c1->SetBottomMargin( 0.12 );
  c1->SetRightMargin( 0.12 );
  c1->SetLeftMargin( 0.12 );


  TH2D *hist_empty= (TH2D*)hist_default->Clone();
  hist_empty->SetTitle("Data fake rate map for " + legname[0] + " electrons ID "+legname[1] );

  hist_empty->GetXaxis()->SetRangeUser(15,80);
  hist_empty->SetName("DUMMY_FOR_AXIS");
  hist_empty->SetMarkerSize(0.8);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 0.4), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 1.4), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 2.), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 2.4), 0);
  //  hist_axis(hist_empty);
  
  hist_empty->GetYaxis()->SetLabelSize(0.03);
  hist_empty->GetYaxis()->SetTitleSize(0.04);
  hist_empty->GetYaxis()->SetTitleOffset(1.20);

  hist_empty->GetXaxis()->SetLabelSize(0.03);
  hist_empty->GetXaxis()->SetTitleSize(0.04);
  hist_empty->GetXaxis()->SetTitleOffset(1.20);

  hist_empty->SetName("Data fake rate map for " + legname[0] + " electrons ID "+legname[1] );
  gStyle->SetPaintTextFormat("4.2f");

  c1->Update();
  hist_empty->SetTitle("Data fake rate map for " + legname[0] + " electrons ID "+legname[1] );
  hist_empty->Draw("colztextE");


  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  //  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);

  TLatex latex_title;
  latex_title.SetNDC();
  latex_title.SetTextSize(plotter.LatexTextCMS_Size);
  latex_title.DrawLatex(0.25, 0.95, "Data fake rate map for " + legname[0] + " electrons ID "+legname[1] );

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  c1->SetTitle("Data fake rate map for " + legname[0] + " electrons ID "+legname[1]);
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+legname[0]+"_"+legname[1]+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;

}


void setTDRStyle2() {


  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  char* ch = "4.4f";
  tdrStyle->SetPaintTextFormat(ch);
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
  tdrStyle->SetPadTopMargin(0.1);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.12);
  tdrStyle->SetPadRightMargin(0.05);


  // For the Global title:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);


  // For the axis titles:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleColor(4, "Z");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(1.2);
  //  tdrStyle->SetTitleXOffset(1.5);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  tdrStyle->SetTitleXOffset(0.9);
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
