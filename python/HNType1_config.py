import os,math

try:
    import ROOT
except ImportError:
    pass

def GetXSecUnityCoupling(mass, Sig):
    
    return 100*GetXSec(mass,Sig)

def GetXSec(mass, Sig):
    
    EXO17=True
    mass = float(mass)
    if Sig == "DY" and EXO17:
        
        if mass ==85:
            return 2.57E-01
        if mass ==90:
            return 1.54E-02

        if mass ==95:
            return 1.09E-01

        if mass ==100: 
            return 7.77E-02
        if mass ==125: 
            return 2.45E-02
        if mass ==150: 
            return 1.10E-02
        if mass ==200: 
            return 3.40E-03
        if mass ==250: 
            return 1.43E-03
        if mass ==300: 
            return 7.13E-04
        if mass ==400: 
            return 2.37E-04
        if mass ==500: 
            return 9.86E-05
        if mass ==600:
            return 4.72E-05
        if mass ==700: 
            return 2.47E-05
        if mass ==800: 
            return 1.38E-05
        if mass ==900: 
            return 8.11E-06
        if mass ==1000: 
            return 4.96E-06
        if mass ==1100: 
            return 3.12E-06
        if mass ==1200: 
            return 2.02E-06
        if mass ==1300: 
            return 1.33E-06
        if mass ==1400: 
            return 8.91E-07
        if mass ==1500: 
            return 6.05E-07
        if mass ==1700:
            return 3.9E-07


    if Sig == "VBF" and EXO17:
        if mass ==100: 
            return 9.65E-04
        if mass ==150: 
            return 4.91E-04
        if mass ==200: 
            return 3.28E-04
        if mass ==300: 
            return 1.83E-04
        if mass ==400: 
            return 1.16E-04
        if mass ==500: 
            return 7.81E-05
        if mass ==600: 
            return 5.50E-05
        if mass ==700: 
            return 3.98E-05
        if mass ==800: 
            return 2.94E-05
        if mass ==900: 
            return 2.22E-05
        if mass ==1000: 
            return 1.69E-05
        if mass ==1100: 
            return 1.30E-05
        if mass ==1200: 
            return 1.02E-05
        if mass ==1300: 
            return 7.94E-06
        if mass ==1400: 
            return 6.27E-06
        if mass ==1500: 
            return 5.00E-06
        if mass ==1700: 
            return 3.21E-06
        if mass ==2000: 
            return 1.69E-06
                
    return 0.

def GetColorByInt(x):

    import ROOT
    vCol = []
    vCol.append(ROOT.kRed)
    vCol.append(800)
    vCol.append(870)
    vCol.append(ROOT.kSpring-1)
    vCol.append(ROOT.kGray)
    vCol.append(ROOT.kViolet)
    vCol.append(ROOT.kYellow+4)
    vCol.append(ROOT.kCyan)
    vCol.append(ROOT.kBlue-2)
    vCol.append(ROOT.kGreen-2)
    vCol.append(ROOT.kGreen+2)
    vCol.append(ROOT.kOrange-2)
    

    if(x > len(vCol)):
        return ROOT.kBlack
    return vCol[x]


def GetColor(bkg):
    
    if bkg == "CF":
        return 74
    
    if bkg == "SSPrompt":
        return 8

    if bkg == "VV":
        return ROOT.kSpring-1

    if bkg == "WZ":
        return ROOT.kSpring-1

    if bkg == "ZZ":
        return ROOT.kBlue-1

    if "VVV" in bkg:
        return ROOT.kSpring+10

    if "XG" in bkg:
        return ROOT.kSpring-7

    if "ZG" in bkg:
        return ROOT.kSpring-7

    if "WG" in bkg:
        return ROOT.kGreen-7

    if "WJet"in bkg:
        return ROOT.kGreen

    if "Top" in bkg:
        return ROOT.kRed

    if "DY" in bkg:
        return ROOT.kYellow

    if "wwpp" in bkg:
        return ROOT.kGray

    if "fake" in bkg:
        return 870

    if "NonPrompt" in bkg:
        return 870
        
    if bkg == "total_background":
        return ROOT.kGreen+1
        
    if bkg == "TTLL":
        return ROOT.kRed

    if bkg == "TW":
        return ROOT.kGray
        
    print ("Failed to  find " + bkg)


