import os


Eras = ["2017"]
Flags = ["RunEE__ELID_CF__HighPt__BB__","RunEE__ELID_CF__HighPt__EC__"]

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

        
