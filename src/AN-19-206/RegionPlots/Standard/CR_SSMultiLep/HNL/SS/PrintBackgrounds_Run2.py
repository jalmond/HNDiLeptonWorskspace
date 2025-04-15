#!/usr/bin/env python3

import os
import sys
import ctypes
import math
import argparse

from os.path import isfile, isdir, join

import ROOT

# Set working directory and insert custom python path
WORKING_DIR = os.environ['HNDILEPTONWORKSPACE_DIR']
sys.path.insert(1, os.path.join(WORKING_DIR, 'python'))

ROOT.gROOT.SetBatch(ROOT.kTRUE)


def GetListFromFile(listpath):
    if not os.path.exists(listpath):
        print(f"File {listpath} MISSING")
        exit()

    with open(listpath, "r") as read_list:
        List = [line.split()[0] for line in read_list if len(line.split()) > 0]
    
    return List


def GetHistError(HistName, InDir, Uncert):
    if not os.path.exists(InDir):
        return 0

    # Open ROOT file
    with ROOT.TFile(InDir) as f:
        hist = f.Get(HistName)

        if not hist:
            print(f"Hist does not exist: {InDir} {HistName}")
            return 0

        # Calculate integral and error
        data_integral = hist.Integral()
        data_error = ctypes.c_double(0.)
        hist.IntegralAndError(0, hist.GetNbinsX(), data_error, "")

        err = data_error.value

        # Apply uncertainty if applicable
        if Uncert > 0:
            err = math.sqrt(err**2 + data_integral**2 * Uncert**2)

    return err


def MakeDir(path_dir):
    if not os.path.exists(path_dir):
        os.makedirs(path_dir, exist_ok=True)


def GetHistIntegral(HistName, InDir):
    try:
        # Open ROOT file with context manager (automatically closed)
        with ROOT.TFile(InDir) as f:
            hist = f.Get(HistName)
            if hist:
                return hist.Integral()
            else:
                print(f"Histogram {HistName} not found in {InDir}")
                return 0
    except Exception as e:
        print(f"Error opening file {InDir}: {e}")
        return 0


def parse_args():
  
    
    parser = argparse.ArgumentParser(description='CR plot commands')
    parser.add_argument('-e', dest='Era', type=str, default='NULL')
    parser.add_argument('-f', dest='Flag', type=str, default='NULL')
    parser.add_argument('-a', dest='Analyser', type=str, default='NULL')
    parser.add_argument('-hist', dest='HistName', type=str, default='NULL')
    parser.add_argument('-input', dest='Input', type=str, default='NULL')
    parser.add_argument('-r', dest='Region', type=str, default='NULL')
    parser.add_argument('-i', dest='ID', type=str, default='NULL')
    parser.add_argument('-c', dest='Channel', type=str, default='NULL')
    parser.add_argument('-p', dest='PlotterTag', type=str, default='NULL')
    parser.add_argument('-l', dest='List', type=str, default='NULL')
    parser.add_argument('-d', dest='DateDir', type=str, default='NULL')
    parser.add_argument('--debug',action='store_true')
    return parser.parse_args()



def get_hist_integrals(hist_name, paths):
    """Helper function to get the histogram integrals for given paths."""
    return {path_name: GetHistIntegral(hist_name, path) for path_name, path in paths.items()}


def calculate_total_error(errors):
    """Calculate total error by summing quadratically all individual errors."""
    return math.sqrt(sum(error**2 for error in errors))


def create_directory_path(*path_parts):
    """Creates a full directory path and makes all directories in the path if they don't exist."""
    full_path = os.path.join(*path_parts)
    MakeDir(full_path)
    return full_path


def write_formatted_line_direct(file,formatted_line_):
    file.write(formatted_line_+"\n")


def write_formatted_line(file, label, value, error):
    """Helper function to format and write a line to the file."""

    formatted_line = f"{label: <20} = {value:.2f} +/- {error:.2f}\n"
    file.write(formatted_line)
    



