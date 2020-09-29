import os,sys

sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

years = ["2016", "2017", "2018"]

##################################################
##### code to merge bkgs to use for limit code
##################################################

analyzername="HNtypeI_Dilepton"
## copy DY to CF


 


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

    ss = ["SS",  ["WWTo2L2Nu_DS","ZG",ZZ ,"ggZZTo4e","WG", WZ, "VBF_HToZZTo4L","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","WpWp_EWK","WpWp_QCD","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu"]]


    

    osprompt = ["OSPrompt", ["DYJets", "WWTo2L2Nu_DS","WWTo2L2Nu_powheg","ZG",ZZ,"WWToLNuQQ_powheg","ggZZTo4e","WGToLNuG", WZ, "VBF_HToZZTo4L","WWTo2L2Nu_DS","ZZZ","ttHToNonbb","ttZ","VHToNonbb","WWW","WZZ","ttWToLNu","TG","WWZ","TTG","ggZZTo2e2tau","ggZZTo2e2mu","TTLL_powheg"]]


    SSLists = [ ssDiboson , ssOther, ssprompt, ss,ssTop, ssTriboson, ssWW, ssXG,osprompt]



    outpath = os.getenv("INFILE_MERGED_PATH") + "/"+analyzername+"/" +y + "/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)
    inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"+y +"/"  
    for list in SSLists:
        file_s  = list[0]
        
        hadd = "hadd " + outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root "
        for s in list[1]:
            hadd = hadd + inpath +analyzername+"_SkimTree_SSNonIso_"+s + "* " 

        print " "
        print hadd
        if os.path.exists(outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root"):
            os.system("rm " + outpath + analyzername+"_SkimTree_SSNonIso_"+file_s + ".root")
        os.system(hadd)

