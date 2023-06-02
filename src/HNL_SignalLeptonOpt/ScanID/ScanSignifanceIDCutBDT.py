#!/usr/bin/env python                                                                                                                                                           
import os,ROOT,sys,math
import argparse, datetime
from array import array

from mylib import *


def GetMassScale(_mass):
    
    if(float(_mass) == 100):
        return 0.001
    if(float(_mass) == 400):
        return 0.1
    return 1

def GetSignificnaceEXO_17_028(mass,dmass, method,scX):

    print("Running GetSignificnaceEXO_17_028 for mass " + mass)
    couplingSF = 1
        
    SignalRegions = ["Bin1", "Bin2"]
    
    ##### check 3 types of significance
    Signifiance = 0.
    SignifianceSB = 0.
    SignifianceP = 0.
    
    print ("GetSignificnaceEXO_17_028: Mass [" + mass+"]")
    for SR in SignalRegions:
        
        Bin = SR
        Bin = Bin.replace('Bin','SR')
        
        nBkg    = float(GetEXO_17_028_Bkg(channel, SR , mass, "" ))
        nBkgErr = GetEXO_17_028_BkgErr(channel, SR , mass, "" ) + 0.2
        nSig    = float(GetEXO_17_028_Eff(channel, Bin, mass,"DY")*GetXSecUnityCoupling(dmass,"DY") + GetEXO_17_028_Eff(channel, Bin, mass,"VBF")*GetXSecUnityCoupling(dmass,"VBF"))
        nSig    = nSig*0.1
        
        print (SR + " DY Efficiency =" + str(GetEXO_17_028_Eff(channel, Bin, mass,"DY")) + " XSEC" + str(GetXSecUnityCoupling(dmass,"DY")) + " VBF Eff = " + str(GetEXO_17_028_Eff(channel, Bin, mass,"VBF")) + " Xsec=" + str(GetXSecUnityCoupling(dmass,"VBF")))
            
            

        nSig =nSig*36500 * couplingSF 

        if nBkg> 0 :

            Signifiance   = Signifiance     +  CalculdateSignificance("Azimoth",float(nSig),nBkg, scX)
            SignifianceSB = SignifianceSB   +  CalculdateSignificance("SB",float(nSig),nBkg,scX)
            SignifianceP  = SignifianceP    +  CalculdateSignificance("Punzi",float(nSig),nBkg,scX)

        print("_"*60)
        print  (SR + " NSig = " + str(nSig ) + " NBkg="  + str(nBkg) + " +/- " + str(nBkgErr))

    print ("Muon " + str(mass) + " Za = " + str(Signifiance))
    print ("Muon " + str(mass) + " s/sqrt(B) = " + str(SignifianceSB))
    print ("Muon " + str(mass) + " Punzi = " + str(SignifianceP))
    
    return [Signifiance, SignifianceSB,SignifianceP]
    
pwd = os.getcwd()

ROOT.gErrorIgnoreLevel = ROOT.kFatal

ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

from GeneralSetup import check_lxplus_connection,GetFromConfig
check_lxplus_connection()

from  HNType1_config import *

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

for channel in channels:

    Print (outlog, "Channel = " + channel)

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')

    c1 = ROOT.TCanvas('c1'+channel, channel, 800, 800)

    InPath=InputDir + "HNL_SignalLeptonOpt_SkimTree_HNMultiLepBDT_Bkg.root"

    f_Bkg = ROOT.TFile(InPath)


    for mass in masses:

        scaleSig= GetMassScale(mass)
        
        EXO17028Sig = GetSignificnaceEXO_17_028(mass,float(mass),"",scaleSig)
        
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
