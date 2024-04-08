#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void IDEffByTypePlotterMuon(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label);
void IDEffByTypePlotterMuon2D(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString InDirDef, TString WebSite_Label);

void IDMVAPlotterMuonPtEff(){
  
  vector<TString> Eras = {"2018"};

  vector<TString> MVAStrings = {"HNTightV2","HNL_Peking","HNTight_17028","HNL_HN3L","HNL_ULID_LF","HNL_ULID_2018", "HNL_HF_v1","HNL_HF_v2","HNL_HF_v3","HNL_HF_v4", "HNL_LF_v1","HNL_LF_v2","HNL_LF_v3","HNL_LF_v4"};

  vector<TString> PtBins = {"Ptgt100_", "Ptlt100_", "Ptlt15_","Ptlt20_","Ptlt50_"}; 

  TString LabelForWeb = "MVAScoreFake_2023_July2_Ratio";
  
  for (auto Era : Eras) IDEffByTypePlotterMuon(Era ,{"BB","EC"} ,   {""}, MVAStrings, "BDTVariables", LabelForWeb+"_Standard");
  

}


void IDEffByTypePlotterMuon(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString WebSite_Label){
  
  vector<TString> eras =  {era};

  
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      for (auto PtBin : PtBins){

	TString Binlabel = PtBin+EtaBin;
	
	map<TString, double> AUCValues;  
	for (auto MVAString : MVAStrings){
	  
	  HNLPlotter Plotter("IDEffPlotter");
	  Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
	  Plotter.CopyToWebsite = true;
	  
	  TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	  
	  
	  TH1D *Prompt_n = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsPrompt"+EtaBin+"_/MVA__"+MVAString);
	  TH1D *Prompt_d = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsPrompt"+EtaBin+"_/MVA__denominator");
	  Prompt_n->Divide(Prompt_d);
	  
	  TH1D *Conv_n = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsConv"+EtaBin+"_/MVA__"+MVAString);
          TH1D *Conv_d = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsConv"+EtaBin+"_/MVA__denominator");
          Conv_n->Divide(Conv_d);
	  
	  
          TH1D *Fake_n = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsFake"+EtaBin+"_/MVA__"+MVAString);
          TH1D *Fake_d = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsFake"+EtaBin+"_/MVA__denominator");
          Fake_n->Divide(Fake_d);


          TH1D *Prompt_cn = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsPrompt"+EtaBin+"_/MVA__"+MVAString);
          TH1D *Prompt_cd = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsPrompt"+EtaBin+"_/MVA__HNTightV2");                                                                  
          Prompt_cn->Divide(Prompt_cd);

          TH1D *Conv_cn = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsConv"+EtaBin+"_/MVA__"+MVAString);
          TH1D *Conv_cd = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsConv"+EtaBin+"_/MVA__HNTightV2");
          Conv_cn->Divide(Conv_cd);


          TH1D *Fake_cn = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsFake"+EtaBin+"_/MVA__"+MVAString);
	  TH1D *Fake_cd = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "IDEff/MuonPtbinned_IsFake"+EtaBin+"_/MVA__HNTightV2");
          Fake_cn->Divide(Fake_cd);



	  for(unsigned int i=1; i < Prompt_cn->GetNbinsX()+1; i++) Prompt_cn->SetBinError(i,0);
	  for(unsigned int i=1; i < Conv_cn->GetNbinsX()+1; i++) Conv_cn->SetBinError(i,0);
	  for(unsigned int i=1; i < Fake_cn->GetNbinsX()+1; i++) Fake_cn->SetBinError(i,0);

	  
	  //Plotter.draw_hists_canvas_pt(  {Prompt_n ,  Conv_n,Fake_n},
	  //					 {"Source lep_{Prompt} ", "Source lep_{Conv} ", "Source lep_{Fake}" },
	  //					 MVAString+ "_"+ InDir+"_"+Binlabel,//
	  //					 WebSite_Label);

          Plotter.draw_hists_canvas_pt(  {Prompt_cn ,  Conv_cn,Fake_cn},
                                         {"Source lep_{Prompt} ", "Source lep_{Conv} ", "Source lep_{Fake}" },
                                         MVAString+ "_"+ InDir+"_"+Binlabel,
                                         WebSite_Label+"_vsPOG");
	  
	    
	}//// MVAStrings	

      }
    }
  }
  
  //for(auto imap : AUCValues) cout << "AUC results : " << imap.first  << " -> " << imap.second << endl;
  //Plotter.MakeAUCHist(AUCValues);


	  
  
  return;
}

