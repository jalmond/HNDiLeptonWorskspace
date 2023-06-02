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


sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')

pwd = os.getcwd()


def GetSignificance(histname,mass,f_Bkg):

    h_LimitInput = f_Bkg.Get(histname)

    UpdatedSIgnificance=[]

    SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/SIGMerged/HNL_SignalRegionPlotter_Type1_SS_M"+str(mass)+".root"
    
    f_Sig = ROOT.TFile(SInPath)
    h_SigLimitInput = f_Sig.Get(histname)
    
    new_sig=0.
    tot_sig=0.
    tot_bkg=0.
    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):
        nsig = h_SigLimitInput.GetBinContent(xbin)
        nbkg = h_LimitInput.GetBinContent(xbin)
        tot_sig =tot_sig + nsig
        if nbkg > 0:
            tot_bkg=tot_bkg+nbkg
            #print "Bin " + str(xbin) + " nsig = " + str(nsig) + " bkg = " + str(nbkg) + " sig = " + str(float(nsig)/float(math.sqrt(nbkg)))
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

Analyser = "HNL_SignalRegionPlotter"
masses = GetEXO_17_028_Masses("",True)
dmasses = GetEXO_17_028_Masses("",True)

channels = ["MuMu", "ElEl","MuEl"]

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
        
    h_sig = ROOT.TH1F('h_sig_'+channel, '', 22, 0, 22)
    imass=0
    for mass in masses:
        if mass == "1400":
            continue
        imass=imass+1
        h_sig.GetXaxis().SetBinLabel(imass, mass)

    h_sig.GetYaxis().SetLabelSize(0.04);
    h_sig.GetYaxis().SetTitleSize(0.054);
    h_sig.GetYaxis().SetTitleOffset(1.30);
    h_sig.GetXaxis().SetLabelSize(0.03);
    h_sig.GetXaxis().SetTitleSize(0.05);
    
    h_sig.Draw("Axis")
        
    
    #h_sig.GetYaxis().SetRangeUser(1E-5,2)

    h_sig.GetYaxis().SetTitle("Relative Significance #Sigma (SR)")
    h_sig.GetXaxis().SetTitle('m_{N} bin [100-1700]')
    h_sig.Draw("histsame")
    
   
    lg = ROOT.TLegend(0.6, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.025)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)

    

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Bkg.root"
    f_Bkg = ROOT.TFile(InPath)


    histNamePrefix="LimitInput/HNL_ULak8_type5_ak4_type1_ak4_vbf_type1_ak4_b_type2_M/FillEventCutflow/"

    AK8Bins = ["ak8_type1","ak8_type2","ak8_type3","ak8_type4","ak8_type5","ak8_type6"]
    AK4Bins = ["ak4_type1"]
    VBFAK4Bins = ["ak4_vbf_type1"]
    BAK4Bins = ["ak4_b_type1_L","ak4_b_type1_M","ak4_b_type1_T","ak4_b_type2_L","ak4_b_type2_M","ak4_b_type2_T"]
    

    for mass in masses:
        if mass == "1400":
            continue


        histnames = []
        sigvalues= []

        for ak8bin in AK8Bins:
            for ak4bin in AK4Bins:
                for vbfak4bin in VBFAK4Bins:
                    for bak4bin in BAK4Bins:
                        histNamePrefix = "LimitInput/HNL_UL"+ak8bin+"_"+ak4bin+"_"+vbfak4bin+"_"+bak4bin +"/FillEventCutflow/"
                        
                        histName=histNamePrefix+"/MuonSR"
                        if channel == "ElEl":
                            histName=histNamePrefix+"/ElectronSR"
        
                        if channel == "MuEl": 
                            histName=histNamePrefix+"/ElectronMuonSR"                                                                        

                        signi = GetSignificance(histName,mass,f_Bkg)
                        histnames.append(histName)
                        sigvalues.append(signi)
                        print histName + " sig = " + str(signi)
                        #for x in range(0, len(SigPerMass)):
                        #    h_sig.SetBinContent(x+1, UpdatedSIgnificance[x]/SigPerMass[x])
        
                        #h_sig.SetLineColor(ROOT.kRed)
                        #h_sig.Draw("hist")
                        #latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")                                                             

                        #latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(2016))+" fb^{-1} (13 TeV)")
                        #lg.AddEntry( h_sig, channel+' Vs EXO17028', 'l')
                        
                        
                        #lg.Draw()
                        
                        #print 'Saving ==> '+outdir+'/'+channel + '_significanceComparison.pdf'
                        
                        #c1.SaveAs(outdir+'/'+channel + '_significanceComparisonNoSSWW.pdf')
                        #    c1.SaveAs(outdir+'/'+channel + '_significanceComparisonNoSSWW.png')
                    
                        #os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/'")
                        #os.system("scp " + outdir+"/"+channel + "_significanceComparisonNoSSWW.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
                        #os.system("scp " + outdir+"/"+channel + "_significanceComparisonNoSSWW.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
                    #print ("scp " + outdir+"/"+channel + "_significanceComparisonNoSSWW.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
                    

        maxvalue=0
        maxhist=""
        for hist in range(0, len(histnames)):
            #print histnames[hist] + " " + str(sigvalues[hist])
            if sigvalues[hist] > maxvalue:
                maxvalue=sigvalues[hist] 
                maxhist = histnames[hist]
                
        print (str(mass) + " " + channel  + " : Max sig = " + maxhist + " "  + str(maxvalue))


