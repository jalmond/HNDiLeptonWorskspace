import os,ROOT,sys
import ctypes,math


WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']

sys.path.insert(1, WORKING_DIR+'/python')
from os import listdir
from os.path import isfile,isdir, join

import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)


def GetListFromFile(listpath):
    
    if not os.path.exists(listpath):
        print("File " + listpath + " MISSING ")
        exit()

    List = []
    read_list = open(listpath, "r")
    for line in read_list:
        sline = line
        if len(sline.split()) == 0:
            break
        
        sline_clipped = sline.split()[0]
        List.append(sline_clipped)
    read_list.close()
    return List

def GetHistError(HistName,InDir, Uncert):

    f = ROOT.TFile(InDir)
    hist=f.Get(HistName)
    if not hist:
        print("Hist does not exist " + str(InDir) + " " + str(HistName))
        print("run python HistPrinter.py -input " + str(InDir))
        return 0

    data_integral=hist.Integral()
    data_error  = ctypes.c_double(0.)
    integral = hist.IntegralAndError(0,hist.GetNbinsX(),data_error,"");

    err = data_error.value

    if Uncert > 0:
        err= math.sqrt(err*err + data_integral*data_integral*Uncert*Uncert)

    f.Close()

    return err
    
        

def MakeDir(path_dir):
    if not os.path.exists(path_dir):
        os.system("mkdir " + path_dir)

def GetHistIntegral(HistName,InDir):

    
    f = ROOT.TFile(InDir)
    hist=f.Get(HistName)
    Integral = 0
    if hist:
        Integral = hist.Integral()
    
    f.Close()

    return Integral




parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-e', dest='Era', type=str, default='NULL')
parser.add_argument('-f', dest='Flag', type=str, default='')
parser.add_argument('-a', dest='Analyser', type=str, default='NULL')
parser.add_argument('-hist', dest='HistName', type=str, default='NULL')
parser.add_argument('-input', dest='Input', type=str, default='NULL')
parser.add_argument('-r', dest='Region', type=str, default='NULL')
parser.add_argument('-i', dest='ID', type=str, default='NULL')
parser.add_argument('-c', dest='Channel', type=str, default='NULL')
parser.add_argument('-p', dest='PlotterTag', type=str, default='NULL')
parser.add_argument('-l', dest='List', type=str, default='NULL')
parser.add_argument('-d', dest='DateDir', type=str, default='NULL')
parser.add_argument('--debug',action='store_true')



args = parser.parse_args()

Analyser='HNL_ControlRegion_Plotter'
Region = args.Region
DateDir=args.DateDir

DataInt = 0
PromptInt = 0
NonPromptInt = 0
ConvInt = 0
CFInt = 0

FilePath="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateDir+"/"

DataPath = FilePath + args.Era + "/"+ args.Flag + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_data.root"
NonPromptPath = FilePath + args.Era + "/"+ args.Flag + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_NonPrompt.root"
CFPath = FilePath + args.Era + "/"+ args.Flag + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_CF.root"

HistName = "/"+Region+"/"+args.ID+"/"+args.Channel+"/NObj/N_Mu"

