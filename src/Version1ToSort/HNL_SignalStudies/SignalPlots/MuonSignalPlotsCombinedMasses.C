#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include<stdlib.h>
#include <iostream>



void MuonSignalPlotsCombinedMasses(){
  
  //vector<TString> eras = {"2016postVFP","2016preVFP","2017","2018"};
  vector<TString> eras = {"2018"};
  vector<TString> signals_available;
  vector<TString> signals_missing;
  for (auto year : eras){
    TString skim="";
    // check which pc is running script to setup local paths
    TString s_hostname = GetHostname();
    
    //HNtypeI_Dilepton_SkimTree_SSNonIso_DYJets.root
    TString analysername="HNL_SignalStudies";
    
    
    // local path names
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    TString ENV_PLOT_PATH = getenv("PLOT_PATH");
    TString FLATVERSION = getenv("FLATVERSION");
    
    
    MakeDir(ENV_PLOT_PATH + FLATVERSION);
    TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
    TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
    
    MakeDir(output);
    output+="/SignalPlots/";
    MakeDir(output);
    output+="/Muon/";
    MakeDir(output);
    
    output+=year+"/";
    MakeDir(output);
    
    
    // Set Plotting style
    setTDRStyle();
    gStyle->SetPalette(1);
    
    
    vector<TString> SSMasses = {"800","1000","1500","2000","5000","20000"};
    vector<TString> DYMasses = {"100","250","1000","2000"};              
    vector<TString> VBFMasses = {"1000","2000"};
    vector<TString> Signals = {"SSWWTypeI_M","DYTypeI_DF_M","VBFTypeI_DF_M"};
    

    TString _dir="SignalGenMuMu";
    for (auto isig: Signals) {

      vector<TString> masses;
      if(isig == "SSWWTypeI_M") masses=SSMasses;
      if(isig == "DYTypeI_DF_M")masses=DYMasses;
      if(isig == "VBFTypeI_DF_M")masses=VBFMasses;

      TString mc_path = input_path +"/"+year+"/SIG/"+analysername+"_"+isig+"500_private.root";

      TFile * file_mc = new TFile((mc_path).Data());

      
      vector<TString> vars = GetListFromKeys(file_mc,_dir,"TH1D");
      
      int nvar=0;
      for (auto var: vars){

	TString canvasname= _dir+isig+year+var;

	nvar++;

	cout << "Running on variable " << var << endl;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	TString s_var = _dir+"/"+var;
	
	// Get TH1 for each type
	
	vector<double> newrbins;
	Double_t array_newrbins[newrbins.size()];
	
	TH1D* hn_sig        = GetHistFull(newrbins, file_mc,s_var, GetHistColor(0), 3.);
	FormatHistogram(hn_sig, var, 0,0);

	c1->cd();

	NormHist(hn_sig);
	hn_sig->Draw("hist");
	TLegend *legend = MakeLegend(0.6, 0.75, 0.9, 0.92);
	legend->AddEntry(hn_sig,isig+"[500]","l");

	setTDRStyle();
	
	int n_sig(0);

	double ymax=-1;
	for(auto im : masses){
	  n_sig++;
	  TString mc_path2 = input_path +"/"+year+"/SIG/"+analysername+"_"+isig+im+"_private.root";
	  cout << "--------- " << mc_path2 << endl;
	  TFile * file_mc2 = new TFile((mc_path2).Data());

	  if(CheckFile(file_mc2) > 0) {
	    cout << isig << " mass = " << im << " missing" << endl;
	    signals_missing.push_back(year+"_HNL_Signal_"+isig+im+".root");
	    continue;
	  }
	  
	  signals_available.push_back(year+"_HNL_Signal_"+isig+im+".root");
	  
	  TH1D* hn_sig2        = GetHistFull(newrbins, file_mc2,s_var, GetHistColor(n_sig), 3.);

	  FormatHistogram(hn_sig2, var, n_sig,ymax);
	  NormHist(hn_sig2);	  
	  if(ymax < hn_sig2->GetMaximum()) ymax = hn_sig2->GetMaximum();
 
	  hn_sig2->Draw("histsame");

	  legend->AddEntry(hn_sig2,isig+im,"l");
	
	  //if(file_mc2){
	  //  file_mc2->Close();
	  //  delete file_mc2;
	  // }
	}
      
	double max = (ymax > hn_sig->GetMaximum()) ? ymax : hn_sig->GetMaximum();
	hn_sig->GetYaxis()->SetRangeUser(0., max*1.4);
	hn_sig->Draw("histsame");

	legend->Draw();	  
	TString save_pdf= output + "/CombinedMasses_"+var+ "_"+year+isig+".pdf";
	TString save_png= output + "/CombinedMasses_"+var+ "_"+year+isig+".png";
	c1->SaveAs(save_pdf);
	c1->SaveAs(save_png);
	
	system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalPlots/'");
	system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalPlots/Muon/'");
	system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalPlots/Muon/'");
	
	system("scp " + save_pdf+ "  jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalPlots/Muon/");
	system("scp " + save_png +  " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalPlots/Muon/");
	
	delete c1; 	

	
      }	
      file_mc->Close();
      
      delete file_mc;
     

    }
  }
  

  cout << "List of signals at tamsa " << endl;
  for(auto is_av : signals_available) cout << is_av << endl;
  cout << " " << endl;
  cout << "List of missing signals at tamsa " << endl;

  for(auto is_miss : signals_missing)  cout << is_miss << endl;
  return;
}

