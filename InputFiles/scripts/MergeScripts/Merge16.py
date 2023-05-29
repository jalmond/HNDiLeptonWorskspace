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

sk_path=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016preVFP/"+FlagDir
sk_path2=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016postVFP/"+FlagDir
path_2016=os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016/"+FlagDir

from os import listdir

from os.path import isfile,isdir, join
arr_tamsadir  = [f for f in listdir(sk_path) if isfile(join(sk_path,f))]
sswwsamples = []
for filename in arr_tamsadir:
    print filename
    sswwsamples.append(filename)


os.system("mkdir -p " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016/")
os.system("mkdir -p " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser +"/2016/"+FlagDir)

for x in sswwsamples:
    if os.path.exists(path_2016 +"/"+x  ):
        os.system("rm " + path_2016 +"/"+x  )
    os.system("hadd  " + path_2016 +"/"+x  + " "  + sk_path2 +"/"+x + " "  +sk_path + "/"+x)



