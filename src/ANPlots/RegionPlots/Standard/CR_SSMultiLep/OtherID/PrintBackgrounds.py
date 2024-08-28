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


FilePath="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_ControlRegion_Plotter/"+DateDir+"/"

DataPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_data.root"
NonPromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_NonPrompt.root"
CFPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_CF.root"
PromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Prompt.root"
WZ_PromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WZ.root"
ZZ_PromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ZZ.root"
WW_PromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WW.root"
Other_PromptPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Other.root"
ConvPath = FilePath + args.Era + "/"+ args.Flag + "/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Conv.root"

HistName = "/"+Region+"/"+args.ID+"/"+args.Channel+"/NObj/N_Mu"

### GET INTEGRALS
Total_WZPrompt = GetHistIntegral(HistName, WZ_PromptPath)
Total_ZZPrompt = GetHistIntegral(HistName, ZZ_PromptPath)
Total_WWPrompt = GetHistIntegral(HistName, WW_PromptPath)
Total_OtherPrompt = GetHistIntegral(HistName, Other_PromptPath)
Total_Conv = GetHistIntegral(HistName, ConvPath)
Total_Prompt = GetHistIntegral(HistName, PromptPath)
Total_Data     = GetHistIntegral(HistName,DataPath)

Total_NonPrompt= GetHistIntegral(HistName, NonPromptPath)
Total_CF       = GetHistIntegral(HistName, CFPath)
Total_Bkg      = Total_Prompt+Total_NonPrompt+Total_Conv+Total_CF
Total_Bkg2      = Total_WZPrompt+Total_ZZPrompt+Total_WWPrompt+Total_OtherPrompt+Total_NonPrompt+Total_Conv+Total_CF

DataErr     = GetHistError(HistName, DataPath,  0)
NonPromptErr= GetHistError(HistName, NonPromptPath,0.3)
CFErr       = GetHistError(HistName, CFPath,    0.2)
PromptErr= GetHistError(HistName, PromptPath,0.15)
ConvErr= GetHistError(HistName, ConvPath,0.15)

BkgErr = math.sqrt(PromptErr*PromptErr + NonPromptErr*NonPromptErr + ConvErr*ConvErr + CFErr*CFErr)

Signif = (Total_Data-Total_Bkg) / (math.sqrt(DataErr*DataErr + BkgErr*BkgErr))


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


Print_PromptInt = float("{:.2f}".format(Total_Prompt))
Print_PromptErr = float("{:.2f}".format(PromptErr))

Print_CFInt = float("{:.2f}".format(Total_CF))
Print_CFErr = float("{:.2f}".format(CFErr))

Print_ConvInt = float("{:.2f}".format(Total_Conv))
Print_ConvErr = float("{:.2f}".format(ConvErr))

Print_NonPromptInt = float("{:.2f}".format(Total_NonPrompt))
Print_NonPromptErr = float("{:.2f}".format(NonPromptErr))

Print_BkgInt = float("{:.2f}".format(Total_Bkg))
Print_BkgErr = float("{:.2f}".format(BkgErr))

Print_DataInt = float("{:.2f}".format(Total_Data))
Print_DataErr = float("{:.2f}".format(DataErr))

Print_Signif = float("{:.2f}".format(Signif))

f.write(args.ID + " " + Region + ":\n")
f.write("NBkg[Prompt] = " + str(Print_PromptInt) + "+/- " + str(Print_PromptErr)+ " \n")
f.write("NBkg[CF] = " + str(Print_CFInt)  + "+/- " + str(Print_CFErr)+ " \n")
f.write("NBkg[Conv] = " + str(Print_ConvInt)  + "+/- " + str(Print_ConvErr)+ " \n")
f.write("NBkg[Fake] = " + str(Print_NonPromptInt) +  "+/- " + str(Print_NonPromptErr)+ "  \n")
f.write("--------------------- \n")
f.write("NBkg[Total] = " + str(Print_BkgInt)  + "+/- " + str(Print_BkgErr)+ " \n")
f.write("--------------------- \n")
f.write("NData = " + str(Print_DataInt) + " \n")
f.write("Significance =  " + str(Print_Signif)+"\n")
f.write("--------------------- \n")

f.write("--"*50 +"\n")
f.write(""*50 +"\n")

f.close()


print "Summary Table ["+Region+"/"+args.ID+"/"+args.Channel+"]"
print "-"*50
print "Data = " + str(Total_Data)
print "Total Bkg =  " + str(Total_Bkg)
print "Total Bkg [summed] =  " + str(Total_Bkg2)
print "="*50
print "Significance =  " + str(Signif)
print "="*50
print "-"*50
print "Prompt = " + str(Total_Prompt)
print "NonPrompt = " + str(Total_NonPrompt)
print "Conv = " + str(Total_Conv)
print "CF = " + str(Total_CF)

