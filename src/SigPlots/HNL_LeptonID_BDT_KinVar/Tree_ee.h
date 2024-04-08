//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul  5 00:16:22 2023 by ROOT version 6.22/06
// from TTree Tree_ee/Tree_ee
// found on file: /data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version2/2016/HNL_LeptonID_BDT_KinVar_CFBkg.root
//////////////////////////////////////////////////////////

#ifndef Tree_ee_h
#define Tree_ee_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Tree_ee {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
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

   // List of branches
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

   Tree_ee(TTree *tree=0);
   virtual ~Tree_ee();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   vector<TH1D*>    Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Tree_ee_cxx
Tree_ee::Tree_ee(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version2/2016/HNL_LeptonID_BDT_KinVar_CFBkg.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonID_BDT_KinVar/Version2/2016/HNL_LeptonID_BDT_KinVar_CFBkg.root");
      }
      f->GetObject("Tree_ee",tree);

   }
   Init(tree);
}

Tree_ee::~Tree_ee()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Tree_ee::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Tree_ee::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Tree_ee::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
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
   Notify();
}

Bool_t Tree_ee::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Tree_ee::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Tree_ee::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Tree_ee_cxx
