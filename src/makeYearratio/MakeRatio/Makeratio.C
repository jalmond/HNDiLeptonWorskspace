#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void Makeratio(TString histname="SR1_HighmassCR/SR1_HighmassCR_lep2_pt_HNtypeI_Dilepton_EE_HNTight2016",  TString path_2016="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2016/HNtypeI_Dilepton_SkimTree_SSHN_FakeEE.root", TString path_2017="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2017/HNtypeI_Dilepton_SkimTree_SSHN_FakeEE.root",TString path_2018="/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/HNtypeI_Dilepton/2018/HNtypeI_Dilepton_SkimTree_SSHN_FakeEE.root",TString savename="EEFake_HNTight2016_lep2_pt", double xmin=0., double xmax=100., int rebin =2){

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  TString analysername = "HNtypeI_Dilepton";
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/Bkgratio/";
  MakeDir(output);

  MakeDir(output);
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TLegend *legend_g = MakeLegend(0.6, 0.7, 0.9, 0.92);
  // canvas for hists
  TString canvasname="c_"+histname;


  TFile * file_2016 = new TFile((path_2016).Data());
  TFile * file_2017 = new TFile((path_2017).Data());
  TFile * file_2018 = new TFile((path_2018).Data());
  
  if(CheckFile(file_2016) > 0) return;
  if(CheckFile(file_2017) > 0) return;
  if(CheckFile(file_2018) > 0) return;
  

  TH1* hist_2016 = GetHist(file_2016,histname);
  TH1* hist_2017 = GetHist(file_2017,histname);
  TH1* hist_2018 = GetHist(file_2018,histname);
  cout << hist_2016->Integral() << " " << hist_2017->Integral() << " " << hist_2018->Integral() << endl;
  if(rebin < 0) rebin = hist_2016->GetNbinsX();
  hist_2016->Rebin(rebin);
  hist_2017->Rebin(rebin);
  hist_2018->Rebin(rebin);
  
  TH1* hist_2016Clone = (TH1*)hist_2016->Clone("2016");

  TH1* hist_2017Clone = (TH1*)hist_2017->Clone("2017");
  TH1* hist_2018Clone = (TH1*)hist_2018->Clone("2018");

  //hist_2016->SetLineColor(kRed);
  hist_2017->SetLineColor(kOrange);
  hist_2018->SetLineColor(kGreen-2);
  hist_2016->SetLineWidth(2.);
  hist_2017->SetLineWidth(2.);
  hist_2018->SetLineWidth(2.);

  hist_2017->Divide(hist_2016Clone);
  hist_2018->Divide(hist_2016Clone);
  hist_2018Clone->Divide(hist_2017Clone);
  hist_2018Clone->SetLineColor(kViolet);
  hist_2016->Divide(hist_2016Clone);
  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
      
  c1->cd();
  setTDRStyle();

  hist_2016->GetXaxis()->SetRangeUser(xmin, xmax);
  hist_2016->GetYaxis()->SetRangeUser(-3., 5);
  hist_2016->GetYaxis()->SetTitle("Ratio");
  hist_2016->Draw("histaxis");
  hist_2016->Draw("histsame");
    
  hist_2017->Draw("histsame");
  hist_2018->Draw("histsame");
  hist_2018Clone->Scale(-1.);
  hist_2018Clone->Draw("histsame");
  
  double r_2017_lumi= 41.5/35.9;
  double r_2018_lumi= 59.9/35.9;
  double r_2018_17_lumi= -59.9/41.5;
  
  TLine *line_r_2017_lumi = new TLine(hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetFirst()),r_2017_lumi,hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetLast()+1),r_2017_lumi  );
  TLine *line_r_2018_lumi = new TLine(hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetFirst()),r_2018_lumi,hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetLast()+1),r_2018_lumi  );
  TLine *line_r_2018_17_lumi = new TLine(hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetFirst()),r_2018_17_lumi,hist_2016->GetBinLowEdge(hist_2016->GetXaxis()->GetLast()+1),r_2018_17_lumi  );

  line_r_2017_lumi->SetLineWidth(3.);
  line_r_2017_lumi->SetLineStyle(3);
  line_r_2017_lumi->SetLineColor(kOrange);
  
  line_r_2017_lumi->Draw("SAME");

  line_r_2018_lumi->SetLineWidth(3.);
  line_r_2018_lumi->SetLineStyle(2);
  line_r_2018_lumi->SetLineColor(kGreen-2);
  line_r_2018_lumi->Draw("SAME");

  
  line_r_2018_17_lumi->SetLineWidth(3.);
  line_r_2018_17_lumi->SetLineStyle(2);
  line_r_2018_17_lumi->SetLineColor(kViolet);
  line_r_2018_17_lumi->Draw("SAME");

  
  AllLegendEntry(legend_g,hist_2016,"2016/2016","l");
  AllLegendEntry(legend_g,hist_2017,"2017/2016","l");
  AllLegendEntry(legend_g,hist_2018,"2018/2016","l");
  AllLegendEntry(legend_g,hist_2018Clone,"2018/2017","l");
  legend_g->AddEntry(line_r_2017_lumi,"Lumi Ratio 17/16","l");
  legend_g->AddEntry(line_r_2018_lumi,"Lumi Ratio 18/16","l");
  legend_g->AddEntry(line_r_2018_17_lumi,"Lumi Ratio 18/17","l");
  legend_g->Draw();
  
  //DrawLatexWithLabel("2016","HighMass "+_sr,0.25,0.88);
  
  
  
  TString save_sg= output + "/hist_" + savename + ".pdf";
  c1->SaveAs(save_sg);
  OutMessage("GetSignalEfficiency",save_sg);

}
