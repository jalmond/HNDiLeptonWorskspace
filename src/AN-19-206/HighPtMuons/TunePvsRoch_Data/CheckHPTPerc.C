#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString DatTag, double mass, TString smass,TString year);

void CheckHPTPerc(){
  
  DrawConfig("Nov8",100,"SR1","2016");
  DrawConfig("Nov8",100,"SR2","2016");
  DrawConfig("Nov8",100,"SR3","2016");

  DrawConfig("Nov8",100,"SR1","2017");
  DrawConfig("Nov8",100,"SR2","2017");
  DrawConfig("Nov8",100,"SR3","2017");

  DrawConfig("Nov8",100,"SR1","2018");
  DrawConfig("Nov8",100,"SR2","2018");
  DrawConfig("Nov8",100,"SR3","2018");  

}

void DrawConfig(TString DateTag ,double mass, TString smass, TString year){
    
  TString ID = "HNL_ULID";

  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HPT_DATA");
  Plotter.SetupPlotter(year,"","Muon_HighPt_TunevsRoch_Data");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/HighPtMuons/SignalSamples/Data/"+year+"/";

  
  TCanvas* c1 = new TCanvas("HPTEff", "", 1200, 800);
  c1->Draw();
  c1->cd();

  canvas_margin(c1);
 
  cout << path+"HNL_HighPtMuon_Studies_SkimTree_DileptonBDT_DoubleMuon.root" << endl;
  
  TH1D *hist = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_DileptonBDT_DoubleMuon.root","Pull_OS_"+smass+"_N");

  hist_axis(hist);

  
  if(!hist)  return;
  TH1D *hist_empty = (TH1D*)hist->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetYaxis()->SetTitle("Events");
  hist_empty->GetXaxis()->SetTitle("(p^{TuneP}_{T}- p_{T})/p^{TuneP}_{T}");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  hist_empty->GetXaxis()->SetRangeUser(-1,1);

  hist_empty->Draw("hist");


  hist->SetLineWidth(2.0);
  hist->GetXaxis()->SetRangeUser(-1,1);

  hist->Draw("histsame");


  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  if(year=="2016preVFP")latex_Lumi.DrawLatex(0.7, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(year=="2016postVFP")latex_Lumi.DrawLatex(0.7, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(year=="2016") latex_Lumi.DrawLatex(0.7, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(year=="2017") latex_Lumi.DrawLatex(0.7, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(year=="2018") latex_Lumi.DrawLatex(0.7, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(year=="Run2") latex_Lumi.DrawLatex(0.7, 0.96, "137.9 fb^{-1} (13 TeV)");
  
    
  TLegend *lg = new TLegend(0.6, 0.75, 0.93, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.03);
  
  lg->Draw();
  
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.03);
  channelname.DrawLatex(0.2, 0.88,smass);
  channelname.DrawLatex(0.2, 0.83,year);
  channelname.DrawLatex(0.7, 0.83,"DoubleMuon");
  
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = DateTag+"_TunePvsRoch_DATA_"+ID +"_"+smass ;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;

  c1->SetLogy();
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  return;
}



