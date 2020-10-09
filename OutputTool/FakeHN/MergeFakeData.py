import os

datalist = [ ["2016" , [ "Electron", [[ "EE","DoubleEG"]]]] ,
             ["2016" , [ "Muon",  [["MM", "DoubleMuon"]]]],
             ["2017" , [ "Electron", [["EE","SingleElectron"]]]],
             ["2017",  [  "Muon", [["MM","DoubleMuon"],["SingleMu","SingleMuon"]]]],
             ["2018" , [ "Electron", [[ "EE","EGamma"]]]] ,
             ["2018",  [  "Muon", [["MM","DoubleMuon"],["SingleMu","SingleMuon"]]]]]

skim="SkimTree_HNFake"
for d in datalist:

    year = d[0]
    outpath = os.getenv("INFILE_MERGED_PATH") + "FakeRateHN/"+ str(year) + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)

    if not os.path.exists(outpath):
        os.system("mkdir " + outpath)

    flavour=d[1][0]
    datasets=d[1][1]
    hadd = "hadd " + outpath + "FakeRateHN_"+skim+"_"+flavour + ".root "
    for dataset in datasets:
        
        inpath = os.getenv("INFILE_PATH") +"FakeRateHN/"+year +"/"
        inpath += "is"+dataset[0]+"__/DATA/"

        
        hadd = hadd + inpath +"FakeRateHN_"+skim+"_"+dataset[1] + "* " 

    print " "
    print hadd
    if os.path.exists(outpath + "FakeRateHN_"+skim+"_"+flavour + ".root"):
        os.system("rm " + outpath + "FakeRateHN_"+skim+"_"+flavour + ".root")
    os.system(hadd)


#os.system("source MC/mergefake.sh "+skim)
