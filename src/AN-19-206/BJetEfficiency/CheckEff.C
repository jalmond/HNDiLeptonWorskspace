#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString Era, TString Type, TString sNum, TString sDen,TString label);



void CheckEff() {

  std::vector<std::string> eras = {"2016preVFP", "2016postVFP", "2017", "2018"};
  std::vector<std::string> files = {
    "MeasureJetTaggingEfficiency_TTLL_TTLJ_2L_hadded.root",
    "MeasureJetTaggingEfficiency_DY_2L_hadded.root",
    "MeasureJetTaggingEfficiency_DY_2L.root",
    "MeasureJetTaggingEfficiency_WG_2L_hadded.root",
    "MeasureJetTaggingEfficiency_WW_2L_hadded.root",
    "MeasureJetTaggingEfficiency_TTV_2L_hadded.root",
    "MeasureJetTaggingEfficiency_WZ_2L_hadded.root",
    "MeasureJetTaggingEfficiency_ZG_2L_hadded.root",
    "MeasureJetTaggingEfficiency_ZZ_2L_hadded.root",
    "MeasureJetTaggingEfficiency_HNL_SSWW_2L_hadded.root",
    "MeasureJetTaggingEfficiency_HNL_VBF_2L_hadded.root",
    "MeasureJetTaggingEfficiency_HNL_DY_2L_hadded.root"
  };

  for (const auto& era : eras) {
    for (const auto& file : files) {
      DrawConfig(era, file, "Jet_" + era + "_DeepJet_Medium_eff_B_num", "Jet_" + era + "_eff_B_denom", "BFlavour");
      DrawConfig(era, file, "Jet_" + era + "_DeepJet_Medium_eff_C_num", "Jet_" + era + "_eff_C_denom", "CFlavour");
      DrawConfig(era, file, "Jet_" + era + "_DeepJet_Medium_eff_Light_num", "Jet_" + era + "_eff_Light_denom", "LFlavour");
    }
  }

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

  
  
  // === Check and fix numerator and denominator bins before division ===
  for (int x = 1; x <= hist_denom->GetNbinsX(); ++x) {
    for (int y = 1; y <= hist_denom->GetNbinsY(); ++y) {
      
      double den_content = hist_denom->GetBinContent(x, y);
      double num_content = hist_num->GetBinContent(x, y);
      
      
      // Fix denominator if <= 0
      if (den_content <= 0) {
	std::cout << "[BinFix] hist_denom bin (" << x << "," << y
		  << ") had content " << den_content << " -> set to 1.0" << std::endl;
	hist_denom->SetBinContent(x, y, 1.0);
	hist_denom->SetBinError(x, y, 1.0);
      }

      
      // Fix numerator if < 0
      if (num_content == 1) {
        std::cout << "[BinFix] hist_num bin (" << x << "," << y
                  << ") had negative content " << num_content << " -> set to 1.0" << std::endl;
        hist_num->SetBinContent(x, y, 0.99);
	hist_num->SetBinError(x, y, 0.99);
      }

      if (num_content <= 0) {
	std::cout << "[BinFix] hist_num bin (" << x << "," << y
		  << ") had negative content " << num_content << " -> set to 1.0" << std::endl;
	hist_num->SetBinContent(x, y, 0.99);
	hist_num->SetBinError(x, y, 0.99);
      }
    }
  }
  
  // === Perform binomial division ===
  hist_num->Divide(hist_num, hist_denom, 1., 1., "b");
  
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
  c1->SaveAs("Results/"+HNAME+".pdf");

  delete c1;
  cout << "END" << endl;
  return;
}



