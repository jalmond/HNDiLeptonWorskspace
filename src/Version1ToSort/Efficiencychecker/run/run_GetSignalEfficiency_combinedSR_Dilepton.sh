echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel true"
dir=GetSignalEfficiency_combinedSR
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel true all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel true all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel true all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel true all
echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false  "
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false high
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_Dilepton  Schannel false high

source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false low
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false high
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false low
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Schannel false high


echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel true"
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel true
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel true
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel true
echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false"

source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false high
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR_ppmm.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false high
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false low
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_EE.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false high
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false all
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false low
source GetSignalEfficiency_combinedSR/GetSignalEfficiency_combinedSR_MM.C  $PWD/GetSignalEfficiency_combinedSR HNtypeI_Dilepton  Tchannel false high
