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
masses  = ["100","400"]#,"1000"]

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-f', dest='Flag', type=str, default='')
parser.add_argument('-I', dest='ID', type=str, default='')
parser.add_argument('-e', dest='Era', type=str, default='')
parser.add_argument('-ch', dest='Channel', type=str, default='MuMu')
parser.add_argument('--debug',action='store_true')

args = parser.parse_args()
DoDEBUG=args.debug
channels = [args.Channel]
FOM = "Azimoth"
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

HNTightArray=[]
OptArray=[]
SigResults=[]
for channel in channels:

    Print (outlog, "Channel = " + channel,True)

    InPath=InputDir + "HNL_SignalLeptonOpt_SkimTree_HNMultiLepBDT_Bkg.root"
    f_Bkg = ROOT.TFile(InPath)

    for mass in masses:

        scaleSig= Arxiv17028.GetSigScaleFactorForLimitCalc(mass)
        EXO17028Sig = Arxiv17028.GetSignalSignificance(channel, mass,scaleSig)
        
        SigInPath=InputDir + "SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+mass+".root"
        Print (outlog, SigInPath,True)
        
        f_Sig = ROOT.TFile(SigInPath)
  
        DirName = "LimitInput"
        HistName="/HNLOpt_ULHNTightV2/LimitBins/MuonSR"

        BDTMasses = ["100","400"]

        if mass in BDTMasses:
            DirName = "LimitInputBDT"
            HistName="/HNLOpt_ULHNTightV2/"+mass+"/LimitBins/MuonSR"


        hsigV2 = f_Sig.Get(DirName+HistName)
        hbkgV2 = f_Bkg.Get(DirName+HistName)
        val_HNV2= GetSignificanceArray(outlog,hsigV2,hbkgV2,FOM,scaleSig,EXO17028Sig )
        HNTightArray.append([mass,val_HNV2])
        
        DirName = "LimitInput"
        OptHistName="/"+args.ID+"/LimitBins/MuonSR"
        if mass in BDTMasses:
            DirName = "LimitInputBDT"
            OptHistName="/"+args.ID+"/"+mass+"/LimitBins/MuonSR"

        print(OptHistName)
        hsig = f_Sig.Get(DirName+OptHistName)
        hbkg = f_Bkg.Get(DirName+OptHistName)
        Print (outlog, "GetSignificance " + DirName+OptHistName +" ==========================",True)
        Optsig= GetSignificanceArray(outlog,hsig,hbkg,FOM,scaleSig,EXO17028Sig)
        OptArray.append([mass, Optsig,val_HNV2])
        
        
    f_Bkg.Close()


for x in OptArray:
    for y in range(0, len(x[1])):
        if x[2][y]> 0:
            print x[0] + " " + str(x[1][y]/x[2][y])
        else:
            print x[0] + " 0"
