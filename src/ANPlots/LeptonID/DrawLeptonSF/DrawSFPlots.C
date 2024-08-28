#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


void DrawConfig(TString flavour, TString year, TString filepath, double ymax);

void DrawSFPlots(){
  
  DrawConfig("Muon","2016preVFP", "Muon/efficiency_ID_2016a.root",10);
  DrawConfig("Muon","2016postVFP", "Muon/efficiency_ID_2016b.root",10);
  DrawConfig("Muon","2017", "Muon/efficiency_ID_2017.root",8);
  DrawConfig("Muon","2018", "Muon/efficiency_ID_2018.root",8);

}

void DrawConfig(TString flavour, TString era, TString filepath,double ymax){


  vector<TString> eras =  {era};
  
  for (auto year : eras){
    HNL_Efficiency_Plotter Plotter("LeptonSF");
    Plotter.SetupPlotter(year,"",flavour+"_ID_SF_Uncertainty");
    Plotter.CopyToWebsite = false;
    
    TString path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/ID/"+filepath;

    
    TH2D *hist_Cent       = Plotter.Construct2DHist(path,"sf");

    
    TH1D* h_lepIDSF_Syst =  new TH1D ("h_"+flavour+"IDSF_Syst","h_"+flavour+"IDSF_Syst",36,0,36);
    int nBinx=0;
    vector<TString> etabins = {"0.0-0.8","0.8-1.2","1.2-2.1","2.1-2.5"};
    for(auto etabin : etabins){
      double nBinx_shift = 9*double(nBinx);
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+1, "10-15");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+2, "15-20");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+3, "20-25");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+4, "25-30");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+5, "30-40");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+6, "40-50");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+7, "50-60");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+8, "60-120");
      h_lepIDSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+9, "120-1000");
      nBinx=nBinx+1;
    }
    vector<double> etabinsD = {0.2, 0.9, 1.3,2.2};
    vector<double> BinPts = {12., 17., 22., 27., 32., 42., 52., 62., 122.};
    int nbin=1;
    for(auto etabinD : etabinsD){
      for(auto BinPt : BinPts){
	int this_bin = hist_Cent->FindBin( etabinD ,BinPt);
	double Value = hist_Cent->GetBinContent(this_bin);
	double error = hist_Cent->GetBinError(this_bin);
	double errorP = 100*error/Value;
	cout << "etabinD = " << etabinD << " BinPt = " << BinPt << "  errorP = " << errorP << endl;
	h_lepIDSF_Syst->SetBinContent(nbin, errorP);
	nbin++;
      }
    }

    //Plotter.draw_IDSF_Syst_canvas(h_lepIDSF_Syst,flavour+"_IDSF_Syst",year,ymax);

  }
  
  return;
}



