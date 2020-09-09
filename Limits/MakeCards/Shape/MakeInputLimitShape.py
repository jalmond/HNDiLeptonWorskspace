import os

def GetHistName(channel,SR, mass,year):

    histname =""
    if SR == "Bin1" or SR == "Bin3":
        histname += "SR1"
    else:
        histname += "SR2"
 
    histname += "_" +channel + "_mn"+  mass + "_"#histname += "highmass"    
    if SR == "Bin1" or SR == "Bin2":
        histname += "same_sign"
    else:
        histname += "opposite_sign"

    if channel == "EE":
        histname+= "/"+ histname +"_nevent_HNtypeI_JA_"+channel+"_HNTight2016_"
    else:
        histname+= "/"+ histname +"_nevent_HNtypeI_JA_"+channel+"_HNTightV1_"
    return histname

def GetMassBin(mass, VBF):

    masses = ["100",
              "125",
              "200",
              "250",
              "300",
              "400",
              "500",
              "600",
              "700",
              "800",
              "900",
              "1000",
              "1100",
              "1200",
              "1300",
              "1400",
              "1500",
              "1700"]

    masses_vbf =  [   "300",
              "400",
              "500",
              "600",
              "700",
              "800",
              "900",
              "1000",
              "1100",
              "1200",
              "1300",
              "1400",
              "1500",
              "1700"]

    counter = 0
    _masses= masses
    if VBF == "_VBF":
        _masses = masses_vbf
    for m in _masses:
        counter = counter +1
        if m == mass:
            return counter


    return -1

def GetSignalEvents(channel,SR, mass,year, VBF):

    histname="signal"

    filepath = os.getenv("PLOT_PATH") + "Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ SR + "/HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "__"+_id + ".root"
    
    total=0

    _file = ROOT.TFile(_filename)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    if total < 0:
        return 0.

    return total



        
def GetCount(histname,flavour,SR, mass,year,_id):

    filepath  = os.getenv("PLOT_PATH") + "Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ SR + "/HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "__"+_id + ".root"

    total=0
    _file = ROOT.TFile(filepath)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    return round(total,5)


import ROOT

_channels = ["Schannel","Tchannel"]#, "Combinedchannel"]
channels = ["MuMu", "EE"]
years = ["2016","2017","2018"]
SRs = ["Bin1","Bin2","Bin3","Bin4"]
masses = ["100" ,"200","200", "400", "500", "600","700","800","900","1000","1100", "1200","1500"]
masses_t = [ "600","700","800","900","1000","1100", "1200","1500"]

for year in years:
    for _channel in _channels:
        for channel in channels:
            for SR in SRs:
                _masses = masses
                if _channel == "Tchannel":
                    _masses = masses_t

                for mass in _masses:
                    pinput = os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsShape/"
                    if not os.path.exists(pinput):
                        os.system("mkdir " + pinput)

                    isVBF=""
                    if _channel == "Tchannel":
                        isVBF="_VBF"
                    if _channel == "Combinedchannel":
                        isVBF="_combined"

                    if not os.path.exists(pinput+year+"/"):
                        os.system("mkdir " + pinput +year+"/")
                    if not os.path.exists(pinput+year+"/" + channel + "_" + SR ):
                        os.system("mkdir " + pinput +year+"/"+ channel + "_" + SR )


                    limitfile = open(pinput + year+"/"+ channel + "_" + SR + "/card_"+channel + "_" + SR+"_N" + mass + isVBF+".txt","w")


                    limitfile.write("imax 1  number of channels\n")
                    limitfile.write("jmax 3  number of backgrounds\n")
                    limitfile.write("kmax *  number of nuisance parameters (sources of systematical uncertainties)\n")
                    limitfile.write("------------\n")
                    limitfile.write("shapes * * shape_HN"+mass+"_"+year+"_"+chanel+"_"+SR+"_input.root $PROCESS $PROCESS_$SYSTEMATIC\n")
                    limitfile.write("------------\n")
                    limitfile.write("# we have just one channel, in which we observe 0 events\n")
                    limitfile.write("bin bin1\n")
                    limitfile.write("observation *\n")
                    limitfile.write("------------\n")
                    limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
                    limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
                    limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
                    limitfile.write("# on each process and bin\n")
                    limitfile.write("bin	bin1	bin1	bin1	bin1\n")
                    limitfile.write("process	prompt	fake	cf	HN"+mass+"\n")
                    limitfile.write("process	1	2	3	0\n")
                    rate_line = "rate  " + str(GetCount("prompt",channel,SR, mass,year)) + " " + str(GetCount("Fake",channel,SR, mass,year)) + " " + str(GetCount("cf",channel,SR,mass,year)) + " " + str(GetEvents("signal",channel,SR,mass,year, _channel))
                    print  pinput + year+"/"+ channel + "_" + SR + "/card_"+channel + "_" + SR+"_N" + mass + isVBF+".txt" + str(GetSignalEvents(channel,SR,mass,year, _channel))
                    rate_line += "\n"
                    limitfile.write(rate_line)
                    limitfile.write("Lumi	lnN	1.05	-	-	1.05\n")
                    limitfile.write("Fake	lnN	-	1.3	-	-\n")
                    limitfile.write("CF	        lnN	-	-	1.439	-\n")
                    limitfile.write("MuonID	shapeN2 1       1       1       1\n")
                    limitfile.write("ElectronE	shapeN2 1       1       1       1\n") 
                    limitfile.write("JES	shapeN2 1       1       1       1\n") 
                    limitfile.write("JER	shapeN2 1       1       1       1\n") 
                    limitfile.write("* autoMCStats 1 0 0 0\n")
                    
                    limitfile.close()

