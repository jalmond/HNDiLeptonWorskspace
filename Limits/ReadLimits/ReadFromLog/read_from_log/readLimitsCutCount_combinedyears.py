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

check_limit_reader_path(input_dir,"comb_years")
check_arg(config_file,"ConfigFile","readLimitsShape.py")

from file_reader import read_limit_output

_Fulllog = read_limit_output(input_dir,"combinedyears")

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
Regions   =  GetConfig("Regions",     config_file,_setup)
_vars     =  GetConfig("Vars",        config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([Regions, flavours,Channels])
outfiles = []
files_tocopy=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [Regions, flavours,Channels])
       year     = "CombinedYears"
       region   = GetIter[0]
       flavour  = GetIter[1]
       channel       = GetIter[2]

       print year + " " +region + " " + flavour + " " + channel

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, channel, 1)


       for _id in IDs:
              for _var in _vars:
                     nbin = region
                     _allmassfilename = flavour + "_"+ nbin
                     MakeDirectory(Outdir)
                     MakeDirectory(Outdir+ year)
                     MakeDirectory(Outdir+ year+"/"+_allmassfilename)
                     outfile = open(Outdir+ year+"/"+_allmassfilename+"/result"+channel+"_"+_id+"_"+_var+".txt","w")
                     print "Creating file  " + Outdir+ year+"/"+_allmassfilename+"/result"+channel+"_"+_id+"_"+_var+".txt"
                     for mass in _masses:
                            
                            Expected_Central = "--"
                            Expected_1sdUp = "--"
                            Expected_1sdDn = "--"
                            Expected_2sdUp = "--"
                            Expected_2sdDn = "--"
                            #card_combinedSS_MuMu_N100_POGTightPFIsoVeryTight_reco_ml1jj_2016.txt
                            #EE_CombinedSS_EE_N300_passTightID_reco_mlljj_combinedyears.txt
                            tag = flavour + "_"+region+"_"+flavour+"_N"+mass+"_"+_id+"_"+_var
                                   
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

