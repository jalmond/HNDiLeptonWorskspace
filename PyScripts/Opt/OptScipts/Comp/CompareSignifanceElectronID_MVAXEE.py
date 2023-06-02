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



def getall(d, basepath="/"):

    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def GetSignificance(histname,mass,f_Bkg):

    h_LimitInput = f_Bkg.Get(histname)

    UpdatedSIgnificance=[]

    SInPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/SIGMerged/HNL_SignalRegionOpt_Type1_SS_M"+str(mass)+".root"
    f_Sig = ROOT.TFile(SInPath)
    h_SigLimitInput = f_Sig.Get(histname)
    new_sig=0.
    tot_sig=0.
    tot_bkg=0.
    print(SInPath + " - " + histname)
    for xbin in range(1,h_SigLimitInput.GetNbinsX()+1):
    #for xbin in range(9,h_SigLimitInput.GetNbinsX()+1):
    #for xbin in range(1,8):
        nsig = h_SigLimitInput.GetBinContent(xbin)
        nbkg = h_LimitInput.GetBinContent(xbin)
        tot_sig =tot_sig + nsig
        if nsig < 0:
            continue

        if nbkg == 0:
            nbkg = 1
            bkgerr=1
        if nbkg > 0:
            tot_bkg=tot_bkg+nbkg
            bkgerr = h_SigLimitInput.GetBinError(xbin) + 0.2
            print "Bin " + str(xbin) + " nsig = " + str(nsig) + " bkg = " + str(nbkg) + " sig = " + str(float(nsig)/math.sqrt(float(bkgerr)*float(bkgerr)+float(nbkg))) #str(float(nsig)/float(math.sqrt(nbkg)))
            #new_sig=new_sig+float(nsig)/float(math.sqrt(nbkg))
            new_sig =new_sig +  float(nsig)/(1+math.sqrt(float(bkgerr)*float(bkgerr)+float(nbkg)))
            
            
    f_Sig.Close()

    print "GetSignificance " + SInPath + " " + histname + " SIG = " + str(new_sig)   + " total_sig = " + str(tot_sig) + " total_bkg = " + str(tot_bkg)

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
dmasses = [100,250, 500,800,1200, 2000]#GetEXO_17_028_Masses("",True)
masses =  ["100","250","500","800","1200","2000"] #GetEXO_17_028_Masses("",True)

channels = [ "ElEl"]


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

    

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2017/HNL_SignalRegionOpt_SkimTree_HNMultiLep_data.root"
    f_Bkg = ROOT.TFile(InPath)

    HistNames = []
    DefHistName=""
    for k, o in getall(f_Bkg):
        print o.ClassName(), k
        if not "ElectronSR" in k:
            continue
        if "MVABWP90_MVAECWP90" in k:
            DefHistName=k

        if not "MVAEEX" in k:
            continue

        if "LimitInput" in  k:
            #HNLOpt_UL_ElOpt_LooseTrig_ConvBConvEC_CCBCCEC_MVABWP90_MVAECWP90_ISOB0p1_ISOEC0p1_DXYB1EC1
            HistNames.append(k)
        #for key in .GetListOfKeys():
        #kname = key.GetName()
        #if key.IsFolder():


    histNamePrefix=""


    for mass in masses:


        histnames = []
        sigvalues= []
        
        for histName in HistNames:

            signi = GetSignificance(histName,mass,f_Bkg)/ GetSignificance(DefHistName,mass,f_Bkg)
            histnames.append(histName)
            sigvalues.append(signi)
            #print histName + " sig = " + str(signi)
                    

        maxvalue=0
        maxhist=""
        nBin=len(histnames)
        h_dummy = ROOT.TH1D('h_dumy', '', len(histnames), 0., len(histnames))
        
        for hist in range(0, len(histnames)):
            print histnames[hist] + " " + str(sigvalues[hist])
            h_dummy.SetBinContent(hist+1, sigvalues[hist])
            h_dummy.GetXaxis().SetBinLabel(hist+1, histnames[hist])
            if sigvalues[hist] > maxvalue:
                maxvalue=sigvalues[hist] 
                maxhist = histnames[hist]
                
        print (str(mass) + " " + channel  + " : Max sig = " + maxhist + " "  + str(maxvalue))
        
        c1 = ROOT.TCanvas('c1', '', 800, 800)
        h_dummy.Draw("hist")
        c1.SaveAs()


        filename= outdir+'/'+channel + '_OptElectron_MVAEEX_'+str(mass)

        c1.SaveAs(filename+'.pdf')
        c1.SaveAs(filename+'.png')

        os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Opt/'")
        os.system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Opt/'")
        os.system("scp " + filename+".png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Opt/")
        os.system("scp " + filename+".pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Opt/")
        print ("scp " + filename+".pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Opt/")

