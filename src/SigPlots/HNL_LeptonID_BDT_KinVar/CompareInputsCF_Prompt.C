#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void CompareInputsCFConfig(TString LabelForWeb, TString Era1, TString Era2, TString Era3, TString histname, TString axisname,int rebin, double minx, double maxx);

void CompareInputsCF_Prompt(){

  TString Era1="2016";
  TString Era2="2017";
  TString Era3="2018";

  TString LabelForWeb = "CompareInputsCF_2023_July4_ElectronPrompt";
  
  LabelForWeb = LabelForWeb + "_CFvsCF";
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"pt", "Lepton p_{T} (GeV)", 1, 0, 200);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"Eta" ,"Lepton #eta"  ,  1, 0, 2.5);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"Dxy" ,"D_{xy}"  ,  1, -12, 0);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"DxySig" ,"D_{xy} Sig"  ,  1, -8, 5);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"Dz" ,"D_{z}"  ,  1, -12, 0);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"DzSig" ,"D_{z} Sig"  ,  1, -8, 5);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"IP3D" , "IP3D" ,  1, 0, 8);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"MVA" , "MVA" ,  1, 0, 1);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"MVAIso" , "MVAIso"  ,  1, 0, 1);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"Full5x5_sigmaIetaIeta" ,"Full5x5_sigmaIetaIeta"  ,  1, 0, 0.035);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"dPhiIn" , "dPhiIn" ,  1, -0.12, 0.12);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"EoverP" , "EoverP" ,  1, -2, 4);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"FBrem" , "FBrem" ,  1, -1.2, 1.2);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"R9" , "R9" ,  1, 0.2, 1);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"e55" ,"e55"  ,  1, 0, 1500);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"EtaWidth", "EtaWidth" ,  1, 0, 0.1);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"PhiWidth" , "PhiWidth" ,  1, 0, 0.2);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"PassConversionVeto" ,"PassConversionVeto"  ,  1, 0, 4);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"IsGsfCtfScPixChargeConsistent" , "IsGsfCtfScPixChargeConsistent"   ,  1, 0, 4);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"IsGsfScPixChargeConsistent" , "IsGsfScPixChargeConsistent" ,   1, 0, 4);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"IsGsfCtfChargeConsistent" ,"IsGsfCtfChargeConsistent"  ,   1, 0, 4);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"InvEminusInvP" ,"InvEminusInvP"  ,  1, 0, 0.2);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"hcalPFClusterIso", "hcalPFClusterIso" ,  1, 0, 0.3);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"ecalPFClusterIso" ,"ecalPFClusterIso"  ,  1, 0, 0.15);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"dr03TkSumPt" ,"dr03TkSumPt"  ,  1, 0, 0.1);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"HoverE", "HoverE" ,  1, 0, 0.2);
  CompareInputsCFConfig(LabelForWeb,Era1,Era2,Era3,"MissingHits" ,"MissingHits"  ,  1, 0, 4);

}

void CompareInputsCFConfig(TString LabelForWeb,TString Era1, TString Era2, TString Era3,  TString histname, TString axisname, int rebin, double minx, double maxx){
  

  
  HNLPlotter Plotter("CompareInputsPrompt");
  Plotter.SetupPlotter(Era1+"vs"+Era2+"vs"+Era3,"","HNL_LeptonID_BDT_KinVar");
  Plotter.CopyToWebsite = true;
  
  TString path1="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+Era1+".root";
  TString path2="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+Era2+".root";
  TString path3="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+Era3+".root";

  TH1D *hist_1     = Plotter.ConstructHist(path1,  "h_"+histname);
  TH1D *hist_2     = Plotter.ConstructHist(path2,  "h_"+histname);
  TH1D *hist_3     = Plotter.ConstructHist(path3,  "h_"+histname);

  hist_1->Rebin(rebin);
  hist_2->Rebin(rebin);
  hist_3->Rebin(rebin);

  double int1=hist_1->Integral();
  double int2=hist_2->Integral();
  double int3=hist_3->Integral();

  hist_1->Scale(1./hist_1->Integral());
  hist_2->Scale(1./hist_2->Integral());
  hist_3->Scale(1./hist_3->Integral());
  hist_1->GetXaxis()->SetTitle(axisname);
  hist_1->GetXaxis()->SetRangeUser(minx,maxx);
  TString scale1=Era1 + " scale=" + TString(DToString(int1,0));
  TString scale2=Era2 + " scale=" + TString(DToString(int2,0));
  TString scale3=Era3 + " scale=" + TString(DToString(int3,0));
  Plotter.SaveHists({hist_1,hist_2,hist_3}, {Era1,Era2,Era3},Era1+"_"+Era2+"_"+Era3+"_"+histname,LabelForWeb, {scale1,scale2,scale3});
  
  
  return;
}

