import os,ROOT
import mylib
from array import array
import math 

import CMS_lumi, tdrstyle


def GetError(num, den, num_err, den_err):
    
    A= num/den
    dA = math.sqrt( (num_err/num)*(num_err/num)  + (den_err/den)*(den_err/den)  )* A

    return dA


def GetSignalList(era, signalChannel):
    
    SampleList= []
    outSig=[]
    with open(os.getenv('SKFlat_WD')+'/data/Run2UltraLegacy_v3/'+era+'/Sample/SampleSummary_Signal_Type1.txt','r') as f:
            for line in f:
                if len(line.split())>0:
                    SampleList.append(line.split()[0])
    os.system("mkdir -p " + os.getenv('SKFlat_WD')+ '/runJobs/HNL_SignalStudies/Signals/'+era)

    for signal in SampleList:
        if signalChannel in signal :
            outSig.append(signal)
    return outSig



eras = ["2016preVFP", "2016postVFP","2017","2018"]


eras = ["2018"] 


sig_mass_list =[]
for era in eras:

    List = GetSignalList(era,"VBF") #+   GetSignalList(era,"VBF") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("VBFTypeI_NLO_DF_M","")
        
        if not int(mass) in sig_mass_list:
            sig_mass_list.append(int(mass))
        continue

sig_mass_list.sort()

channel = "Muon"
sig_pre = "VBFTypeI"
mm_phist = ["SS_Mu+Mu+"]
mm_mhist = ["SS_Mu-Mu-"]
ee_phist = ["SS_El+El+"]
ee_mhist = ["SS_El-El-"]
em_phist = ["SS_Mu+El+","SS_El+Mu+"]
em_mhist = ["SS_Mu-El-","SS_El-Mu-"]


ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

