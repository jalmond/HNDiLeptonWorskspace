declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a FLAGS=("MuID_NP2__FullPt__BB__" "MuID_NP2__FullPt__EC__")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Conv
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --MC                                                                                            	
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Bkg   
    done
    
    python MergeAll.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge

done
