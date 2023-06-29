#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
//#include "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/HNDiLeptonWorskspace/src/HNLPlotter.cc"
#include "HNLPlotter.cc"                                                                       

void IDMVAPlotterCFRun(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label);
void IDMVAPlotterCFRun2D(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString InDirDef, TString WebSite_Label);

void IDMVAPlotterCF(){

  vector<TString> MVAStrings = {"MVA__El_CF_v1", "MVA__El_CF_v2","MVA__El_CF_v2p1","MVA__El_CF_v2p2",                                                                                                               
				"MVA__El_ED_CF_v2","MVA__El_ED_CF_v2p1","MVA__El_ED_CF_v2p2"};                                                                                                           

  vector<TString> Eras = {"2016","2017","2018"};
  TString LabelForWeb = "MVAScoreCF_2023_June29";
                                                               

  vector<TString> PtBins = {"Ptgt200_", "Ptlt200_", "Ptlt15_","Ptlt20_","Ptlt50_"};

  for (auto Era : Eras) IDMVAPlotterCFRun(Era ,{"BB"} ,   PtBins, MVAStrings, "BDTVariables", LabelForWeb+"_PtBins");
  for (auto Era : Eras) IDMVAPlotterCFRun(Era ,{"EC"} ,   PtBins, MVAStrings, "BDTVariables", LabelForWeb+"_PtBins");

  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"BB"} ,      {""}, MVAStrings, "BDTVariablesNPBB4", "BDTVariables", LabelForWeb+"_2D");
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"EC"} ,      {""}, MVAStrings, "BDTVariablesNPEC4",  "BDTVariables",LabelForWeb+"_2D");

  return;

  for(auto Era: Eras) IDMVAPlotterCFRun(Era ,{"BB"} , {""}, MVAStrings, "BDTVariables", LabelForWeb+"_EtaBins");
  for(auto Era: Eras) IDMVAPlotterCFRun(Era ,{"EC"} , {""}, MVAStrings, "BDTVariables", LabelForWeb+"_EtaBins");
  //////////
  for(auto Era: Eras)IDMVAPlotterCFRun(Era ,{"BB","EC"} , {""}, MVAStrings, "SSBDTVariables", LabelForWeb+"_SS");
  //////////
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"BB"} ,      {""}, {"MVA__El_CF_v2"}, "BDTVariablesNPBB1", "BDTVariables", LabelForWeb+"_2D");
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"BB"} ,      {""}, {"MVA__El_CF_v2"}, "BDTVariablesNPBB2", "BDTVariables", LabelForWeb+"_2D");
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"BB"} ,      {""}, {"MVA__El_CF_v2"}, "BDTVariablesNPBB3", "BDTVariables", LabelForWeb+"_2D");

  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"EC"} ,      {""}, {"MVA__El_ED_CF_v2"}, "BDTVariablesNPEC1",  "BDTVariables",LabelForWeb+"_2D");
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"EC"} ,      {""}, {"MVA__El_ED_CF_v2"}, "BDTVariablesNPEC2",  "BDTVariables",LabelForWeb+"_2D");
  for(auto Era: Eras)IDMVAPlotterCFRun2D(Era ,{"EC"} ,      {""}, {"MVA__El_ED_CF_v2"}, "BDTVariablesNPEC3",  "BDTVariables",LabelForWeb+"_2D");


}


