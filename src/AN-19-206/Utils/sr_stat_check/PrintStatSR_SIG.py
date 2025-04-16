import os ,ROOT
   
Eras = ["2016preVFP","2016postVFP","2017","2018"]
DateTag="Jan20"
ID="HNL_ULIDv2"
Channels=[["MuMu","Muon"], ["EE","Electron"],["EMu","ElectronMuon"]]
SRs = ["SR1","SR2","SR3"]
Signames= ["DY_MN100",
           "DY_MN200",
           "DYVBF_MN500",
           "DYVBF_MN1000",
           "DYVBF_MN2000",
           "SSWW_MN750",
           "SSWW_MN1000",
           "SSWW_MN10000",
           "SSWW_MN20000",
           "Weinberg"]


for Signame in Signames:
    for Channel in Channels:
        for Era in Eras:
            LogTotals = []
            for SR in SRs:
            
                Label_loop = Channel[0]+"_"+Era+"_"+SR

                path_bkg = "/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+Era+"/SIG/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+Signame+".root"
                
                file_bkg = ROOT.TFile.Open(path_bkg)

                if not file_bkg or file_bkg.IsZombie():
                    print("Error: Could not open file")
                    exit()
                else:
                    print("Opening " + path_bkg)
                
                SRHist = file_bkg.Get("LimitExtraction/"+ID+"/"+Channel[0]+"/LimitBins/"+Channel[1] + SR)
                
                # Check if histogram was retrieved successfully
                if not SRHist or not isinstance(SRHist, ROOT.TH1):
                    print("LimitExtraction/"+ID+"/"+Channel[0]+"/LimitBins/"+Channel[1] + SR)
                    print("Error: Histogram not found or wrong type")
                    continue
                    
                # Get number of bins in X and Y directions
                nbinsX = SRHist.GetNbinsX()

            
                for ix in range(1, nbinsX + 1):  # Bins start from 1 in ROOT
                    binlabelX= SRHist.GetXaxis().GetBinLabel(ix) + " "*(15-len(SRHist.GetXaxis().GetBinLabel(ix)))
                    content  = round(SRHist.GetBinContent(ix), 3)
                    scontent = str(content)  + " "*(10-len(str(content)))
                    error    = round(SRHist.GetBinError(ix), 3)
                    error_perc = 100*error / content if content > 0 else 0.00
                    error_perc = round(error_perc,3)
                    #print(f"Bin ({ix}, {iy}): Content = {content}, Error = {error}")
                    serror = str(error)  + " "*(6-len(str(error)))
                    
                    LogTotals.append([content, f"{Label_loop} Bin ({binlabelX}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}"])
                    print(f"Bin ({binlabelX}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}")

                    

                # Close the file
                file_bkg.Close()
        
    
            LogTotals.sort(key=lambda x: x[0],reverse=True)
            
            for x in LogTotals:
                print(x[1])

            os.system("mkdir -p Text_"+DateTag)

            with open( "Text_"+DateTag+"/SR_"+Channel[0]+"_"+Era + "_"+Signame+".txt" , "w") as ofile:
                for item in LogTotals:
                    ofile.write(f"{item[1]}\n")  # Writes each element on a new line
        

