#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void CompareInputsConfig(TString LabelForWeb, TString reg,TString Era, TString histname, TString axisname,int rebin, double minx, double maxx);

void CompareInputsWithConvBkgEra(  TString Era1);

void CompareInputsWithConvBkg(){
  CompareInputsWithConvBkgEra("2016preVFP");
  CompareInputsWithConvBkgEra("2016postVFP");
  CompareInputsWithConvBkgEra("2016");
  CompareInputsWithConvBkgEra("2017");
  CompareInputsWithConvBkgEra("2018");
}

void CompareInputsWithConvBkgEra(  TString Era1){
  
  TString LabelForWeb = "CompareInputs_2023_Sep6_ElectronPrompt";
  TString LabelForWeb2 = "CompareInputs_2023_Sep6_ElectronPrompt_Var2_";

  LabelForWeb = LabelForWeb + "_ConvFull";
  LabelForWeb2 = LabelForWeb2 + "_ConvFull";

  vector<TString> regs = {"Pt1_Eta1","Pt1_Eta8",//"Pt1_Eta3","Pt1_Eta4","Pt1_Eta5","Pt1_Eta6","Pt1_Eta7","Pt1_Eta8",
                          "Pt2_Eta1","Pt2_Eta8",//"Pt2_Eta3","Pt2_Eta4","Pt2_Eta5","Pt2_Eta6","Pt2_Eta7","Pt2_Eta8",
                          "Pt3_Eta1","Pt3_Eta8"};//"Pt3_Eta3","Pt3_Eta4","Pt3_Eta5","Pt3_Eta6","Pt3_Eta7","Pt3_Eta8",};

  
  for(auto reg : regs){

    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRatio", "PtRatio", 5,0, 1.5);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRel", "PtRel", 5, 0, 100);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRatioV2", "PtRatioV2", 5,0, 1.5);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRelV2", "PtRelV2", 5, 0, 100);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRatioV3", "PtRatioV3", 5,0, 1.5);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PtRelV3", "PtRelV3", 5, 0, 100);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"Pt", "Lepton p_{T} (GeV)", 1, 0, 200);
    CompareInputsConfig(LabelForWeb,reg,Era1,"Eta" ,"Lepton #eta"  ,  1, 0, 2.5);

    CompareInputsConfig(LabelForWeb,reg,Era1,"MiniIsoChHad", "MiniIsoChHad", 1, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MiniIsoNHad", "MiniIsoNHad", 1, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MiniIsoPhHad", "MiniIsoPhHad", 1, 0, 10);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsoChHad", "IsoChHad", 1, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsoNHad", "IsoNHad", 1, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsoPhHad", "IsoPhHad", 1, 0, 10);
   
    CompareInputsConfig(LabelForWeb,reg,Era1,"RelMiniIsoCh", "RelMiniIsoCh", 5, 0, 0.4);
    CompareInputsConfig(LabelForWeb,reg,Era1,"RelMiniIsoN", "RelMiniIsoN", 5, 0, 0.4);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"RelIso", "RelIso", 1, 0,1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"Minireliso", "MiniRelIso", 2, 0,0.4);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"JetDiscCJ", "JetDiscCJ", 4, 0, 1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"JetDiscCJCvsB", "JetDiscCJCvsB", 4, 0, 1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"JetDiscCJCvsL", "JetDiscCJCvsL", 4, 0, 1);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"Full5x5_sigmaIetaIeta" ,"Full5x5_sigmaIetaIeta"  ,  4, 0, 0.035);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"dEtaSeed" ,"dEtaSeed"  ,  2, 0, 0.03);
    CompareInputsConfig(LabelForWeb,reg,Era1,"dPhiIn" , "dPhiIn" ,  2, 0, 0.1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"dEtaIn" , "dEtaIn" ,  2, 0, 0.06);
    CompareInputsConfig(LabelForWeb,reg,Era1,"EtaWidth", "EtaWidth" ,  2, 0, 0.1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"PhiWidth" , "PhiWidth" ,  2, 0, 0.4);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"Dxy" ,"D_{xy}"  ,  1, -12, -2);
    CompareInputsConfig(LabelForWeb,reg,Era1,"DxySig" ,"D_{xy} Sig"  ,  1, -8, 2);
    CompareInputsConfig(LabelForWeb,reg,Era1,"Dz" ,"D_{z}"  ,  1, -12, -2);
    CompareInputsConfig(LabelForWeb,reg,Era1,"DzSig" ,"D_{z} Sig"  ,  1, -8, 2);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IP3D" , "IP3D" ,  2, 0, 5);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MVA" , "MVA" ,  10, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MVAIso" , "MVAIso"  ,  10, 0, 10);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MVARaw" , "MVA" ,  10, 0, 1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MVAIsoRaw" , "MVAIso"  ,  10, 0, 1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"MissingHits" ,"MissingHits"  ,  1, 0, 4);
    CompareInputsConfig(LabelForWeb,reg,Era1,"HoverE", "HoverE" ,  1, 0, 0.2);
    
    CompareInputsConfig(LabelForWeb,reg,Era1,"EoverP" , "EoverP" ,  2, -4, 4);
    CompareInputsConfig(LabelForWeb,reg,Era1,"FBrem" , "FBrem" ,  2, -0.1, 2);
    CompareInputsConfig(LabelForWeb,reg,Era1,"R9" , "R9" ,  1, 0., 1.1);
    CompareInputsConfig(LabelForWeb,reg,Era1,"e55" ,"e55"  ,  1, 0, 1500);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsGsfCtfScPixChargeConsistent" , "IsGsfCtfScPixChargeConsistent"   ,  1, 0, 4);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsGsfScPixChargeConsistent" , "IsGsfScPixChargeConsistent" ,   1, 0, 4);
    CompareInputsConfig(LabelForWeb,reg,Era1,"IsGsfCtfChargeConsistent" ,"IsGsfCtfChargeConsistent"  ,   1, 0, 4);

    
    //    CompareInputsConfig(LabelForWeb2,reg,Era1,"TrkIso", "TrkIso", 1, 0, 5);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"JetDiscCJ2", "JetDiscCJ", 1, 0, 1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"JetDiscCJCvsB2", "JetDiscCJCvsB", 1, 0, 1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"JetDiscCJCvsL2", "JetDiscCJCvsL", 1, 0, 1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"CEMFracCJ", "CEMFracCJ", 1, 0, 1.1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"NEMFracCJ", "NEMFracCJ", 1, 0, 0.5);
    ///CompareInputsConfig(LabelForWeb2,reg,Era1,"CHFracCJ", "CHFracCJ", 1, 0, 0.5);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"NHFracCJ", "NHFracCJ", 1, 0, 0.5);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"EMFracCJ", "EMFracCJ", 1, 0, 1.1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"HFracCJ", "HFracCJ", 1, 0, 1.1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"CHMultCJ", "CHMultCJ", 1, 0, 30);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"NMultCJ", "NMultCJ", 1, 0, 30);
    CompareInputsConfig(LabelForWeb2,reg,Era1,"InvEminusInvP" ,"InvEminusInvP"  ,  1, 0, 0.4);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"hcalPFClusterIso", "hcalPFClusterIso" ,  2, 0, 0.5);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"ecalPFClusterIso" ,"ecalPFClusterIso"  ,  2, 0, 0.5);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"dr03TkSumPt" ,"dr03TkSumPt"  ,  1, 0, 0.1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"e2x5OverE5x5" , "e2x5OverE5x5" ,  2, 0, 1.1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"e1x5OverE5x5" , "e1x5OverE5x5" ,  2, -0.5, 1);
    //CompareInputsConfig(LabelForWeb2,reg,Era1,"Full5x5_sigmaIetaIeta" ,"Full5x5_sigmaIetaIeta"  ,  1, 0, 0.035);
  }


}

