#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void SignalRegionPlot_BDT(){
  
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"Muon","Electron","ElectronMuon"};
  vector<TString> masses= {"100","200","300","400","500"};
  
  for (auto year : eras){
    for (auto channel : channels){
      for (auto mass : masses){
    
	TString skim="";
	// check which pc is running script to setup local paths
	TString s_hostname = GetHostname();
	
	TString analysername="HNL_SignalRegionPlotter";
	
	// local path names
	TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
	TString ENV_PLOT_PATH = getenv("PLOT_PATH");
	TString FLATVERSION = getenv("FLATVERSION");
	
	
	MakeDir(ENV_PLOT_PATH + FLATVERSION);
	TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
	TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
	
	MakeDir(output);
	output+="/SignalRegionPlot/";
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
      
	
	TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Bkg.root";
	TString mc_path1 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_MC.root";
	TString mc_path2 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_NonPrompt.root";
	TString mc_path3 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_CF.root";
	TString mc_path4 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Conv.root";
	
	TFile * file_bkg = new TFile((mc_path).Data());
	TFile * file_prompt = new TFile((mc_path1).Data());
	TFile * file_fake = new TFile((mc_path2).Data());
	TFile * file_cf = new TFile((mc_path3).Data());
	TFile * file_conv = new TFile((mc_path4).Data());
	
	
	
	if(CheckFile(file_bkg) > 0) {
	  continue;
	}
	
	
	TString sr_hist= "LimitInputBDT/HNL_UL/"+mass+"/FillEventCutflow/"+channel+"SR";
	
	
	TString sig_path100 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIGMerged/HNL_SignalRegionPlotter_Type1_SS_M"+mass+".root";
	TFile * file_sig100 = new TFile((sig_path100).Data());
	
	
	if(CheckFile(file_sig100) > 0) {
	  continue;
	}
	
	
	TH1* hn_sig100        = GetHist(file_sig100,sr_hist);
	
	hn_sig100->GetYaxis()->SetTitle("Events / SR bin");
	if (!hn_sig100) continue;
	
	TH1* hn_bkg        = GetHist(file_bkg,sr_hist);
	TH1* hn_prompt        = GetHist(file_prompt,sr_hist);
	TH1* hn_fake        = GetHist(file_fake,sr_hist);
	TH1* hn_cf        = GetHist(file_cf,sr_hist);
	TH1* hn_conv        = GetHist(file_conv,sr_hist);
	if (!hn_bkg) continue;
	
	TString canvasname= sr_hist+channel;
	
	THStack *hs = new THStack("hs"+canvasname,canvasname);
	
	hn_prompt->SetFillColor(kSpring-1);
	if(channel != "Muon")hn_cf->SetFillColor(74);
	hn_conv->SetFillColor(kSpring-7);
	hn_fake->SetFillColor(870);
	
	hs->Add(hn_prompt);
	hs->Add(hn_fake);
	if(channel != "Muon")hs->Add(hn_cf);
	hs->Add(hn_conv);
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	c1->cd();
	hn_sig100->Scale(hn_bkg->Integral() / hn_sig100->Integral());
	
	hn_sig100->GetYaxis()->SetRangeUser(0.8, hn_sig100->GetMaximum()*1000);
	hn_sig100->SetLineColor(kRed);
	hn_sig100->Draw("hist");
	
	//hn_bkg->SetFillColor(kOrange);
	hs->Draw("histsame");
	hn_sig100->Draw("histsame");
	TString binlabel="BDT "+channel + " Channel";
	DrawLatexWithLabel(year,binlabel,0.25,0.68);
	
	TLegend *legend = MakeLegend(0.25, 0.75, 0.5, 0.92);
	legend->AddEntry(hn_sig100,"mN="+mass+" GeV","l");
	legend->AddEntry(hn_prompt,"Prompt","f");
	legend->AddEntry(hn_fake,"NonPrompt","f");
	if(channel != "Muon")legend->AddEntry(hn_cf,"CF","f");
	legend->AddEntry(hn_conv,"Conv","f");
	legend->Draw();
	
	
	TString save_pdf= output + "/LimitBDT"+mass+""+channel+"_"+year+"_.pdf";
	TString save_png= output + "/LimitBDT"+mass+""+channel+"_"+year+"_.png";
	
	c1->SetLogy();
	c1->SaveAs(save_pdf);
	c1->SaveAs(save_png);
	
	//system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/'");
	
	system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/'");
	
	system("scp " + output+"/LimitBDT"+mass+""+channel+"_"+year+"_.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/");
	system("scp " + output+"/LimitBDT"+mass+""+channel+"_"+year+"_.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/");
	
	cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/SignalRegionLimitInput/" << endl;
	
	delete c1;
	
	
	delete file_sig100;
	
	file_bkg->Close();
	
	delete file_bkg;
      }
    }
    
  }
    

  return;
}

