import os 

import os 

import argparse


parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="HNL_SignalRegionPlotter")
parser.add_argument('-f', dest='Flag', default="")

args = parser.parse_args()
FlagDir=args.Flag

Analyser=args.Analyzer


if os.getenv("FILE_MERGED_PATH") == "NULL":
    print("Env not set.....")
    exit()

sk_path=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016/"+FlagDir
sk_path2=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2017/"+FlagDir
sk_path3=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2018/"+FlagDir
path_Run2=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/YearCombined/"+FlagDir

from os import listdir

from os.path import isfile,isdir, join
arr_tamsadir  = [f for f in listdir(sk_path) if isfile(join(sk_path,f))]
sswwsamples = []
for filename in arr_tamsadir:
    print filename
    sswwsamples.append(filename)


os.system("mkdir -p " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/YearCombined/")
os.system("mkdir -p " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/YearCombined/"+FlagDir)

for x in sswwsamples:
    if os.path.exists(path_Run2 +"/"+x  ):
        os.system("rm " + path_Run2 +"/"+x  )
    os.system("hadd  " + path_Run2 +"/"+x  + " "  + sk_path2 +"/"+x + " "  +sk_path + "/"+x + " "  + sk_path3 +"/"+x)


sig_arr_tamsadir  = [f for f in listdir(sk_path+"/SIGMerged/") if isfile(join(sk_path+"/SIGMerged/",f))]

sigsamples = []
for filename in sig_arr_tamsadir:
    sigsamples.append(filename)


os.system("mkdir -p " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/YearCombined/"+FlagDir+"/SIGMerged/")

for x in sigsamples:
    if os.path.exists(path_Run2 +"/SIGMerged/"+x  ):
        os.system("rm " + path_Run2 +"/SIGMerged/"+x  )
    os.system("hadd  " + path_Run2 +"/SIGMerged/"+x  + " "  + sk_path2 +"/SIGMerged/"+x + " "  +sk_path + "/SIGMerged/"+x + " " + sk_path3 +"/SIGMerged/"+x)



