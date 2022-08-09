#!/bin/bash

export SKFLATVERSION="Run2UltraLegacy_v2"
export SKANVERSION="Run2UltraLegacy_v2_Default"

##   make plotter alias                                                                                                                                                       
export HNDILEPTONWORKSPACE_DIR=$PWD
export PLOTTER_WORKING_DIR=$PWD
export HTML_DIR=$PWD/HTML

export FILE_MERGED_PATH=$HNDILEPTONWORKSPACE_DIR/InputFiles/MergedFiles/$SKANVERSION/

if [[ ! -d $FILE_MERGED_PATH ]]; then mkdir $FILE_MERGED_PATH ; fi
export FILE_PATH=$HNDILEPTONWORKSPACE_DIR/InputFiles/rootfiles/$SKANVERSION/
export OUTFILE_PATH=$HNDILEPTONWORKSPACE_DIR/Output/rootfiles/$SKANVERSION/

export DATACARD_SHAPE_PATH=$HNDILEPTONWORKSPACE_DIR/Limits/DataCardsShape/
export LIMIT_PATH=$HNDILEPTONWORKSPACE_DIR/LimitCode/CMS-StatisticalTools/:$HNDILEPTONWORKSPACE_DIR/Limits/MakeShapeInput

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$HNDILEPTONWORKSPACE_DIR/include/:$HNDILEPTONWORKSPACE_DIR/src/:$HNDILEPTONWORKSPACE_DIR/src/SignalEfficiency:$HNDILEPTONWORKSPACE_DIR/src/SignalRegionPlotter:$HNDILEPTONWORKSPACE_DIR/Limits/MakeCards

### PLOT PATHS
export PLOT_PATH=/Users/john/Dropbox/HNL_13TeV/DiLepton/plots/
export WWW_PLOT_PATH=/tmp/www/html/HNL_13TeV/
alias pl='rsync -auv --delete-excluded '$PLOT_PATH/$SKANVERSION' '$WWW_PLOT_PATH
alias plforce='rsync -auv -I --delete-excluded output/'$SKANVERSION' '$WWW_PLOT_PATH
  
export PYTHONPATH=$PYTHONPATH:$PLOTTER_WORKING_DIR/python/:$PLOTTER_WORKING_DIR/include/
export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/

alias lqout='cd '$PLOT_PATH
alias webout='cd '$WWW_PLOT_PATH
alias makehtml='make_html_master --To=HNL_13TeV'
alias makehtml2='make_html_master --To=HNL_13TeV --From=*/'


CurrentGitBranch=`git branch | grep \* | cut -d ' ' -f2`
source bin/BashColorSets.sh
printf "@@@@ Current HNL_Plotter branch : "${BGreen}$CurrentGitBranch${Color_Off}"\n"

alias run="bash "$SCRIPT_DIR"/run.sh"
alias skout='cd '$PLOT_PATH

python python/UsefulTwiki_sites.py