def GetEXO_17_028_Masses(Channel, isString):
    

    masses = ["100",              "125",              "200",              "250",              "300",              "400",              "500",              "600",              "700",              "800",              "900",              "1000",              "1100",              "1200",              "1300",              "1400",              "1500", "1700" , "2000","2500","5000" , "10000"]

    masses_vbf =  [            "500",              "600",              "700",              "800",              "900",              "1000",              "1100",              "1200",              "1300",              "1400",              "1500", "1700" , "2000","2500","5000" , "10000"]

    MassList=masses
    if Channel == "TChannel":
        MassList=masses_vbf

    Masses_S = []    
    if isString:
        for m in MassList:
                Masses_S.append(float(m))
        else:
            Masses_S =MassList

    return MassList

def GetEXO_17_028_Events(channel,SR,mass):
    
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
            
    if channel == "ElEl":
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



def GetEXO_17_028_Eff(channel,SR,mass, Sig):
    
    effs=[]
    if Sig == "DY":

        if SR == "SR1":

            if channel == "MuMu":
                effs = [
                    ["85", 0.5],
                    ["90", 1.21],
                    ["100", 2.58],
                    ["125", 5.11],
                    ["150", 6.6],
                    ["200", 8.07],
                    ["250", 10.99],
                    ["300", 13.21],
                    ["400", 11.77],
                    ["500", 8.63],
                    ["600", 7.45],
                    ["700", 6.69],
                    ["800", 6.05],
                    ["900", 5.38],
                    ["1000", 4.59],
                    ["1100", 4.07],
                    ["1200", 3.59],
                    ["1300", 3.20],
                    ["1400", 2.75],
                    ["1500", 2.5],
                    ["1700", 1.85]]

            if channel == "ElEl":

                effs = [
                    ["85", 0.11],
                    ["90", 0.23],
                    ["100", 1.11],
                    ["125", 2.59],
                    ["150", 3.12],
                    ["200", 4.94],
                    ["250", 5.87],
                    ["300", 7.58],
                    ["400", 6.63],
                    ["500", 5.52],
                    ["600", 3.84],
                    ["700", 4.02],
                    ["800", 3.64],
                    ["900", 3.17],
                    ["1000", 2.64],
                    ["1100", 2.22],
                    ["1200", 1.97],
                    ["1300", 1.79],
                    ["1400", 1.47],
                    ["1500", 1.31],
                    ["1700", 0.87]]
            if channel == "MuEl":
        
                effs = [
                    ["85", 0.21],
                    ["90", 0.59],
                    ["100", 1.28],
                    ["125", 3.11],
                    ["150", 5.06],
                    ["200", 6.13],
                    ["250", 8.90],
                    ["300", 9.02],
                    ["400", 7.36],
                    ["500", 6.60],
                    ["600", 5.89],
                    ["700", 5.19],
                    ["800", 4.48],
                    ["900", 3.82],
                    ["1000", 3.37],
                    ["1100", 2.80],
                    ["1200", 2.45],
                    ["1300", 2.09],
                    ["1400", 1.81],
                    ["1500", 1.53],
                    ["1700", 1.25]]

        if SR == "SR2":

            if channel == "MuMu":

                effs = [
                    ["150", 0.28],
                    ["200", 1.43],
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
                    ["1500", 36.4],
                    ["1700", 29.0]]
                
                
            elif channel == "ElEl":

                effs = [
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
                    ["1500", 19.5],
                    ["1700", 14.45]]

            elif channel == "MuEl":

                effs = [
                    ["200", 0.86],
                    ["250", 1.74],
                    ["300", 4.44],
                    ["400", 11.79],
                    ["500", 16.7],
                    ["600", 20.2],
                    ["700", 25.0],
                    ["800", 26.1],
                    ["900", 25.6 ],
                    ["1000", 23.5],
                    ["1100", 26.86],
                    ["1200", 25.94],
                    ["1300", 27.12],
                    ["1400", 26.7],
                    ["1500", 21.6],
                    ["1700", 17.0]  ]

    if Sig == "VBF":


        if channel == "MuMu":

            if SR == "SR1":

                effs = [
                    ["300", 5.2],
                    ["400", 5.14],
                    ["500", 4.08],
                    ["600", 4.15],
                    ["700", 3.93],
                    ["800", 5.44],
                    ["900", 4.98],
                    ["1000", 4.24],
                    ["1100", 3.77],
                    ["1200", 3.43],
                    ["1300", 2.98],
                    ["1400", 2.68],
                    ["1500", 2.34],
                    ["1700", 1.85]]
                
            if SR == "SR2":

                effs = [
                    ["300", 0.73],
                    ["400", 2.72],
                    ["500", 6.78],
                    ["600", 20.44],
                    ["700", 24.66],
                    ["800", 24.93],
                    ["900", 26.92],
                    ["1000", 28.89],
                    ["1100", 29.23],
                    ["1200", 30.06],
                    ["1300", 30.65],
                    ["1400", 29.37],
                    ["1500", 29.98],
                    ["1700", 29.02]]



        if channel == "ElEl":

            if SR == "SR1":

                effs = [
                    ["300", 3.03],
                    ["400", 3.03],
                    ["500", 2.68],
                    ["600", 1.69],
                    ["700", 2.78],
                    ["800", 3.],
                    ["900", 2.86],
                    ["1000", 2.37],
                    ["1100", 2.],
                    ["1200", 1.82],
                    ["1300", 1.56],
                    ["1400", 1.31],
                    ["1500", 1.2],
                    ["1700", 0.87]]

            if SR == "SR2":

                effs = [
                    ["300", 0.81],
                    ["400", 2.71],
                    ["500", 5.17],
                    ["600", 13.21],
                    ["700", 17.59],
                    ["800", 18.3],
                    ["900", 18.5],
                    ["1000", 17.57],
                    ["1100", 19.56],
                    ["1200", 19.88],
                    ["1300", 20.75],
                    ["1400", 20.82],
                    ["1500", 18.04],
                    ["1700", 16.98]]


        if channel == "MuEl":

            if SR == "SR1":

                effs = [
                    ["300", 3.4],
                    ["400", 2.99],
                    ["500", 3.01],
                    ["600", 3.55],
                    ["700", 3.85],
                    ["800", 3.72],
                    ["900", 3.31],
                    ["1000", 3.03],
                    ["1100", 2.58],
                    ["1200", 2.26],
                    ["1300", 1.89],
                    ["1400", 1.70],
                    ["1500", 1.54],
                    ["1700", 1.25]]

            if SR == "SR2":

                effs = [
                    ["300", 0.81],
                    ["400", 2.71],
                    ["500", 5.17],
                    ["600", 13.21],
                    ["700", 17.59],
                    ["800", 18.3],
                    ["900", 18.5],
                    ["1000", 17.57],
                    ["1100", 19.56],
                    ["1200", 19.88],
                    ["1300", 20.75],
                    ["1400", 20.82],
                    ["1500", 18.04],
                    ["1700", 16.98]]


    for x in effs:
        if str(x[0]) == str(mass):
            return float(x[1])/float(100.)
    

    return 0

