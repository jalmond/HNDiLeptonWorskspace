####### MERGE Scripts
declare  -a era_list=("2017")
FLAG="MuID_NP__FullEta__"

for i in "${era_list[@]}"
do
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Sig
    ##python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Conv
    #python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Prompt
    #python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --FakeMC
    python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --Bkg   
    #python MergeScripts/MergeConfig.py  -e $i -f $FLAG  -a HNL_SignalLeptonOpt -s SkimTree_HNMultiLepBDT --MC

done
#python MergeConfig.py  -f $j  -a HNL_SignalLeptonOpt --EraMerge
