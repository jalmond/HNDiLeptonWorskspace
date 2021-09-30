import os,sys
import time

def getoutput(_command,tag):

    tag=tag.replace('/','_')
    cdir = os.getenv("PWD")+"/"
    os.system(_command + " &> log_getoutput"+tag+".txt &")
    time.sleep(2)
    arr_commands=[]
    commandlist = open (cdir+"/log_getoutput"+tag+".txt","r")

    for _line in commandlist:
        arr_commands.append(_line)
    commandlist.close()

    os.system('rm ' + cdir+'/log_getoutput'+tag+'.txt')

    return arr_commands

def rsync_tamsa(_dir):
    print (' ')
    print ('---'*30)
    print('rsync -av -e "ssh -p 1240 " jalmond@147.47.242.42:/data6/Users/jalmond/SKFlatOutput/'+os.getenv('SKFLATVERSION')+'/'+_dir + ' ' + os.environ['FILE_PATH'])
    os.system('rsync -av -e "ssh -p 1240 " jalmond@147.47.242.42:/data6/Users/jalmond/SKFlatOutput/'+os.environ['SKFLATVERSION']+'/'+_dir + ' ' + os.environ['FILE_PATH'])
    print (' ')
    print ('---'*30)

def Diff(li1, li2):
    return list(set(li1) - set(li2)) + list(set(li2) - set(li1))


def merge_2016(test_run,analyser,skim):

    from os import listdir
    from os.path import isfile,isdir, join


    dir_2016 = os.environ['FILE_MERGED_PATH'] +analyser + "/2016/"
    if not os.path.exists(dir_2016):
        os.system('mkdir ' +dir_2016)

    preVFP_path = os.environ['FILE_MERGED_PATH'] +analyser + "/2016preVFP/"
    postVFP_path = os.environ['FILE_MERGED_PATH'] +analyser + "/2016postVFP/"

    dirlist_2016 =  [f for f in listdir(preVFP_path) if isfile(join(preVFP_path,f))]

    for _file in dirlist_2016:
        if os.path.exists(dir_2016+'/'+_file):
            os.system('rm ' + dir_2016+'/'+_file)
        os.system('hadd ' + dir_2016+'/'+_file + ' ' + preVFP_path + '/'+_file + ' ' + postVFP_path + '/'+_file)
        

        
def merge_all_years(test_run,analyser,skim):

    print ('')
    print (' ')
    print ('---'*30)
    print ('All Run2 merging')
    print ('---'*30)
    print (' ')

    from os import listdir
    from os.path import isfile,isdir, join
    
    
    allyear_dir = os.environ['FILE_MERGED_PATH'] +analyser + "/YearCombined/"
    if not os.path.exists(allyear_dir):
        os.system('mkdir ' +allyear_dir)
        
    preVFP_path = os.environ['FILE_MERGED_PATH'] +analyser + "/2016preVFP/"

    dirlist_2016 =  [f for f in listdir(preVFP_path) if isfile(join(preVFP_path,f))]
    eras = ["2016postVFP", "2017", "2018"]
    for era in eras:
        file_path = os.environ['FILE_MERGED_PATH'] +analyser + "/"+era+"/"
        dirlist =  [f for f in listdir(file_path) if isfile(join(file_path,f))]
        print('Check difference in rootfiles per era ['+era+']:')
        print(Diff(dirlist,dirlist_2016) )

        
    for _file in dirlist_2016:
        print ('@@@_file -- ' + _file)
        if os.path.exists(allyear_dir+_file):
            os.system('rm ' +allyear_dir+_file)
        hadd_cmd = 'hadd '+allyear_dir+_file + ' ' + preVFP_path+_file + ' '
        print(allyear_dir+_file + ' [hadd output]')
        print(' ' )
        print(preVFP_path+_file + ' [hadd input]')

        for era in eras:
            hadd_cmd+= os.environ['FILE_MERGED_PATH'] +analyser + "/"+era+'/'+_file +' '
            print(os.environ['FILE_MERGED_PATH'] +analyser + "/"+era+'/'+_file +'  [hadd input]')
            
        out = getoutput(hadd_cmd,'')
        for x in out:
            if "ERROR" in x or "Error" in x:
                print ("ERROR found in hadd_cmd=" + hadd_cmd)
                print (x)
                exit()
            if "Warning" in out:
                print ("Warning found in hadd_cmd=" + hadd_cmd)
                print (x)
                exit()

