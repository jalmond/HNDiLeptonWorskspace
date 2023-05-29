declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a FLAGS=("")
ANALYSER=HNL_Validation

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	python MergeScripts/MergeAll.py  -e $i   -a $ANALYSER --MC   -s SkimTree_Dilepton
        python MergeScripts/MergeAll.py  -e $i   -a $ANALYSER --Data  -s SkimTree_Dilepton                                                                                          		
    done
    
    
    #if [ "${#era_list[@]}" -eq 4 ];
    #then
    #python MergeScripts/MergeAll.py   -a $ANALYSER --EraMerge 
    #python MergeScripts/MergeAll.py   -a $ANALYSER --Run2Merge
    #fi

done
