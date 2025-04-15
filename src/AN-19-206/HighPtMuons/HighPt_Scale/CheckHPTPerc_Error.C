#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag, double mass, TString smass);

void CheckHPTPerc_Error(){
  

  DrawConfig("Nov8",1000,"1000");
  DrawConfig("Nov8",2000,"2000");
  DrawConfig("Nov8",10000,"10000");

  //  DrawConfig("Nov8",500,"500");
  //DrawConfig("Nov8",1000,"1000");
  

}

void DrawConfig(TString DateTag ,double mass, TString smass){
    
  TString ID = "HNL_ULID";
  TString year = "2018";
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HPT");
  Plotter.SetupPlotter(year,"","Muon_HighPt_Scale");
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


 
  TH1D *hist_ULID_Nom    = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS/Muon1_Pt_Muon_ULID_v1");
  TH1D *hist_ULID_GEUp   = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS/Muon1_Pt_Muon_HighPt_Tune_GEUp");
  TH1D *hist_ULID_GEDown = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS/Muon1_Pt_Muon_HighPt_Tune_GEDown");
  TH1D *hist_ULID_GE = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_HNL_M"+smass+"_private.root","SS/Muon1_Pt_Muon_ULID_v7");
 

  //hist_HPT->Scale(1/hist_HPT->Integral());
  //hist_ULID->Scale(1/hist_ULID->Integral());
 

  TH1D *hist_empty = (TH1D*)hist_ULID_Nom->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);

  hist_empty->GetYaxis()->SetRangeUser(0,hist_empty->GetMaximum()*1.2);
  hist_empty->GetXaxis()->SetLabelSize(0);
  hist_empty->Draw("hist");


  hist_ULID_Nom->SetLineWidth(2.0);
  hist_ULID_Nom->SetLineStyle(23);      
  hist_ULID_Nom->SetLineStyle(4);
  hist_ULID_Nom->Draw("histsame");
  
  hist_ULID_GE->SetLineColor(kRed);
  hist_ULID_GEUp->SetLineColor(kRed);
  hist_ULID_GEDown->SetLineColor(kBlue);
  
  hist_ULID_GE->SetLineStyle(4);

  hist_ULID_GE->Draw("histsame");
  hist_ULID_GEUp->Draw("histsame");
  hist_ULID_GEDown->Draw("histsame");
    
  TLegend *lg = new TLegend(0.6, 0.75, 0.93, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.035);
  lg->AddEntry(hist_ULID_Nom,"Nominal","l");
  lg->AddEntry(hist_ULID_GE,"GE","l");
  lg->AddEntry(hist_ULID_GEUp,"GEUp","l");
  lg->AddEntry(hist_ULID_GEDown,"GEGEDown","l");
  
  lg->Draw();
  
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.035);
  channelname.DrawLatex(0.2, 0.88,"m_{N} "+smass);
  
  
  c1_down->cd();
  TH1D *ratio_point_GE = (TH1D *)hist_ULID_GE->Clone();
  TH1D *ratio_point_GEUp = (TH1D *)hist_ULID_GEUp->Clone();
  TH1D *ratio_point_GEDown = (TH1D *)hist_ULID_GEDown->Clone();
  hist_axis(hist_empty, ratio_point_GE);

  ratio_point_GE->Divide(hist_ULID_Nom);
  ratio_point_GEUp->Divide(hist_ULID_Nom);
  ratio_point_GEDown->Divide(hist_ULID_Nom);

  ratio_point_GE->GetYaxis()->SetRangeUser(0.5,1.5);
  ratio_point_GE->GetYaxis()->SetTitle("Diff.");
  ratio_point_GE->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  ratio_point_GE->Draw("");
  ratio_point_GEUp->Draw("same");
  ratio_point_GEDown->Draw("same");

  TLegend *lg2 = new TLegend(0.8, 0.45, 0.93, 0.55);
  lg2->SetFillStyle(0);
  lg2->SetBorderSize(0);
  lg2->SetTextSize(0.05);
  lg2->AddEntry(ratio_point_GE,"GE(TP)/PF","l");
  lg2->AddEntry(ratio_point_GEUp,"GE(TP scale up)/PF","l");
  lg2->AddEntry(ratio_point_GEDown,"GE(TP scale down)/PF","l");

  lg2->Draw();

  
  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 1;
  x_1[1] = 3000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->Draw("same");

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = DateTag+"_SignalComp_GEUncert_Scale_DY_"+ID +"_"+smass ;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  return;
}



