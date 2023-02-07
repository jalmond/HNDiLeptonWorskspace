declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a FLAGS=("")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	python MergeAll.py  -e $i   -a HNL_SignalLeptonOpt --Conv
	python MergeAll.py  -e $i   -a HNL_SignalLeptonOpt --MC                                                                                            	
	python MergeAll.py  -e $i   -a HNL_SignalLeptonOpt --Bkg   
	
    done
    
    
    
    python MergeAll.py   -a HNL_SignalLeptonOpt --EraMerge

done
