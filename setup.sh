#!/bin/bash

export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc12
export cmsswrel='cmssw/CMSSW_14_1_0_pre4'

cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
echo "@@@@ SCRAM_ARCH = "$SCRAM_ARCH
echo "@@@@ cmsswrel = "$cmsswrel
echo "@@@@ scram..."
eval `scramv1 runtime -sh`
cd -
source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh


export SKFlatV="Run2UltraLegacy_v3"
export FLATVERSION=${SKFlatV}
export HNDILEPTONWORKSPACE_DIR=$PWD
export PLOT_PATH=$PWD/Output/Plots/
export OUTFILE_PATH=$HNDILEPTONWORKSPACE_DIR/Output/rootfiles/
export DATACARD_SHAPE_PATH=$HNDILEPTONWORKSPACE_DIR/Limits/DataCardsShape/
export INFILE_MERGED_PATH=$HNDILEPTONWORKSPACE_DIR/Output/OutputTool/MergedFiles/
export SCRIPT_DIR=$HNDILEPTONWORKSPACE_DIR/script/
export HTML_DIR=$PWD/script/HTML

## PYTHON ## (no more python2...)
alias python=python3

export FILE_MERGED_PATH=$HNDILEPTONWORKSPACE_DIR/InputFiles/MergedFiles/
export FILE_PATH=$HNDILEPTONWORKSPACE_DIR/InputFiles/rootfiles/
export OUTFILE_PATH=$HNDILEPTONWORKSPACE_DIR/Output/rootfiles/

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$HNDILEPTONWORKSPACE_DIR/include/:$HNDILEPTONWORKSPACE_DIR/src/plugin/:$HNDILEPTONWORKSPACE_DIR/SignalEfficiency:$HNDILEPTONWORKSPACE_DIR/SignalRegionPlotter:$HNDILEPTONWORKSPACE_DIR/Limit/MakeCards:$HNDILEPTONWORKSPACE_DIR/Output/OutputTool

export PYTHONPATH=$PYTHONPATH:$HNDILEPTONWORKSPACE_DIR/python/:$HNDILEPTONWORKSPACE_DIR/include/:$HNDILEPTONWORKSPACE_DIR/PyScripts
export SCRIPT_DIR=$HNDILEPTONWORKSPACE_DIR/script/

export INFILE_PATH=$SKFlatOutputDir/
export LIMIT_PATH=$HNDILEPTONWORKSPACE_DIR/LimitCode/CMS-StatisticalTools/:$HNDILEPTONWORKSPACE_DIR/Limits/MakeShapeInput:"/data9/Users/jalmond/Limits/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/batch/"

CurrentGitBranch=`git branch | grep \* | cut -d ' ' -f2`
source bin/BashColorSets.sh

printf "@@@@ Current HNL_Plotter branch : "${BGreen}$CurrentGitBranch${Color_Off}"\n"

alias run="bash "$SCRIPT_DIR"/run.sh"
alias skout='cd '$PLOT_PATH

python3 python/UsefulTwiki_sites.py
