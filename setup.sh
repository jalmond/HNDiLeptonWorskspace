#!/bin/bash
if [[ $HOSTNAME == "tamsa1" ]];
then

    #### use cvmfs for root ####
    export CMS_PATH=/cvmfs/cms.cern.ch
    source $CMS_PATH/cmsset_default.sh
    export SCRAM_ARCH=slc7_amd64_gcc700
    export cmsswrel='cmssw-patch/CMSSW_10_4_0_patch1'
    cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
    echo "@@@@ SCRAM_ARCH = "$SCRAM_ARCH
    echo "@@@@ cmsswrel = "$cmsswrel
    echo "@@@@ scram..."
    eval `scramv1 runtime -sh`
    cd -
    source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh
    
    export VERSION="Initial"
    export FLATVERSION="Run2Legacy_v4"
    export PLOTTER_WORKING_DIR=`pwd`
    export PLOT_PATH=$PWD/Plots/
    export OUTFILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
    export INFILE_MERGED_PATH=$PLOTTER_WORKING_DIR/OutputTool/MergedFiles/ 
    export INFILE_PATH=/data6/Users/jalmond/SKFlatOutput/Run2Legacy_v4/HNtypeI_JA/
    export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/
    export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/:$PLOTTER_WORKING_DIR/SignalEfficiency:$PLOTTER_WORKING_DIR/SignalRegionPlotter:$PLOTTER_WORKING_DIR/MakeCards:$PLOTTER_WORKING_DIR/OutputTool
    export LIMIT_PATH="/data6/Users/jalmond/Limits/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/data/2016_HNDiLepton/batch/"

fi
if [[ $HOST == "JohnMB2018s-MacBook-Pro.local" ]];then

    export VERSION="Initial"
    export FLATVERSION="Run2Legacy_v4"
    export PLOTTER_WORKING_DIR=`pwd`
    export PLOT_PATH=$PWD/Plots/
    export OUTFILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
    export INFILE_MERGED_PATH=$HOME/HNDiLeptonWorskspace/OutputTool/MergedFiles/
    export INFILE_PATH=$PLOTTER_WORKING_DIR/Files/HNtypeI_JA/
    export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/
    export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/:$PLOTTER_WORKING_DIR/SignalEfficiency:$PLOTTER_WORKING_DIR/SignalRegionPlotter:$PLOTTER_WORKING_DIR/MakeCards:$PLOTTER_WORKING_DIR/OutputTool
    export LIMIT_PATH=$PLOTTER_WORKING_DIR/LimitCode/CMS-StatisticalTools/:$PLOTTER_WORKING_DIR/Limits/MakeShapeInput

fi    
alias run="bash "$SCRIPT_DIR"/run.sh"
alias skout='cd '$PLOT_PATH

