echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs HNtypeI_JA  Schannel true"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Schannel true all
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Schannel true all

echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  HNtypeI_JA  Schannel false  "
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false all
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false low
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false high
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false all
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false low
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs  $1 HNtypeI_JA  Schannel false high


echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel true"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel true
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel true

echo "##########################################################################################"
echo "source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false"
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false all
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false low
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false high
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false all
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false low
source GetSignalEfficiency_SRs/run_GetSignalEfficiency_SRs_ppmm.sh $PWD/GetSignalEfficiency_SRs $1 HNtypeI_JA  Tchannel false high
