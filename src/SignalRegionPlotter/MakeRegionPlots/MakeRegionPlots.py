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
id_file = "ConfigCR/ID.txt"
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
IDMu      =  GetConfig("IDMu",        id_file,_setup)
IDEl      =  GetConfig("IDEl",        id_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
Skim      =  GetSConfig("Skim",   config_file,_setup)
savetag   =  GetSConfig("savetag",   config_file,_setup)
ShowData  =  GetSConfig("showdata",   config_file,_setup)
PlotSig   =  GetSConfig("plotsig",   config_file,_setup)
Bkgs      =  GetConfig("bkgs",   config_file,_setup)
logy      =  GetConfig("logy",   config_file,_setup)
rebins    =  GetConfig("rebin",   config_file,_setup)
xmins     =  GetConfig("xmin",   config_file,_setup)
xmaxs     =  GetConfig("xmax",   config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([years,flavours,regions])     

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years,flavours,regions])

       year     = GetIter[0]
       flavour  = GetIter[1]
       region   = GetIter[2]




       IDs     = ChooseID(IDMu, IDEl, flavour, 1)

       for ID in IDs:

           counter =-1

           for hist in hists:
               print hist
           for hist in hists:
               print year + " " + flavour + " " + region  + " " + hist
               counter=counter+1
               xmin=xmins[counter]
               xmax=xmaxs[counter]
               rebin=rebins[counter]
               _logy=logy[counter]
               config_file = open("config.txt","w")
               if (flavour == "EE"):
                   if year == "2018":
                       config_file.write("config          data_file       /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_EGamma.root\n")
                   else:
                       config_file.write("config          data_file       /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_DoubleEG.root\n")
               else:
                   config_file.write("config          data_file       /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_Muon.root\n")
           
               config_file.write("config          cut_dir         "+region+"\n")
               config_file.write("config          plot_dir        "+region+"\n")
               config_file.write("config          analysername    "+Analyzer+"\n")
               config_file.write("config          year            "+year+"\n")
               config_file.write("config          id              "+ID+"\n")
               config_file.write("config          flavour         "+flavour+"\n")
               config_file.write("config          histname        "+hist+"\n")
               config_file.write("config          showdata        "+ShowData+"\n")
               config_file.write("config          plotsig        "+PlotSig+"\n")
               config_file.write("config_int          logy        "+_logy+"\n")
               config_file.write("config          savetag         "+savetag+"\n")
               config_file.write("config_int          rebin        "+rebin+"\n")
               config_file.write("config_double          xmin        "+xmin+"\n")
               config_file.write("config_double          xmax        "+xmax+"\n")

               if "SR3_HighmassCR" in region:
                   
                   if "prompt" in Bkgs:
                       config_file.write("sample          prompt /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_OSprompt.root  632\n")


               else:
                   if "prompt" in Bkgs:
                       config_file.write("sample          prompt /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_SSprompt.root  8\n")
                       
               if "prompt_pythia" in Bkgs:
                   config_file.write("sample          prompt /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_SSprompt2.root  8\n")

               if "diboson" in Bkgs:
                   config_file.write("sample          diboson /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_Diboson.root  8\n")
               if "triboson" in Bkgs:
                   config_file.write("sample          triboson /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_VVV.root  802\n")

               if "Xgamma" in Bkgs:
                   config_file.write("sample          X+gamma /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_XG.root  400\n")

               if "top" in Bkgs:
                   config_file.write("sample          Top /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_top.root  632\n")

               if "dy" in Bkgs:
                   config_file.write("sample          DY /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_dy.root  400\n")
               if "wwpp" in Bkgs:
                                   config_file.write("sample        wwpp /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_WWpp.root  840\n")

               if (flavour == "EE"):
                   
                   if "fake" in Bkgs:
                       config_file.write("sample          fake   /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_FakeEE.root  870\n")
                   if "cf" in Bkgs:
                       config_file.write("sample          chareflip    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_CF.root 5\n")

                   if "SR2" in region:
                       config_file.write("signal          400    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_EE_400_nlo.root  2\n")
                       config_file.write("signal          1000    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_EE_1000_nlo.root  2\n")
                   else:
                       config_file.write("signal          100    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_EE_100_nlo.root  2\n")
                       config_file.write("signal          600    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_EE_600_nlo.root  2\n")
                   
               else:

                   if "fake" in Bkgs:
                       config_file.write("sample          fake   /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_FakeMuMu.root  870\n")

                   if "SR2"	in region:
                       config_file.write("signal          400    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_MuMu_400_nlo.root  2\n")
                       config_file.write("signal          1000    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_MuMu_1000_nlo.root  2\n")
                   else:
                       config_file.write("signal          100    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_MuMu_100_nlo.root  2\n")
                       config_file.write("signal          600    /Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_MuMu_600_nlo.root  2\n")

               config_file.close()
               if ShowData == "true":
                   os.system("root -l -q -b macro/MakeRegionPlots.C")
               else:
                   os.system("root -l -q -b macro/MakeRegionPlotsNoData.C")
               os.remove("config.txt")
