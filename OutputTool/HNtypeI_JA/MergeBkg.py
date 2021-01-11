import os,sys

sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *


years = ["2016", "2017", "2018"]

##################################################
##### code to merge bkgs to use for limit code
##################################################

for y in years:

    ZZ="ZZ_pythia"
    WZ ="WZ_pythia"
    if y == "2016":
        ZZ="ZZTo4L_powheg"
        WZ="WZTo3LNu_powheg"

    # SS bkg individual    
    ssDiboson = ["Diboson", ["WWTo2L2Nu_DS",ZZ,"ggZZ", WZ,"VBF_HToZZTo4L"]]
    ssTop = ["top", ["ttWToLNu" ,"ttHToNonbb","ttZ","VHToNonbb"]]
    ssTriboson = ["VVV", ["ZZZ", "WWW","WZZ","WWZ"]]
    ssWW = ["WWpp", ["WpWp_EWK","WpWp_QCD"]]
    ssXG= ["XG" , ["TG" ,"TTG", "WG", "ZG"]]

    # SS summed bk
    ssOther = ["Other", ["VBF_HToZZTo4L","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu"]]
    ssprompt = ["SSPrompt",  ["WWTo2L2Nu_DS","ZG",ZZ ,"ggZZTo4e","WG", WZ, "VBF_HToZZTo4L","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu"]]

    # SS Fake / CF
    ssFakesMuon_list = ["FakeMuMu", ["DYJets", "TTLJ_powheg", "WJets_MG","SingleTop","TTLL_powheg"]]
    ssFakesEl_list = ["FakeEE", [ "TTLJ_powheg", "WJets_MG","SingleTop"]]
    osFakesOS_list = ["FakeOS", [ "TTLJ_powheg", "WJets_MG","SingleTop"]]
    ssCF = ["CF", ["DYJets", "TTLL_powheg"]]
    osCF = [ "OSCF", ["WpWp_EWK","WpWp_QCD"]]
    
    allSS = ["SS", ["WWTo2L2Nu_DS","WWTo2L2Nu_powheg","ZG",ZZ,"WWToLNuQQ_powheg","ggZZTo4e","WGToLNuG", WZ ,"VBF_HToZZTo4L","WWTo2L2Nu_DS","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu", "DY", "TTLJ_powheg", "WJets_MG","SingleTop","TTLL_powheg"]]

    osprompt = ["OSPrompt", ["DYJets","TT"]]
                             #"WWTo2L2Nu_DS","WWTo2L2Nu_powheg","ZG",ZZ,"WWToLNuQQ_powheg","ggZZTo4e","WGToLNuG", WZ, "VBF_HToZZTo4L","WWTo2L2Nu_DS","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu","TTLL_powheg"]]

    top = ["top", ["TT"]]
    dy = ["dy", ["DY"]]
    SSLists = [ osprompt, top, dy]

    analyzername="HNtypeI_JA"
    outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/"+ y + "/"
    MakeDirectory(outpath)
    inpath = os.getenv("INFILE_PATH") + "/"+ analyzername+"/" +y +"/"  
    print "-"*30
    for list in SSLists:
        file_s  = list[0]
        
        hadd = "hadd " + outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root "
        for s in list[1]:
            hadd = hadd + inpath +analyzername+"_SkimTree_SSNonIso_"+s + "* " 

        if os.path.exists(outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root"):
            os.remove( outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root")
        print "Merging " + outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root "
        os.system(hadd )#+ " >> haddbkg.log " )


