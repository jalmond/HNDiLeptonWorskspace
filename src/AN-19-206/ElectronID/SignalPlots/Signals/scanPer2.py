import ROOT
import os

# Define mass values
mass_values = ["M100", "M200", "M500", "M1000", "M2000", "M10000"]

# Histogram path inside ROOT files
histogram_path = "Signal_NoCut/HNL_ULIDv2/EE/Leptons/HighPtEtaCheck_200"

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

    # Get the bin 1 value
    bin1_value = hist.GetBinContent(1)

    if bin1_value == 0:
        print(f"Mass {mass}: Bin 1 has zero entries, cannot calculate percentages.")
        root_file.Close()
        continue

    # Calculate bin percentages (bins 2, 3, and 4 as a percentage of bin 1)
    bin_percentages = {
        2: (hist.GetBinContent(2) / bin1_value) * 100,
        3: (hist.GetBinContent(3) / bin1_value) * 100,
        4: (hist.GetBinContent(4) / bin1_value) * 100,
    }

    print(f"Mass {mass}:")
    for bin_num, percentage in bin_percentages.items():
        print(f"  Bin {bin_num}: {percentage:.2f}% of Bin 1")

    # Close the ROOT file
    root_file.Close()
