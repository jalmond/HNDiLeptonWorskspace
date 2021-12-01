import os,ROOT,math
import CMS_lumi, tdrstyle
from array import array
import mylib,canvas_margin
import copy

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
#ROOT.gStyle.SetOptStat(0)

FILE_PATH = os.environ['FILE_PATH']
PLOT_PATH = os.environ['PLOT_PATH']

Years = [
    "2017"
]
for Year in Years:
    
    basedir = FILE_PATH + '/HNL_Signal/'+str(Year)+'/'
    outDir = PLOT_PATH+'/'+os.environ['SKANVERSION']+'/HNL_Signal/'+str(Year)+'/'
    os.system('mkdir -p '+outDir)


    f_MC_TriLMu100  = ROOT.TFile(basedir+'/HNL_Signal_HeavyN_lll_mu_100.root')


    Hists=['SignalMuMu','SignalMuMu']

    
    for hist in Hists:

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        h_TriLepMu100OS = f_MC_TriLMu100.Get('FillEventCutflow/'+hist+'_OS')
        h_TriLepMu100SS = f_MC_TriLMu100.Get('FillEventCutflow/'+hist+'_SS')
        
        if h_TriLepMu100OS :
            h_TriLepMu100OS.Scale(1./h_TriLepMu100OS.Integral())
            h_TriLepMu100SS.Scale(1./h_TriLepMu100SS.Integral())

        h_Ref_TriLepMu100OS = h_TriLepMu100OS.Clone("h_RefMCTriLepMu100OS"+hist+Year)
        h_Ref_TriLepMu100SS = h_TriLepMu100SS.Clone("h_RefMCTriLepMu100SS"+hist+Year)

        lg = ROOT.TLegend(0.55, 0.7, 0.90, 0.90)
        lg.SetBorderSize(0)
        lg.SetFillStyle(0)

        c1.cd()
        
        str_channel = ""
        channelname = ROOT.TLatex()
        channelname.SetNDC()
        channelname.SetTextSize(0.037)
        channelname.DrawLatex(0.2, 0.88, str_channel)

        latex_CMSPriliminary = ROOT.TLatex()
        latex_Lumi = ROOT.TLatex()

        latex_CMSPriliminary.SetNDC()
        latex_Lumi.SetNDC()
        latex_CMSPriliminary.SetTextSize(0.035)
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS Simulation} #font[42]{#it{#scale[0.8]{Preliminary}}}")


        latex_Lumi.SetTextSize(0.035)
        latex_Lumi.SetTextFont(42)

        
        h_Ref_TriLepMu100OS.SetLineWidth(2)
        h_Ref_TriLepMu100OS.SetLineColor(ROOT.kRed)
        h_Ref_TriLepMu100SS.SetLineWidth(2)
        h_Ref_TriLepMu100SS.SetLineColor(ROOT.kGreen)

        h_Ref_TriLepMu100OS.Draw("hist")
        h_Ref_TriLepMu100SS.Draw("histsame")
 
        lg.AddEntry(h_Ref_TriLepMu100SS,'Trilep(SSmm)[100 GeV]', 'l')
        lg.AddEntry(h_Ref_TriLepMu100OS,'Trilep(OSmm)[100 GeV]', 'l')
        lg.Draw()
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS Simulation} #font[42]{#it{#scale[0.8]{Preliminary}}}")
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(Year))+" fb^{-1} (13 TeV)")
        c1.SaveAs(outDir+'/SignalCutflowTrilep_'+hist+'.pdf')

