import os

years = ["2016"]

datalist = [ ["2016" , [ "DoubleEG", "DoubleMuon"]], 
             ["2017" , [ "DoubleEG", "DoubleMuon"]],
             ["2018",  [ "EGamma",  "DoubleMuon"]]]

for d in datalist:
    year = d[0]
    if not os.path.exists("/Users/john/Type1/MergedFiles/" + year + "/"):
        os.system("mkdir " + "/Users/john/Type1/MergedFiles/" + year + "/")
    for dataset in d[1]:
        if not os.path.exists("/Users/john/Type1/MergedFiles/" + year + "/" + dataset):
            os.system("mkdir " + "/Users/john/Type1/MergedFiles/" + year + "/" + dataset)

                    
        outpath = "/Users/john/Type1/MergedFiles/" + year + "/"
        if not os.path.exists(outpath):
            os.system("mkdir " + outpath)
            
        inpath = "/Users/john/Type1/Files/HNtypeI_JA/"+year + "/"
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

