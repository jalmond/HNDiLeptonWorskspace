echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Schannel true"
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Schannel true all

echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_JA  Schannel false  "
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_JA  Schannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_JA  Schannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR  HNtypeI_JA  Schannel false high


echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel true"
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel true

echo "##########################################################################################"
echo "source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel false"
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel false all
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel false low
source GetSignalEfficiency_combinedSR/run_GetSignalEfficiency_combinedSR.sh $PWD/GetSignalEfficiency_combinedSR HNtypeI_JA  Tchannel false high
