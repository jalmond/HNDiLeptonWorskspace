#!/bin/bash

string_date=Version1

function scp_tamsa() {    scp -r jalmond@tamsa:/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v2/${1} ${2} }
function rsync_tamsa() {

    echo 'rsync -av -e "ssh -p 1240 " jalmond@147.47.242.42:/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v2/'${1} ${FILE_PATH}
    rsync -av -e "ssh -p 1240 " jalmond@147.47.242.42:/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v2/${1} ${FILE_PATH} 
}
function clone_copy_dir(){

    local_dir=$FILE_PATH/$1

    echo "Copying "$local_dir":"

    if [[ -d $local_dir ]] then
       rm -r ${local_dir}
    fi

    scp_tamsa ${1} ${local_dir}
       
    #cp -r ${local_dir} History/${local_dir}-${string_date}
}

if [[ "$1"  == "RS_Fake"  ]]; then  rsync_tamsa FakeRateHN ; 
elif [[ "$1"  == "Fake"  ]]; then   clone_copy_dir FakeRateHN ;   
elif [[ "$1"  == "IDSF"  ]]; then   clone_copy_dir LepScaleFactorCalc ; 
elif [[ "$1"  == "CF"    ]]; then   clone_copy_dir HNtypeI_CF ;  
else echo "Need input RS_Fake,Fake,IDSF,CF"
fi
