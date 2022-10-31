#!/usr/bin/python

import os,sys 

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

    MassList = ["100","125","150", "200","250","300","400","500","600", "700","800","900","1000","1100","1200","1500","2000", "10000","20000"] 

    if os.getenv("FILE_MERGED_PATH") == "NULL":
        print("Env not set.....")
        exit()
    
    if not os.path.exists(os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"):
        os.system("mkdir  "+ os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/")
    

    for Mass in MassList:
        if os.path.exists(os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root"):
            os.system("rm " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root")
 
        
        os.system ("hadd " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M"+str(Mass)+".root "     + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIG/*F_M"+str(Mass)+"_*private*")
        

    if os.path.exists(os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root"):
        os.system("rm "  + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root")
        
    os.system ("hadd " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"_Type1_SS_M0.root "     + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era+"/SIGMerged/"+Analyser+"*"+ str(Mass)+"*")
    
