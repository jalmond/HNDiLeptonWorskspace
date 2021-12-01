python MergeFilesForPlotting.py -a PrescaledTriggerSF -s SkimTree_HNFake --SYNC --NoMerge


declare  -a era_list=("2016postVFP" "2016preVFP" "2017" "2018")

for i in "${era_list[@]}"
do
    mkdir -p $FILE_MERGED_PATH/PrescaledTriggerSF/${i}/
    rm  $FILE_MERGED_PATH/PrescaledTriggerSF/${i}/PrescaledTriggerSF_SkimTree_HNFake_Data.root
    hadd  $FILE_MERGED_PATH/PrescaledTriggerSF/${i}/PrescaledTriggerSF_SkimTree_HNFake_Data.root $FILE_PATH/PrescaledTriggerSF/${i}/DATA/*
    mv $FILE_PATH/PrescaledTriggerSF/${i}/PrescaledTriggerSF_SkimTree_HNFake_DYJets.root $FILE_MERGED_PATH/PrescaledTriggerSF/${i}/
done
