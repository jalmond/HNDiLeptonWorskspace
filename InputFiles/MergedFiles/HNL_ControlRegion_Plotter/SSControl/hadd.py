import os
import argparse
import subprocess

import logging


# A helper function to add clear breaks in logging
def log_section_start(section_name):
    logging.info("-" * 50)  # Print 50 '=' characters as a separator
    logging.info(f"STARTING SUBSECTION: {section_name}")
    logging.info("-" * 50)


def remove_file(filename):
    """Remove file if it exists."""
    if os.path.exists(filename):
        logging.info(f"REMOVING {filename}")

        try:
            os.remove(filename)
        except OSError as e:
            logging.error(f"Error removing file {filename}: {e}")


def get_list_from_file(filepath):
    """Read file and return a list of non-empty first column entries."""

    if not os.path.exists(filepath):
        raise FileNotFoundError(f"Required file {filepath} missing")

    with open(filepath, "r") as f:
        return [line.split()[0] for line in f if line.strip()]

def check_missing_files(v_in_files, job_name, dataset_names, era, missing_files):
    """Check for missing samples."""
    sample_dir = "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_UL_LONG/SKFlatAnalyzer/runJobs/SampleLists/"
    data_files = []

    if "CONV" in job_name:
        mc_names = get_list_from_file(f"{sample_dir}/Bkg/Conv/Conv.txt")
        mc_names.extend(get_list_from_file(f"{sample_dir}/Bkg/Conv/ConvWG.txt"))
                
    elif "CFMC" in job_name:
        mc_names = ["DYJets_MG", "TTLL_powheg"]
    else:
        mc_names = []

    if "DATA" in job_name:
        for period in DataPeriods:
            for name in dataset_names:
                data_files.append(f"{name}_{period}")
    else:
        data_files.extend(mc_names)

    logging.info((job_name + " "))
    logging.info(f"List: {data_files}")
    logging.info(f"List2: {v_in_files}")

    for file in data_files:
        if file not in v_in_files:
            missing_files.append(f"{job_name} : MISSING SAMPLE ---> {era} : {file}")
    for file in v_in_files:
        if file not in data_files:
            missing_files.append(f"{job_name} : MISSING SAMPLE [REV] ---> {era} : {file}")

def hadd_run2(path_a, path_b):
    """Merge files using hadd for Run2."""
    logging.info(f"--------> Run 2 hadd {path_a} {path_b}")
    remove_file(path_a)
    # Run the hadd command with logging
    command = f"hadd {path_a} {path_b}"
    
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        logging.info(f"Command executed successfully: {command}")
    except subprocess.CalledProcessError as e:
        logging.error(f"Error executing command: {e.stderr.decode()}")
        logging.error(f"Command output: {e.stdout.decode()}")
        logging.error(f"Command error output: {e.stderr.decode()}")



def hadd_merge_from_list(path_a, path_b, prefix_file, textfile, use_data):

    # Merge files for prompt sample lists.
    logging.info(f"--------> hadd [list] {path_a} {path_b}/...")
    
    # Remove the existing file at path_a
    remove_file(path_a)
    
    # Join the paths using os.path.join for portability
    file_path_b = os.path.join(path_b, prefix_file)
    
    # Get the list from the provided text file
    InputList = get_list_from_file(textfile)
    
    # Check each file in the InputList
    for x in InputList:
        # Construct the file path
        full_file_path = file_path_b + f"{x}.root"
        
        # Check if the file exists
        if not os.path.exists(full_file_path):
            logging.warning(f"{full_file_path} is Missing")  # Use logging.warning for missing files
            exit(1)  # Exit with a non-zero status to indicate failure
            
    # Construct the hadd command by joining file paths
    haddcommand = " ".join([os.path.join(path_b, prefix_file + x + ".root") for x in InputList])

    command=["hadd", path_a] + haddcommand.split()
    logging.info(f"Command: {command}")
    
    # Execute the hadd command using subprocess for better control and error handling
    subprocess.run(["hadd", path_a] + haddcommand.split(), check=True)

    return InputList

