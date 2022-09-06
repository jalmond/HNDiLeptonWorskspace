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


sig_mass_list =[]
for era in eras:

    List =  GetSignalList(era,"DY") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("DYTypeI_NLO_DF_M","")
        mass=mass.replace("VBFTypeI_NLO_DF_M","")
        if mass == "750" or mass == "1250":
            continue
        if not int(mass) in sig_mass_list:
            sig_mass_list.append(int(mass))
        continue

sig_mass_list.sort()



ROOT.gErrorIgnoreLevel = ROOT.kFatal

tdrstyle.setTDRStyle()
#ROOT.TH1.AddDirectory(False)
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

PLOT_PATH = os.environ['PLOT_PATH']

for era in eras:
   

    #stack_sr = ROOT.THStack ("STmm"+era,"STmm"+era)
    
    outdir = PLOT_PATH+'/CheckRatioSR/'+era+'/'
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioSR/')
    os.system("mkdir -p " + PLOT_PATH+'/CheckRatioSR/'+era)

    
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

    h_dy = ROOT.TH1F('h_dy_'+era, '',len(sig_mass_list), 0 , float(len(sig_mass_list)))
    for x in range(0, len(sig_mass_list)):
        h_dy.GetXaxis().SetBinLabel(x+1, str(sig_mass_list[x]))



    h_dy.GetYaxis().SetLabelSize(0.04);
    h_dy.GetYaxis().SetTitleSize(0.054);
    h_dy.GetYaxis().SetTitleOffset(1.30);
    h_dy.GetXaxis().SetLabelSize(0.03);
    h_dy.GetXaxis().SetTitleSize(0.05);

    h_dy.Draw("Axis")

    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumiByEra((era))+" fb^{-1} (13 TeV)")

    
    #h_dy.GetXaxis().SetRangeUser(0.,2E4)
    h_dy.GetYaxis().SetRangeUser(1E-5,1.1)
    
    h_dy.GetYaxis().SetTitle("Fraction ev per SR")
    h_dy.GetXaxis().SetTitle('m_{N} (GeV)')
    h_dy.Draw("histsame")


    lg = ROOT.TLegend(0.75, 0.6, 0.85, 0.85)
    lg.SetTextSize(0.025)
    lg.SetBorderSize(0)
    lg.SetFillStyle(0)

    h_sig_sr1= h_dy.Clone("h_sig_SR1_mm"+era)
    h_sig_sr3= h_dy.Clone("h_sig_SR3_mm"+era)
    h_sig_sr1FAIL= h_dy.Clone("h_sig_sr1FAIL_mm"+era)
    h_sig_sr3FAIL= h_dy.Clone("h_sig_sr3FAIL_mm"+era)


    nmass=-1    
    for x in sig_mass_list :
        nmass=nmass+1
        print "==="*40
        print "Mass = " + str(x)  + " GeV"
        mass = x

        sigDY =  "DYTypeI_NLO_DF_M"+str(x)
        sigVBF =  "VBFTypeI_NLO_DF_M"+str(x)

          

        tot_SR1=0
        tot_SR3=0
        tot_SR1FAIL=0
        tot_SR3FAIL=0
        
        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root"):
           
            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root")
            h_sig = f_sig.Get("MuonChannelSignals/FillEventCutflow_SR/SR_Summary_17028")
            
            
            print "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root"
            if h_sig:
                tot_SR1 = tot_SR1 +  h_sig.GetBinContent(6)
                tot_SR3 = tot_SR3 +  h_sig.GetBinContent(8)
                tot_SR1FAIL = tot_SR1FAIL +  h_sig.GetBinContent(7)
                tot_SR3FAIL = tot_SR3FAIL +  h_sig.GetBinContent(9)
            else:
                print("No hist " + "MuonChannelSignals/FillEventCutflow_SR/SR_Summary_17028")
                exit()
                
            print "["+sigDY+"] [MuMu] "


            f_sig.Close()


            
        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"):

            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root")
            h_sig = f_sig.Get("MuonChannelSignals/FillEventCutflow_SR/SR_Summary_17028")

            print "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"

            tot_SR1 = tot_SR1 +  h_sig.GetBinContent(6)
            tot_SR3 = tot_SR3 +  h_sig.GetBinContent(8)
            tot_SR1FAIL = tot_SR1FAIL +  h_sig.GetBinContent(7) 
            tot_SR3FAIL = tot_SR3FAIL +  h_sig.GetBinContent(9) 


            print "["+sigVBF+"] [MuMu] "

            f_sig.Close()


        tot_SR = tot_SR1+tot_SR3+tot_SR1FAIL+tot_SR3FAIL

        h_sig_sr1.Fill(nmass, tot_SR1 / tot_SR)
        h_sig_sr1FAIL.Fill(nmass, tot_SR1FAIL / tot_SR)
        h_sig_sr3.Fill(nmass, tot_SR3 / tot_SR)
        h_sig_sr3FAIL.Fill(nmass, tot_SR3FAIL / tot_SR)
        
    
    h_sig_sr1.SetFillColor(ROOT.kRed);
    h_sig_sr1FAIL.SetFillColor(800);
    h_sig_sr3.SetFillColor(870);
    h_sig_sr3FAIL.SetFillColor(ROOT.kGray);


    h_sig_sr1.Add(h_sig_sr1FAIL)
    h_sig_sr1.Add(h_sig_sr3)
    h_sig_sr1.Add(h_sig_sr3FAIL)
    
    h_sig_sr1FAIL.Add(h_sig_sr3)
    h_sig_sr1FAIL.Add(h_sig_sr3FAIL)

    h_sig_sr3.Add(h_sig_sr3FAIL)


    h_sig_sr1.Draw("histsame")
    h_sig_sr1FAIL.Draw("histsame")
    h_sig_sr3.Draw("histsame")
    h_sig_sr3FAIL.Draw("histsame")
   # 
    lg.AddEntry( h_sig_sr1, 'SR1 MM', 'f')
    lg.AddEntry( h_sig_sr1FAIL, 'FAIL SR1  MM', 'f')
    lg.AddEntry( h_sig_sr3, 'SR3 MM', 'f')
    lg.AddEntry( h_sig_sr3FAIL, 'FAIL SR MM', 'f')
    

    lg.Draw()
    
    print 'Saving ==> '+outdir+'/HIST_'+era+'_SRSplit_EXO17028.pdf'

    c1.SaveAs(outdir+'/HIST_'+era+'_SRSplit_EXO17028.pdf')
    c1.SaveAs(outdir+'/HIST_'+era+'_SRSplit_EXO17028.png')
    os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/'")
    os.system("scp " + outdir+"/HIST_"+era+"_SRSplit_EXO17028.pdf  jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/")
    os.system("scp " + outdir+"/HIST_"+era+"_SRSplit_EXO17028.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/")
    
    c1.Close()
