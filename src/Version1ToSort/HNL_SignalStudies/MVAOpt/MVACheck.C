#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MVACheck(){
  
  vector<TString> eras =  {"2017"};
  
  for (auto year : eras){
      
    TString skim="";
    // check which pc is running script to setup local paths
    TString s_hostname = GetHostname();
    
    TString analysername="HNL_SignalStudies";
    
    // local path names
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    TString ENV_PLOT_PATH = getenv("PLOT_PATH");
    TString FLATVERSION = getenv("FLATVERSION");
    
    
    MakeDir(ENV_PLOT_PATH + FLATVERSION);
    TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
    TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
    
    MakeDir(output);
    output+="/MVACheck/";
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
      
    
    TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_SkimTree_HNMultiLep_MC.root";
    
    TFile * file_bkg = new TFile((mc_path).Data());
    
    if(CheckFile(file_bkg) > 0) {
      continue;
    }
    
    map<double, vector<double > > map_sig;
    int NBins(0);
    double sig_def=0.;
    vector<double> Vsig;
    for(unsigned int i=0; i < 200; i++){
      double mva_1 = (-1.+0.01*double(i));
      std::string mva1= std::to_string(mva_1);
      
      TString label = "HNMVA_"+mva1;
      
      
      TString sr_hist= "LooseMVAOpt/SigElectron/"+label+"_endcap";
      TString bkg_hist= "LooseMVAOpt/BkgElectron/"+label+"_endcap";
      TH1* hn_bkg        = GetHist(file_bkg,bkg_hist);
      
      TString sig_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_Sig.root";
      TFile * file_sig = new TFile((sig_path).Data());
      
      if(CheckFile(file_sig) > 0) {
	continue;
      }
      
      TH1* hn_sig        = GetHist(file_sig,sr_hist);
      if (!hn_sig) continue;
      
      vector<double > signif;
      double tot_sig(0);
      for(unsigned int ibin = 1; ibin <  hn_sig->GetNbinsX()+1; ibin++){
	double sig = hn_sig->GetBinContent(ibin);
	//double nbkg = hn_bkg->GetBinContent(ibin);
	//double sign = (sig/sqrt(nbkg)> 0) ? sig/sqrt(nbkg) : 0.;
	signif.push_back(sig);
      }	
      if (i==0) sig_def = tot_sig;
      if(i==0) NBins = hn_sig->GetNbinsX();
      if(i==0) Vsig = signif;
      //cout << mva_1 << " sig = " << tot_sig << endl;
      map_sig [mva_1] = signif;
    }
   
    for(unsigned int ibin = 1; ibin < NBins+1; ibin++){
      
      for(map<double, vector<double> >::iterator mit = map_sig.begin(); mit != map_sig.end(); mit++){
	if(Vsig[ibin] > 0)cout << "Bin " << ibin << " MVA " <<  mit->first << " " << mit->second[ibin]/Vsig[ibin]<< endl;
	
      }
      
    }
    
  }
    

  return;
}

