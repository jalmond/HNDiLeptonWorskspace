import os 

eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

eras = ["2018"]

# This script will merge CF root files

Analyser="HNL_Validation"

for era in eras:
    
    if os.getenv("INFILE_PATH") == None:
        print("Env not set.....")
        exit()

    input_dir=os.getenv("INFILE_PATH") + "/"+Analyser+"/"+era
    
    from os import listdir
    from os.path import isfile,isdir, join
    in_dir  = [f for f in listdir(input_dir) if isfile(join(input_dir,f))]
    MC_list=[]
    for f in in_dir:
        ftmp=f
        ftmp=ftmp.replace(Analyser+'_','')
        ftmp=ftmp.replace('.root','')
        ftmp=ftmp.replace('SkimTree_Dilepton_','')
        MC_list.append(ftmp)

        samples = [  [ "VV", ["WZ_*","ZZ_*","WZ_*"]],
                     [ "Top", ["TT*"]]]

               

    local_dir=os.getenv("FILE_MERGED_PATH")+"/"+Analyser
    if not os.path.exists(local_dir):
        os.system("mkdir " + local_dir)
    local_dir=local_dir+"/"+era
    if not os.path.exists(local_dir):
        os.system("mkdir " + local_dir)
    
    print('cp ' + input_dir + "/"+Analyser+'* ' + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/")
    os.system('cp ' + input_dir + "/"+Analyser+'* ' + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/")
    for sample in samples:
        sample_group = sample[0]

        if os.path.exists(os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/"+ Analyser+"_"+sample_group+".root"):
            os.system("rm " +  os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/"+ Analyser+"_"+sample_group+".root")
        

        haddcmd="hadd  " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/"+ Analyser+"_"+sample_group+".root " 
        for x in sample[1]:
            haddcmd=haddcmd + " " + input_dir + "/"+Analyser+'*_'+x + " " 
        print(haddcmd)
        os.system(haddcmd)
        print "-"*40
        print "Created: " + os.getenv("FILE_MERGED_PATH")+"/"+Analyser+"/"+era + "/"+ Analyser+"_"+sample_group+".root "
        print "-"*40
