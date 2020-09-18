import os

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
limit_dir=options.x

file_limit_path= str(os.getenv("LIMIT_PATH")) +limit_dir+"/"
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


filelists=[]
Found=False
_card=""
_Fulllog=[]
for x in fulllog:

       if "Input datacard" in x:
              _Fulllog.append(x)
              
       if Found:
              _Fulllog.append(x)
       if "-- Hybrid New -- " in x:
              _Fulllog.append(x)
              Found=True

       if "Done" in x:
              _Fulllog.append(x)
                    
              Found=False
       
for x in _Fulllog:
       print x

print "Number of jobs in dir " +  file_limit_path + " is " + str(counter)

Years =   ["2016","2017","2018"]
Channels = ["_combined"] 
Flavours= ["MuMu","EE"]
Masses =  ["100","125","200","250","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500"]
Masses =  ["100","200","300","400","500","600","700","800","900","1000","1100","1200","1500"]

IDMu = ["POGTightPFIsoVeryTight","HNTight2016"]

IDEl = ["passTightID","HNTight2016","passTightID_noccb","passTightID_nocc"]
bins = ["SR1_SR2"]

for year in Years:
       for flavour in Flavours:
              IDs=[]
              if flavour == "MuMu":
                     IDs=IDMu
              else:
                     IDs=IDEl

              for _id in IDs:
                     for _bin in bins:
                     
                            _allmassfilename = flavour + "_"+ _bin
                            if not os.path.exists("out/HNTypeI_JA/"):
                                   os.mkdir("out/HNTypeI_JA/")
                            if not os.path.exists("out/HNTypeI_JA/"+ year):
                                   os.mkdir("out/HNTypeI_JA/"+ year)
                            if not os.path.exists("out/HNTypeI_JA/"+ year+"/"+_allmassfilename):
                                   os.mkdir ("out/HNTypeI_JA/"+ year+"/"+_allmassfilename)

                            outfile = open("out/HNTypeI_JA/"+ year+"/"+_allmassfilename +"/result_combined_"+_id+".txt","w")
                            print "Creating file  out/HNTypeI_JA/"+ year+"/"+_allmassfilename +"/result_combined_"+_id+".txt"
                            for mass in Masses:
                
                                   Expected_Central = "--"
                                   Expected_1sdUp = "--"
                                   Expected_1sdDn = "--"
                                   Expected_2sdUp = "--"
                                   Expected_2sdDn = "--"
                                   #card_combinedSS_MuMu_N125_combined_2016_POGTightPFIsoVeryTight.txt
                                   #card_combinedSS_EE_N1500_combined_2018_passTightID_nocc.txt
                                   tag = "card_combinedSS_"+flavour+"_N"+mass+"_combined_"+year+"_"+_id
                                   
                                   if mass == "1300" or mass == "1200" :
                                          tag = "card_combinedSS_"+flavour+"_N1100_combined_"+year+"_"+_id
                           
                                   if mass == "125": 
                                          tag = "card_combinedSS_"+flavour+"_N100_combined_"+year+"_"+_id
                                   if mass == "250":
                                          tag = "card_combinedSS_"+flavour+"_N250_combined_"+year+"_"+_id

                                   Found=False
                                   for line in _Fulllog:
                                          if "Input datacard" in line:
                                                 if tag in line:
                                                        Found=True
                                          if "Done in" in line:
                                                 Found=False
                                          if Found:
                                                 if "Limit: r" in line:
                                                        Expected_Central = line.split()[3]
                                                        Expected_1sdUp = line.split()[3]
                                                        Expected_1sdDn = line.split()[3]
                                                        Expected_2sdUp = line.split()[3]
                                                        Expected_2sdDn = line.split()[3]
                                   outfile.write(mass + '\t' + Expected_Central+'\t' + Expected_Central+'\t'+Expected_1sdUp+'\t'+Expected_1sdDn+'\t'+Expected_2sdUp+'\t'+Expected_2sdDn+'\n')
                            outfile.close()
                
