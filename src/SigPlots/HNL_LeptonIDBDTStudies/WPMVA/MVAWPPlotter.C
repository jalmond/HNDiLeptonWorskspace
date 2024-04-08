#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void MVAWPPlotterRun(TString era, vector<TString>  EtaBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label);


void MVAWPPlotter(){

  vector<TString> MVAStrings = {"BDTGv3","BDTGv3p1","BDTGv3p2", "BDTGv3b","BDTGv3c","BDTGv3cp1","BDTGv3cp2","BDTGv3d","BDTGv3dp1","BDTGv3dp2"};


  vector<TString> Eras = {"2017"};
  TString LabelForWeb = "MVAWP_";
                                                               


  for(auto Era: Eras) MVAWPPlotterRun(Era ,{"IB","OB","EC"} , MVAStrings, "MVA2D", LabelForWeb+Era+"_EC");

}


void MVAWPPlotterRun(TString era, vector<TString>  EtaBins, vector<TString> MVAStrings,TString InDir, TString WebSite_Label){
  
  vector<TString> eras =  {era};
  
  for (auto year : eras){
    for (auto EtaBin : EtaBins){

      TString Binlabel = EtaBin;

      for (auto MVAString : MVAStrings){
	
	HNLPlotter Plotter("MVAWPPlotter");
	Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
	Plotter.CopyToWebsite = true;
	
	TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	
	vector<TH1D*> vHists;
	
	TH2D *hist_prompt   = Plotter.Construct2DHist(path+"/HNL_LeptonIDBDTStudies_SkimTree_DileptonBDT_DYJets.root",		    InDir + "/"+EtaBin+"_RegionPlots_"+MVAString);
	
	Plotter.Draw_MVA_WP( {hist_prompt} , {"95% WP"} , 0.95,  MVAString+ "_"+ InDir+"_"+Binlabel, WebSite_Label);
	
      }//// MVAStrings                                                                                                                                                                     
    }
    
  }
  
  return;

}
