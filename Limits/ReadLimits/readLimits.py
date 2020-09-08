import os

file_limit_path= os.getenv("PLOTTER_WORKING_DIR")+"/Files/Limits/CutCount/out/"

Years =   ["combined"]
Charges = ["SS","OS_SS"]
Flavours= ["MuMu","EE"]
Masses =  ["100","200","300","400","500","600","700","800","900","1000","1100","1200","1500"]
for year in Years:
    for charge in Charges:
        for flavour in Flavours:

            _allmassfilename = "log_"+flavour+"_"+year+charge+"_"+flavour

            outfile = open("out/"+_allmassfilename+'.txt','w')

            for mass in Masses:
                filename = "log_"+flavour+"_"+year+charge+"_"+flavour+"_N"+mass 

                lines_log=[]
                open_file = open(file_limit_path+filename,"r")
                for line in open_file:
                    lines_log.append(line) 
                open_file.close()

                Expected_Central = ""
                Expected_1sdUp = ""
                Expected_1sdDn = ""
                Expected_2sdUp = ""
                Expected_2sdDn = ""

                for line in lines_log:
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

