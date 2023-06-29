import os,sys,ROOT
import argparse

#sys.path.insert(1, WORKING_DIR+'/python')
from os import listdir
from os.path import isfile,isdir, join

def AbstractNEvents(FilePath):

    _file = ROOT.TFile(FilePath)
    if not _file:
        print "Missing " + FilePath
        exit()
    _hist=_file.Get("NEvents")
    return _hist.Integral()

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-i', dest='Input', type=str, default='NULL')
parser.add_argument('-s', dest='Skim', type=str, default='NULL')
parser.add_argument('-e', dest='Era', type=str, default='NULL')

args = parser.parse_args()

Path= args.Input 
SkimName= args.Skim
Era=args.Era

SampleListPath="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/data/Run2UltraLegacy_v3/"+Era+"/Sample/ForSNU/"
list_file_path  = [f for f in listdir(SampleListPath) if isfile(join(SampleListPath,f))]
SkimFiles=[]
for x in list_file_path:
    if SkimName in x:
        SkimFileName=x
        SkimFileName=SkimFileName.replace(".txt","")
        SkimFiles.append(SkimFileName)

file_path  = [f for f in listdir(Path) if isfile(join(Path,f))]

FileList=[]
for x in file_path:
    if SkimName in x:
        FileList.append(x)

DATANames = ["DoubleEG", "SingleMu", "SingleE","Muon","EGamma"]

for SkimFile in SkimFiles:

    if "/DATA/" in Path:

        isDATA=False
        for x in DATANames:
            if x in SkimFile:
                isDATA=True
        if not isDATA:
            continue

    else:

        isDATA=False
        for x in DATANames:
            if x in SkimFile:
                isDATA=True
        if isDATA:
            continue

    

    
    SkimFound=False
    for x in FileList:

        if x == "SumEvents_"+SkimFile+".root":
            SkimFound=True
            
            File1=Path+x
            File2=File1
            if "Type" in File1:
                File2=File2.replace(SkimName+"_","")
            elif "DileptonBDT_MuonEG" in File1:
                continue
            
            else:
                File2=File2.replace("BDT","")

            Value1=AbstractNEvents(File1)
            Value2=AbstractNEvents(File2)
            print ((x + "{0} RatioBDT {1} ").format(" "*(75-len(x)),Value2/Value1))
            if Value1 != Value2:
                print ("ERROR in skim number")
                exit()
    if not SkimFound:
        print ("samples not processed " +SkimFile)

