#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString Era, TString Type, TString sNum, TString sDen,TString lNum, TString lDen);

void CheckEff(){
  vector<TString> Etas = {"BB","EC"};
  vector<TString> TypesEl = {"Prompt_EE","CF_EE","Conv_EE","Fake_EE"};
  vector<TString> TypesMu = {"Prompt_MuMu","Conv_MuMu","Fake_MuMu"};
  for (auto ieta : Etas){
    for (auto itype : {"Fake_EE"}){
      DrawConfig("2016a",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_TopHNSSL_2016a","TopID "+ieta,"TopID "+ieta);
      DrawConfig("2016b",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_TopHNSSL_2016b","TopID "+ieta,"TopID "+ieta);
      DrawConfig("2017",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_TopHNSSL_2017","TopID "+ieta,"TopID "+ieta);
      DrawConfig("2018",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_TopHNSSL_2018","TopID "+ieta,"TopID "+ieta);
    }
    for (auto itype : {"Fake_MuMu"}){
      DrawConfig("2016a",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_TopHNL","TopID "+ieta,"TopID "+ieta);
      DrawConfig("2017",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_TopHNL","TopID "+ieta,"TopID "+ieta);
      DrawConfig("2018",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_TopHNL","TopID "+ieta,"TopID "+ieta);
    }
    //for (auto itype : {"Prompt_EE","CF_EE","Conv_EE"}){
    //  DrawConfig("2016a",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    //  DrawConfig("2017",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    //  DrawConfig("2018",itype,"Electron_pt_"+ieta+"_TopHNSST","Electron_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    // }
    //for (auto itype : {"Prompt_MuMu","Conv_MuMu"}){
    //  DrawConfig("2016a",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    //  DrawConfig("2017",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    // DrawConfig("2018",itype,"Muon_pt_"+ieta+"_TopHN","Muon_pt_"+ieta+"_NoCut","TopID "+ieta,"TopID "+ieta);
    // }
  }  

}

void DrawConfig(TString Era, TString Type, TString sNum,TString sDen,TString lNum, TString lDen){
    
  TString ID = "HNL_ULID";
  TString year = Era;
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("TopHNL");
  Plotter.SetupPlotter(year,"","ID_Rates");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/ElectronIDEff/Samples/Top/";

  
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
  
  TString filePath=path+"MC_"+year+"_DY_TT.root";
  std::ifstream file(filePath);
  if (!file) {
    std::cerr << "Error: File " << path+"MC_DY_TT.root" << " does not exist.\n";
    return 1; // Exit with a non-zero status code.
  }
  else cout << "Accessing " << filePath << endl;

  TH1D *hist_num = Plotter.ConstructHist(filePath,Type+"/"+sNum);
  TH1D *hist_denom = Plotter.ConstructHist(filePath,Type+"/"+sDen);
  hist_num->GetXaxis()->SetRangeUser(1,200);
  hist_denom->GetXaxis()->SetRangeUser(1,200);


  cout << "Num = " << Type+"/"+sNum <<  " denom = " << Type+"/"+sDen << endl;
  double int_highpt = hist_num->Integral();
  double int_tight = hist_denom->Integral();
  double int_r = int_tight/int_highpt;
  string str = std::to_string(int_r); 

  //hist_HPT->Scale(1/hist_HPT->Integral());
  //hist_ULID->Scale(1/hist_ULID->Integral());
 

  cout << "Setup hist " << endl;

  TH1D *hist_empty = (TH1D*)hist_num->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  
  if(hist_num->GetMaximum() > hist_denom->GetMaximum() )hist_empty->GetYaxis()->SetRangeUser(1,hist_empty->GetMaximum()*1.4);
  else hist_empty->GetYaxis()->SetRangeUser(1,hist_denom->GetMaximum()*1.4);
  
  hist_empty->GetXaxis()->SetRangeUser(1,200);

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
  
  cout << "Legend " << endl;
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.035);
  channelname.DrawLatex(0.2, 0.88,Type);
  channelname.DrawLatex(0.2, 0.83,year);
  
  //  channelname.DrawLatex(0.2, 0.8,"Tight/HPT = " +TString(str));
  
  c1_down->cd();
  TH1D *ratio_point = (TH1D *)hist_num->Clone();
  ratio_point->GetXaxis()->SetLabelSize(0);
  
  hist_axis(hist_empty, ratio_point);

  if(Type.Contains("CF")) c1_down->SetLogy();
  
  ratio_point->Divide(hist_denom);
  if(Type.Contains("Fake_")) ratio_point->GetYaxis()->SetRangeUser(0.01,0.5);
  else if(Type.Contains("CF")) ratio_point->GetYaxis()->SetRangeUser(0.00001,1);
  else if(Type.Contains("Prompt_"))ratio_point->GetYaxis()->SetRangeUser(0.6,1.1);
  else ratio_point->GetYaxis()->SetRangeUser(0.1,1.);

  ratio_point->GetYaxis()->SetTitle("#epsilon_{Fake}");
  ratio_point->GetXaxis()->SetTitle("p_{T} (GeV)");
  ratio_point->Draw("text");
  
  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 1;
  x_1[1] = 3000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->Draw("same");

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = Type + "_ID_Eff__"+sNum +"_"+sDen +"_"+year;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  cout << "END" << endl;
  return;
}



