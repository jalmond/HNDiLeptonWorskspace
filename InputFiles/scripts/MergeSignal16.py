import os 

sk_path="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/2016preVFP/SIG/"
sk_path2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/2016postVFP/SIG/"
path_2016="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles///HNL_SignalRegionPlotter/2016/SIG/"

from os import listdir

from os.path import isfile,isdir, join
arr_tamsadir  = [f for f in listdir(sk_path) if isfile(join(sk_path,f))]
sswwsamples = []
for filename in arr_tamsadir:
    print filename
    sswwsamples.append(filename)


os.system("mkdir -p " + path_2016)
for x in sswwsamples:
    if os.path.exists(path_2016 +"/"+x  ):
        os.system("rm " + path_2016 +"/"+x  )
    os.system("hadd  " + path_2016 +"/"+x  + " "  + sk_path2 +"/"+x + " "  +sk_path + "/"+x)
