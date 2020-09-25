import os

datalist = [ ["2016" , [ "Electron", [[ "EE","DoubleEG"]]]] ,
             ["2016" , [ "Muon",  [["MM", "DoubleMuon"]]]],
             ["2017" , [ "Electron", [["EE","SingleElectron"]]]],
             ["2017",  [  "Muon", [["MM","DoubleMuon"],["SingleMu","SingleMuon"]]]],
             ["2018" , [ "Electron", [[ "EE","EGamma"]]]] ,
             ["2018",  [  "Muon", [["MM","DoubleMuon"],["SingleMu","SingleMuon"]]]]]

for d in datalist:

    year = d[0]
    outpath = os.getenv("INFILE_MERGED_PATH") + "FakeRateHN/"+ str(year) + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)

    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)

    flavour=d[1][0]
    datasets=d[1][1]
    hadd = "hadd " + outpath + "FakeRateHN_SkimTree_NonIso_"+flavour + ".root "
    for dataset in datasets:
        
        inpath = os.getenv("INFILE_PATH") +"FakeRateHN/"+year +"/"
        inpath += "is"+dataset[0]+"__/DATA/"

        
        hadd = hadd + inpath +"FakeRateHN_SkimTree_NonIso_"+dataset[1] + "* " 

    print " "
    print hadd
    if os.path.exists(outpath + "FakeRateHN_SkimTree_NonIso_"+dataset[1] + ".root"):
        os.system("rm " + outpath + "FakeRateHN_SkimTree_NonIso_"+dataset[1] + ".root")
    #os.system(hadd)
