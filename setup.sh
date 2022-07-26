#!/bin/bash

if [[ $HOSTNAME == "tamsa1" ]];
then

    export VERSION="Initial"
    export FLATVERSION=${SKFlatV}
    export HNDILEPTONWORKSPACE_DIR=`pwd`
    export PLOT_PATH=$PWD/Plots/
    export OUTFILE_PATH=$HNDILEPTONWORKSPACE_DIR/rootfiles/
    export DATACARD_SHAPE_PATH=$HNDILEPTONWORKSPACE_DIR/Limits/DataCardsShape/
    export INFILE_MERGED_PATH=$HNDILEPTONWORKSPACE_DIR/OutputTool/MergedFiles/ 
    export INFILE_PATH=/data6/Users/jalmond/SKFlatOutput/${SKFlatV}
    
    export SCRIPT_DIR=$HNDILEPTONWORKSPACE_DIR/script/
    export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$HNDILEPTONWORKSPACE_DIR/include/:$HNDILEPTONWORKSPACE_DIR/src/:$HNDILEPTONWORKSPACE_DIR/SignalEfficiency:$HNDILEPTONWORKSPACE_DIR/SignalRegionPlotter:$HNDILEPTONWORKSPACE_DIR/MakeCards:$HNDILEPTONWORKSPACE_DIR/OutputTool
    export LIMIT_PATH="/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"

fi


alias run="bash "$SCRIPT_DIR"/run.sh"
alias skout='cd '$PLOT_PATH

