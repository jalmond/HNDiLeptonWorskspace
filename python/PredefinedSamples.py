import os,ROOT
from Plotter import SampleGroup

#VV_incl", "DY","Xgamma", "VVV", "top", "WW_double","ttbar"


#SSWW

SampleGroup_SSWW_2016 = SampleGroup(
  Name='SSWW',
  Type='Bkgd',
  Samples=['SSWW'],
  Year = 2016,
  Color=74,
  Style=1,
    TLatexAlias='W^{p}W^{p}',
  LatexAlias='W^{p}W^{p}'

)

SampleGroup_SSWW_2017 = SampleGroup(
  Name='SSWW',
  Type='Bkgd',
    Samples=['SSWW'],
  Year = 2017,
  Color=74,
  Style=1,
    TLatexAlias='W^{p}W^{p}',
  LatexAlias='W^{p}W^{p}'

)

SampleGroup_SSWW_2018 = SampleGroup(
  Name='SSWW',
  Type='Bkgd',
    Samples=['SSWW'],
  Year = 2018,
  Color=74,
  Style=1,
    TLatexAlias='W^{p}W^{p}',
  LatexAlias='W^{p}W^{p}'

)


## TT+X

SampleGroup_Top_2016 = SampleGroup(
  Name='Top',
  Type='Bkgd',
    Samples=['TTLL_powheg','TTLJ_powheg'],
  Year = 2016,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}[powheg]',
  LatexAlias='$\\mathrm{t}\\bar{\\mathrm{t}}$[powheg]'
)

SampleGroup_Top_2017 = SampleGroup(
  Name='Top',
  Type='Bkgd',
    Samples=['TTLL_powheg','TTLJ_powheg'],
  Year = 2017,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}[powheg]',
  LatexAlias='$\\mathrm{t}\\bar{\\mathrm{t}}$[powheg]'


)

SampleGroup_Top_2018 = SampleGroup(
  Name='Top',
  Type='Bkgd',
    Samples=['TTLL_powheg','TTLJ_powheg'],
  Year = 2018,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}[powheg]',
  LatexAlias='$\\mathrm{t}\\bar{\\mathrm{t}}$[powheg]'



)




#VVV

SampleGroup_VVV_2016 = SampleGroup(
  Name='VVV',
  Type='Bkgd',
  Samples=['WWW', 'WWZ', 'WZZ', 'ZZZ'],
  Year = 2016,
  Color=ROOT.kSpring+10,
  Style=1,
  TLatexAlias='VVV',
  LatexAlias='VVV'
)

SampleGroup_VVV_2017 = SampleGroup(
  Name='VVV',
  Type='Bkgd',
  Samples=['WWW', 'WWZ', 'WZZ', 'ZZZ'],
  Year = 2017,
  Color=ROOT.kSpring+10,
  Style=1,
  TLatexAlias='VVV',
  LatexAlias='VVV'
)

SampleGroup_VVV_2018 = SampleGroup(
  Name='VVV',
  Type='Bkgd',
  Samples=['WWW', 'WWZ', 'WZZ', 'ZZZ'],
  Year = 2018,
  Color=ROOT.kSpring+10,
  Style=1,
  TLatexAlias='VVV',
  LatexAlias='VVV'
)



#Xgamma
SampleGroup_XG_2016 = SampleGroup(
  Name='XG',
  Type='Bkgd',
    Samples=['ZGTo2LG_01J', 'WGToLNuG'],
  Year = 2016,
  Color=ROOT.kSpring-7,
  Style=1,
  TLatexAlias='X+#gamma',
  LatexAlias='X+$\\gamma$'
)

SampleGroup_XG_2017 = SampleGroup(
  Name='XG',
  Type='Bkgd',
    Samples=['ZGTo2LG_01J', 'WGToLNuG'],
  Year = 2017,
  Color=ROOT.kSpring-7,
  Style=1,
  TLatexAlias='X+#gamma',
  LatexAlias='X+$\\gamma$'

)

SampleGroup_XG_2018 = SampleGroup(
  Name='XG',
  Type='Bkgd',
    Samples=['ZGTo2LG_01J', 'WGToLNuG'],
  Year = 2018,
  Color=ROOT.kSpring-7,
  Style=1,
  TLatexAlias='X+#gamma',
  LatexAlias='X+$\\gamma$'

)

## VV
SampleGroup_VV_incl_2016 = SampleGroup(
  Name='VV',
  Type='Bkgd',
  Samples=['WZ_pythia', 'ZZ_pythia', 'WW_pythia'],
  Year = 2016,
  Color=ROOT.kSpring-1,
  Style=1,
    TLatexAlias='VV[Pythia]',
  LatexAlias='VV[Pythia]'
)

