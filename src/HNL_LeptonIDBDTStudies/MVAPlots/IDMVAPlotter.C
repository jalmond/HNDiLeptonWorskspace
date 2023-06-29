#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void IDMVAPlotter(){

  //  vector<TString> eras =  {"2016preVFP", "2016postVFP", "2017","2018"};
  vector<TString> eras =  {"2018"};
  vector<TString> EtaBins = {"BB","EC"};//,"Ptgt50", "Ptlt15","Ptlt20","Ptlt50"};
  //vector<TString> MVAStrings = {"MVA__El_ED_CF_v2" };//,"MVA__El_CF_v2", "MVA__El_CF_v2p1","MVA__El_CF_v2p2", "MVA__El_ED_CF_v2p1","MVA__El_ED_CF_v2p2"};
  
  vector<TString> MVAStrings = {"MVA__El_ED_Fake_v4" };
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      for (auto MVAString : MVAStrings){
	
	HNLPlotter Plotter("IDMVAPlotter");
	Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
	Plotter.DoDebug=true;
	Plotter.CopyToWebsite = true;
	
	TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	//vector<TString> SampleList = {}
	
	TH1D *hist_prompt   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root", 
						    "BDTVariables/Electron/IsPrompt"+EtaBin+"_/"+MVAString);
	TH1D *hist_cf       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root",
						    "BDTVariables/Electron/IsPromptCF_IsCF"+EtaBin+"_/"+MVAString);
	
        TH1D *hist_fake     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root",
                                                    "BDTVariables/Electron/IsFake"+EtaBin+"_/"+MVAString);


	TH1D *hist_Eff = Plotter.GetScanEfficiency(hist_prompt);
	hist_Eff->GetYaxis()->SetTitle("Cut Efficiency");
	hist_Eff->GetXaxis()->SetTitle("MVA Score");
	
	TH1D *hist_Eff_CF = Plotter.GetScanEfficiency(hist_cf);
	TH1D *hist_Eff_Fake = Plotter.GetScanEfficiency(hist_fake);
	
	
	TH1D *HNTightPrompt = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root",
						    "TightID/Electron/IsPrompt"+EtaBin+"_/MVA__HNTightV2");
	TH1D *hist_CutEff_Prompt = Plotter.GetCutEfficiency(HNTightPrompt);
	

	TH1D *HNTightCF  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root",
						 "TightID/Electron/IsPromptCF_IsCF"+EtaBin+"_/MVA__HNTightV2");
	TH1D *hist_CutEff_CF  = Plotter.GetCutEfficiency(HNTightCF);


        TH1D *HNTightFake  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Bkg.root",
                                                 "TightID/Electron/IsFake"+EtaBin+"_/MVA__HNTightV2");
        TH1D *hist_CutEff_Fake  = Plotter.GetCutEfficiency(HNTightFake);

	

	
	Plotter.draw_hists_canvas({hist_Eff,hist_Eff_CF,hist_Eff_Fake,hist_CutEff_Prompt,hist_CutEff_CF,hist_CutEff_Fake}, {"Prompt ","CF", "Fake","POG[T] Prompt", "POG[T] CF", "POG[T] Fake"},MVAString+"_"+EtaBin, "MVAScore");
	//Plotter.draw_SvsB_canvas({hist_Eff,hist_Eff_CF,hist_CutEff_Prompt,hist_CutEff_CF}, {"Prompt TT","CF TT", "POG[T] Prompt", "POG[T] CF"},MVAString+"_"+EtaBin, "MVAScore");
      
	

      }	
    }
  }
  
  return;
}

