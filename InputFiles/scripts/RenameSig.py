import os


Eras = ["2016preVFP","2016postVFP","2018"]
Flags = ["MuID_NP__BB__","MuID_NP__EC__"]

for Era in Eras:
    for Flag in Flags:
        _path = "/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_SignalLeptonOpt/"+Era+"/"+Flag

        from os import listdir
        from os.path import isfile,isdir, join
        
        filelist  = [f for f in listdir(_path) if isfile(join(_path,f))]

        for x in filelist:
            if not "Skim" in x:
                continue
            if "Type" in x:
                pathfix = x
                pathfix = pathfix.replace("SkimTree_HNMultiLepBDT_","")
                print pathfix
                os.system("mv " + _path+"/"+x + " " + _path+"/"+pathfix)

        
