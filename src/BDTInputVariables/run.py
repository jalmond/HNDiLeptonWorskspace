import os 

Eras = ["2016preVFP","2016postVFP","2017","2018"]
EtaBins = ["__BB__ptbin1","__BB__ptbin2","__BB__ptbin3","__BB__ptbin4", "__EC__ptbin1","__EC__ptbin2","__EC__ptbin3","__EC__ptbin4"]
EtaBins = [""]

for Era in Eras:
    for EtaBin in EtaBins:

        Hists = [ 
            ["Electron_E15_Electron"+EtaBin+"_OSElectron","e15", "0","300.","5."],
            ["Electron_E25_Electron"+EtaBin+"_OSElectron","e25",0,300.,5],
            ["Electron_E55_Electron"+EtaBin+"_OSElectron","e55",0,300.,5], 
            ["Electron_EoverP_Electron"+EtaBin+"_OSElectron","EoverP",0,10.,2],
            ["Electron_EtaWidth_Electron"+EtaBin+"_OSElectron","EtaWidth",0.,0.04,1],
            ["Electron_FBrem_Electron"+EtaBin+"_OSElectron","FBrem",-0.2,1.,1],
            ["Electron_Full5x5_sigmaIetaIeta_Electron"+EtaBin+"_OSElectron","Full5x5_sigmaIetaIeta",0,0.035,1],
            ["Electron_HoverE_Electron"+EtaBin+"_OSElectron","HoverE",0,0.1,1],
            ["Electron_InvEminusInvP_Electron"+EtaBin+"_OSElectron","InvEminusInvP",0,0.04,1],
            ["Electron_IsGsfCtfChargeConsistent_Electron"+EtaBin+"_OSElectron","IsGsfCtfChargeConsistent",0,2,1],
            ["Electron_IsGsfCtfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron","IsGsfCtfScPixChargeConsistent",0,2,1],
            ["Electron_IsGsfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron","IsGsfScPixChargeConsistent",0,2,1],
            ["Electron_LogEoverP_Electron"+EtaBin+"_OSElectron","LogEoverP",-1,2,1],
            ["Electron_MissingHits_Electron"+EtaBin+"_OSElectron","MissingHits",0,4,1],
            ["Electron_NoIsoMvaResponse_Electron"+EtaBin+"_OSElectron","NoIsoMvaResponse",0,10,1],
            ["Electron_NoIsoMva_Electron"+EtaBin+"_OSElectron","NoIsoMva",0,0,5],
            ["Electron_PassConversionVeto_Electron"+EtaBin+"_OSElectron","PassConversionVeto",0,0,1],
            ["Electron_PhiWidth_Electron"+EtaBin+"_OSElectron","PhiWidth",0,0.12,1],
            ["Electron_R9_Electron"+EtaBin+"_OSElectron","R9",0.2,0,1],
            ["Electron_SCEta_Electron"+EtaBin+"_OSElectron","SCEta",0,0,1],
            ["Electron_TrkIso_Electron"+EtaBin+"_OSElectron","TrkIso",0,10,2],
            ["Electron_dEtaIn_Electron"+EtaBin+"_OSElectron","dEtaIn",-0.05,0.05,2],
            ["Electron_dEtaSeed_Electron"+EtaBin+"_OSElectron","dEtaSeed",-0.02,0.02,2],
            ["Electron_dPhiIn_Electron"+EtaBin+"_OSElectron","dPhiIn",-0.1,0.1,2],
            ["Electron_dr03EcalRecHitSumEt_Electron"+EtaBin+"_OSElectron","dr03EcalRecHitSumEt",0,10,2], #--->

            ["Electron_dr03HcalDepth1TowerSumEt_Electron"+EtaBin+"_OSElectron","dr03HcalDepth1TowerSumEt",0,6,2],
            ["Electron_dr03HcalTowerSumEt_Electron"+EtaBin+"_OSElectron","dr03HcalTowerSumEt",0,6,2],
            ["Electron_dr03TkSumPt_Electron"+EtaBin+"_OSElectron","dr03TkSumPt",0,0.1,2],
            ["Electron_e1x5OverE5x5_Electron"+EtaBin+"_OSElectron","e1x5OverE5x5",0.3,0,1],
            ["Electron_e2x5OverE5x5_Electron"+EtaBin+"_OSElectron","e2x5OverE5x5",0.4,0,1],
            ["Electron_ecalPFClusterIso_Electron"+EtaBin+"_OSElectron","ecalPFClusterIso",0,0.3,2],
            ["Electron_hcalPFClusterIso_Electron"+EtaBin+"_OSElectron","hcalPFClusterIso",0,0.3,2],
            ["Lepton_CEMFracCJ_Electron"+EtaBin+"_OSElectron","CEMFracCJ",0,0,2],
            ["Lepton_CHFracCJ_Electron"+EtaBin+"_OSElectron","CHFracCJ",0,0,2],
            ["Lepton_Dxy_Electron"+EtaBin+"_OSElectron","Dxy",0,0.05,2],
            ["Lepton_Dz_Electron"+EtaBin+"_OSElectron","Dz",0,0.1,2],
            ["Lepton_IP3D_Electron"+EtaBin+"_OSElectron","IP3D",0,10,2],
            ["Lepton_JetDiscCJ_Electron"+EtaBin+"_OSElectron","JetDiscCJ",0,1,2],
            ["Lepton_LogDxy_Electron"+EtaBin+"_OSElectron","LogDxy",-10,5,1],
            ["Lepton_MiniIsoChHad_Electron"+EtaBin+"_OSElectron","MiniIsoChHad",0,10,1],
            ["Lepton_MiniIsoNhHad_Electron"+EtaBin+"_OSElectron","MiniIsoNhHad",0,10,1],
            ["Lepton_MiniIsoPhHad_Electron"+EtaBin+"_OSElectron","MiniIsoPhHad",0,10,1],
            ["Lepton_MiniReliso_Electron"+EtaBin+"_OSElectron","MiniReliso",0,10,1],
            ["Lepton_MiniReliso_ch_Electron"+EtaBin+"_OSElectron","MiniReliso_ch",0,10,1],
            ["Lepton_MiniReliso_neu_Electron"+EtaBin+"_OSElectron","MiniReliso_neu",0,10,1],
            ["Lepton_NEMFracCJ_Electron"+EtaBin+"_OSElectron","NEMFracCJ",0,1,2],
            ["Lepton_NFracCJ_Electron"+EtaBin+"_OSElectron","NFracCJ",0,1,2],
            ["Lepton_PtBinned_Electron"+EtaBin+"_OSElectron","PtBinned",15,1000,1],
            ["Lepton_PtRatio_Electron"+EtaBin+"_OSElectron","PtRatio",0,2,5],
            ["Lepton_PtRel_Electron"+EtaBin+"_OSElectron","PtRel",0,100,10],
            ["Lepton_SIP3D_Electron"+EtaBin+"_OSElectron","SIP3D",0,10,1],
            ["Lepton_dXYSig_Electron"+EtaBin+"_OSElectron","dXYSig",0,10,1],
            ["Lepton_dZSig_Electron"+EtaBin+"_OSElectron","dZSig",0,10,1]
        ]
        

        Hists = [
            ["Lepton_PtRatioCorr_Electron"+EtaBin+"_OSElectron","PtRatio",0,2,5],
            ["Lepton_PtRel_Electron"+EtaBin+"_OSElectron","PtRel",0,100,10],
            ["Lepton_PtRatio_Electron"+EtaBin+"_OSElectron","PtRatio",0,2,5],
            ["Lepton_PtRelCorr_Electron"+EtaBin+"_OSElectron","PtRel",0,100,10],
            ["Lepton_SIP3D_Electron"+EtaBin+"_OSElectron","SIP3D",0,10,1],
            ["Lepton_SIP3D2_Electron"+EtaBin+"_OSElectron","SIP3D",0,10,1],
            ["Lepton_SIP3D3_Electron"+EtaBin+"_OSElectron","SIP3D",0,10,1],
            ["Lepton_LogDxy_Electron"+EtaBin+"_OSElectron","LogDxy",-10,5,1],
            ["Lepton_LogDxy2_Electron"+EtaBin+"_OSElectron","LogDxy",-10,5,1],
            ["Lepton_LogDxy3_Electron"+EtaBin+"_OSElectron","LogDxy",-10,5,1],

        ]

        for Hist  in Hists:
            print("root -l -q -b 'BDTInputVariablesFake.C(\""+Era+"\",\""+EtaBin+"\",\""+Hist[0]+"\","+str(Hist[2])+","+str(Hist[3])+","+str(Hist[4])+",\""+Hist[1]+"\")'")
            os.system("root -l -q -b 'BDTInputVariablesFake.C(\""+Era+"\",\""+EtaBin+"\",\""+Hist[0]+"\","+str(Hist[2])+","+str(Hist[3])+","+str(Hist[4])+",\""+Hist[1]+"\")'")

            
            

