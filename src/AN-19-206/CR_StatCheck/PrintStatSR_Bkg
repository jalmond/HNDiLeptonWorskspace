import os ,ROOT
   
    
Eras = ["2018"] 
DateTag="Jan15"
ID="HNL_ULIDv2"
Channels=[["MuMu","Muon"]]
SRs = ["SR1","SR2","SR3"]


for Channel in Channels:
    for Era in Eras:
        LogTotals = []
        for SR in SRs:
            
            Label_loop = Channel[0]+"_"+Era+"_"+SR

            path_bkg = "/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/"+DateTag+"/"+Era+"/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_Bkg.root"
    
            
            file_bkg = ROOT.TFile.Open(path_bkg)

            if not file_bkg or file_bkg.IsZombie():
                print("Error: Could not open file")
                exit()
            else:
                print("Opening " + path_bkg)
            
            print("LimitExtraction/"+ID+"/"+Channel[0]+"_2D/LimitBins/"+Channel[1] + SR)
            SRHist = file_bkg.Get("LimitExtraction/"+ID+"/"+Channel[0]+"_2D/LimitBins/"+Channel[1] + SR)

            # Check if histogram was retrieved successfully
            if not SRHist or not isinstance(SRHist, ROOT.TH2):
                print("Error: Histogram not found or wrong type")
                exit()

            # Get number of bins in X and Y directions
            nbinsX = SRHist.GetNbinsX()
            nbinsY = SRHist.GetNbinsY()

            
            Bkgs = ["Prompt","Conv","Fake","Total"]
            if Channel[0] == "EE":
                Bkgs = ["Prompt","Conv","CF","Fake","Total"]

            # Loop over all bins
            for iy in range(1, nbinsY + 1):
                if not SRHist.GetYaxis().GetBinLabel(iy) in Bkgs:
                    continue

                binlabelY=SRHist.GetYaxis().GetBinLabel(iy)  + " "*(10-len(SRHist.GetYaxis().GetBinLabel(iy)))
                for ix in range(1, nbinsX + 1):  # Bins start from 1 in ROOT
                    binlabelX= SRHist.GetXaxis().GetBinLabel(ix) + " "*(15-len(SRHist.GetXaxis().GetBinLabel(ix)))
                    content  = round(SRHist.GetBinContent(ix, iy), 3)
                    scontent = str(content)  + " "*(10-len(str(content)))
                    error    = round(SRHist.GetBinError(ix, iy), 3)
                    error_perc = 100*error / content if content > 0 else 0.00
                    error_perc = round(error_perc,3)
                    #print(f"Bin ({ix}, {iy}): Content = {content}, Error = {error}")
                    serror = str(error)  + " "*(6-len(str(error)))

                    if SRHist.GetYaxis().GetBinLabel(iy) == "Total":
                        LogTotals.append(f"{Label_loop} Bin ({binlabelX}, {binlabelY}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}")
                    if content > 0:
                        print(f"Bin ({binlabelX}, {binlabelY}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}")
                    elif content<0:
                        print(f"[NEG ] Bin ({binlabelX}, {binlabelY}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}")
                    else:
                        print(f"Bin ({binlabelX}, {binlabelY}): Content = {scontent}, Error = {serror}, Error Perc. ={error_perc}  ---> 0 bin")

                if iy == 1:
                    print ("-"*50)


            # Close the file
            file_bkg.Close()
        
    
        for x in LogTotals:
            print(x)

        with open( "SR_"+Channel[0]+"_"+Era + "_Bkgs.txt" , "w") as ofile:
            for item in LogTotals:
                ofile.write(f"{item}\n")  # Writes each element on a new line
        