def GetEXO_17_028_BkgErr(channel,SR,mass, SIG):

    channels = ["MuMu","ElEl","MuEl"]
    SRs = ["Bin1", "Bin2","Combined"]
    SIGS = ["","_VBF","_VBFOnly"]
    if not channel in channels:
        print ("Error in GetEXO_17_028_Bkg : channel " )
        exit()

    if not SR in SRs:
        print ("Error in GetEXO_17_028_Bkg : SR " )
        exit()

    if not SIG in SIGS:
        print ("Error in GetEXO_17_028_Bkg : SIG " )
        exit()

    DATACARD_PATH=os.getenv("HNDILEPTONWORKSPACE_DIR") + "/Limits/DataCardsCutCount/EXO-17-028/2016/"+channel + "_"+SR + "/HN"+channel+"_"+mass + SIG + ".txt"

    if not os.path.exists(DATACARD_PATH):
        print(DATACARD_PATH + " does not exist")
        exit()


    lines_card = open(DATACARD_PATH).readlines()
    err_bkg=0
    for line in lines_card:
        word=line.split()
        if len(word) < 2:
            continue
        if str(word[1]) == "lnN":
            if not "-" in  word[2] :
                err_bkg= err_bkg + (1.-float(word[2]))*(1.-float(word[2]))
                
    err_bkg_final = math.sqrt(err_bkg)
    err_bkg_final = err_bkg_final * float(GetEXO_17_028_Bkg(channel,SR,mass, SIG))

    return err_bkg_final



def GetEXO_17_028_Bkg(channel,SR,mass, SIG):

    channels = ["MuMu","ElEl","MuEl"]
    SRs = ["Bin1", "Bin2","Combined"]
    SIGS = ["","_VBF","_VBFOnly"]
    if not channel in channels:
        print ("Error in GetEXO_17_028_Bkg : channel " )
        exit()

    if not SR in SRs:
        print ("Error in GetEXO_17_028_Bkg : SR " )
        exit()

    if not SIG in SIGS:
        print ("Error in GetEXO_17_028_Bkg : SIG " )
        exit()

    DATACARD_PATH=os.getenv("HNDILEPTONWORKSPACE_DIR") + "/Limits/DataCardsCutCount/EXO-17-028/2016/"+channel + "_"+SR + "/HN"+channel+"_"+mass + SIG + ".txt"
    
    if not os.path.exists(DATACARD_PATH):
        print(DATACARD_PATH + " does not exist")
        exit()
    

    lines_card = open(DATACARD_PATH).readlines()
    for line in lines_card:
        word=line.split()
        if word[0] == "rate":
            return str(float(word[1]) + float(word[2]) + float(word[3]))

    return 0
            


