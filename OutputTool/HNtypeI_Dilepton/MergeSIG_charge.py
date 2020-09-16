import os

years =["2016"]
tag="Run2Legacy_v4"
Channel =[ ["MuMu", ["MumMum" , "MupMup"]],
           ["EE"  , ["EmEm","EpEp"]]]

Type=["Schannel","Tchannel"]
mass = ["100","125","200","250","300","400", "500", "600","700","800","900","1000","1100","1200","1300","1400","1500","1700","2000"]
charge= ["Signal__/","SignalOS__/"]

####################################
# code for merging ++ and -- samples
####################################
duplicated=[]
missing_samples=[]
for y in years:
    outpath = os.getenv("INFILE_MERGED_PATH")+ y + "/SIG/"
    if not os.path.exists(outpath):
        os.system("mkdir "  +outpath)

    for m in mass:
        for t in Type:
            for c in Channel:
                
                noMerge=False
                nFiles=0
                hadd = "hadd " + outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root "
                s_cp = outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root "
                counter=0
                sigs=[]
                # loop over SS and OS
                for ch in charge:
                    # loop over ++/--
                    samples_per_ssos=[]
                    for s in c[1]:
                        
                        inpath =  os.getenv("INFILE_PATH") + "2016/" + ch + "/"

                        if os.path.exists(inpath +"HNtypeI_JA_HN_"+t+"_" + s + "_" + m + "_nlo.root"):
                            sigs.append(inpath +"HNtypeI_JA_HN_"+t+"_" + s + "_" + m + "_nlo.root")
                            samples_per_ssos.append(inpath +"HNtypeI_JA_HN_"+t+"_" + s + "_" + m + "_nlo.root")
                    if len(samples_per_ssos) == 1:
                        duplicated.append(samples_per_ssos[0])
                        sigs.append(samples_per_ssos[0])
                    if len(samples_per_ssos) == 0 :
                        missing_samples.append(outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root " + ch)


                for si in sigs:
                    
                    hadd = hadd + " " + si

                if len(sigs)==0:
                    print "No Signal " + outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root "
                    #missing_samples.append(outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root ")
                    continue 
                print " "
                print hadd
                if os.path.exists(outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root"):
                    os.system("rm " + outpath + "HNtypeI_JA_HN_"+t+"_" + c[0] + "_" + m + "_nlo.root")
                os.system(hadd)


for dup in  duplicated:
    print "Sample duplicated since missing other charge" + dup

for miss_sample in missing_samples:
    print "Sample missing, fix after merging " + miss_sample


print "cp /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_EE_250_nlo.root  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_EE_300_nlo.root "
print " cp /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_MuMu_400_nlo.root  /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_MuMu_500_nlo.root"
print " cp /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_EE_400_nlo.root /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Schannel_EE_500_nlo.root"
print "cp /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Tchannel_MuMu_400_nlo.root /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Tchannel_MuMu_500_nlo.root"
print " cp /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Tchannel_EE_400_nlo.root /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/OutputTool/MergedFiles/2016/SIG/HNtypeI_JA_HN_Tchannel_EE_500_nlo.root"
