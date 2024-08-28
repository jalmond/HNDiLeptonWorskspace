#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


void DrawConfig(TString flavour, TString year, TString filepath, TString Tag);

void DrawTriggerSFPlots(){
  
  DrawConfig("Muon","2016preVFP", "Muon/efficiency_Mu17Leg1_2016a.root","Mu17Leg1");
  DrawConfig("Muon","2016postVFP", "Muon/efficiency_Mu17Leg1_2016b.root","Mu17Leg1");
  DrawConfig("Muon","2017", "Muon/efficiency_Mu17Leg1_2017.root","Mu17Leg1");
  DrawConfig("Muon","2018", "Muon/efficiency_Mu17Leg1_2018.root","Mu17Leg1");

  DrawConfig("Muon","2016preVFP", "Muon/efficiency_Mu8Leg2_2016a.root","Mu8Leg2");
  DrawConfig("Muon","2016postVFP", "Muon/efficiency_Mu8Leg2_2016b.root","Mu8Leg2");
  DrawConfig("Muon","2017", "Muon/efficiency_Mu8Leg2_2017.root","Mu8Leg2");
  DrawConfig("Muon","2018", "Muon/efficiency_Mu8Leg2_2018.root","Mu8Leg2");
  
}

void DrawConfig(TString flavour, TString era, TString filepath,TString Tag){

  vector<TString> eras =  {era};
  
  for (auto year : eras){
    HNL_Efficiency_Plotter Plotter("LeptonSF");
    Plotter.SetupPlotter(year,"",flavour+"_Trigger_SF_Uncertainty");
    Plotter.CopyToWebsite = false;
    
    TString path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+year+"/ID/"+filepath;

    
    TH2D *hist_Cent       = Plotter.Construct2DHist(path,"sf");

    double nBins = 32.;
    TH1D* h_lepTriggerSF_Syst =  new TH1D ("h_"+flavour+"IDSF_Syst","h_"+flavour+"IDSF_Syst",int(nBins),0,nBins);
    int nBinx=0;
    vector<TString> etabins = {"0.0-0.9","0.9-1.2","1.2-2.1","2.1-2.4"};
    for(auto etabin : etabins){
      double nBinx_shift = 8*double(nBinx);
      if(Tag=="Mu17Leg1"){
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+1, "16-18");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+2, "18-20");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+3, "20-25");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+4, "25-30");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+5, "30-40");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+6, "40-50");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+7, "50-100");
	h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+8, "100-1000");
      }
      else{
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+1, "10-15");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+2, "15-20");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+3, "20-25");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+4, "25-30");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+5, "30-40");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+6, "40-50");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+7, "50-100");
        h_lepTriggerSF_Syst->GetXaxis()->SetBinLabel(nBinx_shift+8, "100-1000");
      }
      nBinx=nBinx+1;
    }
    vector<double> etabinsD = {0.2, 0.95, 1.3,2.2};
    vector<double> BinPts = { 12.,17., 22., 27., 32., 42., 52.,  122.};
    if(Tag=="Mu17Leg1") BinPts = { 17.,19., 22., 27., 32., 42., 52.,  122.};

    double MaxError = 0;
    int nbin=1;
    for(auto etabinD : etabinsD){
      for(auto BinPt : BinPts){
	int this_bin = hist_Cent->FindBin( etabinD ,BinPt);
	double Value = hist_Cent->GetBinContent(this_bin);
	double error = hist_Cent->GetBinError(this_bin);
	double errorP = 100*error/Value;
	if(errorP > MaxError) MaxError = errorP;
	cout << "etabinD = " << etabinD << " BinPt = " << BinPt << "  errorP = " << errorP << endl;
	h_lepTriggerSF_Syst->SetBinContent(nbin, errorP);
	nbin++;
      }
    }
    double MaxErrorI = double(int(MaxError)) * 1.4;
    Plotter.draw_IDSF_Muon_canvas(h_lepTriggerSF_Syst,flavour+"_"+Tag+"_SF_Syst",year,Tag,MaxErrorI);

  }
  
  return;
}



