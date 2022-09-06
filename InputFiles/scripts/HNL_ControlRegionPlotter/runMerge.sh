python MergeFilesForPlotting.py --Data -a HNL_SignalRegionPlotter -s SkimTree_HNMultiLep # --FullRun2
python MergeFilesForPlotting.py -a HNL_SignalRegionPlotter -s SkimTree_SS2lOR3l  --MC
python MergeCF.py  
python MergeSignal.py
#python MergeSignal16.py
python MergeSignalFull.py


