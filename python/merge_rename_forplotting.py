import os

import argparse

from os import listdir
from os.path import isfile,isdir, join

parser = argparse.ArgumentParser(description='option')
parser.add_argument('--GetTarFiles', action='store_true')
parser.add_argument('--Untar', action='store_true')
parser.add_argument('--Merge2016', action='store_true')
parser.add_argument('--MvSig', action='store_true')
parser.add_argument('--MergeDATA', action='store_true')
parser.add_argument('--MergeDATA2', action='store_true')
parser.add_argument('--MergeYears', action='store_true')


args = parser.parse_args()

wor_dir= os.getenv("PWD")
tmpdir= os.getenv("SKVERSION")
file_path= os.getenv("FILE_PATH")

if args.GetTarFiles:
    os.system("rm " + file_path + "/HNtypeI_Dilepton-*")
    os.system('scp -r tamsa:/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v2/HNtypeI_Dilepton/HNtypeI_Dilepton-14-9-21.tar.gz '+file_path+'/')
    os.system('scp -r tamsa:/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v2/HNtypeI_Dilepton/HNtypeI_Dilepton_preleg-14-9-21.tar.gz  '+file_path+'/')

    
if args.Untar:
    os.chdir(file_path)
    os.system(' rm -rf tamsafiles')
    os.system('mkdir  tamsafiles')
    os.system('tar -xvf HNtypeI_Dilepton_preleg-14-9-21.tar.gz -C tamsafiles/')
    os.system('tar -xvf HNtypeI_Dilepton-14-9-21.tar.gz -C tamsafiles/')
    os.system('rm -rf ' + tmpdir)
    os.system('mkdir ' + tmpdir)

    os.system('mv tamsafiles/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v2/HNtypeI_Dilepton/  ' + tmpdir + '/')
    os.system('mv tamsafiles/data6/Users/jalmond/SKFlatOutput/Run2Legacy_v4/HNtypeI_Dilepton/2016/  ' + tmpdir + '/HNtypeI_Dilepton/')
    os.system('mv tamsafiles/data6/Users/jalmond/SKFlatOutput/Run2Legacy_v4/HNtypeI_Dilepton/2017/*  ' + tmpdir + '/HNtypeI_Dilepton/2017/')
    os.system('mv tamsafiles/data6/Users/jalmond/SKFlatOutput/Run2Legacy_v4/HNtypeI_Dilepton/2018/*  ' + tmpdir + '/HNtypeI_Dilepton/2018/')
    os.system('rm -r tamsafiles')    
    os.chdir(wor_dir)


if args.Merge2016:

    path_2016 = file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016/'
    path_2016a = file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016preVFP/'
    path_2016b = file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016postVFP/'

    arr_dir_2016a  = [f for f in listdir(path_2016a) if isfile(join(path_2016a,f))]
    arr_dir_2016b  = [f for f in listdir(path_2016b) if isfile(join(path_2016b,f))]

    for x in arr_dir_2016a:
        if x in arr_dir_2016b:
            #print 'hadd ' + path_2016 + '/' + x + ' ' + path_2016a+ '/' + x + ' '  + path_2016b+ '/' + x
            os.system('hadd ' + path_2016 + '/' + x + ' ' + path_2016a+ '/' + x + ' '  + path_2016b+ '/' + x )
            
    
if args.MvSig:

    eras = ['2016' , '2017', '2018']
    for era in eras:
        if not os.path.exists(file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/Signal__/'):
            os.system('mkdir  ' +  file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/Signal__/')
        print 'mv ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/HNtypeI_Dilepton_Heavy* ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/Signal__/'
        os.system('mv ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/HNtypeI_Dilepton_Heavy* ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/Signal__/')

        arr_dir_samples  = [f for f in listdir(file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era) if isfile(join(file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era,f))]
        for x in arr_dir_samples:
            if "SSNonIso_" in x:
                change_skim=x
                change_skim=change_skim.replace('SSNonIso_','HNMulitLep_')
                os.system("mv " +file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era + "/"+x + "  " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era + "/"+change_skim)
        
    
if args.MergeDATA:

    os.system('rm ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/201*/HNtypeI_Dilepton_SkimTree_data_*root')
    
    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Electron.root ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016p*/isEE__/DATA/HNtypeI_Dilepton_SkimTree_HNMultiLep_*')
    
    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Muon.root ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016p*/isMM__/DATA/HNtypeI_Dilepton_*  ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016p*/isSingleMu__/DATA/HNtypeI_Dilepton_*  ' )
    
    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Electron.root ' + file_path + '/'+tmpdir +
 '/HNtypeI_Dilepton/2017/isEE__/DATA/HNtypeI_Dilepton_SkimTree_HNMultiLep_*')
    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Muon.root ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2017/isMM__/DATA/HNtypeI_Dilepton_*  ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2017/isSingleMu__/DATA/HNtypeI_Dilepton_*  ' )


    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Electron.root ' + file_path + '/'+tmpdir +
 '/HNtypeI_Dilepton/2018/isEE__/DATA/HNtypeI_Dilepton_SkimTree_HNMultiLep_*')
    os.system("hadd -f " + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Muon.root ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2018/isMM__/DATA/HNtypeI_Dilepton_*  ' + file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2018/isSingleMu__/DATA/HNtypeI_Dilepton_*  ' )



if args.MergeDATA2:

    eras = ["2016", "2017", "2018"]
    for era in eras:
        lep_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Lepton.root '
        muon_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Muon.root '
        electon_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/'+era+'/HNtypeI_Dilepton_SkimTree_data_HNMultiLep_Electron.root '
        
        os.system("hadd -f " + lep_name + muon_name + electon_name)

    
if args.MergeYears:

    p2016_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2016/'
    p2017_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2017/'
    p2018_name=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/2018/'

    
    arr_dir_2016  = [f for f in listdir(p2016_name) if isfile(join(p2016_name,f))]
    arr_dir_2017  = [f for f in listdir(p2017_name) if isfile(join(p2017_name,f))]
    arr_dir_2018  = [f for f in listdir(p2018_name) if isfile(join(p2018_name,f))]


    AllYearPath=file_path + '/'+tmpdir + '/HNtypeI_Dilepton/AllYears/'
    os.system('mkdir ' + AllYearPath)
    for x in arr_dir_2016:
        if x in arr_dir_2017 and x in arr_dir_2018:
            #print 'hadd ' + AllYearPath + x + ' ' + p2016_name + '/' + x + ' '  + p2017_name + '/' + x + ' '  + p2018_name + '/' + x + ' '
            os.system('hadd ' + AllYearPath + x + ' ' + p2016_name + '/' + x + ' '  + p2017_name + '/' + x + ' '  + p2018_name + '/' + x + ' ')
            

            
