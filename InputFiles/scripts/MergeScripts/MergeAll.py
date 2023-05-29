import os 

if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()


##### Flag Dir merges files into dir based on rnun flags

import argparse


parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="")
parser.add_argument('-f', dest='Flag', default="")
parser.add_argument('-e', dest='Era', default="2017")
parser.add_argument('-s', dest='Skim', default="")

parser.add_argument('--Data',action='store_true')
parser.add_argument('--Fake',action='store_true')
parser.add_argument('--Sig',action='store_true')
parser.add_argument('--CF',action='store_true')
parser.add_argument('--Conv',action='store_true')
parser.add_argument('--MC',action='store_true')
parser.add_argument('--LMC',action='store_true')
parser.add_argument('--Run2Merge',action='store_true')
parser.add_argument('--EraMerge',action='store_true')
parser.add_argument('--Bkg',action='store_true')
parser.add_argument('--Full',action='store_true')

args = parser.parse_args()

FlagDir="/"+args.Flag
era = args.Era

Analyser=args.Analyzer

MergeFake=args.Fake
MergeCF=args.CF
MergeConv=args.Conv
MergeMC=args.MC
MergeLargeMC=args.LMC
MergeBkg=args.Bkg
MergeSignal=args.Sig

MergeData=args.Data
Merge16=args.EraMerge
FullMerge=args.Run2Merge

if args.Full:
    MergeFake=True
    MergeCF=True
    MergeConv=True
    MergeMC=True
    MergeBkg=True
    MergeData=True


InputPath=os.getenv("SKFlatOutputDir")+"/"+os.getenv("SKFlatV") + "/"+Analyser+"/"
OutputPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"
SkimName=args.Skim

if not os.path.exists(OutputPath):
    os.system("mkdir " + OutputPath)

    
if not os.path.exists(OutputPath + era):
    os.system("mkdir " + OutputPath + era)
if not os.path.exists(OutputPath + era+FlagDir):
    os.system("mkdir " + OutputPath + era+FlagDir)


OutputPathEra = OutputPath + era+FlagDir
InputPathEra = InputPath + "/"+era+FlagDir

if MergeFake:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_NonPrompt.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    if FlagDir == "":
        os.system("hadd " + OutFile + "  " + InputPathEra+"/RunFake__/DATA/*")
    else:
        os.system("hadd " + OutFile + "  " + InputPathEra+"RunFake__/DATA/*")


if MergeMC:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Prompt.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    
    os.system("hadd " + OutFile + "  " + InputPathEra+"/*SkimTre*")
    os.system("cp " + InputPathEra+"/*SkimTre* " + OutputPathEra+"/" )

if MergeLargeMC:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName#+"_MC.root"
    if os.path.exists(OutFile+"_ZMC.root"):
        os.system("rm " + OutFile+"_ZMC.root")
        os.system("rm " + OutFile+"_TMC.root")
        os.system("rm " + OutFile+"_tMC.root")
        os.system("rm " + OutFile+"_SMC.root")
        os.system("rm " + OutFile+"_GMC.root")
        os.system("rm " + OutFile+"_DMC.root")
        os.system("rm " + OutFile+"_WMC.root")
        os.system("rm " + OutFile+"_W2MC.root")


    os.system("hadd " + OutFile + "_ZMC.root  " + InputPathEra+"/*HNMultiLepBDT_Z* &> log/"+args.Era+"_"+Analyser+"Zlog &")
    os.system("hadd " + OutFile + "_TMC.root  " + InputPathEra+"/*HNMultiLepBDT_T* &> log/"+args.Era+"_"+Analyser+"Tlog &")
    os.system("hadd " + OutFile + "_tMC.root  " + InputPathEra+"/*HNMultiLepBDT_t* &> log/"+args.Era+"_"+Analyser+"tlog &")
    os.system("hadd " + OutFile + "_SMC.root  " + InputPathEra+"/*HNMultiLepBDT_S* &> log/"+args.Era+"_"+Analyser+"Slog &")
    os.system("hadd " + OutFile + "_GMC.root  " + InputPathEra+"/*HNMultiLepBDT_G* &> log/"+args.Era+"_"+Analyser+"Glog &")
    os.system("hadd " + OutFile + "_DMC.root  " + InputPathEra+"/*HNMultiLepBDT_D* &> log/"+args.Era+"_"+Analyser+"Dlog &")
    os.system("hadd " + OutFile + "_WMC.root  " + InputPathEra+"/*HNMultiLepBDT_Wp* " + InputPathEra+"/*HNMultiLepBDT_WW* " + InputPathEra+"/*HNMultiLepBDT_WZ*    &> log/"+args.Era+"_"+Analyser+"Wlog &")
    os.system("hadd " + OutFile + "_W2MC.root  " + InputPathEra+"/*HNMultiLepBDT_WJ* ")


if MergeCF:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_CF.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    if FlagDir == "":
        os.system("hadd " + OutFile + "  " + InputPathEra+"/RunCF__/*")
    else:
        os.system("hadd " + OutFile + "  " + InputPathEra+"RunCF__/*")
       
if MergeConv:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Conv.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    if FlagDir == "":
        os.system("hadd " +OutFile+  "   " + InputPathEra+"/RunConv__/*")
    else:
        os.system("hadd " +OutFile+  "   " + InputPathEra+"RunConv__/*")



if MergeBkg:
    
    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Bkg.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)
        
    os.system("hadd " +OutFile+  "   " + OutputPathEra + "/"+Analyser+"_"+SkimName+"*")
    
if MergeSignal:
    os.system("python MergeScripts/MergeSignal.py -a " + Analyser + " -f " + FlagDir + " -e " + era)
    os.system("python MergeScripts/MergeSignalFull.py -a " + Analyser + " -f " + FlagDir + " -e " + era)


if MergeData:

    
    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_data.root"
        
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    os.system("hadd " +OutFile + "   " + InputPathEra+"/DATA/*")




if Merge16:
    os.system("python MergeScripts/Merge16.py  -a " + Analyser + " -f " + FlagDir )
    

if FullMerge:
    os.system("python MergeScripts/FullMerge.py  -a " + Analyser + " -f " + FlagDir )



