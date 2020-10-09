import os

datalist = [ ["2016" , ["EE", "DoubleEG"]],
             ["2017" , ["EE", "DoubleEG"]], 
             ["2018",  ["EE", "EGamma"  ]]]

analyzername="HNtypeI_Dilepton"
for d in datalist:
    
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/" + d[0] + "/"
    year = d[0]
    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)

    dataset=d[1]
    inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"  + d[0] +"/" 
    if dataset[1]=="DoubleMuon":
        inpath += "isMM__RunCF__/DATA/"
    else:
        inpath += "isEE__RunCF__/DATA/"

    hadd = "hadd " + outpath + analyzername+"_SkimTree_SSHN_CF.root "
    hadd = hadd + inpath +analyzername+"_SkimTree_SSHN_"+dataset[1] + "* " 
    print " "
    print hadd

    if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_CF.root"):
        os.system("rm " + outpath + analyzername+"_SkimTree_SSHN_CF.root")
    os.system(hadd)

