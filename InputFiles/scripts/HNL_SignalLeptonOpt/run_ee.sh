declare  -a era_list=( "2017" )
declare  -a FLAGS=("RunEE__ELID_CF__HighPt__FullEta__")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Conv
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --CF
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --MC                                                                                              
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Bkg   
    done
    
    python MergeAll.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge

done
