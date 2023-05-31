import os

import argparse

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-e', dest='Era', default="2017")
parser.add_argument('-f', dest='Flag', default="")
parser.add_argument('-a', dest='Analyzer', default="")

args = parser.parse_args()

Analyser=args.Analyzer
FlagDir=args.Flag
era = args.Era

_path = "/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/"++"/"+Era+"/"+Flag

print ("@@@@@@@@@@@@@@@@@ RUNNING RenameSig.py @@@@@@@@@@@@@@)")
print ("PATH:" +_path)

from os import listdir
from os.path import isfile,isdir, join

filelist  = [f for f in listdir(_path) if isfile(join(_path,f))]

for x in filelist:
    if not "Skim" in x:
    continue
    if "Type" in x:
        pathfix = x
        pathfix = pathfix.replace("SkimTree_HNMultiLepBDT_","")
        print pathfix
        os.system("mv " + _path+"/"+x + " " + _path+"/"+pathfix)
        
        
