import os,ROOT
import mylib
from array import array

import CMS_lumi, tdrstyle
from HNType1_config import *




eras = ["2017"] 


ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

for era in eras:
    
    
    outdir = PLOT_PATH+'/BDTEff/'+era+'/'
    os.system("mkdir -p " + PLOT_PATH+'/BDTEff/')
    os.system("mkdir -p " + PLOT_PATH+'/BDTEff/'+era)

    
    c1 = ROOT.TCanvas('c1'+era, era, 800, 800)

    latex_CMSPriliminary = ROOT.TLatex()
    latex_Lumi = ROOT.TLatex()
    
    latex_CMSPriliminary.SetNDC()
    latex_Lumi.SetNDC()
    latex_CMSPriliminary.SetTextSize(0.055)
    #latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")
    latex_CMSPriliminary.DrawLatex(0.2, 0.88, "#font[62]{CMS}")
        
    latex_Lumi.SetTextSize(0.035)
    latex_Lumi.SetTextFont(42)

    h_ssww = ROOT.TH1F('h_ssww_'+era, '', len(sig_mass_list), 0 , float(len(sig_mass_list)))
    h_sswwEE = ROOT.TH1F('h_sswwEE_'+era, '', len(sig_mass_list), 0 , float(len(sig_mass_list)))

    h_ssww.SetTitle("");
    h_ssww.GetYaxis().SetLabelSize(0.04);
    h_ssww.GetYaxis().SetTitleSize(0.054);
    h_ssww.GetYaxis().SetTitleOffset(1.30);
    h_ssww.GetXaxis().SetLabelSize(0.03);
    h_ssww.GetXaxis().SetTitleSize(0.05);
    h_ssww.SetDirectory(0)
    h_ssww.Draw("Axis")

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(era))+" fb^{-1} (13 TeV)")

    
    #h_ssww.GetXaxis().SetRangeUser(0.,2E4)
    h_ssww.GetYaxis().SetRangeUser(1E-5,0.5)
    
    h_ssww.GetYaxis().SetTitle("Efficiency of DY signal EXO-17-028")
    h_ssww.GetXaxis().SetTitle('m_{N} (GeV)')
    h_ssww.Draw("histsame")
    h_sswwEE.Draw("histsame")


    lg = ROOT.TLegend(0.7, 0.6, 0.8, 0.81)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)
    lg.SetTextSize(0.03)
    
    g_mN=[]

    nbin=0
    for x in sig_mass_list :
        nbin=nbin+1
        h_ssww.GetXaxis().SetBinLabel(nbin, str(x))



    nmass=-1    
    for x in sig_mass_list :
        nmass=nmass+1
        g_mN.append(int(x))
        print "==="*40
        print "Mass = " + str(x)  + " GeV"
        mass = x

        sig =   "M"+str(x)
        

        eff_17 = GetEXO_17_028_Eff("MuMu","SR1",x, "DY") + GetEXO_17_028_Eff("MuMu","SR2",x, "DY") 
        ee_eff_17 = GetEXO_17_028_Eff("ElEl","SR1",x, "DY") + GetEXO_17_028_Eff("ElEl","SR2",x, "DY") 
        print str(x) + " " + str(ee_eff_17)
        if eff_17 <= 0:
            continue

        if os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_SignalRegionPlotter/2017/SIG/HNL_SignalRegionPlotter_DYTypeI_DF_"+sig+"_private.root"):
           
            f_sig = ROOT.TFile(  "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_SignalRegionPlotter/2017/SIG/HNL_SignalRegionPlotter_DYTypeI_DF_"+sig+"_private.root")



            NoCut = "ChannelCutFlow/MVAUL_UL/ChannelDependant_Inclusive"
            h_sig = f_sig.Get(NoCut)
            h_sigSR1 = f_sig.Get("ChannelCutFlow/MVAUL_UL/ChannelDependantSR1")
            h_sigSR2 = f_sig.Get("ChannelCutFlow/MVAUL_UL/ChannelDependantSR2")
            h_sigSR3 = f_sig.Get("ChannelCutFlow/MVAUL_UL/ChannelDependantSR3")
            
            MMNoCUt = h_sig.GetBinContent(1)
            SR= h_sigSR1.GetBinContent(1)+h_sigSR2.GetBinContent(1)+h_sigSR3.GetBinContent(1)


            EENoCUt = h_sig.GetBinContent(2)
            EESR= h_sigSR1.GetBinContent(2)+h_sigSR2.GetBinContent(2)+h_sigSR3.GetBinContent(2)



            print ("eff " + str(SR/MMNoCUt))
            print ("eff " + str((SR/MMNoCUt)/eff_17))

            #h_ssww.Fill(nmass, (SR/MMNoCUt)/eff_17)
            #h_sswwEE.Fill(nmass, (EESR/EENoCUt)/ee_eff_17)

            h_ssww.Fill(nmass, eff_17)                                                                                                                                                             
            h_sswwEE.Fill(nmass,ee_eff_17)                                                                                                                                           
            

            f_sig.Close()
            

    gr_ssww_mm = ROOT.TGraphAsymmErrors(h_ssww)
    gr_ssww_ee = ROOT.TGraphAsymmErrors(h_sswwEE)

    
    for i in range(0, gr_ssww_mm.GetN()):

        #N = gr_Data.GetY()[i]
        gr_ssww_mm.SetPointEYlow(i, 0)
        gr_ssww_mm.SetPointEYhigh(i, 0)
        gr_ssww_ee.SetPointEYlow(i, 0)
        gr_ssww_ee.SetPointEYhigh(i, 0)        
    #gr_ssww_mm = ROOT.TGraph(len(g_mN), array("d", g_mN), array("d", g_RSSMM))
    #gr_ssww_mm.SetName('gr_r_pp_mm_mN')
    gr_ssww_mm.SetMarkerStyle(20)
    gr_ssww_mm.SetMarkerSize(1.2)
    gr_ssww_ee.SetMarkerStyle(20)
    gr_ssww_ee.SetMarkerSize(1.2)

    counter = 2
    gr_ssww_mm.SetMarkerColor(counter)
    gr_ssww_mm.SetLineColor(counter)

    counter = 3
    gr_ssww_ee.SetMarkerColor(counter)
    gr_ssww_ee.SetLineColor(counter)
    
    #h_ssww.Draw("phistsame")

    #gr_ssww_mm.SetLineWidth(2)
    #gr_ssww_mm.SetMarkerSize(0.)
    #gr_ssww_mm.SetMarkerColor(ROOT.kBlack)
    #gr_ssww_mm.SetLineColor(ROOT.kBlack)
    gr_ssww_mm.Draw('p0same')
    gr_ssww_ee.Draw('p0same')

    #ROOT.gPad.Update()
    lg.AddEntry( gr_ssww_mm, 'CC DY MM', 'lp')
    lg.AddEntry( gr_ssww_ee, 'CC DY EE', 'lp')

    lg.Draw()
    
    print 'Saving ==> '+outdir+'/Graph_Qratio_MM.pdf'
    c1.SaveAs(outdir+'/Graph_Qratio_MM.pdf')
    
    
    c1.Close()
