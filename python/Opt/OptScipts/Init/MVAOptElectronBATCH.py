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

def GetSignificance(h_LimitInput,h_SigLimitInput,A,B,C):
    
    FOM=0
    tot_sig=0.
    nbkg=0.
    bkgErr=0.

    Debug=False
    if Debug:
        print(SInPath + " - " + histname)
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
        cut = A - math.exp(-pt / B) * C
        if Debug:
            print "cut = "+ str(cut)

        sumYBkg=0
        sumYSig=0
        for ybin in range(1,h_SigLimitInput.GetNbinsY()+1):
            if Debug:
                print "x/ybin " + str(xbin)+"/"+str(ybin) + "   center = " + str(h_SigLimitInput.GetXaxis().GetBinCenter(xbin)) + "/"+ str(h_SigLimitInput.GetYaxis().GetBinCenter(ybin))
            if h_SigLimitInput.GetYaxis().GetBinCenter(ybin) > cut:
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
        nbkg = 0.2

    FOM =  float(tot_sig)/(1+math.sqrt(float(bkgErr)*float(bkgErr)+float(nbkg)))
    f_Sig.Close()
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

Analyser = "HNL_SignalRegionOpt"

channels = [ "ElEl"]



parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-m', dest='Mass', default="100")
parser.add_argument('-t', dest='Tag', default="Default")
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-q', dest='Queue', default="fastq")
parser.add_argument('-N', dest='NProc', default=1, type=int, help="maximum running jobs")
parser.add_argument('-r', dest='EtaRegion',  default="BB")
parser.add_argument('--nmax', dest='NMax', default=100, type=int, help="maximum running jobs")
parser.add_argument('--reduction', dest='Reduction', default=1, type=float)
parser.add_argument('--memory', dest='Memory', default=0, type=float)
parser.add_argument('--batchname',dest='BatchName', default="")
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
        

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalRegionOpt_SkimTree_HNMultiLep_Bkg.root"
    f_Bkg = ROOT.TFile(InPath)

    EtaNames = [args.EtaRegion]
    SRNames = ["SR1_bin1",
               "SR1_bin2",
               "SR1_bin3",
               "SR1_bin4",
               "SR1_bin5",
               "SR1_bin6",
               "SR1_bin7",
               "SR2_bin1",
               "SR2_bin2",
               "SR3_bin1",
               "SR3_bin2",
               "SR3_bin3",
               "SR3_bin4",
               "SR3_bin5",
               "SR3_bin6",
               "SR3_bin7",
               "SR3_bin8",
               "SR3_bin9",
               "SR3_bin10",
               "SR3_bin11",
               "SR3_bin12",
               "SR3_bin13",
               "SR3_bin14",
               "SR3_bin15",
               "SR3_bin16"]
    #    SRNames = [ "SR3_bin4",
    #              "SR3_bin5",
    #              "SR3_bin6",
    #              "SR3_bin7",
    #             "SR3_bin10"]
    
    DefHistName=""

    

    HistNames = []
    for x in SRNames:
        for y  in EtaNames:
            HistNames.append("MVAOpt/"+x+"__"+y+"Pt_mvaresponse_HNLOpt_UL_HNOpt")

    histNamePrefix=""

    
    for mass in masses:
        filename_log  = open(channel + 'log_'+args.EtaRegion+'_'+str(mass)+'_'+str(args.NProc)+'.txt','w')
        

        histnames = []
        sigvalues= []
        
        histnamesX=args.NProc
        histnamesY=1
        histnamesZ=100

        h_dummy = ROOT.TH3D('h_dummy'+mass, 'h_dummy'+mass, 100, -8.,8., 150, 0., 15, 100, -10.,10)        
        MaxPunzi=-999
        MaxCut=""
        
        SigHists=[]
        BkgHists=[]
        SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalRegionOpt_Type1_SS_M"+str(mass)+".root"
        f_Sig = ROOT.TFile(SInPath)
        for histName in HistNames:
            h_LimitInput = f_Bkg.Get(histName)
            h_SigLimitInput = f_Sig.Get(histName)
            SigHists.append(h_SigLimitInput)
            BkgHists.append(h_LimitInput)
            
        for _A in range(0, 1):
            for _B in range(0, histnamesY):
                for _C in range(0,histnamesZ):
                    signi=0

                    for X in range(0,len(SigHists)):
                        histSig=SigHists[X]
                        histBkg=BkgHists[X]
                        
                        value_A = -4 + float(args.NProc)*0.1
                        value_B = 13. 
                        value_C = 0 + _C*0.2
                        signi = signi + GetSignificance(histBkg,histSig,value_A,value_B,value_C)
                        
                    histnames.append(histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C))
                    sigvalues.append(signi)
                    if signi > MaxPunzi:
                        MaxPunzi = signi
                        MaxCut = histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C)
                    print histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi)
                    filename_log.write(histName+"_"+str(value_A)+"_"+str(value_B)+"_"+str(value_C) + " sig = " + str(signi)+'\n')
                    h_dummy.Fill(value_A,value_B,value_C, signi)
                    
        print("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi))
        filename_log.write("Max punzi = " + MaxCut + " punzi = " + str(MaxPunzi)+'\n')
        c1 = ROOT.TCanvas('c1', '', 800, 800)
        h_dummy.Draw("LEGO2Z")
        c1.SaveAs()

        filename= channel + '_OptElectronMVA_'+args.EtaRegion+'_3D_'+str(mass)+"_"+str(args.NProc)

        c1.SaveAs(filename+'.pdf')
        c1.SaveAs(filename+'.png')

        fOut = ROOT.TFile.Open(filename+'.root','RECREATE')
        fOut.cd()
        h_dummy.Write()
        fOut.Close()
        print ("---> "  + filename+'.root' )
        
        
    f_Bkg.Close()
