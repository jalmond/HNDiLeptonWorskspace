#!/usr/bin/env python                                                                                                             
import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

args = setupargs()
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
masses_s  =  GetConfig("masses_s",      config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)

Analyzer  =  GetSConfig("Analyzer",    config_file,_setup)
Indir     =  GetSConfig("InDir",      config_file,_setup)
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
Limitdir  =  GetSConfig("LimitDir",      config_file,_setup)
batch_tag_bins       =  GetSConfig("batch_tag_bins",      config_file,_setup)
batch_tag_combbins   =  GetSConfig("batch_tag_combins",      config_file,_setup)
batch_tag_combyears  =  GetSConfig("batch_tag_combyears",      config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)

list_liters = [years, _channels, flavours,SRs]
niter = NIteration(list_liters)

input_list = open(Indir + "/run/input_sr1to4.txt","w")

print "cd " + Limitdir 
print "./create-batch -n "+batchtag_combbin+"  -l " + Indir + "run/input_sr1to4.txt"          


runOS= False
if len(SRs) == 4:
    runOS=True
    print "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2_SR3_SR4.txt"
else:
    print "./create-batch -n "+batch_tag_bins  +"  -l " + Indir + "run/AllCards_SR1_SR2.txt"

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter,  list_liters)
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]


       #card_2018_EE_SR2_N1500_combined_HNTight2016.txt
       channel_tag = ChooseTag(channel)
       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, _channel, 1)
                
       for mass in masses:
           #cardname="card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+".txt"
           cardname1="card_"+year+"_"+flavour+"_SR1_N"+mass+"_"+channel_tag+"_"+_id+".txt"
           cardname2="card_"+year+"_"+flavour+"_SR2_N"+mass+"_"+channel_tag+"_"+_id+".txt"
           path1=Indir + year + "/" +flavour+"_SR1/"+cardname1
           path2=Indir + year + "/" +flavour+"_SR2/"+cardname2
           path3=""
           path4=""
           if runOS:
               path3=Indir + year + "/" +flavour+"_SR3/card_"+year+"_"+flavour+"_SR3_N"+mass+"_"+channel_tag+"_"+_id+".txt"
               path4=Indir + year + "/" +flavour+"_SR4/card_"+year+"_"+flavour+"_SR4_N"+mass+"_"+channel_tag+"_"+_id+".txt"
                   
           
           out1= Outdir +  + year + "/"+flavour+"_CombinedSR1_SR2/"
           out2= Outdir +  + year + "/"+flavour+"_CombinedSR1_SR2_SR3_SR4/"
           MakeDir(out1)
           MakeDir(out2)
           #card_2016_EE_combined_SR1_SR2_N200_combined_passTightID.txt


           outcardname1="card_"+year + "_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
           outcardname2="card_"+year + "_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
           os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> " + out1 + "/"+ outcardname1)
           input_list.write(out1 + outcardname1 + "\n")
           if len(SR) ==4:
               os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 +  "    Name3=" + path3 + "    Name4=" + path4 +" &> " + out2 + "/"+outcardname2)
           input_list.write(out2 + outcardname2+"\n")

input_list.close()

input_list = open(Indir + "/run/input_combinedyears.txt","w")

print "./create-batch -n " + batch_tag_combinedyears+"  -l " + Indir + "run/input_combinedyears.txt"


for channel in channels:
    for flavour in flavours:

        IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, _channel, 1)
       channel_tag = ChooseTag(channel)

       for mass in masses:
           for _id in IDs:
               #card_CombinedYears_MuMu_X_MuMu_N600_POGTightPFIsoVeryTight.txt
               cardname1="card_"+year + "_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
               cardname2="card_"+year + "_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"

               path1=Indir + "/2016/" +flavour+"_SR1_SR2/"+cardname1 
               path2=Indir + "/2017/" +flavour+"_SR1_SR2/"+cardname1 
               path3=Indir + "/2018/" +flavour+"_SR1_SR2/"+cardname1 
               ospath1= Indir + "/2016/" +flavour+"_SR1_SR2_SR3_SR4/"+cardname2
               ospath2= Indir + "/2017/" +flavour+"_SR1_SR2_SR3_SR4/"+cardname2
               ospath3= Indir + "/2018/" +flavour+"_SR1_SR2_SR3_SR4/"+cardname2


               outdir =Indir+"/CombinedYears/"
               MakeDirectory(Indir+"/CombinedYears/")
               out1=outdir+"card_CombinedYears_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
               out2=outdir+"card_CombinedYears_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
               os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + "  Name3=" + path3 + "  &> " + out1 )

               if runOS:
                   os.system("combineCards.py  Name1="+ospath1+ "    Name2=" + ospath2 + "  Name3=" + ospath3 + "  &> " + out2 )                    
               input_list.write(out1 + "\n")
               if runOS:
                   input_list.write(osout1 + "\n")

input_list.close()
#for x in lists:
 #   print x