def merge_data_flavour(test_run,analyser,skim,  label, flavours):

    print (' ')
    print ('---'*30)
    print ("merge channel data: [analyser = "  + analyser +"]  Lepton")
    print ('---'*30)
    print (' ')

    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

    for era in eras:
        
        local_dir=os.environ['FILE_MERGED_PATH'] +analyser + "/" +era

        out_file =local_dir+"/"+analyser+skim+"_data_"+label+".root"
        if "NonPrompt" in label:
            out_file =local_dir+"/"+analyser+skim+"_"+label+".root"

        if os.path.exists(out_file):
            os.system('rm ' + out_file)
            
        hadd_cmd = "hadd "+ out_file +' '
        print(out_file + ' [hadd output]')
        print(' ' )
        for x in flavours:
            in_file =local_dir+"/"+analyser+skim+"_data_"+x+".root "
            if "NonPrompt" in label:
                in_file =local_dir+"/"+analyser+skim+"_"+x+".root "

            hadd_cmd = hadd_cmd + in_file

            print(in_file +"  [hadd input]")

        if not test_run:
            out = getoutput(hadd_cmd,'')
            for x in out:
                if "ERROR" in x  or "Error" in x:
                    print ("ERROR found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()
                if "Warning" in out:
                    print ("Warning found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()



            
def merge_data(test_run,analyser,skim, flavour, flav_dir):

    print (' ')
    print ('---'*30)
    print ("merge_data: [analyser = "  + analyser +"]  flavour="+ flavour)
    print ('---'*30) 
    print (' ')
    eras = ["2016preVFP", "2016postVFP", "2017", "2018"]

    n_era=-1
    for era in eras:
        n_era+=1
        
        local_dir=os.environ['FILE_MERGED_PATH'] +analyser
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)

        local_dir=os.environ['FILE_MERGED_PATH'] +analyser + "/" +era
        if not os.path.exists(local_dir):
            os.mkdir(local_dir)

            
        #HNL_Validation_SkimTree_HNFake_NonPrompt_Muon.root HNL_Validation_SkimTree_HNFake_data_Muon.root

        out_file=local_dir+"/"+analyser+skim+"_data_"+flavour+".root"
        if "NonPrompt" in flavour:
            out_file=local_dir+"/"+analyser+skim+"_"+flavour+".root"

        if os.path.exists(out_file):
            os.remove(out_file)

        string_hadd = ""
        _dir=flav_dir[n_era]
        print _dir
        file_path=os.environ['FILE_PATH'] + analyser + "/" +era+"/"+_dir[0]+"DATA/"+analyser+skim + _dir[1]+"* "
        string_hadd = string_hadd+file_path
            
        hadd_cmd="hadd  " + out_file + " " + file_path
        print (out_file + " [hadd output]")
        print(' ' )
        print ("hadd [input] :")
        mclist =os.system("ls " + os.environ['FILE_PATH'] + analyser + "/" +era+"/"+_dir[0]+"DATA/"+analyser+skim + _dir[1]+"* ")
        
        if not test_run:
            out = getoutput(hadd_cmd,'data_'+era+'_'+_dir[0]+'_'+_dir[1])
            for x in out:
                if "ERROR" in x  or "Error" in x:
                    print ("ERROR found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()
                if "Warning" in out:
                    print ("Warning found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()


def merge_mc(test_run,analyser, skim):

    print ('')
    print (' ')
    print ('---'*30)
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
            os.system('rm ' +out_file)

        file_path=os.environ['FILE_PATH'] + analyser + "/" +era+"/"+analyser+skim+"*"
        os.system('cp ' + file_path + ' '  + local_dir)
        hadd_cmd="hadd  " + out_file + " " + file_path

        print (out_file + " [hadd output]")
        print(' ' )
	print ("hadd [input] :")
        _list =os.system("ls " + os.environ['FILE_PATH'] + analyser + "/" +era+"/"+analyser+skim+"*")
        
        
        if not test_run:
            out = getoutput(hadd_cmd,'')
            for x in out:
                if "ERROR" in x  or "Error" in x:
                    print ("ERROR found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()
                if "Warning" in out:
                    print ("Warning found in hadd_cmd=" + hadd_cmd)
                    print (x)
                    sys.exit()
                    

    return

def merge_data_setup(_isTest,_analyser_name,_skim_name):
    print (' ')
    print ('---'*30)
    print ('merge_data_setup: ')
    print ('---'*30)
    print (' ')

    if analyser_name == "FakeRateHN":
        merge_data(_isTest,_analyser_name,_skim_name,"Electron", [["/","SingleElectron_"]])
        merge_data(_isTest,_analyser_name,_skim_name,"Muon",     [["SingleMuon"], ["SingleMuon"], ["SingleMuon"], ["SingleMuon"]])
        merge_data_flavour(_isTest,_analyser_name,_skim_name , "Lepton", ["Muon","Electron"])

    elif analyser_name == "HNL_Validation":
        
        merge_data(_isTest,_analyser_name,_skim_name,"Electron",   [["/","_SingleElectron"],["/","_SingleElectron"],["/","_SingleElectron"],["/","_EGamma"]])
        merge_data(_isTest,_analyser_name,_skim_name,"Muon",       [["/","_SingleMuon"],["/","_SingleMuon"],["/","_SingleMuon"],["/","_SingleMuon"]])
        merge_data(_isTest,_analyser_name,_skim_name,"NonPrompt_Electron",   [["/RunFake__/","_SingleElectron"],["/RunFake__/","_SingleElectron"],["/RunFake__/","_SingleElectron"],["/RunFake__/","_EGamma"]])
        merge_data(_isTest,_analyser_name,_skim_name,"NonPrompt_Muon",       [["/RunFake__/","_SingleMuon"],["/RunFake__/","_SingleMuon"],["/RunFake__/","_SingleMuon"],["/RunFake__/","_SingleMuon"]])

        merge_data_flavour(_isTest,_analyser_name,_skim_name , "Lepton", ["Muon","Electron"])
        merge_data_flavour(_isTest,_analyser_name,_skim_name , "NonPrompt_Lepton", ["NonPrompt_Muon","NonPrompt_Electron"])

    return

            
if str(os.getenv("HNDILEPTONWORKSPACE_DIR")) == "None":
    print ("setup enviroment....")
    exit()

import argparse
parser = argparse.ArgumentParser(description='option')
parser.add_argument('--Data', action='store_true')
parser.add_argument('--MC', action='store_true')
parser.add_argument('--mergeFlavour', action='store_true')
parser.add_argument('--Test', action='store_true')
parser.add_argument('--SYNC', action='store_true')
parser.add_argument('--NoMerge', action='store_true')
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


if args.SYNC:
    rsync_tamsa(analyser_name)
if args.NoMerge:
    exit()
    
if isData:
    merge_data_setup(isTest,analyser_name,skim_name)
    merge_2016(isTest,analyser_name,skim_name)
    
elif args.MC:
    merge_mc(isTest,analyser_name,skim_name)

    
else:
    
    merge_data_setup(isTest,analyser_name,skim_name)
    merge_2016(isTest,analyser_name,skim_name)
    merge_mc(isTest,analyser_name,skim_name)
    merge_all_years(isTest,analyser_name,skim_name )


