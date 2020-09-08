#!/bin/bash
if [[ $HOSTNAME == "tamsa1" ]];
then
    export VERSION="Initial"
    export FLATVERSION="Run2Legacy_v4"
    export PLOTTER_WORKING_DIR=`pwd`
    export PLOT_PATH=$PWD/Plots/
    export OUTFILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
    export INFILE_MERGED_PATH=/data6/User/$USER/HNDiLep/MergedFiles/
    export INFILE_PATH=$SKFlatOutputDir/
    export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/
    export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/:$PLOTTER_WORKING_DIR/SignalEfficiency:$PLOTTER_WORKING_DIR/SignalRegionPlotter:$PLOTTER_WORKING_DIR/MakeCards:$PLOTTER_WORKING_DIR/OutputTool
    export LIMIT_PATH=$PLOTTER_WORKING_DIR/LimitCode/CMS-StatisticalTools/
    
fi
if [[ $HOST == "JohnMB2018s-MacBook-Pro.local" ]];then

    export VERSION="Initial"
    export FLATVERSION="Run2Legacy_v4"
    export PLOTTER_WORKING_DIR=`pwd`
    export PLOT_PATH=$PWD/Plots/
    export OUTFILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
    export INFILE_MERGED_PATH=$HOME/HNDiLeptonWorskspace/OutputTool/MergedFiles/
    export INFILE_PATH=$SKFlatOutputDir
    export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/
    export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/:$PLOTTER_WORKING_DIR/SignalEfficiency:$PLOTTER_WORKING_DIR/SignalRegionPlotter:$PLOTTER_WORKING_DIR/MakeCards:$PLOTTER_WORKING_DIR/OutputTool
    export LIMIT_PATH=$PLOTTER_WORKING_DIR/LimitCode/CMS-StatisticalTools/

fi    
alias run="bash "$SCRIPT_DIR"/run.sh"
alias skout='cd '$PLOT_PATH

