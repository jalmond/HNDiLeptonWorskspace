import os 

eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

for era in eras:
    
    if os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/HNL_SignalRegionPlotter_SkimTree_Dilepton_CF.root"):
        os.system("rm /data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/HNL_SignalRegionPlotter_SkimTree_Dilepton_CF.root")
    os.system("hadd /data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/HNL_SignalRegionPlotter_SkimTree_Dilepton_CF.root  /data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_SignalRegionPlotter/"+era+"/RunCF__/HNL_SignalRegionPlotter_SkimTree_Dilepton_*")

