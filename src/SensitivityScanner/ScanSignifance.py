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

Analyser = "SensitivityCheck"

masses  = ["100","400","1000"]

parser = argparse.ArgumentParser(description='CR plot commands')
masses  = ["100","400","1000"]
parser.add_argument('-InputFile', dest='InputFile', type=str, default='')
parser.add_argument('-e', dest='Era', type=str, default='')
parser.add_argument('-h', dest='HistName', type=str, default='')
parser.add_argument('-t', dest='tag', type=str, default='')
parser.add_argument('--debug',action='store_true')

args = parser.parse_args()
DoDEBUG=args.debug
channels = [args.Channel]
FOM = "Azimoth"
InputFile=args.InputFile
Era=args.Era
Tag=args.tag
HistName=args.HistName

InputDir=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+Era+"/"+Tag+"/"

os.system("mkdir -p results/")
os.system("mkdir -p results/"+Analyser)
os.system("mkdir -p results/"+Analyser + "/"+Era)

outlog = open("results/"+Analyser  + "/"+Era+"/"+Tag+".txt","w")
sample_dict = {}
sample_dict2 = {}

Arxiv17028 = HNLArxiv("17028", "EXO-17-028")
if DoDEBUG:
    Arxiv17028.Debug()

    
    
Print (outlog, "Channel = " + channel,True)

outdir = PLOT_PATH+'/Significance/'
os.system("mkdir -p " + PLOT_PATH+'/Significance/')

f_Bkg = ROOT.TFile(InputFile)
    
DefaultCouplingValue=0.1

for mass in masses:
    
    print ("%"*150)
    print ("Processing HNL mass {0}".format(mass))
    print ("%"*150)
    
    scaleSig     = Arxiv17028.GetSigScaleFactorForLimitCalc(mass)
    EXO17028Sig  = Arxiv17028.GetSignalSignificance(channel, mass,scaleSig,DefaultCouplingValue) ##### Set V^2=0.1 
    EXO17028NSig = Arxiv17028.GetSignalRegionYields(channel, mass,DefaultCouplingValue)
    EXO17028NBkg = Arxiv17028.GetBkgYields(channel, mass)
        

    SigInPathDY   = InputDir + "SIG/HNL_SignalLeptonOpt_DYTypeI_DF_M"+mass+"_private.root"
    SigInPathVBF  = InputDir + "SIG/HNL_SignalLeptonOpt_VBFTypeI_DF_M"+mass+"_private.root"
    SigInPathSSWW = InputDir + "SIG/HNL_SignalLeptonOpt_SSWWTypeI_SF_M"+mass+"_private.root"
    Print (outlog, SigInPathDY,True)
    Print (outlog, SigInPathVBF,True)
    Print (outlog, SigInPathSSWW,True)
    
    f_SigDY   = ROOT.TFile(SigInPathDY)
    f_SigVBF  = ROOT.TFile(SigInPathVBF)
    f_SigSSWW = ROOT.TFile(SigInPathSSWW)
    
    BDTMasses = ["100","400"]
    
    _HistName=HistName
    if mass in BDTMasses:
        _HistName= _HistName.replace("Bins/","BinsBDT/"+mass+"/")
        
    hsigDYV2   = f_SigDY.Get(HistNameComp)
    hsigVBFV2  = f_SigVBF.Get(DirName+HistName)
    hsigSSWWV2 = f_SigSSWW.Get(DirName+HistName)
    hbkgV2     = f_Bkg.Get(DirName+HistName)
    Validate(hsigDYV2,hbkgV2)

        val_HNV2= GetSignificance(outlog,Era,IDName,hsigDYV2,hsigVBFV2,hsigSSWWV2,hbkgV2,FOM,scaleSig,EXO17028Sig, EXO17028NSig,EXO17028NBkg,mass)
        
        for x in HistNames:
            if "Charge" in x:
                continue
            if "weight" in x:
                continue
            hsigDY   = f_SigDY.Get(DirName+x)
            hsigVBF  = f_SigVBF.Get(DirName+x)
            hsigSSWW = f_SigSSWW.Get(DirName+x)
            hbkg = f_Bkg.Get(DirName+x)
            print ("-"*150)
            Print (outlog, "GetSignificance for ID [V^{2}_{lN} = "+str(DefaultCouplingValue)+")]==" + DirName+x ,True)
            _sig= GetSignificance(outlog,Era,IDName,hsigDY,hsigVBF, hsigSSWW,hbkg,FOM,scaleSig,EXO17028Sig,EXO17028NSig,EXO17028NBkg,mass)/val_HNV2
            _hist = x
            for _mass in BDTMasses:
                _hist=_hist.replace(_mass+"/","")

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


print("@"*150)
print("@"*150)
print("Print out in order:")
print("@"*150)
print("@"*150)


sorted_x = sorted(sample_dict.items(), key=lambda kv: kv[1])


maxLength=50
for x in range(0, len(sorted_x)):
    if len(sorted_x[x][0]) > maxLength:
        maxLength=len(sorted_x[x][0])+10

    Print (outlog, sorted_x[x][0] + " " + str(sorted_x[x][1]),True)
    for key, value in sample_dict2.items():
        if sorted_x[x][0] in key:
            keyM=key
            keyM = keyM.replace(sorted_x[x][0]+"_","")
            Print (outlog, "mN = " + keyM + ' : ' + str(value),True)


for x in range(0, len(sorted_x)):
    Print (outlog, sorted_x[x][0] + " "*(maxLength-len(sorted_x[x][0])) + str(sorted_x[x][1]),True)

#from PlotterID import *

#hPlotter = IDPlotter(Era,Flag,args.Channel)
#hPlotter.MakeAllIDHist(sorted_x)

#for key, value in sample_dict2.items():
#    if sorted_x[len(sorted_x)-1][0] in key:
#        Print (outlog, "Max mN = " + keyM + ' : ' + str(value),True)
#    if "HNTightV2" in key:
#        Print (outlog, "max mN = " + keyM + ' : ' + str(value),True)


#hPlotter.MakeOptDHist()


