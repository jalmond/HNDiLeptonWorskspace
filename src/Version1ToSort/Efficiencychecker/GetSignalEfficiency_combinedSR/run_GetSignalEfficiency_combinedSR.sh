echo "File runs over Signal and combines SR1+SR2 to get high mass SR efficiency"
echo "Deault is Schannel and Dilepton code"
echo "source run_GetSignalEfficiency_combinedSR.sh  analysername  Channel [Schannel,Tchannel] bool(log axis) range" 
cd $1
if [[ $2 == "" ]];
then
    echo "Running Default" 
    root -l -q -b  GetSignalEfficiency_combinedSR.C
else
    echo "Running non default"
    if [[ $4 == "false" ]];
    then
	root -l -q -b 'GetSignalEfficiency_combinedSR.C("'$2'","'$3'",false,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_EEv1.C("'$2'","'$3'",false,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_EEv2.C("'$2'","'$3'",false,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_MM.C("'$2'","'$3'",false,"'$5'")'
    else
	root -l -q -b 'GetSignalEfficiency_combinedSR.C("'$2'","'$3'",true,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_EEv1.C("'$2'","'$3'",true,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_EEv2.C("'$2'","'$3'",true,"'$5'")'
	root -l -q -b 'GetSignalEfficiency_combinedSR_MM.C("'$2'","'$3'",true,"'$5'")'

    fi
fi

cd -
