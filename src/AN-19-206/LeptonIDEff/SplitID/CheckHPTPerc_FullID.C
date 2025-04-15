#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString Era, TString Type, TString sNum, TString sDen,TString lNum, TString lDen, TString Eta);

void CheckHPTPerc_FullID(){
  vector<TString> Etas = {"BB","EC"};
  vector<TString> Types = {"Prompt_EE","CF_EE","Conv_EE","Fake_EE"};

  vector<TString> Eras = {"2016","2017","2018"};
  for (auto iera : Eras){
    for (auto ieta : Etas){
      for (auto itype : Types){
	//	DrawConfig(iera,itype,"Electron_pt_"+ieta+"_HNL_ULID_HighPt_"+iera,"Electron_pt_"+ieta+"_HNL_ULID_Baseline","Full ID","Baseline MVA ", ieta+"_"+iera);
	//	DrawConfig(iera,itype,"Electron_pt_"+ieta+"_HNL_ULID_HighPt_"+iera,"Electron_pt_"+ieta+"_HNL_ULID_"+iera,"Full ID [HighPt1]","ULID", ieta+"_"+iera);
	DrawConfig(iera,itype,"Electron_pt_"+ieta+"_HNL_ULID_HighPt_"+iera,"Electron_pt_"+ieta+"_HNL_ULID_"+iera,"Full ID [HighPt1]","ULID", ieta+"_"+iera);
      }
    }  
  }

}

void DrawConfig(TString Era, TString Type, TString sNum,TString sDen,TString lNum, TString lDen, TString Eta){
    
  TString ID = "HNL_ULID";
  TString year = Era;
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("ElectronID");
  Plotter.SetupPlotter(year,"","ElectronIDSF_HighPt");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/ElectronIDEff/Samples/";

  
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
  
 
  TH1D *hist_num = Plotter.ConstructHist(path+"MC_"+Era+"_DY_TT.root",Type+"/"+sNum);
  TH1D *hist_denom = Plotter.ConstructHist(path+"MC_"+Era+"_DY_TT.root",Type+"/"+sDen);

  cout << "Num = " << Type+"/"+sNum <<  " denom = " << Type+"/"+sDen << endl;
  double int_highpt = hist_num->Integral();
  double int_tight = hist_denom->Integral();
  double int_r = int_tight/int_highpt;
  string str = std::to_string(int_r); 

  //hist_HPT->Scale(1/hist_HPT->Integral());
  //hist_ULID->Scale(1/hist_ULID->Integral());
 

  TH1D *hist_empty = (TH1D*)hist_num->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  
  if(hist_num->GetMaximum() > hist_denom->GetMaximum() )hist_empty->GetYaxis()->SetRangeUser(1,hist_empty->GetMaximum()*1.4);
  else hist_empty->GetYaxis()->SetRangeUser(1,hist_denom->GetMaximum()*1.4);
  
  hist_empty->GetXaxis()->SetLabelSize(0);
  hist_empty->Draw("hist");


  hist_num->SetLineWidth(2.0);
  //  hist_num->SetLineStyle(23);      
  //  hist_num->SetLineStyle(4);
  hist_num->Draw("histsame");
  
  hist_denom->SetLineColor(kRed);
  
  hist_denom->Draw("histsame");
    
  TLegend *lg = new TLegend(0.6, 0.75, 0.93, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.03);
  lg->AddEntry(hist_num, lNum,"l");
  lg->AddEntry(hist_denom,lDen,"l");  
  lg->Draw();
  
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.035);
  channelname.DrawLatex(0.2, 0.88,Type + "_"+Eta);
  
  //  channelname.DrawLatex(0.2, 0.8,"Tight/HPT = " +TString(str));
  
  c1_down->cd();
  //  if(!Type.Contains("Prompt")) c1_down->SetLogy();

  TH1D *ratio_point = (TH1D *)hist_num->Clone();

  hist_axis(hist_empty, ratio_point);

  
  ratio_point->Divide(hist_denom);
  if(Type == "Prompt_EE")ratio_point->GetYaxis()->SetRangeUser(0.7,1.5);
  else  if(Type == "Fake_EE") ratio_point->GetYaxis()->SetRangeUser(0.7,4.1);
  else ratio_point->GetYaxis()->SetRangeUser(0.7,2);
  //if(ratio_point->GetBinContent(2) < 0.9) 
  //ratio_point->GetYaxis()->SetRangeUser(0.01,1.1);
  //  ratio_point->SetLineStyle(1);
  ratio_point->GetYaxis()->SetTitle("Eff ID(N)/ID(N-1)");
  ratio_point->GetXaxis()->SetTitle("p_{T} (GeV)");
  ratio_point->Draw();
  
  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 1;
  x_1[1] = 3000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->Draw("same");

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = Era+"_"+Type + "_ElectronID_SF_Split__"+sNum +"_"+sDen ;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  return;
}



