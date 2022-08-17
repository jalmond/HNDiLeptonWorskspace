import os 

eras = ["2016preVFP", "2016postVFP", "2017"]


for era in eras:
    
    if not os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/SIG/"):
        os.system("mkdir  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/SIG/")
    os.system("cp /data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_SignalRegionPlotter/"+era+"/*Type*  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/SIG/")

    sk_path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/"+era+"/SIG/"
    from os import listdir
    from os.path import isfile,isdir, join
    arr_tamsadir  = [f for f in listdir(sk_path) if isfile(join(sk_path,f))]
    sswwsamples = []
    for filename in arr_tamsadir:
        if "SSWWTypeI_DF" in filename:
            sswwsamples.append(filename)
    for x in sswwsamples:
        mergedname=x
        mergedname=mergedname.replace('_DF','')
        sfname=x
        sfname=sfname.replace('_DF','_SF')
        if os.path.exists(sk_path + "/"+mergedname):
            os.system("rm " +sk_path + "/"+mergedname)
        os.system( "hadd " + sk_path + "/"+mergedname + " " + sk_path + "/"+x + " " + sk_path + "/"+sfname)
        
