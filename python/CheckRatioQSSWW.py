import os,ROOT
import mylib
from array import array

import CMS_lumi, tdrstyle




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

    List = GetSignalList(era,"SSWW") #+   GetSignalList(era,"DY") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("SSWWTypeI_NLO_SF_M","")
        mass=mass.replace("SSWWTypeI_NLO_DF_M","")
        #mass=mass.replace("DYTypeI_NLO_DF_M","")
        #mass=mass.replace("VBFTypeI_NLO_DF_M","")
        
        if not int(mass) in sig_mass_list:
            sig_mass_list.append(int(mass))
        continue

sig_mass_list.sort()

channel = "Muon"
sig_pre = "SSWWTypeI"
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

    h_ssww = ROOT.TH1F('h_ssww_'+era, '', len(sig_mass_list), 0 , float(len(sig_mass_list)))

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
    h_ssww.GetYaxis().SetRangeUser(1E-5,10)
    
    h_ssww.GetYaxis().SetTitle("Ration of ++/--")
    h_ssww.GetXaxis().SetTitle('m_{N} (GeV)')
    h_ssww.Draw("histsame")

    nbin=0
    for x in sig_mass_list :
        nbin=nbin+1
        h_ssww.GetXaxis().SetBinLabel(nbin, str(x))



    h_ssww_mm = h_ssww.Clone("h_ssww_mm"+era)
    h_ssww_ee = h_ssww.Clone("h_ssww_ee"+era)
    h_ssww_em = h_ssww.Clone("h_ssww_em"+era)



    lg = ROOT.TLegend(0.8, 0.4, 0.91, 0.91)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)
    
    g_mN=[]
    g_RSSMM=[]
    g_RSSEE=[]
    g_RSSEM=[]

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

        sigSSWW=""

        sigSSWW =  "SSWWTypeI_NLO_SF_M"+str(x)
        sigSSWWDF =  "SSWWTypeI_NLO_DF_M"+str(x)
        

           
        tot_plus=0
        tot_minus=0

        tot_plus_ssww_mm=0
        tot_minus_ssww_mm=0

        tot_plus_ssww_ee=0
        tot_minus_ssww_ee=0

        tot_plus_ssww_em=0
        tot_minus_ssww_em=0

        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigSSWW+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigSSWW+".root")
            f_sigDF = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigSSWWDF+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")
            h_sigDF = f_sigDF.Get("SignalProcess/FillEventCutflow/SplitChannel")
        
            
            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)
                yDF = h_sigDF.GetBinContent(z+1)
                bl = h_sig.GetXaxis().GetBinLabel(z+1) 
                blDF = h_sigDF.GetXaxis().GetBinLabel(z+1) 
                if bl in mm_phist:
                    tot_plus_ssww_mm=tot_plus_ssww_mm+y
                if bl in mm_mhist:
                    tot_minus_ssww_mm=tot_minus_ssww_mm+y

                if bl in ee_phist:
                    tot_plus_ssww_ee=tot_plus_ssww_ee+y
                if bl in ee_mhist:
                    tot_minus_ssww_ee=tot_minus_ssww_ee+y

                if blDF in em_phist:
                    tot_plus_ssww_em=tot_plus_ssww_em+yDF
                if blDF in em_mhist:
                    tot_minus_ssww_em=tot_minus_ssww_em+yDF

                
            tot_plus=tot_plus+tot_plus_ssww_mm+tot_plus_ssww_ee+tot_plus_ssww_em
            tot_minus=tot_minus+tot_minus_ssww_mm+tot_minus_ssww_ee+tot_minus_ssww_em

            print "["+sigSSWW+"] [MuMu] Ratio ++/-- =  "+ str(tot_plus_ssww_mm/tot_minus_ssww_mm)
            print "["+sigSSWW+"] [ElEl] Ratio ++/-- =  "+ str(tot_plus_ssww_ee/tot_minus_ssww_ee)
            print "["+sigSSWWDF+"] [ElMu] Ratio ++/-- =  "+ str(tot_plus_ssww_em/tot_minus_ssww_em)

            h_ssww_mm.Fill(nmass, tot_plus_ssww_mm/tot_minus_ssww_mm)
            h_ssww_ee.Fill(nmass, tot_plus_ssww_ee/tot_minus_ssww_ee)
            h_ssww_em.Fill(nmass, tot_plus_ssww_em/tot_minus_ssww_em)

            f_sig.Close()
            f_sigDF.Close()
            
            g_RSSMM.append(tot_plus_ssww_mm/tot_minus_ssww_mm)
            g_RSSEE.append(tot_plus_ssww_mm/tot_minus_ssww_mm)
            g_RSSEM.append(tot_plus_ssww_mm/tot_minus_ssww_mm)
        else:
            g_RSSMM.append(0.)
            


        print "-"*40    
        print "[Total] Ratio ++/-- =  "+ str(tot_plus/tot_minus)
        print ""*40    
            

    gr_ssww_mm = ROOT.TGraphAsymmErrors(h_ssww_mm)

    
    for i in range(0, gr_ssww_mm.GetN()):

        #N = gr_Data.GetY()[i]
        gr_ssww_mm.SetPointEYlow(i, 0)
        gr_ssww_mm.SetPointEYhigh(i, 0)

    #gr_ssww_mm = ROOT.TGraph(len(g_mN), array("d", g_mN), array("d", g_RSSMM))
    #gr_ssww_mm.SetName('gr_r_pp_mm_mN')
    gr_ssww_mm.SetMarkerStyle(20)
    gr_ssww_mm.SetMarkerSize(1.2)
        
    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSMM[x])

    counter = 2
    gr_ssww_mm.SetMarkerColor(counter)
    gr_ssww_mm.SetLineColor(counter)

    
    h_ssww_mm.SetLineColor(ROOT.kGreen-2) 
    h_ssww_ee.SetLineColor(ROOT.kRed) 
    h_ssww_em.SetLineColor(ROOT.kCyan) 

    
    h_ssww_mm.Draw("histsame")
    h_ssww_ee.Draw("histsame")
    h_ssww_em.Draw("histsame")



    #gr_ssww_mm.SetLineWidth(2)
    #gr_ssww_mm.SetMarkerSize(0.)
    #gr_ssww_mm.SetMarkerColor(ROOT.kBlack)
    #gr_ssww_mm.SetLineColor(ROOT.kBlack)
    #gr_ssww_mm.Draw('p0same')

    #ROOT.gPad.Update()
    lg.AddEntry( h_ssww_mm, 'SSWW MM', 'l')
    lg.AddEntry( h_ssww_ee, 'SSWW EE', 'l')
    lg.AddEntry( h_ssww_em, 'SSWW EM', 'l')


    
    print 'Saving ==> '+outdir+'/Graph_Qratio_SSWW.pdf'
    c1.SaveAs(outdir+'/Graph_Qratio_SSWW.pdf')
    
    
    c1.Close()
