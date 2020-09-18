import os

SRs = ["SR1","SR2"]
masses = ["100" ,"200","300","400","500","600","700","800","900","1000","1100","1200","1500"]
channels = ["MuMu","EE"]
cards = [""]
years = ["2016", "2017","2018"]

lists =[]
IDMu = ["POGTightPFIsoVeryTight","HNTight2016"]
IDEl = ["passTightID","HNTight2016","passTightID_noccb","passTightID_nocc"]


vars_2=["signalbin","reco_ml1J","reco_ml2J","reco_mllJ"]
vars_1=["signalbin","reco_ml1jj","reco_ml2jj","reco_mlljj"]

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/MCBased/run/input_sr1to4.txt","w")
print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"
print "./create-batch -n Shape_HNSR12_MM  -l /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/run/input_sr1to4.txt"
workspace="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Plots/Run2Legacy_v4/Limit/Shape/Workspace/"
os.chdir(workspace);
print workspace
for year in years:
    for c in cards:
        for channel in channels:
            for mass in masses:
                IDs=[]
                if channel == "MuMu":
                    IDs=IDMu
                else:
                    IDs=IDEl
                for _id in IDs:

                        

                    for x in range(0, len(vars_1)):

                        path1="card_"+year+"_"+channel+"_SR1_N"+mass+"_"+_id+"_"+vars_1[x]+".txt"
                        path2="card_"+year+"_"+channel+"_SR2_N"+mass+"_"+_id+"_"+vars_2[x]+".txt"

                        
                        out1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/MCBased/" + year + "/"+channel+"_CombinedSS"
                        if not os.path.exists(out1):
                            os.system("mkdir " + out1)

                        os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> card_combinedSS_"+channel + "_N"+mass+"_"+_id+"_"+ vars_1[x]+"_"+year+".txt")
                        input_list.write(workspace + "/card_combinedSS_"+channel + "_N"+mass+"_"+_id+"_"+ vars_1[x]+"_"+year+".txt\n")
                               

input_list.close()

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/MCBased/run/input_combinedyears.txt","w")

print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"
print "./create-batch -n HNCombinedYears_SR12_1234_EE_MM  -l  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/MCBased/run/input_combinedyears.txt"


for c in cards:
    for channel in channels:

        for mass in masses:
            IDs=[]
            if channel == "MuMu":
                IDs=IDMu
            else:
                IDs=IDEl

            for _id in IDs:
                
                for x in range(0, len(vars_1)):


                    path1="card_combinedSS_"+channel + "_N"+mass+"_"+_id+"_"+vars_1[x]+"_2016.txt"
                    path2="card_combinedSS_"+channel + "_N"+mass+"_"+_id+"_"+vars_1[x]+"_2017.txt"
                    path3="card_combinedSS_"+channel + "_N"+mass+"_"+_id+"_"+vars_1[x]+"_2018.txt"

                    if not os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/CombinedYears/"):
                        os.system("mkdir  " + "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsShape/CombinedYears/")

                    out1=channel+"_CombinedSS_"+channel + "_N"+mass+"_"+_id+"_"+vars_1[x]+"_combinedyears.txt"
                    os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + "  Name3=" + path3 + "  &> " + out1 )
                    
                    input_list.write(workspace+"/"+out1 + "\n")
os.chdir("/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/MakeCards")

input_list.close()
#for x in lists:
 #   print x
