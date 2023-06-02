#!/usr/bin/env python                                                                                                                                                           

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT
import sys,math
import argparse
import datetime
import mylib
from array import array
import math

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/python')

from HNType1_config import *
from OptConfig import *

pwd = os.getcwd()

#  THIS CODE IS TO Check Significnace of MVA cuits in SR bins

SetupOpt()

PLOT_PATH = os.environ['PLOT_PATH']
Analyser = "HNL_SignalLeptonOpt"
channels = [ "ElEl"]


parser = GetParser("Iso")
args = parser.parse_args()
masses = [args.Mass]

for channel in channels:

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')
        

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalLeptonOpt_SkimTree_HNMultiLep_Bkg.root"
    if args.Data:
        InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalLeptonOpt_SkimTree_HNMultiLep_Data.root"
        print "InPath = " + InPath
    f_Bkg = ROOT.TFile(InPath)

    EtaNames = [args.EtaRegion]
    
    SRNames = GetSRBins(args.BinType,args.Mass)

    
    HistNames = []
    HNHistNames = []
    for x in SRNames:
        for y  in EtaNames:
            HistNames.append("IPOpt/"+x+args.MVA+"__"+y+"Pt_DXY_HNLOpt_UL_HNOpt")
            HNHistNames.append("NonOpt/"+x+"RegionPass__"+y+"Pt_HNLOpt_UL_HNOpt_HNTightV2")

    histNamePrefix=""

    
    for mass in masses:


        logname =  "log_"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '_'+str(args.MVA) + '__'+args.BinType+'.txt'
        if args.Data:
            logname =  "log_"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '_'+str(args.MVA) + '__'+args.BinType+'__Data.txt'                  
        filename_log  = open(logname,'w')
        

        histnames = []
        sigvalues= []
        
        histnamesX=args.NProc
        if histnamesX == 999:
            histnamesX = 100
        histnamesY=1
        if args.EtaRegion == "EE":
            histnamesY=100

        MaxPunzi=-999
        RelMaxPunzi=-999
        MaxCut=""
        
        SigHists=[]
        BkgHists=[]
        HNSigHists=[]
        HNBkgHists=[]
        SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+str(mass)+".root"
        f_Sig = ROOT.TFile(SInPath)
        for histName in HistNames:
            print histName
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
            NhistnamesX = 101

        for _A in range(0, NhistnamesX):
            for _B in range(0, histnamesY):
                signi=0
                hnsigni=0

                value_A = 0.01 + float(args.NProc)*0.0001

                if args.NProc == 999:
                    value_A = 0.01 + float(_A)*0.0001
                    
                value_B = 0.01
                value_C = 0

                if args.EtaRegion == "EE":
                    value_A = 0.01 + float(_A)*0.0003
                    value_B = 0.01 + float(_B)*0.0001


                nIt = _A + _B

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

                    sig_h= GetSignificance("DXY", PrintOut,SInPath,nIt,HistNames[X],histBkg,histSig,value_A,value_B,value_C)
                    signi = signi + sig_h
                    if  PrintOut:
                        print HistNames[X] + " Sig = " + str(sig_h)

                histnames.append(histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C))
                sigvalues.append(signi)

                if signi > MaxPunzi:
                    MaxPunzi = signi
                    MaxCut = histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C)
                print histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi)+ " rel HNTightV2 = " + str(signi/hnsigni)
                filename_log.write(histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi)+  " rel HNTightV2 = " + str(signi/hnsigni) +'\n')
                    
        print("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi))
        print("RelMax punzi = " + MaxCut + " punzi = " + str(RelMaxPunzi))

        filename_log.write("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi)+'\n')
        filename_log.write("RelMax punzi = " + MaxCut + " punzi = " + str(RelMaxPunzi)+'\n')

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        c1.SaveAs()

        filename= channel + '_OptDXYElectron_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"__"+args.BinType
        if args.Data:
            filename= channel + '_OptDXYElectron_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"__"+args.BinType+"__DATA"

        c1.SaveAs(filename+'.pdf')
        c1.SaveAs(filename+'.png')

        fOut = ROOT.TFile.Open(filename+'.root','RECREATE')
        fOut.cd()

        fOut.Close()
        print ("---> "  + filename+'.root' )
        
        
    f_Bkg.Close()
    if args.Local:
        os.system("rm  log*")
        os.system("rm  *.ps")
        os.system("rm *.pdf")
        os.system("rm *.png")
        os.system("rm *.root")