SampleGroup_VV_incl_2017 = SampleGroup(
  Name='VV',
  Type='Bkgd',
  Samples=['WZ_pythia', 'ZZ_pythia', 'WW_pythia'],
  Year = 2017,
  Color=ROOT.kSpring-1,
  Style=1,
    TLatexAlias='VV[Pythia]',
  LatexAlias='VV[Pythia]'
)
SampleGroup_VV_incl_2018 = SampleGroup(
  Name='VV',
  Type='Bkgd',
  Samples=['WZ_pythia', 'ZZ_pythia', 'WW_pythia'],
  Year = 2018,
  Color=ROOT.kSpring-1,
  Style=1,
    TLatexAlias='VV[Pythia]',
  LatexAlias='VV[Pythia]'
)


## DY
SampleGroup_DY_2016 = SampleGroup(
  Name='DY',
  Type='Bkgd',
  Samples=['DYJets'],
  Year = 2016,
  Color=ROOT.kYellow,
  Style=1,
    TLatexAlias='DY#rightarrow l l ',
  LatexAlias='DY$\\rightarrow \\ell\\ell$'
)
SampleGroup_DY_2017 = SampleGroup(
  Name='DY',
  Type='Bkgd',
  Samples=['DYJets'],
  Year = 2017,
  Color=ROOT.kYellow,
  Style=1,
    TLatexAlias='DY#rightarrow l l ',
  LatexAlias='DY$\\rightarrow \\ell\\ell$'


)
SampleGroup_DY_2018 = SampleGroup(
  Name='DY',
  Type='Bkgd',
  Samples=['DYJets'],
  Year = 2018,
  Color=ROOT.kYellow,
  Style=1,
    TLatexAlias='DY#rightarrow l l ',
  LatexAlias='DY$\\rightarrow \\ell\\ell$'


)

## ttbar
SampleGroup_ttbar_2016 = SampleGroup(
  Name='ttbar',
  Type='Bkgd',
  Samples=['TTLX_powheg'],
  Year = 2016,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}#rightarrow',
  LatexAlias='ttbar#rightarrow'
)
SampleGroup_ttbar_2017 = SampleGroup(
  Name='ttbar',
  Type='Bkgd',
  Samples=['TTLX_powheg'],
  Year = 2017,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}#rightarrow',
  LatexAlias='ttbar#rightarrow'
)
SampleGroup_ttbar_2018 = SampleGroup(
  Name='ttbar',
  Type='Bkgd',
  Samples=['TTLX_powheg'],
  Year = 2018,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}#rightarrow',
  LatexAlias='ttbar#rightarrow'
)

SampleGroup_TT_TW_2016 = SampleGroup(
  Name='TT_TW',
  Type='Bkgd',
  Samples=['TT_TW'],
  Year = 2016,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}+tW',
  LatexAlias='TT\_TW'
)
SampleGroup_TT_TW_2017 = SampleGroup(
  Name='TT_TW',
  Type='Bkgd',
  Samples=['TT_TW'],
  Year = 2017,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}+tW',
  LatexAlias='TT_TW'
)
SampleGroup_TT_TW_2018 = SampleGroup(
  Name='TT_TW',
  Type='Bkgd',
  Samples=['TT_TW'],
  Year = 2018,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}+tW',
  LatexAlias='TT\_TW'
)

## others
SampleGroup_Others_2016 = SampleGroup(
  Name='Others',
  Type='Bkgd',
  Samples=['Others'],
  Year = 2016,
  Color=870,
  Style=1,
  TLatexAlias='Other backgrounds',
  LatexAlias='Others'
)
SampleGroup_Others_2017 = SampleGroup(
  Name='Others',
  Type='Bkgd',
  Samples=['Others'],
  Year = 2017,
  Color=870,
  Style=1,
  TLatexAlias='Other backgrounds',
  LatexAlias='Others'
)
SampleGroup_Others_2018 = SampleGroup(
  Name='Others',
  Type='Bkgd',
  Samples=['Others'],
  Year = 2018,
  Color=870,
  Style=1,
  TLatexAlias='Other backgrounds',
  LatexAlias='Others'
)

