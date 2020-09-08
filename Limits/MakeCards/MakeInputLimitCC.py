import os

def GetHistName(channel,SR, mass,year):

    histname =""
    if SR == "Bin1" or SR == "Bin3":
        histname += "SR1"
    else:
        histname += "SR2"
    histname += "highmass"
    if SR == "Bin1" or SR == "Bin2":
        histname += "same_sign"
    else:
        histname += "opposite_sign"

def GetFake(channel, SR, mass,year):
    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append("/Users/john/Type1/MergedFiles/"        + year + "/HNtypeI_JA_SkimTree_SSFake"+channel+".root"  )
    else:
        filepaths.append("/Users/john/Type1/MergedFiles/"        + year + "/HNtypeI_JA_SkimTree_OSFake.root"  )

    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return total


def GetCF(channel,SR, mass,year):
    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append("/Users/john/Type1/MergedFiles/"        + year + "/HNtypeI_JA_SkimTree_SSCF.root"  )
    else:
        filepaths.append("/Users/john/Type1/MergedFiles/"        + year + "/HNtypeI_JA_SkimTree_OSCF.root"  )

    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return total
        
def GetPrompt(channel,SR, mass,year):
        
    histname=GetHistName(channel,SR, mass,year)
    filepaths =[]
    if SR == "Bin1" or SR == "Bin2":
        filepaths.append("/Users/john/Type1/MergedFiles/" + year + "/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root")

    else:
        filepaths.append("/Users/john/Type1/MergedFiles/" + year + "/HNtypeI_JA_SkimTree_SSNonIso_OSPrompt.root")


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return total

import ROOT

channels = ["MM", "EE"]
years = ["2016","2017","2018"]
SRs = ["Bin1","Bin2","Bin3","Bin4"]
masses = ["100","200","500","1100","1500"]
for year in years:
    for channel in channels:
        for SR in SRs:
            for mass in masses:
                pinput = "DataCardsCutCount/"
                if not os.path.exists(pinput):
                    os.system("mkdir " + pinput)
                pinput += channel + "_" + SR + "/"
                if not os.path.exists(pinput):
                    os.system("mkdir " + pinput)
                limitfile = open("DataCardsCutCount/" + channel + "_" + SR + "/card_"+channel + "_" + SR+"_N" + mass +".txt","w")
                limitfile.write("imax 1  number of channels\n")
                limitfile.write("jmax 3  number of backgroundss\n")
                limitfile.write("kmax 7  number of nuisance parameters (sources of systematical uncertainties)\n")
                limitfile.write("------------\n")
                limitfile.write("# we have just one channel, in which we observe 0 events\n")
                limitfile.write("bin 1\n")
                limitfile.write("observation -1\n")
                limitfile.write("------------\n")
                limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
                limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
                limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
                limitfile.write("# on each process and bin\n")
                limitfile.write("bin	1	1	1	1\n")
                limitfile.write("process	prompt	fake	cf	HN"+mass+"\n")
                limitfile.write("process	1	2	3	0\n")
                rate_line = "rate  " + GetPrompt(channel,SR, mass,year) + " " + GetFake(channel,SR, mass,year) + " " + GetCF(channel,SR,mass,year) 
                rate_line += "\n"
                limitfile.write(rate_line)
                limitfile.write("Lumi	lnN	1.025	-	-	1.025\n")
                limitfile.write("MCNorm	lnN	1.135	-	-	-\n")
                limitfile.write("Fake	lnN	-	1.3	-	-\n")
                limitfile.write("CF	lnN	-	-	1.439	-\n")
                limitfile.write("MuonID	lnN	1.02	-	-	1.0054\n")
                limitfile.write("ElectronE	lnN	1.0251	-	-	1.0191\n")
                limitfile.write("JES	lnN	1.2491	-	-	1.0154\n")
                limitfile.write("JER	lnN	1.0706	-	-	1.0385\n")
                
                
                limitfile.close()
