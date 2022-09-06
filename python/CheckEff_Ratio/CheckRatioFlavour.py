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

    List = GetSignalList(era,"DY") #+   GetSignalList(era,"DY") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("DYTypeI_NLO_DF_M","")
        
        if not int(mass) in sig_mass_list:
            sig_mass_list.append(int(mass))
        continue

sig_mass_list.sort()

channel = "Muon"
sig_pre = "DYTypeI"
mm_hist = ["SS_Mu+Mu+","SS_Mu-Mu-"]
ee_hist = ["SS_El+El+","SS_El-El-"]
em_hist = ["SS_Mu+El+","SS_El+Mu+","SS_Mu-El-","SS_El-Mu-"]


ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

for era in eras:
    
    
    outdir = PLOT_PATH+'/CheckRatioFlav/'+era+'/'
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioFlav/')
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioFlav/'+era)

    
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

    h_dy = ROOT.TH1F('h_dy_'+era, '', 3000, 0, 3000) 
    #len(sig_mass_list), 0 , float(len(sig_mass_list)))

    #h_dy.SetTitle("");
    h_dy.GetYaxis().SetLabelSize(0.04);
    h_dy.GetYaxis().SetTitleSize(0.054);
    h_dy.GetYaxis().SetTitleOffset(1.30);
    h_dy.GetXaxis().SetLabelSize(0.03);
    h_dy.GetXaxis().SetTitleSize(0.05);

    h_dy.Draw("Axis")

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(era))+" fb^{-1} (13 TeV)")

    
    #h_dy.GetXaxis().SetRangeUser(0.,2E4)
    h_dy.GetYaxis().SetRangeUser(1E-5,1)
    
    h_dy.GetYaxis().SetTitle("Ration of ll/ee+mm+em")
    h_dy.GetXaxis().SetTitle('m_{N} (GeV)')
    h_dy.Draw("histsame")

    nbin=0

    h_dy_mm = h_dy.Clone("h_dy_mm"+era)
    h_dy_ee = h_dy.Clone("h_dy_ee"+era)
    h_dy_em = h_dy.Clone("h_dy_em"+era)



    lg = ROOT.TLegend(0.8, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.015)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)
    
    g_mN=[]
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

        sigDY=""

        sigDY =  "DYTypeI_NLO_DF_M"+str(x)
        

           
        tot_lep=0

        tot_dy_mm=0
        tot_dy_ee=0
        tot_dy_em=0



        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")

            print "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root"

            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)



                bl = h_sig.GetXaxis().GetBinLabel(z+1) 

                if bl in mm_hist:
                    tot_dy_mm=tot_dy_mm+y
                    tot_lep=tot_lep+y
                if bl in ee_hist:
                    tot_dy_ee=tot_dy_ee+y
                    tot_lep=tot_lep+y
                if bl in em_hist:
                    tot_dy_em=tot_dy_em+y
                    tot_lep=tot_lep+y

               

            print "["+sigDY+"] [MuMu] Ratio mm/ll =  "+ str(tot_dy_mm/tot_lep)
            print "["+sigDY+"] [ElEl] Ratio ee/ll =  "+ str(tot_dy_ee/tot_lep)
            print "["+sigDY+"] [ElMu] Ratio em/ll =  "+ str(tot_dy_em/tot_lep)

            h_dy_mm.Fill(nmass, tot_dy_mm/tot_lep)
            h_dy_ee.Fill(nmass, tot_dy_ee/tot_lep)
            h_dy_em.Fill(nmass, tot_dy_em/tot_lep)

            f_sig.Close()
            
            g_RSSMM.append(tot_dy_mm/tot_lep)
            g_RSSMM_exl.append(0)
            g_RSSMM_exh.append(0)
            g_RSSMM_eyl.append(0)
            g_RSSMM_eyh.append(0)

            g_RSSEE.append(tot_dy_ee/tot_lep)
            g_RSSEE_exl.append(0)
            g_RSSEE_exh.append(0)
            g_RSSEE_eyl.append(0)
            g_RSSEE_eyh.append(0)


            g_RSSEM.append(tot_dy_em/tot_lep)
            g_RSSEM_exl.append(0)
            g_RSSEM_exh.append(0)
            g_RSSEM_eyl.append(0)
            g_RSSEM_eyh.append(0)

     

    gr_dy_mm  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSMM),array("d",  g_RSSMM_exl),array("d",  g_RSSMM_exh),array("d",  g_RSSMM_eyl),array("d",  g_RSSMM_eyh));
    gr_dy_ee  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEE),array("d",  g_RSSEE_exl),array("d",  g_RSSEE_exh),array("d",  g_RSSEE_eyl),array("d",  g_RSSEE_eyh));
    gr_dy_em  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEM),array("d",  g_RSSEM_exl),array("d",  g_RSSEM_exh),array("d",  g_RSSEM_eyl),array("d",  g_RSSEM_eyh));


    gr_dy_mm.SetMarkerStyle(20)
    gr_dy_mm.SetMarkerSize(1.1)
        
    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSMM[x])
    counter = 2
    gr_dy_mm.SetMarkerColor(counter)
    gr_dy_mm.SetLineColor(counter)



    for i in range(0, gr_dy_ee.GetN()):
        gr_dy_ee.SetPointEYlow(i, 0)
        gr_dy_ee.SetPointEYhigh(i, 0)

    gr_dy_ee.SetMarkerStyle(21)
    gr_dy_ee.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEE[x])
    counter = 3
    gr_dy_ee.SetMarkerColor(counter)
    gr_dy_ee.SetLineColor(counter)


    for i in range(0, gr_dy_em.GetN()):
        gr_dy_em.SetPointEYlow(i, 0)
        gr_dy_em.SetPointEYhigh(i, 0)

    gr_dy_em.SetMarkerStyle(22)
    gr_dy_em.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEM[x])
    counter = 4
    gr_dy_em.SetMarkerColor(counter)
    gr_dy_em.SetLineColor(counter)


    
    gr_dy_mm.SetLineColor(ROOT.kGreen-2) 
    gr_dy_ee.SetLineColor(ROOT.kRed) 
    gr_dy_em.SetLineColor(ROOT.kCyan) 

    
    #h_dy_mm.Draw("histsame")
    #h_dy_ee.Draw("histsame")
    #h_dy_em.Draw("histsame")

    #gr_dy_mm.SetLineWidth(2)
    #gr_dy_mm.SetMarkerSize(0.)
    #gr_dy_mm.SetMarkerColor(ROOT.kBlack)
    #gr_dy_mm.SetLineColor(ROOT.kBlack)
    gr_dy_mm.Draw('Cp0same')
    gr_dy_ee.Draw('Cp0same')
    gr_dy_em.Draw('Cp0same')

    #ROOT.gPad.Update()
    lg.AddEntry( gr_dy_mm, 'DY MM', 'lp')
    lg.AddEntry( gr_dy_ee, 'DY EE', 'lp')
    lg.AddEntry( gr_dy_em, 'DY EM', 'lp')

    lg.Draw()
    
    print 'Saving ==> '+outdir+'/Graph_Flavourratio_DY.pdf'

    c1.SaveAs(outdir+'/Graph_Flavourratio_DY.pdf')
    
    
    c1.Close()
