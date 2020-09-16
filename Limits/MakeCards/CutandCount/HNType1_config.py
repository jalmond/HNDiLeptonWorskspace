def MakeDirectory(path):
    if not os.path.exists(path):
        os.mkdir(path)


def PrintSetup(setupconfig):

    for x in setupconfig:
        if len(x) == 2:
            if len(str(x[1])) < 50:
                print str(x[0]) + " "*(20-len(str(x[0]))) +" : "+ str(x[1])
            else:
                print str(x[0]) + " "*(20-len(str(x[0]))) +" : "+ str(x[1])[0:50]
                print " "*(20) +" : "+ str(x[1])[50:100]
        else:
            print "Error in PrintSetup"
            exit()
    
def GetConfig(tag, configfile,_setup):
    
    list_channels=[]
    _config = open(configfile,"r")
    is_config_setup=False
    for line in _config:
        if tag in line:
            if len(line.split()) == 3:
                _tmp_line=line.split()[2]
                is_config_setup=True
                _tmp_line=_tmp_line.replace(","," ")
                _tmp_line=_tmp_line.split()
                for x in _tmp_line:
                    list_channels.append(x)
            
    if is_config_setup:
        _setup.append([tag,list_channels])
        return list_channels
        
    else:
        print "Error in finding " + tag + "  from " + configfile 
        exit()
                
    
def GetHistNameSRMassBin(channel,SR, mass,year, _id):

    histname= SR
    histname+= "/"+ histname +"_mn"+mass +"_nevent_HNtypeI_JA_"+channel+"_"+_id+"_"

    return histname



def GetMassBin(mass, VBF):

    masses = ["100",
              "125",
              "200",
              "250",
              "300",
              "400",
              "500",
              "600",
              "700",
              "800",
              "900",
              "1000",
              "1100",
              "1200",
              "1300",
              "1400",
              "1500",
              "1700"]

    masses_vbf =  [   "300",
              "400",
              "500",
              "600",
              "700",
              "800",
              "900",
              "1000",
              "1100",
              "1200",
              "1300",
              "1400",
              "1500",
              "1700"]

    counter = 0
    _masses= masses
    if VBF == "_VBF":
        _masses = masses_vbf
    for m in _masses:
        counter = counter +1
        if m == mass:
            return counter


    return -1


def GetSignalEventsSRMassBin(channel,SR, mass,year, VBF,_id):

    histname=GetHistName(channel,SR, mass,year,_id)

    filepaths = []
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/HNtypeI_JA/2016/SIG/HNtypeI_JA_HN_Schan\
nel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBF":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/HNtypeI_JA/2016/SIG/HNtypeI_JA_HN_Tchan\
nel_"+channel+"_"+mass+"_nlo.root")
    else :
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/HNtypeI_JA/2016/SIG/HNtypeI_JA_HN_Schan\
nel_"+channel+"_"+mass+"_nlo.root")
        if int(mass) > 250:
            filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/HNtypeI_JA/2016/SIG/HNtypeI_JA_HN_T\
channel_"+channel+"_"+mass+"_nlo.root")

    total=0

    for _filename in filepaths:
        _file = ROOT.TFile(_filename)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    if total < 0:
        return 0.

    print total
    # copy scale used by JS in 2016                                                                 \
                                                                                                     
    scale_ = 1.
    if int(mass) <= 200:
        scale_ = 0.001
    elif int(mass) <= 600:
        scale_ = 0.1
    elif int(mass) <=1000:
        scale_ = 1.
    else:
        scale_ = 10.


    #since only 2016 samples available use these and scale to lumi for now                          \
                                                                                                     
    # effective lumi: 36.47 fb-1 (2016) 41.54 fb-1 (2017) 59.96 fb-1 (2018)                         \
                                                                                                     

    if year == "2017":
        scale_ = scale_* 41.54/36.47
    elif year == "2018":
        scale_*59.96/36.47

    return round(total*scale_,4)

def GetFakeCountSRMassBin(channel, SR, mass,year,_id):
    histname=GetHistName(channel,SR, mass,year,_id)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + "/HNtypeI_JA/"+ year + "/HNtypeI_JA_Skim\
Tree_SSNonIso_Fake"+channel+".root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + "/HNtypeI_JA/"+year + "/HNtypeI_JA_SkimT\
ree_SSNonIso_FakeOS.root"  )


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return round(total,4)

def GetCFCountSRMassBin(channel,SR, mass,year,_id):

    if channel == "MuMu":
        return 0.

    histname=GetHistName(channel,SR, mass,year,_id)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")+ "/HNtypeI_JA/"+ year + "/HNtypeI_JA_SkimTr\
ee_SSNonIso_CF.root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH") +"/HNtypeI_JA/"+ year + "/HNtypeI_JA_SkimTr\
ee_SSNonIso_OSCF.root"  )


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    if total < 0:
        return 0.0
