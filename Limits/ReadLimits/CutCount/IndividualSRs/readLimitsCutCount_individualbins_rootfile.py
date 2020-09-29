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

check_limit_reader_path(input_dir,"CutCount_HN_SR1_2")
check_arg(config_file,"ConfigFile","readLimitsCutCount_individualbins_rootfile.py")

from file_reader import read_limit_output

#_Fulllog = read_limit_output(input_dir,"card_")

from HNType1_config import *
#PrintList(_Fulllog)

_setup=[]
Channels  =  GetConfig("channels",    config_file,_setup)
flavours  =  GetConfig("flavours",    config_file,_setup)
years     =  GetConfig("years",       config_file,_setup)
masses_s  =  GetConfig("masses_s",    config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
masses_c  =  GetConfig("masses_c",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
SRs       =  GetConfig("SRs",         config_file,_setup)
Analyzer  =  GetSConfig("Analyzer",   config_file,_setup)
Outdir    =  GetSConfig("OutDir",     config_file,_setup)
Limitdir    =  GetSConfig("LimitDir",     config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)

MissingLimit=[]
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
       
       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t,masses_c, channel, 1)

       channel_tag = ChooseTag(channel)

       for _id in IDs:
              _allmassfilename = flavour + "_"+ _sr
              MakeDirectory("out/"+Analyzer)
              MakeDirectory("out/"+Analyzer+"/CutCount")
              MakeDirectory(Outdir)
              MakeDirectory(Outdir+ year)
              MakeDirectory(Outdir+ year+"/"+_allmassfilename)
              outfile = open(Outdir+ year+"/"+_allmassfilename+"/result"+channel_tag+"_"+_id+".txt","w")
              print "Creating file  " + Outdir+ year+"/"+_allmassfilename+"/result"+channel_tag+"_"+_id+".txt"
              for mass in _masses:
                            
                     Expected_Central = "--"
                     Expected_1sdUp = "--"
                     Expected_1sdDn = "--"
                     Expected_2sdUp = "--"
                     Expected_2sdDn = "--"
                            
                     #card_2017_EE_SR1_N1500_passTightID_nocc_reco_mlljj.txt"
                     #card_2018_MuMu_SR1_N700_combined_POGTightPFIsoVeryTight.txt
                     #higgsCombinecard_2018_MuMu_SR3_N1100_VBF_HNTightV1.txt_exp0.500.HybridNew.mH120.quant0.500.root
                     
                     _filename = Limitdir+  input_dir+"/higgsCombinecard_"+year+"_"+flavour + "_"+_sr+"_N"+mass+channel_tag+"_"+_id+".txt_exp0.500.HybridNew.mH120.quant0.500.root"   

                     if os.path.exists(_filename):
                            os.system("root -l -q -b 'ReadLimitFromTree.C(\"/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"+input_dir+"/higgsCombinecard_"+year+"_"+flavour+"_"+_sr+"_N"+mass+channel_tag+"_"+_id+".txt_exp0.500.HybridNew.mH120.quant0.500.root\",\"test\")'")

                            readlimit = open("test_limit.txt","r")
                            for rl in readlimit:
                                   if len(rl.split()) == 1:
                                          if str(rl.split()[0]) == "0.0000":
                                                 continue

                                          Expected_Central=str(rl.split()[0])
                                          Expected_1sdUp=str(rl.split()[0])
                                          Expected_1sdDn=str(rl.split()[0])
                                          Expected_2sdUp=str(rl.split()[0])
                                          Expected_2sdDn=str(rl.split()[0])
                            readlimit.close()
                            os.system("rm test_limit.txt")
                     
                     print mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n'                     
                     outfile.write(mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n')
                     if Expected_Central == "--":
                            MissingLimit.append(_filename)
              outfile.close()

for x in  MissingLimit:
       print "Limit missing for " + x
