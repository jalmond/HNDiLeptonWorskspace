import os,sys
import argparse
import subprocess
import shutil
import glob

import logging

def delete_log_files(directory):
    """Delete all .log files in the specified directory."""
    
    # List all .log files in the directory using glob
    log_files = glob.glob(os.path.join(directory, "*.log"))
    
    # Check if any .log files were found
    if log_files:
        for log_file in log_files:
            try:
                os.remove(log_file)  # Delete the log file
                print(f"Deleted {log_file}")
            except Exception as e:
                print(f"Error deleting {log_file}: {e}")
    else:
        print("No .log files found.")

        

def log_section_start(section_name):
    logging.info("=" * 50)  # Print 50 '=' characters as a separator
    logging.info(f"STARTING SECTION: {section_name}")
    logging.info("=" * 50)

    

# Set up logging to both file and console
logging.basicConfig(
    level=logging.INFO,
    format='hadd_ControlRegion : %(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('process_main.log'),  # Log to a file
        logging.StreamHandler()  # Log to console (screen)
    ]
)

# Log the start of the first section
log_section_start("Data Preprocessing")


delete_log_files("./")


# Argument parsing
parser = argparse.ArgumentParser(description="Run hadd.py to merge files and check for missing datasets.")
parser.add_argument('--test', action='store_true', help="Run in test mode (does not perform the actual operations)")
parser.add_argument("DateDir", type=str, help="Directory where results will be stored")

# Define the processing eras and flags
Eras = ["2016preVFP", "2016postVFP", "2017", "2018"]
Flags = ["MultiLepton","LLL","SSMultiLep"]

# Add optional flags
for flag in Flags:
    parser.add_argument(f"--{flag}", action="store_true", help=f"Enable {flag} flag")

# Add era as an argument, allowing either a specific era or defaulting to all
parser.add_argument("--Era", choices=Eras, nargs="?", default=None, help="Specify the processing era. If not set, all eras will be used.")

args = parser.parse_args()

# Assign input argument to DateDir
DateDir = args.DateDir

# Determine selected eras
selected_eras = [args.Era] if args.Era else Eras
logging.info(f"Selected Eras: {selected_eras}")
logging.info(f"DateDir: {DateDir}")

# Capture which flags are enabled
enabled_flags = {flag: getattr(args, flag) for flag in Flags}

# Check if enabled_flags is empty, and exit if true
if not enabled_flags:
    logging.error("No flags are enabled. Exiting...")
    sys.exit(1)  # Exit the program with a non-zero status to indicate an error

# Check if any enabled flag is set to True
if not any(enabled_flags.values()):
    logging.error("No flags are enabled (all flags are False). Exiting...")
    sys.exit(1)  # Exit the program with a non-zero status to indicate an error
    
# Print enabled flags (for debugging)
logging.info(f"Enabled Flags: {enabled_flags}")

# Log the start of the first section
log_section_start("Sample check list")



# Run checks for each combination of Era and Flag
for Era in selected_eras:
    for flag, enabled in list(enabled_flags.items()):
        if enabled:
            logging.info(f"Running {Era} check {flag}...")
            logging.info(f"python3 check_files.py -era {Era} -DateDir {DateDir} -flag {flag} ")
            subprocess.run(f"python3 check_files.py -era {Era} -DateDir {DateDir} -flag {flag} ", shell=True)
            
            # Define the file
            filename = f"process_missing_files_{Era}.log"
            
            # Run the cat command with subprocess
            try:
                result = subprocess.run(["cat", filename], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                logging.info(f"Content of {filename}:\n{result.stdout}")
            except subprocess.CalledProcessError as e:
                logging.error(f"Error executing 'cat {filename}': {e.stderr}")
                
# Search for missing samples in the generated logs
subprocess.run(f"grep MISSING process_missing_files_{Era}.log ", shell=True)
subprocess.run(f"grep MISSING process_missing_files_{Era}.log > grep_list.txt", shell=True)

# Check for missing samples and handle accordingly
with open("grep_list.txt", "r") as readfile:
    missing_lines = [line for line in readfile if "MISSING" in line]

if missing_lines:
    logging.warning("Some samples are missing:")
    subprocess.run("cat grep_list.txt", shell=True)
    os.remove("grep_list.txt")
    exit()
else:
    logging.info("No missing samples.")
    os.remove("grep_list.txt")


# Clean up check files
if os.path.exists(f"process_missing_files_{Era}.log"):
    os.remove(f"process_missing_files_{Era}.log")


if args.test:
    logging.info("Running in test mode, will not hadd")
    exit()
    
if not os.path.exists(DateDir):
    logging.info(f"Making directory {DateDir}")
    os.makedirs(DateDir)

if args.test:
    logging.info("Test flag detected. Exiting the script.")
    sys.exit(0)

# Log the start of the first section
log_section_start("Hadd Preprocessing")


    

# Run the hadd process for all Era and Flag combinations
for flag, enabled in list(enabled_flags.items()):
    if enabled:
        for Era in selected_eras:
            logging.info(f"python3 hadd.py -era {Era} -flag {flag} -DateDir {DateDir}  ")
            subprocess.run(f"python3 hadd.py -era {Era} -flag {flag} -DateDir {DateDir} ", shell=True)

    # If all four eras exist, also process "Run2"
    if len(selected_eras) == 4:
        subprocess.run(f"python3 hadd.py -era Run2 -flag {flag} -DateDir {DateDir}", shell=True)
