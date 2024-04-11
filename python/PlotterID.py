import os,ROOT
import mylib
import ctypes
import canvas_margin
import tdrstyle
import CMS_lumi, tdrstyle
import math
from array import array

class IDPlotter:

    def __init__(self,Era,Region,Channel):
        self.DataYear=Era   
        self.OutputDirectory="./"
        self.Region=Region
        self.Channel=Channel


    def MakeOptDHist(self, Masses):
        

    def MakeAllIDHist(self,sorted_x):

        ROOT.gErrorIgnoreLevel = ROOT.kFatal

        tdrstyle.setTDRStyle()
        ROOT.TH1.AddDirectory(False)
        
        Outdir = self.OutputDirectory+'/'+self.Region+'/'
        os.system('mkdir -p '+Outdir)
        

        nBins=len(sorted_x)
        xBins = [0]
        for x in range(0, nBins):
            xBins.append(x+1)
        xBins = array("d",xBins)
        
        h_dummy_up = ROOT.TH1D('h_dumy_up', '', nBins, xBins)
        h_dummy_up.GetXaxis().SetRangeUser(0., nBins)

        
        c1 = ROOT.TCanvas('c1', '', 800, 800)
        c1_up = ROOT.TPad("c1_up", "", 0, 0, 1, 1)
        c1_up.SetTopMargin( 0.052 )
        c1_up.SetBottomMargin( 0.13 )
        c1_up.SetRightMargin( 0.032 )
        c1_up.SetLeftMargin( 0.15 )
        c1.Draw()
        c1_up.Draw()
        c1_up.cd()
        c1.cd()

        latex_CMSPriliminary = ROOT.TLatex()
        latex_Lumi = ROOT.TLatex()
        latex_CMSPriliminary.SetNDC()
        latex_Lumi.SetNDC()
        latex_CMSPriliminary.SetTextSize(0.035)
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")
        
        latex_Lumi.SetTextSize(0.035)
        latex_Lumi.SetTextFont(42)
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumi(float(self.DataYear))+" fb^{-1} (13 TeV)")
        
        h_dummy_up.SetTitle("")
        h_dummy_up.GetYaxis().SetLabelSize(0.04)
        h_dummy_up.GetYaxis().SetTitleSize(0.04)
        h_dummy_up.GetYaxis().SetTitleOffset(1.30)
        h_dummy_up.GetXaxis().SetLabelSize(0.035)
        h_dummy_up.GetXaxis().SetTitleSize(0.055)
        h_dummy_up.GetYaxis().SetTitle('#Sigma ID_{FOM} / #Sigma POG_{FOM}')
        
        for x in range(0,len(sorted_x)):
            label=sorted_x[x][0]
            label=label.replace("LimitBins/MuonSR","")
            label=label.replace("/","")

            h_dummy_up.SetBinContent(x+1,sorted_x[x][1])
            h_dummy_up.SetBinError(x,0)
            h_dummy_up.GetXaxis().SetBinLabel(x+1,label)     
        h_dummy_up.SetLabelSize(0.02,"X")

        h_dummy_up.GetYaxis().SetRangeUser(0., h_dummy_up.GetMaximum()*1.2)

        xbin, ybin = array( 'd' ), array( 'd' )

        for x in range(1,len(sorted_x)):
            xbin.append(x)
            ybin.append(sorted_x[x][1])
            
        gr_ID = ROOT.TGraph(nBins,xbin,ybin)

        c1_up.cd()

        h_dummy_up.Draw("hist")
        h_dummy_up.Draw("histsame")

        gr_D = ROOT.TGraphAsymmErrors(h_dummy_up)
        gr_D.SetLineWidth(2)
        gr_D.SetMarkerSize(0.)
        gr_D.SetMarkerColor(ROOT.kBlack)
        gr_D.SetLineColor(ROOT.kBlack)

        #gr_D.Draw("p0same")

        latex_ID = ROOT.TLatex()
        latex_ID.SetNDC()
        latex_ID.SetTextSize(0.025)
        latex_ID.SetTextFont(42)
        TLabel=sorted_x[nBins-1][0]
        TLabel=TLabel.replace("LimitBins/MuonSR","")
        TLabel=TLabel.replace("/","")
        latex_ID.DrawLatex(0.2, 0.8, "Opt ID="+TLabel+"["+ str(round(sorted_x[nBins-1][1],3)) +"]")
        

        ## y=1 graph                                                                                                                                        
        g1_x = [0, nBins]
        g1_y = [1, 1]
        g1 = ROOT.TGraph(2, array("d", g1_x ), array("d", g1_y ))
        g1.SetLineStyle(10)
        g1.Draw("same")

        c1.SaveAs('TEST.png')
