import os 

EtaBins = ["BB", "EB", "EE"]
Masses  = ["100","250","500","1000","2000","10000"]
MVATypes = ["MVAIso90","MVANoIso90"]
DataTypes = [ "", " --Data "]
DataTypes = [""]

for EtaBin in EtaBins:
    for Mass in Masses:
        for MVAType in MVATypes:
            for DataType in DataTypes:

                os.system("python  RunMVAOpt.py  -a OptElectronIPBATCH -m  " + Mass + "  -c Electron -v " + MVAType+ "  -r "+EtaBin+" -B SR1"+DataType)
                os.system("python  RunMVAOpt.py  -a OptElectronIPBATCH -m  " + Mass + "  -c Electron -v " + MVAType+ "   -r "+EtaBin+" -B SR2"+DataType)
                os.system("python  RunMVAOpt.py  -a OptElectronIPBATCH -m  " + Mass + "  -c Electron -v " + MVAType+ "  -r "+EtaBin+DataType)

