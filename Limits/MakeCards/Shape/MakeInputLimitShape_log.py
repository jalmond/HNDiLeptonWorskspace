#!/usr/bin/env python

import os
import sys
import argparse
import datetime

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

args = setupargs()
if args.Full:
       check_lxplus_connection()
       print "Connected to " + get_lxplus_host()


pwd = os.getcwd()

config_file= args.ConfigFile

# now import analysis functions
from HNType1_config import *


if config_file == "None":
    print "Need input file to configure job"
    print "python MakeInputLimitCC_log.py -c config.txt"
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
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
Vars      =  GetConfig("Vars",        config_file,_setup)
Workspace =  GetSConfig("Workspace", config_file,_setup)

print "Running with setup:"
PrintSetup(_setup)


Outputdir = os.getenv("PLOTTER_WORKING_DIR")+"/"+ str(Outdir) + "/"+str(Analyzer)+"/run/"
MakeDirectory(os.getenv("PLOTTER_WORKING_DIR")+"/"+ str(Outdir))

MakeDirectory(Outputdir)

       
outname="AllCards"
for s in SRs:
       outname+="_"+s

list_liters = [years, _channels, flavours,SRs,Vars]
niter = NIteration(list_liters)

outfiles = []
files_tocopy=[]
for _iter in range(0,niter):

       GetIter  = SumIteration(_iter,  list_liters)
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]
       _var     = GetIter[4]


       print year + " " + _channel + " " + flavour + " " + SR + " " + _var

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, _channel, 1)

       file_output = os.getenv("PLOTTER_WORKING_DIR")+"/"+ Outdir + "/"+str(Analyzer)+"/" + year+"/"
       MakeDirectory(file_output)
       file_output=file_output+ flavour + "_" + SR
       MakeDirectory(file_output)
       
       for _id in IDs:

              _txt =  file_output +"/event_counts_"+year+"_"+SR+"_"+_id+"_"+flavour+"_"+_var+"_cutcount.txt"

              outfiles.append([_txt,"event_counts_"+year+"_"+SR+"_" +_id+"_"+flavour+"_"+_var+"_cutcount.txt", year+"_"+flavour + "_" + SR+"_"+_id+"_"+_var])
              limitfile = open(_txt ,"w")
              limitfile.write("Mass mN   | Nprompt   | NFake    | NCF      |  Total Bkg  | Nsignal   || EXO-17-028 Eff  | EXO-17-028 Bkg \n")
              limitfile.write("-"*len("Mass mN   | Nprompt   | NFake    | NCF      |  Total Bkg  | Nsignal   || EXO-17-028 Eff  | EXO-17-028 Bkg  \n")+"\n")
              for mass in _masses:
                     if args.Plots:
                            os.system("root -l -q -b 'MakePlot/MakeBinnedSignalBkg.C(\"Schannel\",\""+year+"\",\""+flavour+"\",\""+_id+"\", \""+Analyzer+"\", \""+SR+"\", \""+mass+"\",\""_var+"\",\"event_counts_"+year+"_N"+mass+"_"+SR+"_" +_id+"_"+flavour+"_cutcount.png\")'")
                            files_tocopy.append(["event_counts_"+year+"_N" +mass+"_"+SR+"_"+_id+"_"+flavour+"_"+_var+"_cutcount.png", flavour])
                     
                     nprompt = GetCountShape("prompt",flavour,SR, mass,year,_id,_var)
                     nfake   = GetCountShape("Fake",flavour,SR, mass,year,_id,_var)
                     ncf     = GetCountShape("cf",flavour,SR,mass,year,_id,_var) 
                     nsig    = GetSignalEventsShape(flavour,SR,mass,year, _channel,_id,_var)
                     sifeff  = str(GetSignalEventsShape(flavour,SR,mass,year, _channel,_id,_var)
                     bkg     = nprompt+ nfake +ncf

                     bkg_exo_17_028=GetEXO_17_028_Bkg(flavour,SR,mass)
                     eff_exo_17_028=GetEXO_17_028_Eff(flavour,SR,mass)

                     isVBF   = ChooseTag(_channel)

                     rate_line = str(nprompt) + " "*(10-len(str(nprompt))) +"| " + str(nfake) + " "*(9-len(str(nfake)))  +"| "+ str(ncf) + " "*(9-len(str(ncf)))  +"| "+ str(bkg) + " "*(12-len(str(bkg)))  +"| "+ str(sifeff)+" "*(10-len(str(sifeff)))  +"|| "+ str(eff_exo_17_028) + " "*(15-len(str(eff_exo_17_028))) + " | " + str(bkg_exo_17_028) 
                     
                     limitfile.write(mass + " "*(10-len(mass)) +"| " + rate_line + "\n")
                     print mass + " "*(10-len(mass)) +"| " + rate_line 
                                          

              limitfile.close()

if args.Full:
       
       webfile = open("index.html","w")
       webfile.write('<html><font face="Helvetica"><head><title> HNTypeI Event Yields HighMass Mass Shape Analysis</title></head>\n')
       webfile.write("<body>\n")
       webfile.write("<h1> High Mass SR </h1>\n")
       webfile.write('<br> <font size="4"><b>  </b></font> <br><br>\n')
       webfile.write("<a href=MuMu/indexMuMu.html> MuMu </a><br>\n")
       webfile.write("<a href=EE/indexEE.html> EE </a><br>\n")
       webfile.close()
       lxplus=get_lxplus_host()
       os.system("scp index.html jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/")
       os.system("ssh jalmond@" + lxplus + " 'mkdir ~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"'")
       os.system("ssh jalmond@" + lxplus + " 'mkdir ~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/'")
       for x in files_tocopy:
              os.system("scp " + x[0] +  " jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/"+x[1]+"/")
              os.system("rm " + x[0])

       webfileEE = open("indexEE.html","w")
       webfileMuMu = open("indexMuMu.html","w")
       for x in outfiles:
              if "MuMu" in x[0]:
                     os.system("scp " + x[0] +  " jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/MuMu/")
                     webfileMuMu.write('<a href='+x[1]+'> '+x[2]+' </a><br>\n')

              if "EE" in x[0]:
                     os.system("scp " + x[0] +  " jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/EE/")
                     webfileEE.write('<a href='+x[1]+'> '+x[2]+' </a><br> \n'        )
       for x in files_tocopy:
              if x[1] == "EE":
                     webfileEE.write('<a href='+x[0]+'> '+x[0]+' </a><br> \n'        )
              else:
                     webfileMuMu.write('<a href='+x[0]+'> '+x[0]+' </a><br> \n'        )

       webfileEE.close()
       webfileMuMu.close()
       os.system("ssh jalmond@" + lxplus + " 'mkdir ~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/EE/'")
       os.system("ssh jalmond@" + lxplus + " 'mkdir ~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/MuMu/'")

       os.system("scp indexEE.html jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/EE/")
       os.system("scp indexMuMu.html jalmond@" + lxplus + ":~/www/SNU/SKAnalyzer/EventCounts/"+Analyzer+"/HighMassSR/MuMu/")
       os.system("rm  index*.html")