void IDMVAPlotterCFRun(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label){
  
  vector<TString> eras =  {era};
  
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      for (auto PtBin : PtBins){

	TString Binlabel = PtBin+EtaBin;

	map<TString, double> AUCValues;

	for (auto MVAString : MVAStrings){
	  
	  HNLPlotter Plotter("IDMVAPlotter");
	  Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
	  Plotter.CopyToWebsite = true;
	  
	  TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	    //vector<TString> SampleList = {}
	  
	  
	  vector<TH1D*> vHists;
	  
	  TH1D *hist_prompt   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",
						      InDir + "/Electron/IsPrompt"+Binlabel+"_/"+MVAString);
	  
	  TH1D *hist_fake     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",
						      InDir + "/Electron/IsFake"+Binlabel+"_/"+MVAString);

	  TH1D *hist_cf       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_CF.root",
						      InDir + "/Electron/IsPromptCF_IsCF"+Binlabel+"_/"+MVAString);

	  TH1D *hist_conv       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",
                                                      InDir + "/Electron/IsConv"+Binlabel+"_/"+MVAString);




	  TH1D *HNTightPrompt = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "TightID/Electron/IsPrompt"+Binlabel+"_/MVA__HNTightV2");
	  TH1D *hist_CutEff_Prompt = Plotter.GetCutEfficiency(HNTightPrompt);


	  TH1D *HNTightCF  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_CF.root",  "TightID/Electron/IsPromptCF_IsCF"+Binlabel+"_/MVA__HNTightV2");
	  TH1D *hist_CutEff_CF  = Plotter.GetCutEfficiency(HNTightCF);


	  TH1D *HNTightFake  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root", "TightID/Electron/IsFake"+Binlabel+"_/MVA__HNTightV2");
	  TH1D *hist_CutEff_Fake  = Plotter.GetCutEfficiency(HNTightFake);
	  
          TH1D *HNTightConv  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",  "TightID/Electron/IsConv"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_Conv  = Plotter.GetCutEfficiency(HNTightConv);


	  
	  TH1D *hist_Eff = Plotter.GetScanEfficiency(hist_prompt);
	  hist_Eff->GetYaxis()->SetTitle("Cut Efficiency");
	  hist_Eff->GetXaxis()->SetTitle("MVA Score");
	  
	  vHists.push_back(hist_Eff);
	  
	  TH1D *hist_Eff_CF = Plotter.GetScanEfficiency(hist_cf);
          TH1D *hist_Eff_Conv = Plotter.GetScanEfficiency(hist_conv);
	  TH1D *hist_Eff_Fake = Plotter.GetScanEfficiency(hist_fake);
	  vHists.push_back(hist_Eff);
	  
	  
	  vector<TString> IDs = {"HNTightV2", "HNL_Peking_"+year, "HNL_ULID_"+year};
	  vector<TString> Legends = {"Prompt Vs Fake ROC", "POG[T] HNTightV2", "Peking_{2018}", "HNL_{2018} SNU"};
	  
	  Plotter.SvsB_Promptpath(path+"/HNL_LeptonIDBDTStudies_Signal.root");
	  Plotter.SvsB_Comppath(path+"/HNL_LeptonIDBDTStudies_CF.root");
	  Plotter.SvsB_PromptHistPrefix( "TightID/Electron/IsPrompt"+Binlabel+"_/MVA__");
	  Plotter.SvsB_CompHistPrefix("TightID/Electron/IsPromptCF_IsCF"+Binlabel+"_/MVA__");
	  
	  
	  Plotter.draw_hists_canvas({hist_Eff,          hist_Eff_CF,    hist_Eff_Conv, hist_Eff_Fake,
		hist_CutEff_Prompt,hist_CutEff_CF, hist_CutEff_Conv, hist_CutEff_Fake}, {"Source lep_{Prompt} ","Source lep_{CF}", "Source lep_{Conv} ", "Source lep_{Fake}" ,"#epsilon_{HNTightV2} lep_{Prompt}", "#epsilon_{HNTightV2} lep_{CF}", "#epsilon_{HNTightV2} lep_{Conv}","#epsilon_{HNTightV2} lep_{Fake}"},MVAString+ "_"+ InDir+"_"+Binlabel, WebSite_Label);
	  
	  double AUC= Plotter.draw_SvsB_canvas({hist_Eff,hist_Eff_CF},  IDs, Legends , MVAString+"_"+InDir+"_"+Binlabel,WebSite_Label);
	  
          AUCValues[MVAString] = AUC;

        }//// MVAStrings                                                                                                                                                                     

        HNLPlotter Plotter("IDMVAPlotter");
        Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
        Plotter.CopyToWebsite = true;

        for(auto imap : AUCValues) cout << "AUC results : " << imap.first  << " -> " << imap.second << endl;
        Plotter.MakeAUCHist(AUCValues,"AUC_Summary_"+InDir+"_"+Binlabel,WebSite_Label,InDir+"_"+Binlabel);

      }
    }
  }
  
  return;
}

