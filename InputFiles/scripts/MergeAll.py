import os 

if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()


##### Flag Dir merges files into dir based on rnun flags


parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="HNL_SignalLeptonOpt")
parser.add_argument('-f', dest='Flag', default="/RunEE__RunHighPt__")
parser.add_argument('-e', dest='Era', default="2017")

parser.add_argument('--Data',action='store_true')
parser.add_argument('--Fake',action='store_true')
parser.add_argument('--CF',action='store_true')
parser.add_argument('--Conv',action='store_true')
parser.add_argument('--MC',action='store_true')
parser.add_argument('--Full',action='store_true')
args = parser.parse_args()

FlagDir=args.Flag
eras = [args.Era]
if args.Era == "Run2":
    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

Analyser=args.Analyzer

MergeFake=args.Fake
MergeCF=args.CF
MergeConv=args.Conv
MergeMC=args.MC
MergeBkg=False
MergeData=args.Data

if args.Full:
    MergeFake=True
    MergeCF=True
    MergeConv=True
    MergeMC=True
    MergeBkg=True
    MergeData=True


InputPath=os.getenv("SKFlatOutputDir")+"/"+os.getenv("SKFlatV") + "/"+Analyser+"/"
OutputPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"
SkimName="SkimTree_HNMultiLep"

if not os.path.exists(OutputPath):
    os.system("mkdir " + OutputPath)

for era in eras:

    if not os.path.exists(OutputPath + era):
        os.system("mkdir " + OutputPath + era)
    if not os.path.exists(OutputPath + era+FlagDir):
        os.system("mkdir " + OutputPath + era+FlagDir)


OutputPathEra = OutputPath + era+FlagDir
InputPathEra = InputPath + "/"+era+FlagDir

if MergeFake:

    for era in eras:
        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_NonPrompt.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)
        os.system("hadd " + OutFile + "  " + InputPathEra+"//RunFake__/DATA/*")

if MergeMC:

    for era in eras:
        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_MC.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPathEra+"/*HNMu*")


if MergeCF:

    for era in eras:
        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_CF.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPathEra+"//RunCF__/*")

       
if MergeConv:

    for era in eras:

        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Conv.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile+  "   " + InputPathEra+"//RunConv__/*")



if MergeBkg:
    
    for era in eras:

        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_Bkg.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile+  "   " + OutputPathEra + "/"+Analyser+"_"+SkimName+"*")

        os.system("python MergeSignal.py -a " + Analyser + " -f " + FlagDir + " -e " + era)
        os.system("python MergeSignalFull.py -a " + Analyser + " -f " + FlagDir + " -e " + era)


if MergeData:

    for era in eras:

        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_data.root"
        
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile + "   " + InputPathEra+"/DATA/*")


    os.system("python MergeSignal.py -a " + Analyser + " -f " + FlagDir + " -e " + era)
    os.system("python MergeSignalFull.py -a " + Analyser + " -f " + FlagDir + " -e " + era)
