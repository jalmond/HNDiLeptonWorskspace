import os,ROOT,sys

WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']

sys.path.insert(1, WORKING_DIR+'/python')

from Plotter import SampleGroup, Variable, Region, Systematic
from Plotter import Plotter
from IsCorrelated import IsCorrelated

import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)

#if not os.path.exists('/tmp/ssh-jalmond@lxplus.cern.ch'):
from GeneralSetup import check_lxplus_connection,GetFromConfig
check_lxplus_connection()


## Arguments

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-c', dest='Category', type=int, default=0)
parser.add_argument('-y', dest='Year', type=int, default=0)
parser.add_argument('-e', dest='Era', type=str, default='NULL')
parser.add_argument('--debug',action='store_true')
parser.add_argument('--ScaleMC', action='store_true')
args = parser.parse_args()

Analyser='HNL_FakeRate'
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
m.Filename_skim = ""
m.Filename_data_skim = ""

m.OutputDirectoryLocal = ENV_PLOT_PATH+"/"+dataset+"/"+Analyser+"/"+str_Era+"/"
os.system('mkdir -p '+ m.OutputDirectoryLocal)
if args.ScaleMC:
  os.system('mkdir -p '+ m.OutputDirectoryLocal+'/ScaleMC/')
  

# check connection to lxplus is open
check_lxplus_connection()

#set username for lxplus
m.Lxplus_User = GetFromConfig('LXPLUS_USER')
m.Lxplus_Dir = GetFromConfig('LXPLUS_Dir')


if OutPutOnLxplus:
  m.OutputDirectory = m.Lxplus_Dir
  print "-"*40
  print("ssh "+m.Lxplus_User+"@lxplus.cern.ch 'mkdir -p " + m.OutputDirectory + "'")
  print "-"*40
  os.system("ssh "+m.Lxplus_User+"@lxplus.cern.ch 'mkdir -p " + m.OutputDirectory + "'")


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

m.SetBinningFilepath(
  WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/Fake_rebins.txt',
  WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/Fake_xaxis.txt',
  WORKING_DIR+'/data/'+dataset+'/'+str_Era+'/Fake_yaxis.txt',
)


#### Predef samples
from PredefinedSamples import *

###############
#### DY CR ####
###############

if args.Category==0:
  #### Define Samples
  if str_Era != 'YearCombined':
        exec('m.SampleGroups = [SampleGroup_QCD_%s,SampleGroup_TTLJ_%s, SampleGroup_DY_%s,  SampleGroup_WJets_%s ]'%(m.DataEra,m.DataEra, m.DataEra,  m.DataEra))
  else:
    m.SampleGroups = [ SampleGroup_QCD_2016preVFP, SampleGroup_QCD_2016postVFP, SampleGroup_QCD_2017, SampleGroup_QCD_2018,
                       SampleGroup_TTLJ_2016preVFP,SampleGroup_TTLJ_2016postVFP,SampleGroup_TTLJ_2017,SampleGroup_TTLJ_2018,
                       SampleGroup_DY_2016preVFP, SampleGroup_DY_2016postVFP, SampleGroup_DY_2017, SampleGroup_DY_2018,
                       SampleGroup_WJets_2016preVFP, SampleGroup_WJets_2016postVFP, SampleGroup_WJets_2017, SampleGroup_WJets_2018  ]

  #### Signals
  #### Print
  m.PrintSamples()

  PNs=["POG_UL"]
  #### Define reiongs
  m.RegionsToDraw = [

    #Region('RegionPlots_SingleLooseMuJet_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{SingleLooseMu}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_SingleLooseMuAwayJet_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{SingleLooseMu+AwayJet}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_SingleTightMuAwayJet_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{TightMu+AwayJet}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_SingleTightMuAwayJet_promptCR2_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{Prompt CR2}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_SingleTightMuAwayJet_promptCR_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{60  < MT < 100}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_TightMu40_MuMu_HNTightV2', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{Measurement Region}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),


    #Region('RegionPlots_SingleLooseElJet_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{el}{SingleLooseEl}', CutFlowCaption='Number of Events in Zmass Window (SinTrigger). Truth matching applied' ),
    Region('RegionPlots_SingleLooseElAwayJet_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{el}{SingleLooseEl+AwayJet}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_SingleTightElAwayJet_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{el}{TightEl+AwayJet}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_SingleTightElAwayJet_promptCR2_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{Prompt CR2}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_SingleTightElAwayJet_promptCR_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{60  < MT < 100}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_TightEl40_EE_HNTightV2', 'EE', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu}{Measurement Region}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),



    #KEY: TDirectoryFileRegionPlots_Dilep;1RegionPlots_Dilep

    
  ]
  m.PrintRegions()


#### Define Variables
m.VariablesToDraw = [
  Variable('Lep1_binned_pt', 'p_{T} of the leading lepton', 'GeV'),
  Variable('Lep1_pt', 'p_{T} of the leading lepton', 'GeV'),
  Variable('Lep1_eta', '#eta of the leading lepton', ''),
  Variable('JetLepPtRatio', 'J p_{T} / Lep p_{T} ', ''),
  Variable('Met', 'MET', 'GeV'),
  Variable('MetPhi', '#phi MET', 'GeV'),
  Variable('Mt', 'MT', 'GeV'),
  Variable('njets', 'NJet', ''),
  

]
m.PrintVariables()

#### Draw
m.Draw()
print (str(m.Filename_prefix))

#m.DoCutFlow('NJets')