## WJets_MG_HT
SampleGroup_WJets_2016 = SampleGroup(
  Name='WJets_MG',
  Type='Bkgd',
  Samples=['WJets_MG'],
  Year = 2016,
  Color=ROOT.kGreen,
  Style=1,
    TLatexAlias='W#rightarrow l  #nu',
  LatexAlias='W$\\rightarrow \\ell \\nu$'
)
SampleGroup_WJets_2017 = SampleGroup(
  Name='WJets_MG',
  Type='Bkgd',
  Samples=['WJets_MG'],
  Year = 2017,
  Color=ROOT.kGreen,
  Style=1,
    TLatexAlias='W#rightarrow l  #nu',
  LatexAlias='W$\\rightarrow \\ell \\nu$'

)
SampleGroup_WJets_2018 = SampleGroup(
  Name='WJets_MG',
  Type='Bkgd',
  Samples=['WJets_MG'],
  Year = 2018,
  Color=ROOT.kGreen,
  Style=1,
    TLatexAlias='W#rightarrow l  #nu',
  LatexAlias='W$\\rightarrow \\ell \\nu$'

)

## NonPrompt
SampleGroup_NonPrompt_Muon_2016 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Muon'],
  Year = 2016,
  Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)
SampleGroup_NonPrompt_Muon_2017 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Muon'],
  Year = 2017,
  Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)
SampleGroup_NonPrompt_Muon_2018 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Muon'],
  Year = 2018,
  Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)

SampleGroup_NonPrompt_2016 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Lepton'],
  Year = 2016,
    Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)
SampleGroup_NonPrompt_2017 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Lepton'],
  Year = 2017,
    Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)
SampleGroup_NonPrompt_2018 = SampleGroup(
  Name='NonPrompt',
  Type='Bkgd',
  Samples=['NonPrompt_Lepton'],
  Year = 2018,
    Color=870,
  Style=1,
  TLatexAlias='Nonprompt',
  LatexAlias='NonPrompt'
)


## Error from shape
SampleGroup_total_background_2016 = SampleGroup(
  Name='total_background',
  Type='Bkgd',
  Samples=['total_background'],
  Year = 2016,
  Color=ROOT.kGreen+1,
  Style=1,
  TLatexAlias='W+Jets',
  LatexAlias='total_background'
)
SampleGroup_total_background_2017 = SampleGroup(
  Name='total_background',
  Type='Bkgd',
  Samples=['total_background'],
  Year = 2017,
  Color=ROOT.kGreen+1,
  Style=1,
  TLatexAlias='W+Jets',
  LatexAlias='total_background'
)
SampleGroup_total_background_2018 = SampleGroup(
  Name='total_background',
  Type='Bkgd',
  Samples=['total_background'],
  Year = 2018,
  Color=ROOT.kGreen+1,
  Style=1,
  TLatexAlias='W+Jets',
  LatexAlias='total_background'
)
SampleGroup_total_background_YearCombined = SampleGroup(
  Name='total_background',
  Type='Bkgd',
  Samples=['total_background'],
  Year = 'YearCombined',
  Color=ROOT.kGreen+1,
  Style=1,
  TLatexAlias='W+Jets',
  LatexAlias='total_background'
)

## TTLL
SampleGroup_TTLL_2016 = SampleGroup(
  Name='TTLL',
  Type='Bkgd',
  Samples=['TTLL_powheg'],
  Year = 2016,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}',
  LatexAlias='tt'
)
SampleGroup_TTLL_2017 = SampleGroup(
  Name='TTLL',
  Type='Bkgd',
  Samples=['TTLL_powheg'],
  Year = 2017,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}',
  LatexAlias='tt'
)
SampleGroup_TTLL_2018 = SampleGroup(
  Name='TTLL',
  Type='Bkgd',
  Samples=['TTLL_powheg'],
  Year = 2018,
  Color=ROOT.kRed,
  Style=1,
  TLatexAlias='t#bar{t}',
  LatexAlias='tt'
)


## TW
SampleGroup_TW_2016 = SampleGroup(
  Name='TW',
  Type='Bkgd',
  Samples=['SingleTop_tW_antitop_NoFullyHad','SingleTop_tW_top_NoFullyHad'],
  Year = 2016,
  Color=ROOT.kGray,
  Style=1,
  TLatexAlias='tW',
  LatexAlias='tW'
)
SampleGroup_TW_2017 = SampleGroup(
  Name='TW',
  Type='Bkgd',
  Samples=['SingleTop_tW_antitop_NoFullyHad','SingleTop_tW_top_NoFullyHad'],
  Year = 2017,
  Color=ROOT.kGray,
  Style=1,
  TLatexAlias='tW',
  LatexAlias='tW'
)
SampleGroup_TW_2018 = SampleGroup(
  Name='TW',
  Type='Bkgd',
  Samples=['SingleTop_tW_antitop_NoFullyHad','SingleTop_tW_top_NoFullyHad'],
  Year = 2018,
  Color=ROOT.kGray,
  Style=1,
  TLatexAlias='tW',
  LatexAlias='tW'
)
