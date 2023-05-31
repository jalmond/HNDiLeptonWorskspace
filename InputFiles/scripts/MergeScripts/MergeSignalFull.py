#!/usr/bin/python

import os,sys 
import argparse

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="HNL_SignalRegionPlotter")
parser.add_argument('-f', dest='Flag', default="")
parser.add_argument('-e', dest='Era', default="2017")

args = parser.parse_args()
FlagDir=args.Flag
eras = [args.Era]
Analyser=args.Analyzer

py_path=os.getenv('HNDILEPTONWORKSPACE_DIR')+'/+python'

sys.path.insert(1, py_path)

from GeneralSetup import *

#set current directory to memory                                                                            
pwd = os.getcwd()

# now import analysis functions                                                                             
from HNType1_config import *

eras = [ args.Era]

# This code makes /SIG dir in HNDiLeptonWorskspace/InputFiles/MergedFiles for each DataYear
# It then merges SSWW samples ans merges All signals per mass
# it then merges 2016a and 2016b

Analyser=args.Analyzer



for era in eras:


    OutPathEra=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+FlagDir

    MassList = ["100","250","400", "500","900","1000","750","600","5000","3000","2500","1100","1300","2000","150","200","95","90"]
    MassListSurvived = []
    
    from os import listdir
    from os.path import isfile,isdir, join
    
    filelist  = [f for f in listdir(OutPathEra+"/SIG/") if isfile(join(OutPathEra+"/SIG/",f))]
    
    for Mass in MassList:
        massstring="F_M"+str(Mass)+"_"
        for x in filelist:
            if massstring in x:
                MassListSurvived.append(Mass)
        
    if os.getenv("FILE_MERGED_PATH") == "NULL":
        print("Env not set.....")
        exit()
   

    if not os.path.exists(OutPathEra+"/SIGMerged/"):
        os.system("mkdir  "+ OutPathEra+"/SIGMerged/")
    

    for Mass in MassListSurvived:
        if os.path.exists(OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root"):
            os.system("rm " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root")
 
        
        os.system ("hadd " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root "     + OutPathEra+"/SIG/*F_M"+str(Mass)+"_*private*")
        

    if os.path.exists(OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root"):
        os.system("rm "  + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root")
        
    os.system ("hadd " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root "     + OutPathEra+"/SIGMerged/"+Analyser+"*"+ str(Mass)+"*")
    
