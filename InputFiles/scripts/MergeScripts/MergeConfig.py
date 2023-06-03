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
parser.add_argument('--FakeMC',action='store_true')
parser.add_argument('--Sig',action='store_true')
parser.add_argument('--CF',action='store_true')
parser.add_argument('--Conv',action='store_true')
parser.add_argument('--Prompt',action='store_true')
parser.add_argument('--MC',action='store_true')
parser.add_argument('--Run2Merge',action='store_true')
parser.add_argument('--EraMerge',action='store_true')
parser.add_argument('--Bkg',action='store_true')
parser.add_argument('--CopyMC',action='store_true')
parser.add_argument('--Full',action='store_true')

args = parser.parse_args()

FlagDir="/"+args.Flag
era = args.Era

Analyser=args.Analyzer

MergeFake=args.Fake
MergeFakeMC=args.FakeMC
MergeCF=args.CF
MergeConv=args.Conv
MergePrompt=args.Prompt
MergeMC=args.MC
MergeBkg=args.Bkg
MergeSignal=args.Sig
CopyMC=args.CopyMC

MergeData=args.Data
Merge16=args.EraMerge
FullMerge=args.Run2Merge

if args.Full:
    MergeFake=True
    MergeCF=True
    MergeConv=True
    MergePrompt=True
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

if MergeFakeMC:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_NonPrompt.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    if FlagDir == "":
        os.system("hadd " +OutFile+  "   " + InputPathEra+"/RunFake__/*")
    else:
        os.system("hadd " +OutFile+  "   " + InputPathEra+"RunFake__/*")



if MergeFake:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_NonPrompt.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)

    if FlagDir == "":
        os.system("hadd " + OutFile + "  " + InputPathEra+"/RunFake__/DATA/*")
    else:
        os.system("hadd " + OutFile + "  " + InputPathEra+"RunFake__/DATA/*")


if MergePrompt:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Prompt.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)


    if FlagDir == "":
        os.system("hadd " + OutFile + "  " + InputPathEra+"/RunPrompt__/*SkimTre*")
        if CopyMC:
            os.system("cp " + InputPathEra+"/RunPrompt__/*SkimTre* " + OutputPathEra+"/" )

    else:
        os.system("hadd " + OutFile + "  " + InputPathEra+"RunPrompt__/*SkimTre*")
        if CopyMC:
            os.system("cp " + InputPathEra+"RunPrompt__/*SkimTre* " + OutputPathEra+"/" )


if MergeMC:

    OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_MC.root"
    if os.path.exists(OutFile):
        os.system("rm " + OutFile)


    os.system("hadd " + OutFile + "  " + InputPathEra+"/*SkimTre*")
    if CopyMC:
        os.system("cp " + InputPathEra+"RunPrompt__/*SkimTre* " + OutputPathEra+"/" )


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
        
    if os.path.exists(OutputPathEra + "/"+Analyser+"_"+SkimName +"_CF.root"):
        os.system("hadd " +OutFile+  "   " + OutputPathEra + "/"+Analyser+"_"+SkimName+"*Prompt* "  + OutputPathEra + "/"+Analyser+"_"+SkimName+"*CF* " + OutputPathEra + "/"+Analyser+"_"+SkimName+"*Conv* ")
    else:
        os.system("hadd " +OutFile+  "   " + OutputPathEra + "/"+Analyser+"_"+SkimName+"*Prompt* "  + OutputPathEra + "/"+Analyser+"_"+SkimName+"*Conv* ")

if MergeSignal:
    os.system("python MergeScripts/RenameSig.py -a " + Analyser + " -f " + FlagDir + " -e " + era)
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



