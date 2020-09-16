import os,ROOT


def GetEXO_17_028_Bkg(channel,SR,mass):
    
    effs=[]
    if channel == "MuMu":
        if SR == "SR1":
            effs = [
                ["100", 20.3],
                ["125", 17.7],
                ["150", 14.7],
                ["200", 12.4],
                ["250", 6.0],
                ["300", 8.2],
                ["400", 2.5],
                ["500", 1.5],
                ["600", 0.9],
                ["700", 1.7],
                ["800", 1.7],
                ["900", 1.7],
                ["1000",1.7],
                ["1100",1.7],
                ["1200",1.7],
                ["1300",1.7],
                ["1400",1.7],
                ["1500",1.7]]
        if SR == "SR2":
            effs = [
                ["100", 3.4],
                ["125", 0.2],
                ["150", 1.3],
                ["200", 0.8],
                ["250", 2.1],
                ["300", 1.3],
                ["400", 3.1],
                ["500", 2.8],
                ["600", 0.8],
                ["700", 0.8],
                ["800", 0.9],
                ["900", 0.2],
                ["1000", 0.3],
                ["1100",0.1],
                ["1200",0.1],
                ["1300",0.1],
                ["1400",0.1],
                ["1500",0.1]]
            
    if channel == "EE":
        if SR == "SR1":
            effs = [
                ["100", 18.6],
                ["125", 11.7],
                ["150", 8.9],
                ["200", 4.6],
                ["250", 3.0],
                ["300", 2.6],
                ["400", 0.9],
                ["500", 0.4],
                ["600", 0.3],
                ["700", 0.2],
                ["800", 0.2],
                ["900", 0.2],
                ["1000",0.2],
                ["1100",0.2],
                ["1200",0.2],
                ["1300",0.2],
                ["1400",0.2],
                ["1500",0.2]]
        if SR == "SR2":
            effs = [
                ["100", 1.0],
                ["125", 0.8],
                ["150", 1.0],
                ["200", 1.3],
                ["250", 0.3],
                ["300", 0.4],
                ["400", 0.5],
                ["500", 0.8],
                ["600", 0.7],
                ["700", 0.8],
                ["800", 0.4],
                ["900", 0.2],
                ["1000",0.1],
                ["1100",0.1],
                ["1200",0.2],
                ["1300",0.3],
                ["1400",0.1],
                ["1500",0.1]]
            
                
    for x in effs:
        if str(x[0]) == str(mass):
            return float(x[1])

    return -999.    



def GetEXO_17_028_Eff(channel,SR,mass):
    
    effs=[]
    if channel == "MuMu":
        if SR == "SR1":
            effs = [
                ["100", 2.6],
                ["125", 5.1],
                ["150", 6.6],
                ["200", 8.1],
                ["250", 11],
                ["300", 13.2],
                ["400", 11.7],
                ["500", 8.6],
                ["600", 7.4],
                ["700", 6.7],
                ["800", 6.0],
                ["900", 5.4],
                ["1000", 4.6],
                ["1100", 4.1],
                ["1200", 3.6],
                ["1300", 3.2],
                ["1400", 2.7],
                ["1500", 2.5]]
            
        elif SR == "SR2":
            effs = [
                ["100", 0.006],
                ["125", 0.08],
                ["150", 0.28],
                ["200", 1.4],
                ["250", 3],
                ["300", 5.4],
                ["400", 13.3],
                ["500", 22.4],
                ["600", 30.2],
                ["700", 34.6],
                ["800", 34.8],
                ["900", 35.8],
                ["1000", 38.4],
                ["1100", 36.7],
                ["1200", 38.5],
                ["1300", 38.5],
                ["1400", 35.9],
                ["1500", 36.4]]

    elif channel == "EE":
        if SR == "SR1":
            effs = [
                ["100", 1.1],
                ["125", 2.6],
                ["150", 3.1],
                ["200", 4.9],
                ["250", 5.9],
                ["300", 7.6],
                ["400", 6.6],
                ["500", 5.5],
                ["600", 3.8],
                ["700", 4.0],
                ["800", 3.6],
                ["900", 3.2 ],
                ["1000", 2.6],
                ["1100", 2.2],
                ["1200", 2.0],
                ["1300", 1.8],
                ["1400", 1.5],
                ["1500", 1.3]]
            
        elif SR == "SR2":
            effs = [
                ["100", 0.005],
                ["125", 0.04],
                ["150", 0.19],
                ["200", 0.6],
                ["250", 2.2],
                ["300", 3.5],
                ["400", 9.1],
                ["500", 14.3],
                ["600", 17.4],
                ["700", 19.4],
                ["800", 20.8],
                ["900", 19.2],
                ["1000", 21.5],
                ["1100", 20.3],
                ["1200", 20.8],
                ["1300", 20.5],
                ["1400", 19.6],
                ["1500", 19.5]]
                
    for x in effs:
        if str(x[0]) == str(mass):
            return float(x[1])/float(100.)

    return -999.

def ChooseMassList(list1, list2, channel,order_sc):

    if order_sc == 1:
        if channel == "TChannel":
            return list2
        else:
            return list1
    else:
        if channel == "TChannel":
            return list1
        else:
            return list2


