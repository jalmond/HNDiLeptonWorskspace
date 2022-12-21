import os 


if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()


eras = ["2016preVFP", "2016postVFP", "2017" , "2018"]

eras = [  "2017"]

MergeFake=False
MergeCF=False
MergeConv=False
MergeMC=False
MergeBkg=False

Analyser="HNL_SignalRegionOpt"
InputPath=os.getenv("SKFlatOutputDir")+"/"+os.getenv("SKFlatV") + "/"+Analyser+"/"
OutputPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"
SkimName="SkimTree_HNMultiLep"
if not os.path.exists(OutputPath):
    os.system("mkdir " + OutputPath)

for era in eras:

    if not os.path.exists(OutputPath + era):
        os.system("mkdir " + OutputPath + era)

if MergeFake:

    for era in eras:
        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_NonPrompt.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)
        
        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"//RunFake__/DATA/*")


if MergeMC:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_MC.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"/*HNMu*")



if MergeCF:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_CF.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"//RunCF__/*")

       
if MergeConv:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_Conv.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile+  "   " + InputPath + "/"+era+"//RunConv__/*")



if MergeBkg:
    
    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_Bkg.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile+  "   " + OutputPath + era + "/"+Analyser+"_"+SkimName+"*")

    os.system("python MergeSignal.py")
    #os.system("python MergeSignal16.py")
    #os.system("python Merge16.py")
    os.system("python MergeSignalFull.py")



MergeData=True
if MergeData:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_"+SkimName+"_data.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile + "   " + InputPath + "/"+era+"/DATA/*")
        
    os.system("python MergeSignal.py")
    os.system("python MergeSignalFull.py")
