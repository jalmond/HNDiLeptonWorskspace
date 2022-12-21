import os,ROOT,sys

WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']

sys.path.insert(1, WORKING_DIR+'/python')
from os import listdir
from os.path import isfile,isdir, join

import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)

#if not os.path.exists('/tmp/ssh-jalmond@lxplus.cern.ch'):

def getall(d, basepath="/"):

    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def PrintHist(HistName,InDir,PrintBins):

    f = ROOT.TFile(InDir)
    hist=f.Get(HistName)
    if hist:
        print ( ("%s : Intergal %f") %(InDir, hist.Integral()))
        if PrintBins:
            for x in range(1, hist.GetXaxis().GetNbins()+1):
                if hist.GetBinContent(x) != 0:
                    print ( ("Bin [%f - %f], integral=%f") %(hist.GetXaxis().GetBinLowEdge(x),hist.GetXaxis().GetBinUpEdge(x),hist.GetBinContent(x)))
    else:
        print ( ("%s : Intergal %s") %(InDir, "-999"))

    f.Close()


def PrintHistsInFile(InDir):

    f = ROOT.TFile(InDir)
        
    HistNames=[]
    
    for k, o in getall(f):
        print k
    f.Close()

def CheckIndividualInput(_s, _sstring):
    if _s == "NULL":
        print _sstring+ " not set...."
        return False
    else:
        return True

def CheckInput(sEra,sInput,sAnalyser,sHistName,sargs):

    if len(sInput) ==0:
        print "sInput has 0 enters"
        return False

    if not CheckIndividualInput(sHistName,"HistName"):
        if os.path.exists(sInput[0]):
            PrintHistsInFile(sInput[0])
        return False
    
    if os.path.exists(sInput[0]):
        return True

    if not CheckIndividualInput(sEra,"Era"):
        return False
    if not CheckIndividualInput(sInput[0],"Input"):
        return False
    if not CheckIndividualInput(sAnalyser,"Analyser"):
        return False


    return True

def  GetFromConfig(slines, tag,pargs):
    
    tagged_line=""

    vLines =[]
    for line in slines:
        if tag in line:
            
            if line.split()[0] == "Input":
                vLines.append( line.split()[2])
            else:
                tagged_line = line.split()[1]
                break
    if len(vLines) > 0:
        return vLines
                
    if tagged_line == "":
        if tag == "Era":
            tagged_line = args.Era
        if tag == "Input":
            tagged_line = args.Input
        if tag == "HistName":
            tagged_line = args.HistName

        if tag == "Analyser":
            tagged_line = args.Analyser


    return tagged_line



## Arguments

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-e', dest='Era', type=str, default='NULL')
parser.add_argument('-a', dest='Analyser', type=str, default='NULL')
parser.add_argument('-hist', dest='HistName', type=str, default='NULL')
parser.add_argument('-dir', dest='Input', type=str, default='NULL')
parser.add_argument('-c', dest='Config', type=str, default='NULL')
parser.add_argument('--Bins', action='store_true')

parser.add_argument('--debug',action='store_true')
parser.add_argument('--lxcopy', action='store_true')
parser.add_argument('--PrintHists', action='store_true')
parser.add_argument('--List', action='store_true')


args = parser.parse_args()

Analyser='HNL_Validation'


if args.lxcopy:
    check_lxplus_connection()

Era=""
Input=[]
ListInput=[]
Analyzer=""
HistName=""

if args.Config != "NULL":
    
    with open(args.Config) as f:
        lines = f.readlines()
        Era = GetFromConfig(lines,"Era",args)
        Input = GetFromConfig(lines,"Input",args)
        Analyser = GetFromConfig(lines,"Analyser",args)
        HistName = GetFromConfig(lines,"HistName",args)
    
    print (("HistName = %s ") %(HistName))
else:
    
    Era = args.Era
    Input = [args.Input]
    Analyser = args.Analyser
    HistName = args.HistName

if args.List:
    if len(Input) > 0:
        if ".root" in Input[0]:
            PrintHistsInFile(Input[0])
        else:
            print "Dir is not root file.... list dir and update "
            in_path  = [f for f in listdir(Input[0]) if isfile(join(Input[0],f))]
            for files in in_path:
                print Input[0]+"/"+files
            
    exit()


for _Input in Input:

    if ".root" in _Input:
        ListInput.append(_Input)

    else:
        print _Input
        in_path  = [f for f in listdir(_Input) if isfile(join(_Input,f))]
        for files in in_path:
            if ".root" in files:
                ListInput.append(_Input+"/"+files)



if not CheckInput(Era,Input,Analyser,HistName,args):
    exit()

for x in ListInput:

    if ".root" in x:
        print (("Looking up hist %s in file %s") % (HistName, x))
    else:
        print("Error in input")
        exit()

for x in ListInput:
    PrintHist(HistName, x,args.Bins)

