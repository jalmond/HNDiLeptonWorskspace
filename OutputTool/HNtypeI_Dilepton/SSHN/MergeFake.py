import os

datalist = [ ["2016" , ["EE", "DoubleEG"]],
             ["2016" , ["MuMu", "DoubleMuon"]], 
             ["2017" , ["EE", "DoubleEG"]], 
             ["2017" , ["MM", "DoubleMuon"]],
             ["2017" , ["M", "SingleMuon"]],
             ["2018",  ["EE", "EGamma"  ]], 
             ["2018",  ["MM", "DoubleMuon"]],
             ["2018",  ["M", "SingleMuon"]]]

analyzername="HNtypeI_Dilepton"
for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/" + d[0] + "/"
    year = d[0]
    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)

    dataset=d[1]
    inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"  + d[0] +"/" 
    if dataset[1]=="DoubleMuon":
        inpath += "isMM__RunFake__/DATA/"
    elif dataset[1]=="SingleMuon":
        inpath += "isSingleMu__RunFake__/DATA/"
    else:
        inpath += "isEE__RunFake__/DATA/"

    hadd = "hadd " + outpath + analyzername+"_SkimTree_SSHN_Fake"+dataset[0]+".root "
    hadd = hadd + inpath +analyzername+"_SkimTree_SSHN_"+dataset[1] + "* " 
    print " "
    print hadd
    if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_Fake"+dataset[0] + ".root"):
        os.system("rm " + outpath + analyzername+"_SkimTree_SSHN_Fake"+dataset[0] + ".root")
    os.system(hadd)



years = ["2017","2018"]
for year in years:
    print "Merging Muon samples"
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/" + year + "/"

    print "hadd " + outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root  " + outpath + analyzername+"_SkimTree_SSHN_FakeMM.root  "+  outpath + analyzername+"_SkimTree_SSHN_FakeM.root "
    if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root"):
            os.remove(outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root")
    os.system("hadd " + outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root  " + outpath + analyzername+"_SkimTree_SSHN_FakeMM.root  "+  outpath + analyzername+"_SkimTree_SSHN_FakeM.root ")

