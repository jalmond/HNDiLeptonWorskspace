import os 

Eras = ["2016preVFP","2016postVFP","2017","2018"]

for Era in Eras:

    Hists = [
        ["TopJets_TightMu/","ElectronJet_PtRatio_TightMuE", "p_{T} Inclusive",  "0","2","2."]
    ]

    for Hist  in Hists:
        print("root -l -q -b 'BDTInputVariablesJetVar.C(\""+Era+"\",\""+Hist[0]+"\",\""+Hist[1]+"\",\""+Hist[2]+"\","+str(Hist[3])+","+str(Hist[4])+","+str(Hist[5])+",\""+Hist[1]+"\")'")
        os.system("root -l -q -b 'BDTInputVariablesJetVar.C(\""+Era+"\",\""+Hist[0]+"\",\""+Hist[1]+"\",\""+Hist[2]+"\","+str(Hist[3])+","+str(Hist[4])+","+str(Hist[5])+",\""+Hist[1]+"\")'")



            
            

