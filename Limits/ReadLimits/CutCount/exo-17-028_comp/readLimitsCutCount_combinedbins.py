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

check_limit_reader_path(input_dir,"exo_17028")
check_arg(config_file,"ConfigFile","readLimitsCutCount_combinedbins.py")

from file_reader import read_limit_output

_Fulllog = read_limit_output(input_dir,"")

from HNType1_config import *
#PrintList(_Fulllog)

_setup=[]
Channels  =  GetConfig("channels",    config_file,_setup)
flavours  =  GetConfig("flavours",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
masses_s  =  GetConfig("masses_s",    config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
Outdir    =  GetSConfig("OutDir",     config_file,_setup)
Charges   =  GetConfig("Charges",     config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)

niter = NIteration([years, Charges, flavours,Channels])
outfiles = []
files_tocopy=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years, Charges, flavours,Channels])
       year     = GetIter[0]
       charge   = GetIter[1]
       flavour  = GetIter[2]
       channel       = GetIter[3]

       print year + " " + charge + " " + flavour + " " + channel

       _masses = ChooseMassList(masses_s, masses_t, channel, 1)


       _allmassfilename = flavour + "_Combined"
       MakeDirectory(Outdir)
       MakeDirectory(Outdir +"/"+ year)
       MakeDirectory(Outdir + "/"+ year+"/"+_allmassfilename)
       outfile = open(Outdir+ "/"+ year+"/"+_allmassfilename+"/result"+channel+".txt","w")
       print "Creating file  " + Outdir+ "/"+ year+"/"+_allmassfilename+"/result"+channel+".txt"
       for mass in _masses:
              
              Expected_Central = "--"
              Expected_1sdUp = "--"
              Expected_1sdDn = "--"
              Expected_2sdUp = "--"
              Expected_2sdDn = "--"
              #card_combinedSS_MuMu_N100_POGTightPFIsoVeryTight_reco_ml1jj_2016.txt
              #HNMuMu_300_VBF.txt
              tag = "HN"+flavour + "_"+mass +channel

                                   
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

