import os,math

try:
    import ROOT
except ImportError:
    pass


def PrintList(_list):
    for x in _list:
        print (x)


def ChooseTag(channel):
   
    if channel == "Tchannel":
        return "_VBFOnly"
    elif channel == "Combinedchannel":
        return "_Combined"
    else:
        return "_DY"

def ChooseMassList(list1, list2,list3, channel,order_sc):

    if order_sc == 1:
        if channel == "Combinedchannel":
            return list3
        elif channel == "Tchannel":
            return list2
        else:            
            return list1
    else:
        if channel == "Combinedchannel":
            return list3
        elif channel == "Tchannel":
            return list1
        else:
            return list2

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
    elif len(lists) == 5:
        niter = NIteration(lists)
        return SumIteration5(i, lists[0],lists[1],lists[2],lists[3],lists[4],niter)

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


def SumIteration5(i, list1, list2, list3,list4,list5,nmax):

    iter_1=0
    iter_2=0
    iter_3=0
    iter_4=0
    iter_5=0

    for x in range(0, nmax):
        if x == i :
            return [list1[iter_1],list2[iter_2],  list3[iter_3] , list4[iter_4], list5[iter_5] ]


        iter_5=iter_5+1
        if iter_5 == len(list5):
            iter_5=0
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


    return ["","","","",""]

def PrintSetup(setupconfig):

    for x in setupconfig:
        if len(x) == 2:
            if len(str(x[1])) < 75:
                print (str(x[0]) + " "*(20-len(str(x[0]))) +" : "+ str(x[1]))
            else:
                print str(x[0]) + " "*(20-len(str(x[0]))) +" : "+ str(x[1])[0:75]
                print " "*(20) +" : "+ str(x[1])[75:150]
        else:
            print "Error in PrintSetup"
            exit()
    
def GetCentralConfig(scriptname, tag, configfile,_setup):

    list_channels=[]
    _config = open(configfile,"r")
    is_config_setup=False

    # first look if var is specified for the script, which is taken over global var
    for line in _config:
        if "#" in line:
            continue

        if tag in line:
            if len(line.split()) == 4:
                if scriptname+":" != line.split()[0]:
                    continue

                _tmp_line=line.split()[3]
                is_config_setup=True
                _tmp_line=_tmp_line.replace(","," ")
                _tmp_line=_tmp_line.split()
                for x in _tmp_line:
                    list_channels.append(x)

    if is_config_setup:
        _setup.append([tag,list_channels])
        return list_channels
    
    # now check global var
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

def GetConfig(tag, configfile,_setup):

    list_channels=[]
    _config = open(configfile,"r")
    is_config_setup=False
    for line in _config:
        if "#" in line:
            continue
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


def GetCentralSConfig(scriptname, tag, configfile,_setup):

    list_channels=[]
    _config = open(configfile,"r")
    is_config_setup=False

    for line in _config:
        if tag in line:
            if len(line.split()) == 4:
                if scriptname+":" != line.split()[0]:
                    continue
                _tmp_line=line.split()[3]
                is_config_setup=True
                _tmp_line=_tmp_line.replace(","," ")
                _tmp_line=_tmp_line.split()
                for x in _tmp_line:
                    list_channels.append(x)

    if is_config_setup:
        _setup.append([tag,list_channels])
        return list_channels[0]

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

def GetSConfig(tag, configfile,_setup):
    
    list_channels=[]
    _config = open(configfile,"r")
    is_config_setup=False
    for line in _config:
	if "#" in line:
            continue

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
                
    
def MakeDirectory(dirname):
    os.system("mkdir -p " +dirname)

#def GetHistNameSRHighMass(flavour,SR, mass,year, _id,Analyzer):
#    histname = SR+"_highmass/"+SR+"_highmass_njets_"+Analyzer+"_"+flavour + "_"+_id + "_"
#    return histname

def GetHistNameNoCut(flavour,_id,Analyzer):#

    histname = flavour+"_NoCut"
    return histname

def GetHistNameSRMassBin(channel,SR, mass,year, _id,Analyzer):#

    histname= "EXO17028_"+channel + "/EXO17028/HNL_"+SR+"_17028"
    if channel == "EE":
        if SR == "SR1":
            histname+= "/_mn"+mass +"_nevent"
        else:
            histname+= "/mn"+mass +"_nevent"
    else:
        histname+= "/mn"+mass +"_nevent"

    return histname



