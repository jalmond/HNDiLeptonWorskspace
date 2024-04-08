#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void CompareInputsConfig(TString LabelForWeb, TString File1, TString File2,TString Eras1, TString Era2, TString histname, TString axisname,int rebin, double minx, double maxx);

void CompareInputsGeneral(){

  vector<TString> Eras1 = {"Prompt_SKIM100_2017"};
  vector<TString> Eras2 = {"Prompt_SKIM200_2017"};

  TString LabelForWeb = "CompareInputs_2023_July4_ElectronFakevsPrompt";
  
  for(unsigned int i=0 ; i < Eras1.size();  i++){

    TString Dir1="PromptFiles";
    TString Dir2="PromptFiles";
    
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"pt", "Lepton p_{T} (GeV)", 1, 0, 200);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"Eta" ,"Lepton #eta"  ,  1, 0, 2.5);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"Dxy" ,"D_{xy}"  ,  1, -12, 0);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"DxySig" ,"D_{xy} Sig"  ,  1, -8, 5);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"Dz" ,"D_{z}"  ,  1, -12, 0);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"DzSig" ,"D_{z} Sig"  ,  1, -8, 5);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IP3D" , "IP3D" ,  1, 0, 8);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MVA" , "MVA" ,  2, -10, 10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MVAIso" , "MVAIso"  ,  2, -10, 10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"Full5x5_sigmaIetaIeta" ,"Full5x5_sigmaIetaIeta"  ,  1, 0, 0.035);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"dPhiIn" , "dPhiIn" ,  1, -0.12, 0.12);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"EoverP" , "EoverP" ,  1, -2, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"FBrem" , "FBrem" ,  1, -1.2, 1.2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"R9" , "R9" ,  1, 0.2, 1);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"e55" ,"e55"  ,  1, 0, 1500);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"EtaWidth", "EtaWidth" ,  1, 0, 0.1);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"PhiWidth" , "PhiWidth" ,  1, 0, 0.2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"PassConversionVeto" ,"PassConversionVeto"  ,  1, 0, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IsGsfCtfScPixChargeConsistent" , "IsGsfCtfScPixChargeConsistent"   ,  1, 0, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IsGsfScPixChargeConsistent" , "IsGsfScPixChargeConsistent" ,   1, 0, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IsGsfCtfChargeConsistent" ,"IsGsfCtfChargeConsistent"  ,   1, 0, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"InvEminusInvP" ,"InvEminusInvP"  ,  1, 0, 0.2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"hcalPFClusterIso", "hcalPFClusterIso" ,  1, 0, 0.3);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"ecalPFClusterIso" ,"ecalPFClusterIso"  ,  1, 0, 0.15);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"dr03TkSumPt" ,"dr03TkSumPt"  ,  1, 0, 0.1);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"HoverE", "HoverE" ,  1, 0, 0.2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MissingHits" ,"MissingHits"  ,  1, 0, 4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MiniIsoChHad","MiniIsoChHad", 1,0,10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MiniIsoNHad","MiniIsoNHad", 1,0,10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MiniIsoPhHad","MiniIsoPhHad", 1,0,10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"RelMiniIsoCh","RelMiniIsoCh", 1,0,0.4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"RelMiniIsoN","RelMiniIsoN", 1,0,0.4);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IsoChHad","IsoChHad", 1,0,10);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"IsoPhHad","IsoPhHad", 1,0,10);

    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"RelIso","RelIso", 1,0,0.5);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"RelIP3D","RelIP3D", 1,0,0.5);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"PtRatio","PtRatio", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"PtRel","PtRel", 1,0,200);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"CEMFracCJ","CEMFracCJ", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"NEMFracCJ","NEMFracCJ", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"CHFracCJ","CHFracCJ", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"NHFracCJ","NHFracCJ", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"MuFracCJ","MuFracCJ", 1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"JetDiscCJ","JetDiscCJ",1,0,2);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"dEtaSeed","dEtaSeed", 1,-0.04,0.04);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"dEtaIn","dEtaIn", 1,-0.04,0.04);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"TrkIso","TrkIso", 1,0,1);
    CompareInputsConfig(LabelForWeb, Dir1,Dir2,Eras1[i], Eras2[i],"e2x5OverE5x5","e2x5OverE5x5", 1,0,1.2);

  }
}

void CompareInputsConfig(TString LabelForWeb,TString File1, TString File2,TString Era1, TString Era2, TString histname, TString axisname, int rebin, double minx, double maxx){
  

  
  HNLPlotter Plotter("CompareInputs");
  Plotter.SetupPlotter(Era1+Era2,"","HNL_LeptonID_BDT_KinVar");
  Plotter.CopyToWebsite = true;
  
  TString path1=File1+"/HNL_LeptonID_BDT_KinVar_"+Era1+".root";
  TString path2=File2+"/HNL_LeptonID_BDT_KinVar_"+Era2+".root";


  TH1D *hist_1     = Plotter.ConstructHist(path1,  "h_"+histname);
  TH1D *hist_2     = Plotter.ConstructHist(path2,  "h_"+histname);

  hist_1->Rebin(rebin);
  hist_2->Rebin(rebin);

  double int1=hist_1->Integral();
  double int2=hist_2->Integral();

  hist_1->Scale(1./hist_1->Integral());
  hist_2->Scale(1./hist_2->Integral());
  hist_1->GetXaxis()->SetTitle(axisname);
  hist_1->GetXaxis()->SetRangeUser(minx,maxx);
  Plotter.SaveHists({hist_1,hist_2}, {Era1,Era2},Era1+Era2 +"_"+histname,LabelForWeb, {});
  
  
  return;
}

