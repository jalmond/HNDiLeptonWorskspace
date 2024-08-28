import ROOT as rt
rt.gROOT.LoadMacro('./histFitter.C+')
#rt.gROOT.LoadMacro('./RooCBExGaussShape.cc+')
rt.gROOT.LoadMacro('./RooCMSShape.cc+')
from ROOT import tnpFitter
import time
import os

def RunFit(DateTag,channel, era, ID, HistName):

  filepath= os.getenv("FILE_MERGED_PATH") + "/HNL_Lepton_ChargeFlip/ScaleFactor/"+DateTag + "/"+era +"/HNL_Lepton_ChargeFlip_SkimTreeBDT_ScaleFactor.root"
  filepathMC= os.getenv("FILE_MERGED_PATH") + "/HNL_Lepton_ChargeFlip/ScaleFactor/"+DateTag + "/"+era +"/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYJetsToEE_MiNNLO.root"
  fileName = "FitResults"
  os.system("mkdir -p "+fileName)
  fileTruth  = rt.TFile(filepathMC,'read')

  funcs = [
      "Gaussian::sigResPass(x,meanOS,sigmaOS)",
      "Gaussian::sigResFail(x,meanSS,sigmaSS)",
      "RooCMSShape::bkgPass(x, acmsOS, betaOS, gammaOS, peakOS)",
      "RooCMSShape::bkgFail(x, acmsSS, betaSS, gammaSS, peakSS)",
      ]
 
  if  channel == "BB":
    pars = [
        "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
        "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
        "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 2]","peakOS[90.0]",
        "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0., -2, 0.04]","peakSS[90.0]",
        ]
  elif  channel == "EE":
    pars = [
      "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
      "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
      "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 0.2]","peakOS[90.0]",
      "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0., -2, 0.04]","peakSS[90.0]",
    ]

  else:
    pars = [
      "meanOS[-0.0,-5.0,5.0]","sigmaOS[0.9,0.5,5.0]",
      "meanSS[-0.0,-5.0,5.0]","sigmaSS[0.9,0.5,5.0]",
      "acmsOS[60.,50.,80.]","betaOS[0.05,0.01,0.08]","gammaOS[0.1, -2, 0.2]","peakOS[90.0]",
      "acmsSS[60.,50.,80.]","betaSS[0.05,0.01,0.08]","gammaSS[0., -2, 0.04]","peakSS[90.0]",
    ]

  
  this_workspace = []
  this_workspace.extend(pars)
  this_workspace.extend(funcs)
  
  infile = rt.TFile(filepath, "read")
  if channel == "BE":
    hOS = infile.Get(ID+"/ScaleFactor/"+channel+"_"+HistName)
  else:
    hOS = infile.Get(ID+"/ScaleFactor/"+channel+"_"+HistName)
  hSS = infile.Get(ID+"/ScaleFactor/"+channel+"_ZMass_SS")

  print filepath
  print(ID+"/ScaleFactor/"+channel+"_"+HistName)

  #  fitter = tnpFitter( hOS, hSS, fileName, "myhist_"+channel )

  fitter = tnpFitter( hOS, hSS, fileName, HistName+"_"+channel+"_"+era+"_"+ID )
  infile.Close()
  
  fitter.useMinos()
  rootfile = rt.TFile("newfit_"+fileName+"_"+era+"_"+ID+"_"+channel+"_"+HistName+".root",'update')

  fitter.setOutputFile( rootfile )
  
  if channel == "BE":
    histZLineShapeOS = fileTruth.Get(ID+"/ScaleFactor/"+channel+"_"+HistName)
  else:
    print (ID+"/ScaleFactor/"+channel+"_"+HistName)
    histZLineShapeOS = fileTruth.Get(ID+"/ScaleFactor/"+channel+"_"+HistName)
  histZLineShapeSS = fileTruth.Get(ID+"/ScaleFactor/"+channel+"_ZMass_SS")
 
  print ("histZLineShapeOS Integral = " + str(histZLineShapeOS.Integral()) )
  print ("histZLineShapeSS Integral = " + str(histZLineShapeSS.Integral()) )
  fitter.setZLineShapes(histZLineShapeOS,histZLineShapeSS)
  
  fileTruth.Close()
  
  workspace = rt.vector("string")()
  for i in this_workspace:
    workspace.push_back(i)
  fitter.setWorkspace( workspace )
  
  title = "mytitle_"+channel+"_"+ID+"_"+HistName + "_"+era
  fitter.fits(False,title)
  rootfile.Close()



Channels = ["BB","EE"]
Eras = ["2016a","2016b", "2017","2018"]
for Channel in Channels:
  for era in Eras:
    #RunFit(Channel, era, "POGTight", "ZMass_OS_CFSFweighted")
    #RunFit(Channel, era, "HNTightV2","ZMass_OS_CFSFweighted")
    year = era
    if "2016" in era:
      year = "2016"
    HNLID = "HNL_ULID_"+year
    HNLID2 = "HNL_TC1_ULID_"+year
   
    RunFit("May9",Channel, era, HNLID,"ZMass_OS_CF_PTB_weighted")
    RunFit("May9",Channel, era, HNLID2,"ZMass_OS_CF_PTB_weighted")
    #RunFit(Channel, era, HNLID3,"ZMass_OS_CFweightedSF")
