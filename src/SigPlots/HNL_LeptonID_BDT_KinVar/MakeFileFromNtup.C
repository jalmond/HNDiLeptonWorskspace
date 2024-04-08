#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeFileFromNtupRun(TString input_path, TString OUTNAME);


void MakeFileFromNtup(){

  vector<TString> Eras = {"2017","2018", "2016", "2016postVFP","2016preVFP"};
  
  vector<TString> Samples = {"FakeBkg","FakeConv","FakeCF","Prompt"};
  
  for(auto Era : Eras)   MakeFileFromNtupRun("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version3/"+Era+"/HNL_LeptonID_BDT_KinVar_FakeBkg.root", "HNL_LeptonID_BDT_KinVar_FakeBkg_"+Era+".root");
  for(auto Era : Eras)   MakeFileFromNtupRun("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version2/"+Era+"/HNL_LeptonID_BDT_KinVar_CFBkg.root", "HNL_LeptonID_BDT_KinVar_CFBkg_"+Era+".root");
  for(auto Era : Eras)   MakeFileFromNtupRun("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version3/"+Era+"/HNL_LeptonID_BDT_KinVar_ConvBkg.root", "HNL_LeptonID_BDT_KinVar_ConvBkg_"+Era+".root");
  for(auto Era : Eras)   MakeFileFromNtupRun("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version3/"+Era+"/HNL_LeptonID_BDT_KinVar_Prompt.root", "HNL_LeptonID_BDT_KinVar_Prompt_"+Era+".root");
  
}


