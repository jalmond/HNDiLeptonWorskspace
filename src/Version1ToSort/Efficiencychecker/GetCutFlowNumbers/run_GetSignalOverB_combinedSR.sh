echo "File runs over Signal and combines SR1+SR2 to get high mass SR efficiency"
echo "Deault is Schannel and Dilepton code"
echo "source run_GetSignalEfficiency_combinedSR.sh  analysername  Channel [Schannel,Tchannel] bool(log axis) range" 
cd $2
if [[ $3  == "" ]];
then
    echo "Running Default" 
    root -l -q -b  GetSignalOverB_combinedSR.C
else
    echo "Running non default"
    if [[ $6 == "false" ]];
    then
	root -l -q -b 'GetSignalOverB_combinedSR.C("'$1'","'$8'","'$3'","'$4'","'$5'",false,"'$7'")'
    else
	root -l -q -b 'GetSignalOverB_combinedSR.C("'$1'","'$8'","'$3'","'$4'","'$5'",true,"'$7'")'

    fi
fi

cd -
