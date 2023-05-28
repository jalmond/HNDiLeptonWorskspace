#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void TauCheck(){
  
  vector<TString> eras = {"2016postVFP","2016preVFP","2017","2018"};
  vector<TString> SRs = {"SR1","SR2","SR3"};
  eras = {"2018"};
  
  vector<TString> channels = {"MuMu","EE","EMu"};


  
  for (auto channel : channels){
    for (auto year : eras){
      for (auto SR : SRs){

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
	output+="/TauCheck/";
	MakeDir(output);
	output+="/"+channel+"/";
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
	
	vector<TString> tmp;
	vector<TString> Masses = GetMassType1Strings(tmp, "");
	
	
	TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_SS2lOR3l_SSPrompt.root";
	
	TString np_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_NonPrompt_Lepton.root";
	
	TFile * file_bkg = new TFile((mc_path).Data());
	TFile * file_npbkg = new TFile((np_path).Data());
	
	if(CheckFile(file_bkg) > 0) {
	  continue;
	}
	
	TString sr_hist= channel + "/HNL_UL/FillEventCutflow/"+SR+"Tau";
	TH1* hn_bkg        = GetHist(file_bkg,sr_hist);
	TH1* hn_np         = GetHist(file_npbkg,sr_hist);
	if(!hn_np) cout << "Missing " << np_path << endl;

	for(auto im : Masses){
	  
	  TString sig_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIGMerged/HNL_SignalRegionPlotter_Type1_SS_M"+im+".root";
	  TFile * file_sig = new TFile((sig_path).Data());
	  
	  if(CheckFile(file_sig) > 0) {
	    continue;
	  }
	  
	  
	  TString canvasname= sr_hist+im;
	  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	  
	  TH1* hn_sig        = GetHist(file_sig,sr_hist);
	  if (!hn_sig) continue;
	  c1->cd();
	  
	  TString binlabel_max="";
	  double maxbin = -1.;
	  double nocut = -1;
	  for(unsigned int ibin = 1; ibin <  hn_sig->GetNbinsX()+1; ibin++){
	    
	  double binValue= 0.;
	  
	  if(hn_bkg->GetBinContent(ibin) > 0 ) binValue = hn_sig->GetBinContent(ibin)/ sqrt(hn_bkg->GetBinContent(ibin));
	  cout << ibin << " Sig= " << hn_sig->GetBinContent(ibin) << " Prompt= " << hn_bkg->GetBinContent(ibin) << " NP=" << hn_np->GetBinContent(ibin) << endl;
	  double signif = hn_sig->GetBinContent(ibin) / sqrt(hn_bkg->GetBinContent(ibin) + hn_np->GetBinContent(ibin));
	  if(signif > maxbin) {
	    maxbin = signif;
	    binlabel_max=hn_sig->GetXaxis()->GetBinLabel(ibin);
	  }
	  if(ibin==1) nocut=signif;
	  
	  hn_sig->SetBinContent(ibin, signif);
	}
	
	string sd = "Max(Sig) = "+to_string(maxbin/nocut);
	
	
	hn_sig->Scale(1./nocut);
	hn_sig->GetYaxis()->SetRangeUser(0.8, 1.2);
	hn_sig->Draw("hist");

	DrawLatexWithLabel(year,sd,0.45,0.78);
	DrawLatexWithLabel(year,binlabel_max,0.45,0.68);

	TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
	legend->AddEntry(hn_sig,"mN="+im+" GeV","l");
	legend->Draw();
	
	//setTDRStyle();
	
	TString save_pdf= output + "/"+SR+"Tau"+channel+ "_"+year+"_"+im+".pdf";
	TString save_png= output + "/"+SR+"Tau"+channel+ "_"+year+"_"+im+".png";
	
	c1->SaveAs(save_pdf);
	c1->SaveAs(save_png);
	
	system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/TauCheck/'");
	
	system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/TauCheck/'");

	system("scp " + output+"/"+SR+"Tau"+channel+ "_"+year+"_"+im+".pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/TauCheck/");
	system("scp " + output+"/"+SR+"Tau"+channel+ "_"+year+"_"+im+".png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/TauCheck/");
	
	cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/TauCheck/" << endl;

	delete c1;
	

	delete file_sig;
	
	}	
	file_bkg->Close();
	
	delete file_bkg;
	
      }
    }
  }


  return;
}

