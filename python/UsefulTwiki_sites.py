site = [  ["ElectronID_94","https://indico.cern.ch/event/732971/contributions/3022843/attachments/1658685/2656462/eleIdTuning.pdf"],
          ["Electron_hlt","https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgHLTPathDetails"],
          ["Higgs_combined","https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part2/settinguptheanalysis/"],
          ["git_js_2016_plotter","https://github.com/jedori0228/HN_dilepton_plotter/tree/v8-0-7.37_Approved"],
          ["MUON18","https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2018"],
          ["GD","https://docs.google.com/spreadsheets/d/1d5ZOqy1uv3FyIcNQ6a87LxRCuomur4RFxIKHFAMS1sI/edit#gid=851619247"],
          ["",""],
          ["EXO-20-006","http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/EXO-20-006/"],
          ["EXOPUB","https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsEXO"],
          ["TDRSTyle","https://ghm.web.cern.ch/ghm/plots/"],
          ["MET","https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections"],
          ["Jet","https://twiki.cern.ch/twiki/bin/view/CMS/JetMET"],
          ["Publications","https://twiki.cern.ch/twiki/bin/view/CMS/Internal/PubGuidelines"],
          ["Publications","https://twiki.cern.ch/twiki/bin/view/CMS/Internal/PaperSubmissionPrep"],
          ["Publications","https://twiki.cern.ch/twiki/bin/view/CMS/Internal/Publications"],

      ]

for s in site:
    if s[0] == "":
        continue
    print ("Nickname : "  + s[0]  +  " --- " + s[1] )
