import os,ROOT
import mylib
import canvas_margin
import tdrstyle
import CMS_lumi, tdrstyle
import math
from array import array


Years = ["2016preVFP","2016postVFP","2017","2018"]

Channels = ["Muon"]

Samples = ["Prompt"]

masses = ["100","125","150","200","250","300","400","500","600","700","800","900","1000","1100","1300","1500","1700","2000","2500","5000","20000"]
for m in masses:
    Samples.append('DYTypeI_NLO_SF_M'+m)
    Samples.append('VBFTypeI_NLO_SF_M'+m)
    Samples.append('SSWWTypeI_NLO_SF_M'+m)

baseDir = "/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_DileptonSR/"

#2018/HNL_DileptonSR_DYTypeI_NLO_DF_M200.root"

Systematics = ["JetEn","JetRes","JetMass","PU","MuonEn","Prefire","BTag"]

for Year in Years:
    for Channel in Channels:
        for sample in Samples:
            
            Region="HNL_SR3"
            fileName=baseDir+"/"+Year+"/HNL_DileptonSR_"+sample+".root"
            dirName = Region +"/HNL_SR3_mn200_nevent_Version1_Muon"
            if not os.path.exists(fileName):
                continue
            f_data = ROOT.TFile(fileName)
               
            h_data = f_data.Get(dirName)

            if not h_data:
                continue
            
            y_data = h_data.Integral()

            for Syst in Systematics:
                
                systup = Region +"/HNL_SR3_mn200_nevent_Syst_"+Syst+"Up_HNType1_Muon"
                h_systup = f_data.Get(systup)
                v_systup = y_data
                if h_systup:
                    v_systup = h_systup.Integral()
                
                systdown = Region + "/HNL_SR3_mn200_nevent_Syst_"+Syst+"Down_HNType1_Muon"
                h_systdown = f_data.Get(systdown)
                v_systdown= y_data
                if h_systdown:
                    v_systdown = h_systdown.Integral()
                
                upval = abs((v_systup - y_data)/y_data)*100
                downval = abs((-v_systdown + y_data)/y_data)*100
                print ('Region = ' +Region + ' Sample = ' +sample+ ' Syst source= ' + Syst + ' up=' + str(upval) +  ' down='+str(downval))
                
            
            
            
