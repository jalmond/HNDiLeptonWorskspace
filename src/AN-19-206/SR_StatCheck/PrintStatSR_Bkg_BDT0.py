import os ,ROOT
   
    
Eras = ["2016preVFP","2016postVFP","2017","2018"] 
DateTag="Jan15"
ID="HNL_ULIDv2"
Channels=[["MuMu","Muon"], ["EE","Electron"],["EMu","ElectronMuon"]]
SRs = ["SR3BDT"]

for Channel in Channels:
    for Era in Eras:
        LogTotals = []
        for SR in SRs:
            
            Mass="100"
            Label_loop = Mass + "_"+Channel[0]+"_"+Era+"_"+SR

            path_bkg = "/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+Era+"/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_Bkg.root"
    
            
            file_bkg = ROOT.TFile.Open(path_bkg)

            if not file_bkg or file_bkg.IsZombie():
                print("Error: Could not open file")
                exit()
            else:
                print("Opening " + path_bkg)
            
            print("LimitExtractionBDT/"+ID+"/"+Channel[0]+"/M"+Mass+"/LimitBins/"+Channel[1] + SR)
            SRHist = file_bkg.Get("LimitExtractionBDT/"+ID+"/"+Channel[0]+"/M"+Mass+"/LimitBins/"+Channel[1] + SR)

            # Check if histogram was retrieved successfully
            if not SRHist or not isinstance(SRHist, ROOT.TH1):
                print("Error: Histogram not found or wrong type")
                exit()

            # Get number of bins in X and Y directions
            nbinsX = SRHist.GetNbinsX()


            
            Bkgs = ["Prompt","Conv","Fake","Total"]
            if Channel[0] == "EE":
                Bkgs = ["Prompt","Conv","CF","Fake","Total"]

            # Loop over all bins
            for ix in range(1, nbinsX + 1):  # Bins start from 1 in ROOT
                binlabelX= SRHist.GetXaxis().GetBinLabel(ix) + " "*(15-len(SRHist.GetXaxis().GetBinLabel(ix)))
                content  = round(SRHist.GetBinContent(ix), 3)
                scontent = str(content)  + " "*(10-len(str(content)))
                error    = round(SRHist.GetBinError(ix), 3)
                error_perc = 100*error / content if content > 0 else 0.00
                error_perc = round(error_perc,3)
                #print(f"Bin ({ix}): Content = {content}, Error = {error}")
                serror = str(error)  + " "*(6-len(str(error)))
                
                print(f"Bin ({binlabelX}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}")

            # Close the file
            file_bkg.Close()
        
    
        for x in LogTotals:
            print(x)

        with open( "SR_"+Channel[0]+"_"+Era + "_"+Mass+"_Bkgs.txt" , "w") as ofile:
            for item in LogTotals:
                ofile.write(f"{item}\n")  # Writes each element on a new line
        

