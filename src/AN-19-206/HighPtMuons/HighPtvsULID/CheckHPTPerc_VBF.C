#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag, double mass, TString smass);

void CheckHPTPerc_VBF(){
  
  DrawConfig("Nov8",500,"500");
  DrawConfig("Nov8",1000,"1000");
  DrawConfig("Nov8",2000,"2000");
  

}

void DrawConfig(TString DateTag ,double mass, TString smass){
    
  TString ID = "HNL_ULID";
  TString year = "2018";
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HPT");
  Plotter.SetupPlotter(year,"","Muon_HighPtvsULID");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_HighPtMuon_Studies/2018/";
  
  TCanvas* c1 = new TCanvas("HPTVBFEff", "", 1200, 800);
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

 
  TH1D *hist_HPT = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_VBFTypeI_DF_M"+smass+"_private.root","SS/Muon1_Pt_Muon_HighPt_v3");
  TH1D *hist_ULID = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_VBFTypeI_DF_M"+smass+"_private.root","SS/Muon1_Pt_Muon_ULID_v3");

  double int_highpt = hist_HPT->Integral();
  double int_tight = hist_ULID->Integral();
  double int_r = int_tight/int_highpt;
  string str = std::to_string(int_r);

    
  //hist_HPT->Scale(1/hist_HPT->Integral());
  //hist_ULID->Scale(1/hist_ULID->Integral());
 

  TH1D *hist_empty = (TH1D*)hist_ULID->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);

  if(hist_ULID->GetMaximum() > hist_HPT->GetMaximum() )hist_empty->GetYaxis()->SetRangeUser(1,hist_empty->GetMaximum()*1.4);
  else hist_empty->GetYaxis()->SetRangeUser(1,hist_HPT->GetMaximum()*1.4);
  
  hist_empty->GetXaxis()->SetLabelSize(0);
  hist_empty->Draw("hist");


  hist_ULID->SetLineWidth(2.0);
  hist_ULID->SetLineStyle(23);      
  hist_ULID->SetLineStyle(4);
  hist_ULID->Draw("histsame");
  
  hist_HPT->SetLineColor(kRed);
  
  hist_HPT->Draw("histsame");
    
  TLegend *lg = new TLegend(0.55, 0.8, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.03);
  lg->AddEntry(hist_HPT,"highpt id","l");
  lg->AddEntry(hist_ULID,"tight id","l");
  
  lg->Draw();
  
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.03);
  channelname.DrawLatex(0.2, 0.88,"W#gamma Mass "+smass);
  channelname.DrawLatex(0.2, 0.8,"Tight/HPT = " +TString(str));
  
  c1_down->cd();
  TH1D *ratio_point = (TH1D *)hist_HPT->Clone();

  hist_axis(hist_empty, ratio_point);

  ratio_point->Divide(hist_ULID);
  ratio_point->GetYaxis()->SetTitle("#frac{HighPt}{Tight}");
  ratio_point->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  ratio_point->Draw();
  
  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 1;
  x_1[1] = 3000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->Draw("same");

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = DateTag+"_SignalComp_VBF_"+ID +"_"+smass ;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  return;
}