def hadd_merge(path_a, path_b, prefix_file, use_data):
    """Merge ROOT files using hadd."""
    logging.info(f"--------> hadd {path_a} {path_b}")

    # Remove the existing file at path_a                                                                                                                                                                                                     
    remove_file(path_a)

    # Construct the base file path
    file_path_b = os.path.join(path_b, "DATA") if use_data else path_b

    # List all files in the directory and filter by prefix_file
    file_list = [os.path.join(file_path_b, f) for f in os.listdir(file_path_b) if f.startswith(prefix_file) and f.endswith(".root")]

    # Check if we found any matching files
    if not file_list:
        logging.error(f"No files matching the prefix {prefix_file} found in {file_path_b}")
        return

    # Construct the hadd command (list of arguments)
    hadd_command = ["hadd", path_a] + file_list

    logging.info(f"hadd_command={hadd_command}")

    
    # Run the hadd command with subprocess for better error handling and logging
    try:
        subprocess.run(hadd_command, check=True)
        logging.info(f"Successfully merged files into {path_a}")
    except subprocess.CalledProcessError as e:
        logging.error(f"Error during hadd operation: {e}")
        raise  # Optionally re-raise the error to stop further execution if needed

    

# Argument Parsing

parser = argparse.ArgumentParser(description="Run hadd.py to merge files and check for missing datasets.")
parser.add_argument('--CF', action='store_true')
parser.add_argument('--Data', action='store_true')
parser.add_argument('--Conv', action='store_true')
parser.add_argument('--Fake', action='store_true')
parser.add_argument('--Prompt', action='store_true')
parser.add_argument('-flag', dest='Flag', default="NULL")
parser.add_argument('-DateDir', dest='DateDir', default="NULL")
parser.add_argument('-era', dest='Era', default="NULL")
args = parser.parse_args()

DateDir = args.DateDir
runCF = args.CF
runData = args.Data
runConv = args.Conv
runFake = args.Fake
runPrompt = args.Prompt

runCF = runData = runConv = runFake = runPrompt = True


if "LLL" in args.Flag:
    runCF=False


                                                                                                                                                                                                                                           
logging.basicConfig(
    level=logging.INFO,
    format='HaddJob:  %(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler(f'process_hadd_{args.Era}.log'),  # Log to a file                                                                                                                                                                             
        logging.StreamHandler()  # Log to console (screen)                                                                                                                                                                                                                                                                                                                                                                                                                                
    ]
)

    
# Process Inputs
Era = args.Era
Flag = f"{args.Flag}__" if args.Flag != "NULL" else ""

Analyzer = "HNL_ControlRegion_Plotter"
FilePrefix = f"{Analyzer}_SkimTree_HNMultiLepBDT"
FilePrefixDilep= f"{Analyzer}_SkimTree_DileptonBDT"

InputPath = f"/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/{Analyzer}/{Era}"
OutputDir = f"/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/{Analyzer}/SSControl/{DateDir}/{Era}/{Flag}"

if not os.path.exists(OutputDir):
    os.makedirs(OutputDir)

logging.info(f"Running hadd_merge for {Era} Analyzer = {Analyzer}")

# Data Periods
DataPeriods = {
    "2016preVFP": ["B_ver2", "C", "D", "E", "F"],
    "2016postVFP": ["F", "G", "H"],
    "2017": ["B", "C", "D", "E", "F"],
    "2018": ["A", "B", "C", "D"],
}.get(Era, [])

DATASETNAMES = ["DoubleEG", "DoubleMuon", "MuonEG"]
if Era == "2018":
    DATASETNAMES = ["EGamma_GT36", "DoubleMuon_GT36", "MuonEG_GT36"]

DATASETNAMESCF = ["DoubleEG"]
if Era == "2018":
    DATASETNAMESCF = ["EGamma_GT36"]


ConvBkgs = ["WG","ZG","Other_Conv"]
    
PromptBkgs = ["WZ","WZAlt","qqZZ","ggZZ","WW","Top","TopAlt","Other"]

