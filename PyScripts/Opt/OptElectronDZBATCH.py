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

def GetSignificance(h_LimitInput,h_SigLimitInput,A,B):
    
    FOM=0
    tot_sig=0.
    nbkg=0.
    bkgErr=0.

    Debug=False
    if Debug:
        print("Pre Signal cut Int = " + str(h_SigLimitInput.Integral()))
        print("Pre Bkg cut Int = " + str(h_LimitInput.Integral()))


    if not h_SigLimitInput:
        return 0.
    if h_SigLimitInput.Integral() <= 0:
        return 0.

    
    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):

        # Get pt from X axis bin center

        pt=h_SigLimitInput.GetXaxis().GetBinCenter(xbin)
        
        # calulate Cut value
        cut = A   +  ((B-A) * (pt-10)) / 50
        if pt > 59:
            cut = B
        if Debug:
            print "cut = "+ str(cut)


        sumYBkg=0
        sumYSig=0
        for ybin in range(1,h_SigLimitInput.GetNbinsY()+1):
            if Debug:
                print "x/ybin " + str(xbin)+"/"+str(ybin) + "   center = " + str(h_SigLimitInput.GetXaxis().GetBinCenter(xbin)) + "/"+ str(h_SigLimitInput.GetYaxis().GetBinCenter(ybin))

            if h_SigLimitInput.GetYaxis().GetBinCenter(ybin) < cut:
                if h_LimitInput:
                    sumYBkg =sumYBkg+h_LimitInput.GetBinContent(xbin,ybin)
                    bkgErr = math.sqrt(bkgErr*bkgErr + h_LimitInput.GetBinError(xbin,ybin)*h_LimitInput.GetBinError(xbin,ybin))
                sumYSig =sumYSig+h_SigLimitInput.GetBinContent(xbin,ybin)
        tot_sig=tot_sig+sumYSig
        nbkg=nbkg+sumYBkg
        
        if Debug:
            print "sumBkg = " + str(nbkg) + " sumYSig = " + str(sumYSig)
            
    if nbkg <=0:
        nbkg = 0.2
        nbkgErr = 0.2

    FOM =  float(tot_sig)/(1+math.sqrt(float(bkgErr)*float(bkgErr)+float(nbkg)))
    f_Sig.Close()
    if Debug:
        print "GetSignificance " + SInPath + " " +  " SIG = " + str(FOM)   + " total_sig = " + str(tot_sig) + " total_bkg = " + str(nbkg)

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
parser.add_argument('-q', dest='Queue', default="fastq")
parser.add_argument('-N', dest='NProc', default=999, type=int, help="maximum running jobs")
parser.add_argument('-B', dest='BinType', default="Def")
parser.add_argument('-v', dest='MVA', default="MVANoIso90")
parser.add_argument('-r', dest='EtaRegion',  default="BB")
parser.add_argument('--nmax', dest='NMax', default=100, type=int, help="maximum running jobs")
parser.add_argument('--Data', action='store_true')
parser.add_argument('--Local', action='store_true')

args = parser.parse_args()

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
    
    if args.Mass == "100":
        SRNames = ["SR1_bin1_",
                   "SR1_bin2_",
                   "MN100_SR3_bin1_",
                   "MN100_SR3_bin2_",
                   "MN100_SR3_bin3_"]

    elif args.Mass =="250":
        SRNames = ["SR1_bin1_",
                   "SR1_bin2_",
                   "MN250_SR3_bin1_",
                   "MN250_SR3_bin2_",
                   "MN250_SR3_bin3_"]
        
    elif args.Mass =="500":
        SRNames = ["SR1_bin1_",
                   "SR1_bin2_",
                   "MN500_SR3_bin1_",
                   "MN500_SR3_bin2_",
                   "MN500_SR3_bin3_"]
            
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
        
            
    if args.BinType == "SR1":

        SRNames = ["SR1_bin1_",
                   "SR1_bin2_"]

    if args.BinType == "SR2":

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





    DefHistName=""
    
    HistNames = []
    for x in SRNames:
        for y  in EtaNames:
            HistNames.append("IPOpt/"+x+args.MVA+"__"+y+"Pt_DZ_HNLOpt_UL_HNOpt")

    histNamePrefix=""

    
    for mass in masses:

        logname = "log_"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '_'+str(args.MVA)+  '__'+args.BinType+'.txt'
        if args.Data:
            logname = "log_"+channel + '__'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+ '_'+str(args.MVA)+ '__'+args.BinType+'__Data.txt'
        filename_log  = open(logname,'w')

        histnames = []
        sigvalues= []
        
        histnamesX = 101
        histnamesY=101

        h_dummy = ROOT.TH2D('h_dummy'+mass, 'h_dummy'+mass, 110, -4,7, 100, 0., 20)
        h_dummy.GetXaxis().SetTitle("A ( A + Cexp(-pt/B))")
        h_dummy.GetYaxis().SetTitle("C")
        MaxPunzi=-999
        MaxCut=""
        
        SigHists=[]
        BkgHists=[]
        SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalLeptonOpt_Type1_SS_M"+str(mass)+".root"
        f_Sig = ROOT.TFile(SInPath)
        for histName in HistNames:
            print histName
            h_LimitInput = f_Bkg.Get(histName)
            h_SigLimitInput = f_Sig.Get(histName)
            SigHists.append(h_SigLimitInput)
            BkgHists.append(h_LimitInput)
            
        NhistnamesX = 101

        for _A in range(0, NhistnamesX):
            for _B in range(0, histnamesY):
                signi=0
                
                value_A = 0. + float(_A)*0.0007
                value_B = 0.0 + float(_B)*0.0007
                for X in range(0,len(SigHists)):
                    histSig=SigHists[X]
                    histBkg=BkgHists[X]
                        
                    signi = signi + GetSignificance(histBkg,histSig,value_A,value_B)

                histnames.append(histName+"_"+str(value_A)+"_"+str(value_B))
                sigvalues.append(signi)
                h_dummy.Fill(value_A,value_B,signi)
                if signi > MaxPunzi:
                    MaxPunzi = signi
                    MaxCut = histName+"_"+str(value_A)+"_"+str(value_B)
                print histName+"_"+str(value_A)+"_"+str(value_B) + " sig = " + str(signi)
                filename_log.write(histName+"_"+str(value_A)+"_"+str(value_B) + " sig = " + str(signi)+'\n')
                    
        print("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi))
        filename_log.write("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi)+'\n')
        c1 = ROOT.TCanvas('c1', '', 800, 800)
        h_dummy.Draw("colz")
        c1.SaveAs()

        filename= channel + '_OptDZElectron_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"__"+args.BinType

        if args.Data:
            filename= channel + '_OptDZElectron_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)+ "_"+str(args.MVA)+"__"+args.BinType+"__DATA"
            
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

