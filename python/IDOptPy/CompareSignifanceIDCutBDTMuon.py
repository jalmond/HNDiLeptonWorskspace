#!/usr/bin/env python                                                                                                                                                           
### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT,sys,math
import argparse, datetime, mylib
from array import array
import math, CMS_lumi, tdrstyle



def Print(out, line):
    print line
    out.write(line+"\n")

def getall(d, basepath="/"):

    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def GetSignificance(out,h_sig, h_bkg):

    SigBins = []
    BkgBins = []
    for xbin in range(1,h_sig.GetNbinsX()+1):
        SigBins.append(h_sig.GetBinContent(xbin))

    for xbin in range(1,h_bkg.GetNbinsX()+1):
        BkgBins.append(h_bkg.GetBinContent(xbin))

    Signif = 0.

    for x in range(0, len(BkgBins)):
        Bkg=BkgBins[x] 
        if Bkg <0:
            Bkg = 0.5
        Signif = Signif + SigBins[x]/ math.sqrt(Bkg +1)
        Print(out, "Bin " + str(x+1) + " s/sqrt(B+1) = " + str(SigBins[x]/ math.sqrt(Bkg +1)) + " sig = " + str(SigBins[x]) + " bkg = " + str(Bkg))

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


Analyser = "HNL_SignalLeptonOpt"
masses  = ["100", "250","500","2000"]
dmasses = [100]


FOM = "punzi"

channels = ["MuMu"]




parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-f', dest='Flag', type=str, default='')
parser.add_argument('-e', dest='Era', type=str, default='')

args = parser.parse_args()



Flag=args.Flag

Era=args.Era
InputDir=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+Era+"/"+Flag+"/"

os.system("mkdir -p results/")
os.system("mkdir -p results/"+Analyser)
os.system("mkdir -p results/"+Analyser + "/"+Era)

outlog = open("results/"+Analyser  + "/"+Era+"/"+Flag+".txt","w")



sample_dict = {}
sample_dict2 = {}



for channel in channels:

    Print (outlog, "Channel = " + channel)

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')

    c1 = ROOT.TCanvas('c1'+channel, channel, 800, 800)

    InPath=InputDir + "HNL_SignalLeptonOpt_SkimTree_HNMultiLep_Bkg.root"
    ##SigInPath=InputDir + "SIGMerged/HNL_SignalLeptonOpt_Type1_SS.root"

    for mass in masses:
        SigInPath=InputDir + "SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+mass+".root"
        Print (outlog, SigInPath)
        f_Bkg = ROOT.TFile(InPath)
        f_Sig = ROOT.TFile(SigInPath)
        
        HistNames=[]

        DirName = "LimitInput"
        HistName="/HNLOpt_ULHNTightV2/FillEventCutflow/MuonSR"
        if mass == "100":
            DirName = "LimitInputBDT"
            HistName="/HNLOpt_ULHNTightV2/100/FillEventCutflow/MuonSR"

        #if mass == "500":
        #    DirName = "LimitInputBDT"
        #    HistName="/HNLOpt_ULHNTightV2/500/FillEventCutflow/MuonSR"



        for k, o in getall(f_Bkg.Get(DirName)):
            if "HNLOpt" in  k:
                if mass == "100" :
                    if mass in k:
                        print mass + " " + k
                        HistNames.append(k)
                else:
                    HistNames.append(k)
                    print mass + " " + k


        Print (outlog, DirName+HistName)
                
        hsigV2 = f_Sig.Get(DirName+HistName)
        hbkgV2 = f_Bkg.Get(DirName+HistName)
        val_HNV2= GetSignificance(outlog,hsigV2,hbkgV2)
    
        for x in HistNames:
            if "Charge" in x:
                continue
            hsig = f_Sig.Get(DirName+x)
            hbkg = f_Bkg.Get(DirName+x)
            Print (outlog, "GetSignificance " + x +" ==========================")
            _sig= GetSignificance(outlog,hsig,hbkg)/val_HNV2

            _hist = x
            _hist=_hist.replace("100/","")
            _hist=_hist.replace("500/","")
            print _hist
            sample_dict2[_hist+"_"+mass] = float(_sig)
            
            if not _hist in sample_dict:
                sample_dict[_hist] = _sig
                print 
            else:
                print "sample_dict.get(x) = " + x 
                print sample_dict.get(_hist)
                #/HNLOpt_ULHNTightPFIsoLoose/500/FillEventCutflow/MuonSR x
                SSline2Tmp = sample_dict.get(_hist)
                SSline2Tmp =SSline2Tmp + _sig
                sample_dict.update({_hist:SSline2Tmp})

        

    f_Bkg.Close()


sorted_x = sorted(sample_dict.items(), key=lambda kv: kv[1])

for x in range(0, len(sorted_x)):
    Print (outlog, sorted_x[x][0] + " " + str(sorted_x[x][1]))
    for key, value in sample_dict2.items():
        if sorted_x[x][0] in key:
            keyM=key
            keyM = keyM.replace(sorted_x[x][0]+"_","")
            Print (outlog, "mN = " + keyM + ' : ' + str(value))


for x in range(0, len(sorted_x)):
    Print (outlog, sorted_x[x][0] + " " + str(sorted_x[x][1]))
