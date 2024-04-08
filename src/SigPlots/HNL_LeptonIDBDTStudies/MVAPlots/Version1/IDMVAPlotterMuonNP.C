#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void IDMVAPlotterMuonNPRun(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label);

void IDMVAPlotterMuonNP(){
  
  vector<TString> Eras = {"2016","2017","2018"};

  vector<TString> MVAStrings = {"MVA__Mu_HF_Fake_POG","MVA__Mu_ED_LF_Fake_v4"};

  vector<TString> PtBins = {"Ptgt200_", "Ptlt200_", "Ptlt15_","Ptlt20_","Ptlt50_"}; 

  TString LabelForWeb = "MuonMVAScoreFake_2023_June30";
  
  for (auto Era : Eras) IDMVAPlotterMuonNPRun(Era ,{"BB","EC"} ,  PtBins, MVAStrings, "SSBDTVariables", LabelForWeb+"_EtaBins_PtBins");

  return;
  for (auto Era : Eras) IDMVAPlotterMuonNPRun(Era ,{"BB"} ,   {""}, MVAStrings, "BDTVariables", LabelForWeb+"_EtaBins");
  for (auto Era : Eras) IDMVAPlotterMuonNPRun(Era ,{"EC"} ,   {""}, MVAStrings, "BDTVariables", LabelForWeb+"_EtaBins");
  
  return;
  //////// SS vs All lep                                                                                                                                                                                                                    
  for (auto Era : Eras) IDMVAPlotterMuonNPRun(Era ,{"BB","EC"} ,   {""}, MVAStrings, "BDTVariables",   LabelForWeb+"_EtaBins_SS");
  for (auto Era : Eras) IDMVAPlotterMuonNPRun(Era ,{"BB","EC"} ,   {""}, MVAStrings, "SSBDTVariables", LabelForWeb+"_EtaBins_SS");


  return;

}


void IDMVAPlotterMuonNPRun(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label){
  
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
	  cout << InDir + "/Muon/IsPrompt"+Binlabel+"_/"+MVAString << endl;
	  TH1D *hist_prompt   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",
						      InDir + "/Muon/IsPrompt"+Binlabel+"_/"+MVAString);
	  
	  cout << InDir + "/Muon/IsPrompt"+Binlabel+"_/"+MVAString << " " << hist_prompt << endl;
	  TH1D *hist_fake     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",
						      InDir + "/Muon/IsFake"+Binlabel+"_/"+MVAString);

	  TH1D *hist_conv       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",
                                                      InDir + "/Muon/IsConv"+Binlabel+"_/"+MVAString);

  
	  TH1D *HNTightPrompt = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "TightID/Muon/IsPrompt"+Binlabel+"_/MVA__HNTightV2");
	  TH1D *hist_CutEff_Prompt = Plotter.GetCutEfficiency(HNTightPrompt);

	  TH1D *HNTightFake  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root", "TightID/Muon/IsFake"+Binlabel+"_/MVA__HNTightV2");
	  TH1D *hist_CutEff_Fake  = Plotter.GetCutEfficiency(HNTightFake);

  
          TH1D *HNTightConv  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",  "TightID/Muon/IsConv"+Binlabel+"_/MVA__HNTightV2");
          TH1D *hist_CutEff_Conv  = Plotter.GetCutEfficiency(HNTightConv);


	  cout << HNTightPrompt << " " << hist_CutEff_Prompt << " " << HNTightFake << " " << hist_CutEff_Fake << endl;
	  
	  TH1D *hist_Eff = Plotter.GetScanEfficiency(hist_prompt);
	  hist_Eff->GetYaxis()->SetTitle("Cut Efficiency");
	  hist_Eff->GetXaxis()->SetTitle("MVA Score");
	  
  
          TH1D *hist_Eff_Conv = Plotter.GetScanEfficiency(hist_conv);
	  TH1D *hist_Eff_Fake = Plotter.GetScanEfficiency(hist_fake);

	  vector<TString> IDs = {"HNTightV2", "HNL_ULID_"+year};
	  vector<TString> Legends = {"Prompt Vs Fake ROC", "POG[T] HNTightV2",  "HNL_{2018} SNU"};
	  
	  Plotter.SvsB_Promptpath(path+"/HNL_LeptonIDBDTStudies_Signal.root");
	  Plotter.SvsB_Comppath(path+"/HNL_LeptonIDBDTStudies_Fake.root");
	  Plotter.SvsB_PromptHistPrefix( "TightID/Muon/IsPrompt"+Binlabel+"_/MVA__");
	  Plotter.SvsB_CompHistPrefix("TightID/Muon/IsFake"+Binlabel+"_/MVA__");
	  
  
	  Plotter.draw_hists_canvas(  {hist_Eff,          hist_Eff_Conv, hist_Eff_Fake,hist_CutEff_Prompt, hist_CutEff_Conv, hist_CutEff_Fake}, 
				      {"Source lep_{Prompt} ", "Source lep_{Conv} ", "Source lep_{Fake}" ,"#epsilon_{HNTightV2} lep_{Prompt}", "#epsilon_{HNTightV2} lep_{Conv}","#epsilon_{HNTightV2} lep_{Fake}"}, 
				      MVAString+ "_"+ InDir+"_"+Binlabel, 
				      WebSite_Label);


	  cout << hist_Eff << " " << hist_Eff_Fake << endl;
	  double AUC= Plotter.draw_SvsB_canvas({hist_Eff,hist_Eff_Fake},  
				   IDs, 
				   Legends , 
				   MVAString+"_"+InDir+"_"+Binlabel,
				   WebSite_Label);
	  
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
  
  //for(auto imap : AUCValues) cout << "AUC results : " << imap.first  << " -> " << imap.second << endl;
  //Plotter.MakeAUCHist(AUCValues);


	  
  
  return;
}

