#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void makeshapeinput(int k=0){

  TString var = "";
  if (k == 0) var = "reco_ml1jj";
  if (k == 1) var = "reco_ml2jj";
  if (k == 2) var = "reco_mlljj";
  if (k == 3) var = "signalbin";
  if (k == 4) var = "reco_finebin_ml1jj";
  if (k == 5) var = "reco_finebin_ml2jj";
  if (k == 6) var = "reco_finebin_mlljj";

  // check which pc is running script to setup local paths                                                                                                                   
  TString s_hostname = GetHostname();

  
  // local path names                                                                                                                                                        
  TString ENV_FILE_PATH= getenv("INFILE_PATH");
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  TString analysername="HNtypeI_JA";

  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";


  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
     input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }
   
  // Set Plotting style                                                                                                                                                      
  setTDRStyle();
  gStyle->SetPalette(1);
  
  vector<TString> ignore_masses = {"100","125","150","200","250","300"};
  //  if (_chan=="Schannel") 
  ignore_masses = {"300"};
  vector <TString> masses = GetMassType1Strings(ignore_masses);
  vector <double> d_masses = GetMassType1Doubles(ignore_masses);

  vector<TString>  Years = {"2016","2017","2018"};
  vector<TString> Bins={"SR1","SR2"};//,"SR3","SR4"};
  vector<TString> Channels={"MuMu","EE"};
  vector<TString> Card={""};
  vector<TString> Charge={""};
//same_sign","opposite_sign"};

  //vector<TString> muIDs={"HNTight2016","POGTightPFIsoVeryTight");
  vector<TString> muIDs={"POGTightPFIsoVeryTight"};

  //vector<TString> elIDs={"HNTight2016","passTightID_nocc","passTightID_noccb","passMVAID_iso_WP80","passMVAID_iso_WP90","passMediumID","passTightID"};
  vector<TString> elIDs={""};

  for(const auto& year: Years) {
    for(const auto& _bin: Bins) {
      for(const auto& channel: Channels) {
	vector<TString> IDs = (channel == "MuMu") ? muIDs: elIDs; 
	vector<TString> systs;
	if (channel == "MuMu") systs= {""};//,"JERDown","JERUp","JESUp","JESDown","MUIDDown","MUIDUp"};
	else  systs= {""};//,"ELIDDown","ELIDUp","JERDown","JERUp","JERUp","JERDown"};
	for(const auto& id: IDs) {
	  for(const auto& card: Card) {
	    for(const auto& _charge: Charge) {
	      TString charge = "same_sign";
	      TString bin = _bin;
	      //if (_bin == "SR3")   { bin = "SR1"; charge = "opposite_sign";}
	      //if (_bin == "SR4")   { bin = "SR2"; charge = "opposite_sign";}
	      
	      //cout << "Running year 
	        vector<pair<TString, TString> > samples;
		if(charge=="same_sign"){
		  if(channel=="EE")samples.push_back(make_pair("cf","CF"));
		  samples.push_back(make_pair("fake","Fake"+channel));
		  samples.push_back(make_pair("prompt","SSPrompt"));
		  samples.push_back(make_pair("data_obs","SS"));
		}
		else {
		  samples.push_back(make_pair("fake","Fake"+channel));
		  samples.push_back(make_pair("prompt","OSPrompt"));
		  if(channel=="EE")samples.push_back(make_pair("cf","CF"));
                  samples.push_back(make_pair("data_obs","OSPrompt"));
		}
		
		for(const auto& mass: masses) {
		
		  TString outfile = ENV_PLOT_PATH+ FLATVERSION+"/Limit/";
		  MakeDir(outfile);
		  outfile+="Shape/";	      MakeDir(outfile);
		  outfile+=year+"/";	      MakeDir(outfile);
		  outfile+=channel+"_"+_bin+"/";	      MakeDir(outfile);
		  
		  
		  TString _var =var;
                  if (_bin == "SR2") _var = _var.ReplaceAll("jj","J");
                  //if (_bin == "SR4") var = var.ReplaceAll("jj","J");

		  
		  outfile+= "HN"+mass+"_highmass_"+FLATVERSION+"_"+year+"_"+_bin+"_"+channel+"_"+id+"_"+_var+".root";
		  cout << "Creating file " << outfile << endl;
		  TFile* fout = new TFile(outfile.Data(),"RECREATE");
		  //SR1_highmass_reco_finebin_ml1jj_HNtypeI_Dilepton_EE_HNTight2016_
		  TString input_hist=bin+"_highmass/"+bin+"_highmass_"+_var+"_HNtypeI_JA_"+channel+"_"+id+"_";
		  
		  TString signalpath= ENV_MERGEDFILE_PATH + "/HNtypeI_JA/2016/SIG/HNtypeI_JA_HN_Schannel_" + channel + "_"+mass + "_nlo.root";
		  

		  //WriteToFile(mass, year, signalpath, fout, ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_", samples,input_hist,systs );

		  TString h_path_prompt =  ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_SSPrompt.root";
		  TString h_path_cf =  ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_CF.root";
		  TString h_path_data =  ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_SS.root";
		  TString h_path_fake =  ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_Fake"+channel+".root";

		  if(channel == "EE"){
		    TFile * file_cf = new TFile((h_path_cf).Data());
		    TH1* h_cf = GetHist(file_cf,input_hist);
		    h_cf->SetName("cf");
		    fout->cd();
		    h_cf->Write();
		    cout << "NCF = " << h_cf->Integral()<< endl;;
		    file_cf->Close();
		  }
		  TFile * file_fake = new TFile((h_path_fake).Data());
		  TFile * file_prompt = new TFile((h_path_prompt).Data());
		  TFile * file_data = new TFile((h_path_data).Data());
		  

		  fout->cd();
		  TH1* h_fake  = GetHist(file_fake,input_hist);
		  h_fake->SetName("fake");
		  h_fake->Write();
		  TH1* h_prompt = GetHist(file_prompt, input_hist);
		  h_prompt->SetName("prompt");
                  h_prompt->Write();
		  TH1* h_data = GetHist(file_data,input_hist);
		  int _int = int(h_data->Integral());
		  h_data->Scale(_int/h_data->Integral());
		  h_data->SetName("data_obs");
		  h_data->Write();
		  TFile * file_sig = new TFile((signalpath).Data());

		  TH1* h_sig = GetHist(file_sig,input_hist);
		  double _scale= SignalScale(year,mass);

		  h_sig->Scale(_scale);
		  cout << "Nsig = " << h_sig->Integral()<< endl;;
		  cout << "promptN = " << h_prompt->Integral()<< endl;;
		  cout << "NFake= " << h_fake->Integral()<< endl;;

		  cout << "NDATA = " << h_data->Integral()<< endl;;
		  fout->cd();
		  h_sig->SetName("signal");
		  h_sig->Write();
		  file_fake->Close();
		  file_prompt->Close();
		  file_sig->Close();

		  file_data->Close();
		  fout->Close();
		  delete fout;

		  system("cp " + outfile + " /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Plots/Run2Legacy_v4/Limit/Shape/Workspace/");
		  cout << "cp " + outfile + " /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Plots/Run2Legacy_v4/Limit/Shape/Workspace/" << endl;
			
		  cout <<" closed file"<< endl;
		}
		cout << "End of Mass loop";
	    }
	    cout << "End of charge loop";
	  }
	  cout << "End of card loop";
	}
	cout << "End of ID loop";
      }
      cout << "End of channel "  ;
    }
    cout << "End of bins"  ;
  }
  cout << "End of years" << endl;
  return;
}