def GetEXO_17_028_Yield(channel,SR,mass,SIG):
    

    channels = ["MuMu","ElEl","MuEl"]
    SRs = ["Bin1", "Bin2","Combined"]
    SIGS = ["","_VBF","_VBFOnly"]
    if not channel in channels:
        print ("Error in GetEXO_17_028_Bkg : channel " )
        exit()
        
    if not SR in SRs:
        print ("Error in GetEXO_17_028_Bkg : SR " )
        exit()

    if not SIG in SIGS:
        print ("Error in GetEXO_17_028_Bkg : SIG " )
        exit()

    DATACARD_PATH=os.getenv("HNDILEPTONWORKSPACE_DIR") + "/Limits/DataCardsCutCount/EXO-17-028/2016/"+channel + "_"+SR + "/HN"+channel+"_"+mass + SIG + ".txt"

    if not os.path.exists(DATACARD_PATH):
        print(DATACARD_PATH + " does not exist")
        exit()


    lines_card = open(DATACARD_PATH).readlines()
    print ("Using " + DATACARD_PATH)
    NBkg=0
    for line in lines_card:
        word=line.split()
        if word[0] == "rate":
            NBkg=float(word[4])
    

    return NBkg 


def PrintList(_list):
    for x in _list:
        print (x)


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


def ChooseTag(channel):
    
    if channel == "Tchannel":
        return "_VBFOnly"
    elif channel == "Combinedchannel":
        return "_VBF"
    else:
        return "_DY"
        
def ChooseID(list1, list2, flavour,order_mu):
    if order_mu == 1:
        if flavour == "MuMu" or "SingleMuon":
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
                
    
#def GetHistNameSRHighMass(flavour,SR, mass,year, _id,Analyzer):
#    histname = SR+"_highmass/"+SR+"_highmass_njets_"+Analyzer+"_"+flavour + "_"+_id + "_"
#    return histname

#def GetHistNameNoCut(flavour,_id,Analyzer):#
#
#    #histname = "CutFlow/NoCut_"+Analyzer+"_"+flavour+"_"+Analyzer
#    #return histname
#    histname = "FillEventCutflow/"+Analyzer+"_"+flavour + "_"+_id + "exo_17_028_dimu_same_sign";
#    
#    if flavour == "EE":
#        histname = "FillEventCutflow/"+Analyzer+"_"+flavour+ "_"+_id + "exo_17_028_diel_same_sign";
#    return histname

#def GetHistNameSRMassBin(channel,SR, mass,year, _id,Analyzer):#
#
#    histname= SR
#    histname+= "/"+ str(histname) +"_mn"+mass +"_nevent_"+str(Analyzer)+"_"+str(channel)+"_"+str(_id)+"_"
#    return histname



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
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBFOnly":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")
    else :
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
        if int(mass) > 250:
            filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/"+year+"/SIG/"+Analyzer+"_HN_Tchannel_"+channel+"_"+mass+"_nlo.root")

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
    if VBF == "_DY":
        filepaths.append(os.getenv("INFILE_MERGED_PATH") + "/"+Analyzer+"/2016/SIG/"+Analyzer+"_HN_Schannel_"+channel+"_"+mass+"_nlo.root")
    elif VBF == "_VBFOnly":
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
        scale_ = 0.1
    elif int(mass) <= 700:
        scale_ = 1
    elif int(mass) <=1000:
        scale_ = 10.
    else:
        scale_ = 100.


    #since only 2016 samples available use these and scale to lumi for now                          \
                                                                                                     
    # effective lumi: 36.47 fb-1 (2016) 41.54 fb-1 (2017) 59.96 fb-1 (2018)                         \
                                                                                                     
    if year == "2017":
        scale_ = scale_* 41.54/36.47
    elif year == "2018":
        scale_ = scale_ *59.96/36.47

    return round(total*scale_,4)

def GetFakeCountSRMassBin(channel, SR, mass,year,_id,Analyzer):
    histname=GetHistNameSRMassBin(channel,SR, mass,year,_id,Analyzer)
    filepaths =[]
    if SR == "SR1" or SR == "SR2" or Analyzer == "HNtypeI_Dilepton":
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
        filepaths.append(os.getenv("INFILE_MERGED_PATH")+ "/"+Analyzer+"/"+ year + "/"+Analyzer+"_SkimTree_SSNonIso_CF.root"  )
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

