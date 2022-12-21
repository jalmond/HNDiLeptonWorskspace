#!/usr/bin/python

import os,sys 

FlagDir="/RunEE__RunHighPt__"


py_path=os.getenv('HNDILEPTONWORKSPACE_DIR')+'/+python'

sys.path.insert(1, py_path)

from GeneralSetup import *

#set current directory to memory                                                                            
pwd = os.getcwd()

# now import analysis functions                                                                             
from HNType1_config import *

eras = [ "2017"]

# This code makes /SIG dir in HNDiLeptonWorskspace/InputFiles/MergedFiles for each DataYear
# It then merges SSWW samples ans merges All signals per mass
# it then merges 2016a and 2016b

Analyser="HNL_SignalLeptonOpt"



for era in eras:


    OutPathEra=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+FlagDir

    MassList = ["100","500","2000"]

    if os.getenv("FILE_MERGED_PATH") == "NULL":
        print("Env not set.....")
        exit()
   

    if not os.path.exists(OutPathEra+"/SIGMerged/"):
        os.system("mkdir  "+ OutPathEra+"/SIGMerged/")
    

    for Mass in MassList:
        if os.path.exists(OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root"):
            os.system("rm " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root")
 
        
        os.system ("hadd " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root "     + OutPathEra+"/SIG/*F_M"+str(Mass)+"_*private*")
        

    if os.path.exists(OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root"):
        os.system("rm "  + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root")
        
    os.system ("hadd " + OutPathEra+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root "     + OutPathEra+"/SIGMerged/"+Analyser+"*"+ str(Mass)+"*")
    
