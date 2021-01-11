import os

list_of_types=["-1.", "0.", "1.", "2.", "3.", "4.", "5.", "6.", "-2.", "-3.", "-4.", "-5.", "-6."]
list_of_ch= ["muon", "electron"]
list_of_years= ["2016"]#, "2017", "2018"]
list_of_samples= ["DYJets", "TTLJ_powheg", "WJets_MG", "WZTo3LNu_powheg", "ZGToLLG_01J", "ZZTo4L_powheg", "WGToLNuG_01J", "ZGTo2LG", "WGToLNuG"]
list_of_samples= ["DYJets","ZGTo2LG","WJets_MG"]
for itype in  list_of_types:
    for ich in  list_of_ch:
	for iyear in  list_of_years:
	    for isamples in  list_of_samples:
                _type = itype+"000000"
                _dxy = "\"dxy\""
                _iso = "\"relsio\""
                _ip = "\"ip3d\""
                os.system("root -l -q -b 'FakeCut_dxy.C(\""+isamples+"\",\""+ich+"\","+_dxy+",\""+_type+"\",\""+ iyear+"\")'")
                os.system("root -l -q -b 'FakeCut_reliso.C(\""+isamples+"\",\""+ich+"\","+_iso+",\""+_type+"\",\""+ iyear+"\")'")
                os.system("root -l -q -b 'FakeCut_ip3d.C(\""+isamples+"\",\""+ich+"\","+_ip+",\""+_type+"\",\""+ iyear+"\")'")
