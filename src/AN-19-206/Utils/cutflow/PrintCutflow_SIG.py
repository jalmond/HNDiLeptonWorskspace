import ROOT,os

Eras=["Run2"]
InputDir="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/Jan23/"


Channels = ["EE"]
Signals = ["DYTypeI_DF_M100_private","DYTypeI_DF_M500_private","VBFTypeI_DF_M500_private", "VBFTypeI_DF_M1000_private", "SSWWTypeI_SF_M1000_private", "SSWWTypeI_SF_M10000_private"]
Weights= [0.01,0.01,0.01,0.01,1,1]

Results = []

for Era in Eras:

    for Signal in Signals:

        file_path=InputDir+ Era+"/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_"+Signal+".root"
        
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
        
            # Access a specific directory inside the ROOT file
            histogram= root_file.Get("ChannelCutFlow/HNL_ULIDv2/"+channel+"/SignalRegionFlow")  # Replace 'directory_name' with the actual directory name
        

            # Check if the histogram was successfully retrieved
            if histogram and isinstance(histogram, ROOT.TH1):
                # Loop over bins in the histogram
                #print(f"Histogram: {histogram.GetName()}")
                
                NoCut=histogram.GetBinContent(1)
                for bin_idx in range(2, histogram.GetNbinsX() + 1):  # Bins are 1-indexed in ROOT
                    bin_label = histogram.GetXaxis().GetBinLabel(bin_idx)  # Get the bin label (if any)
                    bin_content = histogram.GetBinContent(bin_idx)  # Get the bin content
                    bin_center = histogram.GetXaxis().GetBinCenter(bin_idx)  # Get the bin center (optional)
                    bin_content_perc = bin_content*100/NoCut

                    bin_content=round(bin_content, 2)
                    bin_content_perc=round(bin_content_perc, 2)
                    # Print the information
                    if bin_label:  # If the bin has a label
                        print(f"{Signal} {channel} Bin {bin_idx}: Label = {bin_label}, Content = {bin_content}({bin_content_perc}%)")
                    else:  # If the bin does not have a label
                        print(f"{Signal} {channel} Bin {bin_idx}: Center = {bin_center}, Content = {bin_content}")
                    W=0.01
                    if "SSWW" in Signal:
                        W=1
                    bin_content=bin_content*W
                    Results.append([Signal, channel, bin_label, f"${bin_content:.2f}$  $({bin_content_perc:.2f}\%)$"])
            else:
                print("Histogram not found or is not a valid TH1.")


        

    # Close the ROOT file when done
    root_file.Close()



for Result in Results:
    print(f"{Result[0]} {Result[1]} {Result[2]} {Result[3]}")

Row1 = ""
nresult_sampels=[]
for Result in Results:
    
    if Result[0] in nresult_sampels:
        continue

    nresult_sampels.append(Result[0])

    SignalType = "CCDY"
    if "VBF" in Result[0]:
        SignalType = "W$\\gamma$"
    elif "SSWW" in Result[0]:
        SignalType = "SSWW"

    SignalMass = "100~$\\GeV$"
    if "M10000" in Result[0]:
        SignalMass = "10~$\\TeV$"
    elif "M1000" in Result[0]:
        SignalMass = "1~$\\TeV$"
    elif "M500" in Result[0]:
        SignalMass = "500~$\\GeV$"

    SigName = f"{SignalType} $m_{{N}}$ = {SignalMass}"
    Row1 += SigName + " "
        
print(Row1.strip())
    


Labels=[["Trigger","Trigger"], ["HEMVeto","HEMVeto"], ["METFilter","METFilter"], ["LeptonFlavour","2 $\ell$"], ["SSLepton","$\ell^{\pm} \ell^{\pm}$"],["LepVeto","3rd $\ell$ veto"],["DiLepMass","$m_{\ell \ell}$ "], ["BJet","$N_{\mathrm{B}} =0$ "],["MET","MET"]]

for Label in Labels:
    Row= "{ \\bf "+Label[1]+" }&  "
    for Result in Results:
        if Result[2] == Label[0]:
            Row=Row+" & "+ Result[3]
    Row=Row+"\\\\"
    print(Row.strip())

    

