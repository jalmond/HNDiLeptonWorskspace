#!/usr/bin/env python                                                                                                                                                           

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT
import sys,math
import argparse
import datetime
import mylib
from array import array
import math

import CMS_lumi, tdrstyle


sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/python')

pwd = os.getcwd()

#  THIS CODE IS TO Check Significnace of MVA cuits in SR bins

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


def GetSignificance(Print ,DefSig,nIt,histname,h_LimitInput,h_SigLimitInput,A,B,C):
    
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
        cut = A - math.exp(-pt / B) * C
        #if Debug:
        #    print "cut = "+ str(cut) + " A= " + str(A) + " B = " + str(B) + " C = " + str(C)

        sumYBkg=0
        sumYSig=0
        for ybin in range(1,h_SigLimitInput.GetNbinsY()+1):
            #if Debug:
            #    print "x/ybin " + str(xbin)+"/"+str(ybin) + "   center = " + str(h_SigLimitInput.GetXaxis().GetBinCenter(xbin)) + "/"+ str(h_SigLimitInput.GetYaxis().GetBinCenter(ybin))
            if h_SigLimitInput.GetYaxis().GetBinCenter(ybin) > cut:
                if h_LimitInput:
                    sumYBkg =sumYBkg+h_LimitInput.GetBinContent(xbin,ybin)
                    bkgErr = math.sqrt(bkgErr*bkgErr + h_LimitInput.GetBinError(xbin,ybin)*h_LimitInput.GetBinError(xbin,ybin))
                sumYSig =sumYSig+h_SigLimitInput.GetBinContent(xbin,ybin)
        tot_sig=tot_sig+sumYSig
        nbkg=nbkg+sumYBkg
        #if Debug:
        #    print "pt = " + str(pt) + " cut = " + str(cut)+ " sumBkg = " + str(nbkg) + " sumYSig = " + str(sumYSig) 
        
        #if Debug:
        #    print "sumBkg = " + str(nbkg) + " tot_sig = " + str(tot_sig)

    if sumYSig < 0:
        print "NO SIGNAL GetSignificance " + SInPath + " " + histname + " SIG = " + str(FOM)   + " total_sig = " + str(tot_sig) + " total_bkg = " + str(nbkg)

                    
    if nbkg <=0:
        nbkg = 0.2
        bkgErr = 0.2

    FOM =  float(tot_sig)/(1+math.sqrt(float(bkgErr)*float(bkgErr)+float(nbkg)))
    if Debug:
        print "GetSignificance " + SInPath + " " + histname + " SIG = " + str(FOM)   + " total_sig = " + str(tot_sig) + " total_bkg = " + str(nbkg)

        

    return FOM



ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']



# now import analysis functions                                                                                                                                                 
from HNType1_config import *

Analyser = "HNL_SignalLeptonOpt"

channels = [ "ElEl"]



parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-m', dest='Mass', default="100")
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-N', dest='NProc', default=999, type=int, help="maximum running jobs")
parser.add_argument('-I', dest='Iso', default="014")
parser.add_argument('-MI', dest='IsoType', default="Iso")
parser.add_argument('-CC', dest='ChargeCut', default="Def")
parser.add_argument('-B', dest='BinType', default="Def")
parser.add_argument('-v', dest='MVA', default="mva")
parser.add_argument('-r', dest='EtaRegion',  default="BB")
parser.add_argument('--Data', action='store_true')
parser.add_argument('--Local', action='store_true')
parser.add_argument('--nmax', dest='NMax', default=300, type=int, help="maximum running jobs")

args = parser.parse_args()

CC = args.ChargeCut
if CC == "Def":
    CC = ""

masses = [args.Mass]

