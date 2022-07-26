import os,ROOT
import mylib

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

    List = GetSignalList(era,"SSWW") +   GetSignalList(era,"DY") +  GetSignalList(era,"VBF")

    for x in List:
        mass = x
        mass=mass.replace("SSWWTypeI_NLO_SF_M","")
        mass=mass.replace("SSWWTypeI_NLO_DF_M","")
        mass=mass.replace("DYTypeI_NLO_DF_M","")
        mass=mass.replace("VBFTypeI_NLO_DF_M","")
        
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

for era in eras:
    
    c1 = ROOT.TCanvas('c1', '', 800, 800)
    c1.cd()
    

    latex_CMSPriliminary = ROOT.TLatex()
    latex_Lumi = ROOT.TLatex()
    
    latex_CMSPriliminary.SetNDC()
    latex_Lumi.SetNDC()
    latex_CMSPriliminary.SetTextSize(0.055)
    #latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")
    latex_CMSPriliminary.DrawLatex(0.2, 0.88, "#font[62]{CMS}")
        
    latex_Lumi.SetTextSize(0.035)
    latex_Lumi.SetTextFont(42)
    latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(era))+" fb^{-1} (13 TeV)")


    h_ssww = ROOT.TH1D('h_ssww_'+era, '', len(sig_mass_list), 0 , len(sig_mass_list))
    h_dy = ROOT.TH1D('h_ssww_'+era, '', len(sig_mass_list), 0 , len(sig_mass_list))
    h_vbf = ROOT.TH1D('h_ssww_'+era, '', len(sig_mass_list), 0 , len(sig_mass_list))
    h_ssww.GetXaxis().SetTitle("mN (GeV)")
    h_dy.GetXaxis().SetTitle("mN (GeV)")
    h_vbf.GetXaxis().SetTitle("mN (GeV)")
    nbin=0
    for x in sig_mass_list :
        nbin=nbin+1
        h_ssww.GetXaxis().SetBinLabel(nbin, str(x))
        h_dy.GetXaxis().SetBinLabel(nbin, str(x))
        h_vbf.GetXaxis().SetBinLabel(nbin, str(x))



    for x in sig_mass_list :
        print "==="*40
        print "Mass = " + str(x)  + " GeV"
        mass = x

        sigSSWW=""
        sigDY=""
        sigVBF=""

        sigSSWW =  "SSWWTypeI_NLO_SF_M"+str(x)
        sigSSWWDF =  "SSWWTypeI_NLO_DF_M"+str(x)
        sigDY  =   "DYTypeI_NLO_DF_M"+str(x)
        sigVBF =   "VBFTypeI_NLO_DF_M"+str(x)
        

           
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

            #h_ssww.Fill(x, tot_plus_ssww/tot_minus_ssww)
            f_sig.Close()
            f_sigDF.Close()


            
        tot_plus_dy_mm=0
        tot_minus_dy_mm=0

        tot_plus_dy_ee=0
        tot_minus_dy_ee=0

        tot_plus_dy_em=0
        tot_minus_dy_em=0



        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root"):

            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigDY+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")


            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)
                bl = h_sig.GetXaxis().GetBinLabel(z+1)

                if bl in mm_phist:
                    tot_plus_dy_mm=tot_plus_dy_mm+y
                if bl in mm_mhist:
                    tot_minus_dy_mm=tot_minus_dy_mm+y

                if bl in ee_phist:
                    tot_plus_dy_ee=tot_plus_dy_ee+y
                if bl in ee_mhist:
                    tot_minus_dy_ee=tot_minus_dy_ee+y

                if bl in em_phist:
                    tot_plus_dy_em=tot_plus_dy_em+y
                if bl in em_mhist:
                    tot_minus_dy_em=tot_minus_dy_em+y


            tot_plus=tot_plus+tot_plus_dy_mm+tot_plus_dy_ee+tot_plus_dy_em
            tot_minus=tot_minus+tot_minus_dy_mm+tot_minus_dy_ee+tot_minus_dy_em

            print "["+sigDY+"] [MuMu] Ratio ++/-- =  "+ str(tot_plus_dy_mm/tot_minus_dy_mm)
            print "["+sigDY+"] [ElEl] Ratio ++/-- =  "+ str(tot_plus_dy_ee/tot_minus_dy_ee)
            print "["+sigDY+"] [ElMu] Ratio ++/-- =  "+ str(tot_plus_dy_em/tot_minus_dy_em)

            #h_dy.Fill(x, tot_plus_dy/tot_minus_dy)
            f_sig.Close()




        tot_plus_vbf_mm=0
        tot_minus_vbf_mm=0

        tot_plus_vbf_ee=0
        tot_minus_vbf_ee=0

        tot_plus_vbf_em=0
        tot_minus_vbf_em=0



        
        if os.path.exists("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root"):

            f_sig = ROOT.TFile(   "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/"+era+"/HNL_SignalStudies_"+sigVBF+".root")
            h_sig = f_sig.Get("SignalProcess/FillEventCutflow/SplitChannel")


            for z in range(0,h_sig.GetXaxis().GetNbins()):
                x_l = h_sig.GetXaxis().GetBinLowEdge(z+1)
                x_r = h_sig.GetXaxis().GetBinUpEdge(z+1)
                y = h_sig.GetBinContent(z+1)
                bl = h_sig.GetXaxis().GetBinLabel(z+1)



                if bl in mm_phist:
                    tot_plus_vbf_mm=tot_plus_vbf_mm+y
                if bl in mm_mhist:
                    tot_minus_vbf_mm=tot_minus_vbf_mm+y

                if bl in ee_phist:
                    tot_plus_vbf_ee=tot_plus_vbf_ee+y
                if bl in ee_mhist:
                    tot_minus_vbf_ee=tot_minus_vbf_ee+y

                if bl in em_phist:
                    tot_plus_vbf_em=tot_plus_vbf_em+y
                if bl in em_mhist:
                    tot_minus_vbf_em=tot_minus_vbf_em+y


            tot_plus=tot_plus+tot_plus_vbf_mm+tot_plus_vbf_ee+tot_plus_vbf_em
            tot_minus=tot_minus+tot_minus_vbf_mm+tot_minus_vbf_ee+tot_minus_vbf_em

            print "["+sigVBF+"] [MuMu] Ratio ++/-- =  "+ str(tot_plus_vbf_mm/tot_minus_vbf_mm)
            print "["+sigVBF+"] [ElEl] Ratio ++/-- =  "+ str(tot_plus_vbf_ee/tot_minus_vbf_ee)
            print "["+sigVBF+"] [ElMu] Ratio ++/-- =  "+ str(tot_plus_vbf_em/tot_minus_vbf_em)

            #h_vbf.Fill(x, tot_plus_vbf/tot_minus_vbf)

            f_sig.Close()


        print "-"*40    
        print "[Total] Ratio ++/-- =  "+ str(tot_plus/tot_minus)
        print ""*40    
            
    ## Save
    c1.cd()
    #h_ssww.SetLineColor(kRed)
    h_ssww.Draw("histsame")
    #h_dy.Draw("histsame")
    #h_vbf.Draw("histsame")
    c1.SaveAs(era+'_sis_Qratio.pdf')
    print era+'_ssww.pdf'
    
    c1.Close()
