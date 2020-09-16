import os

years = ["2016"]

datalist = [ ["2016" , [ "DoubleEG", "DoubleMuon"]], 
             ["2017" , [ "SingleElectron", "DoubleMuon","SingleMuon"]],
             ["2018",  [ "EGamma",  "DoubleMuon","SingleMuon"]]]

for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") + "FakeRateHN/"+ d[0] + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)


    year = d[0]
    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)
    for dataset in d[1]:
        
        outpath = outpath
        if not os.path.exists(outpath):
            os.system("mkdir " + outpath)

        inpath = os.getenv("INFILE_PATH") +"FakeRateHN/"+d[0] +"/"
        if dataset == "DoubleMuon" :
            inpath += "isMM__/DATA/"
        elif dataset == "SingleMuon" :
            inpath += "isSingleMu__/DATA/"

        else:
            inpath += "isEE__/DATA/"

        hadd = "hadd " + outpath + "FakeRateHN_SkimTree_NonIso_"+dataset + ".root "
        hadd = hadd + inpath +"FakeRateHN_SkimTree_NonIso_"+dataset + "* " 

        print " "
        print hadd
        if os.path.exists(outpath + "FakeRateHN_SkimTree_NonIso_"+dataset + ".root"):
            os.system("rm " + outpath + "FakeRateHN_SkimTree_NonIso_"+dataset + ".root")
        os.system(hadd)

