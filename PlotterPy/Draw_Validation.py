import os,ROOT,sys

WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']

sys.path.insert(1, WORKING_DIR+'/python')

from Plotter import SampleGroup, Variable, Region, Systematic
from Plotter import Plotter
from IsCorrelated import IsCorrelated
import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)

if not os.path.exists('/tmp/ssh-jalmond@lxplus.cern.ch'):
  print('Setup lxplus connection ')
  exit()

## Arguments

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-c', dest='Category', type=int, default=0)
parser.add_argument('-y', dest='Year', type=int, default=0)
parser.add_argument('-e', dest='Era', type=str, default='NULL')
parser.add_argument('--debug',action='store_true')
parser.add_argument('--ScaleMC', action='store_true')
args = parser.parse_args()

Analyser='HNL_Validation'
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
        exec('m.SampleGroups = [SampleGroup_TTLL_%s,SampleGroup_TW_%s, SampleGroup_VV_incl_%s,  SampleGroup_DY_%s ]'%(m.DataEra,m.DataEra, m.DataEra, m.DataEra))
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

    #Region('RegionPlots_ZPeakTruthMatched_BTagSF', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ), 
    #Region('RegionPlots_DiLep_LumiWeight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_PileUpWight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_LeptonID', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_DiLep_BTagSF', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_DYReweight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_TopRW', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    #Region('RegionPlots_ZPeak_DYReweight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_LeptonID', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_LumiWeight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_ZPeak_BTagSF', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_TopRW', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_PileUpWight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    #Region('RegionPlots_BJetCR_PileUpWight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_BJetCR_TopRW', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_BTagSF', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events# in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_LeptonID', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_LumiWeight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_PileUpWight', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_TopRW', 'MuMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    
    #Region('RegionPlots_ZPeakTruthMatched_BTagSF', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_LumiWeight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_PileUpWight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_LeptonID', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_DiLep_BTagSF', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_DYReweight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_DiLep_TopRW', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll CR (M>50)}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    #Region('RegionPlots_ZPeak_DYReweight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_LeptonID', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_LumiWeight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_BTagSF', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_TopRW', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_ZPeak_PileUpWight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{DY->ll Z-Peak}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),

    #Region('RegionPlots_BJetCR_PileUpWight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    Region('RegionPlots_BJetCR_TopRW', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_BTagSF', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_LeptonID', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_LumiWeight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_PileUpWight', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),
    #Region('RegionPlots_BJetCR_TopRW', 'EMu', PNs[0],  UnblindData=True, Logy=0, TLatexAlias='#splitline{e#mu}{Top->ll CR}', CutFlowCaption='Number of Events in Zmass Window (SingleMuon Trigger). Truth matching applied' ),


    
  ]
  m.PrintRegions()


#### Define Variables
m.VariablesToDraw = [
  #Variable('Lep1Pt', 'p_{T} of the leading lepton', 'GeV'),
  #Variable('Lep2Pt', 'p_{T} of the second lepton', 'GeV'),
  #Variable('LLMass', 'm(ll)','GeV'),
  #Variable('NJets', 'N_{j}',''),
  #Variable('NBJets', 'N_{bj}',''),
  #Variable('nPV', 'N_{pv}',''),
  #Variable('PuppiMETType1XY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  Variable('PFMETPhiType1', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PFMETPhiType1POGXY', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PFMETPhiType1XY', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  #Variable('PFMETType1', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PFMETType1POGXY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PFMETType1XY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  Variable('PuppiMETPhiType1', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PuppiMETPhiType1POGXY', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PuppiMETPhiType1XY', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PuppiMETPhiType1XYSmeared', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  Variable('PuppiMETPhiType1XYSmeared2', '#slash{E}_{T}^{miss} (#phi)', '#phi'),
  #Variable('PuppiMETType1', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PuppiMETType1POGXY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PuppiMETType1XY', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PuppiMETType1XYSmeared', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  #Variable('PuppiMETType1XYSmeared2', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),


]
m.PrintVariables()

#### Draw
#m.Draw()
print (str(m.Filename_prefix))

m.DoCutFlow('NJets')
