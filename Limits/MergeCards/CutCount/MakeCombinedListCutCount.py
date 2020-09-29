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

Analyzer  =  GetSConfig("Analyzer",    config_file,_setup)
Indir     =  GetSConfig("InDir",      config_file,_setup)
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
Limitdir  =  GetSConfig("LimitDir",      config_file,_setup)
batch_tag_bins       =  GetSConfig("batch_tag_bins",      config_file,_setup)
batch_tag_combbins   =  GetSConfig("batch_tag_combbins",      config_file,_setup)
batch_tag_combyears  =  GetSConfig("batch_tag_combinedrun2",      config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)

list_liters = [years, _channels, flavours,SRs]
niter = NIteration(list_liters)

input_list = open(Indir + "/run/input_sr1to4.txt","w")

runscript_s="/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/runCutCountCombine.sh"
print "cd " + Limitdir
print "source " + runscript_s

runscript = open(runscript_s,"w")
runscript.write( "./create-batch -n "+batch_tag_combbins+"  -l " + Indir + "run/input_sr1to4.txt --Full \n"          )



runOS=False

if len(SRs) == 4:
    
    runOS=True
    runscript.write( "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2_SR3_SR4.txt --Full")
else:
    runscript.write( "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2.txt  --Full")


for _iter in range(0,niter):

       GetIter  = SumIteration(_iter,  list_liters)
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]
       if SR=="SR2":
           continue
       if SR=="SR4":
           continue
       
       print year + " " + _channel + " " + flavour + " " + SR
       #card_2018_EE_SR2_N1500_combined_HNTight2016.txt
       channel_tag = ChooseTag(_channel)
       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t,masses_c, _channel, 1)
                
       for mass in _masses:
           for _id in IDs:
               cardname1="card_"+year+"_"+flavour+"_SR1_N"+mass+channel_tag+"_"+_id+".txt"
               cardname2="card_"+year+"_"+flavour+"_SR2_N"+mass+channel_tag+"_"+_id+".txt"
               path1=Indir + year + "/" +flavour+"_SR1/"+cardname1
               path2=Indir + year + "/" +flavour+"_SR2/"+cardname2
               path3=""
               path4=""
               if runOS:
                   path3=Indir + year + "/" +flavour+"_SR3/card_"+year+"_"+flavour+"_SR3_N"+mass+channel_tag+"_"+_id+".txt"
                   path4=Indir + year + "/" +flavour+"_SR4/card_"+year+"_"+flavour+"_SR4_N"+mass+channel_tag+"_"+_id+".txt"
                   
           
               out1= Outdir +   year + "/"+flavour+"_CombinedSR1_SR2/"
               out2= Outdir +   year + "/"+flavour+"_CombinedSR1_SR2_SR3_SR4/"

               MakeDirectory(out1)
               MakeDirectory(out2)
               if not os.path.exists(path1):
                   print "Error no " + path1
                   exit()
               if not os.path.exists(path2):
                   print "Error no " + path2
                   exit()
               if runOS: 
                   if not os.path.exists(path3):
                       print "Error no " + path3
                       exit()
                   if not os.path.exists(path4):
                       print "Error no " + path4
                       exit()

               #card_2016_EE_combined_SR1_SR2_N200_combined_passTightID.txt


               outcardname1="card_"+year + "_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
               outcardname2="card_"+year + "_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
               os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> " + out1 + "/"+ outcardname1)
               print out1 + outcardname1 
               input_list.write(out1 + outcardname1 + "\n")
               if len(SRs) ==4:
                   os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 +  "    Name3=" + path3 + "    Name4=" + path4 +" &> " + out2 + "/"+outcardname2)
                   input_list.write(out2 + outcardname2+"\n")

input_list.close()


input_list = open(Indir + "/run/input_combinedyears.txt","w")

runscript.write(  "./create-batch -n " + batch_tag_combyears+"  -l " + Indir + "run/input_combinedyears.txt --Full \n ")
runscript.close()

for channel in _channels:
    for flavour in flavours:

        IDs     = ChooseID(IDMu, IDEl, flavour, 1)
        _masses = ChooseMassList(masses_s, masses_t,masses_c, channel, 1)
        channel_tag = ChooseTag(channel)

        for mass in _masses:
            for _id in IDs:
                #card_CombinedYears_MuMu_X_MuMu_N600_POGTightPFIsoVeryTight.txt
                cardname1a="card_2016_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
                cardname1b="card_2017_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
                cardname1c="card_2018_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
                cardname2a="card_2016_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
                cardname2b="card_2017_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
                cardname2c="card_2018_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
                #MuMu_CombinedSR1_SR2
                
                path1=Indir + "/2016/" +flavour+"_CombinedSR1_SR2/"+cardname1a 
                path2=Indir + "/2017/" +flavour+"_CombinedSR1_SR2/"+cardname1b 
                path3=Indir + "/2018/" +flavour+"_CombinedSR1_SR2/"+cardname1c 
                ospath1= Indir + "/2016/" +flavour+"_CombinedSR1_SR2_SR3_SR4/"+cardname2a
                ospath2= Indir + "/2017/" +flavour+"_CombinedSR1_SR2_SR3_SR4/"+cardname2b
                ospath3= Indir + "/2018/" +flavour+"_CombinedSR1_SR2_SR3_SR4/"+cardname2c
                
                if not os.path.exists(path1):
                    print "Error no file " + path1
                    exit()
                if not os.path.exists(path2):
                    print "Error no file " + path2
                    exit()
                if not os.path.exists(path3):
                    print "Error no file " + path3
                    exit()
                if runOS:
                    if not os.path.exists(ospath1):
                        print "Error no file " + ospath1
                        exit()
                    if not os.path.exists(ospath2):
                        print "Error no file " + ospath2
                        exit()
                    if not os.path.exists(ospath3):
                        print "Error no file " + ospath3
                        exit()


                outdir =Indir+"/CombinedYears/"
                MakeDirectory(Indir+"/CombinedYears/")
                out1=outdir+"card_CombinedYears_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
                out2=outdir+"card_CombinedYears_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
                os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + "  Name3=" + path3 + "  &> " + out1 )
                input_list.write(out1 + "\n")               
                if runOS:
                    print  "combineCards.py  Name1="+ospath1+ "    Name2=" + ospath2 + "  Name3=" + ospath3 + "  &> " + out2
                    os.system("combineCards.py  Name1="+ospath1+ "    Name2=" + ospath2 + "  Name3=" + ospath3 + "  &> " + out2 )                    
                    input_list.write(out2 + "\n")
                   
input_list.close()
#for x in lists:
 #   print x
