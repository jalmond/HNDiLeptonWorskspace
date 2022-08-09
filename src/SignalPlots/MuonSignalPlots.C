#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MuonSignalPlots(){
  
  vector<TString> eras = {"2016postVFP","2016preVFP","2017","2018"};

  vector<TString> signals_available;
  vector<TString> signals_missing;
  for (auto year : eras){
    TString skim="";
    // check which pc is running script to setup local paths
    TString s_hostname = GetHostname();
    
    //HNtypeI_Dilepton_SkimTree_SSNonIso_DYJets.root
    TString analysername="HNL_Signal";
    
    vector<TString> code_names= {"HNL_Signal"};
    
    if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
    else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }
    
    // local path names
    TString ENV_FILE_PATH= (getenv("FILE_PATH"));
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    TString ENV_PLOT_PATH = getenv("PLOT_PATH");
    TString FLATVERSION = getenv("FLATVERSION");
    
    
    MakeDir(ENV_PLOT_PATH + FLATVERSION);
    TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
    TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
    
    MakeDir(output);
    output+="/SignalPlots/";
    MakeDir(output);
    output+="/Muon/";
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
    
    
    vector<TString> SSMasses = {"500","600","700","750","800","900","1000","1100","1200","1300","1500","1700","2000","2500","3000","5000","10000","15000","20000"};
    vector<TString> DYMasses = {"85","90","95","100","125","150","200","250","300","400","500","600","700","800","900","1000","1100","1200","1300","1500","1700","2000"};
    vector<TString> VBFMasses = {"500","600","700","800","900","1000","1100","1200","1300","1500","1700","2000"};
    
    
    //vector<TString> Signals = {"SSWWTypeI_NLO_SF_M","DYTypeI_NLO_SF_M","VBFTypeI_NLO_SF_M"};
    vector<TString> Signals = {"VBFTypeI_NLO_SF_M"};
    
    for (auto isig: Signals) {
      vector<TString> masses;
      if(isig == "SSWWTypeI_NLO_SF_M") masses=SSMasses;
      if(isig == "DYTypeI_NLO_SF_M")masses=DYMasses;
      if(isig == "VBFTypeI_NLO_SF_M")masses=VBFMasses;
      
      for(auto im : masses){
	
	TString mc_path = ENV_FILE_PATH+ "/"+analysername+"/"+year+"/HNL_Signal_"+isig+im+".root";
	
	TFile * file_mc = new TFile((mc_path).Data());

	if(CheckFile(file_mc) > 0) {
	  cout << isig << " mass = " << im << " missing" << endl;
	  signals_missing.push_back(year+"_HNL_Signal_"+isig+im+".root");
	  continue;
	}
	signals_available.push_back(year+"_HNL_Signal_"+isig+im+".root");
	
	
	TString _dir="Inclusive_SSMuMu";
	if (!isig.Contains("SS")) _dir="Inclusive_MuMu_SS";
	// canvas for hists
	vector<TString> vars = GetListFromKeys(file_mc,_dir,"TH1D");
	
	
	for (auto var: vars){

	  TString canvasname= var;
	  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	  //c1->SetLogy();
	  
	  TString s_var = _dir+"/"+var;
	  
	  // Get TH1 for each type

	  vector<double> newrbins;
	  Double_t array_newrbins[newrbins.size()];
	  
	  TH1* hn_sig        = GetHistFull(newrbins, file_mc,s_var, kRed, 3.);
	  
	  c1->cd();
	  
	  NormHist(hn_sig);
	  hn_sig->Draw("hist");
	  TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
	  legend->AddEntry(hn_sig,isig+im,"l");
	  legend->Draw();
	  
	  setTDRStyle();
	  
	  TString save_sg= output + "/"+var+ "_"+year+isig+im+".pdf";
	  
	  c1->SaveAs(save_sg);
	  
	  delete c1;
	
	}	
	file_mc->Close();
	
	delete file_mc;
	
      }
    }
  }

  cout << "List of signals at tamsa " << endl;
  for(auto is_av : signals_available) cout << is_av << endl;
  cout << " " << endl;
  cout << "List of missing signals at tamsa " << endl;

  for(auto is_miss : signals_missing)  cout << is_miss << endl;
  return;
}

