indiv_bins=
combbins=
combyears=
indiv_bins_dilep=
combbins_dilep=
combyears_dilep=
cd IndividualSRs/
python readLimitsShape_individualbins_rootfile.py  -c configfiles/HNtypeI_JA/config_HNtypeI_JA_individualbins.txt -i $indiv_bins
python readLimitsShape_individualbins_rootfile.py  -c configfiles/HNtypeI_Dilepton/config_HNtypeI_Dilepton_individualbins.txt -i $indiv_bins_dilep
cd -
cd CombinedSRs
python readLimitsShape_combinedsrs.py -c configfiles/HNtypeI_JA/config_HNtypeI_JA_combinedsrs.txt -i  $combbins
python readLimitsShape_combinedsrs.py -c configfiles/HNtypeI_Dilepton/config_HNtypeI_Dilepton_combinedsrs.txt -i $combbins_dilep
cd -
cd CombinedYears
python readLimitsShape_combyears.py  -c configfiles/HNtypeI_JA/config_HNtypeI_JA_combinedyears.txt -i $combyears
python readLimitsShape_combyears.py  -c configfiles/HNtypeI_Dilepton/config_HNtypeI_Dilepton_combinedyears.txt -i $combyears_dilep
cd -