void MakeFileFromNtupRun(TString input_path,TString OUTNAME){
 
 
  Float_t         Pt;
  Float_t         PtBinned;
  Float_t         Eta;
  Float_t         PileUp;
  Float_t         MiniIsoChHad;
  Float_t         MiniIsoNHad;
  Float_t         MiniIsoPhHad;
  Float_t         RelMiniIsoCh;
  Float_t         RelMiniIsoN;
  Float_t         IsoChHad;
  Float_t         IsoNHad;
  Float_t         IsoPhHad;
  Float_t         Dxy;
  Float_t         RelDxy;
  Float_t         DxySig;
  Float_t         Dz;
  Float_t         RelDz;
  Float_t         DzSig;
  Float_t         RelIso;
  Float_t         IP3D;
  Float_t         RelIP3D;
  Float_t         MVA;
  Float_t         RelMVA;
  Float_t         MVAIso;
  Float_t         RelMVAIso;
  Float_t         POGTight;
  Float_t         POGMedium;
  Float_t         HNTightID;
  Float_t         PtRatio;
  Float_t         PtRel;
  Float_t         MassDrop;
  Float_t         CEMFracCJ;
  Float_t         NEMFracCJ;
  Float_t         CHFracCJ;
  Float_t         NHFracCJ;
  Float_t         MuFracCJ;
  Float_t         JetDiscCJ;
  Float_t         MissingHits;
  Float_t         Full5x5_sigmaIetaIeta;
  Float_t         dEtaSeed;
  Float_t         dPhiIn;
  Float_t         dEtaIn;
  Float_t         HoverE;
  Float_t         TrkIso;
  Float_t         isEcalDriven;
  Float_t         EoverP;
  Float_t         FBrem;
  Float_t         InvEminusInvP;
  Float_t         PassConversionVeto;
  Float_t         ecalPFClusterIso;
  Float_t         hcalPFClusterIso;
  Float_t         IsGsfCtfScPixChargeConsistent;
  Float_t         IsGsfScPixChargeConsistent;
  Float_t         IsGsfCtfChargeConsistent;
  Float_t         EtaWidth;
  Float_t         PhiWidth;
  Float_t         e2x5OverE5x5;
  Float_t         e1x5OverE5x5;
  Float_t         e15;
  Float_t         e25;
  Float_t         e55;
  Float_t         dr03EcalRecHitSumEt;
  Float_t         dr03HcalDepth1TowerSumEt;
  Float_t         dr03HcalTowerSumEt;
  Float_t         dr03TkSumPt;
  Float_t         R9;
  Float_t         w_id_tot;
  TBranch        *b_Pt;   //!
  TBranch        *b_PtBinned;   //!
  TBranch        *b_Eta;   //!
  TBranch        *b_PileUp;   //!
  TBranch        *b_MiniIsoChHad;   //!
  TBranch        *b_MiniIsoNHad;   //!
  TBranch        *b_MiniIsoPhHad;   //!
  TBranch        *b_RelMiniIsoCh;   //!
  TBranch        *b_RelMiniIsoN;   //!
  TBranch        *b_IsoChHad;   //!
  TBranch        *b_IsoNHad;   //!
  TBranch        *b_IsoPhHad;   //!
  TBranch        *b_Dxy;   //!
  TBranch        *b_RelDxy;   //!
  TBranch        *b_DxySig;   //!
  TBranch        *b_Dz;   //!
  TBranch        *b_RelDz;   //!
  TBranch        *b_DzSig;   //!
  TBranch        *b_RelIso;   //!
  TBranch        *b_IP3D;   //!
  TBranch        *b_RelIP3D;   //!
  TBranch        *b_MVA;   //!
  TBranch        *b_RelMVA;   //!
  TBranch        *b_MVAIso;   //!
  TBranch        *b_RelMVAIso;   //!
  TBranch        *b_POGTight;   //!
  TBranch        *b_POGMedium;   //!
  TBranch        *b_HNTightID;   //!
  TBranch        *b_PtRatio;   //!
  TBranch        *b_PtRel;   //!
  TBranch        *b_MassDrop;   //!
  TBranch        *b_CEMFracCJ;   //!
  TBranch        *b_NEMFracCJ;   //!
  TBranch        *b_CHFracCJ;   //!
  TBranch        *b_NHFracCJ;   //!
  TBranch        *b_MuFracCJ;   //!
  TBranch        *b_JetDiscCJ;   //!
  TBranch        *b_MissingHits;   //!
  TBranch        *b_Full5x5_sigmaIetaIeta;   //!
  TBranch        *b_dEtaSeed;   //!
  TBranch        *b_dPhiIn;   //!
  TBranch        *b_dEtaIn;   //!
  TBranch        *b_HoverE;   //!
  TBranch        *b_TrkIso;   //!
  TBranch        *b_isEcalDriven;   //!
  TBranch        *b_EoverP;   //!
  TBranch        *b_FBrem;   //!
  TBranch        *b_InvEminusInvP;   //!
  TBranch        *b_PassConversionVeto;   //!
  TBranch        *b_ecalPFClusterIso;   //!
  TBranch        *b_hcalPFClusterIso;   //!
  TBranch        *b_IsGsfCtfScPixChargeConsistent;   //!
  TBranch        *b_IsGsfScPixChargeConsistent;   //!
  TBranch        *b_IsGsfCtfChargeConsistent;   //!
  TBranch        *b_EtaWidth;   //!
  TBranch        *b_PhiWidth;   //!
  TBranch        *b_e2x5OverE5x5;   //!
  TBranch        *b_e1x5OverE5x5;   //!
  TBranch        *b_e15;   //!
  TBranch        *b_e25;   //!
  TBranch        *b_e55;   //!
  TBranch        *b_dr03EcalRecHitSumEt;   //!
  TBranch        *b_dr03HcalDepth1TowerSumEt;   //!
  TBranch        *b_dr03HcalTowerSumEt;   //!
  TBranch        *b_dr03TkSumPt;   //!
  TBranch        *b_R9;   //!
  TBranch        *b_w_id_tot;   //!


  TTree          *fChain;


  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<< endl;

  cout << "Opening file " << input_path << endl;

  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(input_path);

  if (!f || !f->IsOpen()) {
    f = new TFile(input_path);
  }
  f->GetObject("Tree_ee",fChain);
  if (!fChain) {
    cout << "ERROR" << endl;
    return;
  }

  fChain->SetMakeClass(1);
  

  fChain->SetBranchAddress("Pt", &Pt, &b_Pt);
  fChain->SetBranchAddress("PtBinned", &PtBinned, &b_PtBinned);
  fChain->SetBranchAddress("Eta", &Eta, &b_Eta);
  fChain->SetBranchAddress("PileUp", &PileUp, &b_PileUp);
  fChain->SetBranchAddress("MiniIsoChHad", &MiniIsoChHad, &b_MiniIsoChHad);
  fChain->SetBranchAddress("MiniIsoNHad", &MiniIsoNHad, &b_MiniIsoNHad);
  fChain->SetBranchAddress("MiniIsoPhHad", &MiniIsoPhHad, &b_MiniIsoPhHad);
  fChain->SetBranchAddress("RelMiniIsoCh", &RelMiniIsoCh, &b_RelMiniIsoCh);
  fChain->SetBranchAddress("RelMiniIsoN", &RelMiniIsoN, &b_RelMiniIsoN);
  fChain->SetBranchAddress("IsoChHad", &IsoChHad, &b_IsoChHad);
  fChain->SetBranchAddress("IsoNHad", &IsoNHad, &b_IsoNHad);
  fChain->SetBranchAddress("IsoPhHad", &IsoPhHad, &b_IsoPhHad);
  fChain->SetBranchAddress("Dxy", &Dxy, &b_Dxy);
  fChain->SetBranchAddress("RelDxy", &RelDxy, &b_RelDxy);
  fChain->SetBranchAddress("DxySig", &DxySig, &b_DxySig);
  fChain->SetBranchAddress("Dz", &Dz, &b_Dz);
  fChain->SetBranchAddress("RelDz", &RelDz, &b_RelDz);
  fChain->SetBranchAddress("DzSig", &DzSig, &b_DzSig);
  fChain->SetBranchAddress("RelIso", &RelIso, &b_RelIso);
  fChain->SetBranchAddress("IP3D", &IP3D, &b_IP3D);
  fChain->SetBranchAddress("RelIP3D", &RelIP3D, &b_RelIP3D);
  fChain->SetBranchAddress("MVA", &MVA, &b_MVA);
  fChain->SetBranchAddress("RelMVA", &RelMVA, &b_RelMVA);
  fChain->SetBranchAddress("MVAIso", &MVAIso, &b_MVAIso);
  fChain->SetBranchAddress("RelMVAIso", &RelMVAIso, &b_RelMVAIso);
  fChain->SetBranchAddress("POGTight", &POGTight, &b_POGTight);
  fChain->SetBranchAddress("POGMedium", &POGMedium, &b_POGMedium);
  fChain->SetBranchAddress("HNTightID", &HNTightID, &b_HNTightID);
  fChain->SetBranchAddress("PtRatio", &PtRatio, &b_PtRatio);
  fChain->SetBranchAddress("PtRel", &PtRel, &b_PtRel);
  fChain->SetBranchAddress("MassDrop", &MassDrop, &b_MassDrop);
  fChain->SetBranchAddress("CEMFracCJ", &CEMFracCJ, &b_CEMFracCJ);
  fChain->SetBranchAddress("NEMFracCJ", &NEMFracCJ, &b_NEMFracCJ);
  fChain->SetBranchAddress("CHFracCJ", &CHFracCJ, &b_CHFracCJ);
  fChain->SetBranchAddress("NHFracCJ", &NHFracCJ, &b_NHFracCJ);
  fChain->SetBranchAddress("MuFracCJ", &MuFracCJ, &b_MuFracCJ);
  fChain->SetBranchAddress("JetDiscCJ", &JetDiscCJ, &b_JetDiscCJ);
  fChain->SetBranchAddress("MissingHits", &MissingHits, &b_MissingHits);
  fChain->SetBranchAddress("Full5x5_sigmaIetaIeta", &Full5x5_sigmaIetaIeta, &b_Full5x5_sigmaIetaIeta);
  fChain->SetBranchAddress("dEtaSeed", &dEtaSeed, &b_dEtaSeed);
  fChain->SetBranchAddress("dPhiIn", &dPhiIn, &b_dPhiIn);
  fChain->SetBranchAddress("dEtaIn", &dEtaIn, &b_dEtaIn);
  fChain->SetBranchAddress("HoverE", &HoverE, &b_HoverE);
  fChain->SetBranchAddress("TrkIso", &TrkIso, &b_TrkIso);
  fChain->SetBranchAddress("isEcalDriven", &isEcalDriven, &b_isEcalDriven);
  fChain->SetBranchAddress("EoverP", &EoverP, &b_EoverP);
  fChain->SetBranchAddress("FBrem", &FBrem, &b_FBrem);
  fChain->SetBranchAddress("InvEminusInvP", &InvEminusInvP, &b_InvEminusInvP);
  fChain->SetBranchAddress("PassConversionVeto", &PassConversionVeto, &b_PassConversionVeto);
  fChain->SetBranchAddress("ecalPFClusterIso", &ecalPFClusterIso, &b_ecalPFClusterIso);
  fChain->SetBranchAddress("hcalPFClusterIso", &hcalPFClusterIso, &b_hcalPFClusterIso);
  fChain->SetBranchAddress("IsGsfCtfScPixChargeConsistent", &IsGsfCtfScPixChargeConsistent, &b_IsGsfCtfScPixChargeConsistent);
  fChain->SetBranchAddress("IsGsfScPixChargeConsistent", &IsGsfScPixChargeConsistent, &b_IsGsfScPixChargeConsistent);
  fChain->SetBranchAddress("IsGsfCtfChargeConsistent", &IsGsfCtfChargeConsistent, &b_IsGsfCtfChargeConsistent);
  fChain->SetBranchAddress("EtaWidth", &EtaWidth, &b_EtaWidth);
  fChain->SetBranchAddress("PhiWidth", &PhiWidth, &b_PhiWidth);
  fChain->SetBranchAddress("e2x5OverE5x5", &e2x5OverE5x5, &b_e2x5OverE5x5);
  fChain->SetBranchAddress("e1x5OverE5x5", &e1x5OverE5x5, &b_e1x5OverE5x5);
  fChain->SetBranchAddress("e15", &e15, &b_e15);
  fChain->SetBranchAddress("e25", &e25, &b_e25);
  fChain->SetBranchAddress("e55", &e55, &b_e55);
  fChain->SetBranchAddress("dr03EcalRecHitSumEt", &dr03EcalRecHitSumEt, &b_dr03EcalRecHitSumEt);
  fChain->SetBranchAddress("dr03HcalDepth1TowerSumEt", &dr03HcalDepth1TowerSumEt, &b_dr03HcalDepth1TowerSumEt);
  fChain->SetBranchAddress("dr03HcalTowerSumEt", &dr03HcalTowerSumEt, &b_dr03HcalTowerSumEt);
  fChain->SetBranchAddress("dr03TkSumPt", &dr03TkSumPt, &b_dr03TkSumPt);
  fChain->SetBranchAddress("R9", &R9, &b_R9);
  fChain->SetBranchAddress("w_id_tot", &w_id_tot, &b_w_id_tot);



  Long64_t nentries = fChain->GetEntriesFast();

  TH1D* h_pt = new TH1D("h_pt","h_pt", 200, 0, 200);
  TH1D* h_PtBinned = new TH1D("PtBinned","PtBinned", 5  , 0 ,5);
  TH1D* h_Eta = new TH1D("h_Eta","h_Eta", 300 ,0 , 3);
  TH1D* h_Dxy = new TH1D("h_Dxy","h_Dxy",200 , -30, 10);
  TH1D* h_DxySig = new TH1D("h_DxySig","h_DxySig", 200 , -30, 10);
  TH1D* h_Dz = new TH1D("h_Dz","h_Dz",200 , -30, 10);
  TH1D* h_DzSig = new TH1D("h_DzSig","h_DzSig", 200 , -30, 10);
  TH1D* h_IP3D = new TH1D("h_IP3D","h_IP3D", 100, 0, 8);
  TH1D* h_MVA = new TH1D("h_MVA","h_MVA",220 , -1 ,10);
  TH1D* h_MVAIso = new TH1D("h_MVAIso","h_MVAIso",220 , -1 ,10);
  TH1D* h_Full5x5_sigmaIetaIeta = new TH1D("h_Full5x5_sigmaIetaIeta","h_Full5x5_sigmaIetaIeta",200 , 0 , 0.04);
  TH1D* h_dPhiIn = new TH1D("h_dPhiIn","h_dPhiIn", 200, -0.2 , 0.2);
  TH1D* h_EoverP = new TH1D("h_EoverP","h_EoverP", 200, -10 ,10);
  TH1D* h_FBrem = new TH1D("h_FBrem","h_FBrem", 200, -2 , 2);
  TH1D* h_R9 = new TH1D("h_R9","h_R9",220 , 0 , 1.1);
  TH1D* h_e55 = new TH1D("h_e55","h_e55", 400, 0 , 8000);
  TH1D* h_EtaWidth = new TH1D("h_EtaWidth","h_EtaWidth",200 , 0 , 1);
  TH1D* h_PhiWidth = new TH1D("h_PhiWidth","h_PhiWidth", 400, 0, 2);
  TH1D* h_PassConversionVeto = new TH1D("h_PassConversionVeto","h_PassConversionVeto",3 ,0 ,3);
  TH1D* h_IsGsfCtfScPixChargeConsistent = new TH1D("h_IsGsfCtfScPixChargeConsistent","h_IsGsfCtfScPixChargeConsistent",3 ,0 ,3);
  TH1D* h_IsGsfScPixChargeConsistent = new TH1D("h_IsGsfScPixChargeConsistent","h_IsGsfScPixChargeConsistent", 3 ,0 ,3);
  TH1D* h_IsGsfCtfChargeConsistent = new TH1D("h_IsGsfCtfChargeConsistent","h_IsGsfCtfChargeConsistent", 3 ,0 ,3);
  TH1D* h_InvEminusInvP = new TH1D("h_InvEminusInvP","h_InvEminusInvP", 200, 0 ,2);
  TH1D* h_hcalPFClusterIso = new TH1D("h_hcalPFClusterIso","h_hcalPFClusterIso", 200,0 , 0.5);
  TH1D* h_ecalPFClusterIso = new TH1D("h_ecalPFClusterIso","h_ecalPFClusterIso", 200,0 , 0.5);
  TH1D* h_dr03TkSumPt = new TH1D("h_dr03TkSumPt","h_dr03TkSumPt", 250, 0 , 0.25);
  TH1D* h_HoverE = new TH1D("h_HoverE","h_HoverE",150 , 0 , 1.5);
  TH1D* h_MissingHits = new TH1D("h_MissingHits","h_MissingHits",5 ,0 ,5);
  TH1D* h_w_id_tot = new TH1D("h_w_id_tot","h_w_id_tot", 100, 0,2);
  

  TH1D* h_MiniIsoChHad = new TH1D("h_MiniIsoChHad","h_MiniIsoChHad", 200, 0, 100);
  TH1D* h_MiniIsoNHad = new TH1D("h_MiniIsoNHad","h_MiniIsoNHad", 200, 0, 100);
  TH1D* h_MiniIsoPhHad = new TH1D("h_MiniIsoPhHad","h_MiniIsoPhHad", 200, 0, 100);
  TH1D* h_RelMiniIsoCh = new TH1D("h_RelMiniIsoCh","h_RelMiniIsoCh", 200, 0, 0.5);
  TH1D* h_RelMiniIsoN = new TH1D("h_RelMiniIsoN","h_RelMiniIsoN", 200, 0, 0.5);
  TH1D* h_IsoChHad = new TH1D("h_IsoChHad","h_IsoChHad", 200, 0, 100);
  TH1D* h_IsoNHad = new TH1D("h_IsoNHad","h_IsoNHad", 200, 0, 100);
  TH1D* h_IsoPhHad = new TH1D("h_IsoPhHad","h_IsoPhHad", 200, 0, 100);
  TH1D* h_RelIso = new TH1D("h_RelIso","h_RelIso", 200, 0, 1);
  TH1D* h_RelIP3D = new TH1D("h_RelIP3D","h_RelIP3D", 200, 0, 1.);
  TH1D* h_PtRatio = new TH1D("h_PtRatio","h_PtRatio", 200, 0, 2);
  TH1D* h_PtRel = new TH1D("h_PtRel","h_PtRel", 500, 0, 500);
  TH1D* h_CEMFracCJ = new TH1D("h_CEMFracCJ","h_CEMFracCJ", 200, 0, 2);
  TH1D* h_NEMFracCJ = new TH1D("h_NEMFracCJ","h_NEMFracCJ", 200, 0, 2);
  TH1D* h_CHFracCJ = new TH1D("h_CHFracCJ","h_CHFracCJ", 200, 0, 2);
  TH1D* h_NHFracCJ = new TH1D("h_NHFracCJ","h_NHFracCJ", 200, 0, 2);
  TH1D* h_MuFracCJ = new TH1D("h_MuFracCJ","h_MuFracCJ", 200, 0, 2);
  TH1D* h_JetDiscCJ = new TH1D("h_JetDiscCJ","h_JetDiscCJ", 200, 0, 2);
  TH1D* h_dEtaSeed = new TH1D("h_dEtaSeed","h_dEtaSeed", 200, -0.05, 0.05);
  TH1D* h_dEtaIn = new TH1D("h_dEtaIn","h_dEtaIn", 200, -0.1, 0.1);
  TH1D* h_TrkIso = new TH1D("h_TrkIso","h_TrkIso", 200, 0, 5);
  TH1D* h_e2x5OverE5x5 = new TH1D("h_e2x5OverE5x5","h_e2x5OverE5x5", 220, 0, 1.1);


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(!(jentry%10000)) cout << "Entry ["<< jentry <<"/"<< nentries <<"] "<< endl;

    Long64_t centry = fChain->LoadTree(jentry);
    if (centry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;                                                                                                                                                                                                      

    h_pt->Fill(Pt, w_id_tot);
    h_PtBinned->Fill(PtBinned, w_id_tot);
    h_Eta->Fill(Eta, w_id_tot);
    h_Dxy->Fill(Dxy, w_id_tot);
    h_DxySig->Fill(DxySig, w_id_tot);
    h_Dz->Fill(Dz, w_id_tot);
    h_DzSig->Fill(DzSig, w_id_tot);
    h_IP3D->Fill(IP3D, w_id_tot);
    h_MVA->Fill(MVA, w_id_tot);
    h_MVAIso->Fill(MVAIso, w_id_tot);
    h_Full5x5_sigmaIetaIeta->Fill(Full5x5_sigmaIetaIeta, w_id_tot);
    h_dPhiIn->Fill(dPhiIn, w_id_tot);
    h_EoverP->Fill(EoverP, w_id_tot);
    h_FBrem->Fill(FBrem, w_id_tot);
    h_R9->Fill(R9, w_id_tot);
    h_e55->Fill(e55, w_id_tot);
    h_EtaWidth->Fill(EtaWidth, w_id_tot);
    h_PhiWidth->Fill(PhiWidth, w_id_tot);
    h_PassConversionVeto->Fill(PassConversionVeto, w_id_tot);
    h_IsGsfCtfScPixChargeConsistent->Fill(IsGsfCtfScPixChargeConsistent, w_id_tot);
    h_IsGsfScPixChargeConsistent->Fill(IsGsfScPixChargeConsistent, w_id_tot);
    h_IsGsfCtfChargeConsistent->Fill(IsGsfCtfChargeConsistent, w_id_tot);
    h_InvEminusInvP->Fill(InvEminusInvP, w_id_tot);
    h_hcalPFClusterIso->Fill(hcalPFClusterIso, w_id_tot);
    h_ecalPFClusterIso->Fill(ecalPFClusterIso, w_id_tot);
    h_dr03TkSumPt->Fill(dr03TkSumPt, w_id_tot);
    h_HoverE->Fill(HoverE, w_id_tot);
    h_MissingHits->Fill(MissingHits, w_id_tot);

    
    h_MiniIsoChHad->Fill(MiniIsoChHad, w_id_tot);
    h_MiniIsoNHad->Fill(MiniIsoNHad, w_id_tot);
    h_MiniIsoPhHad->Fill(MiniIsoPhHad, w_id_tot);
    h_RelMiniIsoCh->Fill(RelMiniIsoCh, w_id_tot);
    h_RelMiniIsoN->Fill(RelMiniIsoN, w_id_tot);
    h_IsoChHad->Fill(IsoChHad, w_id_tot);
    h_IsoNHad->Fill(IsoNHad, w_id_tot);
    h_IsoPhHad->Fill(IsoPhHad, w_id_tot);
    h_RelIso->Fill(RelIso, w_id_tot);
    h_RelIP3D->Fill(RelIP3D, w_id_tot);
    h_PtRatio->Fill(PtRatio, w_id_tot);
    h_PtRel->Fill(PtRel, w_id_tot);
    h_CEMFracCJ->Fill(CEMFracCJ, w_id_tot);
    h_NEMFracCJ->Fill(NEMFracCJ, w_id_tot);
    h_CHFracCJ->Fill(CHFracCJ, w_id_tot);
    h_NHFracCJ->Fill(NHFracCJ, w_id_tot);
    h_MuFracCJ->Fill(MuFracCJ, w_id_tot);
    h_JetDiscCJ->Fill(JetDiscCJ, w_id_tot);
    h_dEtaSeed->Fill(dEtaSeed, w_id_tot);
    h_dEtaIn->Fill(dEtaIn, w_id_tot);
    h_TrkIso->Fill(TrkIso, w_id_tot);
    h_e2x5OverE5x5->Fill(e2x5OverE5x5, w_id_tot);

  }

  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  cout << "Creating " << OUTNAME << endl;
  TFile * OutFile = new TFile(OUTNAME,"RECREATE");
  
  OutFile->cd();

  h_pt->Write();
  h_PtBinned->Write();
  h_Eta->Write();
  h_Dxy->Write();
  h_DxySig->Write();
  h_Dz->Write();
  h_DzSig->Write();
  h_IP3D->Write();
  h_MVA->Write();
  h_MVAIso->Write();
  h_Full5x5_sigmaIetaIeta->Write();
  h_dPhiIn->Write();
  h_EoverP->Write();
  h_FBrem->Write();
  h_R9->Write();
  h_e55->Write();
  h_EtaWidth->Write();
  h_PhiWidth->Write();
  h_PassConversionVeto->Write();
  h_IsGsfCtfScPixChargeConsistent->Write();
  h_IsGsfScPixChargeConsistent->Write();
  h_IsGsfCtfChargeConsistent->Write();
  h_InvEminusInvP->Write();
  h_hcalPFClusterIso->Write();
  h_ecalPFClusterIso->Write();
  h_dr03TkSumPt->Write();
  h_HoverE->Write();
  h_MissingHits->Write();


  h_MiniIsoChHad->Write();
  h_MiniIsoNHad->Write();
  h_MiniIsoPhHad->Write();
  h_RelMiniIsoCh->Write();
  h_RelMiniIsoN->Write();
  h_IsoChHad->Write();
  h_IsoNHad->Write();
  h_IsoPhHad->Write();
  h_RelIso->Write();
  h_RelIP3D->Write();
  h_PtRatio->Write();
  h_PtRel->Write();
  h_CEMFracCJ->Write();
  h_NEMFracCJ->Write();
  h_CHFracCJ->Write();
  h_NHFracCJ->Write();
  h_MuFracCJ->Write();
  h_JetDiscCJ->Write();
  h_dEtaSeed->Write();
  h_dEtaIn->Write();
  h_TrkIso->Write();
  h_e2x5OverE5x5->Write();

  OutFile->Close();
  
  return;
}