void CompareInputsConfig(TString LabelForWeb,TString reg,TString Era1,  TString histname, TString axisname, int rebin, double minx, double maxx){
  
  cout << histname << endl;
  
  HNLPlotter Plotter("CompareInputs");
  Plotter.SetupPlotter(Era1,"","HNL_LeptonID_BDT_KinVar");
  Plotter.CopyToWebsite = true;
  
  TString path1="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ControlRegionPlotter/MVA/"+Era1+"/HNL_ControlRegionPlotter_SkimTree_DileptonBDT_SingleElectron.root";
  TString path2="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ControlRegionPlotter/MVA/"+Era1+"/HNL_ControlRegionPlotter_SkimTree_DileptonBDT_DYJets.root";
  TString path3="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_ControlRegionPlotter/MVA/"+Era1+"/HNL_LeptonIDBDTStudies_SkimTree_ConvEventSkim.root";


  TH1D *hist_1     = Plotter.ConstructHist(path1,  reg+"/Lepton_bdt_id_"+histname);
  TH1D *hist_2     = Plotter.ConstructHist(path2,  reg+"/Lepton_bdt_id_"+histname);
  TH1D *hist_3     = Plotter.ConstructHist(path3,  "Conv/"+reg+"/Lepton_bdt_id_"+histname);

  hist_1->Rebin(rebin);
  hist_2->Rebin(rebin);
  hist_3->Rebin(rebin);

  double M1=hist_1->GetMean();
  double M2=hist_2->GetMean();
  double ST1=hist_1->GetStdDev();
  double ST2=hist_2->GetStdDev();
  
  hist_1->Scale(1./hist_1->Integral());
  hist_2->Scale(1./hist_2->Integral());
  hist_3->Scale(1./hist_3->Integral());
  hist_1->GetXaxis()->SetTitle(axisname);
  hist_1->GetXaxis()->SetRangeUser(minx,maxx);
  TString scale1=Era1 + "Zeak Data/MC Mean=" + TString(DToString(M1/M2,4)) + " std. " + TString(DToString(ST1/ST2,4));

  
  Plotter.SaveHistsWithRatio({hist_1,hist_2,hist_3}, {"Data","DY","Conv"},Era1+"_"+reg+"_"+histname,LabelForWeb, {scale1});
  
  
  return;
}

