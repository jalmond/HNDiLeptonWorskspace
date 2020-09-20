

#!/usr/bin/env python                                                                                                                                         
import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

args = setupargs("MakeCard")
pwd = os.getcwd()

config_file= args.ConfigFile

# now import analysis functions                                                                                                                               
from HNType1_config import *


if config_file == "None":
    print "Need input file to configure job"
    print "python MakeCombinedListCutCount.py -c config.txt"
    exit()


_setup=[]
_channels =  GetConfig("channels",    config_file,_setup)
flavours  =  GetConfig("flavours",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
SRs       =  GetConfig("SRs",         config_file,_setup)
masses_s  =  GetConfig("masses_s",    config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
masses_c  =  GetConfig("masses_c",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Vars      =  GetConfig("Vars",        config_file,_setup)

Analyzer  =  GetSConfig("Analyzer",    config_file,_setup)
Indir     =  GetSConfig("InDir",      config_file,_setup)
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
Limitdir  =  GetSConfig("LimitDir",      config_file,_setup)
batch_tag_bins       =  GetSConfig("batch_tag_bins",      config_file,_setup)
batch_tag_combbins   =  GetSConfig("batch_tag_combbins",      config_file,_setup)
batch_tag_combyears  =  GetSConfig("batch_tag_combinedrun2",      config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)


list_liters = [years, _channels, flavours,Vars]
niter = NIteration(list_liters)

input_list = open(Indir + "/run/input_sr1to4.txt","w")

print "cd " + Limitdir
print "./create-batch -n "+batch_tag_combbins+"  -l " + Indir + "run/input_sr1to4.txt"



runOS=False

if len(SRs) == 4:

    runOS=True
    print "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2_SR3_SR4.txt"
else:
    print "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2.txt"


workspace="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/HNtypeI_JA/Workspace/"
os.chdir(workspace);
print workspace

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter,  list_liters)
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       var      = GetIter[3]

       print year + " " + _channel + " " + flavour + var
       #card_2018_EE_SR2_N1500_combined_HNTight2016.txt                                                                                                       
       channel_tag = ChooseTag(_channel)
       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t,masses_c, _channel, 1)

       for mass in _masses:
           for _id in IDs:
                        
               varJ = var
               varJ= varJ.replace("jj","J")
               path1="card_"+year+"_"+flavour+"_SR1_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
               path2="card_"+year+"_"+flavour+"_SR2_N"+mass+channel_tag+"_"+_id+"_"+varJ+".txt"
               ospath1="card_"+year+"_"+flavour+"_SR3_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
               ospath2="card_"+year+"_"+flavour+"_SR4_N"+mass+channel_tag+"_"+_id+"_"+varJ+".txt"

               if not os.path.exists(path1):
                   print "Error no " + path1
                   exit()
               if not os.path.exists(path2):
                   print "Error no " + path2
                   exit()
               if runOS:
                   if not os.path.exists(ospath1):
                       print "Error no " + ospath1
                       exit()
                   if not os.path.exists(ospath2):
                       print "Error no " + ospath2
                       exit()

               outcardname1="card_"+year + "_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+"_"+ var+".txt"
               outcardname2="card_"+year + "_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+"_"+ var+".txt"

               os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> " + outcardname1)
               input_list.write(workspace + outcardname1 + "\n")
               if len(SRs) ==4:
                   os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 +  "    Name3=" + ospath1 + "    Name4=" + ospath2 +" &> " +outcardname2)
               input_list.write(workspace + outcardname2+"\n")

    
input_list.close()

input_list = open(Indir + "/run/input_combinedyears.txt","w")      

print "./create-batch -n " + batch_tag_combyears+"  -l " + Indir + "run/input_combinedyears.txt"


for channel in _channels:
    for flavour in flavours:

        IDs     = ChooseID(IDMu, IDEl, flavour, 1)
        _masses = ChooseMassList(masses_s, masses_t,masses_c, channel, 1)
        channel_tag = ChooseTag(channel)

        for mass in _masses:
            for _id in IDs:
                
                
                cardname1a="card_2016_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                cardname1b="card_2017_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                cardname1c="card_2018_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                cardname2a="card_2016_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                cardname2b="card_2017_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                cardname2c="card_2018_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"

                MakeDirectory("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/CombinedYears/")


                out1="card_CombinedYears_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"
                out2="card_CombinedYears_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+"_"+var+".txt"

                os.system("combineCards.py  Name1="+cardname1a+ "    Name2=" + cardname1b + "  Name3=" + cardname1c + "  &> " + out1 )
                os.system("combineCards.py  Name1="+cardname2a+ "    Name2=" + cardname2b + "  Name3=" + cardname2c + "  &> " + out2 )
                input_list.write(workspace+"/"+out1 + "\n")
                input_list.write(workspace+"/"+out2 + "\n")

os.chdir("/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/MakeCards")

input_list.close()
#for x in lists:
 #   print x
