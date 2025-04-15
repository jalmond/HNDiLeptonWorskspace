import os

Eras = [ "2016postVFP", "2016preVFP", "2017", "2018"]
Eras = [ "2018"]

##### Add Flag if Analyzer has FLAG in run script
Flags = ["SSMultiLep"]

#######################################################################################################################################
TagDir="April25"
#######################################################################################################################################

Analyzer="HNL_ControlRegion_Plotter"
Channel = "EE"
Regions = ["HNL_HighMassNP_TwoLepton_CR","HNL_HighMassSR3_2J_TwoLepton_CR","HNL_HighMassSR3_TwoLepton_CR","HNL_HighMassSSZPeak_TwoLepton_CR","HNL_TopNP_ThreeLepton_CR","HNL_ZG_ThreeLepton_CR","HNL_ZNPMu_ThreeLepton_CR","HNL_WpWp_TwoLepton_CR1","HNL_WpWp_TwoLepton_CR2","HNL_WpWpNP_TwoLepton_CR","HNL_WpWpNP2_TwoLepton_CR","HNL_WpWpNP3_TwoLepton_CR","HNL_HighMassSR1_TwoLepton_CR","HNL_HighMassBJet_TwoLepton_CR","HNL_WZ2_ThreeLepton_CR","HNL_WZB_ThreeLepton_CR","HNL_ZZ_FourLepton_CR","HNL_ZZLoose_FourLepton_CR","HNL_WG_ThreeLepton_CR","HNL_WZ_ThreeLepton_CR"]

Regions = ["HNL_HighMassSR3_TwoLepton_CR"]

for Era in Eras:
    Year = Era
    if "2016" in Year:
        Year = "2016"
    IDs = ["HNL_ULID"]
    
    for ID in IDs:
        for Region in Regions:
            if len(Flags) == 0:
                print("_"*50)
                print("python PrintNTUP.py -e "+Era+" -r "+Region+" -i " + ID + "  -c "+Channel+" -d "+ TagDir  + " -a " +Analyzer)
                os.system("python PrintNTUP.py -e "+Era+"  -r "+Region+"   -i " + ID + "  -c "+Channel+" -d " + TagDir  + " -a " +Analyzer)

            elif Flags[0] == "":
                print("_"*50)
                print("python PrintNTUP.py -e "+Era+" -r "+Region+" -i " + ID + "  -c "+Channel+" -d "+ TagDir  + " -a " +Analyzer)
                os.system("python PrintNTUP.py -e "+Era+"  -r "+Region+"   -i " + ID + "  -c "+Channel+" -d " + TagDir  + " -a " +Analyzer)

            else:
                for Flag in Flags:
                    print("_"*50)
                    print("python PrintNTUP.py -e "+Era+" -f "+Flag + " -r "+Region+" -i " + ID + "  -c "+Channel+" -d "+ TagDir  + " -a " +Analyzer)
                    os.system("python PrintNTUP.py -e "+Era+" -f "+Flag + " -r "+Region+"   -i " + ID + "  -c "+Channel+" -d " + TagDir  + " -a " +Analyzer)
                
