TString axisname#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void CompareInputsCF(TString era1, TString era2, TString histname, TString axisname,TString SKIM, int rebin, double minx, double maxx);
void CompareInputsCFConfig(TString HistName, TString axisname, int rebin, double minx, double maxx);

void CompareInputsCFSkim(){
  
  CompareInputsCFConfig("pt", "Lepton p_{T} (GeV)", 2, 0, 200);
  CompareInputsCFConfig("Eta" ,"Lepton #eta"  ,  2, 0, 2.5);
  CompareInputsCFConfig("Dxy" ,"D_{xy}"  ,  2, -12, 0);
  CompareInputsCFConfig("DxySig" ,"D_{xy} Sig"  ,  2, -8, 5);
  CompareInputsCFConfig("Dz" ,"D_{z}"  ,  2, -12, 0);
  CompareInputsCFConfig("DzSig" ,"D_{z} Sig"  ,  2, -8, 5);
  CompareInputsCFConfig("IP3D" , "IP3D" ,  2, 0, 8);
  CompareInputsCFConfig("MVA" , "MVA" ,  2, 0, 1);
  CompareInputsCFConfig("MVAIso" , "MVAIso"  ,  2, 0, 1);
  CompareInputsCFConfig("Full5x5_sigmaIetaIeta" ,"Full5x5_sigmaIetaIeta"  ,  2, 0, 0.035);
  CompareInputsCFConfig("dPhiIn" , "dPhiIn" ,  2, -0.12, 0.12);
  CompareInputsCFConfig("EoverP" , "EoverP" ,  2, -2, 4);
  CompareInputsCFConfig("FBrem" , "FBrem" ,  2, -1.2, 1.2);
  CompareInputsCFConfig("R9" , "R9" ,  2, 0.2, 1);
  CompareInputsCFConfig("e55" ,"e55"  ,  2, 0, 1500);
  CompareInputsCFConfig("EtaWidth", "EtaWidth" ,  2, 0, 0.1);
  CompareInputsCFConfig("PhiWidth" , "PhiWidth" ,  2, 0, 0.2);
  CompareInputsCFConfig("PassConversionVeto" ,"PassConversionVeto"  ,  1, 0, 4);
  CompareInputsCFConfig("IsGsfCtfScPixChargeConsistent" , "IsGsfCtfScPixChargeConsistent"   ,  1, 0, 4);
  CompareInputsCFConfig("IsGsfScPixChargeConsistent" , "IsGsfScPixChargeConsistent" ,   1, 0, 4);
  CompareInputsCFConfig("IsGsfCtfChargeConsistent" ,"IsGsfCtfChargeConsistent"  ,   1, 0, 4);
  CompareInputsCFConfig("InvEminusInvP" ,"InvEminusInvP"  ,  2, 0, 0.2);
  CompareInputsCFConfig("hcalPFClusterIso", "hcalPFClusterIso" ,  2, 0, 0.3);
  CompareInputsCFConfig("ecalPFClusterIso" ,"ecalPFClusterIso"  ,  2, 0, 0.15);
  CompareInputsCFConfig("dr03TkSumPt" ,"dr03TkSumPt"  ,  2, 0, 0.1);
  CompareInputsCFConfig("HoverE", "HoverE" ,  2, 0, 0.2);
  CompareInputsCFConfig("MissingHits" ,"MissingHits"  ,  1, 0, 4);
}
void CompareInputsCFConfig(TString HistName, TString axisname, int rebin, double minx, double maxx){

  CompareInputsCF("2016","2017", HistName, axisname, "SKIM30_",rebin,minx,maxx);
  CompareInputsCF("2016","2017", HistName, axisname, "SKIM40_",rebin,minx,maxx);
  CompareInputsCF("2016","2017", HistName, axisname, "SKIM50_",rebin,minx,maxx);
  CompareInputsCF("2016","2017", HistName, axisname, "SKIM60_",rebin,minx,maxx);
  
}

void CompareInputsCF(TString Era1, TString Era2, TString histname, TString axisname, TString SKIM, int rebin, double minx, double maxx){
  

  TString LabelForWeb = "CompareInputsCF_2023_July4_ElectronCFSkim";
  
  
  HNLPlotter Plotter("CompareInputsCF");
  Plotter.SetupPlotter(Era1+"_"+Era2,"","HNL_LeptonID_BDT_KinVar");
  Plotter.CopyToWebsite = true;
  
  TString path1="CFFiles/HNL_LeptonID_BDT_KinVar_CFBkg_"+SKIM+Era1+".root";
  TString path2="CFFiles/HNL_LeptonID_BDT_KinVar_CFBkg_"+SKIM+Era2+".root";
  TString path3="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+SKIM+Era1+".root";
  TString path4="PromptFiles/HNL_LeptonID_BDT_KinVar_Prompt_"+SKIM+Era2+".root";


  TH1D *hist_1     = Plotter.ConstructHist(path1,  "h_"+histname);
  TH1D *hist_2     = Plotter.ConstructHist(path2,  "h_"+histname);
  TH1D *hist_3     = Plotter.ConstructHist(path3,  "h_"+histname);
  TH1D *hist_4     = Plotter.ConstructHist(path4,  "h_"+histname);

  hist_1->Rebin(rebin);
  hist_2->Rebin(rebin);
  hist_3->Rebin(rebin);
  hist_4->Rebin(rebin);

  hist_1->GetXaxis()->SetTitle(axisname);
  hist_2->GetXaxis()->SetTitle(axisname);
  hist_3->GetXaxis()->SetTitle(axisname);
  hist_1->GetXaxis()->SetRangeUser(minx,maxx);
  hist_1->Scale(1./hist_1->Integral());
  hist_2->Scale(1./hist_2->Integral());
  hist_3->Scale(1./hist_3->Integral());
  hist_4->Scale(1./hist_4->Integral());
  //hist_1->Divide(hist_2);
  Plotter.SaveHists({hist_1,hist_2,hist_3,hist_4}, {"CF_"+Era1,"CF_"+Era2,"Prompt_16","Prompt_17"},Era1+"_"+Era2+"_"+histname+SKIM, LabelForWeb);
  
  
  return;
}

