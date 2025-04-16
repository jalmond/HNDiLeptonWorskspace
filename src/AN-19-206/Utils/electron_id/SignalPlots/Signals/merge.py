import os

# Define mass values
mass_values = ["M100", "M200", "M500", "M1000", "M2000", "M10000"]

# Define the base path for input files
input_dir = "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/2018/"

# Loop over each mass value and run the hadd command
for mass in mass_values:
    output_file = f"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_{mass}.root"
    input_pattern = f"{input_dir}*{mass}_*"
    
    # Construct the hadd command
    command = f"hadd {output_file} {input_pattern}"
    
    # Print the command (for debugging purposes)
    print(f"Running: {command}")
    
    # Execute the command
    os.system(command)
