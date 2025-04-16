import ROOT,os


InputDir="/data9/Users/jalmond_public/SUS-24-014/HNL_SignalRegion_Plotter_ANv3/2017/RunSyst__/"


import argparse
parser = argparse.ArgumentParser(description='option')
parser.add_argument('-ch', dest='ch', default="MuMu")
parser.add_argument('-sig', dest='sig', default="SSWW")
parser.add_argument('-m', dest='mass', default="1000")

args = parser.parse_args()

Channels = [args.ch]
Signals=[args.sig+"_M"+args.mass+"_private"]

Era="2017"

Systs=[["Central",""] ,
       
       ["JESDown","Syst_JetEnDown"], ["PNETDown","Syst_JetPNETDown"], ["BTagSFHTagDown","Syst_BTagSFHTagDown"], ["BTagSFLTagDown","Syst_BTagSFLTagDown"],       ["ElectronEnDown","Syst_ElectronEnDown"], ["ElectronResDown","Syst_ElectronResDown"],["JetPUIdDown","Syst_JetPUIDDown"], ["JetResDown","Syst_JetResDown"],    ["METUnclDown","Syst_METUnclDown"], ["PDFDown","Syst_PDFDown"],["PUDown","Syst_PUDown"], ["PrefireDown", "Syst_PrefireDown"], ["ScaleDown","Syst_ScaleDown"],
       
       ["JESUp","Syst_JetEnUp"], ["PNETUp","Syst_JetPNETUp"], ["BTagSFHTagUp","Syst_BTagSFHTagUp"], ["BTagSFLTagUp","Syst_BTagSFLTagUp"],       ["ElectronEnUp","Syst_ElectronEnUp"], ["ElectronResUp","Syst_ElectronResUp"],["JetPUIdUp","Syst_JetPUIDUp"], ["JetResUp","Syst_JetResUp"],    ["METUnclUp","Syst_METUnclUp"], ["PDFUp","Syst_PDFUp"],["PUUp","Syst_PUUp"], ["PrefireUp", "Syst_PrefireUp"], ["ScaleUp","Syst_ScaleUp"]]


       
Results=[]
for Signal in Signals:
    
    Histname="SR_Summary"
    file_path=InputDir+"/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+Signal+".root"
        
    # Open the ROOT file

    root_file = ROOT.TFile.Open(file_path, "READ")    
    if os.path.exists(file_path):

        if root_file and not root_file.IsZombie():
            print(f"Successfully opened ROOT file: {file_path}")
            # Perform operations on the file
            root_file.ls()  # List the contents of the file
        else:
            print(f"Failed to open ROOT file: {file_path}. The file might be corrupted or unreadable.")

    for channel in Channels:
        for Syst in Systs:
            SYST=Syst[0]
            SYSTDIR=Syst[1]
            
            # Access a specific directory inside the ROOT file
            histogram= root_file.Get("ChannelCutFlow/"+SYSTDIR+"HNL_ULIDv2/"+channel+"/"+Histname)  # Replace 'directory_name' with the actual directory name
            

            # Check if the histogram was successfully retrieved
            HistBins=[]
            if histogram and isinstance(histogram, ROOT.TH1):
                # Loop over bins in the histogram
                print(f"Histogram: {histogram.GetName()}")
                for bin_idx in range(1, histogram.GetNbinsX() + 1):  # Bins are 1-indexed in ROOT
                    if "Inclusive" in histogram.GetXaxis().GetBinLabel(bin_idx):
                        continue
                    bin_label = histogram.GetXaxis().GetBinLabel(bin_idx)  # Get the bin label (if any)
                    bin_content = histogram.GetBinContent(bin_idx)  # Get the bin content
                    if bin_content == 0 :
                        bin_content=0.001
                    bin_center = histogram.GetXaxis().GetBinCenter(bin_idx)  # Get the bin center (optional)
                    HistBins.append([bin_label,bin_content])
                    # Print the information
                    if bin_label:  # If the bin has a label
                        print(f"{Era} {SYST} Bin {bin_idx}: Label = {bin_label}, Content = {bin_content}")
                    else:  # If the bin does not have a label
                        print(f"{Era} {SYST} Bin {bin_idx}: Center = {bin_center}, Content = {bin_content}")
            else:
                print("Histogram not found or is not a valid TH1.")
            Results.append([SYST,HistBins,Signal,channel])

        

    # Close the ROOT file when done
    root_file.Close()
    

CentralResult = Results[0]
for item in Results:
    # Print the first element
    print("-"*50)
    print(f"First element: {item[0]}")
    # Print the content of the second element, which is a sub-list
    print("Sub-list elements:")


    for i in range(len(item[1])):
        #print(f"  {item[1][i]}")
        diff_sys= 100*(1-item[1][i][1] / CentralResult[1][i][1])
        print(f"RESULT  {item[3]} {item[2]} {item[0]} Systemaic Diff [{CentralResult[1][i][0]}]=  {diff_sys}")
        
