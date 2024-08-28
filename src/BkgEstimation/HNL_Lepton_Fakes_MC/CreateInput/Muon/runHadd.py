import os 

def GetFullEra(_era):
    if _era == "2016a":
        return "2016preVFP"
    if _era == "2016b":
        return "2016postVFP"
    return _era

Eras = ["2016a", "2016b","2017","2018"]
os.system("rm *.root")
os.system("rm *~")
os.system("root -l -q -b MakeMVA_FR_FileLL.C")

for Era in Eras:
    os.system("hadd MC_"+Era+"_Muon_FR.root FR_MC_Mu_*"+Era+"_*")
    print("Merging .... MC_"+Era+"_Muon_FR.root")
    os.system("rm FR_MC_Mu_*"+Era+"_*")

os.system("ls -lth ")
    
for Era in Eras:
    FullEra=GetFullEra(Era)
    
    PATH_SK="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+FullEra+"/FakeRate/MCFR/MuFR/"
    
    command2="mv MC_"+Era+"_Muon_FR.root " + PATH_SK + "/MC_"+Era+"_Muon_FR.root"                                                                                                  
    print(command2)
    os.system("rm " + PATH_SK + "*~")
    os.system("rm " + PATH_SK + "*.root")
    os.system(command2)

    os.system("ls -lth "+PATH_SK)

