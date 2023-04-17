declare  -a era_list=( "2017" )
declare  -a FLAGS=("RunEE__ELID_CF__HighPt__BB__" "RunEE__ELID_CF__HighPt__EC__")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT  --Conv
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT  --CF
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT  --MC                                                                                              
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT  --Bkg   
    done
    
    #python MergeAll.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge
    
done
