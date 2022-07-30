import os,ROOT
import mylib
from array import array

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

    h_vbf = ROOT.TH1F('h_vbf_'+era, '', 3000, 0, 3000) 
    #len(sig_mass_list), 0 , float(len(sig_mass_list)))

    #h_vbf.SetTitle("");
    h_vbf.GetYaxis().SetLabelSize(0.04);
    h_vbf.GetYaxis().SetTitleSize(0.054);
    h_vbf.GetYaxis().SetTitleOffset(1.30);
    h_vbf.GetXaxis().SetLabelSize(0.03);
    h_vbf.GetXaxis().SetTitleSize(0.05);

    h_vbf.Draw("Axis")

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumiByEra((era))+" fb^{-1} (13 TeV)")

    
    #h_vbf.GetXaxis().SetRangeUser(0.,2E4)
    h_vbf.GetYaxis().SetRangeUser(1E-5,1)
    
    h_vbf.GetYaxis().SetTitle("Ration of ll/ee+mm+em")
    h_vbf.GetXaxis().SetTitle('m_{N} (GeV)')
    h_vbf.Draw("histsame")

    nbin=0

    h_vbf_mm = h_vbf.Clone("h_vbf_mm"+era)
    h_vbf_ee = h_vbf.Clone("h_vbf_ee"+era)
    h_vbf_em = h_vbf.Clone("h_vbf_em"+era)



    lg = ROOT.TLegend(0.8, 0.6, 0.91, 0.91)
    lg.SetTextSize(0.025)
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

        sigVBF=""

        sigVBF =  "VBFTypeI_NLO_DF_M"+str(x)
        

           
        tot_lep=0

        tot_vbf_mm=0
        tot_vbf_ee=0
        tot_vbf_em=0



        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")

            print "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"

            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)



                bl = h_sig.GetXaxis().GetBinLabel(z+1) 

                if bl in mm_hist:
                    tot_vbf_mm=tot_vbf_mm+y
                    tot_lep=tot_lep+y
                if bl in ee_hist:
                    tot_vbf_ee=tot_vbf_ee+y
                    tot_lep=tot_lep+y
                if bl in em_hist:
                    tot_vbf_em=tot_vbf_em+y
                    tot_lep=tot_lep+y

               

            print "["+sigVBF+"] [MuMu] Ratio mm/ll =  "+ str(tot_vbf_mm/tot_lep)
            print "["+sigVBF+"] [ElEl] Ratio ee/ll =  "+ str(tot_vbf_ee/tot_lep)
            print "["+sigVBF+"] [ElMu] Ratio em/ll =  "+ str(tot_vbf_em/tot_lep)

            h_vbf_mm.Fill(nmass, tot_vbf_mm/tot_lep)
            h_vbf_ee.Fill(nmass, tot_vbf_ee/tot_lep)
            h_vbf_em.Fill(nmass, tot_vbf_em/tot_lep)

            f_sig.Close()
            
            g_RSSMM.append(tot_vbf_mm/tot_lep)
            g_RSSMM_exl.append(0)
            g_RSSMM_exh.append(0)
            g_RSSMM_eyl.append(0)
            g_RSSMM_eyh.append(0)

            g_RSSEE.append(tot_vbf_ee/tot_lep)
            g_RSSEE_exl.append(0)
            g_RSSEE_exh.append(0)
            g_RSSEE_eyl.append(0)
            g_RSSEE_eyh.append(0)


            g_RSSEM.append(tot_vbf_em/tot_lep)
            g_RSSEM_exl.append(0)
            g_RSSEM_exh.append(0)
            g_RSSEM_eyl.append(0)
            g_RSSEM_eyh.append(0)

     

    gr_vbf_mm  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSMM),array("d",  g_RSSMM_exl),array("d",  g_RSSMM_exh),array("d",  g_RSSMM_eyl),array("d",  g_RSSMM_eyh));
    gr_vbf_ee  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEE),array("d",  g_RSSEE_exl),array("d",  g_RSSEE_exh),array("d",  g_RSSEE_eyl),array("d",  g_RSSEE_eyh));
    gr_vbf_em  = ROOT.TGraphAsymmErrors(nmass+1,array("d",  g_mN), array("d",  g_RSSEM),array("d",  g_RSSEM_exl),array("d",  g_RSSEM_exh),array("d",  g_RSSEM_eyl),array("d",  g_RSSEM_eyh));


    gr_vbf_mm.SetMarkerStyle(20)
    gr_vbf_mm.SetMarkerSize(1.1)
        
    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSMM[x])
    counter = 2
    gr_vbf_mm.SetMarkerColor(counter)
    gr_vbf_mm.SetLineColor(counter)



    for i in range(0, gr_vbf_ee.GetN()):
        gr_vbf_ee.SetPointEYlow(i, 0)
        gr_vbf_ee.SetPointEYhigh(i, 0)

    gr_vbf_ee.SetMarkerStyle(21)
    gr_vbf_ee.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEE[x])
    counter = 3
    gr_vbf_ee.SetMarkerColor(counter)
    gr_vbf_ee.SetLineColor(counter)


    for i in range(0, gr_vbf_em.GetN()):
        gr_vbf_em.SetPointEYlow(i, 0)
        gr_vbf_em.SetPointEYhigh(i, 0)

    gr_vbf_em.SetMarkerStyle(22)
    gr_vbf_em.SetMarkerSize(1.1)

    for x in range (0, len(g_mN)):
        print str(g_mN[x]) + ' ' + str(g_RSSEM[x])
    counter = 4
    gr_vbf_em.SetMarkerColor(counter)
    gr_vbf_em.SetLineColor(counter)


    
    gr_vbf_mm.SetLineColor(ROOT.kGreen-2) 
    gr_vbf_ee.SetLineColor(ROOT.kRed) 
    gr_vbf_em.SetLineColor(ROOT.kCyan) 

    
    #h_vbf_mm.Draw("histsame")
    #h_vbf_ee.Draw("histsame")
    #h_vbf_em.Draw("histsame")

    #gr_vbf_mm.SetLineWidth(2)
    #gr_vbf_mm.SetMarkerSize(0.)
    #gr_vbf_mm.SetMarkerColor(ROOT.kBlack)
    #gr_vbf_mm.SetLineColor(ROOT.kBlack)
    gr_vbf_mm.Draw('Cp0same')
    gr_vbf_ee.Draw('Cp0same')
    gr_vbf_em.Draw('Cp0same')

    #ROOT.gPad.Update()
    lg.AddEntry( gr_vbf_mm, 'VBF MM', 'lp')
    lg.AddEntry( gr_vbf_ee, 'VBF EE', 'lp')
    lg.AddEntry( gr_vbf_em, 'VBF EM', 'lp')

    lg.Draw()
    
    print 'Saving ==> '+outdir+'/Graph_Flavourratio_VBF.pdf'

    c1.SaveAs(outdir+'/Graph_'+era+'_Flavourratio_VBF.pdf')
    c1.SaveAs(outdir+'/Graph_'+era+'_Flavourratio_VBF.png')
    print ("scp " + outdir+"/Graph_"+era+"_Flavourratio_VBF.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/")
    os.system("scp " + outdir+"/Graph_"+era+"_Flavourratio_VBF.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/")
    print ("scp " + outdir+"/Graph_"+era+"_Flavourratio_VBF.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/")
    os.system("scp " + outdir+"/Graph_"+era+"_Flavourratio_VBF.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/")
    
    
    
    c1.Close()
