import subprocess
import os

# Define the combinations of options
years = ['2016preVFP', '2016postVFP', '2017', '2018', 'Run2']
channels = ['MuMu', 'EE', 'EMu', 'LL']
lists = ['List1', 'List2', 'List3', 'List4']
regions = ['PassCR1_MET', 'PassCR1_BJet', 'PassCR2', 'PassCR1_BJet', 'PassCR2_MET','PassCR3_BJet_HighJet','PassCR3_MET_HighJet']

regions = ['PassCR1_MET']


# Output directory path
output_dir = "CutFlow"

# Ensure the output directory exists
os.makedirs(output_dir, exist_ok=True)

# Iterate over all combinations of years, channels, lists, and regions
for year in years:
    for channel in channels:
        for list_option in lists:
            for region in regions:
                # Create an output file for each combination
                output_file = os.path.join(output_dir, f"output_{year}_{channel}_{list_option}_{region}.txt")
                print(f"Running {output_file}...")

                with open(output_file, 'w') as f:
                    # Build the command string
                    command = [
                        'python3', 'PrintBackgrounds_Run2.py',
                        '-f', 'SSMultiLep__',
                        '-e', year,
                        '-r', region,
                        '-i', 'HNL_ULIDv2',
                        '-c', channel,
                        '-d', 'Mar25',
                        '-a', 'HNL_ControlRegion_Plotter',
                        '-p', 'HNL_ControlRegion_LLCRPlots_LL__',
                        '-l', list_option
                    ]

                    # Run the command and capture the output
                    result = subprocess.run(command, capture_output=True, text=True)

                    # Write the output to the file
                    f.write(f"Running command for year={year}, channel={channel}, list={list_option}, region={region}\n")
                    f.write(result.stdout)
                    f.write("\n" + "="*50 + "\n")
                    f.write(result.stderr)

print(f"All outputs have been saved to {output_dir}.")

