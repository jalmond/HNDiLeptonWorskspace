#!/usr/bin/env python                                                                                                                                                           


### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt                                                                                                       
import os,ROOT
import sys,math

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
import argparse
import datetime
import mylib
from array import array
import math

import CMS_lumi, tdrstyle



pwd = os.getcwd()


def GetSignificance(histname,mass,f_Bkg,Era):

    h_LimitInput = f_Bkg.Get(histname)

    UpdatedSIgnificance=[]

    SInPath=os.getenv("FILE_MERGED_PATH")+"/HNL_SignalRegionOptSR1/"+Era+"/SIGMerged/HNL_SignalRegionOpt_Type1_SS_M"+str(mass)+".root"
    
    f_Sig = ROOT.TFile(SInPath)
    h_SigLimitInput = f_Sig.Get(histname)

    print(SInPath)
    print (histname)
    
    new_sig=0.
    tot_sig=0.
    tot_bkg=0.
    cent_sig=0.
    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):
        nsig = h_SigLimitInput.GetBinContent(xbin)
        nbkg = h_LimitInput.GetBinContent(xbin)
        tot_sig =tot_sig + nsig
        if nbkg > 0:
            tot_bkg=tot_bkg+nbkg
            #print "Era " + Era + " Bin " + str(xbin) + " nsig = " + str(nsig) + " bkg = " + str(nbkg) + " sig = " + str(float(nsig)/float(math.sqrt(nbkg)))
            

            new_sig=new_sig+float(nsig)/float(math.sqrt(nbkg))
    

    f_Sig.Close()

    return new_sig



ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']



# now import analysis functions                                                                                                                                                 
from HNType1_config import *

Analyser = "HNL_SignalRegionOpt"
masses = GetEXO_17_028_Masses("",True)
dmasses = GetEXO_17_028_Masses("",True)

channels = ["MuMu"]#, "ElEl","MuEl"]
Eras = ["2016"]#,"2017","2018"]

for Era in Eras:

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
        
    InPath=os.getenv("FILE_MERGED_PATH")+"/HNL_SignalRegionOptSR1/"+Era+"/HNL_SignalRegionOpt_SkimTree_HNMultiLep_Bkg.root"
    f_Bkg = ROOT.TFile(InPath)

    histNamePrefix="LimitInput/HNL_ULak8_etabin1_LV_tau21_HP_SDMassCut__ak4_type1PuL_ak4_vbf_type1_ak4_b_type2_M/FillEventCutflow/"


    s_etabins = ["etabin1_","etabin2_"]
    s_LepVeto = ["LV_","NoLV_"]
    s_Tau21Cut = ["tau21_HP_","","tau21_LP_"]
    s_SDMassCut = ["SDMassCut_",""]
    s_WQCDTagger = ["","PNTagger06", "PNTagger07","PNTagger08"]

    

    SRBins = []
    for x in s_etabins:
        for y in s_LepVeto:
            for z in s_Tau21Cut:
                for j in s_SDMassCut:
                    for k in s_WQCDTagger:
                        if "tau21" in z and "PNTagg" in k:
                            continue
                        SRBins.append(x+y+z+j+k+'_ak4_type1PuL_ak4_vbf_type1_ak4_b_type2_M')
    

    if True:

        histnames = []
        sigvalues= []
        masses = ["100", "250", "500", "800","1200","2000","5000","10000"]

        for sbin in SRBins:
            
            sig_tot=0.
            hist = "HNL_ULak8_"+sbin
            for channel in channels:
                histNamePrefix = "LimitInput/" + hist+ "/FillEventCutflow/"
                centhistNamePrefix = "LimitInput/HNL_ULak8_etabin1_LV_tau21_HP_SDMassCut__ak4_type1PuL_ak4_vbf_type1_ak4_b_type2_M/FillEventCutflow/"
                histName=histNamePrefix+"/MuonSR"
                centhistName =  centhistNamePrefix+"/MuonSR"
                
                
                if channel == "ElEl":
                    histName=histNamePrefix+"/ElectronSR"
                    centhistName =  centhistNamePrefix+"/ElectronSR"
                                
                if channel == "MuEl": 
                    centhistName =  centhistNamePrefix+"/ElectronMuonSR"
                    histName=histNamePrefix+"/ElectronMuonSR"                                                                        

                                
                for mass in masses:
                    signi = GetSignificance(histName,mass,f_Bkg,Era)
                    cernsig = GetSignificance(centhistName,mass,f_Bkg,Era)
                    sig_tot = sig_tot + signi/cernsig
            histnames.append(hist)
            sigvalues.append(sig_tot)

        maxvalue=0
        maxhist=""
        for hist in range(0, len(histnames)):
            print histnames[hist] + " " + str(sigvalues[hist])
            if sigvalues[hist] > maxvalue:
                maxvalue=sigvalues[hist] 
                maxhist = histnames[hist]
                
        print str(Era) + " : "  + (str(masses[0]) + " - " + str(masses[len(masses)-1]) +  " : Max sig = " + maxhist + " "  + str(maxvalue))


