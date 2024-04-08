#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void CompareInputsPrompt(TString era1, TString era2, TString histname);

void CompareInputsPrompt(){

    vector<TString> HistNames = {"pt","Eta","Dxy","DxySig","Dz","DzSig","IP3D","MVA","MVAIso","Full5x5_sigmaIetaIeta","dPhiIn","EoverP","FBrem","R9","e55","EtaWidth","PhiWidth","PassConversionVeto","IsGsfCtfScPixChargeConsistent","IsGsfScPixChargeConsistent","IsGsfCtfChargeConsistent","InvEminusInvP","hcalPFClusterIso","ecalPFClusterIso","dr03TkSumPt","HoverE","MissingHits", "MiniIsoChHad", "MiniIsoNHad", "MiniIsoPhHad", "RelMiniIsoCh",  "RelMiniIsoN", "IsoChHad", "IsoPhHad",  "RelIso",  "RelIP3D",  "PtRatio",  "PtRel",  "CEMFracCJ",  "NEMFracCJ",  "CHFracCJ",  "NHFracCJ",  "MuFracCJ",  "JetDiscCJ",  "dEtaSeed",  "dEtaIn",  "TrkIso",  "e2x5OverE5x5"};

  for(auto HistName : HistNames) CompareInputsPrompt("SKIM200_2016preVFP","SKIM200_2016postVFP", HistName);


}

void CompareInputsPrompt(TString Era1, TString Era2, TString histname){
  

  TString LabelForWeb = "CompareInputs_2023_July4_ElectronPrompt_Pt200_2016a_b";
  
  
  HNLPlotter Plotter("CompareInputsCF");
  Plotter.SetupPlotter("None","","HNL_LeptonID_BDT_KinVar");
  Plotter.CopyToWebsite = true;
  //HNL_LeptonID_BDT_KinVar_Prompt_SKIM200_2017
  TString path1="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+Era1+".root";
  TString path2="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+Era2+".root";

  TH1D *hist_1     = Plotter.ConstructHist(path1,  "h_"+histname);
  
  TH1D *hist_2     = Plotter.ConstructHist(path2,  "h_"+histname);

  hist_1->Rebin(4);
  hist_2->Rebin(4);

  hist_1->Scale(1./hist_1->Integral());
  hist_2->Scale(1./hist_2->Integral());
  //hist_1->Divide(hist_2);
  Plotter.SaveHists({hist_1,hist_2}, {Era1,Era2},Era1+"_"+Era2+"_"+histname, LabelForWeb,{});
  
  
  return;
}

