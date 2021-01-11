#void GetSignalOverB_combinedSR(TString _SR="SR2",TString channel="MuMu", TString ptbin="_HighPt",  TString year="2016",TString _chan = "Schannel"){
#void GetSignalOverB_combinedSR(TString _SR="",TString channel="MuMu", TString ptbin="",  TString year="2016",TString _chan = "Schannel"){ 

root -l -q -b 'GetSignalOverB_combinedSR.C(0,"","MuMu","","Schannel")'
root -l -q -b 'GetSignalOverB_combinedSR.C(1,"","MuMu","","Schannel")'
root -l -q -b 'GetSignalOverB_combinedSR.C(2,"","MuMu","","Schannel")'

root -l -q -b 'GetSignalOverB_combinedSR.C(0,"","EE","","Schannel")'

root -l -q -b 'GetSignalOverB_combinedSR.C(1,"","EE","","Schannel")'

root -l -q -b 'GetSignalOverB_combinedSR.C(2,"","EE","","Schannel")'

root -l -q -b 'GetSignalOverB_combinedSR.C(3,"","EE","","Schannel")'

root -l -q -b 'GetSignalOverB_combinedSR.C(4,"","EE","","Schannel")'
