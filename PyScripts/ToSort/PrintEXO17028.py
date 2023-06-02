#!/usr/bin/env python                                                                                       

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                   
import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')

pwd = os.getcwd()


# now import analysis functions                                                                             
from HNType1_config import *


channels = ["MuMu","ElEl"]
SRs = ["Bin1", "Bin2"]   
SIGS = ["DY","VBF" ]

for channel in channels:
    for SR in SRs:
        for SIG in SIGS:
            
            masses = GetEXO_17_028_Masses("",True)
            dmasses = GetEXO_17_028_Masses("",False)
            if SIG == "VBF":
                masses = GetEXO_17_028_Masses("TChannel",True)
                dmasses = GetEXO_17_028_Masses("TChannel",False)

            Bin=SR
            Bin=Bin.replace('Bin','SR')
            
            im=-1
            for mass in masses:
                im=im+1
                eff= GetEXO_17_028_Eff(channel, Bin, mass,SIG)
                
                xsec = GetXSecUnityCoupling(dmasses[im],SIG)
                print str(xsec)
                nSig =xsec*36500*eff
                nBkg = GetEXO_17_028_Yield(channel, SR , mass,  SIG)
                
                print "Number of siganls in " + channel  +" SR " + SR + " " + mass + " " + SIG +"  " + str(float(v1)/float(v2))
                #print "Number of siganls in " + channel  +" SR " + SR + " " + mass + " " + SIG +"  " +  str(GetEXO_17_028_Yield(channel, SR , mass,  SIG))



# 
#    SRs = ["Bin1", "Bin2","Combined"]
#    SIGS = ["","_VBF","_VBFOnly"
