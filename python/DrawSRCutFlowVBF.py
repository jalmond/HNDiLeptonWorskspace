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


    f_MC_SSWW750  = ROOT.TFile(basedir+'/HNL_Signal_SSWW_HN_750.root')
    f_MC_SSWW1500  = ROOT.TFile(basedir+'/HNL_Signal_SSWW_HN_1500.root')
    f_MC_SSWW5000  = ROOT.TFile(basedir+'/HNL_Signal_SSWW_HN_5000.root')
    f_MC_SSWW10000  = ROOT.TFile(basedir+'/HNL_Signal_SSWW_HN_10000.root')
    if f_MC_SSWW750:
        print (basedir+'/HNL_Signal_SSWW_HN_750.root found')
    

    Hists=['SignalSSMuMu','Signal2SSMuMu']

    
    for hist in Hists:

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        h_SSWW750 = f_MC_SSWW750.Get('FillEventCutflow/'+hist)
        h_SSWW1500 = f_MC_SSWW1500.Get('FillEventCutflow/'+hist)
        h_SSWW5000 = f_MC_SSWW5000.Get('FillEventCutflow/'+hist)
        h_SSWW10000 = f_MC_SSWW10000.Get('FillEventCutflow/'+hist)
    
        if  h_SSWW750:
            print('FillEventCutflow/'+hist  + ' found') 
            h_SSWW750.Scale(1./h_SSWW750.Integral())
            h_SSWW1500.Scale(1./h_SSWW1500.Integral())
            h_SSWW5000.Scale(1./h_SSWW5000.Integral())
            h_SSWW10000.Scale(1./h_SSWW10000.Integral())

        h_Ref_SSWW750 = h_SSWW750.Clone("h_RefMCSSWW750"+hist+Year)
        h_Ref_SSWW1500 = h_SSWW1500.Clone("h_RefMCSSWW1500"+hist+Year)
        h_Ref_SSWW5000 = h_SSWW5000.Clone("h_RefMCSSWW5000"+hist+Year)
        h_Ref_SSWW10000 = h_SSWW10000.Clone("h_RefMCSSWW10000"+hist+Year)


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

        
        h_Ref_SSWW750.SetLineWidth(2)
        h_Ref_SSWW750.SetLineColor(ROOT.kRed)
        h_Ref_SSWW1500.SetLineWidth(2)
        h_Ref_SSWW1500.SetLineColor(ROOT.kBlue-4)
        h_Ref_SSWW5000.SetLineWidth(2)
        h_Ref_SSWW5000.SetLineColor(ROOT.kGreen)
        h_Ref_SSWW10000.SetLineWidth(2)
        h_Ref_SSWW10000.SetLineColor(ROOT.kOrange)

        
        h_Ref_SSWW750.Draw("hist")
        h_Ref_SSWW1500.Draw("histsame")
        h_Ref_SSWW5000.Draw("histsame")
        h_Ref_SSWW10000.Draw("histsame")
        lg.AddEntry(h_Ref_SSWW750,'SSWW[750 GeV]', 'l')
        lg.AddEntry(h_Ref_SSWW1500,'SSWW[1500 GeV]', 'l')
        lg.AddEntry(h_Ref_SSWW5000,'SSWW[5000 GeV]', 'l')
        lg.AddEntry(h_Ref_SSWW10000,'SSWW[10000 GeV]', 'l')
        lg.Draw()
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS Simulation} #font[42]{#it{#scale[0.8]{Preliminary}}}")
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(Year))+" fb^{-1} (13 TeV)")
        c1.SaveAs(outDir+'/SignalCutflow_SSWW_'+hist+'.pdf')

