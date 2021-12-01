import os


os.system("cp /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/2016postVFP/RunFake__/DATA/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon_F.root  /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/DEF/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon.root")



masses=["100","1500"]
ssww_masses=["1500"]
#eras=["2016","2017","2018"]
eras = ["2017"]
for e in eras:

    #os.system("cp /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/*.root /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default//HNL_IDOpt/"+e+"/")  

    for m in ssww_masses:
        if os.path.exists("/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_SSWWTypeI_NLO_SF_M"+m+".root"):
            os.system("rm /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_SSWWTypeI_NLO_SF_M"+m+".root")

        os.system("hadd /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_SSWWTypeI_NLO_SF_M"+m+".root  /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"*/HNL_IDOpt_SSWWTypeI_NLO_SF_M"+m+".root")

    
    for m in masses:
        if os.path.exists("/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_DYTypeI_NLO_SF_M"+m+".root"):
            os.system("rm /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_DYTypeI_NLO_SF_M"+m+".root")
            
        os.system("hadd /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/SIG/HNL_IDOpt_DYTypeI_NLO_SF_M"+m+".root  /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"*/HNL_IDOpt_DYTypeI_NLO_SF_M"+m+".root")
        
        print ' '
        if os.path.exists("/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon.root"):
            os.system("rm /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon.root")

        os.system("hadd /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon.root /Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_IDOpt/"+e+"*/DATA/HNL_IDOpt_SkimTree_HNMultiLep_DoubleMuon_*")

