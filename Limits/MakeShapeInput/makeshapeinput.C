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
  vector<TString> Channels={"MuMu"};
  vector<TString> Card={""};
  vector<TString> Charge={""};
//same_sign","opposite_sign"};

  vector<TString> muIDs={"HNTightV1","HNTightV2","POGTightWithTightIso"};
  vector<TString> elIDs={"HNTight2016","passTightID_nocc","passMVAID_iso_WP80","passMVAID_iso_WP90","passMediumID","passTightID"};


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
	      if (_bin == "SR3")   { bin = "SR1"; charge = "opposite_sign";}
	      if (_bin == "SR4")   { bin = "SR2"; charge = "opposite_sign";}
	      
	      //cout << "Running year 
	        vector<pair<TString, TString> > samples;
		if(charge=="same_sign"){
		  samples.push_back(make_pair("cf","CF"));
		  samples.push_back(make_pair("fake","Fake"+channel));
		  samples.push_back(make_pair("prompt","SSPrompt"));
		  samples.push_back(make_pair("data_obs","SS"));
		}
		else {
		  samples.push_back(make_pair("fake","FakeOS"));
		  samples.push_back(make_pair("prompt","OSPrompt"));
		  samples.push_back(make_pair("cf","OSCF"));
                  samples.push_back(make_pair("data_obs","OSPrompt"));
		}
		
		for(const auto& mass: masses) {
		
		  TString outfile = ENV_PLOT_PATH+ FLATVERSION+"/Limit/";
		  MakeDir(outfile);
		  outfile+="Shape/";	      MakeDir(outfile);
		  outfile+=year+"/";	      MakeDir(outfile);
		  outfile+=channel+"_"+_bin+"/";	      MakeDir(outfile);
		  
		  

                  if (_bin == "SR2") var = var.ReplaceAll("jj","J");
                  if (_bin == "SR4") var = var.ReplaceAll("jj","J");

		  outfile+= "HN"+mass+"_highmass_"+FLATVERSION+"_"+year+"_"+_bin+"_"+channel+"_"+card+"_"+id+"_"+var+".root";
		  cout << "Creating file " << outfile << endl;
		  TFile* fout = new TFile(outfile.Data(),"RECREATE");
		
		  TString input_hist=bin+"_"+channel+"_highmass_"+charge+"/"+bin+"_"+channel+"_highmass_"+charge+"_"+var+"_HNtypeI_JA_"+channel+"_"+id+"_";
		  
		  cout << outfile  << " ----  writing " << endl;
		  TString signalpath= ENV_MERGEDFILE_PATH + "/2016/SIG/HNtypeI_JA_HN_Schannel_" + channel + "_"+mass + "_nlo.root";
		    
		  WriteToFile(mass, year, signalpath, fout, ENV_MERGEDFILE_PATH+ "/"+year+"/"+analysername+"_SkimTree_SSNonIso_", samples,input_hist,systs );
		  
		  
		  cout <<"             ----  written " << endl;

		  fout->Close();
		  delete fout;
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

