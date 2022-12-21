#!/usr/bin/env python

import os,sys,time
import argparse
import datetime
import random
import subprocess


## Arguments

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="")
parser.add_argument('-m', dest='Mass', default=100)
parser.add_argument('-I', dest='Iso', default="014")
parser.add_argument('-MI', dest='IsoType', default="014")
parser.add_argument('-v', dest='MVA', default="mva")
parser.add_argument('-r', dest='EtaRegion',  default="BB")
parser.add_argument('-N', dest='NProc', default=999, type=int, help="maximum running jobs")
parser.add_argument('-t', dest='Tag', default="Default")
parser.add_argument('-CC', dest='ChargeCut', default="Def")
parser.add_argument('-B', dest='BinType', default="Def")
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-q', dest='Queue', default="fastq")
parser.add_argument('-c', dest='Channel', default="EE")
parser.add_argument('-e', dest='Era', default="2017",help="2016preVFP(2016a), 2016postVFP(2016b), 2017, 2018")
parser.add_argument('--Data', action='store_true')
parser.add_argument('--nmax', dest='NMax', default=300, type=int, help="maximum running jobs")
parser.add_argument('--reduction', dest='Reduction', default=1, type=float)
parser.add_argument('--memory', dest='Memory', default=0, type=float)
parser.add_argument('--batchname',dest='BatchName', default="")
args = parser.parse_args()

if ".py" in args.Analyzer:
  print("-a option must not contain subfix .C")
  exit()


if args.Analyzer == "":
  print("Input Macro not set...")
  exit()





NJobs=1

if args.Era=="2016a": args.Era="2016preVFP"
if args.Era=="2016b": args.Era="2016postVFP"

## Add Abosolute path for outputdir
if args.Outputdir!='':
  if args.Outputdir[0]!='/':
    args.Outputdir = os.getcwd()+'/'+args.Outputdir

## TimeStamp

# 1) dir/file name style
JobStartTime = datetime.datetime.now()
timestamp =  JobStartTime.strftime('%Y_%m_%d_%H%M%S')


# 2) log style
JobStartTime = datetime.datetime.now()
string_JobStartTime =  JobStartTime.strftime('%Y-%m-%d %H:%M:%S')
string_ThisTime = ""

## Environment Variables

USER = os.environ['USER']



SCRAM_ARCH = os.environ['SCRAM_ARCH']
cmsswrel = os.environ['cmsswrel']
SKFlat_WD = os.environ['SKFlat_WD']
SKFlatV = os.environ['SKFlatV']
SAMPLE_DATA_DIR = SKFlat_WD+'/data/'+SKFlatV+'/'+args.Era+'/Sample/'
MVARunlogDir = os.environ['MVARunlogDir']
MVAOutputDir = os.environ['MVAOutputDir']

os.system("mkdir -p " +MVARunlogDir)
os.system("mkdir -p " +MVAOutputDir)


UID = str(os.getuid())
HOSTNAME = os.environ['HOSTNAME']
SampleHOSTNAME = HOSTNAME

## Check joblog email

SendLogToWeb = False

## Check hostname

IsTAMSA1 = ("tamsa1" in HOSTNAME)
IsTAMSA2 = ("tamsa2" in HOSTNAME)
IsTAMSA = IsTAMSA1 or IsTAMSA2
if IsTAMSA:
  if IsTAMSA1:
    HOSTNAME = "TAMSA1"
  elif IsTAMSA2:
    HOSTNAME = "TAMSA2"
  SampleHOSTNAME = "SNU"


StringForHash = ""

## When using txt file for input (i.e., -l option)

random.seed(hash(StringForHash+timestamp+args.Era))
RandomNumber = int(random.random()*1000000)
str_RandomNumber = str(RandomNumber)

webdirname = timestamp+"_"+str_RandomNumber

## Define MasterJobDir

MasterJobDir = MVARunlogDir+'/'+args.ChargeCut+'__'+args.BinType+"__"+timestamp+'__'+str_RandomNumber+"__"+str(args.NProc)+"__"+args.Analyzer+'__'+'Era'+args.Era+'__'+ args.EtaRegion + '__'+args.Mass + '__' + args.MVA + '__' + args.Iso + '__'+args.IsoType
if args.Data:
  MasterJobDir += '__Data'
MasterJobDir += '__'+HOSTNAME+'/'

  

os.mkdir(MasterJobDir)

FinalOutputPath = args.Outputdir
if args.Outputdir=="":
  FinalOutputPath = MVAOutputDir+'/'+SKFlatV+'/'+args.Analyzer+'/'+args.Era+'/'
  os.system('mkdir -p '+ MVAOutputDir+'/'+SKFlatV)
  os.system('mkdir -p '+ MVAOutputDir+'/'+SKFlatV +'/'+args.Analyzer+'/')

