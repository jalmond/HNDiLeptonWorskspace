#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString DatTag, double mass, TString smass);

void CheckHPTPerc(){
  
  DrawConfig("Nov8",100,"100");
  DrawConfig("Nov8",500,"500");
  DrawConfig("Nov8",1000,"1000");
  DrawConfig("Nov8",2000,"2000");
  DrawConfig("Nov8",20000,"20000");
  

}

void DrawConfig(TString DateTag ,double mass, TString smass){
    
  TString ID = "HNL_ULID";
  TString year = "2018";
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HPT");
  Plotter.SetupPlotter(year,"","Muon_HighPt_Smear");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/HighPtMuons/SignalSamples/";

  
  TCanvas* c1 = new TCanvas("HPTEff", "", 800, 800);
  c1->Draw();
  c1->cd();

  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

  canvas_margin(c1, c1_up, c1_down);

  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();

 
  TH1D *hist_Tune = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS_MET/Muon1_Pt_Muon_ULID_v5");
  TH1D *hist_Syst = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS_smearcorr/Muon_ULID_v5");

  //HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M"+smass+"_private.root","SS/Muon1_Pt_Muon_ULID_v3");

  double int_highpt = hist_Tune->Integral();
  double int_tight = hist_Syst->Integral();
  double int_r = int_tight/int_highpt;
  string str = std::to_string(int_r); 

  TH1D *hist_empty = (TH1D*)hist_Tune->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);

  if(hist_Tune->GetMaximum() > hist_Syst->GetMaximum() )hist_empty->GetYaxis()->SetRangeUser(1,hist_empty->GetMaximum()*1.4);
  else hist_empty->GetYaxis()->SetRangeUser(1,hist_Syst->GetMaximum()*1.4);
  
  hist_empty->GetXaxis()->SetLabelSize(0);
  hist_empty->Draw("hist");


  hist_Tune->SetLineWidth(2.0);
  hist_Tune->SetLineStyle(23);      
  hist_Tune->SetLineStyle(4);
  hist_Tune->Draw("histsame");
  
  hist_Syst->SetLineColor(kRed);
  
  hist_Syst->Draw("histsame");
    
  TLegend *lg = new TLegend(0.6, 0.75, 0.93, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.03);
  lg->AddEntry(hist_Tune,"Nom","l");
  lg->AddEntry(hist_Syst,"Smeared.","l");
  
  lg->Draw();
  
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.03);
  channelname.DrawLatex(0.2, 0.88,"m_{N} "+smass);
  
  //  channelname.DrawLatex(0.2, 0.8,"Tight/HPT = " +TString(str));
  
  c1_down->cd();
  TH1D *ratio_point = (TH1D *)hist_Syst->Clone();

  hist_axis(hist_empty, ratio_point);

  ratio_point->Divide(hist_Tune);
  ratio_point->GetYaxis()->SetTitle("#frac{Syst}{Nom}");
  ratio_point->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  ratio_point->Draw();
  
  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 1;
  x_1[1] = 3000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->Draw("same");

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = DateTag+"_SignalComp_Smear_"+ID +"_"+smass ;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  return;
}



