import os,ROOT,math
import CMS_lumi, tdrstyle
from array import array
import mylib,canvas_margin
import copy

tdrstyle.setTDRStyle()
ROOT.TH1.AddDirectory(False)
#ROOT.gStyle.SetOptStat(0)

FILE_PATH = os.environ['FILE_MERGED_PATH']
PLOT_PATH = os.environ['PLOT_PATH']

Years = [
    "2016"
]
for Year in Years:
    
    basedir = FILE_PATH + '/HNL_DileptonCR/'+str(Year)+'/'
    outDir = PLOT_PATH+'/'+os.environ['SKANVERSION']+'/HNL_DileptonCR/'+str(Year)+'/'
    os.system('mkdir -p '+outDir)


    f_data_muon  = ROOT.TFile(basedir+'/HNL_DileptonCR_SkimTree_HNMultiLep_data_Muon.root')
    list_bkg = [ ["Fake",["NonPrompt_Muon"]], ["Charge flip", ["CF"]], ["DY", ["DYJets"]],["ZZ",["GluGluToZZto4e","GluGluToZZto4mu","ZZTo4L_m_1toInf_powheg","GluGluToZZto2e2mu"]] ,["Top",["TTLL_powheg","ttWToLNu","ttWToQQ","ttZToLLNuNu","ttZToQQ"]]  , ["WZ", ["WZTo3LNu_mll0p1_powheg"]] , ["WG", ["WGToLNuG"]] , ["ZG",["ZGTo2LG_01J"]] , ["VVV", ["WWW","ZZZ","WWZ","WZZ"]]]
    list_bkg = [ ["Charge flip", ["CF"]], ["DY", ["DYJets"]],["ZZ",["GluGluToZZto4e","GluGluToZZto4mu","ZZTo4L_m_1toInf_powheg","GluGluToZZto2e2mu"]] ,["Top",["TTLL_powheg","ttWToLNu","ttWToQQ","ttZToLLNuNu","ttZToQQ"]]  , ["WZ", ["WZTo3LNu_mll0p1_powheg"]] , ["WG", ["WGToLNuG"]] , ["ZG",["ZGTo2LG_01J"]] , ["VVV", ["WWW","ZZZ","WWZ","WZZ"]]]
    

    Hists=['Version1_Muon_FillEventCutflow']

    
    for hist in Hists:

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        h_data_muon=  f_data_muon.Get('FillEventCutflow/'+hist)

        h_Totbkg = 0

        for bkg in list_bkg:

            print (bkg [0])
            h_bkg = 0
            for x in bkg[1]:
                f_tmp  = ROOT.TFile(basedir+'/HNL_DileptonCR_SkimTree_HNMultiLep_'+x+'.root')
                h_tmp_bkg = f_tmp.Get('FillEventCutflow/'+hist)
                if h_bkg == 0:
                    if h_tmp_bkg:
                        h_bkg=h_tmp_bkg.Clone()
                elif h_tmp_bkg:
                    h_bkg.Add(h_tmp_bkg)

            if h_bkg:
                for x in range(1, h_bkg.GetNbinsX()+1):
                    print(h_bkg.GetXaxis().GetBinLabel(x) + ' ' + str(h_bkg.GetBinContent(x)))
            if h_Totbkg == 0:
                if h_bkg:
                    h_Totbkg= h_bkg.Clone()
            else:
                h_Totbkg.Add(h_bkg)

        print('Total:')

        for x in range(1, h_Totbkg.GetNbinsX()+1):
            print(h_Totbkg.GetXaxis().GetBinLabel(x) + ' ' + str(h_Totbkg.GetBinContent(x)))

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


        h_data_muon.SetLineWidth(2)
        h_data_muon.SetLineColor(ROOT.kBlack)

        h_data_muon.Draw("hist")

        for x in range(1, h_data_muon.GetNbinsX()+1):
            print(h_data_muon.GetXaxis().GetBinLabel(x) + ' ' + str(h_data_muon.GetBinContent(x))  + ' : ' + str(h_Totbkg.GetBinContent(x)))
            
        lg.AddEntry(h_data_muon,'Data Muon', 'l')
        lg.Draw()
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS Simulation} #font[42]{#it{#scale[0.8]{Preliminary}}}")
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(Year))+" fb^{-1} (13 TeV)")
        c1.SaveAs(outDir+'/BkgCRCutflow_'+hist+'.pdf')

