import os 

Eras = ["2016preVFP","2016postVFP","2017","2018"]

for Era in Eras:
    
    Hists = [ 
        ["TopJets_TightMu/","CJ_NonPromptLep_JetDisc_DeepJet_gt35_Electron_TightMuE", "p_{T} > 35 GeV", "0","1","10."],
        ["TopJets_TightMu/","CJ_NonPromptLep_JetDisc_DeepJet_lt35_Electron_TightMuE", "20 < p_{T} > 35 GeV", "0","1","10."],
        ["TopJets_TightMu/","CJ_NonPromptLep_JetDisc_DeepJet_lt20_Electron_TightMuE", "p_{T} < 20 GeV", "0","1","10."],
        ["TopJets_TightMu/","CJ_NonPromptLep_JetDisc_DeepJet_Electron_TightMuE", "p_{T} Inclusive", "0","1","10."],
    ]

    Hists = [
        ["ZJets_EE/","CJ_NonPromptLep_JetDisc_DeepJet_Electron_TightEMu", "p_{T} Inclusive",  "0","2","10."],
        ["ZJets_MuMu/","CJ_NonPromptLep_JetDisc_DeepJet_Muon_TightMuE", "p_{T} Inclusive",  "0","2","10."]
        
    ]

    for Hist  in Hists:
        print("root -l -q -b 'BDTInputVariablesJetDisc.C(\""+Era+"\",\""+Hist[0]+"\",\""+Hist[1]+"\",\""+Hist[2]+"\","+str(Hist[3])+","+str(Hist[4])+","+str(Hist[5])+",\""+Hist[1]+"\")'")
        os.system("root -l -q -b 'BDTInputVariablesJetDisc.C(\""+Era+"\",\""+Hist[0]+"\",\""+Hist[1]+"\",\""+Hist[2]+"\","+str(Hist[3])+","+str(Hist[4])+","+str(Hist[5])+",\""+Hist[1]+"\")'")



            
            

