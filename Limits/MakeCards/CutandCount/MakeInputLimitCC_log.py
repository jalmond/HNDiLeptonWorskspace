from HNType1_config import *
import os,  ROOT


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


Outputdir = os.getenv("PLOTTER_WORKING_DIR")+"/"+ Outdir + "/"+BkgType+"/run/"
MakeDirectory(Outputdir)

       
outname="AllCards"
for s in SRs:
       outname+="_"+s

for year in years:
    for _channel in _channels:
        for flavour in flavours:
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

                     
                        if not os.path.exists(pinput+year+"/"):
                            os.system("mkdir " + pinput +year+"/")
                        if not os.path.exists(pinput+year+"/" + flavour + "_" + SR ):
                            os.system("mkdir " + pinput +year+"/"+ flavour + "_" + SR )
                      
                     
                        rate_line = "rate  " + str(GetPromptCount(flavour,SR, mass,year,_id)) + " " + str(GetFakeCount(flavour,SR, mass,year,_id)) + " " + str(GetCFCount(flavour,SR,mass,year,_id)) + " " + str(GetSignalEvents(flavour,SR,mass,year, _channel,_id))
                        print  pinput + year+"/"+ flavour + "_" + SR + "/card_"+flavour + "_" + SR+"_N" + mass + isVBF+".txt" + str(GetSignalEvents(flavour,SR,mass,year, _channel,_id))
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
