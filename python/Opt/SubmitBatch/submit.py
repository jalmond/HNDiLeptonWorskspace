import os 

EtaBins = ["BB", "EB", "EE"]
IsoBins = ["020","015","014","013","012","011","010","0095","009","0085","008","0075","007","0065","006","0055","005"]
IsoTypes = ["MiniIso","Iso"]
MVATypes = ["mva","Isomva"]
Masses  = ["100","250","500","1000","2000","10000"]
DataTypes = ["", " --Data "]

Test=False
if Test:
    EtaBins = ["BB"]
    Masses  = ["100"]
    IsoTypes = ["Iso"]
    MVATypes = ["mva"]
    IsoBins = ["0085"]

SR1Mass = ["500","1000","2000","10000"]

for EtaBin in EtaBins:
    for  IsoBin in IsoBins:
        for Mass in Masses:
            for IsoType in IsoTypes:
                for MVAType in MVATypes:
                    for DataType in DataTypes:

                        #os.system("python   RunMVAOpt.py  -a OptMVAElectronIsoBATCH -e 2017 -m " + Mass + "  -c Electron -r "+EtaBin+" -I "+IsoBin + " -v  " + MVAType + " -MI "+ IsoType + " -CC CC_ "+DataType)
                        os.system("python   RunMVAOpt.py  -a OptMVAElectronIsoBATCH -e 2017 -m " + Mass + "  -c Electron -r "+EtaBin+" -I "+IsoBin + " -v  " + MVAType + " -MI "+ IsoType +DataType)
                        #if  Mass in SR1Mass:
                            #os.system("python   RunMVAOpt.py  -a OptMVAElectronIsoBATCH -e 2017 -m " + Mass + "  -c Electron -r "+EtaBin+" -I "+IsoBin + " -v  " + MVAType + " -MI "+ IsoType + " -CC CC_ -B SR1 "+DataType)
                        os.system("python   RunMVAOpt.py  -a OptMVAElectronIsoBATCH -e 2017 -m " + Mass + "  -c Electron -r "+EtaBin+" -I "+IsoBin + " -v  " + MVAType + " -MI "+ IsoType + " -CC CC_ -B SR2 "+DataType)

