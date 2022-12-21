#!/usr/bin/env python                                                                                                                                                                                             

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                                                         
import os,ROOT
import sys,math
import argparse
import datetime
import mylib
from array import array
import math


def SetupOpt():
    import CMS_lumi, tdrstyle

    ROOT.gErrorIgnoreLevel = ROOT.kFatal

    tdrstyle.setTDRStyle()
    ROOT.TH1.AddDirectory(False)
    ROOT.gROOT.SetBatch(True)
    ROOT.gStyle.SetOptStat(0)
    
def GetParser(Version):

    parser = argparse.ArgumentParser(description='SKFlat Command')
    parser.add_argument('-m', dest='Mass', default="100")
    parser.add_argument('-o', dest='Outputdir', default="")
    parser.add_argument('-q', dest='Queue', default="fastq")
    parser.add_argument('-N', dest='NProc', default=999, type=int, help="maximum running jobs")
    parser.add_argument('-B', dest='BinType', default="Def")
    parser.add_argument('-r', dest='EtaRegion',  default="BB")
    parser.add_argument('--nmax', dest='NMax', default=300, type=int, help="maximum running jobs")
    parser.add_argument('--Data', action='store_true')
    parser.add_argument('--Local', action='store_true')

    parser.add_argument('-I', dest='Iso', default="Def")
    
    if Version == "Iso" or Version == "IP" or Version == "DXY" or  Version == "DZ":
        parser.add_argument('-v', dest='MVA', default="MVANoIso90")
    
    return parser
    
def GetHNSignificance(Print,nIt,histname,h_LimitInput,h_SigLimitInput):

    bkgErr=0.

    if not h_SigLimitInput:
        if nIt == 0:
            print "No signal for " + histname
        return 0.
    if h_SigLimitInput.Integral() <= 0:
        return 0.

    tot_sig = h_SigLimitInput.Integral()
    nbkg = h_LimitInput.Integral()

    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):
        for ybin in range(1,h_SigLimitInput.GetNbinsY()+1):
            if h_LimitInput:
                bkgErr = math.sqrt(bkgErr*bkgErr + h_LimitInput.GetBinError(xbin,ybin)*h_LimitInput.GetBinError(xbin,ybin))


    if nbkg <=0:
        if nIt == 0:
            print "GetHNSignificance " + histname +" Negative bkg " + str(nbkg) + " +/- " + str(bkgErr)
        nbkg = 0.2
        bkgErr = 0.2

    FOM =  float(tot_sig)/(1+math.sqrt(float(bkgErr)*float(bkgErr)+float(nbkg)))


    if Print:
        print ("histname HNTightV2 " + histname + " "  + str(tot_sig) + " nbkg = " + str(nbkg) + " FOM = " + str(FOM))

    return FOM



