import os

years = ["2016"]

datalist = [ ["2016" , [ "DoubleEG", "DoubleMuon"]], 
             ["2017" , [ "DoubleEG", "DoubleMuon"]],
             ["2018",  [ "EGamma",  "DoubleMuon"]]]

for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") + d[0] + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)


    year = d[0]
    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)
    for dataset in d[1]:
        if not os.path.exists(outpath + dataset):
            os.system("mkdir " + outpath + dataset)

        
        outpath = outpath
        if not os.path.exists(outpath):
            os.system("mkdir " + outpath)

        inpath = os.getenv("INFILE_PATH") +d[0] +"/"
        if dataset == "DoubleMuon" :
            inpath += "isMM__/DATA/"
        else:
            inpath += "isEE__/DATA/"

        hadd = "hadd " + outpath + "HNtypeI_JA_SkimTree_SSNonIso_"+dataset + ".root "
        hadd = hadd + inpath +"HNtypeI_JA_SkimTree_SSNonIso_"+dataset + "* " 

        print " "
        print hadd
        if os.path.exists(outpath + "HNtypeI_JA_SkimTree_SSNonIso_"+dataset + ".root"):
            os.system("rm " + outpath + "HNtypeI_JA_SkimTree_SSNonIso_"+dataset + ".root")
        os.system(hadd)

