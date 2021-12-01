import os,ROOT
from PlotterCF import SampleGroup, Variable, Region, Systematic
from PlotterCF import Plotter
from IsCorrelated import IsCorrelated
from HNLGeneral import GetOutput

import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)

## Arguments

parser = argparse.ArgumentParser(description='Validation plot commands')
parser.add_argument('-c', dest='Category', type=int, default=0)
parser.add_argument('-y', dest='Year', type=int)
parser.add_argument('--debug',action='store_true')
parser.add_argument('--ScaleMC', action='store_true')
args = parser.parse_args()

## Enviroment

WORKING_DIR = os.environ['PLOTTER_WORKING_DIR']
dataset = os.environ['SKANVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

connection_lxplus=False
for x in GetOutput('ls /tmp/',''):
  if 'ssh-jalmond@lxplus.cern.ch' in x:
    connection_lxplus=True
if not connection_lxplus:

  print ('open lxplus connection')
  exit()
    
    
m = Plotter()

m.DoDebug = args.debug

#### In/Out
m.DataYear = args.Year
str_Year = str(args.Year)
#m.InputDirectory = WORKING_DIR+'/rootfiles/'+dataset+"/Regions/"
m.InputDirectory = WORKING_DIR+'/InputFiles/MergedFiles/'+dataset+"/HNL_DileptonCR/"
if args.Year<0:
  str_Year = 'YearCombined'

m.DataDirectory = str_Year
m.Filename_prefix = "HNL_DileptonCR"
m.Filename_suffix = ""
m.Filename_skim = "_SkimTree_HNMultiLep"

if not os.path.exists(ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/"):
  os.system("mkdir " + ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/")

os.system('cp ' + os.getenv('HTML_DIR') + '/index.php ' + ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/")
  
m.OutputDirectory = ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/"+str_Year+"/"
os.system('cp ' + os.getenv('HTML_DIR') + '/index.php ' + ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/"+str_Year+"/")
print('cp ' + os.getenv('HTML_DIR') + '/index.php ' + ENV_PLOT_PATH+"/"+dataset+"/HNL_DileptonCR/"+str_Year+"/")

#### Category
m.ScaleMC = args.ScaleMC

#### Systematic
tmp_Systematics = [
  #"Lumi",
  #"JetRes",
  #"JetEn",
  #"JetMass",
  #"MuonRecoSF",
  #"MuonEn",
  #"MuonIDSF",
  #"MuonISOSF",
  #"MuonTriggerSF",
  #"ElectronRecoSF",
  #"ElectronRes",
  #"ElectronEn",
  #"ElectronIDSF",
  #"ElectronTriggerSF",
  #"PU",
  #"Prefire",
  #"DYNorm",
  #"DYReshapeSyst",
  #"NonPromptNorm",
  #"OthersNorm",
  #"BTag",
]
#tmp_Systematics = ["Lumi"]

m.Systematics = [ Systematic(Name="Central", Direction=0, Year=-1) ]
for s in tmp_Systematics:
  isCorr = IsCorrelated(s)
  if isCorr:
    m.Systematics.append( Systematic(Name=s, Direction=+1, Year=-1) )
    m.Systematics.append( Systematic(Name=s, Direction=-1, Year=-1) )
  else:
    if args.Year>0:
      m.Systematics.append( Systematic(Name=s, Direction=+1, Year=args.Year) )
      m.Systematics.append( Systematic(Name=s, Direction=-1, Year=args.Year) )
    else:
      for Y in [2016,2017,2018]:
        m.Systematics.append( Systematic(Name=s, Direction=+1, Year=Y) )
        m.Systematics.append( Systematic(Name=s, Direction=-1, Year=Y) )
m.PrintSystematics()

#### Binning infos
m.SetBinningFilepath(
  WORKING_DIR+'/data/'+dataset+'/'+str_Year+'/CR_rebins.txt',
  WORKING_DIR+'/data/'+dataset+'/'+str_Year+'/CR_xaxis.txt',
  WORKING_DIR+'/data/'+dataset+'/'+str_Year+'/CR_yaxis.txt',
)

#### Predef samples
from PredefinedSamples import *

###############
#### DY CR ####
###############

if args.Category==0:
  #### Define Samples
  if args.Year>0:
    exec('m.SampleGroups = [SampleGroup_Top_%s, SampleGroup_WZ_powheg_%s,  SampleGroup_ZZ_powheg_%s,SampleGroup_NonPrompt_Muon_%s,  SampleGroup_VVV_%s , SampleGroup_DY_%s , SampleGroup_CF_%s,SampleGroup_Others_%s,SampleGroup_ZG_%s, SampleGroup_WG_%s ]'%(args.Year,args.Year, args.Year,args.Year,args.Year,args.Year,args.Year,args.Year,args.Year,args.Year))
  else:
    m.SampleGroups = [
      SampleGroup_Others_2016, SampleGroup_Others_2017, SampleGroup_Others_2018,
      SampleGroup_NonPrompt_Muon_2016, SampleGroup_NonPrompt_Muon_2017, SampleGroup_NonPrompt_Muon_2018,
      SampleGroup_TT_TW_2016, SampleGroup_TT_TW_2017, SampleGroup_TT_TW_2018,
      SampleGroup_DY_2016, SampleGroup_DY_2017, SampleGroup_DY_2018,
    ]

  #### Signals
  #### Print
  m.PrintSamples()

  IDs=["POG"]
  #### Define reiongs
  m.RegionsToDraw = [
    Region('FillEventCutflow' , 'Muon', UnblindData=True, Logy=1, TLatexAlias='#splitline{#mu#mu}{CutFlow}',CutFlowCaption="Single Muon Trigger On Z shell, OS dilepton pair"),

  ]
  m.PrintRegions()

######################
#### emu sideband ####
######################



#### Define Variables
m.VariablesToDraw = [

  Variable('OptID_Muon_Inclusive', '', ''),
  Variable('OptID_Muon_v1', '', ''),
  Variable('OptID_Muon_v2', '', ''),
  #Variable('OptID_Electron_FillEventCutflow', '', ''),


]
m.PrintVariables()

#### Draw
m.Draw()
#m.DoCutFlow('NEvent')