for channel in channels:

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')


    latex_CMSPriliminary = ROOT.TLatex()
    latex_Lumi = ROOT.TLatex()
    
    latex_CMSPriliminary.SetNDC()
    latex_Lumi.SetNDC()
    latex_CMSPriliminary.SetTextSize(0.055)
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")                                                                                            
    latex_Lumi.SetTextSize(0.035)
    latex_Lumi.SetTextFont(42)
        

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalLeptonOpt_SkimTree_HNMultiLep_Bkg.root"
    if args.Data:
        InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalLeptonOpt_SkimTree_HNMultiLep_Data.root"
        print "InPath = " + InPath
    f_Bkg = ROOT.TFile(InPath)

    EtaNames = [args.EtaRegion]

    
    SRNames = []


    if args.BinType == "SR1":

        SRNames = ["SR1_bin1_",
                   "SR1_bin2_"]

    elif args.BinType == "SR2":

        if args.Mass == "100":

            SRNames = ["MN100_SR3_bin1_",
                       "MN100_SR3_bin2_",
                       "MN100_SR3_bin3_"]

        elif args.Mass =="250":
            
            SRNames = ["MN250_SR3_bin1_",
                       "MN250_SR3_bin2_",
                       "MN250_SR3_bin3_"]

        elif args.Mass =="500":
            
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
        

        if args.Mass == "100":

            SRNames = ["MN100_SR3_bin1_",
                       "MN100_SR3_bin2_",
                       "MN100_SR3_bin3_",
                       "SR1_bin1_",
                       "SR1_bin2_"]
            
        elif args.Mass =="250":

            SRNames = ["MN250_SR3_bin1_",
                       "MN250_SR3_bin2_",
                       "MN250_SR3_bin3_",
                       "SR1_bin1_",
                       "SR1_bin2_"]

        elif args.Mass =="500":

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

 
    

    DefHistName=""
    
    HistNames = []
    HNHistNames = []
    for x in SRNames:
        for y  in EtaNames:
            HistNames.append("MVAOpt/"+CC+x+args.IsoType+args.Iso+"__"+y+"Pt_"+args.MVA+"response_HNLOpt_UL_HNOpt")
            #MN100_SR3_bin1__EBPt_HNLOpt_UL_HNTightV2
            HNHistNames.append("NonOpt/"+x+"RegionPass__"+y+"Pt_HNLOpt_UL_HNOpt_HNTightV2")
            
            print "MVAOpt/"+CC+x+args.IsoType+args.Iso+"__"+y+"Pt_"+args.MVA+"response_HNLOpt_UL_HNOpt"
    histNamePrefix=""

    
    for mass in masses:
     
        logname = "log_"+CC+"__"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '__'+str(args.MVA)+'__'+args.IsoType+str(args.Iso)+'__'+args.BinType+'.txt'
        if args.Data:
            logname = "log_"+CC+"__"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '__'+str(args.MVA)+'__'+args.IsoType+str(args.Iso)+'__'+args.BinType+'__Data'+'.txt'

        filename_log  = open(logname ,'w')
        

        histnames = []
        sigvalues= []
        
        histnamesX=args.NProc
        if histnamesX == 999:
            histnamesX = 110
        histnamesY=1
        histnamesZ=100

        h_dummy = ROOT.TH2D('h_dummy'+mass, 'h_dummy'+mass, 110, -4,7, 100, 0., 20)
        h_dummy.GetXaxis().SetTitle("A ( A + Cexp(-pt/B))")
        h_dummy.GetYaxis().SetTitle("C")
        MaxPunzi=-999
        MaxCut=""
        
        SigHists=[]
        BkgHists=[]
        HNSigHists=[]
        HNBkgHists=[]
        SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+str(mass)+".root"
        f_Sig = ROOT.TFile(SInPath)
        if not  os.path.exists(SInPath):
            print "No file " + SInPath
            exit()
        for histName in HistNames:
            h_LimitInput = f_Bkg.Get(histName)
            h_SigLimitInput = f_Sig.Get(histName)
            SigHists.append(h_SigLimitInput)
            BkgHists.append(h_LimitInput)
        for hnhistName in HNHistNames:
            hn_LimitInput = f_Bkg.Get(hnhistName)
            hn_SigLimitInput = f_Sig.Get(hnhistName)
            HNSigHists.append(hn_SigLimitInput)
            HNBkgHists.append(hn_LimitInput)
            print hnhistName + " " 
        f_Sig.Close()

        NhistnamesX = 1
        if args.NProc == 999:
            NhistnamesX = 110

        for _A in range(0, NhistnamesX):
            for _B in range(0, histnamesY):
                for _C in range(0,histnamesZ):
                    signi=0
                    hnsigni=0
                    value_A = -4 + float(args.NProc)*0.1
                    if args.NProc == 999:
                        value_A = -4 + float(_A)*0.1

                    value_B = 13.
                    value_C = 0 + _C*0.2
                    
                    nIt = _A + _B + _C
                    
                    PrintOut= False
                    if  nIt% 50  == 0:
                        PrintOut=True
                        

                    for X in range(0,len(SigHists)):
                        hnhistSig=HNSigHists[X]
                        hnhistBkg=HNBkgHists[X]
                        hnsigni = hnsigni + GetHNSignificance(PrintOut,nIt,HNHistNames[X],hnhistBkg,hnhistSig)
                        
                    for X in range(0,len(SigHists)):
                        histSig=SigHists[X]
                        histBkg=BkgHists[X]
                        
                        sig_h= GetSignificance(PrintOut,hnsigni,nIt,HistNames[X],histBkg,histSig,value_A,value_B,value_C)

                        signi = signi + sig_h
                        if PrintOut:
                            print HistNames[X] + " Sig = " + str(sig_h)
                    histnames.append(histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C))
                    sigvalues.append(signi/hnsigni)
                    h_dummy.Fill(value_A,value_C,signi)
                    if signi > MaxPunzi:
                        MaxPunzi = signi
                        MaxCut = histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C)
                    print str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi) + " rel HNTightV2 = " + str(signi/hnsigni)
                    filename_log.write(str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi) + " rel HNTightV2 = " + str(signi/hnsigni) +'\n')
                    
        print("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi))
        filename_log.write("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi)+'\n')
        c1 = ROOT.TCanvas('c1', '', 800, 800)
        h_dummy.Draw("colz")
        c1.SaveAs()

        filename= CC+channel + '_OptElectronMVA_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"_Iso"+str(args.Iso)+args.IsoType+"__"+args.BinType+"__Bkg"
        if args.Data:
            filename= CC+channel + '_OptElectronMVA_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"_Iso"+str(args.Iso)+args.IsoType+"__"+args.BinType+"__DATA"

        c1.SaveAs(filename+'.pdf')
        c1.SaveAs(filename+'.png')

        fOut = ROOT.TFile.Open(filename+'.root','RECREATE')
        fOut.cd()
        h_dummy.Write()
        fOut.Close()
        print ("---> "  + filename+'.root' )
        
        
    f_Bkg.Close()
    if args.Local:
        os.system("rm  log*")
        os.system("rm  *.ps")
        os.system("rm *.pdf")
        os.system("rm *.png")
        os.system("rm *.root")
