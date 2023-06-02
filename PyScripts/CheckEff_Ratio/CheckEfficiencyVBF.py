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


eras = ["2017"] 


sig_mass_list =[]
for era in eras:

    List = GetSignalList(era,"VBF") #+   GetSignalList(era,"VBF") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("VBFTypeI_NLO_DF_M","")
        mass=mass.replace("VBFTypeI_DF_ll_M","")
        mass=mass.replace("VBFTypeI_SF_ll_M","")
        mass=mass.replace("VBFTypeI_DF_M","")
        mass=mass.replace("_private","")
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
    h_vbf.GetYaxis().SetRangeUser(1E-5,2)
    
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

        sigVBF =  "VBFTypeI_DF_ll_M"+str(x)
        
           

        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root")
            h_sig = f_sig.Get("MuMu_ChannelSignalsNewSel_SignalStudy/FillEventCutflow_SR/SR_Summary")

            eff_MM=0
            if h_sig:
                eff_MM =  h_sig.GetBinContent(6) / h_sig.GetBinContent(1)


            h_vbf_mm.Fill(nmass,eff_MM)

            f_sig.Close()
            
            g_RSSMM.append(eff_MM)
            g_RSSMM_exl.append(0)
            g_RSSMM_exh.append(0)
            g_RSSMM_eyl.append(0)
            g_RSSMM_eyh.append(0)

        else:
            print "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"
            print "FAIL"
            exit()
     

            

    # gr_vbf_mm = ROOT.TGraphAsymmErrors(h_vbf_mm)
    # #gr_vbf_ee = ROOT.TGraphAsymmErrors(h_vbf_ee)
    #gr_vbf_em = ROOT.TGraphAsymmErrors(h_vbf_em)
  
    for x in g_RSS:
        print x

    gr_vbf_mm  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSMM),array("d",  g_RSSMM_exl),array("d",  g_RSSMM_exh),array("d",  g_RSSMM_eyl),array("d",  g_RSSMM_eyh));


    counter = 1

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSMM[x])

    counter = 2
    gr_vbf_mm.SetMarkerColor(counter)
    gr_vbf_mm.SetLineColor(counter)


    gr_vbf_mm.SetLineColor(ROOT.kGreen-2) 
    #gr_vbf_ee.SetLineColor(ROOT.kRed) 
    #gr_vbf_em.SetLineColor(ROOT.kCyan) 

    #gr_vbf_tot.SetFillColor(ROOT.kGreen-2)
    gr_vbf_mm.SetFillColor(ROOT.kGreen-2)
    #gr_vbf_ee.SetFillColor(ROOT.kRed)
    #gr_vbf_em.SetFillColor(ROOT.kCyan)

    
    #h_vbf_mm.Draw("histsame")
    #h_vbf_ee.Draw("histsame")
    #h_vbf_em.Draw("histsame")

    #gr_vbf_mm.SetLineWidth(2)
    #gr_vbf_mm.SetMarkerSize(0.)
    #gr_vbf_mm.SetMarkerColor(ROOT.kBlack)
    #gr_vbf_mm.SetLineColor(ROOT.kBlack)

    gr_vbf_mm.SetFillStyle(3010)
    gr_vbf_mm.Draw('CpsameE3')

    #ROOT.gPad.Update()
    lg.AddEntry( gr_vbf_mm, 'VBF MM', 'lp')
    lg.Draw()
    
    print 'Saving ==> '+outdir+'/Graph_Qratio_VBF.pdf'

    c1.SaveAs(outdir+'/Graph_'+era+'_Efficiency_VBF_private.pdf')
    c1.SaveAs(outdir+'/Graph_'+era+'_Efficiency_VBF_private.png')

    os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Efficiency/'")    
    os.system("scp " + outdir+"/Graph_"+era+"_Efficiency_VBF_private.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Efficiency/")
    os.system("scp " + outdir+"/Graph_"+era+"_Efficiency_VBF_private.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Efficiency/")

    
    c1.Close()
