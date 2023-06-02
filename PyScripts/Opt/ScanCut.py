#!/usr/bin/env python                                                                                                                                                           

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT
import sys,math
import argparse
import datetime
import mylib
from array import array
import math

from OptConfig import *


sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/python')
SetupOpt()

Analyser = "HNL_SignalLeptonOpt"
channels = [ "ElEl"]


pwd = os.getcwd()

from HNType1_config import *

parser = GetParser("Scan")
args = parser.parse_args()

Dir ="/data6/Users/jalmond/MVAOutput//Run2UltraLegacy_v3/OptMVAElectronIsoBATCH/Default/2017/Txt/"

from os import listdir
from os.path import isfile,isdir, join

#SR1_bin2__EBPt_HNLOpt_UL_HNTightV2;1
#KEY: TH1DSR1_bin2__EBPt_HNLOpt_UL_HNTight_17028;1
#KEY: TH1DSR1_bin2__EBPt_HNLOpt_UL_passMVAID_noIso_WP80;1
#KEY: TH1DSR1_bin2__EBPt_HNLOpt_UL_passMVAID_noIso_WP90;1
#KEY: TH1DSR1_bin2__EEPt_HNLOpt_UL_HNTightV2;1
#KEY: TH1DSR1_bin2__EEPt_HNLOpt_UL_HNTight_17028;1
#KEY: TH1DSR1_bin2__EEPt_HNLOpt_UL_passMVAID_noIso_WP80;1

EtaNames = ["BB"]
SRNames = GetSRBins(args.BinType,args.Mass)

get_list  = [f for f in listdir(Dir) if isfile(join(Dir,f))]
Masses = ["100","500","1000","2000","10000"]

Iso = [args.Iso]
MVABins = ["mva"]
ISOTypes = ["Iso"]
sample_dict = {}
sample_dict2 = {}
for I in Iso:
    for m in Masses:
        for EtaBin in EtaNames:
            for MVA in MVABins:
                for ISOType  in ISOTypes:
                    for x in get_list:

                        if "log_CC___ElEl__"+EtaBin+"_"+m+"_999__"+MVA+"__"+ISOType+I in x:
                            if not "Def" in x:
                                continue
                            if not "Data" in x:
                                continue
                            
                            file_X = Dir + "/" + x
                            
                            file_res = open( file_X,"r")
                            MaxValue=0
                            for line in file_res:
                                if "Max" in line:
                                    #print line
                                    #lineS=line
                                    #lineS = lineS.replace("MVAOpt/CC_SR1_bin2_"+ISOType+I+"__"+EtaBin+"Pt_"+MVA+"response_HNLOpt_UL_HNOpt","")
                                    SSline = line.split()
                                    MaxValue = SSline[6]
                                    
                            file_res.close()
                            
                            print "Max = " + str(MaxValue)
                         
                            
                            file_res = open( file_X,"r")
                            for line in file_res:
                                if "Max" in line:
                                    continue

                                SSline = line.split()
                                SSline1 = SSline[0] 
                                SSline2 = float(SSline[3]) / float(MaxValue)
                                if SSline2 < 0.95:
                                    continue
                                #if "6.9_13.0_12.2" in line:
                                #    print line + " " + str(SSline2)

                                sample_dict2[SSline1+"_"+m] = float(SSline[3])
                                if not SSline1 in sample_dict:
                                    sample_dict[SSline1] = SSline2
                                
                                else:
                                    SSline2Tmp = sample_dict.get(SSline1)
                                    SSline2Tmp = SSline2Tmp + SSline2
                                    sample_dict.update({SSline1:SSline2Tmp})
                                    
                                    
                            file_res.close()
                        
                        
#dict(sorted(sample_dict.items()))
sorted_x = sorted(sample_dict.items(), key=lambda kv: kv[1])

for x in range(len(sorted_x) - 10, len(sorted_x)):
    print sorted_x[x][0] + " " + str(sorted_x[x][1])
    for key, value in sample_dict2.items():
        if sorted_x[x][0] in key:
            keyM=key
            keyM = keyM.replace(sorted_x[x][0]+"_","")
            print "mN = " + keyM + ' : ' + str(value)


