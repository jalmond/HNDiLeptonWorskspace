import os,sys

sys.path.insert(1, '/data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/python')
from GeneralSetup import *

# now import analysis functions
from HNType1_config import *

datalist = [ ["2016" , [ "DoubleEG", "DoubleMuon"]], 
             ["2017" , [ "DoubleEG", "DoubleMuon"]],
             ["2018",  [ "EGamma",  "DoubleMuon"]]]

analyzername="HNtypeI_JA"
for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/" +d[0] + "/"
    MakeDirectory(outpath)

    year = d[0]
    for dataset in d[1]:
        MakeDirectory(outpath + dataset)

        inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"+d[0] +"/"

        if dataset == "DoubleMuon" :
            inpath += "isMM__/DATA/"
        else:
            inpath += "isEE__/DATA/"

        hadd = "hadd " + outpath + analyzername+"_SkimTree_SSNonIso_"+dataset + ".root "
        hadd = hadd + inpath +analyzername+"_SkimTree_SSNonIso_"+dataset + "* " 

        print " "
        print hadd
        if os.path.exists(outpath + analyzername+"_SkimTree_SSNonIso_"+dataset + ".root"):
            os.system("rm " + outpath + analyzername+"_SkimTree_SSNonIso_"+dataset + ".root")

        os.system("rm hadddata.log")
        os.system(hadd+ " > hadddata.log")

