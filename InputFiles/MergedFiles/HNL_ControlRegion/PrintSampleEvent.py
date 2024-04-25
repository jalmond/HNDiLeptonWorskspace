import os

Eras = [ "2016postVFP", "2016preVFP", "2017", "2018", "Run2"]
Flags = ["ScanFakes_Inclusive", "ScanFakes_Barrel","ScanFakes_Endcap"]
Flags = ["ScanFakes_Inclusive"]

#######################################################################################################################################
TagDir="April20"
#######################################################################################################################################


IDs = [   "HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v1_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v1_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v1_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v2_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v2_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v2_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v3_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v3_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v3_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v4_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v4_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v4_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v5_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v5_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v5_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v6_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v6_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v6_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v7_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v7_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v7_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v8_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v8_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v8_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v9_a_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v9_b_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v9_c_Standard_PtParton_AJ30",
       "HNL_ULID_HNL_ULID_FO_v0_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v1_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v1_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v1_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v2_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v2_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v2_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v3_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v3_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v3_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v4_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v4_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v4_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v5_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v5_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v5_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v6_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v6_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v6_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v7_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v7_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v7_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v8_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v8_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v8_c_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v9_a_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v9_b_Standard_PtParton_AJ40",
       "HNL_ULID_HNL_ULID_FO_v9_c_Standard_PtParton_AJ40"]


Regions = ["HNL_SSPresel_TwoLepton", "HNL_HighMassNP_TwoLepton_CR","HNL_HighMassBJet_TwoLepton_CR" ,"HNL_HighMassSR3_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassCR2_TwoLepton_CR"]
for Era in Eras:
    for Flag in Flags:
        for ID in IDs:
            for Region in Regions:
                print("_"*50)
                print("python PrintNTUPBinned.py -e "+Era+" -f "+Flag + " -r "+Region+" -i " + ID + "  -c MuMu -d YieldSummary/"+ TagDir  )
                os.system("python PrintNTUPBinned.py -e "+Era+" -f "+Flag + " -r "+Region+"   -i " + ID + "  -c MuMu -d YieldSummary/" + TagDir )
