####### MERGE Scripts
declare  -a era_list=("2016preVFP" "2016postVFP" "2017" "2018")
declare  -a flag_list=("Mu_SelectionOptSR1__" "Mu_SelectionOptSR2__" "Mu_SelectionOptSR3__")

#for i in "${era_list[@]}"
#do
#    #for fl in "${flag_list[@]}"
#    #do
#	python MergeScripts/MergeConfig.py  -e $i -f $fl  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Sig
#	python MergeScripts/MergeConfig.py  -e $i -f $fl  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Conv
#	python MergeScripts/MergeConfig.py  -e $i -f $fl  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Prompt
#	python MergeScripts/MergeConfig.py  -e $i -f $fl  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --FakeMC
#	python MergeScripts/MergeConfig.py  -e $i -f $fl  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Bkg   
#   done
#done
python MergeScripts/MergeConfig.py  -f Mu_SelectionOptSR1__  -a HNL_SignalLeptonOpt --EraMerge
python MergeScripts/MergeConfig.py  -f Mu_SelectionOptSR2__  -a HNL_SignalLeptonOpt --EraMerge
python MergeScripts/MergeConfig.py  -f Mu_SelectionOptSR3__  -a HNL_SignalLeptonOpt --EraMerge