void IDMVAPlotterCFRun2D(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString InDirDef,TString WebSite_Label){

  vector<TString> eras =  {era};

  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      for (auto PtBin : PtBins){

        TString Binlabel = PtBin+EtaBin;

	map<TString, double> AUCValues;

        for (auto MVAString : MVAStrings){

          HNLPlotter Plotter("IDMVAPlotter");
          Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
          Plotter.CopyToWebsite = true;

          TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	  //vector<TString> SampleList = {}                                                                                                                                                                                                                                                                                                                                                                                                                                            


          vector<TH1D*> vHists;

          TH1D *hist_prompt   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",       InDir + "/Electron/IsPrompt"+Binlabel+"_/"+MVAString);

	  TH1D *hist_prompt_def   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",   InDirDef + "/Electron/IsPrompt"+Binlabel+"_/"+MVAString);


          TH1D *hist_fake     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",         InDir + "/Electron/IsFake"+Binlabel+"_/"+MVAString);
          TH1D *hist_fake_def     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",     InDirDef + "/Electron/IsFake"+Binlabel+"_/"+MVAString);

          TH1D *hist_cf       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_CF.root",                                            InDir + "/Electron/IsPromptCF_IsCF"+Binlabel+"_/"+MVAString);
          TH1D *hist_cf_def       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_CF.root",                                        InDirDef + "/Electron/IsPromptCF_IsCF"+Binlabel+"_/"+MVAString);

          TH1D *hist_conv       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",InDir + "/Electron/IsConv"+Binlabel+"_/"+MVAString);
          TH1D *hist_conv_def       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",InDirDef + "/Electron/IsConv"+Binlabel+"_/"+MVAString);




          TH1D *HNTightPrompt = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "TightID/Electron/IsPrompt"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_Prompt = Plotter.GetCutEfficiency(HNTightPrompt);

          TH1D *HNTightCF  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_CF.root",  "TightID/Electron/IsPromptCF_IsCF"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_CF  = Plotter.GetCutEfficiency(HNTightCF);

          TH1D *HNTightFake  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root", "TightID/Electron/IsFake"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_Fake  = Plotter.GetCutEfficiency(HNTightFake);

          TH1D *HNTightConv  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",  "TightID/Electron/IsConv"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_Conv  = Plotter.GetCutEfficiency(HNTightConv);



          TH1D *hist_Eff = Plotter.GetScanEfficiency2D(hist_prompt, hist_prompt_def);
          hist_Eff->GetYaxis()->SetTitle("Cut Efficiency");
          hist_Eff->GetXaxis()->SetTitle("MVA Score");

          vHists.push_back(hist_Eff);

          TH1D *hist_Eff_CF = Plotter.GetScanEfficiency2D(hist_cf,hist_cf_def);
          TH1D *hist_Eff_Conv = Plotter.GetScanEfficiency2D(hist_conv, hist_conv_def);
          TH1D *hist_Eff_Fake = Plotter.GetScanEfficiency2D(hist_fake,hist_fake_def);
          vHists.push_back(hist_Eff);


          vector<TString> IDs = {"HNTightV2", "HNL_Peking_"+year, "HNL_ULID_"+year};
          vector<TString> Legends = {"Prompt Vs Fake ROC", "POG[T] HNTightV2", "Peking_{2018}", "HNL_{2018} SNU"};

          Plotter.SvsB_Promptpath(path+"/HNL_LeptonIDBDTStudies_Signal.root");
          Plotter.SvsB_Comppath(path+"/HNL_LeptonIDBDTStudies_CF.root");
          Plotter.SvsB_PromptHistPrefix( "TightID/Electron/IsPrompt"+Binlabel+"_/MVA__");
          Plotter.SvsB_CompHistPrefix("TightID/Electron/IsPromptCF_IsCF"+Binlabel+"_/MVA__");


          Plotter.draw_hists_canvas({hist_Eff,          hist_Eff_CF,    hist_Eff_Conv, hist_Eff_Fake,
                hist_CutEff_Prompt,hist_CutEff_CF, hist_CutEff_Conv, hist_CutEff_Fake}, {"Source lep_{Prompt} ","Source lep_{CF}", "Source lep_{Conv} ", "Source lep_{Fake}" ,"#epsilon_{HNTightV2} lep_{Prompt}", "#epsilon_{HNTightV2} lep_{CF}", "#epsilon_{HNTightV2} lep_{Conv}","#epsilon_{HNTightV2} lep_{Fake}"},MVAString+ "_"+ InDir+"_"+Binlabel, WebSite_Label);
	  
          double AUC=Plotter.draw_SvsB_canvas({hist_Eff,hist_Eff_CF},  IDs, Legends , MVAString+"_"+InDir+"_"+Binlabel,WebSite_Label);

	  AUCValues[MVAString] = AUC;

        }//// MVAStrings                                                                                                                                                                     

        HNLPlotter Plotter("IDMVAPlotter");
        Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
        Plotter.CopyToWebsite = true;

        for(auto imap : AUCValues) cout << "AUC results : " << imap.first  << " -> " << imap.second << endl;
        Plotter.MakeAUCHist(AUCValues,"AUC_Summary_"+InDir+"_"+Binlabel,WebSite_Label,InDir+"_"+Binlabel);

      }
    }
  }

  return;
}
