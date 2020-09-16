import os

SRs = ["SR1","SR2"]
masses = ["100" ,"125","200","250","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500"]
channels = ["MuMu", "EE"]
cards = ["_combined"]
years = ["2016", "2017","2018"]

lists =[]

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/run/input_sr1to4.txt","w")

print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"

print "./create-batch -n HN_SRComb12_EE_MM  -l /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/run/input_sr1to4.txt"
print "./create-batch -n HN_SR1_2_3_4_EE_MM  -l /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/run/AllCards_SR1_SR2_SR3_SR4.txt"
#card_2018_EE_SR2_N1500_combined_HNTight2016.txt
IDMu = ["POGTightPFIsoVeryTight","HNTight2016"]
IDEl = ["passTightID","HNTight2016","passTightID_noccb","passTightID_nocc"]

for year in years:
    for c in cards:
        for channel in channels:
            IDs=[]
            if channel == "MuMu":
                IDs= IDMu
            else:
                IDs = IDEl
            for _id in IDs:
                
                for mass in masses:
                    path1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/"+ year + "/" +channel+"_SR1/card_"+year+"_"+channel+"_SR1_N"+mass+c+"_"+_id+".txt"
                    path2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/" + year  + "/" +channel+"_SR2/card_"+year+"_"+channel+"_SR2_N"+mass+c+"_"+_id+".txt"
                    #path3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/"+ year  + "/"+ channel+"_SR3/card_"+year+"_"+channel+"_SR3_N"+mass+c+"_"+_id+".txt"

                    #path4="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/"+ year  + "/"+ channel+"_SR4/card_"+year+"_"+channel+"_SR4_N"+mass+c+"_"+_id+".txt"
                
                    out1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/" + year + "/"+channel+"_CombinedSS"
                    #out2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/"+ year + "/"+channel+"_CombinedOS_SS"
                    if not os.path.exists(out1):
                        os.system("mkdir " + out1)
                    #if not os.path.exists(out2):
                    #    os.system("mkdir " + out2)
                    os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> " + out1 + "/card_combinedSS_"+channel + "_N"+mass+c+"_"+year+"_"+_id+".txt")
                    #os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 +  "    Name3=" + path3 + "    Name4=" + path4 +" &> " + out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+year+"_"+_id+".txt")
                    input_list.write(out1 + "/card_combinedSS_"+channel + "_N"+mass+c+"_"+year+"_"+_id+".txt\n")
                    #input_list.write(out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+year+"_"+_id+".txt\n")

input_list.close()

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/run/input_combinedyears.txt","w")

print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"
print "./create-batch -n HNCombinedYears_SR12_EE_MM  -l  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/run/input_combinedyears.txt"


for c in cards:
    for channel in channels:

        IDs=[]
        if channel == "MuMu":
            IDs= IDMu
        else:
            IDs = IDEl
        for _id in IDs:

            for mass in masses:

                path1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2016/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+"_2016_"+_id+".txt"
                path2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2017/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+"_2017_"+_id+".txt"
                path3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2018/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+"_2018_"+_id+".txt"

                #ospath1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2016/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+_id+".txt"
                #ospath2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2017/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+_id+".txt"
                #ospath3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/2018/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+_id+".txt"

                
                if not os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/CombinedYears/"):
                    os.system("mkdir  " + "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/CombinedYears/")
                    
                out1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/CombinedYears/"+channel+"_CombinedSS_"+channel + "_N"+mass+c+"allyears_"+_id+".txt"
                #osout1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/MCBased/CombinedYears/"+channel+"_CombinedOS_SS_"+channel + "_N"+mass+c+"allyears_"+_id+".txt"
                
                os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + "  Name3=" + path3 + "  &> " + out1 )
                #os.system("combineCards.py  Name1="+ospath1+ "    Name2=" + ospath2 + "  Name3=" + ospath3 + "  &> " + osout1 )

                input_list.write(out1 + "\n")
                #input_list.write(osout1 + "\n")
        #ss_list.close()
        #osss_list.close()

input_list.close()
#for x in lists:
 #   print x
