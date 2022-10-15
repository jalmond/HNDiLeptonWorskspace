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

pwd = os.getcwd()

ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

from GeneralSetup import check_lxplus_connection,GetFromConfig
check_lxplus_connection()


# now import analysis functions                                                                                                                                                 
#from HNType1_config import GetEXO_17_028_Masses

from  HNType1_config import *

Analyser = "HNL_SignalRegionPlotter"
masses = GetEXO_17_028_Masses("",True)
dmasses = GetEXO_17_028_Masses("",True)

FOM = "punzi"

channels = ["MuMu", "ElEl","MuEl"]

for channel in channels:

    print ("Channel = " + channel)

    outdir = PLOT_PATH+'/Significance/'
    os.system("mkdir -p " + PLOT_PATH+'/Significance/')


    im=-1

    SigPerMass=[]

    for mass in masses:

        couplingSF = 0.5
        if float(mass) < 500:
            couplingSF = 0.05
        elif float(mass) < 10000:
            couplingSF = 0.2
        
        couplingSF=1


        im=im+1
        if mass == "1400":
            continue
        if int(mass) > 1600:
            continue
        

        SRs = ["Bin1", "Bin2"]
        
        Signifiance = 0.
        for SR in SRs:

            Bin=SR
            Bin=Bin.replace('Bin','SR')

            nBkg = float(GetEXO_17_028_Bkg(channel, SR , mass, "" ))
            nBkgErr = GetEXO_17_028_BkgErr(channel, SR , mass, "" ) + 0.2
            nSig = float(GetEXO_17_028_Eff(channel, Bin, mass,"DY")*GetXSecUnityCoupling(dmasses[im],"DY") + GetEXO_17_028_Eff(channel, Bin, mass,"VBF")*GetXSecUnityCoupling(dmasses[im],"VBF"))
            
            print (mass + " : " + SR + " " + str(GetEXO_17_028_Eff(channel, Bin, mass,"DY")) + " " + str(GetXSecUnityCoupling(dmasses[im],"DY")) + " " + str(GetEXO_17_028_Eff(channel, Bin, mass,"VBF")) + " " + str(GetXSecUnityCoupling(dmasses[im],"VBF")))

            
            #print str(dmasses[im])
            nSig =nSig*36500 * couplingSF 
            if nBkg> 0 :
                
                if FOM == "punzi":
                    Signifiance =Signifiance +   float(nSig)/math.sqrt(float(nBkgErr)*float(nBkgErr)+float(nBkg))
                else:
                    Signifiance =Signifiance +  math.sqrt(2* ((nSig+nBkg)*math.log(1+(nSig/nBkg)) -nSig ) )
            
            print  (mass + " : " + SR + " " + str(nSig ) + " "  + str(nBkg) + " +/- " + str(nBkgErr))
            
        print (channel + " " + str(mass) + " s/sqrt(B) = " + str(Signifiance))
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
        
    h_sig = ROOT.TH1F('h_sig_'+channel, '', 16, 0, 16)
    imass=0
    for mass in masses:
        if mass == "1400":
            continue
        if mass == "1700":
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
    h_sig.GetXaxis().SetTitle('m_{N} bin [100-1500]')
    h_sig.Draw("histsame")
    
   
    lg = ROOT.TLegend(0.6, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.025)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)

    

    InPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Bkg.root"
    f_Bkg = ROOT.TFile(InPath)
    
    

    im2=-1

    UpdatedSIgnificance=[]
    for mass in masses:
        if mass == "1400":
            continue
        if int(mass) > 1700:
            continue
            
            
        histName="LimitInput/HNL_UL/FillEventCutflow/MuonSR"
        
        if channel == "ElEl":
            histName="LimitInput/HNL_UL/FillEventCutflow/ElectronSR"

        if channel == "MuEl":
            histName="LimitInput/HNL_UL/FillEventCutflow/ElectronMuonSR"

        if int(mass) < 600:

            histName="LimitInputBDT/HNL_UL/"+str(mass)+"/FillEventCutflow/MuonSR"

            if channel == "ElEl":
                histName="LimitInputBDT/HNL_UL/"+str(mass)+"/FillEventCutflow/ElectronSR"

            if channel == "MuEl":
                histName="LimitInputBDT/HNL_UL/"+str(mass)+"/FillEventCutflow/ElectronMuonSR"

        print("#"*50)
        print("Using hist " + histName)
        print("#"*50)

        h_LimitInput = f_Bkg.Get(histName)




        im2=im2+1


        SInPathDY=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/SIG/HNL_SignalRegionPlotter_DYTypeI_DF_M"+str(mass)+"_private.root"
        SInPathVBF=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/SIG/HNL_SignalRegionPlotter_VBFTypeI_DF_M"+str(mass)+"_private.root"
        SInPathSSWW=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/2016/SIG/HNL_SignalRegionPlotter_SSWWTypeI_M"+str(mass)+"_private.root"

        print SInPathVBF
        print histName
        f_Sig = ROOT.TFile(SInPathDY)
        h_SigLimitInput = f_Sig.Get(histName)

        if os.path.exists(SInPathVBF):
            print "Adding " + SInPathVBF
            f_SigVBF = ROOT.TFile(SInPathVBF)
            h_SigLimitInputVBF = f_SigVBF.Get(histName)
            h_SigLimitInput.Add(h_SigLimitInputVBF)
            h_SigLimitInput.Add(h_SigLimitInputVBF) # tmpfix                                                                                                                    
            f_SigVBF.Close()


        h_SigLimitInputSSWW = None    
        if os.path.exists(SInPathSSWW):
            f_SigSSWW = ROOT.TFile(SInPathSSWW)
            h_SigLimitInputSSWW = f_SigSSWW.Get(histName)
            f_SigSSWW.Close()



        print histName
        new_sig=0.
        tot_sig=0
        tot_bkg=0.
        tot_bkg_err=0.
        for xbin in range(1, h_SigLimitInput.GetNbinsX()+1):
            nsig = h_SigLimitInput.GetBinContent(xbin) *couplingSF 
            if h_SigLimitInputSSWW:
                nsig = nsig+  h_SigLimitInputSSWW.GetBinContent(xbin) * couplingSF*couplingSF 
            nbkg = h_LimitInput.GetBinContent(xbin)
            bkgerr = h_LimitInput.GetBinError(xbin) + 0.2
            print str(nsig)
            if nbkg > 0 and nsig > 0:
                if FOM == "punzi":
                    print ("Bin " + str(xbin) + " nsig = " + str(nsig) + " bkg = " + str(nbkg) + " err = " + str(bkgerr) + "  sig = " +str(float(nsig)/math.sqrt(float(bkgerr)*float(bkgerr)+float(nbkg))))
                else:
                    print ("Bin " + str(xbin) + " nsig = " + str(nsig) + " bkg = " + str(nbkg) + " err = " + str(bkgerr) + "  sig = " +str(math.sqrt(2* ((nsig+nbkg)*math.log(1+(nsig/nbkg)) -nsig ) )))

                if FOM == "punzi":
                    new_sig=new_sig+  float(nsig)/math.sqrt(float(bkgerr)*float(bkgerr)+float(nbkg))
                else:
                    new_sig=new_sig+  math.sqrt(2* ((nsig+nbkg)*math.log(1+(nsig/nbkg)) -nsig ) ) 
                    
                tot_sig=tot_sig+nsig
                tot_bkg=tot_bkg+nbkg
                tot_bkg_err= math.sqrt(tot_bkg_err*tot_bkg_err + bkgerr*bkgerr)
                
                
                
        print (channel + " " + str(mass) + " new s/sqrt(B) = " + str(new_sig))
        print ("1Bin " +  " " + str(mass) + " sig = " + str(tot_sig) + " bkg = " + str(tot_bkg) + " err = " + str(bkgerr) + "  signif. = " + str(tot_sig/(math.sqrt(bkgerr*bkgerr + tot_bkg))))
        if mass == "500":
            new_sig= new_sig*0.75
        UpdatedSIgnificance.append(new_sig)
        f_Sig.Close()
    
    for x in range(0, len(SigPerMass)):
        h_sig.SetBinContent(x+1, UpdatedSIgnificance[x]/SigPerMass[x])
        
    h_sig.SetLineColor(ROOT.kRed)
    h_sig.Draw("hist")
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")                                                             

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(2016))+" fb^{-1} (13 TeV)")
    lg.AddEntry( h_sig, channel+' Vs EXO17028', 'l')


    lg.Draw()

    
    print('-'*50)
    outFilePDF = outdir+'/'+channel + '_significanceComparison_BDT100-500_'+FOM+'.pdf'
    outFilePNG = outFilePDF
    outFilePNG = outFilePNG.replace('pdf','png')
    c1.SaveAs(outFilePDF)
    c1.SaveAs(outFilePNG)


    print ('Saving ==> ' + outFilePDF)
    print ('Saving ==> ' + outFilePNG)
    print('-'*50)

    os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/'")
    os.system("scp " + outFilePDF + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    os.system("scp " + outFilePNG + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    print ("scp " + outFilePDF + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    print ("scp " + outFilePNG + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/Significance/")
    

    c1.Close()

