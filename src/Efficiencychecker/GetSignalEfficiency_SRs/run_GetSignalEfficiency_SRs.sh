echo "File runs over Signal and combines SR1+SR2 to get high mass SR efficiency"
echo "Deault is Schannel and Dilepton code"
echo "source run_GetSignalEfficiency_SRs.sh  analysername  Channel [Schannel,Tchannel] bool(log axis) range" 
cd $1
if [[ $3 == "" ]];
then
    echo "Running Default" 
    root -l -q -b  GetSignalEfficiency_SRs.C
else
    echo "Running non default"
    if [[ $5 == "false" ]];
    then
	root -l -q -b 'GetSignalEfficiency_SRs.C("'$7'","'$2'","'$3'","'$4'",false,"'$6'")'
    else
	root -l -q -b 'GetSignalEfficiency_SRs.C("'$7'","'$2'","'$3'","'$4'",true,"'$6'")'

    fi
fi

cd -
