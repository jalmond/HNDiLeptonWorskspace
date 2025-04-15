import ROOT
import numpy as np
import os

def process_bin_label(bin_label):

    if not "Jet" in bin_label:
        if not "Mu" in bin_label:
            if not "El" in bin_label:
                return bin_label
            
    # Split the label by underscores
    parts = bin_label.split('_')

    # Prepare a list for the new label parts
    new_label_parts = ["-","-","-"]

    # Iterate through the parts and determine what they correspond to
    for part in parts:
        if "Jet" in part:
            # If it's a Jet label, take the postfix and add to the list
            new_label_parts[0] = (part.replace("Jet", ""))
        elif "Mu" in part:
            # If it's a Muon label, take the postfix and add to the list
            new_label_parts[1] = (part.replace("Mu", ""))
        elif "El" in part:
            # If it's an Electron label, take the postfix and add to the list
            new_label_parts[2] = (part.replace("El", ""))
            
    snew_label_parts = f"[{new_label_parts[0]},{new_label_parts[1]},{new_label_parts[2]}]"
    if "AK8" in bin_label:
        snew_label_parts="AK8 "+snew_label_parts
    # Return the processed label as a string in the format you require
    return snew_label_parts

def add_files_from_directory(directory, files_list):
    # Check if the given directory exists
    if os.path.isdir(directory):
        # Loop through all files in the directory
        for file_name in os.listdir(directory):
            # Full path to the file
            file_path = os.path.join(directory, file_name)
            # Check if the file is a ROOT file (ends with .root)
            if os.path.isfile(file_path) and file_path.endswith('.root'):
                files_list.append(file_path)
    else:
        print(f"Directory {directory} does not exist!")




# List of input ROOT file paths
files = [
    "Input/SS_Data.root",
    "Input/SS_HighJet_Data.root",
    # Add the rest of your file paths here
]

final_files = []
for item in files:
    if os.path.isdir(item):
        # If it's a directory, add all ROOT files in that directory to the list
        add_files_from_directory(item, final_files)
    else:
        # If it's a file, just add it directly to the list
        final_files.append(item)



# Path template for histogram of interest
histogram_template = "ChannelCutFlow/{}/LL/ChannelDependant_CR2"
default_histogram_path = "ChannelCutFlow/HNL_ULIDv2Default/LL/ChannelDependant_CR2"


# Initialize ROOT for histogram plotting
ROOT.gStyle.SetOptStat(0)

