#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void makeshapeinputSS(int k=0,TString analysername="HNtypeI_JA"){

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


  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";


  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
     input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }
   
  // Set Plotting style                                                                                                                                                      
  setTDRStyle();
  gStyle->SetPalette(1);
  
  vector<TString> ignore_masses = {"-100"};



  vector<TString>  Years = {"2016","2017","2018"};
  vector<TString> Bins={"SR1","SR2"};
  vector<TString> Flavours={"MuMu","EE"};
  vector<TString> Channels={"Combinedchannel"};
  vector<TString> ChannelTags={"_VBF"};

  vector<TString> muIDs={"POGTightPFIsoVeryVeryTight","POGTightPFIsoVeryTight","HNTight2016","HNTightV1","POGTightPFIsoTight","POGTightPFIsoMedium","POGTightPFIsoLoose","POGHighPtTight","POGHighPtMixTight"};
  vector<TString> elIDs={"passTightID","passMediumID", "HNTightV1", "HNTight2016","passTightID_noccb","passTightID_nocc","passMVAID_iso_WP90","passMVAID_iso_WP80"};


  for(const auto& year: Years) {
    for(const auto& _bin: Bins) {
      for(const auto& flavour: Flavours) {
	for(const auto& channel: Channels) {
	  vector<TString> IDs = (flavour == "MuMu") ? muIDs: elIDs; 
	  vector<TString> systs;
	  if (flavour == "MuMu") systs= {""};//,"JERDown","JERUp","JESUp","JESDown","MUIDDown","MUIDUp"};
	  else  systs= {""};//,"ELIDDown","ELIDUp","JERDown","JERUp","JERUp","JERDown"};
	  for(const auto& id: IDs) {
	    
	    TString bin = _bin;
	    TString charge="same_sign";
	    if(bin=="SR3" || bin == "SR4") charge = "opposite_sign";
	    vector<pair<TString, TString> > samples;
	    if(charge=="same_sign"){
	      if(flavour=="EE")samples.push_back(make_pair("cf","CF"));
	      samples.push_back(make_pair("fake", "Fake"+flavour));
	      samples.push_back(make_pair("prompt","SSPrompt"));
	      samples.push_back(make_pair("data_obs","SS"));
	    }
	    else {
	      samples.push_back(make_pair("fake","FakeOS")); // TTLJ_powheg", "WJets_MG","SingleTop"
	      samples.push_back(make_pair("prompt","OSPrompt")); 
	      if(flavour=="EE")samples.push_back(make_pair("cf","OSCF"));
	      samples.push_back(make_pair("data_obs","OSPrompt"));
	    }
	    
	    ignore_masses = {""};
	    vector <TString> masses = GetMassType1Strings(ignore_masses,channel);
	    vector <double> d_masses = GetMassType1Doubles(ignore_masses,channel);
	    
	    if(masses.size() != d_masses.size() ){ cout << "ERROR" << endl; return;}
	    int mass_counter=-1;
	    for(const auto& mass: masses) {
	      bool t_channel=false;
	      mass_counter+=1;
	      double mass_d=d_masses[mass_counter];
	      TString outfile = getenv("DATACARD_SHAPE_PATH");
	      MakeDir(outfile);
	      outfile+= analysername+"/";  MakeDir(outfile);
	      outfile+=year+"/";	      MakeDir(outfile);
	      outfile+=flavour+"_"+_bin+"/";	      MakeDir(outfile);
	      
	      /// since var is a glaboal variable need to copy so jet string can be replaced
	      TString _var =var;
	      if (_bin == "SR2") _var = _var.ReplaceAll("jj","J");
	      if (_bin == "SR4") _var = _var.ReplaceAll("jj","J");
	      
	      TString channel_tag = "_DY";

	      if(channel == "Tchannel") channel_tag = "_VBFOnly";
	      if(channel == "Combinedchannel") channel_tag = "_VBF";
	      
	      outfile+= "HN_"+channel+"_"+mass+"_highmass_"+FLATVERSION+"_"+year+"_"+_bin+"_" +flavour+"_"+id+"_"+_var+".root";

	      cout << "Creating file " << outfile << endl;
	      TFile* fout = new TFile(outfile.Data(),"RECREATE");
	      //SR1_highmass_reco_finebin_ml1jj_HNtypeI_Dilepton_EE_HNTight2016_
	      
	      TString input_hist=bin+"_highmass/"+bin+"_highmass_"+_var+"_"+analysername+"_"+flavour+"_"+id+"_";
	      TString signalpath_s= ENV_MERGEDFILE_PATH + "/"+analysername+"/"+year+"/SIG/"+analysername+"_HN_Schannel_" + flavour + "_"+mass + "_nlo.root";
	      TString signalpath_t= ENV_MERGEDFILE_PATH + "/"+analysername+"/"+year+"/SIG/"+analysername+"_HN_Tchannel_" + flavour + "_"+mass + "_nlo.root";
	      
	      
	      //WriteToFile(mass, year, signalpath, fout, ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_", samples,input_hist,systs );
	      
	      TString h_path_prompt =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_SSPrompt.root";
	      if (_bin == "SR3" || _bin == "SR4")  h_path_prompt =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_OSPrompt.root";
	      TString h_path_cf =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_CF.root";
	      if (_bin == "SR3" || _bin == "SR4")h_path_cf =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_OSCF.root";

	      TString h_path_data =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_SS.root";
	      TString h_path_fake =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_Fake"+flavour+".root";
	      if (_bin == "SR3" || _bin == "SR4") h_path_fake =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_FakeOS.root";

						    
              TFile * file_fake = new TFile((h_path_fake).Data());
              TFile * file_prompt = new TFile((h_path_prompt).Data());
              TFile * file_data = new TFile((h_path_data).Data());
	      
	      fout->cd();

	      vector <double > binvalues;
              TH1* h_fake  = GetHist(file_fake,input_hist);
              if(h_fake){
                h_fake->SetName("fake");
		fout->cd();
                h_fake->Write();
		for(int ibin=0; ibin < h_fake->GetNbinsX()+1;ibin++){
		  binvalues.push_back(0.);
		}
		for(int ibin=0; ibin < h_fake->GetNbinsX()+1;ibin++){
		  binvalues[ibin] = binvalues[ibin] + h_fake->GetBinContent(ibin);
                }
              }
	      TH1* h_prompt = GetHist(file_prompt, input_hist);
	      //if(h_prompt)h_prompt->Scale(0.8);
              if(h_prompt){
		if(binvalues.size()==0){
		  for(int ibin=0; ibin < h_prompt->GetNbinsX()+1;ibin++){
		    binvalues.push_back(0.);
		  }
		}
		for(int ibin=0; ibin < h_prompt->GetNbinsX()+1;ibin++){
                  binvalues[ibin] = binvalues[ibin] + h_prompt->GetBinContent(ibin);
                }

                h_prompt->SetName("prompt");
		fout->cd();

                h_prompt->Write();
              }
	      
	      if(flavour == "EE"){
		TFile * file_cf = new TFile((h_path_cf).Data());
		if(CheckHist(file_cf,input_hist)){
		  TH1* h_cf = GetHist(file_cf,input_hist);
		  for(int ibin=0; ibin < h_cf->GetNbinsX()+1;ibin++){
		    binvalues[ibin] = binvalues[ibin] + h_cf->GetBinContent(ibin);
		  }
		  
		  fout->cd();
		  h_cf->SetName("cf");
		  h_cf->Write();
		  
		  cout << "NCF = " << h_cf->Integral()<< " " ;
		  file_cf->Close();
		}
	      }


	      //TH1* h_data =GetHist(file_data,input_hist);                          
	      TH1* h_data = (TH1*)h_prompt->Clone("data_"+input_hist);//GetHist(file_data,input_hist);
	      for(int ibin=0; ibin < h_prompt->GetNbinsX()+1; ibin++){
		int i_bincontent = (int)binvalues[ibin];
		h_data->SetBinContent(ibin,i_bincontent);
	      }
	      
	      h_data->SetName("data_obs");
	      h_data->Write();
	

	      TFile * file_sig_s; 
	      TFile * file_sig_t; 
      
	      TH1* h_sig;

	      if(channel == "Schannel"){
		file_sig_s = new TFile((signalpath_s).Data());

		h_sig = GetHist(file_sig_s,input_hist);
	      }
	      else if(channel =="Tchannel"){
		file_sig_t = new TFile((signalpath_t).Data());
		h_sig = GetHist(file_sig_t,input_hist);
		t_channel=true;


	      }
	      else {
		file_sig_s = new TFile((signalpath_s).Data());		
		h_sig = GetHist(file_sig_s,input_hist);
		if(mass_d > 250.){
		  file_sig_t = new TFile((signalpath_t).Data());
		  TH1* h_sig_t = GetHist(file_sig_t,input_hist);
		  h_sig->Add(h_sig_t);
		  t_channel=true;
		}
	      }
	      
	      // scale 
	      double _scale= SignalScale(year,mass);
	      cout << h_sig->Integral();

	      h_sig->Scale(_scale);
	      cout << "sclaed " << h_sig->Integral();
	      
	      
	      cout << "Nsig = " << h_sig->Integral()<< " ";
	      cout << "promptN = " << h_prompt->Integral()<< " ";
	      cout << "NFake= " << h_fake->Integral()<< " ";
	      cout << "NDATA = " << h_data->Integral()<< endl;;
	      fout->cd();
	      h_sig->SetName("signal");
	      h_sig->Write();
	      file_fake->Close();
	      file_prompt->Close();
	      if(channel == "Schannel"){
		file_sig_s->Close();
		delete file_sig_s;
	      }
	      else  if(channel == "Tchannel"){
		if(t_channel){
		  file_sig_t->Close();
		  delete file_sig_t;
		}
	      }
	      else{
		file_sig_s->Close();
		delete file_sig_s;
		if(t_channel){
		  file_sig_t->Close();
		  delete file_sig_t;
		}
	      }
	      file_data->Close();
	      fout->Close();
	      delete fout;
	      delete file_fake;
	      delete file_prompt;	
      
	    }
	  }
	}
      }
    }
  }
  return;
}

