root -l -q -b 'MakeSKEE.C("2016")'
root -l -q -b 'MakeSKEE.C("2017")'
root -l -q -b 'MakeSKEE.C("2018")'
root -l -q -b 'MakeSKMM.C("2016")'
root -l -q -b 'MakeSKMM.C("2017")'
root -l -q -b 'MakeSKMM.C("2018")'

mv *.root IDUSER/
scp -r IDUSER jalmond@tamsa:~/