SSList="BkgLists/"+args.List+".txt"
PromptList = GetListFromFile(SSList)
PromptDir = "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/"+args.Era+"/RunPrompt__/"
VPromptInt = []
VPromptErr = []
TotalPrompt =0
TotalErrPrompt=0
for x in PromptList:
    PRVal = GetHistIntegral(HistName, PromptDir + "/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+x+".root")
    TotalPrompt =TotalPrompt+PRVal
    VPromptInt.append(PRVal)
    PRErr=GetHistError(HistName, PromptDir + "/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+x+".root",0.15)
    TotalErrPrompt = math.sqrt(PRErr*PRErr + TotalErrPrompt*TotalErrPrompt)
    VPromptErr.append(PRErr)


ConvList="BkgLists/Conv.txt"
ConvList = GetListFromFile(ConvList)
ConvDir = "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/"+args.Era+"/RunConv__/"
VConvInt = []
VConvErr = []
TotalConv =0
TotalErrConv=0
for x in ConvList:
    PRVal = GetHistIntegral(HistName, ConvDir + "/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+x+".root")
    TotalConv =TotalConv+PRVal
    VConvInt.append(PRVal)
    PRErr=GetHistError(HistName, ConvDir + "/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+x+".root",0.15)
    TotalErrConv = math.sqrt(PRErr*PRErr + TotalErrConv*TotalErrConv)
    VConvErr.append(PRErr)







DataInt     = GetHistIntegral(HistName,DataPath)

NonPromptInt= GetHistIntegral(HistName, NonPromptPath)
CFInt       = GetHistIntegral(HistName, CFPath)
BkgInt      = TotalPrompt+NonPromptInt+TotalConv+CFInt


DataErr     = GetHistError(HistName, DataPath,  0)
NonPromptErr= GetHistError(HistName, NonPromptPath,0.3)
CFErr       = GetHistError(HistName, CFPath,    0.2)


BkgErr = math.sqrt(TotalErrPrompt*TotalErrPrompt + NonPromptErr*NonPromptErr + TotalErrConv*TotalErrConv + CFErr*CFErr)

Signif = (DataInt-BkgInt) / (math.sqrt(DataErr*DataErr + BkgErr*BkgErr))


outfile_path = os.getenv("PLOT_PATH") + args.Analyser 
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  +args.DateDir
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  + args.PlotterTag
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  +args.Era
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  +Region
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  +args.ID
MakeDir(outfile_path)
outfile_path = outfile_path + "/"  +args.Channel
MakeDir(outfile_path)
outfile_path = outfile_path + "/BkgYields_"+args.List+".txt"

print ("@@@"*50)
print ("outfile_path = " + outfile_path)

f = open(outfile_path, "w")

WriteString = ""

#for x in VPromptInt:

Print_PromptInt = float("{:.2f}".format(TotalPrompt))
Print_PromptErr = float("{:.2f}".format(TotalErrPrompt))

Print_CFInt = float("{:.2f}".format(CFInt))
Print_CFErr = float("{:.2f}".format(CFErr))

Print_ConvInt = float("{:.2f}".format(TotalConv))
Print_ConvErr = float("{:.2f}".format(TotalErrConv))

Print_NonPromptInt = float("{:.2f}".format(NonPromptInt))
Print_NonPromptErr = float("{:.2f}".format(NonPromptErr))

Print_BkgInt = float("{:.2f}".format(BkgInt))
Print_BkgErr = float("{:.2f}".format(BkgErr))

Print_DataInt = float("{:.2f}".format(DataInt))
Print_DataErr = float("{:.2f}".format(DataErr))

Print_Signif = float("{:.2f}".format(Signif))

f.write(args.ID + " " + Region + " NBkg[Prompt] = " + str(Print_PromptInt) + "+/- " + str(Print_PromptErr)+ " NBkg[CF] = " + str(Print_CFInt)  + "+/- " + str(Print_CFErr)+ " NBkg[Conv] = " + str(Print_ConvInt)  + "+/- " + str(Print_ConvErr)+ " NBkg[Fake] = " + str(Print_NonPromptInt) +  "+/- " + str(Print_NonPromptErr)+ "  NBkg[Total] = " + str(Print_BkgInt)  + "+/- " + str(Print_BkgErr)+ " NData = " + str(Print_DataInt) + " Significance =  " + str(Print_Signif)+"\n")

f.write("--"*50 +"\n")
f.write(""*50 +"\n")

for x in range(0,len(VPromptInt)): 
    Print_BkgInt = float("{:.2f}".format(VPromptInt[x]))
    f.write("Bkg : "+ PromptList[x] + " "*(50-len(PromptList[x] )) + str(Print_BkgInt) + " " + '\n')
f.write("--"*50 +"\n")
f.write("NBkg[Prompt] = " + " "*45 + str(Print_PromptInt) +"\n")
f.write("--"*50 +"\n")

for x in range(0,len(VConvInt)):
    Print_BkgInt = float("{:.2f}".format(VConvInt[x]))
    f.write("Bkg : "+ ConvList[x] + " "*(50-len(ConvList[x] )) + str(Print_BkgInt) + " " + '\n')
f.write("--"*50 +"\n")
f.write("NBkg[Conv] = " + " "*45 + str(Print_ConvInt) +"\n")
f.write("--"*50 +"\n")
f.close()


print "Summary Table ["+Region+"/"+args.ID+"/"+args.Channel+"]"
print "-"*50
print "Data = " + str(DataInt)
print "Total Bkg =  " + str(BkgInt)
print "="*50
print "Significance =  " + str(Signif)
print "="*50
print "-"*50
print "Prompt = " + str(TotalPrompt)
print "NonPrompt = " + str(NonPromptInt)
print "Conv = " + str(TotalConv)
print "CF = " + str(CFInt)

