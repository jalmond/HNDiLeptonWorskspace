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

    if not os.path.exists(InDir):
        return 0

    f = ROOT.TFile(InDir)
    hist=f.Get(HistName)
    if not hist:
        print("Hist does not exist " + str(InDir) + " " + str(HistName))
        #        print("run python HistPrinter.py -input " + str(InDir))
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
parser.add_argument('-f', dest='Flag', type=str, default='NULL')
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
PromptWZInt = 0
PromptZZInt = 0
PromptWWInt = 0
PromptOtherInt = 0
NonPromptInt = 0
ConvInt = 0
CFInt = 0

FilePath="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_ControlRegion_Plotter/"+DateDir+"/"

DataPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_data.root"
NonPromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_NonPrompt.root"
CFPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_CF.root"
ConvPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Conv.root"
WZPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WZ.root"
WWPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WW.root"
ZZPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ZZ.root"
TopPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Top.root"
OtherPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Other.root"

HistName = "/"+Region+"/"+args.ID+"/"+args.Channel+"/NObj/N_Mu"




DataInt     = GetHistIntegral(HistName,DataPath)
NonPromptInt= GetHistIntegral(HistName, NonPromptPath)
CFInt       = GetHistIntegral(HistName, CFPath)
WZInt       = GetHistIntegral(HistName, WZPath)
ZZInt       = GetHistIntegral(HistName, ZZPath)
WWInt       = GetHistIntegral(HistName, WWPath)
TopInt      = GetHistIntegral(HistName, TopPath)
OtherInt    = GetHistIntegral(HistName, OtherPath)
ConvInt     = GetHistIntegral(HistName, ConvPath)
BkgInt      = +NonPromptInt+CFInt+WZInt+ZZInt+WWInt+TopInt+OtherInt+ConvInt

TotalPrompt = WZInt + ZZInt + WWInt + TopInt+OtherInt

DataErr     = GetHistError(HistName, DataPath,  0)

NonPromptErr= GetHistError(HistName, NonPromptPath,0.3)
CFErr       = GetHistError(HistName, CFPath,    0.2)
ConvErr     = GetHistError(HistName, ConvPath,    0.25)
WZErr       = GetHistError(HistName, WZPath,    0.12)
ZZErr       = GetHistError(HistName, ZZPath,    0.15)
WWErr       = GetHistError(HistName, WWPath,    0.20)
TopErr  = GetHistError(HistName, TopPath,    0.20)
OtherErr  = GetHistError(HistName, OtherPath,    0.5)

TotalErrPrompt = math.sqrt(WZErr*WZErr + ZZErr*ZZErr + WWErr*WWErr + TopErr*TopErr + OtherErr*OtherErr)
BkgErr = math.sqrt(TotalErrPrompt*TotalErrPrompt + NonPromptErr*NonPromptErr + ConvErr*ConvErr + CFErr*CFErr)

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


Print_PromptInt = float("{:.2f}".format(TotalPrompt))
Print_PromptErr = float("{:.2f}".format(TotalErrPrompt))

WZ_Print_PromptInt = float("{:.2f}".format(WZInt))
WZ_Print_PromptErr = float("{:.2f}".format(WZErr))

ZZ_Print_PromptInt = float("{:.2f}".format(ZZInt))
ZZ_Print_PromptErr = float("{:.2f}".format(ZZErr))

WW_Print_PromptInt = float("{:.2f}".format(WWInt))
WW_Print_PromptErr = float("{:.2f}".format(WWErr))

Top_Print_PromptInt = float("{:.2f}".format(TopInt))
Top_Print_PromptErr = float("{:.2f}".format(TopErr))

Other_Print_PromptInt = float("{:.2f}".format(OtherInt))
Other_Print_PromptErr = float("{:.2f}".format(OtherErr))

Print_CFInt = float("{:.2f}".format(CFInt))
Print_CFErr = float("{:.2f}".format(CFErr))

Print_ConvInt = float("{:.2f}".format(ConvInt))
Print_ConvErr = float("{:.2f}".format(ConvErr))

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
f.write("--"*50 +"\n")
f.write("WZ = " + " "*45 + str(WZ_Print_PromptInt) + " " + " \pm " + str(WZ_Print_PromptErr) +"\n")
f.write("ZZ = " + " "*45 + str(ZZ_Print_PromptInt) + " " + " \pm " + str(ZZ_Print_PromptErr) +"\n")
f.write("WW = " + " "*45 + str(WW_Print_PromptInt) + " " + " \pm " + str(WW_Print_PromptErr) +"\n")
f.write("Top = " + " "*45 + str(Top_Print_PromptInt) + " " + " \pm " + str(Top_Print_PromptErr) +"\n")
f.write("Other = " + " "*45 + str(Other_Print_PromptInt) + " " + " \pm " + str(Other_Print_PromptErr) +"\n")
f.write("--"*50 +"\n")

f.write("--"*50 +"\n")
f.write("NBkg[Prompt] = " + " "*45 + str(Print_PromptInt) + " " + " \pm " + str(Print_PromptErr) +"\n")
f.write("--"*50 +"\n")


f.write("NBkg[Conv] = " + " "*45 + str(Print_ConvInt) + " " + " \pm " + str(Print_ConvErr) +"\n")
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
if ConvInt > 0:
    print "Conv = " + str(ConvInt)
if CFInt > 0:
    print "CF = " + str(CFInt)


print (outfile_path)
