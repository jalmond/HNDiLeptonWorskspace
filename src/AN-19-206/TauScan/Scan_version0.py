import ROOT

# List of input ROOT file paths
files = [
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1000_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M100_private.root",
    "Input/TauScan__RunSignals__/HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1100_private.root",
    # Add the rest of your file paths here
]

# Path to the histogram of interest
histogram_path = "ChannelCutFlow/HNL_ULIDv2JetVL__/LL/ChannelDependant_Presel"

# Initialize ROOT for histogram plotting
ROOT.gStyle.SetOptStat(0)

# Loop over each file
for file_path in files:
    try:
        # Open the ROOT file
        file = ROOT.TFile.Open(file_path)
        
        # Get the histogram from the ROOT file
        histogram = file.Get(histogram_path)
        
        if not histogram:
            print(f"Histogram {histogram_path} not found in {file_path}")
            continue
        
        # Print out the bin entries
        print(f"Bin entries for {file_path}:")
        for i in range(1, histogram.GetNbinsX() + 1):
            print(f"Bin {i}: {histogram.GetBinContent(i)} entries")
        
        # Draw the histogram
        canvas = ROOT.TCanvas("c1", "Histogram", 800, 600)
        histogram.SetLineColor(ROOT.kBlack)  # Set the color of the histogram line
        histogram.SetTitle(f"Histogram: {histogram_path} from {file_path}")
        histogram.GetXaxis().SetTitle('Bin')
        histogram.GetYaxis().SetTitle('Entries')
        
        histogram.Draw()
        canvas.Update()
        
        # Optionally, save the canvas as an image
        # canvas.SaveAs(f"{file_path.split('/')[-1].replace('.root', '.png')}")
        
        # Pause to view the canvas if not running in batch mode
        input("Press Enter to continue to the next file...")

        file.Close()  # Close the file

    except Exception as e:
        print(f"Error processing file {file_path}: {e}")
