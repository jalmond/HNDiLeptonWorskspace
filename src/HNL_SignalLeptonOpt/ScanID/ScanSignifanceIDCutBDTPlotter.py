#!/usr/bin/env python                                                                                                                                                           
import os,ROOT,sys,math
import argparse, datetime
from array import array

from mylib import *
from HNLArxiv import HNLArxiv

pwd = os.getcwd()

ROOT.gErrorIgnoreLevel = ROOT.kFatal

ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

from GeneralSetup import check_lxplus_connection,GetFromConfig
check_lxplus_connection()

#from  HNType1_config import *

Analyser = "HNL_SignalLeptonOpt"
masses  = ["100"]#,"400","1000"]

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-f', dest='Flag', type=str, default='')
parser.add_argument('-e', dest='Era', type=str, default='')
parser.add_argument('-ch', dest='Channel', type=str, default='MuMu')
parser.add_argument('--debug',action='store_true')

args = parser.parse_args()
DoDEBUG=args.debug
channels = [args.Channel]
FOM = "SB"
Flag=args.Flag
Era=args.Era
InputDir=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+Era+"/"+Flag+"/"

os.system("mkdir -p results/")
os.system("mkdir -p results/"+Analyser)
os.system("mkdir -p results/"+Analyser + "/"+Era)

outlog = open("results/"+Analyser  + "/"+Era+"/"+Flag+".txt","w")
sample_dict = {}
sample_dict2 = {}

Arxiv17028 = HNLArxiv("17028", "EXO-17-028")

for channel in channels:

    Print (outlog, "Channel = " + channel)

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')

    c1 = ROOT.TCanvas('c1'+channel, channel, 800, 800)

    InPath=InputDir + "HNL_SignalLeptonOpt_SkimTree_HNMultiLepBDT_Bkg.root"

    f_Bkg = ROOT.TFile(InPath)


    for mass in masses:

        scaleSig= Arxiv17028.GetSigScaleFactorForLimitCalc(mass)
        
        EXO17028Sig = Arxiv17028.GetSignificnaceEXO_17_028(channel, mass,scaleSig)
        
        SigInPath=InputDir + "SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+mass+".root"
        Print (outlog, SigInPath)
        
        f_Sig = ROOT.TFile(SigInPath)
        
        HistNames=[]

        DirName = "LimitInput"
        HistName="/HNLOpt_ULHNTightV2/LimitBins/MuonSR"

        BDTMasses = ["100","400"]

        if mass in BDTMasses:
            DirName = "LimitInputBDT"
            HistName="/HNLOpt_ULHNTightV2/"+mass+"/LimitBins/MuonSR"


        for k, o in GetAllObjs(f_Bkg.Get(DirName)):
            if "HNLOpt" in  k:
                if mass in BDTMasses:
                    if mass in k:
                        print mass + " " + k
                        HistNames.append(k)
                else:
                    HistNames.append(k)
                    print mass + " " + k

        Print (outlog, DirName+HistName)
        
        hsigV2 = f_Sig.Get(DirName+HistName)
        hbkgV2 = f_Bkg.Get(DirName+HistName)
        if not hsigV2 or not hbkgV2:
            print (DirName+HistName)
            print (f_Sig)
            print (f_Bkg)
            print (hsigV2) 
            print (hbkgV2) 


        val_HNV2= GetSignificance(outlog,hsigV2,hbkgV2,FOM,scaleSig,EXO17028Sig )
        
        for x in HistNames:
            if "Charge" in x:
                continue
            if "weight" in x:
                continue
            hsig = f_Sig.Get(DirName+x)
            hbkg = f_Bkg.Get(DirName+x)
            Print (outlog, "GetSignificance " + DirName+x +" ==========================")
            _sig= GetSignificance(outlog,hsig,hbkg,FOM,scaleSig,EXO17028Sig)/val_HNV2

            _hist = x
            for _m in BDTMasses:
                _hist=_hist.replace(_m+"/","")
            print _hist

            sample_dict2[_hist+"_"+mass] = float(_sig)
            
            if not _hist in sample_dict:
                sample_dict[_hist] = _sig
                print 
            else:
                print "sample_dict.get(x) = " + x 
                print sample_dict.get(_hist)
                #/HNLOpt_ULHNTightPFIsoLoose/500/LimitBins/MuonSR x
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
