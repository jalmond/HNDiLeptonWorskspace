import os,ROOT
from os import listdir
from os.path import isfile,isdir, join



def ReadBins(filepath, isMuon,Bkg):


    RootFile = ROOT.TFile(filepath)
    if not RootFile:
        return -1


    SingleLepHist = "LepType/Electron"
    if isMuon:
        SingleLepHist = "LepType/Muon"

    SLHist = RootFile.Get(SingleLepHist)
    if not SLHist:
        return -1

    DiLepHist = "LepType/SSElectron"
    if isMuon:
        DiLepHist = "LepType/SSMuon"

    DLHist = RootFile.Get(DiLepHist)
    if not DLHist:
        return -1

    if isMuon:
        print (filepath + " Bin Content [Muon]: ")
    else:
        print (filepath + " Bin Content [Electron]: ")

        
    Types = [-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6]
    if Bkg == "Fake":
        Types = [-4,-3,-2,-1]
    if Bkg == "Conv":
        Types = [-6,-5,4,5,6]

        
    for x in Types:
        _slbin = SLHist.FindBin(x)
        sl =SLHist.GetBinContent(_slbin)
        _dlbin = DLHist.FindBin(x)
        dl =  DLHist.GetBinContent(_dlbin)
        if sl > 0 and dl > 0:
            print ("if(lepttype == "+str(x)+") return " + str(dl/sl)) + ";"
        else:
            print ("if(lepttype == "+str(x)+") return 0.")
        
    RootFile.Close()

            

import argparse
parser = argparse.ArgumentParser(description='option')
parser.add_argument('-s', dest='Sample', default="NULL")
parser.add_argument('-e', dest='Era', default="NULL")
parser.add_argument('-b', dest='Bkg', default="NULL")
parser.add_argument('--Muon', action='store_true')

args = parser.parse_args()


    
InPath = "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_LepIDKinVar/"
Eras = [args.Era]
DirList =  ["Seperate"+args.Bkg+"__GetRatio__"]



for Era in Eras:
    for Dir in DirList:

        File_Dir = InPath + Era + "/"+ Dir +"/"
        FileList  = [f for f in listdir(File_Dir) if isfile(join(File_Dir,f))]
        

        for f in  FileList:
            

            if not args.Sample+".root" in f:
                continue


            if not ".root" in f:
                continue
    
            if args.Muon:
                ReadBins(File_Dir+f,True,args.Bkg)
            else:
                ReadBins(File_Dir+f,False,args.Bkg)
