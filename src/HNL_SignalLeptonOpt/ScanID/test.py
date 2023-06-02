import os

from HNLArxiv import HNLArxiv


#HNL = HNLArxiv("testClass","EXO-17-028")
#HNL.GetEXO_17_028_Eff("MuMu","SR1","100","DY")
#HNL.GetXSecUnityCoupling(100,"DY")
#HNL.GetXSecUnityCoupling(100,"VBF")
#HNL.GetXSecUnityCoupling(100,"SSWW")

HNL = HNLArxiv("testClass","EXO-21-003")
HNL.Debug()
#HNL.GetXSecUnityCoupling(100,"DY")
HNL.GetLimits()
