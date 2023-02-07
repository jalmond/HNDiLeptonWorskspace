#!/usr/bin/env python                                                                                                                                                           
### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT,sys,math
import argparse, datetime, mylib
from array import array
import math, CMS_lumi, tdrstyle



def getall(d, basepath="/"):

    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def GetSignificance(h_sig, h_bkg):

    SigBins = []
    BkgBins = []
    for xbin in range(1,h_sig.GetNbinsX()+1):
        SigBins.append(h_sig.GetBinContent(xbin))

    for xbin in range(1,h_bkg.GetNbinsX()+1):
        BkgBins.append(h_bkg.GetBinContent(xbin))

    Signif = 0.

    for x in range(0, len(BkgBins)):
        print "Bin " + str(x+1) + " s/sqrt(B+1) = " + str(SigBins[x]/ math.sqrt(BkgBins[x] +1)) + " sig = " + str(SigBins[x]) + " bkg = " + str(BkgBins[x])
        Signif = Signif + SigBins[x]/ math.sqrt(BkgBins[x] +1)

    return Signif



pwd = os.getcwd()

ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

from GeneralSetup import check_lxplus_connection,GetFromConfig
check_lxplus_connection()


from  HNType1_config import *


Analyser = "HNL_SignalRegionOpt"
masses  = ["500"]#,"500","1200"]
dmasses = [100]

FOM = "punzi"

channels = ["MuMu"]


sample_dict = {}
for channel in channels:

    print ("Channel = " + channel)

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')

    c1 = ROOT.TCanvas('c1'+channel, channel, 800, 800)

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalRegionOpt_SkimTree_HNMultiLep_data.root"
    ##SigInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalRegionOpt_Type1_SS.root"

    for mass in masses:
        SigInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalRegionOpt_Type1_SS_M"+mass+".root"
        
        f_Bkg = ROOT.TFile(InPath)
        f_Sig = ROOT.TFile(SigInPath)
        
        HistNames=[]
        for k, o in getall(f_Bkg.Get("LimitInput")):
            if "HNLOpt" in  k:
                HistNames.append(k)




    
        hsigV2 = f_Sig.Get("LimitInputBDT/HNLOpt_ULHNTightV2/FillEventCutflow/MuonSR")
        hbkgV2 = f_Bkg.Get("LimitInput/HNLOpt_ULHNTightV2/FillEventCutflow/MuonSR")
        val_HNV2= GetSignificance(hsigV2,hbkgV2)
    
        for x in HistNames:
            if "Charge" in x:
                continue
            hsig = f_Sig.Get("LimitInputBDT"+x)
            hbkg = f_Bkg.Get("LimitInput"+x)
            print "GetSignificance " + x +" =========================="
            _sig= GetSignificance(hsig,hbkg)/val_HNV2

            if not x in sample_dict:
                sample_dict[x] = _sig
            else:
                SSline2Tmp = sample_dict.get(x)
                SSline2Tmp =SSline2Tmp + _sig
                sample_dict.update({x:SSline2Tmp})

        

    f_Bkg.Close()


sorted_x = sorted(sample_dict.items(), key=lambda kv: kv[1])

for x in range(0, len(sorted_x)):
    print sorted_x[x][0] + " " + str(sorted_x[x][1])

