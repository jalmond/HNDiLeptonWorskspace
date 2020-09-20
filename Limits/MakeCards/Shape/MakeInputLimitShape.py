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


if config_file == "None":
    print "Need input file to configure job"
    print "python MakeInputLimitShape.py -c config.txt"
    exit()

_setup=[]
_channels =  GetConfig("channels",    config_file,_setup)
flavours  =  GetConfig("flavours",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
SRs       =  GetConfig("SRs",         config_file,_setup)
masses_s  =  GetConfig("masses_s",      config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
masses_c  =  GetConfig("masses_c",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",    config_file,_setup)
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
Vars      =  GetConfig("Vars",        config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)


# setup output path                                                                                      
Outputdir = os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir) 
MakeDirectory(Outputdir)
RunOutputdir = os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir)+ "/run/"
MakeDirectory(RunOutputdir)
WorkSpaceDirectory= os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir)+"/Workspace/"
MakeDirectory(WorkSpaceDirectory)

outname="AllCards"
for s in SRs:
       outname+="_"+s
all_list = open(RunOutputdir + outname + ".txt","w")

list_liters = [years, _channels, flavours,SRs,Vars]
niter = NIteration(list_liters)
outfiles = []
files_tocopy=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, list_liters)
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]
       _var     = GetIter[4] 
       print year + " " + _channel + " " + flavour + " " + SR + " " + _var

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t,masses_c, _channel, 1)
       
       for _id in IDs:
           for mass in _masses:
               isVBF=ChooseTag(_channel)
               _var = GetVariableName(_var,SR)
               
               #card_2016_EE_SR1_N200_combined_passTightID.txt
               cardname = "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_" +_id+"_"+_var+".txt"
               card_output_dir=Outputdir+year + "/"
               MakeDirectory(card_output_dir)
               card_output_dir = card_output_dir+flavour + "_"+ SR + "/"
               MakeDirectory(card_output_dir)

               limitfile = open(card_output_dir + cardname,"w")
               print card_output_dir + cardname
               all_list.write(card_output_dir + cardname + "\n") 
               
               input_rootfile = "HN_"+_channel+"_"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root"

               input_filepath =  card_output_dir +input_rootfile
               if not os.path.exists(input_filepath):
                   print "Error no " + input_filepath
                   exit()
               #input_filepath ="HN"+mass+"_highmass_Run2Legacy_v4_"+year+"_"+SR+"_"+flavour+"_"+_id+"_"+_var+".root"
               
               #os.system("cp " + input_filepath + " " + WorkSpaceDirectory)
               
               limitfile.write("imax 1  number of channels\n")
               limitfile.write("jmax 3  number of backgrounds\n")
               limitfile.write("kmax *  number of nuisance parameters (sources of systematical uncertainties)\n")
               limitfile.write("------------\n")
               limitfile.write("shapes * * "+ " " + input_filepath  + " $PROCESS $PROCESS_$SYSTEMATIC\n")
               limitfile.write("------------\n")
               limitfile.write("# we have just one channel, in which we observe 0 events\n")
               limitfile.write("bin bin1\n")

               
               limitfile.write("observation "+str(GetCountShape(_channel,"data_obs",flavour,SR, mass,year,_id,_var,Analyzer ))+"\n")
               print str(GetCountShape(_channel,"data_obs",flavour,SR, mass,year,_id,_var,Analyzer))
               limitfile.write("------------\n")
               limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
               limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
               limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
               limitfile.write("# on each process and bin\n")
               limitfile.write("bin	bin1	bin1	bin1	bin1\n")
               limitfile.write("process	prompt	fake	cf	signal\n")
               limitfile.write("process	1	2	3	0\n")
               rate_line = "rate  " + str(GetCountShape(_channel,"prompt",flavour,SR, mass,year,_id,_var,Analyzer)) + " " + str(GetCountShape(_channel,"Fake",flavour,SR, mass,year,_id,_var,Analyzer)) + " " + str(GetCountShape(_channel,"cf",flavour,SR,mass,year,_id,_var,Analyzer)) + " " + str(GetSignalEventsShape(flavour,SR,mass,year, _channel,_id,_var,Analyzer))

               rate_line += "\n"
               limitfile.write(rate_line)
               limitfile.write("Lumi	lnN	1.05	-	-	1.05\n")
               limitfile.write("Fake	lnN	-	1.3	-	-\n")
               limitfile.write("CF	        lnN	-	-	1.439	-\n")
               lepid = "MUID"
               #if flavour == "EE":
               #    lepid = "ELID"
               #limitfile.write(lepid + "	shapeN2 1       1       1       1\n")
               #limitfile.write("JES	shapeN2 1       1       1       1\n") 
               #limitfile.write("JER	shapeN2 1       1       1       1\n") 
               limitfile.write("* autoMCStats 0 0 1\n")
               
               limitfile.close()
               os.system("cp " + card_output_dir + cardname + " " + WorkSpaceDirectory)    
all_list.close()

