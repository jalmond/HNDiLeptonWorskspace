####### MERGE Scripts
declare  -a era_list=("2016preVFP" "2016postVFP" "2017" "2018")

declare  -a flag_list=("RunEE__ELID_CF_Scan__Bin4__")

for j in "${flag_list[@]}"
do
    for i in "${era_list[@]}"
    do
	#python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Sig
	#	python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Conv
	#python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --CF
	#python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Prompt
	python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --FakeMC
	python MergeScripts/MergeConfig.py  -e $i -f $j  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Bkg   
	echo ""
    done
    python MergeScripts/MergeConfig.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge
done
