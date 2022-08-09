#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void PlotMVASignals(TString channel="muon", TString year="2017"){
  

  TString skim="SkimTree_HNMultiLep";
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  TString analysername="HNL_Signal";

  vector<TString> code_names= {"HNL_Signal"};
  vector<TString> channel_names= {"muon","electron"};

  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  if(std::find(channel_names.begin(), channel_names.end(), channel) != channel_names.end()) cout <<	"Running with channel " <<  channel <<	endl;
  else {cout << "Error in input of _chan: " << channel << endl;  for (auto i: channel_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("SKFLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/CutOpt/MVASignal/";
  MakeDir(output);

  output+=channel+"/";
  MakeDir(output);
  output+=year+"/";
  MakeDir(output);

  cout << "FakerateType1::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  TString data_path ="/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_Signal/"+year+"/HNL_Signal_SkimTree_HNMultiLep_bkg.root";
  
  TFile * file_data = new TFile((data_path).Data());
  if(CheckFile(file_data) > 0) {
    file_data->Close();
    delete file_data;
    return;
  }
  
  // canvas for hists
  TString canvasname= channel;
  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

  vector <TString> etabins = {"eta1","eta2","eta3"};
  vector <TString> ptbins  = {"10_15","15_20","20_30","30_40","40_50","50_100","100_2000"};
  vector <TString> selections = {"MVA"};
  
  vector <TString> ssww_signals = {"SSWWTypeI_NLO_SF_M1000", "SSWWTypeI_NLO_SF_M1500", "SSWWTypeI_NLO_SF_M20000", "SSWWTypeI_NLO_SF_M2500", "SSWWTypeI_NLO_SF_M5000", "SSWWTypeI_NLO_SF_M750"};
  vector <TString> dy_signals = {"VBFTypeI_NLO_SF_M1500", "VBFTypeI_NLO_SF_M2500", "VBFTypeI_NLO_SF_M700", "VBFTypeI_NLO_SF_M500", "DYTypeI_NLO_SF_M1000", "DYTypeI_NLO_SF_M200", "DYTypeI_NLO_SF_M500", "DYTypeI_NLO_SF_M100", "DYTypeI_NLO_SF_M1500", "DYTypeI_NLO_SF_M2500", "DYTypeI_NLO_SF_M700"};

  for (auto ieta : etabins){
    for (auto ipt : ptbins){
      for (auto isel : selections){

	for (unsigned int isig =0; isig <  dy_signals.size(); isig++){
	  
	  TString histname="MVA_"+ieta+"_pt_"+ipt;
	  
	  TString sig_path ="/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_Signal/"+year+"/HNL_Signal_"+dy_signals[isig]+".root";
	  
	  TFile * file_sig = new TFile((sig_path).Data());
	  
	  TH1D* sig_hist = GetHist(file_sig,isel+"/"+histname);
	  sig_hist->Scale(1/sig_hist->Integral());
	  double eff(1.);
	  double effL(1.);
	  string s_eff = std::to_string(eff);
	  string s_effL = std::to_string(eff/effL);
	  sig_hist->SetLineColor(GetHistColor(isig));
	  sig_hist->SetLineWidth(3.);
	  TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
	  //if(type.Contains("-1"))legend->AddEntry(data_hist,var + " Lep Type -1","l");	  
	  //c1->SetLogy();
	  c1->cd();
	  if(isig==0)  sig_hist->Draw("hist");
	  else sig_hist->Draw("histsame");

	  TLine *devz;
	  //if ( channel.Contains("el") ) devz= new TLine(-0.05,0.1,-0.05,data_hist->GetMaximum());
	  //else devz= new TLine(-0.02,0.1,-0.02,data_hist->GetMaximum());
	  
	  //devz->SetLineWidth(2);
	  //devz->SetLineStyle(1);
	  //devz->Draw("SAME");
	  TLine *devz2;
	  //	  if ( channel.Contains("el") ) devz2= new TLine(0.05,0.1,0.05,data_hist->GetMaximum());
	  //else devz2= new TLine(0.02,0.1,0.02,data_hist->GetMaximum());
	  //devz2->SetLineWidth(2);
	  //devz2->SetLineStyle(1);
	  //devz2->Draw("SAME");
	  
	  legend->Draw();
	
	  setTDRStyle();
	
	  
	  TString _leptype = "Lep Type " ;
	  //	DrawLatexWithLabel(year,,0.25,0.88);
	  DrawLatexWithLabel(year,ieta + "_"+ipt,0.25,0.78);
	  //DrawLatexWithLabel(year,channel,0.25,0.73);
	  
	  DrawLatexWithLabel(year,"Eff. = ["+TString(s_eff)+","+TString(s_effL)+"]",0.25,0.83);
	  
	  TString save_sg= output + "/histname_"+channel + "_"+year+"_"+ieta+"_"+ipt+"_"+isel+".pdf";
	  
	  c1->SaveAs(save_sg);
	  OutMessage("GetSignalEfficiency",save_sg);
	}
      }
    }
  }
  file_data->Close();
  
  delete file_data;
  delete c1;
  return;
}
