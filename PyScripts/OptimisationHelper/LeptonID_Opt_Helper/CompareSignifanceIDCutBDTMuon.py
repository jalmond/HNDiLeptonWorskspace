#!/usr/bin/env python                                                                                                                                                           
### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT,sys,math
import argparse, datetime, mylib
from array import array
import math, CMS_lumi, tdrstyle



def Print(out, line):
    print line
    out.write(line+"\n")

def GetAllObjs(d, basepath="/"):

    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in GetAllObjs(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def GetSignificnaceEXO_17_028(mass,dmass, method):

    print("Running GetSignificnaceEXO_17_028 for mass " + mass)
    couplingSF = 1
        
    SignalRegions = ["Bin1", "Bin2"]
    
    ##### check 3 types of significance
    Signifiance = 0.
    SignifianceSB = 0.
    SignifianceP = 0.

    for SR in SignalRegions:
        
        Bin = SR
        Bin = Bin.replace('Bin','SR')
        
        nBkg    = float(GetEXO_17_028_Bkg(channel, SR , mass, "" ))
        nBkgErr = GetEXO_17_028_BkgErr(channel, SR , mass, "" ) + 0.2
        nSig    = float(GetEXO_17_028_Eff(channel, Bin, mass,"DY")*GetXSecUnityCoupling(dmass,"DY") + GetEXO_17_028_Eff(channel, Bin, mass,"VBF")*GetXSecUnityCoupling(dmass,"VBF"))
        nSig    = nSig*0.1

        print (mass + " : " + SR + " " + str(GetEXO_17_028_Eff(channel, Bin, mass,"DY")) + " " + str(GetXSecUnityCoupling(dmass,"DY")) + " " + str(GetEXO_17_028_Eff(channel, Bin, mass,"VBF")) + " " + str(GetXSecUnityCoupling(dmass,"VBF")))
            
            

        nSig =nSig*36500 * couplingSF 

        if nBkg> 0 :
            
            Signifiance =Signifiance     +  CalculdateSignificance("",float(nSig),nBkg)
            SignifianceSB =SignifianceSB +  CalculdateSignificance("SB",float(nSig),nBkg)
            SignifianceP =SignifianceP   +  CalculdateSignificance("Punzi",float(nSig),nBkg)

        print  (mass + " : " + SR + " " + str(nSig ) + " "  + str(nBkg) + " +/- " + str(nBkgErr))

    print ("Muon " + str(mass) + " Za = " + str(Signifiance))
    print ("Muon " + str(mass) + " s/sqrt(B) = " + str(SignifianceSB))
    print ("Muon " + str(mass) + " Punzi = " + str(SignifianceP))

def CalculdateSignificance(method,Nsig, Nbkg):

    ###### set Neg bins to 0
    if Nsig < 0: 
        Nsig = 0
    if Nbkg < 0.5:
        Nbkg=0.5

    if method == "SB":
        return Nsig/ math.sqrt(Nbkg +1)
    
    if method == "Punzi":
        return Nsig/math.sqrt(float(Nbkg*0.3)*float(Nbkg*0.3)+float(Nbkg))
    
    
    return  math.sqrt(2* ((Nsig+Nbkg)*math.log(1+(Nsig/Nbkg)) -Nsig ) )

    
def GetSignificance(out,h_sig, h_bkg):

    SigBins = []
    BkgBins = []

    print ("Nb bins = " + str(h_bkg.GetNbinsX()))
    print ("Ns bins = " + str(h_sig.GetNbinsX()))

    for xbin in range(1,h_sig.GetNbinsX()+1):
        SigBins.append(h_sig.GetBinContent(xbin))

    for xbin in range(1,h_bkg.GetNbinsX()+1):
        BkgBins.append(h_bkg.GetBinContent(xbin))


    Signif = 0.
    SignifSB = 0.
    SignifP = 0.

    print ("N bins = " + str(len(BkgBins)))
    for x in range(0, len(BkgBins)):
        Bkg=BkgBins[x] 
        if Bkg <0:
            Bkg = 0.5
        SigBin = SigBins[x]
        if SigBin < 0:
            SigBin = 0

        Signif = Signif + CalculdateSignificance("",SigBin,Bkg)
        SignifSB = SignifSB + CalculdateSignificance("SB",SigBin,Bkg)
        SignifP = SignifP + CalculdateSignificance("Punzi",SigBin,Bkg)

        
        Print(out, "Bin " + str(x+1)  + " sig = " + str(SigBin) + " bkg = " + str(Bkg) + " s/sqrt(B+1) = " + str(CalculdateSignificance("SB",SigBin,Bkg)) + "  Punzi = " + str(CalculdateSignificance("Punzi",SigBin,Bkg))  + " Za = " + str(CalculdateSignificance("",SigBin,Bkg))  )
    print "Signif Za = " + str(Signif)
    print "Signif SB = " + str(SignifSB)
    print "Signif Punzi = " + str(SignifP)

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
masses  = ["100", "250","400","500","1000","2000"]

FOM = "punzi"

channels = ["MuMu"]

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-f', dest='Flag', type=str, default='')
parser.add_argument('-e', dest='Era', type=str, default='')
parser.add_argument('--d',action='store_true')

args = parser.parse_args()
DoDEBUG=args.d


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

        GetSignificnaceEXO_17_028(mass,float(mass),"")
        
        SigInPath=InputDir + "SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+mass+".root"
        Print (outlog, SigInPath)
        
        f_Sig = ROOT.TFile(SigInPath)
        
        HistNames=[]

        DirName = "LimitInput"
        HistName="/HNLOpt_ULHNTightV2/LimitBins/MuonSR"

        BDTMasses = ["100"]

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
        if(DoDEBUG):
            print (DirName+HistName)
            print (f_Sig)
            print (f_Bkg)
            print (hsigV2) 
            print (hbkgV2) 

        val_HNV2= GetSignificance(outlog,hsigV2,hbkgV2)
        
        for x in HistNames:
            if "Charge" in x:
                continue
            if "weight" in x:
                continue
            hsig = f_Sig.Get(DirName+x)
            hbkg = f_Bkg.Get(DirName+x)
            Print (outlog, "GetSignificance " + DirName+x +" ==========================")
            _sig= GetSignificance(outlog,hsig,hbkg)/val_HNV2

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