def GetSignificance(Version, Print ,SInPath,nIt,histname,h_LimitInput,h_SigLimitInput,A,B,C):

    Versions = ["MVA","Iso","IP","DXY","DZ"]
    if not Version in Versions:
        print("GetSignificance Version is not set correct")
        exit()
 
    FOM=0
    tot_sig=0.
    nbkg=0.
    bkgErr=0.

    if not h_SigLimitInput:
        return 0

    Debug=Print

    if Debug:
        print(SInPath + " - " + histname)
        print("Pre Signal cut Int = " + str(h_SigLimitInput.Integral()))
        print("Pre Bkg cut Int = " + str(h_LimitInput.Integral()))


    if not h_SigLimitInput:
        if nIt == 0:
            print "No signal for " + histname
        return 0.
    if h_SigLimitInput.Integral() <= 0:
        return 0.

    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):

        # Get pt from X axis bin center                                                                                         

        pt=h_SigLimitInput.GetXaxis().GetBinCenter(xbin)

        # calulate Cut value                                                                                                    
    
        cut = 0
        if Version == "MVA":
            cut = A - math.exp(-pt / B) * C
        if Version == "Iso" or Version == "IP"  or Version == "DXY" or  Version == "DZ":
            cut = A   +  ((B-A) * (pt-10)) / 50
            if pt > 59:
                cut = B
        if Debug:                                                                                                              
            print "pt = " + str(pt) + " cut = "+ str(cut) + " A= " + str(A) + " B = " + str(B) + " C = " + str(C)                                   


        sumYBkg=0
        sumYSig=0
        for ybin in range(1,h_SigLimitInput.GetNbinsY()+1):
            
            PassCut = False
            if Version == "MVA":
                PassCut = h_SigLimitInput.GetYaxis().GetBinCenter(ybin) > cut
            if Version == "Iso" or Version == "IP"  or Version == "DXY" or  Version == "DZ":
                PassCut = h_SigLimitInput.GetYaxis().GetBinCenter(ybin) < cut

            if PassCut:
                if h_LimitInput:
                    sumYBkg =sumYBkg+h_LimitInput.GetBinContent(xbin,ybin)
                    bkgErr = math.sqrt(bkgErr*bkgErr + h_LimitInput.GetBinError(xbin,ybin)*h_LimitInput.GetBinError(xbin,ybin))
                sumYSig =sumYSig+h_SigLimitInput.GetBinContent(xbin,ybin)
        tot_sig=tot_sig+sumYSig
        nbkg=nbkg+sumYBkg

    if sumYSig < 0:
        print "NO SIGNAL GetSignificance " + SInPath + " " + histname + " SIG = " + str(FOM)   + " total_sig = " + str(tot_sig)\
 + " total_bkg = " + str(nbkg)


    if nbkg <=0:
        nbkg = 0.2
        bkgErr = 0.2

    FOM =  float(tot_sig)/(1+math.sqrt(float(bkgErr)*float(bkgErr)+float(nbkg)))

    if Debug:
        print "GetSignificance " + SInPath + " " + histname + " SIG = " + str(FOM)   + " total_sig = " + str(tot_sig) + " total\
_bkg = " + str(nbkg)

    return FOM


def GetSRBins(binType,Mass):
    
    SRNames = []
    print ("GetSRBins : " + str(binType) + " mass = " + str(Mass))
    if binType == "SR1":
    
        SRNames = ["SR1_bin1_",
                   "SR1_bin2_"]

    if binType == "SR2":
    
        if Mass == "100":

            SRNames = ["MN100_SR3_bin1_",
                       "MN100_SR3_bin2_",
                       "MN100_SR3_bin3_"]
        if Mass == "250":
                
            SRNames = ["MN250_SR3_bin1_",
                       "MN250_SR3_bin2_",
                       "MN250_SR3_bin3_"]
            

        if Mass == "500":
        
            SRNames = ["MN500_SR3_bin1_",
                       "MN500_SR3_bin2_",
                       "MN500_SR3_bin3_"]
            
        else:

            SRNames = ["SR2_bin1_",
                       "SR2_bin2_",
                       "SR3_bin1_",
                       "SR3_bin2_",
                       "SR3_bin3_",
                       "SR3_bin4_",
                       "SR3_bin5_",
                       "SR3_bin6_"]
            
            
    else:


        if Mass == "100":
            
            SRNames = ["MN100_SR3_bin1_",
                       "MN100_SR3_bin2_",
                       "MN100_SR3_bin3_",
                       "SR1_bin1_",
                       "SR1_bin2_"]

        elif Mass =="250":

            SRNames = ["MN250_SR3_bin1_",
                       "MN250_SR3_bin2_",
                       "MN250_SR3_bin3_",
                       "SR1_bin1_",
                       "SR1_bin2_"]

        elif Mass =="500":
            
            SRNames = ["MN500_SR3_bin1_",
                       "MN500_SR3_bin2_",
                       "MN500_SR3_bin3_",
                       "SR1_bin1_",
                       "SR1_bin2_"]
            
        else:

            SRNames = ["SR1_bin1_",
                       "SR1_bin2_",
                       "SR2_bin1_",
                       "SR2_bin2_",
                       "SR3_bin1_",
                       "SR3_bin2_",
                       "SR3_bin3_",
                       "SR3_bin4_",
                       "SR3_bin5_",
                       "SR3_bin6_"]


    return SRNames


