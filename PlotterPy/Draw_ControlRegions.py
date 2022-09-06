import os,ROOT,sys

WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']

sys.path.insert(1, WORKING_DIR+'/python')

from Plotter import SampleGroup, Variable, Region, Systematic
from Plotter import Plotter
from IsCorrelated import IsCorrelated

import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)

#if not os.path.exists('/tmp/ssh-jalmond@lxplus.cern.ch'):
from GeneralSetup import check_lxplus_connection
check_lxplus_connection()


## Arguments

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-c', dest='Category', type=int, default=0)
parser.add_argument('-y', dest='Year', type=int, default=0)
parser.add_argument('-e', dest='Era', type=str, default='NULL')
parser.add_argument('--debug',action='store_true')
parser.add_argument('--ScaleMC', action='store_true')
args = parser.parse_args()

Analyser='HNL_ControlRegionPlotter'
OutPutOnLxplus=True
## Enviroment

dataset = os.environ['FLATVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

m = Plotter()

m.DoDebug = args.debug

#### In/Out

if args.Year > 0:
  m.DataEra = str(args.Year)
  m.DataYear=str(args.Year)

else:
  
  if not args.Era == "NULL":
    m.DataEra = args.Era
    if "2016" in args.Era:
      m.DataYear = 2016
    else:
      m.DataYear = int(args.Era)
  else:
    m.DataEra = "YearCombined"
    m.DataYear = -1
      

print ("DataYear Set to " + str(m.DataYear))
print ("DataEra Set to " + str(m.DataEra))


AllowedEras=["2016","2016preVFP","2016postVFP","2017","2018", "YearCombined"]
if not m.DataEra in AllowedEras:
  print("Era input is incorrect")
  exit()


m.InputDirectory = WORKING_DIR+'/InputFiles/MergedFiles/'+dataset+"/"+Analyser+"/"

str_Era=m.DataEra

#HNtypeI_Dilepton_SkimTree_HNMultiLep_Electron.root
m.DataDirectory = str_Era
m.Filename_prefix = Analyser
m.Filename_suffix = ""
m.Filename_skim = "_SkimTree_Dilepton"
m.Filename_data_skim = ""

m.OutputDirectoryLocal = ENV_PLOT_PATH+"/"+dataset+"/"+Analyser+"/"+str_Era+"/"
os.system('mkdir -p '+ m.OutputDirectoryLocal)
if args.ScaleMC:
  os.system('mkdir -p '+ m.OutputDirectoryLocal+'/ScaleMC/')
  

if OutPutOnLxplus:
  m.OutputDirectory = "/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/"+Analyser+"/"+str_Era+"/"
  print "-"*40
  print("ssh jalmond@lxplus.cern.ch 'mkdir -p " + m.OutputDirectory + "'")
  print "-"*40
  os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p " + m.OutputDirectory + "'")


#### Category
m.ScaleMC = args.ScaleMC

#### Systematic
tmp_Systematics = [
  "Lumi",
  "GetMCUncertainty",
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

SetBinningPerEra=False

if not SetBinningPerEra:
  #### Binning infos
  m.SetBinningFilepath(
    WORKING_DIR+'/data/'+dataset+'/YearCombined/Rebins.txt',
    WORKING_DIR+'/data/'+dataset+'/YearCombined/Xaxis.txt',
    WORKING_DIR+'/data/'+dataset+'/YearCombined/CR_yaxis.txt',
  )
else:
  
  m.SetBinningFilepath(
    WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/CR_rebins.txt',
    WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/CR_xaxis.txt',
    WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/CR_yaxis.txt',
  )


#### Predef samples
from PredefinedSamples import *

###############
#### DY CR ####
###############

if args.Category==0:
  #### Define Samples
  if str_Era != 'YearCombined':
        exec('m.SampleGroups = [SampleGroup_NonPrompt_MuMu_%s,SampleGroup_Conv_%s, SampleGroup_VV_%s,  SampleGroup_VVV_%s , SampleGroup_Other_%s  ]'%(m.DataEra,m.DataEra, m.DataEra, m.DataEra, m.DataEra))
  else:
    m.SampleGroups = [
      SampleGroup_TTLL_2016preVFP,SampleGroup_TTLL_2016postVFP,SampleGroup_TTLL_2017,SampleGroup_TTLL_2018,
      SampleGroup_TW_2016preVFP,SampleGroup_TW_2016postVFP,SampleGroup_TW_2017,SampleGroup_TW_2018,
      SampleGroup_VV_incl_2016preVFP, SampleGroup_VV_incl_2016postVFP, SampleGroup_VV_incl_2017, SampleGroup_VV_incl_2018,
      SampleGroup_DY_2016preVFP, SampleGroup_DY_2016postVFP, SampleGroup_DY_2017, SampleGroup_DY_2018,
    ]

  #### Signals
  #### Print
  m.PrintSamples()

  PNs=["POG_UL"]
  #### Define reiongs
  m.RegionsToDraw = [

    Region('HNL_WZ_ThreeLepton_CR', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    
  ]
  m.PrintRegions()


#### Define Variables
m.VariablesToDraw = [
  Variable('Lep_1_pt', 'p_{T} of the leading lepton', 'GeV'),
  Variable('Lep_2_pt', 'p_{T} of the second lepton', 'GeV'),
  Variable('Lep_3_pt', 'm(ll)','GeV'),
  #Variable('NJets', 'N_{j}',''),
  #Variable('NBJets', 'N_{bj}',''),
  #Variable('nPV', 'N_{pv}',''),
  #Variable('PuppiMETType1XY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),

]
m.PrintVariables()

#### Draw
m.Draw()
print (str(m.Filename_prefix))

#m.DoCutFlow('NJets')