if Era == "Run2":

    InputPath=f"{DateDir}/201*/"    +Flag +"/"
    
    InFiles= [f"{FilePrefix}_CF.root",
              f"{FilePrefix}_data.root",
              f"{FilePrefix}_Prompt_v1.root",
              f"{FilePrefix}_Prompt_v2.root",
              f"{FilePrefix}_Prompt_v3.root",
              f"{FilePrefix}_Prompt_v4.root",
              f"{FilePrefix}_Conv.root",
              f"{FilePrefix}_NonPrompt.root"]

    for PromptBkg in PromptBkgs:
        InFiles.append( f"{FilePrefix}_{PromptBkg}.root",)

    for ConvBkgs in ConvBkgs:
        InFiles.append( f"{FilePrefix}_{ConvBkg}.root",)
        
    for x in InFiles:
        hadd_run2(OutputDir+"/"+x,        InputPath+ x)

    exit()

    
log_section_start("Running Hadd Functions:")

# Merging Process
if runCF:
    
    log_section_start("Running CF")
    
    hadd_merge(f"{OutputDir}/{FilePrefix}_CF.root", f"{InputPath}/{Flag}RunCF__"    , FilePrefixDilep+"_", True)

    
if runFake:

    log_section_start("Running Fake")

    hadd_merge(f"{OutputDir}/{FilePrefix}_NonPrompt.root", f"{InputPath}/{Flag}RunFake__", FilePrefix+"_", True)


if runPrompt:
    vInFiles = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_Prompt_v1.root", f"{InputPath}/{Flag}RunPrompt__", FilePrefix+"_", "BkgLists/List1.txt", False)
    for x in vInFiles:
        logging.info (f" Merging Prompt v1 --> {x}")

    vInFiles = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_Prompt_v2.root", f"{InputPath}/{Flag}RunPrompt__", FilePrefix+"_", "BkgLists/List2.txt", False)
    for x in vInFiles:
        logging.info (f" Merging Prompt v2 --> {x}")

    vInFiles = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_Prompt_v3.root", f"{InputPath}/{Flag}RunPrompt__", FilePrefix+"_", "BkgLists/List3.txt", False)
    for x in vInFiles:
        logging.info (f" Merging Prompt v3 --> {x}")

    vInFiles = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_Prompt_v4.root", f"{InputPath}/{Flag}RunPrompt__", FilePrefix+"_", "BkgLists/List4.txt", False)
    for x in vInFiles:
        logging.info (f" Merging Prompt v4 --> {x}")

    for PromptBkg in PromptBkgs:
        vInFiles = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_{PromptBkg}.root", f"{InputPath}/{Flag}RunPrompt__", FilePrefix+"_", f"BkgLists/{PromptBkg}.txt", False)
        for x in vInFiles:
            logging.info (f" Merging Prompt bkgs --> {x}")


if runConv:

    logging.info((" "*50))
    logging.info(("-----------RunConv-----------"))
    logging.info(("_"*50))


    hadd_merge(f"{OutputDir}/{FilePrefix}_Conv.root",f"{InputPath}/{Flag}RunConv__"  , "HNL_ControlRegion_Plotter_SkimTree_",False)

    
    vInFilesConv = hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_WG.root", f"{InputPath}/{Flag}RunConv__", "HNL_ControlRegion_Plotter_SkimTree_DileptonBDT_", f"BkgLists/WG.txt", False)
    vInFilesConv.append(hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_ZG.root", f"{InputPath}/{Flag}RunConv__", FilePrefix+"_", f"BkgLists/ZG.txt", False))
    vInFilesConv.append(hadd_merge_from_list(f"{OutputDir}/{FilePrefix}_Other_Conv.root", f"{InputPath}/{Flag}RunConv__", FilePrefix+"_", f"BkgLists/Other_Conv.txt", False))
    for x in vInFilesConv:
        logging.info (f" Conv bkgs --> {x}")

if runData:

    logging.info((" "*50))
    logging.info(("=============DATA============"))
    logging.info(("_"*50))

    
    hadd_merge(f"{OutputDir}/{FilePrefix}_data.root",f"{InputPath}/{Flag}"  , FilePrefix+"_",True)
