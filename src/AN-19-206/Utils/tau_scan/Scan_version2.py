import ROOT
import numpy as np

# List of input ROOT file paths
files = [
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1000_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M100_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1100_private.root",
    # Add the rest of your file paths here
]

# Path template for histogram of interest
histogram_template = "ChannelCutFlow/{}/LL/ChannelDependant_Presel"
default_histogram_path = "ChannelCutFlow/HNL_ULIDv2Default/LL/ChannelDependant_Presel"

# Initialize ROOT for histogram plotting
ROOT.gStyle.SetOptStat(0)

# Loop over each file
for file_path in files:
    try:
        # Open the ROOT file
        file = ROOT.TFile.Open(file_path)

        # Get the default histogram
        default_histogram = file.Get(default_histogram_path)
        
        if not default_histogram:
            print(f"Default histogram {default_histogram_path} not found in {file_path}")
            continue

        # Sum of bins 1, 2, and 3 for the default histogram
        default_bin_sum = sum([default_histogram.GetBinContent(i) for i in range(1, 4)])

        # Initialize a list to store summed values for each subdirectory
        subdirectory_sums = []

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
            
            # Sum the values of bins 1, 2, and 3 for the current histogram
            subdirectory_bin_sum = sum([histogram.GetBinContent(i) for i in range(1, 4)])
            
            # Add the summed value for this subdirectory to the list
            subdirectory_sums.append((dir_name_str, subdirectory_bin_sum))

        # Create a histogram to compare the summed values of bins 1, 2, and 3 for each subdirectory
        canvas = ROOT.TCanvas("c1", "Comparison of Binned Sums", 800, 600)

        # Prepare the comparison histogram
        hist_comparison = ROOT.TH1F("comparison_hist", "Comparison of Binned Sums", len(subdirectory_sums), 0, len(subdirectory_sums))
        hist_comparison_mm = ROOT.TH1F("comparison_hist_mm", "Comparison of Binned Sums", len(subdirectory_sums), 0, len(subdirectory_sums))
        hist_comparison_ee = ROOT.TH1F("comparison_hist_ee", "Comparison of Binned Sums", len(subdirectory_sums), 0, len(subdirectory_sums))
        hist_comparison_em = ROOT.TH1F("comparison_hist_em", "Comparison of Binned Sums", len(subdirectory_sums), 0, len(subdirectory_sums))
        
        # Set the title and labels
        hist_comparison.SetTitle(f"Sum of Bins 1-3 for {file_path}")
        hist_comparison.GetXaxis().SetTitle("Subdirectory")
        hist_comparison.GetYaxis().SetTitle("Sum of Bins 1, 2, and 3")
        
        # Fill the comparison histogram
        for idx, (dir_name, bin_sum) in enumerate(subdirectory_sums):
            hist_comparison.SetBinContent(idx + 1, bin_sum)
            hist_comparison.GetXaxis().SetBinLabel(idx + 1, dir_name)
            

        # Draw the histogram
        hist_comparison.Draw("hist")
        canvas.Update()

        # Optionally, save the canvas as an image
        canvas.SaveAs(f"{file_path.split('/')[-1].replace('.root', '_comparison.png')}")
        
        # Pause to view the canvas if not running in batch mode
        input("Press Enter to continue to the next file...")

        file.Close()  # Close the file

    except Exception as e:
        print(f"Error processing file {file_path}: {e}")
