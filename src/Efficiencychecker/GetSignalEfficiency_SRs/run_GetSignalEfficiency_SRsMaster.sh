echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs HNtypeI_Dilepton  Schannel true"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Schannel true all $2


echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  HNtypeI_Dilepton  Schannel false  "
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false all  $2
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false low $2
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false high $2


echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel true"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel true all $2

echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false all $2
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false low $2
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false high $2

#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Schannel true all
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false all
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false low
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_Dilepton  Schannel false high
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel true
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false all
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false low
#source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_Dilepton  Tchannel false high