for era in eras:
    
    
    outdir = PLOT_PATH+'/CheckRatioQ/'+era+'/'
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioQ/')
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioQ/'+era)

    
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

    h_vbf = ROOT.TH1F('h_vbf_'+era, '', 3000, 0, 3000) 
    #len(sig_mass_list), 0 , float(len(sig_mass_list)))

    #h_vbf.SetTitle("");
    h_vbf.GetYaxis().SetLabelSize(0.04);
    h_vbf.GetYaxis().SetTitleSize(0.054);
    h_vbf.GetYaxis().SetTitleOffset(1.30);
    h_vbf.GetXaxis().SetLabelSize(0.03);
    h_vbf.GetXaxis().SetTitleSize(0.05);

    h_vbf.Draw("Axis")

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(era))+" fb^{-1} (13 TeV)")

    
    #h_vbf.GetXaxis().SetRangeUser(0.,2E4)
    h_vbf.GetYaxis().SetRangeUser(1E-5,10)
    
    h_vbf.GetYaxis().SetTitle("Ration of ++/--")
    h_vbf.GetXaxis().SetTitle('m_{N} (GeV)')
    h_vbf.Draw("histsame")

    nbin=0

    h_vbf_mm = h_vbf.Clone("h_vbf_mm"+era)
    h_vbf_ee = h_vbf.Clone("h_vbf_ee"+era)
    h_vbf_em = h_vbf.Clone("h_vbf_em"+era)



    lg = ROOT.TLegend(0.8, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.015)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)
    
    g_mN=[]


    g_RSS=[]
    g_RSS_exl=[]
    g_RSS_exh=[]
    g_RSS_eyl=[]
    g_RSS_eyh=[]

    g_RSSMM=[]
    g_RSSMM_exl=[]
    g_RSSMM_exh=[]
    g_RSSMM_eyl=[]
    g_RSSMM_eyh=[]

    g_RSSEE=[]
    g_RSSEE_exl=[]
    g_RSSEE_exh=[]
    g_RSSEE_eyl=[]
    g_RSSEE_eyh=[]


    g_RSSEM=[]
    g_RSSEM_exl=[]
    g_RSSEM_exh=[]
    g_RSSEM_eyl=[]
    g_RSSEM_eyh=[]



    nbin=0


    nmass=-1    
    for x in sig_mass_list :
        nmass=nmass+1
        g_mN.append(float(x))
        print "==="*40
        print "Mass = " + str(x)  + " GeV"
        mass = x

        sigVBF=""

        sigVBF =  "VBFTypeI_NLO_DF_M"+str(x)
        

           
        tot_plus=0
        tot_minus=0

        tot_plus_vbf_mm=0
        tot_minus_vbf_mm=0

        tot_plus_vbf_ee=0
        tot_minus_vbf_ee=0

        tot_plus_vbf_em=0
        tot_minus_vbf_em=0


        tot_plus_err=0
        tot_minus_err=0

        tot_plus_vbf_mm_err=0
        tot_minus_vbf_mm_err=0

        tot_plus_vbf_ee_err=0
        tot_minus_vbf_ee_err=0

        tot_plus_vbf_em_err=0
        tot_minus_vbf_em_err=0

        




        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")

            
            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)
                y_err = h_sig.GetBinError(z+1)



                bl = h_sig.GetXaxis().GetBinLabel(z+1) 

                if bl in mm_phist:
                    tot_plus_vbf_mm=tot_plus_vbf_mm+y
                    tot_plus_vbf_mm_err = math.sqrt(tot_plus_vbf_mm_err*tot_plus_vbf_mm_err + y_err*y_err)
                if bl in mm_mhist:
                    tot_minus_vbf_mm=tot_minus_vbf_mm+y
                    tot_minus_vbf_mm_err = math.sqrt(tot_minus_vbf_mm_err*tot_minus_vbf_mm_err + y_err*y_err)

                                        
                if bl in ee_phist:
                    tot_plus_vbf_ee=tot_plus_vbf_ee+y
                    tot_plus_vbf_ee_err = math.sqrt(tot_plus_vbf_ee_err*tot_plus_vbf_ee_err + y_err*y_err)

                if bl in ee_mhist:
                    tot_minus_vbf_ee=tot_minus_vbf_ee+y
                    tot_minus_vbf_ee_err = math.sqrt(tot_minus_vbf_ee_err*tot_minus_vbf_ee_err + y_err*y_err)

                if bl in em_phist:
                    tot_plus_vbf_em=tot_plus_vbf_em+y
                    tot_plus_vbf_em_err = math.sqrt(tot_plus_vbf_em_err*tot_plus_vbf_em_err + y_err*y_err)

                if bl in em_mhist:
                    tot_minus_vbf_em=tot_minus_vbf_em+y
                    tot_minus_vbf_em_err = math.sqrt(tot_minus_vbf_em_err*tot_minus_vbf_em_err + y_err*y_err)

                
            tot_plus=tot_plus+tot_plus_vbf_mm+tot_plus_vbf_ee+tot_plus_vbf_em
            tot_minus=tot_minus+tot_minus_vbf_mm+tot_minus_vbf_ee+tot_minus_vbf_em
            tot_plus_err = math.sqrt(tot_plus_vbf_mm_err*tot_plus_vbf_mm_err + tot_plus_vbf_ee_err*tot_plus_vbf_ee_err + tot_plus_vbf_em_err*tot_plus_vbf_em_err)
            tot_minus_err = math.sqrt(tot_minus_vbf_mm_err*tot_minus_vbf_mm_err + tot_minus_vbf_ee_err*tot_minus_vbf_ee_err + tot_minus_vbf_em_err*tot_minus_vbf_em_err)
            
            

            print "["+sigVBF+"] [MuMu] Ratio ++/-- =  "+ str(tot_plus_vbf_mm/tot_minus_vbf_mm) + " +/- " + str(GetError(tot_plus_vbf_mm, tot_minus_vbf_mm, tot_plus_vbf_mm_err, tot_minus_vbf_mm_err))
            print "["+sigVBF+"] [ElEl] Ratio ++/-- =  "+ str(tot_plus_vbf_ee/tot_minus_vbf_ee) + " +/- " + str(GetError(tot_plus_vbf_ee, tot_minus_vbf_ee, tot_plus_vbf_ee_err, tot_minus_vbf_ee_err))
            print "["+sigVBF+"] [ElMu] Ratio ++/-- =  "+ str(tot_plus_vbf_em/tot_minus_vbf_em) + " +/- " + str(GetError(tot_plus_vbf_em, tot_minus_vbf_em, tot_plus_vbf_em_err, tot_minus_vbf_em_err))

            h_vbf_mm.Fill(nmass, tot_plus_vbf_mm/tot_minus_vbf_mm)
            h_vbf_ee.Fill(nmass, tot_plus_vbf_ee/tot_minus_vbf_ee)
            h_vbf_em.Fill(nmass, tot_plus_vbf_em/tot_minus_vbf_em)

            f_sig.Close()
            
            g_RSS.append(tot_plus/tot_minus)
            g_RSS_exl.append(0)
            g_RSS_exh.append(0)
            g_RSS_eyl.append(GetError(tot_plus, tot_minus, tot_plus_err, tot_minus_err))
            g_RSS_eyh.append(GetError(tot_plus, tot_minus, tot_plus_err, tot_minus_err))

            
            g_RSSMM.append(tot_plus_vbf_mm/tot_minus_vbf_mm)
            g_RSSMM_exl.append(0)
            g_RSSMM_exh.append(0)
            g_RSSMM_eyl.append(GetError(tot_plus_vbf_mm, tot_minus_vbf_mm, tot_plus_vbf_mm_err, tot_minus_vbf_mm_err))
            g_RSSMM_eyh.append(GetError(tot_plus_vbf_mm, tot_minus_vbf_mm, tot_plus_vbf_mm_err, tot_minus_vbf_mm_err))

            g_RSSEE.append(tot_plus_vbf_ee/tot_minus_vbf_ee)
            g_RSSEE_exl.append(0)
            g_RSSEE_exh.append(0)
            g_RSSEE_eyl.append(GetError(tot_plus_vbf_ee, tot_minus_vbf_ee, tot_plus_vbf_ee_err, tot_minus_vbf_ee_err))
            g_RSSEE_eyh.append(GetError(tot_plus_vbf_ee, tot_minus_vbf_ee, tot_plus_vbf_ee_err, tot_minus_vbf_ee_err))


            g_RSSEM.append(tot_plus_vbf_em/tot_minus_vbf_em)
            g_RSSEM_exl.append(0)
            g_RSSEM_exh.append(0)
            g_RSSEM_eyl.append(GetError(tot_plus_vbf_em, tot_minus_vbf_em, tot_plus_vbf_em_err, tot_minus_vbf_em_err))
            g_RSSEM_eyh.append(GetError(tot_plus_vbf_em, tot_minus_vbf_em, tot_plus_vbf_em_err, tot_minus_vbf_em_err))

     

        print "-"*40    
        print "[Total] Ratio ++/-- =  "+ str(tot_plus/tot_minus)
        print ""*40    
            

    # gr_vbf_mm = ROOT.TGraphAsymmErrors(h_vbf_mm)
    # #gr_vbf_ee = ROOT.TGraphAsymmErrors(h_vbf_ee)
    #gr_vbf_em = ROOT.TGraphAsymmErrors(h_vbf_em)
  
    for x in g_RSS:
        print x

    gr_vbf_mm  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSMM),array("d",  g_RSSMM_exl),array("d",  g_RSSMM_exh),array("d",  g_RSSMM_eyl),array("d",  g_RSSMM_eyh));
    gr_vbf_ee  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEE),array("d",  g_RSSEE_exl),array("d",  g_RSSEE_exh),array("d",  g_RSSEE_eyl),array("d",  g_RSSEE_eyh));
    gr_vbf_em  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEM),array("d",  g_RSSEM_exl),array("d",  g_RSSEM_exh),array("d",  g_RSSEM_eyl),array("d",  g_RSSEM_eyh));


    gr_vbf_tot  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSS),array("d",  g_RSS_exl),array("d",  g_RSS_exh),array("d",  g_RSS_eyl),array("d",  g_RSS_eyh));


    gr_vbf_tot.SetMarkerStyle(18)
    gr_vbf_tot.SetMarkerSize(1.1)

    counter = 1
    gr_vbf_tot.SetMarkerColor(counter)
    gr_vbf_tot.SetLineColor(counter)

        
    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSMM[x])
    counter = 2
    gr_vbf_mm.SetMarkerColor(counter)
    gr_vbf_mm.SetLineColor(counter)




    gr_vbf_ee.SetMarkerStyle(21)
    gr_vbf_ee.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEE[x])
    counter = 3
    gr_vbf_ee.SetMarkerColor(counter)
    gr_vbf_ee.SetLineColor(counter)

    gr_vbf_em.SetMarkerStyle(22)
    gr_vbf_em.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEM[x])
    counter = 4
    gr_vbf_em.SetMarkerColor(counter)
    gr_vbf_em.SetLineColor(counter)


    
    gr_vbf_tot.SetLineColor(ROOT.kGreen-2) 
    gr_vbf_mm.SetLineColor(ROOT.kGreen-2) 
    gr_vbf_ee.SetLineColor(ROOT.kRed) 
    gr_vbf_em.SetLineColor(ROOT.kCyan) 

    gr_vbf_tot.SetFillColor(ROOT.kGreen-2)
    gr_vbf_mm.SetFillColor(ROOT.kGreen-2)
    gr_vbf_ee.SetFillColor(ROOT.kRed)
    gr_vbf_em.SetFillColor(ROOT.kCyan)

    
    #h_vbf_mm.Draw("histsame")
    #h_vbf_ee.Draw("histsame")
    #h_vbf_em.Draw("histsame")

    #gr_vbf_mm.SetLineWidth(2)
    #gr_vbf_mm.SetMarkerSize(0.)
    #gr_vbf_mm.SetMarkerColor(ROOT.kBlack)
    #gr_vbf_mm.SetLineColor(ROOT.kBlack)

    gr_vbf_tot.SetFillStyle(3010)
    gr_vbf_mm.SetFillStyle(3010)
    gr_vbf_ee.SetFillStyle(3010)
    gr_vbf_em.SetFillStyle(3010)
    gr_vbf_mm.Draw('psameE3')

    gr_vbf_ee.Draw('psameE3')
    gr_vbf_em.Draw('psameE3')

    gr_vbf_tot.Draw('CpsameE3')

    #ROOT.gPad.Update()
    lg.AddEntry( gr_vbf_mm, 'VBF MM', 'lp')
    lg.AddEntry( gr_vbf_ee, 'VBF EE', 'lp')
    lg.AddEntry( gr_vbf_em, 'VBF EM', 'lp')
    lg.AddEntry( gr_vbf_tot, 'VBF Sum', 'lp')

    lg.Draw()
    
    print 'Saving ==> '+outdir+'/Graph_Qratio_VBF.pdf'

    c1.SaveAs(outdir+'/Graph_Qratio_VBF.pdf')
    
    
    c1.Close()
