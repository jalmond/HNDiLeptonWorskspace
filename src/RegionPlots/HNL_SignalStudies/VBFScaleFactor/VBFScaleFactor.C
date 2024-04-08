#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void VBFScaleFactor(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2018"};
  vector<TString> Masses = {"600"};
  
  for (auto year : eras){
    for (auto mass : Masses){
      
      HNLPlotter Plotter("VBFScaleFactor");
      Plotter.DoDebug=true;
      Plotter.CopyToWebsite = false;
      
      cout << year << " " << "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/2017/HNL_SignalStudies_SkimTree_HNMultiLepBDT_VBFTypeI_DF_M"+mass+"_private.root" << endl;
      TH1D* hist_channel_breakdown = Plotter.ConstructHist("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/2017/HNL_SignalStudies_SkimTree_HNMultiLepBDT_VBFTypeI_DF_M"+mass+"_private.root","SignalProcess/FillEventCutflow/SplitChannel");
      
      int n_bin = hist_channel_breakdown->GetNbinsX();
      double OS_MuMu(0.), OS_EE(0.), OS_EMu(0), OS_MuE(0);
      double SS_MuMu(0.), SS_EE(0.), SS_EMu(0), SS_MuE(0);
      for(unsigned int i=1; i<=n_bin; i++){
	cout << "Bin " << hist_channel_breakdown->GetXaxis()->GetBinLabel(i) << " " << hist_channel_breakdown->GetBinContent(i) << endl;
	TString lab = hist_channel_breakdown->GetXaxis()->GetBinLabel(i);
	if(lab.Contains("MuMu") ||  lab.Contains("SS_Mu-Mu-") || lab.Contains("SS_Mu+Mu+") ) {
	  if(lab.Contains("MuMu")) OS_MuMu+= hist_channel_breakdown->GetBinContent(i);
	  else SS_MuMu+= hist_channel_breakdown->GetBinContent(i);
	}
	else if(lab.Contains("ElEl") ||  lab.Contains("SS_El-El-") || lab.Contains("SS_El+El") ) {
	  if(lab.Contains("ElEl")) OS_EE+= hist_channel_breakdown->GetBinContent(i);
	  else  SS_EE+= hist_channel_breakdown->GetBinContent(i);
	}


	else if(lab.Contains("MuEl") ||  lab.Contains("SS_Mu-El-") || lab.Contains("SS_Mu+El+") ) {
	  if(lab.Contains("MuEl") ) OS_MuE+= hist_channel_breakdown->GetBinContent(i);
	  else SS_MuE+= hist_channel_breakdown->GetBinContent(i);

	}
	else if(lab.Contains("ElMu") ||  lab.Contains("SS_El-Mu-") || lab.Contains("SS_El+Mu+") ) {
	  if(lab.Contains("ElMu")) OS_EMu+= hist_channel_breakdown->GetBinContent(i);
	  else SS_EMu+= hist_channel_breakdown->GetBinContent(i);
	}
      }
      double SF_ssMM =  (OS_MuMu+SS_MuMu)/(2*SS_MuMu) ;
      double SF_ssEE =  (OS_EE+SS_EE)    /(2*SS_EE) ;
      double SF_ssME =  (OS_MuE+SS_MuE)   /(2*SS_MuE);
      double SF_ssEM =  (OS_EMu+SS_EMu)  /(2*SS_EMu) ;
      
      double SF_osMM =  (OS_MuMu+SS_MuMu)/(2*OS_MuMu) ;
      double SF_osEE =  (OS_EE+SS_EE)    /(2*OS_EE) ;
      double SF_osME =  (OS_MuE+SS_MuE)   /(2*OS_MuE);
      double SF_osEM =  (OS_EMu+SS_EMu)  /(2*OS_EMu) ;

      double SF_MM = (OS_MuMu+SS_MuMu + OS_EE+SS_EE + OS_MuE+SS_MuE + OS_EMu+SS_EMu) / (4* (OS_MuMu+SS_MuMu));
      double SF_EE = (OS_MuMu+SS_MuMu + OS_EE+SS_EE + OS_MuE+SS_MuE + OS_EMu+SS_EMu) / (4* (OS_EE+SS_EE));
      double SF_ME = (OS_MuMu+SS_MuMu + OS_EE+SS_EE + OS_MuE+SS_MuE + OS_EMu+SS_EMu) / (4* (OS_MuE+SS_MuE));
      double SF_EM = (OS_MuMu+SS_MuMu + OS_EE+SS_EE + OS_MuE+SS_MuE + OS_EMu+SS_EMu) / (4* (OS_EMu+SS_EMu));
      
      cout << "SS MuMu  = "   << SF_MM*SF_ssMM << endl;
      cout << "SS EE    = "   << SF_EE*SF_ssEE << endl;
      cout << "SS MuE   = "   << SF_ME*SF_ssME << endl;
      cout << "SS EMu   = "   << SF_EM*SF_ssEM << endl;
      
    }
  }
  
  
  return;
}

