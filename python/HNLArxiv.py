import os,math

try:
    import ROOT
except ImportError:
    pass


class HNLArxiv():

    def __init__(self,MacroName,AnalysisCadi):
        self.MacroName=MacroName
        self.CADI=AnalysisCadi
        
        self.CheckCadi(AnalysisCadi)
        
        if AnalysisCadi == "EXO-17-028" or  "17028" in AnalysisCadi:
            self.IsEXO17028=True
        else:
            self.IsEXO17028=False
        if AnalysisCadi == "SNURun2":
            self.IsSNURun2=True
        else:
            self.IsSNURun2=False

        if AnalysisCadi == "EXO-21-003":
            self.IsPeking=True
        else:
            self.IsPeking=False


        self.DoDebug=False
        
        print("Callling HNLArxiv from " + MacroName)
        print("Accessing stored results from {0} to use in plotting classes".format(self.CADI))

    def Debug(self):
        self.DoDebug=True

    def CheckCadi(self, CADINUMER):
        cadis=["EXO-17-028","EXO-21-003","SNURun2"]
        
        if not CADINUMER in cadis:
            print("CADI Number is incorrect... Possible inputs are:")
            for x in cadis:
                print(x)
            exit()
        return
            
    def GetXSecUnityCoupling(self,_Mass,_Process ):

        if self.DoDebug:
            print("HNLArxiv:GetXSecUnityCoupling : Mass={0},Signal Process={1}".format(_Mass,_Process))

        Xsec=-999
        if self.IsEXO17028:
            # EXO-17-028 xsec are stored using V^2 = 0.01 so * 100: ALso samples are SS mumu/ee only
            # XSEC ion AN is also for OS+SS so in this class XSEC  are already scaled by 0.5

            Xsec=100*self.GetXSec(_Mass,_Process)

        if self.IsPeking:
            Xsec=self.GetXSec(_Mass,_Process)

        if self.IsSNURun2:
            Xsec=self.GetXSec(_Mass,_Process)

        return Xsec



    ################ XSEC #####################################

    def GetXSec(self,_Masss,_Process):

        if self.DoDebug:
            print("Accessing xsec used in {0} for mass {1} and proccess {2}".format(self.CADI, _Masss,_Process))

        float_mass = float(_Masss)
        # XSEC for EXO-17-028 are obtained from AN * 0.5 to get SS only

        if _Process == "DY" and self.IsEXO17028:
            if float_mass ==85:
                return 2.57E-01
            if float_mass ==90:
                return 1.54E-02
            if float_mass ==95:
                return 1.09E-01
            if float_mass ==100:
                return 7.77E-02
            if float_mass ==125:
                return 2.45E-02
            if float_mass ==150:
                return 1.10E-02
            if float_mass ==200:
                return 3.40E-03
            if float_mass ==250:
                return 1.43E-03
            if float_mass ==300:
                return 7.13E-04
            if float_mass ==400:
                return 2.37E-04
            if float_mass ==500:
                return 9.86E-05
            if float_mass ==600:
                return 4.72E-05
            if float_mass ==700:
                return 2.47E-05
            if float_mass ==800:
                return 1.38E-05
            if float_mass ==900:
                return 8.11E-06
            if float_mass ==1000:
                return 4.96E-06
            if float_mass ==1100:
                return 3.12E-06
            if float_mass ==1200:
                return 2.02E-06
            if float_mass ==1300:
                return 1.33E-06
            if float_mass ==1400:
                return 8.91E-07
            if float_mass ==1500:
                return 6.05E-07
            if float_mass ==1700:
                return 2.9E-07
            if float_mass ==2000:
                return 1.025E-07

            print("Mass {0} not available ".format(float_mass))
            return -999

        if _Process == "VBF" and self.IsEXO17028:
            if float_mass ==100:
                return 0.5* 9.65E-04
            if float_mass ==150:
                return 0.5* 4.91E-04
            if float_mass ==200:
                return 0.5* 3.28E-04
            if float_mass ==300:
                return 0.5* 1.83E-04
            if float_mass ==400:
                return 0.5* 1.16E-04
            if float_mass ==500:
                return 0.5* 7.81E-05
            if float_mass ==600:
                return 0.5* 5.50E-05
            if float_mass ==700:
                return 0.5* 3.98E-05
            if float_mass ==800:
                return 0.5* 2.94E-05
            if float_mass ==900:
                return 0.5* 2.22E-05
            if float_mass ==1000:
                return 0.5* 1.69E-05
            if float_mass ==1100:
                return 0.5* 1.30E-05
            if float_mass ==1200:
                return 0.5* 1.02E-05
            if float_mass ==1300:
                return 0.5* 7.94E-06
            if float_mass ==1400:
                return 0.5* 6.27E-06
            if float_mass ==1500:
                return 0.5* 5.00E-06
            if float_mass ==1700:
                return 0.5* 3.21E-06
            if float_mass ==2000:
                return 0.5* 1.69E-06
            print("Mass {0} not available ".format(float_mass))
            return -999


        if _Process == "SSWW" and self.IsEXO17028:
            print "No xsec for SSWW signals in EXO17028"
            print("Mass {0} not available ".format(float_mass))
            return -999

        if self.IsSNURun2:
            InputXsec=os.getenv("HNDILEPTONWORKSPACE_DIR")+"/data/Run2UltraLegacy_v3/Xsecs/xsec_Private_MuMu_NLO_"+_Process+".txt"
            fXsec = open(InputXsec, "r")
            for x in fXsec:
                split_line = x.split()
                if len(split_line) == 2:
                    if str(int(float_mass)) == split_line[0]:
                        return split_line[1]
            fXsec.Close()

            print ("TEST {0} :  {1}".format(_Process,self.CADI))
            print("Mass {0} not available ".format(float_mass))
            return -999


        if _Process == "SSWW" and self.IsPeking:
            InputXsec=os.getenv("HNDILEPTONWORKSPACE_DIR")+"/data/Run2UltraLegacy_v3/Xsecs/xsec_Private_MuMu_NLO_"+_Process+".txt"
            fXsec = open(InputXsec, "r")
            for x in fXsec:
                split_line = x.split()
                if len(split_line) == 2:
                    if str(int(float_mass)) == split_line[0]:
                        return split_line[1]
            fXsec.Close()

            print ("TEST {0} :  {1}".format(_Process,self.CADI))
            print("Mass {0} not available ".format(float_mass))
            return -999


        if _Process == "SSWW" and self.IsSNURun2:
            print ("TEST {0} :  {1}".format(_Process,self.CADI))
            print("Mass {0} not available ".format(float_mass))
            return -999

        if _Process == "SSWW" and self.IsPeking:
            print ("TEST {0} :  {1}".format(_Process,self.CADI))
            print("Mass {0} not available ".format(float_mass))
            return -999




        return 0.


    ################ Limits #####################################                                                                                                                                                   
    def GetLimits(self, Type="obs"):
        observed = []
        _2sigma_low = []
        _1sigma_low = []
        _expected = []
        _1sigma_high = []
        _2sigma_high = []
        if self.IsPeking:
            observed =[0.0632,0.0125,0.0070,0.0061,0.0060,0.0066,0.0067,0.0075,0.0086,0.0098,0.0117,0.0136,0.0189,0.0539,0.1081,0.1908,0.4021,0.7433,1.1322]
            _2sigma_low=[0.0487,0.0100,0.0060,0.0048,0.0048,0.0050,0.0053,0.0057,0.0071,0.0081,0.0092,0.0111,0.0154,0.0438,0.0877,0.1552,0.3264,0.6055,0.9196]
            _1sigma_low=[0.0668,0.0141,0.0076,0.0072,0.0068,0.0075,0.0071,0.0086,0.0102,0.0113,0.0132,0.0152,0.0213,0.0609,0.1220,0.2158,0.4540,0.8421,1.2790]
            _expected=[0.0981,0.0200,0.0112,0.0103,0.0103,0.0107,0.0112,0.0122,0.0142,0.0161,0.0190,0.0229,0.0317,0.0903,0.1812,0.3203,0.6738,1.2500,1.8984]
            _1sigma_high=[0.1459,0.0306,0.0173,0.0152,0.0152,0.0166,0.0166,0.0188,0.0218,0.0251,0.0297,0.0343,0.0477,0.1368,0.2757,0.4863,1.0257,1.9027,2.8822]
            _2sigma_high=[0.2096,0.0443,0.0255,0.0224,0.0224,0.0239,0.0243,0.0274,0.0321,0.0367,0.0433,0.0501,0.0702,0.2014,0.4058,0.7168,1.5094,2.8000,4.2485]
            
            Masses=self.GetMassList("SSWW")
            
            for M in range(0,len(Masses)):
                print ("Mass {0} : exp limit = {1}  obs limit = {2}".format(Masses[M], _expected[M], observed[M]))

            if Type == "obs":
                return [Masses, observed]
                
            if Type == "exp":
                return [Masses, _expected]

            if Type == "2sigma":
                return [Masses, _2sigma_high]
            if Type == "1sigma":
                return [Masses, _1sigma_high]
            if Type == "-1sigma":
                return [Masses, _1sigma_low]
            if Type == "-2sigma":
                return [Masses, _2sigma_low]

                
        if self.IsEXO17028:
            print("Gte limits from /gv0/archive/Users/jskim/EXO-17-028/HN_dilepton_plotter/rootfiles/v8-0-7.38/Limit")

                
    ################ Signal Efficiency #####################################                                                                                                                                                   

    def GetEXO_17_028_Eff(self,_Channel,_SignalRegion,_Mass, _Process):
        
        if self.DoDebug:
            print("HNLArxiv:GetEXO_17_028_Eff : Channel={0},SignalRegion={1}, Mass={2},Process={3} ".format(_Channel,_SignalRegion,_Mass, _Process))
        
        effs=[]
        if _Process == "DY":
            if _SignalRegion == "SR1":
                if _Channel == "MuMu":
                    effs = [["85", 0.5],
                            ["90", 1.21],
                            ["100", 2.58],
                            ["125", 5.11],
                            ["150", 6.6],
                            ["200", 8.07],
                            ["250", 10.99],
                            ["300", 13.21],
                            ["400", 11.77],
                            ["500", 8.63],
                            ["600", 7.4],
                            ["700", 6.69],
                            ["800", 6.05],
                            ["900", 5.38],
                            ["1000", 4.59],
                            ["1100", 4.07],
                            ["1200", 3.59],
                            ["1300", 3.20],
                            ["1400", 2.75],
                            ["1500", 2.5],
                            ["1700", 1.85],
                            ["2000", 1.6]]

                if _Channel == "ElEl":
                    effs = [["85", 0.11],
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
                            ["1700", 0.87], 
                            ["2000", 0.6]] 

                if _Channel == "MuEl":
                    effs = [["85", 0.21],
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
                            ["1200", 2.4],
                            ["1300", 2.09],
                            ["1400", 1.81],
                            ["1500", 1.53],
                            ["1700", 1.25],
                            ["2000", 0.9]]

            if _SignalRegion == "SR2":
                if _Channel == "MuMu":
                    effs = [["85", 0.001],
                            ["90", 0.003],
                            ["100", 0.08],
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
                            ["1700", 29.0],
                            ["2000", 29.0]]
                    
                    
                elif _Channel == "ElEl":
                    
                    effs = [["85", 0.001],
                            ["95", 0.003],
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
                            ["1500", 19.5],
                            ["1700", 14.45],
                            ["2000", 14.45]]
                    
                elif _Channel == "MuEl":
                    
                    effs = [                       
                        ["85", 0.001],
                        ["90", 0.003],
                        ["100", 0.009],
                        ["125", 0.003],
                        ["250", 0.14],
                        ["200", 0.86],
                        ["250", 1.74],
                        ["300", 4.44],
                        ["400", 11.8],
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
                        ["1700", 19.8],
                        ["2000", 17.0]]
                    
        if _Process == "VBF":
                            
            
            if _Channel == "MuMu":

                if _SignalRegion == "SR1":
                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
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
                        ["1700", 1.85],
                        ["2000", 1.85]]
                    
                if _SignalRegion == "SR2":

                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
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
                        ["1700", 29.02],
                        ["2000", 29.02]]

            if _Channel == "ElEl":
                                
                if _SignalRegion == "SR1":

                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
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
                        ["1700", 0.87],
                        ["2000", 0.87]]
                    
                if _SignalRegion == "SR2":

                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
                        ["300", 0.6],
                        ["400", 2.9],
                        ["500", 6.1],
                        ["600", 11.0],
                        ["700", 13.1],
                        ["800", 14.],
                        ["900", 13.2],
                        ["1000", 15.3],
                        ["1100", 14.7],
                        ["1200", 15.3],
                        ["1300", 15.5],
                        ["1400", 15.1],
                        ["1500", 15.2],
                        ["1700", 15.2],
                        ["2000", 15.2]]


            if _Channel == "MuEl":

                if _SignalRegion == "SR1":

                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
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
                        ["1700", 1.25],
                        ["2000", 1.25]]

                if _SignalRegion == "SR2":

                    effs = [
                        ["85", 0],
                        ["90", 0],
                        ["100",0],
                        ["125", 0],
                        ["150", 0],
                        ["200", 0],
                        ["250", 0],
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
                        ["1700", 16.98],
                        ["2000", 16.98]]
                    

        for x in effs:
            if str(x[0]) == str(_Mass):
                if self.DoDebug:
                    print ("Efficiency={0}".format(float(x[1])/float(100.)))
                return float(x[1])/float(100.)

        return 0


    def GetEXO_17_028_BkgErr(self,channel,SR,mass, SIG):

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
        err_bkg_final = err_bkg_final * float(self.GetEXO_17_028_Bkg(channel,SR,mass, SIG))

        return err_bkg_final





    def GetEXO_17_028_Bkg(self,channel,SR,mass, SIG):

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


    def GetEXO_17_028_Yield(self,channel,SR,mass,SIG):


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




    def GetSigScaleFactorForLimitCalc(self,_mass):
        
        ####### convert signal yield to a value ~ 10 events                                                                                                                                                                                                                                            
        if(float(_mass) >= 1000):
            return 1
        if(float(_mass) == 100):
            return 0.001
        if(float(_mass) == 400):
            return 0.1
        return 1


    def CalculdateSignificance(seld,method,Nsig, Nbkg,scaleSig):
    
        Nsig = Nsig*scaleSig
        ###### set Neg bins to 0                                                                                                                                                        
        if Nsig < 0:
            Nsig = 0
        if Nbkg < 0.1:
            Nbkg=0.1
                
        Signi=0.
        if method == "SB":
            Signi=Nsig/ math.sqrt(Nbkg +1)

        if method == "Punzi":
            Signi= Nsig / ( 1 + math.sqrt(float(Nbkg)))

        if method == "Azimoth":
            Signi=  math.sqrt(2* ((Nsig+Nbkg)*math.log(1+(Nsig/Nbkg)) -Nsig ) )

        return Signi /scaleSig


    def PekingBkg(Year):

        if Year == 2016:
            return 1.52

        if Year == 2017:
            return 3.4

        if Year == 2018:
            return 1.94
            

    def Get_PekingXsec(Year, Mass):
        
        Scale=0.9
        if Year == 2016:
            if Mass == 500:
                return Scale*17.66
            if Mass == 600:
                return Scale*16.26
            if Mass == 750:
                return Scale*15.05
            if Mass == 900:
                return Scale*13.48
            if Mass == 1000:
                return Scale*12.36
            if Mass == 1250:
                return Scale*10.12
            if Mass == 1500:
                return Scale*8.598
            if Mass == 1750:
                return Scale*7.3
            if Mass == 2000:
                return Scale*6.264
            if Mass == 2500:
                return Scale*4.602
            if Mass == 5000:
                return Scale*1.536
            if Mass == 7500:
                return Scale*0.7521
            if Mass == 10000:
                return Scale*0.3977
            if Mass == 15000:
                return Scale*0.202
            if Mass == 20000:
                return Scale*0.1089
        else:
            if Mass == 500:
                return Scale*18.2
            if Mass == 600:
                return Scale*16.91
            if Mass == 750:
                return Scale*15.47
            if Mass == 900:
                return Scale*13.86
            if Mass == 1000:
                return Scale*12.84
            if Mass == 1250:
                return Scale*10.67
            if Mass == 1500:
                return Scale*8.918
            if Mass == 1750:
                return Scale*7.612
            if Mass == 2000:
                return Scale*6.425
            if Mass == 2500:
                return Scale*4.811
            if Mass == 5000:
                return Scale*1.598
            if Mass == 7500:
                return Scale*0.773
            if Mass == 10000:
                return Scale*0.448
            if Mass == 15000:
                return Scale*0.205
            if Mass == 20000:
                return Scale*0.1165

                
    def Get_PekingEff(Year, Mass):
       
        Scale =1
        if Year == 2017:
            Scale =1.15
        if Year == 2018:
            Scale =1.1
 

        if Mass ==  500:
            return Scale*0.28
        if Mass ==  600:
            return Scale*0.31
        if Mass ==  750:
            return Scale*0.326
        if Mass == 900:
            return Scale*0.335
        if Mass == 1000:
            return Scale*0.34
        if Mass == 1250:
            return Scale*0.345
        if Mass ==  1500:
            return Scale*0.35

        if Mass == 1750:
            return Scale*0.352

        if Mass == 2000:
            return Scale*0.353
                
        if Mass == 2500:
            return Scale*0.355
        if Mass ==  5000:
            return Scale*0.361 

        else  return Scale*0.361


        
    def GetSignalSignificance(self,_Channel,_Mass, scX,FinalScale):
        if self.IsEXO17028:
            return self.GetSignificanceEXO_17_028(_Channel,_Mass, scX,FinalScale)
        if self.IsPeking:
            return self.GetSignificancePeking(_Mass, scX,FinalScale*FinalScale)

    def GetSignificancePeking(self,_Mass,scX,Year):
        
        _DMass = float(_Mass)

        print("Running GetSignificnace PEKING for mass " + _Mass)
        

        SignifianceAz = 0.
        SignifianceSB = 0.
        SignifianceP = 0.

        print ("GetSignificnacePEKING: Mass [" + _Mass+"]")

        
        nBkg    = float(self.PekingBkg(Year))
        nBkgErr = nBkg * 0.3
        nSig    = float(self.Get_PekingEff(Year,Mass) * self.Get_PekingXsec(Year,Mass))
        

        if self.DoDebug:
            print("SSWW GetEXO_21_003_Eff = " + str(float(self.Get_PekingEff(Year,Mass))))
            print("SSWW GetXSecUnityCoupling = "+str(self.Get_PekingXsec(Year,Mass)))
            

            if nBkg> 0 :
                SignifianceAz = SignifianceAz   +  self.CalculdateSignificance("Azimoth",float(nSig),nBkg, scX)
                SignifianceSB = SignifianceSB   +  self.CalculdateSignificance("SB",float(nSig),nBkg,scX)
                SignifianceP  = SignifianceP    +  self.CalculdateSignificance("Punzi",float(nSig),nBkg,scX)

            print("_"*60)
            print  (SignalRegion + " NSig = " + str(nSig ) + " NBkg="  + str(nBkg) + " +/- " + str(nBkgErr))

            print ("Muon " + str(_Mass) + " Azimoth   = " + str(round(SignifianceAz,3)))
            print ("Muon " + str(_Mass) + " s/sqrt(B) = " + str(round(SignifianceSB,3)))
            print ("Muon " + str(_Mass) + " Punzi     = " + str(round(SignifianceP,3)))

        return [["Azimoth",SignifianceAz], ["SB",SignifianceSB],["Punzi",SignifianceP]]



    def GetSignalYields(self,_Channel,_Mass,FinalScale):

        _DMass = float(_Mass)

        print("Running GetSignificnaceEXO_17_028 for mass " + _Mass)

        SignalRegions = ["Bin1", "Bin2"]

        nSigs=[]
        for SignalRegion in SignalRegions:

            Bin = SignalRegion
            Bin = Bin.replace('Bin','SR')

            nSigs.append(36500*FinalScale*float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"DY")* self.GetXSecUnityCoupling(_DMass,"DY") +
                                                self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"VBF")*self.GetXSecUnityCoupling(_DMass,"VBF")))
            
        return nSigs

    def GetSignalRegionYields(self,_Channel,_Mass,FinalScale):

        _DMass = float(_Mass)

        print("Running GetSignificnaceEXO_17_028 for mass " + _Mass)

        SignalRegions = ["Bin1", "Bin2"]

        nSigsDY=[]
        nSigsVBF=[]

        for SignalRegion in SignalRegions:

            Bin = SignalRegion
            Bin = Bin.replace('Bin','SR')
            
            nSigsDY.append(36500*FinalScale*float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"DY")* self.GetXSecUnityCoupling(_DMass,"DY")))
            nSigsVBF.append(36500*FinalScale*float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"VBF")*self.GetXSecUnityCoupling(_DMass,"VBF")))




        return [nSigsDY, nSigsVBF]



    def GetBkgYields(self,_Channel,_Mass):

        _DMass = float(_Mass)

        print("Running GetSignificnaceEXO_17_028 for mass " + _Mass)
        SignalRegions = ["Bin1", "Bin2"]

        nBkgs=[]

        for SignalRegion in SignalRegions:

            Bin = SignalRegion
            Bin = Bin.replace('Bin','SR')

            nBkgs.append(float(self.GetEXO_17_028_Bkg(_Channel, SignalRegion , _Mass, "" )))
            
        return nBkgs


        
    def GetSignificanceEXO_17_028(self,_Channel,_Mass, scX, FinalScale):
        
        _DMass = float(_Mass)
        
        print("Running GetSignificnaceEXO_17_028 for mass " + _Mass)
        
        #### SR1 in 2016 was AK4 SR2 was AK8 .....                                                                                                                                                                                                                                                     
        SignalRegions = ["Bin1", "Bin2"]
        
        ##### check 3 types of significance                                                                                                                                                                                                                                                            
        SignifianceAz = 0.
        SignifianceSB = 0.
        SignifianceP = 0.
        
        print ("GetSignificnaceEXO_17_028: Mass [" + _Mass+"]")

        for SignalRegion in SignalRegions:

            Bin = SignalRegion
            Bin = Bin.replace('Bin','SR')
            
            nBkg    = float(self.GetEXO_17_028_Bkg(_Channel, SignalRegion , _Mass, "" ))
            nBkgErr = self.GetEXO_17_028_BkgErr(_Channel, SignalRegion , _Mass, "" ) + 0.2 
            nSig    = float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"DY")* self.GetXSecUnityCoupling(_DMass,"DY") + self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"VBF")*self.GetXSecUnityCoupling(_DMass,"VBF"))
            nSig = nSig*FinalScale
            if self.DoDebug:
                print("DY GetEXO_17_028_Eff = " + str(float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"DY"))))
                print("DY GetXSecUnityCoupling = "+str(self.GetXSecUnityCoupling(_DMass,"DY")))
                print("VBF GetEXO_17_028_Eff = " + str(float(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"VBF"))))
                print("VBF GetXSecUnityCoupling = "+str(self.GetXSecUnityCoupling(_DMass,"VBF")))
                
            
            print (SignalRegion + " DY Efficiency = " + str(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"DY")) + " Xsec= " + str(self.GetXSecUnityCoupling(_DMass,"DY")) + " VBF Eff = " + str(self.GetEXO_17_028_Eff(_Channel, Bin, _Mass,"VBF")) + " Xsec= " + str(self.GetXSecUnityCoupling(_DMass,"VBF")))
            
            ####### convert efficiency to number                                                                                                                                                                                                                                                       
            nSig =nSig*36500 
            if self.DoDebug:
                print("NSig = nSig*36500 * couplingSF = " + str(nSig) )

            if nBkg> 0 :
                SignifianceAz = SignifianceAz   +  self.CalculdateSignificance("Azimoth",float(nSig),nBkg, scX)
                SignifianceSB = SignifianceSB   +  self.CalculdateSignificance("SB",float(nSig),nBkg,scX)
                SignifianceP  = SignifianceP    +  self.CalculdateSignificance("Punzi",float(nSig),nBkg,scX)

            print("_"*60)
            print  (SignalRegion + " NSig = " + str(nSig ) + " NBkg="  + str(nBkg) + " +/- " + str(nBkgErr))
            
            print ("Muon " + str(_Mass) + " Azimoth   = " + str(round(SignifianceAz,3)))
            print ("Muon " + str(_Mass) + " s/sqrt(B) = " + str(round(SignifianceSB,3)))
            print ("Muon " + str(_Mass) + " Punzi     = " + str(round(SignifianceP,3)))
            
        return [["Azimoth",SignifianceAz], ["SB",SignifianceSB],["Punzi",SignifianceP]]




    def GetMassList(self,Process):
        
        neutrino_massDY=[]
        neutrino_massVBF=[]
        neutrino_massSSWW=[]

        if self.IsEXO17028:
            
            neutrino_massDY = [85,90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400,1500, 1700]
            neutrino_masses_vbf =  [500,  600,  700,  800,  900,  1000,  1100,  1200,  1300,  1400,        1500, 1700]
            
        if self.IsSNURun2:
                    
            neutrino_massDY = [85,90,100, 125,  200,  250,  300,  400,  500,  600,  700,  800,   900,  1000,  1100,  1200,  1300,  1400,  1500, 1700 , 2000,2500,3000]
            neutrino_massVBF =  [500,  600,  700,  800,  900,  1000,  1100,  1200,  1300,  1400, 1500, 1700 , 2000,2500,3000]
            neutrino_massSSWW = [500,  600,  700,  800,  900,  1000,  1100,  1200,  1300,  1400, 1500, 1700 , 2000,2500,3000,5000,7500,10000,15000,20000]

        if self.IsPeking:
            neutrino_massSSWW=[50,150,300,450,600,750,900,1000,1250,1500,1750,2000,2500,5000,7500,10000,15000,20000,25000]
            
            
        MassList=neutrino_massDY
        if Process == "TChannel" or Process == "VBF":
            MassList=neutrino_massVBF
        if Process == "SSWW":
            MassList=neutrino_massSSWW
                
        return MassList

