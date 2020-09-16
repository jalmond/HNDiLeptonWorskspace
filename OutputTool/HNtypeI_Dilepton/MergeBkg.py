import os

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
    ssTriboson = ["VVV", ["ZZZ", "WWW"]] #WZZ,WWZ
    ssWW = ["WWpp", ["WpWp_EWK","WpWp_QCD"]]
    ssXG= ["XG" , ["TG" ,"TTG", "WG", "ZG"]]

    # SS summed bk
    ssOther = ["Other", ["VBF_HToZZTo4L","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu"]]

    ssprompt = ["SSPrompt",  ["WWTo2L2Nu_DS","ZG",ZZ ,"ggZZTo4e","WG", WZ, "VBF_HToZZTo4L","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu"]]

    # SS Fake / CF

    ssCF = ["CF", ["DYJets"]]
    osCF = [ "OSCF", ["DYJets"]]
    

    osprompt = ["OSPrompt", ["DYJets","DYJets10to50_MG", "WWTo2L2Nu_DS","WWTo2L2Nu_powheg","ZG",ZZ,"WWToLNuQQ_powheg","ggZZTo4e","WGToLNuG", WZ, "VBF_HToZZTo4L","WWTo2L2Nu_DS","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu","TTLL_powheg"]]


    SSLists = [ ssDiboson , ssOther, ssprompt, ssTop, ssTriboson, ssWW, ssXG]



    outpath = os.getenv("INFILE_MERGED_PATH") + "/HNtypeI_Dilepton/" +y + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)
    inpath = os.getenv("INFILE_PATH") +"/HNtypeI_Dilepton/"+y +"/"  
    for list in SSLists:
        file_s  = list[0]
        
        hadd = "hadd " + outpath + "HNtypeI_Dilepton_SkimTree_SSNonIso_"+file_s + ".root "
        for s in list[1]:
            hadd = hadd + inpath +"HNtypeI_Dilepton_SkimTree_SSNonIso_"+s + "* " 

        print " "
        print hadd
        if os.path.exists(outpath + "HNtypeI_Dilepton_SkimTree_SSNonIso_"+file_s + ".root"):
            os.system("rm " + outpath + "HNtypeI_Dilepton_SkimTree_SSNonIso_"+file_s + ".root")
        os.system(hadd)
