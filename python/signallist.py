import os 


siglist = open("signallist.txt","r")
for x in siglist:
    sig=  x.split()[0]
    if "SSWW" in sig:
        #SSWWTypeI_NLO_SF_M1000
        datasetsig = sig
        datasetsig = datasetsig.replace("SSWWTypeI_NLO_","SSWWTypeIHeavyN-")
        datasetsig = datasetsig.replace("_M","mix_Dilepton_NLO_MN")
        datasetsig = datasetsig + "_TuneCP5_13TeV-madgraph-pythia8"
        print datasetsig
    if "DY" in sig:
        #DYTypeI_NLO_SF_M1200
        datasetsig = sig
        datasetsig = datasetsig.replace("DYTypeI_NLO_","DYTypeIHeavyN-")
        datasetsig = datasetsig.replace("_M","mix_Dilepton_NLO_MN")
        datasetsig = datasetsig + "_TuneCP5_13TeV-amcatnlo-pythia8"
        print datasetsig

    if "VBF" in sig:
        datasetsig = sig
        datasetsig = datasetsig.replace("VBFTypeI_NLO_","VBFTypeIHeavyN-")
        datasetsig = datasetsig.replace("_M","mix_Dilepton_NLO_MN")
        datasetsig = datasetsig + "_TuneCP5_13TeV-amcatnlo-pythia8"

        print datasetsig

siglist.close()
siglist = open("signallist.txt","r")

for x in siglist:
    sig=  x.split()[0]
    sig = sig+"_private"
    print sig
siglist.close()