void IDEffByTypePlotterMuon2D(TString era, vector<TString>  EtaBins,vector<TString> PtBins,vector<TString> MVAStrings,TString InDir, TString InDirDef,TString WebSite_Label){

  vector<TString> eras =  {era};

  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      for (auto PtBin : PtBins){

        TString Binlabel = PtBin+EtaBin;

        map<TString, double> AUCValues;

        for (auto MVAString : MVAStrings){

          HNLPlotter Plotter("IDEffPlotter");
          Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
          Plotter.CopyToWebsite = true;

          TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDBDTStudies/"+year;
	  //vector<TString> SampleList = {}                                                                                                                                                                                                                                                                                                                                                                                                                                            



          TH1D *hist_prompt   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",       InDir + "/Muon/IsPrompt"+Binlabel+"_/"+MVAString);

	  TH1D *hist_prompt_def   = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root",   InDirDef + "/Muon/IsPrompt"+Binlabel+"_/"+MVAString);


          TH1D *hist_fake     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",         InDir + "/Muon/IsFake"+Binlabel+"_/"+MVAString);
          TH1D *hist_fake_def     = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root",     InDirDef + "/Muon/IsFake"+Binlabel+"_/"+MVAString);

          TH1D *hist_conv       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",InDir + "/Muon/IsConv"+Binlabel+"_/"+MVAString);
          TH1D *hist_conv_def       = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",InDirDef + "/Muon/IsConv"+Binlabel+"_/"+MVAString);




          TH1D *HNTightPrompt = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Signal.root", "TightID/Muon/IsPrompt"+Binlabel+"_/MVA__"+MVAString);
          TH1D *hist_CutEff_Prompt = Plotter.GetCutEfficiency(HNTightPrompt);

          TH1D *HNTightFake  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Fake.root", "TightID/Muon/IsFake"+Binlabel+"_/MVA__"+MVAString);
          TH1D *hist_CutEff_Fake  = Plotter.GetCutEfficiency(HNTightFake);

          TH1D *HNTightConv  = Plotter.ConstructHist(path+"/HNL_LeptonIDBDTStudies_Conv.root",  "TightID/Muon/IsConv"+Binlabel+"_/MVA__"+MVAString);
          TH1D *hist_CutEff_Conv  = Plotter.GetCutEfficiency(HNTightConv);



          TH1D *hist_Eff = Plotter.GetScanEfficiency2D(hist_prompt, hist_prompt_def);
          hist_Eff->GetYaxis()->SetTitle("Cut Efficiency");
          hist_Eff->GetXaxis()->SetTitle("MVA Score");


          TH1D *hist_Eff_Conv = Plotter.GetScanEfficiency2D(hist_conv, hist_conv_def);
          TH1D *hist_Eff_Fake = Plotter.GetScanEfficiency2D(hist_fake,hist_fake_def);


          vector<TString> IDs = {"HNTightV2", "HNL_Peking", "HNL_HN3L",  "HNL_ULID_2018", "HNL_ULID_LF"};
          vector<TString> Legends = {"Prompt Vs Fake ROC","POG[T] HNTightV2", "Peking", "Top MVA", "HNL_{2018} SNU","HNL_ULID_LF"};


          Plotter.SvsB_Promptpath(path+"/HNL_LeptonIDBDTStudies_Signal.root");
          Plotter.SvsB_Comppath(path+"/HNL_LeptonIDBDTStudies_Fake.root");
          Plotter.SvsB_PromptHistPrefix( "TightID/Muon/IsPrompt"+Binlabel+"_/MVA__");
          Plotter.SvsB_CompHistPrefix("TightID/Muon/IsFake"+Binlabel+"_/MVA__");


          Plotter.draw_hists_canvas({hist_Eff,            hist_Eff_Conv, hist_Eff_Fake,
                hist_CutEff_Prompt, hist_CutEff_Conv, hist_CutEff_Fake}, {"Source lep_{Prompt} ", "Source lep_{Conv} ", "Source lep_{Fake}" ,"#epsilon_{HNTightV2} lep_{Prompt}", "#epsilon_{HNTightV2} lep_{Conv}","#epsilon_{HNTightV2} lep_{Fake}"},MVAString+ "_"+ InDir+"_"+Binlabel, WebSite_Label);

	  double AUC=     Plotter.draw_SvsB_canvas({hist_Eff,hist_Eff_Fake},  IDs, Legends , MVAString+"_"+InDir+"_"+Binlabel,WebSite_Label);

	  AUCValues[MVAString] = AUC;

        }//// MVAStrings                                                                                                                                                                                                                    

        HNLPlotter Plotter("IDEffPlotter");
        Plotter.SetupPlotter(year,"","HNL_LeptonIDBDTStudies");
        Plotter.CopyToWebsite = true;

        for(auto imap : AUCValues) cout << "AUC results : " << imap.first  << " -> " << imap.second << endl;
        Plotter.MakeAUCHist(AUCValues,"AUC_Summary_"+InDir+"_"+Binlabel,WebSite_Label,InDir+"_"+Binlabel);

      }
    }
  }

  return;
}
