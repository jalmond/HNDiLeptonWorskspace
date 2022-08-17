#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void makeshapeinputSS(int k, TString analysername="HNL_SignalRegionPlotter"){

  TString var1 = "N1Mass_Central";
  TString var2 = "HT_LT1_Central";
  TString var3 = "SignalBins";
  if(k==1){

   var1 = "Q_N1Mass_Central";
   var2 = "Q_HT_LT1_Central";
   var3 = "SignalBinsQ";
  }


  // check which pc is running script to setup local paths                                                                                                                   
  TString s_hostname = GetHostname();

  
  // local path names                                                                                                                                                        
  TString ENV_FILE_PATH= getenv("INFILE_PATH");
  TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");//FILE_MERGED_PATH
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



  vector<TString>  Years = {"2016" ,"2017","2018"};
  vector<TString> Bins={"SR1","SR2","SR3"};
  vector<TString> Flavours={"MuMu","EE"};
  vector<TString> Channels={"Combinedchannel"};
  vector<TString> ChannelTags={"_VBF"};

  vector<TString> IDs={"HNL_UL"};


  for(const auto& year: Years) {
    for(const auto& _bin: Bins) {
      for(const auto& flavour: Flavours) {
	for(const auto& channel: Channels) {
	  vector<TString> systs;
	  if (flavour == "MuMu") systs= {""};//,"JERDown","JERUp","JESUp","JESDown","MUIDDown","MUIDUp"};
	  else  systs= {""};//,"ELIDDown","ELIDUp","JERDown","JERUp","JERUp","JERDown"};


	  for(const auto& id: IDs) {
	    
	    TString bin = _bin;

	    ignore_masses = {""};
	    vector <TString> masses = GetMassType1Strings(ignore_masses,channel);
	    vector <double> d_masses = GetMassType1Doubles(ignore_masses,channel);
	    
	    if(masses.size() != d_masses.size() ){ cout << "ERROR" << endl; return;}
	    int mass_counter=-1;
	    for(const auto& mass: masses) {
	      bool t_channel=false;
	      bool s_channel=false;
	      bool ssww = false;
	      mass_counter+=1;
	      cout << "Mass = " << mass << endl;
	      double mass_d=d_masses[mass_counter];
	      TString outfile = getenv("DATACARD_SHAPE_PATH");
	      MakeDir(outfile);
	      outfile+= analysername+"/";  MakeDir(outfile);
	      outfile+=year+"/";	      MakeDir(outfile);
	      outfile+=flavour+"_"+_bin+"/";	      MakeDir(outfile);
	      
	      /// since var is a glaboal vairable need to copy so jet string can be replaced
	      TString _var = _bin;

	      TString signal_tag = "_DY";
	      
	      if(channel == "Tchannel") signal_tag = "_VBFOnly";
	      if(channel == "Combinedchannel") signal_tag = "_CombinedSig";
	      
	      
	      outfile+= "HN_"+channel+"_"+mass+"_highmass_"+FLATVERSION+"_"+year+"_"+_bin+"_" +flavour+"_"+id+"_"+_var+".root";
	      
	      cout << "Creating file " << outfile << endl;

	      TFile* fout = new TFile(outfile.Data(),"RECREATE");
	      //SR1_highmass_reco_finebin_ml1jj_HNtypeI_Dilepton_EE_HNTight2016_
	      
	      TString input_hist="";
	      if (_bin == "SR1") input_hist = "LimitSR1/"+flavour+"/"+id+"/"+var1;
	      if (_bin == "SR2") input_hist = "LimitSR2/"+flavour+"/"+id+"/"+var2;
	      if (_bin == "SR3") input_hist = "LimitSR3/"+flavour+"/"+id+"/"+var3;

	      TString signalpath_s= ENV_MERGEDFILE_PATH + "/"+analysername+"/"+year+"/SIG/"+analysername+"_DYTypeI_DF_M"+mass + "_private.root";
	      TString signalpath_t= ENV_MERGEDFILE_PATH + "/"+analysername+"/"+year+"/SIG/"+analysername+"_VBFTypeI_DF_M"+mass + "_private.root";
	      TString signalpath_ssww= ENV_MERGEDFILE_PATH + "/"+analysername+"/"+year+"/SIG/"+analysername+"_SSWWTypeI_M"+mass + "_private.root";
	      	      
	      
	      //WriteToFile(mass, year, signalpath, fout, ENV_MERGEDFILE_PATH+ "/HNtypeI_JA/"+year+"/"+analysername+"_SkimTree_SSNonIso_", samples,input_hist,systs );
	      
	      TString h_path_prompt =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SS2lOR3l_SSPrompt.root";
	      TString h_path_cf =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_Dilepton_CF.root";
	      //TString h_path_data =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_SS.root";
	      TString h_path_fake =  ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_HNMultiLep_NonPrompt_"+flavour+".root";
	      
	      TFile * file_fake = new TFile((h_path_fake).Data());
	      TFile * file_prompt = new TFile((h_path_prompt).Data());
	      //TFile * file_data = new TFile((h_path_data).Data());
	      
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
	      
	      fout->cd();
	      h_data->SetName("data_obs");
	      h_data->Write();
	      
	      
	      TFile * file_sig_s; 
	      TFile * file_sig_t; 
	      TFile * file_sig_ssww;

	      TH1* h_sig1 = (TH1*)h_prompt->Clone("SIG1_"+input_hist);//GetHist(file_data,input_hist);                                                                                                                                                             
	      TH1* h_sig2 = (TH1*)h_prompt->Clone("SIG2_"+input_hist);//GetHist(file_data,input_hist);                                                                                                                                                             
              for(int ibin=0; ibin < h_sig1->GetNbinsX()+1; ibin++){
                h_sig1->SetBinContent(ibin,0);
                h_sig2->SetBinContent(ibin,0);
              }

	      if(channel == "Schannel"){
		if(IsDYMass(mass)){
		  file_sig_s = new TFile((signalpath_s).Data());
		  if(GetHist(file_sig_s,input_hist))  h_sig1 = GetHist(file_sig_s,input_hist);
		  s_channel=true;
		}
	      }
	      else if(channel =="Tchannel"){
		if(IsVBFMass(mass)){
		  file_sig_t = new TFile((signalpath_t).Data());
		  if(GetHist(file_sig_t,input_hist)) h_sig1 = GetHist(file_sig_t,input_hist);
		  t_channel=true;
		}
	      }
	      else {
		if(IsDYMass(mass)){
		  file_sig_s = new TFile((signalpath_s).Data());		
		  if(GetHist(file_sig_s,input_hist)) h_sig1 = GetHist(file_sig_s,input_hist);
		  s_channel=true;
		  if(IsVBFMass(mass)){
		    file_sig_t = new TFile((signalpath_t).Data());
		    TH1* h_sig_t ;
		    if(GetHist(file_sig_t,input_hist)) {
		      h_sig_t= GetHist(file_sig_t,input_hist);
		      h_sig1->Add(h_sig_t);
		      t_channel=true;
		    }
		  }
		}
		
		if  (IsSSWWMass(mass)){
		  file_sig_ssww = new TFile((signalpath_ssww).Data());
		  if(GetHist(file_sig_ssww,input_hist))h_sig2= GetHist(file_sig_ssww,input_hist);
		}
	      }
	      
	      // scale 
	      double Int1 = h_sig1->Integral();
	      double _scaleSIG1 = SignalScale(h_sig1->Integral());
	      double _scaleSIG2 = SignalScale(h_sig2->Integral());

	      if(h_sig1)h_sig1->Scale(_scaleSIG1);
	      if(h_sig2)h_sig2->Scale(_scaleSIG2);
	      TH1D* h_scale1 = new TH1D("ScaleSigDYVBF","ScaleSigDYVBF", 1, 0., 1.);
	      TH1D* h_scale2 = new TH1D("ScaleSigSSWW","ScaleSigSSWW", 1, 0., 1.);
	      h_scale1->Fill(0.5, _scaleSIG1);
	      h_scale2->Fill(0.5, _scaleSIG2);

	      fout->cd();
      
	      h_scale1->Write();
	      h_scale2->Write();

	      if(h_sig1)cout << "Nsig (DY+VBF) = " << h_sig1->Integral()<< " ";
	      if(h_sig2) cout << "Nsig (SSSWW) = " << h_sig2->Integral()<< " ";
	      cout << "promptN = " << h_prompt->Integral()<< " ";
	      cout << "NFake= " << h_fake->Integral()<< " ";
	      cout << "NDATA = " << h_data->Integral()<< endl;;
	      fout->cd();
	      if(h_sig1)h_sig1->SetName("signalDYVBF");
	      if(h_sig2)h_sig2->SetName("signalSSWW");
	      fout->cd();

	      if(h_sig1)h_sig1->Write();
	      if(h_sig2)h_sig2->Write();
	      file_fake->Close();
	      file_prompt->Close();
	      if(channel == "Schannel"){
		if(s_channel){
		  file_sig_s->Close();
		  delete file_sig_s;
		}
	      }
	      else  if(channel == "Tchannel"){
		if(t_channel){
		  file_sig_t->Close();
		  delete file_sig_t;
		}
	      }
	      else{
		if(s_channel){
		  file_sig_s->Close();
		  delete file_sig_s;
		}
		if(t_channel){
		  file_sig_t->Close();
		  delete file_sig_t;
		}
		if(ssww){
		  
		  file_sig_ssww->Close();
		  delete file_sig_ssww;
		  
		}
	      }
	      //file_data->Close();
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

