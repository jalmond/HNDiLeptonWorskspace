import os

########################################################################################################
Eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

Flags = ["BB","EC", "Inclusive"]

MergeRun2=True

#######################################################################################################################################
TagDir="April20"
#######################################################################################################################################

for Era in Eras:
    for Flag in Flags:
        os.system("python scripts/hadd.py -era "+Era+" -flag "+Flag + " > Check_" + Era+"_"+Flag+".txt")
        
os.system("grep MISSING " + "Check_*.txt > GREP.txt")

for Era in Eras:
    for Flag in Flags:
        os.system("rm Check_" +     Era+"_"+Flag+".txt")
    
readfile = open("GREP.txt", "r")
for line in readfile:
    if "MISSING" in line:
        print("Some samples are missing ")
        os.system("cat  GREP.txt")
        os.system("rm GREP.txt")
        exit()
readfile.close()
os.system("rm GREP.txt")

print ("No Missing samples ")

#######################################################################################################################################
#######################################################################################################################################

if os.path.exists(TagDir):
    os.system("rm -r " +TagDir)

print("Making Dir " + TagDir)
os.system("mkdir -p " + TagDir)



for Flag in Flags:
    for Era in Eras:
        os.system("python scripts/hadd.py -era "+Era+"  -flag "+Flag + " --run")

    os.system("python scripts/hadd.py -era Run2   -flag "+Flag + " --run")

for Era in Eras:
    print("mv " + Era + " -->" + TagDir)
    os.system("mv " + Era + " " + TagDir+"/")

os.system("mv Run2 " + TagDir+"/")