def main():
    # Parse command-line arguments
    args = parse_args()

    # Validate required arguments
    if args.Era == 'NULL' or args.Flag == 'NULL':
        print("Error: Missing required arguments.")
        return

    # File paths based on the input arguments
    base_path = os.path.join("/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_ControlRegion_Plotter/SSControl", args.DateDir, args.Era, args.Flag)

    # Dictionary for file paths based on list options
    paths = {
        "Data": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_data.root"),
        "NonPrompt": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_NonPrompt.root"),
        "CF": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_CF.root"),
        "Conv": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Conv.root"),
        "WZ": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WZ.root"),
        "WW": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WW.root"),
        "qqZZ": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_qqZZ.root"),
        "ggZZ": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ggZZ.root"),
        "Top": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Top.root"),
        "Other": os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Other.root")
    }

    # Corresponding uncertainties for each dataset
    uncertainties = {
        "Data": 0,
        "NonPrompt": 0.3,
        "CF": 0.2,
        "Conv": 0.25,
        "WZ": 0.12,
        "qqZZ": 0.15,
        "ggZZ": 0.15,
        "WW": 0.20,
        "Top": 0.20,
        "Other": 0.5
    }

    
    # Modify paths based on List options
    if args.List == "List1" or args.List == "List2":
        paths["WZ"] = os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_WZAlt.root")
    if args.List == "List2" or args.List == "List4":
        paths["Top"] = os.path.join(base_path, "HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_TopAlt.root")
       
    # Calculate integrals for all paths
    hist_name = f"/{args.Region}/{args.ID}/{args.Channel}/NObj/N_Mu"
    integrals = get_hist_integrals(hist_name, paths)

    # Extract the individual integrals from the dictionary
    DataInt = integrals["Data"]
    NonPromptInt = integrals["NonPrompt"]
    CFInt = integrals["CF"]
    ConvInt = integrals["Conv"]
    WZInt = integrals["WZ"]
    WWInt = integrals["WW"]
    qqZZInt = integrals["qqZZ"]
    ggZZInt = integrals["ggZZ"]
    TopInt = integrals["Top"]
    OtherInt = integrals["Other"]

    # Background and prompt total integrals
    BkgInt = NonPromptInt + CFInt + WZInt + qqZZInt + ggZZInt + WWInt + TopInt + OtherInt + ConvInt
    TotalPrompt = WZInt + qqZZInt + ggZZInt + WWInt + TopInt + OtherInt

    # Print or use the results as needed
    print(f"Total Background Integral: {BkgInt}")
    print(f"Total Prompt Integral: {TotalPrompt}")


    # Get histograms' errors for each dataset
    errors = {dataset: GetHistError(hist_name, path, uncertainties[dataset]) for dataset, path in paths.items()}

    # Calculate total errors
    total_err_prompt = calculate_total_error([errors["WZ"], errors["qqZZ"], errors["ggZZ"], errors["WW"], errors["Top"], errors["Other"]])
    bkg_err = calculate_total_error([errors["NonPrompt"], errors["Conv"], errors["CF"], total_err_prompt])

    # Calculate significance
    significance = (DataInt - BkgInt) / math.sqrt(errors["Data"]**2 + bkg_err**2)

    # Print or use the results as needed
    print(f"Significance: {significance}")
    

    # Start with the base path from the environment variable
    base_path = os.getenv("PLOT_PATH") + args.Analyser

    # Construct and create directories step by step
    outfile_path = create_directory_path(base_path, args.DateDir, args.PlotterTag, args.Era, args.Region, args.ID, args.Channel)

    # Append the final file name to the path
    outfile_path = os.path.join(outfile_path, f"BkgYields_{args.List}.txt")

    # Print the final output path for debugging
    print(("@@@" * 50))
    print(f"outfile_path = {outfile_path}")

    # Open the file for writing
    with open(outfile_path, "w") as f:
        write_formatted_line_direct(f, f"{args.ID} {args.Region} ")
        write_formatted_line_direct(f,"="*50)
        write_formatted_line(f, "NBkg[Prompt]", TotalPrompt, total_err_prompt)
        write_formatted_line(f, "NBkg[CF]", CFInt, uncertainties["CF"])
        write_formatted_line(f, "NBkg[Conv]", ConvInt, uncertainties["Conv"])
        write_formatted_line(f, "NBkg[Fake]", NonPromptInt, uncertainties["NonPrompt"])
        write_formatted_line_direct(f,"_"*50)
        write_formatted_line(f, "NBkg[Total]", BkgInt, bkg_err)
        write_formatted_line_direct(f,"_"*50)
        write_formatted_line(f, "NData", DataInt, errors["Data"])
        write_formatted_line_direct(f,"_"*50)
        write_formatted_line(f, "Significance", significance, 0)  # Significance may not have an error
        write_formatted_line_direct(f,"_"*50)

        # Separator for visual clarity
        f.write("--" * 50 + "\n")
        f.write("--" * 50 + "\n")
        

        # Writing for each individual background type
        for label, int_value, err_value in [
            ("WZ", WZInt, errors["WZ"]),
            ("qqZZ", qqZZInt, errors["qqZZ"]),
            ("ggZZ", ggZZInt, errors["ggZZ"]),
            ("WW", WWInt, errors["WW"]),
            ("Top", TopInt, errors["Top"]),
            ("Other", OtherInt, errors["Other"])
        ]:
            write_formatted_line(f, label, int_value, err_value)

        # Write the final separator and background details
        f.write("--" * 50 + "\n")
        write_formatted_line(f, "NBkg[Prompt]", TotalPrompt, total_err_prompt)
        f.write("--" * 50 + "\n")
        write_formatted_line(f, "NBkg[Conv]", ConvInt, uncertainties["Conv"])
        f.write("--" * 50 + "\n")

    # Reopen the file and print its contents to screen
    with open(outfile_path, "r") as f:
        content = f.read()
        print(content)  # Print the content to screen



if __name__ == "__main__":
    main()
        
