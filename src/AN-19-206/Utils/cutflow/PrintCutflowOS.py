import ROOT,os

Eras=["Run2"]
InputDir="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/Jan23/"


Channels = ["EE"]

for Era in Eras:

    file_path=InputDir+ Era+"/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_FullBkg.root"
        
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
            print(f"Histogram: {histogram.GetName()}")
            for bin_idx in range(1, histogram.GetNbinsX() + 1):  # Bins are 1-indexed in ROOT
                bin_label = histogram.GetXaxis().GetBinLabel(bin_idx)  # Get the bin label (if any)
                bin_content = histogram.GetBinContent(bin_idx)  # Get the bin content
                bin_center = histogram.GetXaxis().GetBinCenter(bin_idx)  # Get the bin center (optional)
        
                # Print the information
                if bin_label:  # If the bin has a label
                    print(f"Bin {bin_idx}: Label = {bin_label}, Content = {bin_content}")
                else:  # If the bin does not have a label
                    print(f"Bin {bin_idx}: Center = {bin_center}, Content = {bin_content}")
        else:
            print("Histogram not found or is not a valid TH1.")


        

    # Close the ROOT file when done
    root_file.Close()
