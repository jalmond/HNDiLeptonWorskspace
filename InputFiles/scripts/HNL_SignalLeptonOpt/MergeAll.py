import os 

if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()


##### Flag Dir merges files into dir based on rnun flags

FlagDir="/RunEE__RunHighPt__"


eras = ["2017"]

MergeFake=False
MergeCF=False
MergeConv=False
MergeMC=False
MergeBkg=False
MergeData=True


Analyser="HNL_SignalLeptonOpt"

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

        os.system("python MergeSignal.py")
        os.system("python MergeSignalFull.py")



MergeData=True
if MergeData:

    for era in eras:

        OutFile=OutputPathEra + "/"+Analyser+"_"+SkimName+"_data.root"
        
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile + "   " + InputPathEra+"/DATA/*")


    os.system("python MergeSignal.py")
    os.system("python MergeSignalFull.py")
