import ROOT
import os

# Define mass values
mass_values = ["M100", "M200", "M500", "M1000", "M2000", "M10000"]

# Histogram path inside ROOT files
histogram_path = "Signal_NoCut/HNL_ULIDv2/EE/Leptons/HighPtEtaCheck"

# Loop over each mass value and process the corresponding ROOT file
for mass in mass_values:
    root_file_path = f"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_{mass}.root"
    
    # Check if file exists
    if not os.path.exists(root_file_path):
        print(f"File not found: {root_file_path}")
        continue

    # Open the ROOT file
    root_file = ROOT.TFile.Open(root_file_path, "READ")
    if not root_file or root_file.IsZombie():
        print(f"Error opening file: {root_file_path}")
        continue

    # Get the histogram
    hist = root_file.Get(histogram_path)
    
    if not hist:
        print(f"Histogram not found in file: {root_file_path}")
        root_file.Close()
        continue
    
    # Print bin contents for bins 2, 3, and 4
    bin_values = {2: hist.GetBinContent(2), 3: hist.GetBinContent(3), 4: hist.GetBinContent(4)}
    
    print(f"Mass {mass}:")
    for bin_num, value in bin_values.items():
        print(f"  Bin {bin_num}: {value}")

    # Close the ROOT file
    root_file.Close()
