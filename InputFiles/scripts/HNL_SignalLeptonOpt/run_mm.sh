#declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a era_list=("2016postVFP" "2016preVFP"  "2018")
declare  -a FLAGS=("MuID_NP__BB__" "MuID_NP__EC__")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	#python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Conv
	echo " "
	echo " "
	echo " "
	echo " "
	#python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --MC                                                                                            	
	echo " "
	echo " "
	echo " "
	echo " "
	#python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Bkg   
	echo " "
	echo " "
	echo " "

    done
    
    
    python MergeAll.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge

done
