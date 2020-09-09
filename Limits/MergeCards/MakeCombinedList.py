import os

SRs = ["Bin1","Bin2","Bin3","Bin4"]
masses = ["100" ,"200","300","400","500","600","700","800","900","1000","1100","1200","1500"]
channels = ["MuMu", "EE"]
cards = ["_combined","_VBF",""]
years = ["2016", "2017","2018"]

lists =[]

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/input_sr1to4.txt","w")
print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"
print "./create-batch -n HNSR1234_EE_MM  -l /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/input_sr1to4.txt"
for year in years:
    for c in cards:
        for channel in channels:
            #lists.append("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/"+  year + "/list"+c+"_"+channel+"_ss.txt")
            #lists.append("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/"+  year + "/list"+c+"_"+channel+"_osss.txt")
            #ss_list =  open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/"+  year + "/list"+c+"_"+channel+"_ss.txt","w")
            #osss_list =  open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/"+  year + "/list"+c+"_"+channel+"_osss.txt","w")
            for mass in masses:
                path1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/"+ year + "/" +channel+"_Bin1/card_"+channel+"_Bin1_N"+mass+c+".txt"
                path2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/" + year  + "/" +channel+"_Bin2/card_"+channel+"_Bin2_N"+mass+c+".txt"
                path3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/"+ year  + "/"+ channel+"_Bin3/card_"+channel+"_Bin3_N"+mass+c+".txt"
                path4="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/"+ year  + "/"+ channel+"_Bin4/card_"+channel+"_Bin4_N"+mass+c+".txt"
                
                out1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/" + year + "/"+channel+"_CombinedSS"
                out2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/"+ year + "/"+channel+"_CombinedOS_SS"
                if not os.path.exists(out1):
                    os.system("mkdir " + out1)
                if not os.path.exists(out2):
                    os.system("mkdir " + out2)
                os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + " &> " + out1 + "/card_combinedSS_"+channel + "_N"+mass+c+"_"+year+".txt")
                os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 +  "    Name3=" + path3 + "    Name4=" + path4 +" &> " + out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+year+".txt")
                input_list.write(out1 + "/card_combinedSS_"+channel + "_N"+mass+c+"_"+year+".txt\n")
                input_list.write(out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+"_"+year+".txt\n")
                #print out1 + "/card_combinedSS_"+channel + "_N"+mass+c+".txt"
                #print out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+".txt"
                
                
                #ss_list.write("combine -M AsymptoticLimits " + out1 + "/card_combinedSS_"+channel + "_N"+mass+c+".txt -n HNCombinedBinsSS_"+channel+"_"+c+"_N"+mass+" --run blind  &> out/log_"+year+"card_combinedSS_"+channel + "_N"+mass+c +"\n")
                #osss_list.write("combine -M AsymptoticLimits " + out2 + "/card_combinedOS_SS_"+channel + "_N"+mass+c+".txt  -n HNCombinedBinsOS_SS_"+channel+"_"+c+"_N"+mass+" --run blind  &> out/log_"+year+"card_combinedSS_"+channel + "_N"+mass+c +"\n")

            #ss_list.close()
            #osss_list.close()
input_list.close()

input_list = open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/input_combinedyears.txt","w")

print "cd /data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"
print "./create-batch -n HNCombinedYears_SR12_1234_EE_MM  -l  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/input_combinedyears.txt"


for c in cards:
    for channel in channels:
        #ss_list =  open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/AllYears/AllYears_list"+c+"_"+channel+"ss.sh","w")
        #osss_list =  open("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/AllYears/AllYears_list"+c+"_"+channel+"osss.sh","w")
        #lists.append("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/AllYears/list"+c+"_"+channel+"ss.sh")
        #lists.append("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/run/AllYears/list"+c+"_"+channel+"osss.sh")
        for mass in masses:

            path1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2016/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+".txt"
            path2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2017/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+".txt"
            path3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2018/"+channel+"_CombinedSS/card_combinedSS_"+channel + "_N"+mass+c+".txt"

            ospath1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2016/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+".txt"
            ospath2="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2017/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+".txt"
            ospath3="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/2018/"+channel+"_CombinedOS_SS/card_combinedOS_SS_"+channel + "_N"+mass+c+".txt"

            
            if not os.path.exists("/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/AllYears/"):
                os.system("mkdir  " + "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/AllYears/")

            out1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/AllYears/"+channel+"_CombinedSS_"+channel + "_N"+mass+c+"allyears.txt"
            osout1="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/DataCardsCutCount/AllYears/"+channel+"_CombinedOS_SS_"+channel + "_N"+mass+c+"allyears.txt"
            
            #ss_list.write("combine -M AsymptoticLimits " + out1 + " -n HNCombinedYearsOS_SS_"+channel+"_"+c+"_N"+mass+" --run blind  &> out/log_combinedyears_"+channel+"_CombinedSS_"+channel + "_N"+mass+c + "\n")
            #osss_list.write("combine -M AsymptoticLimits " + osout1 + " -n HNCombinedYearsOS_SS_"+channel+"_"+c+"_N"+mass+" --run blind &> out/log_combinedyears_"+channel+"_CombinedOS_SS_"+channel + "_N"+mass+c +"  \n")

            os.system("combineCards.py  Name1="+path1+ "    Name2=" + path2 + "  Name3=" + path3 + "  &> " + out1 )
            os.system("combineCards.py  Name1="+ospath1+ "    Name2=" + ospath2 + "  Name3=" + ospath3 + "  &> " + osout1 )
            #print out1
            #print osout1

            input_list.write(out1 + "\n")
            input_list.write(osout1 + "\n")
        #ss_list.close()
        #osss_list.close()

input_list.close()
#for x in lists:
 #   print x