def ChooseTag(channel):
    
    if channel == "TChannel":
        return "_VBF"
    elif channel == "CombinedChannel":
        return "_combined"
    else:
        return ""
        
def ChooseID(list1, list2, flavour,order_mu):
    if order_mu == 1:
        if flavour == "MuMu":
            return list1
        else:
            return list2
    else:
        if flavour == "MuMu":
            return list2
        else:
            return list1

    
def MakeDirectory(path):
    if not os.path.exists(path):
        os.mkdir(path)


def NIteration(samples):
    niter =1
    for x in samples:
        niter=niter* len(x)

    return niter


def SumIteration(i, lists):
    if len(lists) == 3:
        niter = NIteration(lists)
        return SumIteration3(i, lists[0],lists[1],lists[2],niter)
    elif len(lists) == 4:
        niter = NIteration(lists)
        return SumIteration4(i, lists[0],lists[1],lists[2],lists[3],niter)

    return [0,0,0]
    
def SumIteration3(i, list1, list2, list3,nmax):

    iter_1=0
    iter_2=0
    iter_3=0

    for x in range(0, nmax):
        if x == i :
            return [list1[iter_1],list2[iter_2],  list3[iter_3] ]

        iter_3=iter_3+1
        if iter_3 == len(list3):
            iter_3=0
            iter_2=iter_2+1
            if iter_2 == len(list2):
                iter_2=0
                iter_1=iter_1+1


    return ["","",""]

def SumIteration4(i, list1, list2, list3,list4,nmax):

    iter_1=0
    iter_2=0
    iter_3=0
    iter_4=0

    for x in range(0, nmax):
        if x == i :
            return [list1[iter_1],list2[iter_2],  list3[iter_3] , list4[iter_4]]


        iter_4=iter_4+1
        if iter_4 == len(list4):
            iter_4=0
            iter_3=iter_3+1
            if iter_3 == len(list3):
                iter_3=0
                iter_2=iter_2+1         
                if iter_2 == len(list2):
                    iter_2=0
                    iter_1=iter_1+1
                    
    return ["","","",""]
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



def GetSConfig(tag, configfile,_setup):
    
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
        return list_channels[0]
        
    else:
        print "Error in finding " + tag + "  from " + configfile 
        exit()
                
    
def GetHistNameSRHighMass(flavour,SR, mass,year, _id,Analyzer):
    histname = SR+"_highmass/"+SR+"_highmass_njets_"+Analyzer+"_"+flavour + "_"+_id + "_"
    return histname

def GetHistNameNoCut(flavour,_id,Analyzer):

    #histname = "CutFlow/NoCut_"+Analyzer+"_"+flavour+"_"+Analyzer
    #return histname
    histname = "FillEventCutflow/"+Analyzer+"_"+flavour + "_"+_id + "exo_17_028_dimu_same_sign";
    
    if flavour == "EE":
        histname = "FillEventCutflow/"+Analyzer+"_"+flavour+ "_"+_id + "exo_17_028_diel_same_sign";
    return histname

def GetHistNameSRMassBin(channel,SR, mass,year, _id,Analyzer):

    histname= SR
    histname+= "/"+ str(histname) +"_mn"+mass +"_nevent_"+str(Analyzer)+"_"+str(channel)+"_"+str(_id)+"_"
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

def GetSignalEffSRMassBin(channel,SR, mass,year, VBF,_id,Analyzer):

    num_histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)

    den_histname= GetHistNameNoCut(channel, _id,Analyzer)


    filepaths = []
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBF":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")
    else :
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
        if int(mass) > 250:
            filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")

    total=0

    for _filename in filepaths:
        _file = ROOT.TFile(_filename)
        if _file:
            hist=_file.Get(num_histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    no_cut=0.
    for _filename in filepaths:
        _file = ROOT.TFile(_filename)
        if _file:
            hist=_file.Get(den_histname)
            if hist:
                no_cut += hist.GetBinContent(1)
        _file.Close()
    return round((float(total)/float(no_cut)),4)

def GetSignalEventsSRMassBin(channel,SR, mass,year, VBF,_id,Analyzer):

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)

    filepaths = []
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBF":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")
    else :
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
        if int(mass) > 250:
            filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")

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

def GetFakeCountSRMassBin(channel, SR, mass,year,_id,Analyzer):
    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + "/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_Fake"+channel+".root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH")  + "/"+Analyzer+"/"+year + "/"+Analyzer+"_SkimTree_SSNonIso_FakeOS.root"  )


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


    return round(total,4)

def GetCFCountSRMassBin(channel,SR, mass,year,_id,Analyzer):

    if channel == "MuMu":
        return 0.

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH")+ "/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_CF.root"  )
    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH") +"/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_OSCF.root"  )



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
    return round(total,4)


def GetPromptCountSRMassBin(channel,SR, mass,year,_id,Analyzer):

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") +"/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_SSPrompt.root")

    else:
        filepaths.append(os.getenv("INFILE_MERGED_PATH") +"/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_OSPrompt.root")


    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()

    return round(total,4)

