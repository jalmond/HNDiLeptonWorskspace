#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


void DrawConfig(TString flavour, TString year, TString filepath);

void DrawSFPlotsEE(){
  ///data9/Users/jihkim_public/240830_EGM/ID/HNL_2018.root  
  ///  DrawConfig("Electron","2016preVFP", "Electron/IDEff_HNL_v1_2016a.root");
  //DrawConfig("Electron","2016postVFP", "Electron/IDEff_HNL_v1_2016b.root");
  //DrawConfig("Electron","2017", "Electron/IDEff_HNL_v1_2017.root");
  // DrawConfig("Electron","2016preVFP", "HNL_2016a.root");
  //DrawConfig("Electron","2016postVFP", "HNL_2016b.root");
  //DrawConfig("Electron","2017", "HNL_2017.root");
  DrawConfig("Electron","2018", "TightID_2018.root");

}

void DrawConfig(TString flavour, TString era, TString filepath){


  vector<TString> eras =  {era};
  
  for (auto year : eras){
    HNL_Efficiency_Plotter Plotter("LeptonSF");
    Plotter.SetupPlotter(year,"",flavour+"_ID_SF_Uncertainty");
    Plotter.CopyToWebsite = false;
    
    ////    TString path="/data9/Users/jihkim_public/240830_EGM/ID/"+filepath;
    TString path="/data9/Users/jihkim_public/240830_EGM/ID/"+filepath;   
    ///data9/Users/jihkim_public/240830_EGM/ID/"+filepath;
    ///data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/ID/"+filepath;

   
    TH2D *hist_Cent       = Plotter.Construct2DHist(path,"sf");
    TH2D *hist_Cent_Syst  = Plotter.Construct2DHist(path,"sf_sys");

    
    TH1D* h_lepIDSF_plusEta  =  new TH1D ("h_"+flavour+"IDSF_peta","h_"+flavour+"IDSF_Syst",36,0,36);
    TH1D* h_lepIDSF_minusEta =  new TH1D ("h_"+flavour+"IDSF_meta","h_"+flavour+"IDSF_Stat",36,0,36);
    int nBinx=0;
    //-2.5, -2.,-1.566, -1.479, -0.8, 0., 0.8, 1.479,1.566, 2., 2.5
    vector<TString> etabins = {"0-0.8","0.8-1.479","1.566-2","2-2.5"};
    for(auto etabin : etabins){
      double nBinx_shift = 9*double(nBinx);
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+1, "15-20");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+2, "20-25");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+3, "25-30");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+4, "30-35");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+5, "35-50");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+6, "50-70");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+7, "70-100");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+8, "100-200");
      h_lepIDSF_plusEta->GetXaxis()->SetBinLabel(nBinx_shift+9, "200-500");
      nBinx=nBinx+1;
    }
    vector<double> etabinsD = {0.2,1.4,1.9,2.3};
    vector<double> BinPts = { 17., 22., 27., 32., 42., 52., 72., 122.,220};
    int nbin=1;
    for(auto etabinD : etabinsD){
      for(auto BinPt : BinPts){

	int this_binP = hist_Cent->FindBin( etabinD ,BinPt);
	double ValuePlus = hist_Cent->GetBinContent(this_binP);
	double errorPlus = hist_Cent->GetBinError(this_binP);
	double errorPerPlus = 100*errorPlus/ValuePlus;
	
	
        int this_binM = hist_Cent->FindBin( -1*etabinD ,BinPt);
        double ValueMinus = hist_Cent->GetBinContent(this_binM);
        double errorMinus = hist_Cent->GetBinError(this_binM);
        double errorPerMinus = 100*errorMinus/ValueMinus;
	
	//cout << "etabinD = " << etabinD << " BinPt = " << BinPt << " errorStat = " << errorStat << " Value = " << Value <<  " errorPStat = " << errorPStat << " errorPSyst = " << errorPSyst << endl;
	
        h_lepIDSF_plusEta->SetBinContent(nbin, errorPerPlus);
        h_lepIDSF_minusEta->SetBinContent(nbin, errorPerMinus);

	nbin++;
      }
    }

    Plotter.draw_IDSF_Syst_canvas(h_lepIDSF_plusEta,h_lepIDSF_minusEta, flavour+"_IDSF_EtaSplit_POG",year,35);
    
  }
  
  return;
}



