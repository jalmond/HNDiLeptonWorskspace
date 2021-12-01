import os,ROOT,math
import CMS_lumi, tdrstyle
from array import array
import mylib,canvas_margin
import copy

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)

FILE_MERGED_PATH = os.environ['FILE_MERGED_PATH']
FILE_PATH = os.environ['FILE_PATH']
PLOT_PATH = os.environ['PLOT_PATH']

Years = [
    "2016preVFP",
    "2016postVFP",
    "2017",
    "2018",
]

TriggersElectron = ['HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v',
                    'HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v',
                     'HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v',
                     'HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v',
                     'HLT_Ele27_WPTight_Gsf_v',
                     'HLT_Ele32_WPTight_Gsf_v',
                     'HLT_Ele35_WPTight_Gsf_v']


TriggersMuon = [ 
    'HLT_IsoMu24_v',
    'HLT_IsoMu27_v',
    'HLT_Mu3_PFJet40_v',
    'HLT_Mu17_TrkIsoVVL_v',
    'HLT_Mu8_TrkIsoVVL_v'
]

for Year in Years:
    
    basedir = FILE_MERGED_PATH + '/PrescaledTriggerSF/'+str(Year)+'/'
    outDir = PLOT_PATH+'/'+os.environ['SKANVERSION']+'/PrescaledTriggerSF/'+str(Year)+'/'
    os.system('mkdir -p '+outDir)

    for Trigger in TriggersElectron:

        f_MC = ROOT.TFile(basedir+'/PrescaledTriggerSF_SkimTree_HNFake_DYJets.root')
        h = f_MC.Get('ZPeakData_Electron_'+Trigger+'/NEvent_ZPeakData_Electron_'+Trigger)
        if not h:
            continue
        h_Ref = h.Clone("h_RefMC"+Trigger+Year)
        mcIntegral = h_Ref.Integral()
        
        f_DATA = ROOT.TFile(basedir+'/PrescaledTriggerSF_SkimTree_HNFake_DATA.root')
        h_DATA = f_DATA.Get('ZPeakData_Electron_'+Trigger+'/NEvent_ZPeakData_Electron_'+Trigger)
        h_DATARef = h_DATA.Clone("h_RefDATA"+Trigger+Year)
        
        dataIntegral = h_DATARef.Integral()
        #print ('mcIntegral['+Trigger+'] = ' + str(mcIntegral))
        #print ('dataIntegral['+Trigger+'] = ' + str(dataIntegral))
        print (Year + ' Correction  ['+Trigger+']  = ' + str(round(dataIntegral/mcIntegral,2)))

    for Trigger in TriggersMuon:

        f_MC = ROOT.TFile(basedir+'/PrescaledTriggerSF_SkimTree_HNFake_DYJets.root')

        h = f_MC.Get('ZPeakData_Muon_'+Trigger+'/NEvent_ZPeakData_Muon_'+Trigger)
        if not h:
            continue
        mcIntegral = h.Integral()
        #print ('mcIntegral['+Trigger+'] = ' + str(mcIntegral))

        f_DATA = ROOT.TFile(basedir+'/PrescaledTriggerSF_SkimTree_HNFake_DATA.root')
        h_DATA = f_DATA.Get('ZPeakMC_Muon_'+Trigger+'/NEvent_ZPeakMC_Muon_'+Trigger)
        dataIntegral = h_DATA.Integral()
        #print ('dataIntegral['+Trigger+'] = ' + str(dataIntegral))
        
        print (Year+ ' Correction  ['+Trigger+']  = '+ str(round(dataIntegral/mcIntegral,2)))
    
