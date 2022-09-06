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




ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']



# now import analysis functions                                                                                                                                                 
from HNType1_config import *


masses = GetEXO_17_028_Masses("",True)
dmasses = GetEXO_17_028_Masses("",True)
print "masses = " + str(len(masses))

channels = ["MuMu"]#, "ElEl","MuEl"]

for channel in channels:
    
    print ("Channel " + channel)
    
    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')

    im=-1

    SigPerMass=[]
    for mass in masses:
        print "Mass = " + str(mass)
        im=im+1
        SRs = ["Bin1", "Bin2"]
        
        Signifiance = 0.
        for SR in SRs:

            Bin=SR
            Bin=Bin.replace('Bin','SR')

            nBkg = GetEXO_17_028_Bkg(channel, SR , mass, "" )
            nSig = GetEXO_17_028_Eff(channel, Bin, mass,"DY")*GetXSecUnityCoupling(dmasses[im],"DY") + GetEXO_17_028_Eff(channel, Bin, mass,"VBF")*GetXSecUnityCoupling(dmasses[im],"VBF")

            print str(GetEXO_17_028_Eff(channel, Bin, mass,"DY")) + " " + str(GetXSecUnityCoupling(dmasses[im],"DY")) + " " + str(GetEXO_17_028_Eff(channel, Bin, mass,"VBF")) + " " + str(GetXSecUnityCoupling(dmasses[im],"VBF"))

            

            #print str(dmasses[im])
            nSig =nSig*36500
            Signifiance =Signifiance + float(nSig)/math.sqrt(float(nBkg))
            
        print channel + " " + str(mass) + " s/sqrt(B) = " + str(Signifiance)
        SigPerMass.append(Signifiance)
    c1 = ROOT.TCanvas('c1'+channel, channel, 800, 800)
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
        imass=imass+1
        h_sig.GetXaxis().SetBinLabel(imass, mass)

    h_sig.GetYaxis().SetLabelSize(0.04);
    h_sig.GetYaxis().SetTitleSize(0.054);
    h_sig.GetYaxis().SetTitleOffset(1.30);
    h_sig.GetXaxis().SetLabelSize(0.03);
    h_sig.GetXaxis().SetTitleSize(0.05);
    
    h_sig.Draw("Axis")
        
    
    #h_sig.GetYaxis().SetRangeUser(1E-5,2)

    h_sig.GetYaxis().SetTitle("Significance #Sigma (SR)")
    h_sig.GetXaxis().SetTitle('m_{N} bin [100-1700]')
    h_sig.Draw("histsame")
    
   
    lg = ROOT.TLegend(0.6, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.025)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)
    
    for x in range(0, len(SigPerMass)):
        h_sig.SetBinContent(x+1, SigPerMass[x])

    h_sig.SetLineColor(ROOT.kRed)
    h_sig.Draw("hist")
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")                                                             

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(2016))+" fb^{-1} (13 TeV)")
    lg.AddEntry( h_sig, channel+' EXO17028', 'l')


    lg.Draw()

    print 'Saving ==> '+outdir+'/'+channel + '_significance.pdf'

    c1.SaveAs(outdir+'/'+channel + '_significance.pdf')
    c1.SaveAs(outdir+'/'+channel + '_significance.png')

    os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/'")
    os.system("scp " + outdir+"/"+channel + "_significance.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    os.system("scp " + outdir+"/"+channel + "_significance.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    print ("scp " + outdir+"/"+channel + "_significance.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    

    c1.Close()

