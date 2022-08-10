import os,ROOT,sys

sys.path.insert(0, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/python/')

import mylib
import canvas_margin
import tdrstyle
import CMS_lumi, tdrstyle
import math
from array import array


Lumis = [19.52,16.81,41.48,59.83]
total_lumi= 19.52+16.81+41.48+59.83


Eras = [
"2016preVFP",
"2016postVFP",
"2017",
"2018",
]

Channels = [
"MuMu",
"EE",
"EMu",
]

Regions = [
"SR1",
"SR2",
"SR3",
]

Bkgds = [
]

Masses = [ "200" ]



baseDir = "/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_SignalStudies/"



os.system("mkdir -p Output/")
os.system("mkdir -p Output/Yields/")
outdir="Output/Yields/"
woutput = open (outdir+"/Yields.txt","w")



for Region in Regions:
  
  woutput.write("-"*150+"\n")
  woutput.write("Region = " + Region + "\n")
  for Mass in Masses:
  
    woutput.write("-"*150+"\n")

    iera=-1
    for Era in Eras:
      iera=iera+1
      
      outtxt=Era + " "*(15- len(Era))+ " [MM/EE/EMu]  HNL_SignalStudies_DYTypeI_SF_ll_M"+Mass+":" + " "*(10- len(Mass)) +" ["
      outtxtNorm=Era + " "*(15- len(Era))+ " [MM/EE/EMu]  HNL_SignalStudies_DYTypeI_SF_ll_M"+Mass+":" + " "*(10- len(Mass)) +" ["
      
      for Channel in Channels:
             
        dirName = Region
        GetIntegral=True

        histName = dirName + "/" + Channel + "_ChannelSignalsNewSel_SignalStudy/N1Mass_Central"
        if Region == "SR2":
          histName = dirName + "/" + Channel + "_ChannelSignalsNewSel_SignalStudy/HT_LT1_Central"
        if Region == "SR3":
          histName = dirName + "/" + Channel + "_ChannelSignalsNewSel_SignalStudy/SignalBins"
        

        f_vbf_off = ROOT.TFile(baseDir+"/"+Era+"/HNL_SignalStudies_DYTypeI_SF_ll_M"+Mass+".root")
        if not f_vbf_off:
          print "Missing " + baseDir+"/"+Era+"/HNL_SignalStudies_DYTypeI_SF_ll_M"+Mass+".root"
          exit()

        h_vbf_off = f_vbf_off.Get(histName)

        y_vbf_off=0
        if h_vbf_off:
          if GetIntegral:
            y_vbf_off = h_vbf_off.Integral()
          else:
            y_vbf_off = h_vbf_off.GetBinContent(1)
          
        outtxt =outtxt + " " + str(y_vbf_off)+" "*(10- len(str(y_vbf_off)))
        outtxtNorm =outtxtNorm + " " + str(y_vbf_off/Lumis[iera])+" "*(10- len(str(y_vbf_off)))
        


        print("HNL_SignalStudies_DYTypeI_SF_ll_M"+Mass+": ["+str(y_vbf_off)+"] ")

        if len(Bkgds) > 0:
          
          y_TotBkgd = 0

          for Bkgd in Bkgds:
            f_Bkgd = ROOT.TFile(baseDir+"/"+Era+"/HNL_SignalStudies_"+Bkgd+".root")
            h_Bkgd = f_Bkgd.Get(dirName+"/NEvent_"+dirName)
            y_Bkgd=0
            if GetIntegral:
              y_Bkgd = h_Bkgd.Integral()
            else:
              y_Bkgd = h_Bkgd.GetBinContent(1)
            y_TotBkgd += y_Bkgd

      outtxt =outtxt + "] (Weighted)  \n"
      #outtxtNorm =outtxtNorm + "] (Normised to 1pb)  \n"
      woutput.write(outtxtNorm)

woutput.close()
os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Yields/'")

os.system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Yields/'")

os.system("scp "+ outdir+"/Yields.txt  jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/Yields/" )
print ("https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/SignalStudies/Yields/")
