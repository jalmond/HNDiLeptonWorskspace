import os

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
limit_dir=options.x

file_limit_path= str(os.getenv("LIMIT_PATH")) +limit_dir+\
"/"
if str(os.getenv("LIMIT_PATH")) == "None":
       print "setup enviroment...."
       exit()

if not os.path.exists(file_limit_path):
    print "Need dir input from following..."
    os.system("ls " + str(os.getenv("LIMIT_PATH")))
    exit()


counter=0
fulllog=[]
for root, dirs, files in os.walk(file_limit_path):
    for filename in files:
        if "job" in filename:
            if ".log" in filename:
                counter=counter+1
                _file = open(file_limit_path+filename,"r")
                for f in _file:
                    fulllog.append(f)
                _file.close()


print "Number of jobs in dir " +  file_limit_path + " is " + str(counter)

Years =   [""]
Charges = ["SS","OS_SS"]
Flavours= ["MuMu","EE"]
Masses =  ["100","200","300","400","500","600","700","800","900","1000","1100","1200","1500"]
Channels = ["","_VBF","_combined"]

for year in Years:
    for charge in Charges:
        for flavour in Flavours:
            for channel in Channels:
                nbin = "SSCombined"
                if charge == "OS_SS":
                    nbin = "OSSSCombined"

                _allmassfilename = flavour + "_"+ nbin
                if not os.path.exists("out/CombinedYears"):
                    os.mkdir("out/CombinedYears")
                if not os.path.exists("out/CombinedYears/"+_allmassfilename):
                    os.mkdir ("out/CombinedYears/"+_allmassfilename)

                outfile = open("out/"+_allmassfilename+'.txt','w')

                for mass in Masses:
                
                    Expected_Central = ""
                    Expected_1sdUp = ""
                    Expected_1sdDn = ""
                    Expected_2sdUp = ""
                    Expected_2sdDn = ""
                    tag = "Combined"+charge+"_"+flavour+"_N"+mass+"_"+channel
                    Found=False
                    for line in fulllog:
                        if "Input datacard" in line:
                            print tag 
                            print line
                            if tag in line:
                                Found=True
                        if "Done in" in line:
                            Found=False
                        if Found:
                            if "Expected 50.0%" in line:
                                Expected_Central = line.split()[4]
                            if "Expected 84.0%" in line:
                                Expected_1sdUp = line.split()[4]
                            if "Expected 16.0%" in line:
                                Expected_1sdDn = line.split()[4]
                            if "Expected 97.5%" in line:
                                Expected_2sdUp = line.split()[4]
                            if "Expected  2.5%" in line:
                                Expected_2sdDn = line.split()[4]

                            
                outfile.write(mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n')
            outfile.close()

