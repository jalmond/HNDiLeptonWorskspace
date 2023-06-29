####### MERGE Scripts
declare  -a era_list=("2016preVFP" "2016postVFP" "2017" "2018")

FLAG="HF_Bin3__FullEta__MuID_NP__SIP__"

for i in "${era_list[@]}"
do
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Sig
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Conv
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Prompt
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --FakeMC
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Bkg   
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --MC

done

python MergeScripts/MergeConfig.py  -f $FLAG  -a HNL_SignalLeptonOpt --EraMerge
