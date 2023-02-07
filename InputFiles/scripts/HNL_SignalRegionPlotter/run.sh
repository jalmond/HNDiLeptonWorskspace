declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a era_list=("2017")
declare  -a FLAGS=("")
ANALYSER=HNL_SignalRegionPlotter

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	#python MergeAll.py  -e $i   -a $ANALYSER --Conv -s SkimTree_HNMultiLep
	#python MergeAll.py  -e $i   -a $ANALYSER --Fake -s SkimTree_HNMultiLep                                                                                           	
	#python MergeAll.py  -e $i   -a $ANALYSER --MC   -s SkimTree_HNMultiLep                                                                                          	
	python MergeAll.py  -e $i   -a $ANALYSER --Bkg   -s SkimTree_HNMultiLep

	#python MergeAll.py  -e $i   -a $ANALYSER --Data   -s SkimTree                                                                                          		
    done
    
    
   # python MergeAll.py   -a $ANALYSER --EraMerge 
   # python MergeAll.py   -a $ANALYSER --Run2Merge

done
