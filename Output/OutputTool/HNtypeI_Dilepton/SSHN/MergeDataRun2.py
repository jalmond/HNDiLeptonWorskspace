import os,sys
sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *

analyzername="HNtypeI_Dilepton"

outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/Run2/"
MakeDirectory(outpath)

inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"                                                                                              


if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_DoubleEG.root"):
    os.remove(outpath + analyzername+"_SkimTree_SSHN_DoubleEG.root")

os.system("hadd " + outpath + analyzername+"_SkimTree_SSHN_DoubleEG.root "
          + inpath + "2016/isEE__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleEG* "
          + inpath + "2017/isEE__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleEG* "
          + inpath + "2018/isEE__/DATA/" + analyzername+"_SkimTree_SSHN_EGamma* " )

if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_Muon.root"):
    os.remove(outpath + analyzername+"_SkimTree_SSHN_Muon.root")
    
os.system("hadd " + outpath + analyzername+"_SkimTree_SSHN_Muon.root "
          + inpath + "2016/isMM__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2017/isMM__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2018/isMM__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2017/isSingleMu__/DATA/" + analyzername+"_SkimTree_SSHN_SingleMuon* "
          + inpath + "2018/isSingleMu__/DATA/" + analyzername+"_SkimTree_SSHN_SingleMuon* " )

