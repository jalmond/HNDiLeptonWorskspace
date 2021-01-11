#!/usr/bin/env python

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt
import os
import sys
import argparse
import datetime

sys.path.insert(1, os.getenv("HNDILEPTONWORKSPACE_DIR") +"/python")

from GeneralSetup import *

args = setupargs("MakeCard")

#set current directory to memory
pwd = os.getcwd()

# get config file name
config_file= args.ConfigFile

# now import analysis functions
from HNType1_config import *

if config_file == "None":
    print "Need input file to configure job"
    print "python MakeInputLimitCutCount.py -c config.txt"
    exit()

_setup=[]

histnames    =  GetConfig("Histnames",        config_file,_setup)
Analyzer     = GetSConfig("Analyzer",   config_file,_setup)
Bkgs         =  GetConfig("Bkgs",   config_file,_setup)
Flavours     =  GetConfig("Flavour",   config_file,_setup)
IDMu         =  GetConfig("IDMu",        config_file,_setup)
IDEl         =  GetConfig("IDEl",        config_file,_setup)
rebins       =  GetConfig("rebin",   config_file,_setup)
regions      =  GetConfig("Regions",   config_file,_setup)
xmins        =  GetConfig("xmin",   config_file,_setup)
xmaxs        =  GetConfig("xmax",   config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([Flavours,regions,Bkgs])     

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [Flavours,regions,Bkgs])

       flavour  = GetIter[0]
       region   = GetIter[1]
       FileType = GetIter[2]


       IDs     = ChooseID(IDMu, IDEl, flavour, 1)

       for ID in IDs:
           counter=-1
           for histname in histnames:

               print flavour  + "  " + region + "  "  + FileType + " " + histname + " " + ID
               counter=counter+1
               xmin=xmins[counter]
               xmax=xmaxs[counter]
               rebin=rebins[counter]

               filepath2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_Fake"+flavour+".root"
               filepath2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_Fake"+flavour+".root"
               filepath2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_Fake"+flavour+".root"

        
               if FileType == "Data":
                   if flavour=="EE":
                       filepath2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_DoubleEG.root"
                       filepath2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_DoubleEG.root"
                       filepath2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_Egamma.root"
                   else:
                       filepath2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_Muon.root"
                       filepath2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_Muon.root"
                       filepath2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_Muon.root"
                       
               if FileType == "Prompt":
                   filepath2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_SSPrompt.root"
                   filepath2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_SSPrompt.root"
                   filepath2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_SSPrompt.root"
               if FileType == "Diboson":
                   filepath2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_Diboson.root"
                   filepath2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_Diboson.root"
                   filepath2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_Diboson.root"
 
               _histname =  "FillEventCutflow/"+Analyzer+"_"+flavour+"_"+ID+"exo_17_028_diel_same_sign" #region+"/"+region +"_"+histname + "_"+ Analyzer+"_"+ flavour + "_"+ID
               savename   = flavour + "_"+FileType+"_"+histname + "_"+ID
    
               os.system("root -l -q -b 'Makeratio.C(\""+_histname+"\",\""+filepath2016+"\", \""+filepath2017+"\",\""+filepath2018+"\",\""+savename+"\","+xmin+", "+xmax+","+rebin+")'")