if args.Tag != "":
  FinalOutputPath = MVAOutputDir+'/'+SKFlatV+'/'+args.Analyzer+'/' +args.Tag + '/'+args.Era+'/'
  os.system('mkdir -p '+ MVAOutputDir+'/'+SKFlatV)
  os.system('mkdir -p '+ MVAOutputDir+'/'+SKFlatV +'/'+args.Analyzer+'/')
  os.system('mkdir -p '+ MVAOutputDir+'/'+SKFlatV +'/'+args.Analyzer+'/'+args.Tag)

os.system('mkdir -p '+FinalOutputPath)
os.system('mkdir -p '+FinalOutputPath+'/Root/')
os.system('mkdir -p '+FinalOutputPath+'/Plots/')
os.system('mkdir -p '+FinalOutputPath+'/Logs/')
os.system('mkdir -p '+FinalOutputPath+'/Txt/')

macroname=""

MVADirs = ["/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/python/Opt/"]
for MVADir in MVADirs:

  base_rundir = MasterJobDir+"/"+args.Tag
  os.mkdir(base_rundir)
  macroname = args.Analyzer+".py"

  submitPy = macroname+" -N "+str(args.NProc)+"  -m "+args.Mass+" -r " + args.EtaRegion + " -I "  + args.Iso + " -v " + args.MVA + " -MI " + args.IsoType + " -CC " + args.ChargeCut + " -B " + args.BinType
  if  not macroname == "OptMVAElectronIsoBATCH.py":
    submitPy = macroname+" -m "+args.Mass+" -r " + args.EtaRegion + " -v " + args.MVA + " -B " + args.BinType

  if args.Data :
    submitPy=submitPy+" --Data"

  os.system('cp ' + MVADir + '/'+ macroname+' ' + base_rundir)
  os.system('cp ' + MVADir + '/OptConfig.py  ' + base_rundir)

  commandsfilename = args.Analyzer+'-'+args.Tag
  run_commands = open(base_rundir+'/'+commandsfilename+'.sh','w')

  outName = 'output_MVA'+args.Channel+'_M'+str(args.Mass)+'__MVA'
  print>>run_commands,'''#!/bin/bash
SECTION=`printf $1`
WORKDIR=`pwd`

Trial=0

#### make sure use C locale
export LC_ALL=C

#### Don't make root history
export ROOT_HIST=0

#### use cvmfs for root ####
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH={3}
export cmsswrel={4}
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
echo "@@@@ SCRAM_ARCH = "$SCRAM_ARCH
echo "@@@@ cmsswrel = "$cmsswrel
echo "@@@@ scram..."
eval `scramv1 runtime -sh`
cd -
source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh

while [ "$Trial" -lt 3 ]; do
  echo "#### running ####"
  echo "python  {1}/{2}"
  python {1}/{2} 2> err.log 
  EXITCODE=$?
  if [ "$EXITCODE" -eq 5 ]; then
    echo "IO error occured.. running again in 300 seconds.."
    Trial=$((Trial+=1))
    sleep 300
  else
    break
  fi
done

mv *.root    {5}/Root/
mv *.txt    {5}/Txt/
mv *.log    {5}/Logs/
mv *.png    {5}/Plots/ 
mv *.pdf    {5}/Plots/ 

if [ "$EXITCODE" -ne 0 ]; then
  echo "ERROR errno=$EXITCODE" >> err.log
fi

exit $EXITCODE
'''.format(MasterJobDir, base_rundir, submitPy, SCRAM_ARCH, cmsswrel,FinalOutputPath , outName)
  run_commands.close()

  submit_command = open(base_rundir+'/submit.jds','w')
  concurrency_limits=''
  if args.NMax:
    concurrency_limits='concurrency_limits = n'+str(args.NMax)+'.'+os.getenv("USER")
    request_memory=''
    if args.Memory:
      request_memory='request_memory = '+str(args.Memory)
    print>>submit_command,'''executable = {1}.sh
jobbatchname = {1}
universe   = vanilla
arguments  = $(Process)
log = condor.log
getenv     = True
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
{2}
{3}
queue {0}
'''.format(str(NJobs), commandsfilename,concurrency_limits,request_memory)
    submit_command.close()


    cwd = os.getcwd()
    os.chdir(base_rundir)
    condorOptions = ''
    if args.BatchName!="":
      condorOptions = ' -batch-name '+args.BatchName
    os.system('condor_submit submit.jds '+condorOptions)
    os.chdir(cwd)



print '##################################################'
print("RunDir: " + base_rundir)
print 'Submission Finished'
print '- JobID = '+str_RandomNumber
print '- Analyzer = '+args.Analyzer+'.py'
print '- Channel = '+args.Channel
print '- Mass = '+str(args.Mass)
print '- Era = '+args.Era


print '-'*40
print '- NJobs = '+str(NJobs)
print '-'*40

print '- output will be send to : '+FinalOutputPath

print '##################################################'

