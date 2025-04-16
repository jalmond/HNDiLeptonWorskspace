#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString Era, TString Type, TString sNum, TString sDen,TString label);

void CheckEff(){

  DrawConfig("2018","MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root", "Jet_2018_DeepJet_Medium_eff_B_num", "Jet_2018_eff_B_denom", "BFlavour"); 
  DrawConfig("2018","MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root", "Jet_2018_DeepJet_Medium_eff_C_num", "Jet_2018_eff_C_denom", "CFlavour"); 
  DrawConfig("2018","MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root", "Jet_2018_DeepJet_Medium_eff_Light_num", "Jet_2018_eff_Light_denom", "LFlavour"); 
  
  /*
    KEY: TH2DJet_2018_DeepJet_Medium_eff_B_num;1
    KEY: TH2DJet_2018_DeepJet_Medium_eff_C_num;1
    KEY: TH2DJet_2018_DeepJet_Medium_eff_Light_num;1
    KEY: TH2DJet_2018_eff_B_denom;1
    KEY: TH2DJet_2018_eff_C_denom;1
    KEY: TH2DJet_2018_eff_Light_denom;1
   */
   

}

void DrawConfig(TString Era, TString Type, TString sNum,TString sDen,TString label){
    
  TString year = Era;
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("BJetEff");
  Plotter.SetupPlotter(year,"","ID_Rates");
  Plotter.CopyToWebsite = false;
  
  TString path="Input/"+Era+"/"+Type;

  
  TCanvas* c1 = new TCanvas("BJetEff", "", 800, 800);
  c1->Draw();
  c1->cd();

  canvas_margin(c1);

  std::ifstream file(path);
  if (!file) {
    std::cerr << "Error: File " << path << " does not exist.\n";
    return ; // Exit with a non-zero status code.
  }
  else cout << "Accessing " << path << endl;

  cout << "Num " <<  Type+"/"+sNum << endl;
  TH2D *hist_num = Plotter.Construct2DHist(path,sNum);
  TH2D *hist_denom = Plotter.Construct2DHist(path,sDen);

  if (!hist_num || !hist_denom) {
    std::cerr << "Error: One of the histograms could not be created!\n";
    delete c1;
    return;
  }


  TH2D *hist_empty = (TH2D*)hist_num->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  
  hist_empty->Draw("hist");

  hist_axis(hist_empty);

  hist_num->Divide(hist_denom);

  gStyle->SetPaintTextFormat(".2f");

  hist_num->GetXaxis()->SetTitle("#eta");
  hist_num->GetYaxis()->SetTitle("p_{T} (GeV)");
  hist_num->Draw("textcolzE");
  
  TString TypeName = Type;
  if (TypeName.Contains(".root")) {
    TypeName.ReplaceAll(".root", "");
  }

  TString HNAME = TypeName+"_ID_Eff__"+sNum +"_"+sDen +"_"+year;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");

  delete c1;
  cout << "END" << endl;
  return;
}



