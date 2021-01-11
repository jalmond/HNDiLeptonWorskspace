import os,sys

sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *


years =["2016"]
tag="Run2Legacy_v4"
Flavour =[ ["MuMu", ["MumMum" , "MupMup"]],
           ["EE"  , ["EmEm","EpEp"]]]

Channels=["Schannel"]
masses_s = ["100","125","200","250","300","400", "500", "600","700","800","900","1000","1100","1200","1300","1400","1500","1700","2000"]
masses_t = ["300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1700","2000"]

Charge= ["Signal__/"]

analyzername="HNDilepton"
####################################
# code for merging ++ and -- samples
####################################
duplicated=[]
missing_samples=[]
for y in years:
    outpath = os.getenv("INFILE_MERGED_PATH")+ "/"+analyzername+"/"+ y + "/SIG/"
    MakeDirectory(outpath)


    for channel in Channels:
        Masses = masses_s
            
        counter=-1
        for mass in Masses:
            counter=counter+1            
            for flavour in Flavour:


                noMerge=False
                nFiles=0
                hadd = "hadd " + outpath + analyzername+"_HN_STChannel_" + flavour[0] + "_" + mass + "_nlo.root "
                hadd = hadd +  " " + outpath + analyzername+"_HN_Schannel_" + flavour[0] + "_" + mass + "_nlo.root "
                hadd = hadd +  " " + outpath + analyzername+"_HN_Tchannel_" + flavour[0] + "_" + mass + "_nlo.root "
                
                if os.path.exists(outpath + analyzername+"_HN_STChannel_" + flavour[0] + "_" + mass + "_nlo.root"):
                    os.remove(outpath + analyzername+"_HN_STChannel_" + flavour[0] + "_" + mass + "_nlo.root")
                if not os.path.exists(outpath + analyzername+"_HN_Tchannel_" + flavour[0] + "_" + mass + "_nlo.root"):
                    hadd = "cp " +  outpath + analyzername+"_HN_Schannel_" + flavour[0] + "_" + mass + "_nlo.root " + outpath + analyzername+"_HN_STChannel_" + flavour[0] + "_" + mass + "_nlo.root"
                
                os.system(hadd)
            
