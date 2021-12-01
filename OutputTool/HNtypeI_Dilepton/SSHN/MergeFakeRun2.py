import os,sys
sys.path.insert(1,os.getenv("HNDILEPTONWORKSPACE_DIR")+'/python')

from GeneralSetup import *

# now import analysis functions
from HNType1_config import *

analyzername="HNtypeI_Dilepton"
outpath = os.getenv("INFILE_MERGED_PATH") +"/"+analyzername+"/Run2/"
MakeDirectory(outpath)

inpath = os.getenv("INFILE_PATH") +"/"+analyzername+"/"                                                                                              


if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_FakeEE.root"):
    os.remove(outpath + analyzername+"_SkimTree_SSHN_FakeEE.root")

os.system("hadd " + outpath + analyzername+"_SkimTree_SSHN_FakeEE.root "
          + inpath + "2016/isEE__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleEG* "
          + inpath + "2017/isEE__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleEG* "
          + inpath + "2018/isEE__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_EGamma* " )

if os.path.exists(outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root"):
    os.remove(outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root")
    
os.system("hadd " + outpath + analyzername+"_SkimTree_SSHN_FakeMuMu.root "
          + inpath + "2016/isMM__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2017/isMM__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2018/isMM__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_DoubleMuon* "
          + inpath + "2017/isSingleMu__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_SingleMuon* "
          + inpath + "2018/isSingleMu__RunFake__/DATA/" + analyzername+"_SkimTree_SSHN_SingleMuon* " )