# Loop over each file
for file_path in final_files:

    try:
        # Open the ROOT file
        file = ROOT.TFile.Open(file_path)

        # Get the default histogram
        default_histogram = file.Get(default_histogram_path)
        
        if not default_histogram:
            print(f"Default histogram {default_histogram_path} not found in {file_path}")
            continue

        # Sum of bins 1, 2, and 3 for the default histogram
        default_bin_sums = [default_histogram.GetBinContent(i) for i in range(1, 4)]
        default_bin_sums_list = [default_histogram.GetBinContent(1), default_histogram.GetBinContent(2), default_histogram.GetBinContent(3), default_histogram.GetBinContent(4)]

        # Initialize lists to store summed values for each subdirectory's bins
        subdirectory_sums = {
            "bin1": [],
            "bin2": [],
            "bin3": [],
            "total": []  # For the total sum of bins 1, 2, and 3
        }

        # Get the list of directories in the ROOT file under 'ChannelCutFlow'
        channel_cutflow_dir = file.Get("ChannelCutFlow")
        
        if not channel_cutflow_dir:
            print(f"ChannelCutFlow directory not found in {file_path}")
            continue
        
        # Loop through each directory under 'ChannelCutFlow'
        for dir_name in channel_cutflow_dir.GetListOfKeys():
            dir_name_str = dir_name.GetName()

            if not "HNL_ULIDv2" in dir_name_str:
                continue
                
            # Form the histogram path for this directory
            histogram_path = histogram_template.format(dir_name_str)
            
            # Get the histogram for this path
            histogram = file.Get(histogram_path)
            
            if not histogram:
                print(f"Histogram {histogram_path} not found in {file_path}")
                continue
            
            # Sum the values of bins 1, 2, and 3 for the current histogram
            bin1_sum = 0 if default_histogram.GetBinContent(1) == 0 else histogram.GetBinContent(1) 
            bin2_sum = 0 if default_histogram.GetBinContent(2) == 0 else histogram.GetBinContent(2) 
            bin3_sum = 0 if default_histogram.GetBinContent(3) == 0 else histogram.GetBinContent(3) 


            # Add the summed value for each bin and total sum to the lists
            subdirectory_sums["bin1"].append((dir_name_str, bin1_sum))
            subdirectory_sums["bin2"].append((dir_name_str, bin2_sum))
            subdirectory_sums["bin3"].append((dir_name_str, bin3_sum))
            subdirectory_sums["total"].append((dir_name_str, (bin1_sum + bin2_sum + bin3_sum)/3.))

        # Create a canvas to compare histograms
        canvas = ROOT.TCanvas("c1", "Comparison of Binned Sums", 800, 600)
        canvas.SetBottomMargin(0.2)
        canvas.Update()

        # Prepare the comparison histograms for bin1, bin2, bin3, and total sum
        hist_bin1 = ROOT.TH1F("bin1_hist", "Bin Entry / 'Default' ", len(subdirectory_sums["bin1"]), 0, len(subdirectory_sums["bin1"]))
        hist_bin2 = ROOT.TH1F("bin2_hist", "Sum of Bin 2", len(subdirectory_sums["bin2"]), 0, len(subdirectory_sums["bin2"]))
        hist_bin3 = ROOT.TH1F("bin3_hist", "Sum of Bin 3", len(subdirectory_sums["bin3"]), 0, len(subdirectory_sums["bin3"]))
        hist_total = ROOT.TH1F("total_hist", "Total Sum of Bins 1-3", len(subdirectory_sums["total"]), 0, len(subdirectory_sums["total"]))

        # Set the titles and labels
        hist_bin1.SetTitle(f"Sum of Bin 1 for {file_path}")
        hist_bin1.GetXaxis().SetTitle("Tau WP [Jet,Mu,El]")
        hist_bin1.GetYaxis().SetTitle("Bin Entry / 'Default'")

        hist_bin2.SetTitle(f"Sum of Bin 2 for {file_path}")
        hist_bin2.GetXaxis().SetTitle("Subdirectory")
        hist_bin2.GetYaxis().SetTitle("Sum of Bin 2")

        hist_bin3.SetTitle(f"Sum of Bin 3 for {file_path}")
        hist_bin3.GetXaxis().SetTitle("Subdirectory")
        hist_bin3.GetYaxis().SetTitle("Sum of Bin 3")

        hist_total.SetTitle(f"Total Sum of Bins 1-3 for {file_path}")
        hist_total.GetXaxis().SetTitle("Subdirectory")
        hist_total.GetYaxis().SetTitle("Total Sum of Bins 1-3")

        # Fill the histograms with the summed values
        for idx, (dir_name, bin1_sum) in enumerate(subdirectory_sums["bin1"]):
            if not "HNL_ULIDv2" in dir_name:
                continue
            
            hist_bin1.SetBinContent(idx + 1, bin1_sum)
            
            bin_name_str = dir_name
            bin_name_str = bin_name_str.replace("HNL_ULIDv2", "")

            new_bin_label = process_bin_label(bin_name_str)
            print(f"new_bin_label = {new_bin_label} : value = {bin1_sum}")
            hist_bin1.GetXaxis().SetBinLabel(idx + 1, new_bin_label)

        for idx, (dir_name, bin2_sum) in enumerate(subdirectory_sums["bin2"]):
            hist_bin2.SetBinContent(idx + 1, bin2_sum)
            hist_bin2.GetXaxis().SetBinLabel(idx + 1, dir_name)


        for idx, (dir_name, bin3_sum) in enumerate(subdirectory_sums["bin3"]):
            hist_bin3.SetBinContent(idx + 1, bin3_sum)
            hist_bin3.GetXaxis().SetBinLabel(idx + 1, dir_name)

        for idx, (dir_name, total_sum) in enumerate(subdirectory_sums["total"]):
            hist_total.SetBinContent(idx + 1, total_sum)
            hist_total.GetXaxis().SetBinLabel(idx + 1, dir_name)

        # Draw all histograms on the same canvas
        hist_bin1.SetLineColor(ROOT.kRed)
        hist_bin2.SetLineColor(ROOT.kGreen)
        hist_bin3.SetLineColor(ROOT.kBlue)
        hist_total.SetLineColor(ROOT.kBlack)

        hist_bin1.LabelsOption("v", "X");
        
        hist_bin1.GetYaxis().SetRangeUser(0,hist_bin1.GetMaximum()*1.1);
        hist_bin1.GetXaxis().SetTitleOffset(2.5)

        hist_bin1.Draw("hist")
        hist_bin2.Draw("hist same")
        hist_bin3.Draw("hist same")
        hist_total.Draw("hist same")

        # Update and show the canvas
        canvas.Update()

        legend = ROOT.TLegend(0.6, 0.7, 0.9, 0.9)  # (x1, y1, x2, y2) position of the legend
        legend.AddEntry(hist_bin1, "#mu#mu", "l")  # "l" for line
        legend.AddEntry(hist_bin2, "ee", "l")
        legend.AddEntry(hist_bin3, "e#mu", "l")
        legend.AddEntry(hist_total, "Average", "l")
        
        # Draw the legend
        legend.Draw()

        
        # Optionally, save the canvas as an image
        print(f"Saving  TauPlots/{file_path.split('/')[-1].replace('.root', '_CR2_comparison.png')}")
        canvas.SaveAs(f"TauPlots/{file_path.split('/')[-1].replace('.root', '_CR2_comparison.png')}")
        
        # Pause to view the canvas if not running in batch mode
        #input("Press Enter to continue to the next file...")

        file.Close()  # Close the file

    except Exception as e:
        print(f"Error processing file {file_path}: {e}")
