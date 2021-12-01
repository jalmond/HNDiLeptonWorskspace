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


    f_MC_DY100  = ROOT.TFile(basedir+'/HNL_Signal_DYTypeI_NLO_SF_M100.root')
    f_MC_DY1000 = ROOT.TFile(basedir+'/HNL_Signal_DYTypeI_NLO_SF_M1000.root')

    Hists=['SignalMuMu_SS','SignalMuMu_OS','SignalElEl_SS','SignalElEl_OS']

    
    for hist in Hists:

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        h_DY100 = f_MC_DY100.Get('FillEventCutflow/'+hist)
        h_DY1000 = f_MC_DY1000.Get('FillEventCutflow/'+hist)
    
        if  h_DY100:
            h_DY100.Scale(1./h_DY100.Integral())

        if  h_DY1000:
            h_DY1000.Scale(1./h_DY1000.Integral())

        h_Ref_DY100 = h_DY100.Clone("h_RefMCDY100"+hist+Year)
        h_Ref_DY1000 = h_DY1000.Clone("h_RefMCDY1000"+hist+Year)


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

        
        h_Ref_DY100.SetLineWidth(2)
        h_Ref_DY100.SetLineColor(ROOT.kRed)

        h_Ref_DY1000.SetLineWidth(2)
        h_Ref_DY1000.SetLineColor(ROOT.kBlue)
        
        h_Ref_DY100.Draw("hist")
        h_Ref_DY1000.Draw("histsame")
        lg.AddEntry(h_Ref_DY100,'DY[100 GeV]', 'l')
        lg.AddEntry(h_Ref_DY1000,'DY[1000 GeV]', 'l')
        lg.Draw()
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS Simulation} #font[42]{#it{#scale[0.8]{Preliminary}}}")
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(Year))+" fb^{-1} (13 TeV)")
        c1.SaveAs(outDir+'/SignalCutflow_'+hist+'.pdf')

