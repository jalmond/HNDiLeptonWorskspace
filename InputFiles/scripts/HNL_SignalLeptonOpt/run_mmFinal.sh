declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")
declare  -a FLAGS=("Mu_Final__")

for j in "${FLAGS[@]}"
do
    for i in "${era_list[@]}"
    do
	#python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --LMC                                                                                            	
	#python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Conv
	python MergeAll.py  -e $i -f $j  -a HNL_SignalLeptonOpt --Bkg   
    done
    
    python MergeAll.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge

done
