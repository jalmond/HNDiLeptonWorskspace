declare  -a era_list=("2016preVFP" "2016postVFP" "2017" "2018")

declare  -a skim_list=("SkimTree_DileptonBDT" "SkimTree_HNMultiLepBDT" "SkimTree_HNFakeBDT")

for i in "${era_list[@]}"
do
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" $i

    for j in "${skim_list[@]}"
    do
	
	echo  ${j} "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" $i
	#python CheckSkim.py -s ${j} -i /data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/SumEvents/${i}/ -e ${i}
	python CheckSkim.py -s ${j} -i /data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/SumEvents/${i}/DATA/ -e ${i}

	
    done
done
