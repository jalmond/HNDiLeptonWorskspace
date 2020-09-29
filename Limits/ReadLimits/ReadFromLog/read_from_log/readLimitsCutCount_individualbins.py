#!/usr/bin/env python                                                                                                                                        
import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

args = setupargs("ReadCard")
input_dir    = args.indir
config_file  = args.ConfigFile

check_limit_reader_path(input_dir,"card")
check_arg(config_file,"ConfigFile","readLimitsCutCount_individualbins.py")

from file_reader import read_limit_output

_Fulllog=[]
if not os.path.exists(input_dir+".txt"):
       _Fulllog = read_limit_output(input_dir,"card_")
       log_input_dir = open(input_dir+".txt","w")
       for x in _Fulllog:
              log_input_dir.write(x+"\n")
       log_input_dir.close()
else:
       inlog_input_dir = open(input_dir+".txt","r")
       for x in inlog_input_dir:
              _Fulllog.append(x)
       inlog_input_dir.close()
              
from HNType1_config import *
#PrintList(_Fulllog)

_setup=[]
Channels  =  GetConfig("channels",    config_file,_setup)
flavours  =  GetConfig("flavours",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
masses_s  =  GetConfig("masses_s",    config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
Outdir    =  GetSConfig("OutDir",     config_file,_setup)
SRs       =  GetConfig("SRs",         config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([years, SRs, flavours,Channels])
outfiles = []
files_tocopy=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years, SRs, flavours,Channels])
       year     = GetIter[0]
       _sr      = GetIter[1]
       flavour  = GetIter[2]
       channel       = GetIter[3]

       print year + " " + _sr + " " + flavour + " " + channel

       channel_tag = ChooseTag(channel)

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, channel, 1)

       
       for _id in IDs:
              _allmassfilename = flavour + "_"+ _sr
              MakeDirectory(Outdir)
              MakeDirectory(Outdir+ year)
              MakeDirectory(Outdir+ year+"/"+_allmassfilename)
              outfile = open(Outdir+ year+"/"+_allmassfilename+"/result"+channel+"_"+_id+"_"+channel_tag+".txt","w")
              print "Creating file  " + Outdir+ year+"/"+_allmassfilename+"/result"+channel+"_"+_id+"_"+channel_tag+".txt"
              for mass in _masses:
              
                     Expected_Central = "--"
                     Expected_1sdUp = "--"
                     Expected_1sdDn = "--"
                     Expected_2sdUp = "--"
                     Expected_2sdDn = "--"
                            
                     #card_2017_EE_SR1_N1500_passTightID_nocc_reco_mlljj.txt"
                     #card_2018_MuMu_SR1_N700_combined_POGTightPFIsoVeryTight.txt
                     tag = "card_"+year +"_"+flavour + "_"+_sr+"_N"+mass+"_"+_id+"_"+channel_tag
                                   
                     Found=False
                     for line in _Fulllog:
                            if "Input datacard" in line:
                                   if tag in line:
                                          Found=True
                            if "Done in" in line:
                                   Found=False
                            if Found:
                                   if "Limit: r" in line:
                                          print line.split()[3]
                                          Expected_Central = line.split()[3]
                                          Expected_1sdUp = line.split()[3]
                                          Expected_1sdDn = line.split()[3]
                                          Expected_2sdUp = line.split()[3]
                                          Expected_2sdDn = line.split()[3]
                                          
                                          print mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n'                     
                                          outfile.write(mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n')
              outfile.close()

