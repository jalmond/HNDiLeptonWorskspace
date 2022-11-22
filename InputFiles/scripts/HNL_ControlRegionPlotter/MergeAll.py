import os 


if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()


eras = ["2016preVFP", "2016postVFP", "2017", "2018"]
eras = ["2017"]
#eras = ["2018"]
paramNames = ["POGCR_UL", "HNL_UL"]
paramNames = ["HNL_UL"]

MergeData=True
MergeFake=True
MergeCF=  True
MergeConv=True
CopyMC=   True

MergeMC=False #not recommended (see below)

Analyser="HNL_ControlRegionPlotter"
InputPath=os.getenv("SKFlatOutputDir")+"/"+os.getenv("SKFlatV") + "/"+Analyser+"/"
OutputPath=os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"

if not os.path.exists(OutputPath):
    os.system("mkdir -p " + OutputPath)

for era in eras:

    if not os.path.exists(OutputPath + era):
        os.system("mkdir -p " + OutputPath + era)

if MergeFake:

    for era in eras:
        OutFile=OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_NonPrompt.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)
        
        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"//RunFake__/DATA/*") #hadd fakes


if MergeMC:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_MC.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"/*HNMu*") #hadd all MC files; not recommended

if CopyMC:

    for era in eras:

        OutFile=OutputPath + era + "/"

        os.system("cp " + InputPath + "/"+era+"/*HNMu*.root " + OutFile) #just copy all MC samples -- this is better, one can pre-define sets in PredefinedSamples.py


if MergeCF:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_CF.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " + OutFile + "  " + InputPath + "/"+era+"//RunCF__/DATA/*") #hadd CF

       
if MergeConv:

    for era in eras:

        Conv_dict = { #pre-defined WJet sample type
                     'Conv' : " "+InputPath+"/"+era+"/RunConv__/*G.root"+" "+InputPath+"/"+era+"/RunConv__/*DYJets.root", #WG + DYJets
                     'MG' : " "+InputPath+"/"+era+"/RunConv__/*G.root"+" "+InputPath+"/"+era+"/RunConv__/*DYJets.root"+" "+InputPath+"/"+era+"/RunConv__/*WJets_MadGraph.root", #WG + DYJets + WJet_LO
                     'amcatnlo' : " "+InputPath+"/"+era+"/RunConv__/*G.root"+" "+InputPath+"/"+era+"/RunConv__/*DYJets.root"+" "+InputPath+"/"+era+"/RunConv__/*WJets_amcatnlo.root",
                     'Sherpa' : " "+InputPath+"/"+era+"/RunConv__/*G.root"+" "+InputPath+"/"+era+"/RunConv__/*DYJets.root"+" "+InputPath+"/"+era+"/RunConv__/*WJets_Sherpa.root",
                     'HT' : " "+InputPath+"/"+era+"/RunConv__/*G.root"+" "+InputPath+"/"+era+"/RunConv__/*DYJets.root"+" "+InputPath+"/"+era+"/RunConv__/*WJetsToLNu_HT*.root",
                    }

        OutFiles = []

        OutFiles.append(OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_Conv.root")
        #OutFiles.append(OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_Conv_MG.root")
        #OutFiles.append(OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_Conv_amcatnlo.root")
        #OutFiles.append(OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_Conv_Sherpa.root")
        #OutFiles.append(OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_Conv_HT.root")

        for OutFile in OutFiles:

          Conv_tag = OutFile.split('_')[-1][0:-5] #'Conv' or 'MG' or 'amcatnlo' or ...

          if os.path.exists(OutFile):
            os.system("rm " + OutFile)

          os.system("hadd " +OutFile+Conv_dict[Conv_tag]) # hadd samples depending on the WJet sample tag


if MergeData:

    for era in eras:

        OutFile=OutputPath + era + "/"+Analyser+"_SkimTree_HNMultiLep_data.root"
        if os.path.exists(OutFile):
            os.system("rm " + OutFile)

        os.system("hadd " +OutFile + "   " + InputPath + "/"+era+"/DATA/*")
