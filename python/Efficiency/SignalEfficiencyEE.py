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

ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']



# now import analysis functions                                                                                                                                                 
from HNType1_config import *

Analyser = "HNL_SignalRegionOpt"
dmasses = [100,250, 500,800,1200, 2000]#GetEXO_17_028_Masses("",True)
masses = ["100","250","500","800","1200","2000"] #GetEXO_17_028_Masses("",True)

channels = ["EE"]


for channel in channels:

    outdir = PLOT_PATH+'/SignalEfficiency/'
    os.system("mkdir -p " + PLOT_PATH+'/SignalEfficiency/')


    latex_CMSPriliminary = ROOT.TLatex()
    latex_Lumi = ROOT.TLatex()
    
    latex_CMSPriliminary.SetNDC()
    latex_Lumi.SetNDC()
    latex_CMSPriliminary.SetTextSize(0.055)
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")                                                                                            
    latex_Lumi.SetTextSize(0.035)
    latex_Lumi.SetTextFont(42)
    
   
    lg = ROOT.TLegend(0.6, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.025)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)

    histNamePrefix=""
    
    IDType = ["HNIP","HNIP2","HNIP3","HNVeto2016","HNVeto","CutBasedLooseNoIso","CutBasedMediumNoIso","CutBasedTightNoIso","MVALooseNoIso","CutBasedVetoNoIso","HNTightV2","HNTight_17028","passPOGTight","passPOGMedium","passHEEPID","passMVAID_noIso_WP80","passMVAID_noIso_WP90","passMVAID_Iso_WP80","passMVAID_Iso_WP90","HNHEEPID","SUSYTight","HN2016MVA","HN2016MVA2","HN2016MVA2CC","HN2016POG","HNOpt","TriggerTight","TriggerLoose","TightTriggerTight","TightTriggerLoose"]

    EtaReg = ["BB","EB","EE"]
    for mass in masses:
        for ID in IDType:
            for Eta in EtaReg:
                
                c1 = ROOT.TCanvas('c1', '', 800, 800)
                c1.SetLogx()
                c1.cd()
                SInPathDY="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3//HNL_SignalEfficiency/2017/SIGMerged/HNL_SignalEfficiency_Type1_SS_M"+str(mass)+".root"
                
                

                f_SigDY = ROOT.TFile(SInPathDY)
                histname="SignalRecoEE/Electron_pt_"+Eta+"_"+ID
                def_histname="SignalRecoEE/Electron_pt_"+Eta+"_TriggerLoose"

                #Electron_pt_EE_NoCut;1
                #KEY: TH1DElectron_pt_EE_SUSYTight;1
                #KEY: TH1DElectron_pt_EE_TightTriggerLoose;1
                #KEY: TH1DElectron_pt_EE_TightTriggerTight;1
                #KEY: TH1DElectron_pt_EE_TriggerLoose;1
                #KEY: TH1DElectron_pt_EE_TriggerTight
                
                h_sigDY = f_SigDY.Get(histname)
                h_sigDef = f_SigDY.Get(def_histname)
                h_sigDY.Divide(h_sigDef)
                
                h_sigDY.GetYaxis().SetLabelSize(0.04)
                h_sigDY.GetYaxis().SetTitleSize(0.054)
                h_sigDY.GetYaxis().SetTitleOffset(1.30)
                h_sigDY.GetXaxis().SetLabelSize(0.03)
                h_sigDY.GetXaxis().SetTitleSize(0.05)
                h_sigDY.GetYaxis().SetRangeUser(0.5,1.1)
                h_sigDY.Draw("Axis")

                h_sigDY.GetYaxis().SetTitle("#epsilon ID")
                h_sigDY.GetXaxis().SetTitle('p_{T} GeV')
                h_sigDY.Draw("Axis")
                h_sigDY.Draw("histEsame")

                latex_reg  = ROOT.TLatex()
            
                latex_reg.SetNDC()
                latex_reg.SetTextSize(0.035)
                latex_reg.DrawLatex(0.75, 0.65, Eta)
        

                c1.SaveAs()
        
                Hist=ID+'_Eff_'+channel + '_'+Eta+ '_Eff_'+str(mass)
                c1.SaveAs(outdir+'/'+Hist+'.pdf')
                c1.SaveAs(outdir+'/'+Hist+'.png')
            
                os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Efficiency/'")
                os.system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Efficiency/'")
                os.system("scp " + outdir+"/"+Hist+".png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Efficiency/")
                os.system("scp " + outdir+"/"+Hist+".pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Efficiency/")
                print ("scp " + outdir+"/"+Hist+".pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Efficiency/")
