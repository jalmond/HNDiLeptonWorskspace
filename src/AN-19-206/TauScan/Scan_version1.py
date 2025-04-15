import ROOT

# List of input ROOT file paths
files = [
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1000_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M100_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1100_private.root",
    # Add the rest of your file paths here
]

# Path template for histogram of interest
histogram_template = "ChannelCutFlow/{}/LL/ChannelDependant_Presel"

# Initialize ROOT for histogram plotting
ROOT.gStyle.SetOptStat(0)

# Loop over each file
for file_path in files:
    try:
        # Open the ROOT file
        file = ROOT.TFile.Open(file_path)
        
        # Get the list of directories in the ROOT file under 'ChannelCutFlow'
        channel_cutflow_dir = file.Get("ChannelCutFlow")
        
        if not channel_cutflow_dir:
            print(f"ChannelCutFlow directory not found in {file_path}")
            continue
        
        # Loop through each directory under 'ChannelCutFlow'
        for dir_name in channel_cutflow_dir.GetListOfKeys():
            dir_name_str = dir_name.GetName()
            
            # Form the histogram path for this directory
            histogram_path = histogram_template.format(dir_name_str)
            
            # Get the histogram for this path
            histogram = file.Get(histogram_path)
            
            if not histogram:
                print(f"Histogram {histogram_path} not found in {file_path}")
                continue
            
            # Print out the bin entries for the histogram
            print(f"Bin entries for {file_path} - {histogram_path}:")
            for i in range(1, histogram.GetNbinsX() + 1):
                print(f"Bin {i}: {histogram.GetBinContent(i)} entries")
        
        file.Close()  # Close the file

    except Exception as e:
        print(f"Error processing file {file_path}: {e}")
