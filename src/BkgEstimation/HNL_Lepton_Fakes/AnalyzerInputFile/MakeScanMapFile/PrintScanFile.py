import os 

Eras = ["2016a","2016b","2017","2018"]

IDs = ["HNL_ULID_FO_v0", 
       "HNL_ULID_FO_v1_a",
       "HNL_ULID_FO_v1_b",
       "HNL_ULID_FO_v1_c",
       "HNL_ULID_FO_v2_a",
       "HNL_ULID_FO_v2_b",
       "HNL_ULID_FO_v2_c",
       "HNL_ULID_FO_v3_a",
       "HNL_ULID_FO_v3_b",
       "HNL_ULID_FO_v3_c",
       "HNL_ULID_FO_v4_a",
       "HNL_ULID_FO_v4_b",
       "HNL_ULID_FO_v4_c",
       "HNL_ULID_FO_v5_a",
       "HNL_ULID_FO_v5_b",
       "HNL_ULID_FO_v5_c",
       "HNL_ULID_FO_v6_a",
       "HNL_ULID_FO_v6_b",
       "HNL_ULID_FO_v6_c",
       "HNL_ULID_FO_v7_a",
       "HNL_ULID_FO_v7_b",
       "HNL_ULID_FO_v7_c",
       "HNL_ULID_FO_v8_a",
       "HNL_ULID_FO_v8_b",
       "HNL_ULID_FO_v8_c",
       "HNL_ULID_FO_v9_a",
       "HNL_ULID_FO_v9_b",
       "HNL_ULID_FO_v9_c"]

AJPts = ["AJ25","AJ30","AJ40"]
PtVars = ["Pt","PtCorr","PtParton"]
LepFlavours = ["Muon","Electron"]
Version="v4"


for Era in Eras:
    for LepFlavour in LepFlavours:
        OutPutFileName ="scan_histmap_"+LepFlavour+"_"+Era+".txt"
        scanfile = open(OutPutFileName, "w") 

        for ID in IDs:
            for PtVar in PtVars:
                for AJs in AJPts:
                    InFile = "FR_Mu_"+Era+"_HNL_ULID_"+PtVar+"_"+Version+".root"
                    if LepFlavour == "Electron":
                        InFile = "FR_EGamma_"+Era+"_HNL_ULID_"+PtVar+"_"+Version+".root"

                    pteta = "pt_eta"
                    if PtVar == "PtCorr":
                        pteta="ptcorr_eta"
                    if PtVar == "PtParton":
                        pteta="ptparton_eta"
                    Year = Era
                    if "2016" in Era:
                        Year = "2016"
                    print "FakeRate"+" "*5 + "HNL_ULID_"+Year+" "*5 + pteta + " "*(15-len(pteta)) + ID+"_"+AJs + " "*5+ InFile
                    scanfile.write("FakeRate"+" "*5 + "HNL_ULID_"+Year+" "*5 + pteta + " "*(15-len(pteta)) + ID+"_"+AJs + " "*5+ InFile+'\n')
    scanfile.close()
