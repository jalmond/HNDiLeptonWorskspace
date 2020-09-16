from HNType1_config import *
import os

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
masses_s  =  GetConfig("masses",      config_file,_setup)
masses_t  =  GetConfig("masses_t",    config_file,_setup)
IDMu      =  GetConfig("IDMu",        config_file,_setup)
IDEl      =  GetConfig("IDEl",        config_file,_setup)
Analyzer  =  GetConfig("Analyzer",    config_file,_setup)
BkgType   =  GetConfig("BkgType",     config_file,_setup)
Outdir    =  GetConfig("OutDir",      config_file,_setup)
print "Running with setup:"
PrintSetup(_setup)


Outputdir = os.getenv("PLOTTER_WORKING_DIR")+"/"+ str(Outdir[0]) + "/"+str(BkgType[0])+"/run/"
MakeDirectory(Outputdir)

       
outname="AllCards"
for s in SRs:
       outname+="_"+s

niter = NIteration([years, _channels, flavours])     
for _iter in range(0,niter):
       GetIter = SumIteration(_iter, [years, _channels, flavours])
       year    = GetIter[0]
       _channel = GetIter[1]
       flavour = GetIter[2]
       print year + " "  + _channel + " " + flavour
       continue
       
       IDs=[]
       if flavour == "MuMu":
              IDs = IDMu
       else:
              IDs=IDEl
       for SR in SRs:
              _masses = masses
              if flavour == "TChannel":
                     _masses = masses_t
              for _id in IDs:
                     for mass in _masses:
                            pinput = os.getenv("PLOTTER_WORKING_DIR")+"/"+ Outdir + "/"+BkgType+"/"
                      
                            isVBF=""
                            if _channel == "TChannel":
                                   isVBF="_VBF"
                            if _channel == "Combinedflavour":
                                   isVBF="_combined"

                            MakeDirectory(pinput+year+"/")
                            MakeDirectory(pinput+year+"/"+flaovur+"_"+SR)
                            
                            
                
                            limitfile.close()
