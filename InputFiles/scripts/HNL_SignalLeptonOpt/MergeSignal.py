#!/usr/bin/python

import os 

eras = [ "2017"]

FlagDir="/RunEE__RunHighPt__"



# This code makes /SIG dir in HNDiLeptonWorskspace/InputFiles/MergedFiles for each DataYear
# It then merges SSWW samples ans merges All signals per mass
# it then merges 2016a and 2016b

Analyser="HNL_SignalLeptonOpt"

for era in eras:

    OutPathEra=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+FlagDir

    
    if os.getenv("FILE_MERGED_PATH") == "NULL":
        print("Env not set.....")
        exit()
    
    if not os.path.exists(OutPathEra+"/SIG/"):
        os.system("mkdir  "+ OutPathEra+"/SIG/")
    

    print("cp " + os.getenv("INFILE_PATH") + "/"+Analyser+"/"+era+FlagDir+"/*Type* " +  OutPathEra+"/SIG/")
    os.system("cp " + os.getenv("INFILE_PATH") + "/"+Analyser+"/"+era+FlagDir+"/*Type* " +  OutPathEra+"/SIG/")
    

    sk_path= OutPathEra+"/SIG/"

    from os import listdir
    from os.path import isfile,isdir, join
    sig_dir  = [f for f in listdir(sk_path) if isfile(join(sk_path,f))]
    sswwsamples = []

    print("Loop over signal dir: [HADD SSWW [SF,DF]]")
    for filename in sig_dir:
        if "SSWWTypeI_DF" in filename:
            sswwsamples.append(filename)

    for x in sswwsamples:
        mergedname=x
        mergedname=mergedname.replace('_DF','')
        sfname=x
        sfname=sfname.replace('_DF','_SF')
        if os.path.exists(sk_path + "/"+mergedname):
            os.system("rm " + sk_path + "/"+mergedname)
        os.system( "hadd " + sk_path + "/"+mergedname + " " + sk_path + "/"+x + " " + sk_path + "/"+sfname)
        
