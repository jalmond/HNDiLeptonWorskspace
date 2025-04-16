import subprocess
import os

eras = ["2016preVFP", "2016postVFP", "2017", "2018"]
Flag="DiLeptonReq__"

for era in eras:

    # Create directory if it doesn't exist
    os.makedirs(era, exist_ok=True)

    
    cmds = [
        f"hadd {era}/MeasureJetTaggingEfficiency_HNL_DY_2L_hadded.root /data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/*DYTypeI*",
        f"hadd {era}/MeasureJetTaggingEfficiency_HNL_VBF_2L_hadded.root /data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/*VBFTypeI*",
        f"hadd {era}/MeasureJetTaggingEfficiency_HNL_SSWW_2L_hadded.root /data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/*SSWWTypeI*",

        f"hadd {era}/MeasureJetTaggingEfficiency_WW_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_*_WpWp_EWK.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
	f"MeasureJetTaggingEfficiency_SkimTree_*_WpWp_QCD.root ",
        
        f"hadd {era}/MeasureJetTaggingEfficiency_ZZ_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_ZZTo4L_powheg.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_ZZ_pythia.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_*_GluGluToZZ*root ",


        f"hadd {era}/MeasureJetTaggingEfficiency_ZG_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_ZGToLLG.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_ZGToLLG_PtG_130.root ",

        f"hadd {era}/MeasureJetTaggingEfficiency_WZ_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WZTo3LNu_mllmin4p0_powheg.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WZ_pythia.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_*ZTo3LNu_amcatnlo.root ",


        f"hadd {era}/MeasureJetTaggingEfficiency_TTV_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_*_ttW*.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_*_ttZT*.root ",

        
        f"hadd {era}/MeasureJetTaggingEfficiency_WG_2L_hadded.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGToLNuG_MG.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGToLNuG_01J_PtG_500.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGToLNuG_01J_PtG_300.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGToLNuG_01J_PtG_130.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGToLNuG.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_WGJJToLNu.root ",


        
        f"hadd {era}/MeasureJetTaggingEfficiency_DY_2L.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_DYJetsToMuMu_MiNNLO.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_DYJetsToTauTau_MiNNLO.root "
        f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/MeasureJetTaggingEfficiency/{era}/{Flag}/"
        f"MeasureJetTaggingEfficiency_SkimTree_DileptonBDT_DYJetsToEE_MiNNLO.root "
    ]

    for cmd in cmds:
        print(f"Running: {cmd}")
        subprocess.run(cmd, shell=True)
