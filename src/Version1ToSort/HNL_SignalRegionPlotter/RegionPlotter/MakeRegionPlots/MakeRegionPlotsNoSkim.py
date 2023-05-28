#!/usr/bin/env python

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt
import os
import sys
import argparse
import datetime

sys.path.insert(1, os.getenv("HNDILEPTONWORKSPACE_DIR") +"/python")

from GeneralSetup import *

args = setupargs("MakePlotter")

#set current directory to memory
pwd = os.getcwd()

# get config file name
config_file= args.ConfigFile
#id_file = "ConfigVal/ID.txt"
# now import analysis functions
from HNType1_config import *

if config_file == "None":
    print "Need input file to configure job"
    print "python MakeRegionPlots.py -c config.txt"
    exit()

_setup=[]

flavours  =  GetConfig("flavours",    config_file,_setup)
regions   =  GetConfig("regions",    config_file,_setup)
hists     =  GetConfig("hists",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
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

       MERGE_DIR=os.getenv("FILE_MERGED_PATH")

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

               
               config_file.write("config          data_file       "+MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+"_"+flavour+"_data.root\n")
               config_file.write("config          cut_dir         "+ID+"_"+flavour+"_"+region+"\n")
               config_file.write("config          plot_dir        "+ID+"_"+flavour+"_"+region+"\n")
               config_file.write("config          region          "+region+"\n")
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
               
   
               for bkg in Bkgs:

                   
                   if "fake" in bkg and flavour=="SingleMuon":
                       config_file.write("sample    fake   "+MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+Skim+"_Nonprompt_Muon_data.root  870\n")
                       
                   elif os.path.exists(MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+bkg+".root"):
                    
                       print "sample   " +  bkg + " "+MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+bkg + ".root " +GetColor(bkg)
                       config_file.write("sample   " +  bkg + " "+MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+bkg + ".root " +GetColor(bkg)+"\n")                                       
                   else:                                                                       
                       print ("Missing " + MERGE_DIR+Analyzer+"/"+year+"/"+Analyzer+"_"+bkg+".root ")
                       exit()
                   
               config_file.close()
               if ShowData == "true":
                   os.system("root -l -q -b macro/MakeRegionPlots.C")
               else:
                   os.system("root -l -q -b macro/MakeRegionPlotsNoData.C")
               #os.remove("config.txt")
               
