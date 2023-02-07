#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void LeptonVarPlots(){
  
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"Electrons"};//,"EE","EMu"};
  vector<TString> masses= {"100","300","400","500","800","1000","2000","5000","10000","20000"};
  
  vector<bool> ApplyLogY = {"true","false"};
  for (auto year : eras){
    
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    
    TString analysername="HNL_SignalStudies";
    
    TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_Bkg.root";
    
    TFile * file_bkg = new TFile((mc_path).Data());
    
    if(CheckFile(file_bkg) > 0) {
      continue;
    }
    
    for (auto channel : channels){
      for (auto mass : masses){
	
	TString skim="";
	// check which pc is running script to setup local paths
	TString s_hostname = GetHostname();
	
	// local path names
	
	TString ENV_PLOT_PATH = getenv("PLOT_PATH");
	TString FLATVERSION = getenv("FLATVERSION");
	
	
	MakeDir(ENV_PLOT_PATH + FLATVERSION);
	TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
	TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
	
	MakeDir(output);
	output+="/LeptonVarPlot/";
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
	
	
	TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_Bkg.root";
	
	
	
	vector <TString> vars = {"Dxy_el",
				 "Dz_el",
				 "Full5x5_sigmaIetaIeta",
				 "HoverE",
				 "IP3D",
				 "InvEminusInvP",
				 "IsGsfCtfScPixChargeConsistent",
				 "Jet_disc",
				 "MissingHits",
				 "MvaIso",
				 "Mva",
				 "PassConversionVeto",
				 "PtRatioAwayJet",
				 "PtRatio",
				 "PtRel_0",
				 "PtRel_1",
				 "Reliso_el",
				 "dEtaSeed",
				 "dPhiIn",
				 "isEcalDriven"};
				 
				 
				 
				 
      
	for (auto var : vars){
	  
	  TString sr_hist= channel+"/"+var+"_Electron_Fake";
	  
	  TString sig_path100 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIGMerged/HNL_SignalStudies_Type1_SS_M"+mass+".root";
	  
	  TFile * file_sig100 = new TFile((sig_path100).Data());
	  
	  if(CheckFile(file_sig100) > 0) {
	    continue;
	  }
	  
	  
	  cout << sig_path100 << " " << sr_hist << endl;
	  TH1* hn_sig100        = GetHist(file_sig100,sr_hist);
	  hn_sig100->GetYaxis()->SetTitle("Events ");
	  hn_sig100->SetLineWidth(2.);
	  
	  if (!hn_sig100) continue;
	  
	  TString sr_hist_fake= channel+"/"+var+"_Electron_Fake";
	  TString sr_hist_cf= channel+"/"+var+"_Electron_CF";
	  TString sr_hist_Extconv= channel+"/"+var+"_Electron_IntConv";
	  TString sr_hist_Intconv= channel+"/"+var+"_Electron_ExtConv";
	  
	  TH1* hn_fake        = GetHist(file_bkg,sr_hist_fake);
	  hn_fake->SetLineWidth(2.);
	  
	  TH1* hn_cf        = GetHist(file_bkg,sr_hist_cf);
	  hn_cf->SetLineWidth(2.);
	  TH1* hn_Extconv        = GetHist(file_bkg,sr_hist_Extconv);
	  hn_Extconv->SetLineWidth(2.);
	  TH1* hn_Intconv        = GetHist(file_bkg,sr_hist_Intconv);
	  hn_Intconv->SetLineWidth(2.);
	  
	  TString canvasname= sr_hist+channel+mass;
	  
	  hn_Intconv->SetLineColor(kSpring-1);
	  if(hn_cf)hn_cf->SetLineColor(kYellow);
	  if(hn_Extconv)hn_Extconv->SetLineColor(kSpring+7);
	  //if(hn_Extconv)hn_Extconv->SetLineStyle(2);
	  hn_fake->SetLineColor(870);
	  
	  
	  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	  
	  c1->cd();
	  
	  hn_sig100->Scale(1. / hn_sig100->Integral());
	  hn_fake->Scale(1./hn_fake->Integral());
	  hn_cf->Scale(1./hn_cf->Integral());
	  hn_Extconv->Scale(1./hn_Extconv->Integral());
	  hn_Intconv->Scale(1./hn_Intconv->Integral());
	  
	  hn_sig100->GetYaxis()->SetRangeUser(0.0001, hn_sig100->GetMaximum()*1.5);
	  hn_sig100->SetLineColor(kRed);
	  hn_sig100->Draw("hist");
	  
	  hn_fake->Draw("histsame");
	  hn_cf->Draw("histsame");
	  hn_Extconv->Draw("histsame");
	  hn_Intconv->Draw("histsame");
	  
	  hn_sig100->Draw("histsame");
	  TString binlabel=channel;
	  DrawLatexWithLabel(year,binlabel,0.25,0.68);
	  
	  TLegend *legend = MakeLegend(0.25, 0.75, 0.5, 0.92);
	  legend->AddEntry(hn_sig100,"mN="+mass+" GeV","l");
	  legend->AddEntry(hn_fake,"NonPrompt","l");
	  legend->AddEntry(hn_cf,"CF","l");
	  legend->AddEntry(hn_Extconv,"Ext Conv.","l");
	  legend->AddEntry(hn_Intconv,"Int Conv.","l");
	  
	  legend->Draw();
	  
	  for(unsigned int i=0; i < 2; i++){
	    
	    TString save_pdf= output + "/LeptonVar_"+var+"_"+channel+"_"+year+"_"+mass+".pdf";
	    TString save_png= output + "/LeptonVar_"+var+"_"+channel+"_"+year+"_"+mass+".png";
	    if(i==1){
	      save_pdf= output + "/LeptonVar_"+var+"_"+channel+"_"+year+"_"+mass+"_logY.pdf";
	      save_png= output + "/LeptonVar_"+var+"_"+channel+"_"+year+"_"+mass+"_logY.png";
	      
	    }
	    
	    if(i==1)c1->SetLogy();
	    c1->SaveAs(save_pdf);
	    c1->SaveAs(save_png);
	    
	    system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarPlots/'");
	    
	    system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarPlots/'");
	    
	    system("scp " +save_pdf+" jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarPlots/");
	    system("scp " +save_png + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarPlots/");
	    
	    cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/LeptonVarPlots/" << endl;
	  }
	  delete c1;
	  
	  
	  delete file_sig100;
	  
	}
      }
    }
    
      
    
    
    file_bkg->Close();
    
    delete file_bkg;
  }
  
  
  return;
}

