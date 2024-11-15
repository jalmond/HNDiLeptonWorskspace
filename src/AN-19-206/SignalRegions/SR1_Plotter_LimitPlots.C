#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLSRPlotter.cc"


void SR1_Plotter_LimitPlots(){

  TString DATE = "Oct16";
  vector<TString> eras = {"Run2"};
  for (auto year : eras){
    vector<TString> channels = {"MuMu"};
    for (auto channel : channels){
      
      cout << "Running SR/CR plot for "<<  flavour<< " Channel : Era = " <<   year << endl;

      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULID"};

      //// Run Yield print code                                                                                                                                                                                                                                                        
      HNLSRPlotter Plotter(PlotterTag+"_SR1_Plotter");
      //// change def
      Plotter.DoDebug=true;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;


      int nRegionBins = nSRBins + nCRBins;
      TH1D * h_main_plot = new TH1D(PlotterTag+"_SR1_Plotter",PlotterTag+"_SR1_Plotter", nRegionBins,0, nRegionBins);
      h_main_plot->GetXaxis()->SetBinLabel(1,"[0-500)");
      h_main_plot->GetXaxis()->ChangeLabel(1,270,-1,2)
	

      TH1D * h_prompt_SR =  Plotter.ConstructHist(path_prompt,HistSR);

      
      
      
    }
  }
  
  
  return;
}

