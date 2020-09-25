#!/usr/bin/env python

### makes cards with names card_2016_EE_SR1_N200_combined_passTightID.txt
import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

args = setupargs("MakeCard")

#set current directory to memory
pwd = os.getcwd()

# get config file name
config_file= args.ConfigFile

# now import analysis functions
from HNType1_config import *

from CardTemplate import *

if config_file == "None":
    print "Need input file to configure job"
    print "python MakeInputLimitCutCount.py -c config.txt"
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
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
Outdir    =  GetSConfig("OutDir",     config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)


# setup output path
RunOutputdir = os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir) + "/run/"
Outputdir = os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir)
MakeDirectory(Outputdir)
MakeDirectory(RunOutputdir)

# create file of all datacard names used as input to batch jobs       
outname="AllCards"
for s in SRs:
       outname+="_"+s

niter = NIteration([years, _channels, flavours,SRs])     
allcards= open(os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+Outdir+"/run/"+outname+".txt","w")
cardlist=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years, _channels, flavours,SRs])
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]

       print year + " " + _channel + " " + flavour + " " + SR

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t,masses_c, _channel, 1)

       file_output = Outputdir + year+"/"
       MakeDirectory(file_output)
       file_output = file_output+ flavour + "_" + SR+"/"
       MakeDirectory(file_output)

       for _id in IDs:
           for mass in _masses:
               
               isVBF=ChooseTag(_channel)
               cardname="card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+".txt"
               allcards.write(file_output + cardname+"\n")
               cardlist.append(file_output+ cardname)
               limitfile = open(file_output+ cardname,"w")

               nfake = GetFakeCountSRMassBin(flavour,SR, mass,year,_id,Analyzer)
               limitfile.write("imax 1  number of channels\n")
               limitfile.write("jmax 3  number of backgroundss\n")
               limitfile.write("kmax "+GetNuiscances(nfake)+"  number of nuisance parameters (sources of systematical uncertainties)\n")
               
               
                   
               limitfile.write("------------\n")
               limitfile.write("# we have just one channel, in which we observe 0 events\n")
               limitfile.write("bin sr1\n")
               limitfile.write("observation -1\n")
               limitfile.write("------------\n")
               limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
               limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
               limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
               limitfile.write("# on each process and bin\n")
               limitfile.write("bin       sr1     sr1     sr1     sr1\n")
               limitfile.write("process   prompt  fake    cf      HN"+mass+"\n")
               limitfile.write("process   1       2       3       0\n")
               
               nprompt = GetPromptCountSRMassBin(flavour,SR, mass,year,_id,Analyzer)
               ncf = GetCFCountSRMassBin(flavour,SR,mass,year,_id,Analyzer)
               nsig = GetSignalEventsSRMassBin(flavour,SR,mass,year,isVBF,_id,Analyzer)
               

               rate_line = "rate  " + str(nprompt) + " " + str(nfake) + " " + str(ncf) + " " + str(nsig)
               rate_line += "\n"
               limitfile.write(rate_line)
               WriteTemplate(limitfile, SR, flavour, int(mass), ncf,nfake)
               limitfile.close()

allcards.close()

print "Made " + str(len(cardlist)) + " cards:"
for x in cardlist:
       print x

print "#"*30
print "#"*30
os.system("cat  " + cardlist[0])
