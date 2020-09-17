from HNType1_config import *
import os, ROOT

lxplus="lxplus785.cern.ch"

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()

config_file= options.x

if str(os.getenv("PLOTTER_WORKING_DIR")) == "None":
       print "setup enviroment...."
       exit()
if config_file == "123":
    print "Need input file to configure job"
    print "python MakeInputLimitCC_log.py -x config.txt"
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
BkgType   =  GetSConfig("BkgType",     config_file,_setup)
Outdir    =  GetSConfig("OutDir",      config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)


Outputdir = os.getenv("PLOTTER_WORKING_DIR")+"/"+ str(Outdir) + "/"+str(BkgType)+"/run/"
MakeDirectory(Outputdir)

       
outname="AllCards"
for s in SRs:
       outname+="_"+s

niter = NIteration([years, _channels, flavours,SRs])     
outfiles = []
files_tocopy=[]
allcards= open(os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsCutCount/MCBased/run/"+outname+".txt","w")

for _iter in range(0,niter):

       GetIter  = SumIteration(_iter, [years, _channels, flavours,SRs])
       year     = GetIter[0]
       _channel = GetIter[1]
       flavour  = GetIter[2]
       SR       = GetIter[3]

       print year + " " + _channel + " " + flavour + " " + SR

       IDs     = ChooseID(IDMu, IDEl, flavour, 1)
       _masses = ChooseMassList(masses_s, masses_t, _channel, 1)

       file_output = os.getenv("PLOTTER_WORKING_DIR")+"/"+ Outdir + "/"+BkgType+"/" + year+"/"
       MakeDirectory(file_output)
       file_output=file_output+ flavour + "_" + SR
       MakeDirectory(file_output)
       for _id in IDs:

              _txt =  file_output +"/event_counts_"+year+"_"+SR+"_"+_id+"_"+flavour+"_cutcount.txt"
              for mass in _masses:
                     pinput = os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsCutCount/DataDriven/"
                     if not os.path.exists(pinput):
                            os.system("mkdir " + pinput)

                     isVBF=ChooseTag(_channel)
                     MakeDirectory(pinput+year+"/")
                     MakeDirectory(pinput+year+"/"+ flavour + "_" + SR)
                     allcards.write(pinput + year+"/"+ flavour + "_" + SR + "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+".txt\n")
                                       
                     limitfile = open(pinput + year+"/"+ flavour + "_" + SR + "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+".txt","w")
                     
                     limitfile.write("imax 1  number of channels\n")
                     limitfile.write("jmax 3  number of backgroundss\n")
                     limitfile.write("kmax 8  number of nuisance parameters (sources of systematical uncertainties)\n")
                     limitfile.write("------------\n")
                     limitfile.write("# we have just one channel, in which we observe 0 events\n")
                     limitfile.write("bin sr1\n")
                     limitfile.write("observation -1\n")
                     limitfile.write("------------\n")
                     limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
                     limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
                     limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
                     limitfile.write("# on each process and bin\n")
                     limitfile.write("bin	sr1	sr1	sr1	sr1\n")
                     limitfile.write("process	prompt	fake	cf	HN"+mass+"\n")
                     limitfile.write("process	1	2	3	0\n")
                     
                     nprompt = GetPromptCountSRMassBin(flavour,SR, mass,year,_id,Analyzer)
                     nfake = GetFakeCountSRMassBin(flavour,SR, mass,year,_id,Analyzer)
                     ncf = GetCFCountSRMassBin(flavour,SR,mass,year,_id,Analyzer)
                     nsig = GetSignalEventsSRMassBin(flavour,SR,mass,year, _channel,_id,Analyzer)

                     rate_line = "rate  " + str(nprompt) + " " + str(nfake) + " " + str(ncf) + " " + str(nsig)
                     rate_line += "\n"
                     limitfile.write(rate_line)
                     limitfile.write("Lumi	lnN	1.025	-	-	1.025\n")
                     limitfile.write("MCNorm	lnN	1.135	-	-	-\n")
                     limitfile.write("Fake	lnN	-	1.3	-	-\n")
                     limitfile.write("CF	        lnN	-	-	1.439	-\n")
                     limitfile.write("MuonID	lnN	1.02	-	-	1.0054\n")
                     limitfile.write("ElectronE	lnN	1.0251	-	-	1.0191\n")
                     limitfile.write("JES	lnN	1.2491	-	-	1.0154\n")
                     limitfile.write("JER	lnN	1.0706	-	-	1.0385\n")
                     
                
                     limitfile.close()
allcards.close()
