

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

flavours  =  GetConfig("flavours",    config_file,_setup)
regions   =  GetConfig("regions",    config_file,_setup)
hists     =  GetConfig("hists",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([years,flavours,regions, hists])     

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years,flavours,regions, hists])

       year     = GetIter[0]
       flavour  = GetIter[1]
       region   = GetIter[2]
       hist       = GetIter[3]

       print year + " " + flavour + " " + region + " " + hist

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)

       for ID in IDs:
       
           config_file = open("config.txt","w")
           if (flavour == "EE"):
               config_file.write("config          data_file       /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_DoubleEG.root\n")
           else:
               config_file.write("config          data_file       /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_DoubleMuon.root\n")
           
           config_file.write("config          cut_dir         "+region+"\n")
           config_file.write("config          plot_dir        "+region+"\n")
           config_file.write("config          analysername    "+Analyzer+"\n")
           config_file.write("config          year            "+year+"\n")
           config_file.write("config          id              "+ID+"\n")
           config_file.write("config          flavour         "+flavour+"\n")
           config_file.write("config          histname        "+hist+"\n")
           config_file.write("sample          prompt /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_SSprompt.root  8\n")

           if (flavour == "EE"):
               config_file.write("sample          fake   /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_FakeEE.root  870\n")
               config_file.write("sample          chareflip    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_CF.root 5\n")
               if "SR2" in region:
                   config_file.write("signal          400    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_400_nlo.root  2\n")
                   config_file.write("signal          1000    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_1000_nlo.root  2\n")
               else:
                   config_file.write("signal          100    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_100_nlo.root  2\n")
                   config_file.write("signal          200    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_200_nlo.root  2\n")
                   config_file.write("signal          300    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_300_nlo.root  2\n")
                   config_file.write("signal          600    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_EE_600_nlo.root  2\n")

           else:
               config_file.write("sample          fake   /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/"+year+"/HNtypeI_Dilepton_SkimTree_SSNonIso_FakeMuMu.root  870\n")
               if "SR2"	in region:
                   config_file.write("signal          400    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_400_nlo.root  2\n")
                   config_file.write("signal          1000    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_1000_nlo.root  2\n")
               else:
                   config_file.write("signal          100    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_100_nlo.root  2\n")
                   config_file.write("signal          200    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_200_nlo.root  2\n")
                   config_file.write("signal          300    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_300_nlo.root  2\n")
                   config_file.write("signal          600    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/SIG/HNtypeI_Dilepton_HN_Schannel_MuMu_600_nlo.root  2\n")

           config_file.close()
           os.system("root -l -q -b macro/MakeRegionPlots.C")
