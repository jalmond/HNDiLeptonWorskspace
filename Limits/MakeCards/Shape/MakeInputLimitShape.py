import os

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

def GetSignalEvents(channel,SR, mass,year, VBF,_id,_var):

    histname="signal"

    filepath = os.getenv("PLOT_PATH") + "Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ SR + "/HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root"

    total=0

    _file = ROOT.TFile(filepath)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    if total < 0:
        return 0.

    return total



        
def GetCount(histname,flavour,SR, mass,year,_id,_var):

    
    
    filepath = os.getenv("PLOT_PATH") + "Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ SR + "/HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root"
    total=0
    _file = ROOT.TFile(filepath)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    return round(total,4)


import ROOT

_channels = ["reco_ml1jj","reco_ml2jj","reco_mlljj","signalbin"]#"reco_finebin_ml1jj","reco_finebin_ml2jj","reco_finebin_mlljj","signalbin"]#,"Tchannel"]#, "Combinedchannel"]
flavours = ["MuMu", "EE"]
years = ["2016","2017","2018"]

SRs = ["SR1","SR2"] #,"SR3","SR4"]
masses = ["100" ,"200","200", "400", "500", "600","700","800","900","1000","1100", "1200","1500"]
masses_t = [ "600","700","800","900","1000","1100", "1200","1500"]
#_channels =  ["ml1jj","ml2jj","mlljj","signalbin", "finebin_ml1jj","finebin_ml2jj","finebin_mlljj"]

IDMu = ["POGTightPFIsoVeryTight","HNTight2016"]
IDEl = ["passTightID","HNTight2016","passTightID_noccb","passTightID_nocc"]
if not os.path.exists(os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsShape/MCBased/run/"):
    os.mkdir(os.getenv("PLOTTER_WORKING_DIR")+"/Limits/DataCardsShape/MCBased/run/")

all_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/MCBased/run/AllCards_SR1_SR2_SR3_SR4.txt","w")

for year in years:
    for _channel in _channels:
        for flavour in flavours:
            IDs = []
            if flavour == "EE":
                IDs = IDEl
            else:
                IDs = IDMu
         
            for SR in SRs:
                
 
                _masses = masses
                if _channel == "Tchannel":
                    _masses = masses_t

                for _id in IDs:
                    for mass in _masses:
                        
             
                        isVBF=""
                        if _channel == "Tchannel":
                            isVBF="_VBF"
                        if _channel == "Combinedchannel":
                            isVBF="_combined"

             
                        _var=_channel  
                        if SR == "SR2":
                           _var=_channel.replace('jj','J')
        
                           
                           
                        pinput="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Plots/Run2Legacy_v4/Limit/Shape/Workspace/"
                        limitfile = open(pinput + "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+"_"+_var+".txt","w")
                        print pinput + "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+"_"+_var+".txt"
                        all_list.write(pinput + "/card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+"_"+_var+".txt \n")
                        
                        input_filepath = os.getenv("PLOT_PATH") + "Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ SR + "/HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root"
                        #input_filepath ="HN"+mass+"_highmass_Run2Legacy_v4_"+year+"_"+SR+"_"+flavour+"_"+_id+"_"+_var+".root"

                        #os.system("cp " + input_filepath + " " + pinput + year+"/"+ flavour + "_" + SR + "/")
                        limitfile.write("imax 1  number of channels\n")
                        limitfile.write("jmax 3  number of backgrounds\n")
                        limitfile.write("kmax *  number of nuisance parameters (sources of systematical uncertainties)\n")
                        limitfile.write("------------\n")
                        limitfile.write("shapes * * "+ " " + input_filepath  + " $PROCESS $PROCESS_$SYSTEMATIC\n")
                        limitfile.write("------------\n")
                        limitfile.write("# we have just one channel, in which we observe 0 events\n")
                        limitfile.write("bin bin1\n")
                        limitfile.write("observation "+str(GetCount("data_obs",flavour,SR, mass,year,_id,_var))+"\n")
                        print str(GetCount("data_obs",flavour,SR, mass,year,_id,_var))
                        limitfile.write("------------\n")
                        limitfile.write("# now we list the expected events for signal and all backgrounds in that bin\n")
                        limitfile.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
                        limitfile.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
                        limitfile.write("# on each process and bin\n")
                        limitfile.write("bin	bin1	bin1	bin1	bin1\n")
                        limitfile.write("process	prompt	fake	cf	signal\n")
                        limitfile.write("process	1	2	3	0\n")
                        rate_line = "rate  " + str(GetCount("prompt",flavour,SR, mass,year,_id,_var)) + " " + str(GetCount("Fake",flavour,SR, mass,year,_id,_var)) + " " + str(GetCount("cf",flavour,SR,mass,year,_id,_var)) + " " + str(GetSignalEvents(flavour,SR,mass,year, _channel,_id,_var))

                        rate_line += "\n"
                        limitfile.write(rate_line)
                        limitfile.write("Lumi	lnN	1.05	-	-	1.05\n")
                        limitfile.write("Fake	lnN	-	1.3	-	-\n")
                        limitfile.write("CF	        lnN	-	-	1.439	-\n")
                        lepid = "MUID"
                        #if flavour == "EE":
                        #    lepid = "ELID"
                        #limitfile.write(lepid + "	shapeN2 1       1       1       1\n")
                        #limitfile.write("JES	shapeN2 1       1       1       1\n") 
                        #limitfile.write("JER	shapeN2 1       1       1       1\n") 
                        limitfile.write("* autoMCStats 0 0 1\n")
                        
                        limitfile.close()
all_list.close()
