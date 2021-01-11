import os,sys

sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *


years =["2016"]
tag="Run2Legacy_v4"
Flavour =[ ["MuMu", ["MumMum" , "MupMup"]],
           ["EE"  , ["EmEm","EpEp"]]]

Channels=["Schannel","Tchannel"]
masses_s = ["100","300","500","700","1000"]
masses_t = []

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
        Masses=[]
        if channel == "Schannel":
            Masses = masses_s
        else:
            Masses = masses_t
            
        counter=-1
        for mass in Masses:
            counter=counter+1            
            for flavour in Flavour:


                noMerge=False
                nFiles=0
                hadd = "hadd " + outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root "
                s_cp = outpath + analyzername+"_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root "

                sigs=[]
                # loop over SS and OS
                for ch in Charge:
                    # loop over ++/--
                    samples_per_ssos=[]
                    for s in flavour[1]:
                        
                        inpath =  os.getenv("INFILE_PATH") + "/"+analyzername+"/"+y+"/" + ch + "/"

                        if os.path.exists(inpath +analyzername+"_HN_"+channel+"_" + s + "_" + mass + "_nlo.root"):
                            sigs.append(inpath +analyzername+"_HN_"+channel+"_" + s + "_" + mass + "_nlo.root")
                            samples_per_ssos.append(inpath + analyzername+"_HN_"+channel+"_" + s + "_" + mass + "_nlo.root")
                    if len(samples_per_ssos) == 1:
                        duplicated.append(samples_per_ssos[0])
                        sigs.append(samples_per_ssos[0])
                    if len(samples_per_ssos) == 0 :
                        missing_samples.append(outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root " + ch)


                for si in sigs:
                    
                    hadd = hadd + " " + si

                if len(sigs)==0:

                    x_counter=0
                    if counter == 0:
                        x_counter=counter+1
                    else:
                        x_counter=counter-1
                    sample_missing=True
                    while sample_missing:
                        if Masses[x_counter] == mass:
                            continue
                        if os.path.exists(outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + Masses[x_counter] + "_nlo.root"):
                            os.system("cp  " +  outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + Masses[x_counter] + "_nlo.root  " + outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root  ")
                            print "Copying next mass as sample is mising "+ outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + Masses[x_counter] + "_nlo.root  " + outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root  "
                            sample_missing=False
                        x_counter=x_counter-1

                    continue 

                if os.path.exists(outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root"):
                    os.system("rm " + outpath + analyzername+"_HN_"+channel+"_" + flavour[0] + "_" + mass + "_nlo.root")
                os.system(hadd + " >> haddsig.log ")


outpath_16 = os.getenv("INFILE_MERGED_PATH")+ "/"+analyzername+"/2016/SIG/"
outpath_17 = os.getenv("INFILE_MERGED_PATH")+ "/"+analyzername+"/2017/SIG/"
outpath_18 = os.getenv("INFILE_MERGED_PATH")+ "/"+analyzername+"/2018/SIG/"
os.system("rm -r " + outpath_17)
os.system("rm -r " + outpath_18)

os.system("cp -r " + outpath_16 + " " + outpath_17)
os.system("cp -r " + outpath_16 + " " + outpath_18)



