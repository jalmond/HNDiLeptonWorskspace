import os

def merge_data_flavour(test_run,analyser,skim,  label, flavours):


    print ("merge channel data: [analyser = "  + analyser +"]")
    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

    for era in eras:
        
        local_dir=os.environ['FILE_MERGED_PATH'] +analyser + "/" +era

        out_file =local_dir+"/"+analyser+skim+"_"+label+"_data.root "
        hadd_cmd = "hadd "+ out_file 

        for x in flavours:
            in_file =local_dir+"/"+analyser+skim+"_"+ x +"_data.root "
            hadd_cmd = hadd_cmd + out_file
        print (hadd_cmd)
        if not test_run:
            os.system(hadd_cmd)

        
def merge_data(test_run,analyser,skim, flavour, flav_dir):

    print ("merge_data: [analyser = "  + analyser +"]")
    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

    for era in eras:
        
        local_dir=os.environ['FILE_MERGED_PATH'] +analyser
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)

        local_dir=os.environ['FILE_MERGED_PATH'] +analyser + "/" +era
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)
        


        out_file=local_dir+"/"+analyser+skim+"_"+flavour+"_data.root"
        if os.path.exists(out_file):
            os.remove(out_file)

        string_hadd = ""
        for _dir in flav_dir:
            file_path=os.environ['FILE_PATH'] + analyser + "/" +era+"/"+_dir+"/DATA/"+analyser+skim +"* "
            string_hadd = string_hadd+file_path
            
        hadd_cmd="hadd  " + out_file + " " + file_path
        print (hadd_cmd)
        if not test_run:
            os.system(hadd_cmd)

        
def merge_mc(test_run,analyser, skim):

    print ("merge_mc: [analyser = "  + analyser +"]")
    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

    for era in eras:

        local_dir=os.environ['FILE_MERGED_PATH'] +analyser
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)

        local_dir=os.environ['FILE_MERGED_PATH'] +analyser + "/" +era
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)

        out_file=local_dir+"/"+analyser+skim+"_MC.root"
        if os.path.exists(out_file):
            os.remove(out_file)

        file_path=os.environ['FILE_PATH'] + analyser + "/" +era+"/"+analyser+skim+"*"

        hadd_cmd="hadd  " + out_file + " " + file_path
        print (hadd_cmd)
        if not test_run:
            os.system(hadd_cmd)


if str(os.getenv("HNDILEPTONWORKSPACE_DIR")) == "None":
    print ("setup enviroment....")
    exit()

import argparse
parser = argparse.ArgumentParser(description='option')
parser.add_argument('--Data', action='store_true')
parser.add_argument('--MC', action='store_true')
parser.add_argument('--mergeFlavour', action='store_true')
parser.add_argument('--Test', action='store_true')
parser.add_argument('-a',dest='Analyzer', default='NULL')
parser.add_argument('-s',dest='Skim', default='')


args = parser.parse_args()

analyser_name= args.Analyzer
skim_name = args.Skim
if not skim_name == "":
    skim_name = "_"+skim_name
isData=args.Data
isTest=args.Test

if analyser_name == "NULL":
    print ("input -a analyser not added: use one from FILE_MERGED_PATH")
    os.system('ls  ' + os.getenv('FILE_PATH'))
    
    exit()

if isData:
    merge_data(isTest,analyser_name,skim_name,"Electron", ["isEE__"])
    merge_data(isTest,analyser_name,skim_name,"Muon",     ["isMM__","isSingleMu"])


if args.MC:
    merge_mc(isTest,analyser_name,skim_name)


if args.mergeFlavour:
    merge_data_flavour(isTest,analyser_name,skim_name , "Lepton", ["Muon","Electron"])
