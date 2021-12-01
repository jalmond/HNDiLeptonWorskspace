import os,ROOT
from Plotter import SampleGroup, Variable, Region, Systematic
from Plotter import Plotter
from IsCorrelated import IsCorrelated
import argparse

ROOT.gROOT.SetBatch(ROOT.kTRUE)


## Arguments

parser = argparse.ArgumentParser(description='CR plot commands')
parser.add_argument('-c', dest='Category', type=int, default=0)
parser.add_argument('-y', dest='Year', type=int)
parser.add_argument('--debug',action='store_true')
parser.add_argument('--ScaleMC', action='store_true')
parser.add_argument('--ApplyZPtRwg', action='store_true')
parser.add_argument('--ApplyDYReshape', action='store_true')
args = parser.parse_args()

## Enviroment

WORKING_DIR = os.environ['PLOTTER_WORKING_DIR']
dataset = os.environ['SKANVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

m = Plotter()

m.DoDebug = args.debug

#### In/Out
m.DataYear = args.Year
str_Year = str(args.Year)
#m.InputDirectory = WORKING_DIR+'/rootfiles/'+dataset+"/Regions/"
m.InputDirectory = WORKING_DIR+'/InputFiles/MergedFiles/'+dataset+"/HNL_DileptonCR/"

if args.Year<0:
  str_Year = 'YearCombined'

#HNtypeI_Dilepton_SkimTree_HNMultiLep_Electron.root
m.DataDirectory = str_Year
m.Filename_prefix = "HNL_DileptonCR"
m.Filename_suffix = ""
m.Filename_skim = "_SkimTree_HNMultiLep"

m.OutputDirectory = ENV_PLOT_PATH+"/"+dataset+"/CR/"+str_Year+"/"

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
        exec('m.SampleGroups = [SampleGroup_Top_%s, SampleGroup_WZ_powheg_%s,  SampleGroup_ZZ_powheg_%s,SampleGroup_NonPrompt_Muon_%s, SampleGroup_DY_%s , SampleGroup_CF_%s,SampleGroup_Others_%s,SampleGroup_ZG_%s, SampleGroup_WG_%s ]'%(args.Year,args.Year, args.Year,args.Year,args.Year,args.Year,args.Year,args.Year,args.Year))
  else:
    m.SampleGroups = [
      SampleGroup_Others_2016, SampleGroup_Others_2017, SampleGroup_Others_2018,
      SampleGroup_NonPrompt_2016, SampleGroup_NonPrompt_2017, SampleGroup_NonPrompt_2018,
      SampleGroup_TT_TW_2016, SampleGroup_TT_TW_2017, SampleGroup_TT_TW_2018,
      SampleGroup_DY_2016, SampleGroup_DY_2017, SampleGroup_DY_2018,
    ]

  #### Signals
  #### Print
  m.PrintSamples()

  IDs=["POG"]
  #### Define reiongs
  m.RegionsToDraw = [
    Region('HNL_HighMass1Jet_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMass1Jet_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassNP_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassNP_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassSR1_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassSR1_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassSR2_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_OSPresel_TwoLepton_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_HighMassSR2_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_OSPresel_TwoLepton_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_SSPresel_TwoLepton_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_SSPresel_TwoLepton_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_SSVBFPresel_TwoLepton_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_SSVBFPresel_TwoLepton_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_TopAK8_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_TopAK8_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZ2_ThreeLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZ2_ThreeLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZB_ThreeLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZB_ThreeLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZ_ThreeLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WZ_ThreeLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WpWpNP_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WpWpNP_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WpWp_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_WpWp_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZAK8_TwoLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZAK8_TwoLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZG_ThreeLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZG_ThreeLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZNP_ThreeLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZNP_ThreeLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZZLoose_FourLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZZLoose_FourLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZZ_FourLepton_CR_OptID_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    Region('HNL_ZZ_FourLepton_CR_Version1_Electron' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),

    #Region('HNL_WZ_ThreeLepton_CR_Electron_HNtypeI_Dilepton_Version1' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    #Region('HNL_WZ_ThreeLepton_CR_Muon_HNtypeI_Dilepton_Version1' , 'Muon', UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#muX}{WZ->lll CR}'),   
    #Region('HNL_WZ_ThreeLepton_CR_Electron_HNtypeI_Dilepton_EXO17028' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    #Region('HNL_WZ_ThreeLepton_CR_Muon_HNtypeI_Dilepton_EXO17028' , 'Muon', UnblindData=True, Logy=0, TLatexAlias='#splitline{#mu#muX}{WZ->lll CR}'),
    #Region('HNL_WZ_ThreeLepton_CR_Electron_HNtypeI_Dilepton_Opt' , 'Electron', UnblindData=True, Logy=0, TLatexAlias='#splitline{eeX}{WZ->lll CR}'),
    
    #Region('HNWR_SingleMuon_Boosted_DYCR', 'SingleMuon', UnblindData=True, Logy=1, TLatexAlias='#splitline{#mu#mu}{Boosted DY CR}'),
  ]
  m.PrintRegions()

######################
#### emu sideband ####
######################



#### Define Variables
m.VariablesToDraw = [
  Variable('pt_Lep1', 'p_{T} of the leading lepton', 'GeV'),
  Variable('pt_Lep2', 'p_{T} of the leading lepton', 'GeV'),
  Variable('MET', '#slash{E}_{T}^{miss} (GeV)', 'GeV'),
  Variable('M_ll', 'm(ll)',''),
  Variable('M_lll', 'm(lll)',''),

]
m.PrintVariables()

#### Draw
m.Draw()
m.DoCutFlow('NEvent')