def GetMassList(_era):

    #Get List of masses available

    SampleList= []
    with open(os.getenv('SKFlat_WD')+'/data/'+os.getenv('SKFlatV')+'/'+str(_era)+'/Sample/SampleSummary_Signal_Type1.txt','r') as f:
        for line in f:
            if len(line.split())>0:
                signame=line.split()[0]
                if not 'private' in signame:
                    continue
                if not 'Type' in signame:
                    continue
                signame=signame.replace('SSWWTypeI','')
                signame=signame.replace('DYTypeI','')
                signame=signame.replace('VBFTypeI','')
                signame=signame.replace('_SF_M','')
                signame=signame.replace('_DF_M','')
                signame=signame.replace('_private','')
                if not signame in SampleList:
                    SampleList.append(signame)

    return SampleList

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
              "1500"]

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
              "1500"]

    counter = 0
    _masses= masses
    if VBF == "_VBFOnly":
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
    filepaths.append(os.getenv("FILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_MN"+mass+".root")

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
    return round((float(2.*total)/float(no_cut)),4)


def GetSignalEventsShape(histname,flavour,SR, mass,year, channel,_id,_var,analyzername):


    filepath = os.getenv("DATACARD_SHAPE_PATH") + "/" + analyzername+"/"+ year + "/" + flavour + "_"+ SR + "/HN_"+channel+"_"+ mass + "_highmass_Run2UltraLegacy_v3_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+ _var+".root"

    total=0

    _file = ROOT.TFile(filepath)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    if total < 0:
        return 0.

    return round(total,4)



def GetCountShape(channel,histname,flavour,SR, mass,year,_id,_var,analyzername):

    filepath =  os.getenv("DATACARD_SHAPE_PATH") + "/" + analyzername+"/"+year + "/" + flavour + "_"+ SR + "/HN_"+channel+"_"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root"
    total=0
    _file = ROOT.TFile(filepath)
    if _file:
        hist=_file.Get(histname)
        if hist:
            total += hist.Integral()
    _file.Close()

    return round(total,4)




def GetSignalEventsSRMassBin(channel,SR, mass,year, VBF,_id,Analyzer):

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)

    filepaths = []
    filepaths.append(os.getenv("FILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_MN"+mass+".root")

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
    if int(mass) <= 100:
        scale_ = 0.1
    elif int(mass) <= 300:
        scale_ = 1
    elif int(mass) <=700:
        scale_ = 10.
    else:
        scale_ = 100.

    scale_ = scale_ * 0.0001

    #since only 2016 samples available use these and scale to lumi for now                          \
                                                                                                     
    # effective lumi: 36.47 fb-1 (2016) 41.54 fb-1 (2017) 59.96 fb-1 (2018)                         \
                                                                                                     
    #if year == "2017":
    #    scale_ = scale_* 41.54/36.47
    #elif year == "2018":
    #    scale_ = scale_ *59.96/36.47

    return round(total*scale_,4)

def GetFakeCountSRMassBin(channel, SR, mass,year,_id,Analyzer):
    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2" or Analyzer == "HNtypeI_Dilepton":
        filepaths.append(os.getenv("FILE_MERGED_PATH")  + "/"+Analyzer+"/"+ year + "/"+Analyzer+"_NonPrompt.root"  )


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


def GetVariableName(_var, signalregion):
    _vartmp = _var
    if signalregion == "SR2":
        _vartmp=_vartmp.replace('jj','J')
    if signalregion == "SR4":
        _vartmp=_vartmp.replace('jj','J')

    return _vartmp
    
    

def GetCFCountSRMassBin(channel,SR, mass,year,_id,Analyzer):

    if channel == "MuMu":
        return 0.

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2":
        filepaths.append(os.getenv("FILE_MERGED_PATH")+ "/"+Analyzer+"/"+ year + "/"+Analyzer+"_CF.root"  )
    else:
        return 0.



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

    # 0.72 got by scaling 2016 value to EXO-17028
    return round(total,4)


def GetPromptCountSRMassBin(channel,SR, mass,year,_id,Analyzer):

    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    filepaths.append(os.getenv("FILE_MERGED_PATH") +"/"+Analyzer+"/"+ year + "/"+Analyzer+"_Prompt.root")
    
    print (os.getenv("FILE_MERGED_PATH") +"/"+Analyzer+"/"+ year + "/"+Analyzer+"_Prompt.root")
    print (histname)

    total=0
    for f in filepaths:
        _file = ROOT.TFile(f)
        if _file:
            hist=_file.Get(histname)
            if hist:
                total += hist.Integral()
        _file.Close()
    print(str(total))

    return round(total,4)

