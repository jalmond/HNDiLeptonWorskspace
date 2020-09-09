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

    histname=GetHistName(channel,SR, mass,year)

    filepaths = []
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/2016/SIG/HNtypeI_JA_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBF":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/2016/SIG/HNtypeI_JA_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")
    else :
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/2016/SIG/HNtypeI_JA_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
        if int(mass) > 250:
            filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/2016/SIG/HNtypeI_JA_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")

    total=0

    for _filename in filepaths:
        _file = ROOT.TFile(_filename)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    if total < 0:
        return 0.

    print total
    # copy scale used by JS in 2016        
    scale_ = 1.
    if int(mass) <= 200:
        scale_ = 0.001
    elif int(mass) <= 600:
        scale_ = 0.1
    elif int(mass) <=1000:
        scale_ = 1.
    else:
        scale_ = 10.


    #since only 2016 samples available use these and scale to lumi for now
    # effective lumi: 36.47 fb-1 (2016) 41.54 fb-1 (2017) 59.96 fb-1 (2018)

    if year == "2017": 
        scale_ = scale_* 41.54/36.47
    elif year == "2018":
        scale_*59.96/36.47

    return round(total*scale_,4)


def GetFakeCount(channel, SR, mass,year):
    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + year + "/HNtypeI_JA_SkimTree_SSNonIso_Fake"+channel+".root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + year + "/HNtypeI_JA_SkimTree_SSNonIso_FakeOS.root"  )


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return round(total,4)


def GetCFCount(channel,SR, mass,year):

    if channel == "MuMu":
        return 0.

    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + year + "/HNtypeI_JA_SkimTree_SSNonIso_CF.root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + year + "/HNtypeI_JA_SkimTree_SSNonIso_OSCF.root"  )


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return round(total,4)

        
def GetPromptCount(channel,SR, mass,year):
        
    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + year + "/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root")

    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + year + "/HNtypeI_JA_SkimTree_SSNonIso_OSPrompt.root")


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return round(total,4)


import ROOT

_channels = ["Schannel","Tchannel", "Combinedchannel"]
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
                    pinput = os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsCutCount/"
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
                    rate_line = "rate  " + str(GetPromptCount(channel,SR, mass,year)) + " " + str(GetFakeCount(channel,SR, mass,year)) + " " + str(GetCFCount(channel,SR,mass,year)) + " " + str(GetSignalEvents(channel,SR,mass,year, _channel))
                    print  pinput + year+"/"+ channel + "_" + SR + "/card_"+channel + "_" + SR+"_N" + mass + isVBF+".txt" + str(GetSignalEvents(channel,SR,mass,year, _channel))
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
