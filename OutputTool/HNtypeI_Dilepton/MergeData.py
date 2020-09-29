import os,sys
sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *

datalist = [ ["2016" , [ "DoubleEG", "DoubleMuon"]], 
             ["2017" , [ "DoubleEG", "DoubleMuon","SingleMuon"]],
             ["2018",  [ "EGamma",  "DoubleMuon","SingleMuon"]]]

analyzername="HNtypeI_Dilepton"
for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/" +d[0] + "/"
    MakeDirectory(outpath)

    year = d[0]
    for dataset in d[1]:
        MakeDirectory(outpath + dataset)

        inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"+d[0] +"/"

        if dataset == "DoubleMuon" :
            inpath += "isMM__/DATA/"
        elif dataset == "SingleMuon":
            inpath += "isSingleMu__/DATA/"
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
   
    print "Merging Muon samples"
    if "SingleMuon" in d[1]:
        print "hadd " + outpath + analyzername+"_SkimTree_SSNonIso_Muon.root  " + outpath + analyzername+"_SkimTree_SSNonIso_DoubleMuon.root  "+  outpath + analyzername+"_SkimTree_SSNonIso_SingleMuon.root  "
        if os.path.exists(outpath + analyzername+"_SkimTree_SSNonIso_Muon.root"):
            os.remove(outpath + analyzername+"_SkimTree_SSNonIso_Muon.root")
        os.system("hadd " + outpath + analyzername+"_SkimTree_SSNonIso_Muon.root  " + outpath + analyzername+"_SkimTree_SSNonIso_DoubleMuon.root  "+  outpath + analyzername+"_SkimTree_SSNonIso_SingleMuon.root  ")
    else:
        if os.path.exists(outpath + analyzername+"_SkimTree_SSNonIso_Muon.root"):
            os.remove(outpath + analyzername+"_SkimTree_SSNonIso_Muon.root")

        print "mv " + outpath + analyzername+"_SkimTree_SSNonIso_DoubleMuon.root " + outpath + analyzername+"_SkimTree_SSNonIso_Muon.root"
        os.system("mv " + outpath + analyzername+"_SkimTree_SSNonIso_DoubleMuon.root " + outpath + analyzername+"_SkimTree_SSNonIso_Muon.root")
