#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MakeBinnedSignalBkg(TString _chan = "Schannel"){ 

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

  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  // list all masses even tho not all signals are made currently

  vector<TString> ignore_masses = {"100","125","150","200","250","300"};
  if (_chan=="Schannel") ignore_masses = {"125","250","300","500"};
  vector <TString> masses = GetMassType1Strings(ignore_masses);
  vector <double> d_masses = GetMassType1Doubles(ignore_masses);
  
  vector<TString> SR;
  SR.push_back("SR1");
  SR.push_back("SR2");
  //  SR.push_back("SR3");
  //SR.push_back("SR4");
  
  vector <TString> channel;
  channel.push_back("MuMu");
  //channel.push_back("MupMup");
  //channel.push_back("MumMum");
  channel.push_back("EE");
  //channel.push_back("EpEp");
  //channel.push_back("EmEm");

  vector<TString> muIDs;
  muIDs.push_back("HNTightV1");
  muIDs.push_back("HNTightV2");
  muIDs.push_back("POGTightWithTightIso");
  
  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");

  vector<TString>  Years = {"2016"};

  // loop over SR1/2/3/4
  for(unsigned int y = 0 ; y < Years.size(); ++y){
    for(unsigned int j = 0 ; j < SR.size(); ++j){
      
      // run over EE/MM plus charge seperation
      for(unsigned int k = 0 ; k < channel.size(); ++k){
	
	vector<TString> IDs;
	// get efficiencies for each ID ran based on channel
	if ( channel[k].Contains("E") ) IDs = elIDs;
	else IDs =   muIDs;
	
	TString _sr = SR[j];
	TString _channel = channel[k];
	
	TString sign = "same_sign";
	if(_sr == "SR3") { _sr = "SR1"; sign = "opposite_sign";}
	if(_sr == "SR4") { _sr = "SR2"; sign= "opposite_sign"; }
	
	// canvas for hists
	TString canvasname=_sr+"_"+_channel +"_highmass_"+sign +"_njets_"+analysername+"_JA_"+_channel;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	c1->SetLogy();
	vector<Color_t> sighistcolors = GetHistColors(masses.size());
	vector<TGraphAsymmErrors*> _vgraphs;
	
	for(unsigned int l = 0 ; l < IDs.size(); l++){
	  
	  TString _id = IDs[l];
	  
	  // setup hist
	  
	  TString histlabel= _sr+"_"+_channel +  +"_nevent_HNtypeI_JA_"+_channel+"_"+_id;
	  cout << histlabel << endl;

	  TString promptpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root";
	  TString fakepath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_Fake"+_channel+".root";


	  TH1D* this_hist_sig = new TH1D( histlabel+"_prompt" , histlabel, masses.size(), 0, masses.size());
	  TH1D* this_hist_fake = new TH1D( histlabel+"_fake" , histlabel, masses.size(), 0, masses.size());
	  TH1D* this_hist_prompt = new TH1D( histlabel+"_sig" , histlabel, masses.size(), 0, masses.size());

	  // loop over masses 
	  for(unsigned int i = 0 ; i < masses.size(); ++i){
	    
	    TString im = masses.at(i);
	    TString d_im = d_masses.at(i);
	    
	    TString sigpath = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_"+im+"_nlo.root";

	    TFile* filemm = TFile::Open((sigpath).Data());	  
	    if(CheckFile(filemm) > 0) continue;
	    TString n_sr_hist = _sr + "_"+_channel + "_mn"+im + "_"+sign +"/" + _sr + "_"+_channel + "_mn"+im + "_"+sign + "_nevent_HNtypeI_JA_" + _channel + "_"+_id + "_";
	    
	    TH1* hnsig = GetHist(filemm,n_sr_hist);

	    TFile*  file_prompt  = TFile::Open((promptpath).Data());
	    TFile*  file_fake = TFile::Open((fakepath).Data());
	    TH1* hnprompt = GetHist(file_prompt,n_sr_hist);
	    TH1* hnfake = GetHist(file_fake,n_sr_hist);

	    double nsig = double(hnsig->Integral());
	    double nprompt = double(hnprompt->Integral());
	    double nfake = double(hnfake->Integral());

	    double scale = 100.;
	    this_hist_sig->SetBinContent(i+1, scale*nsig);
	    this_hist_sig->SetLineColor(kRed);

	    
	    this_hist_prompt->SetBinContent(i+1, nprompt);
	    this_hist_fake->SetBinContent(i+1, nfake);

	    cout << im<< " " << nfake << " " << nprompt << " " << scale*nsig << endl;
	    this_hist_prompt->SetFillColor(kSpring-1);
            this_hist_prompt->SetLineColor(kSpring-1);
            this_hist_fake->SetFillColor(870);
            this_hist_fake->SetLineColor(870);
	    
	    
	    filemm->Close();
	    file_prompt->Close();
	    file_fake->Close();
	  }

	  THStack *hs = new THStack(_sr+"_"+_channel +"_highmass"+sign +"_nevent_HNtypeI_JA_"+_channel+"_" + _id,"");
	  
	  this_hist_prompt->SetFillColor(kSpring-1);
	  this_hist_fake->SetFillColor(870);

	  hs->Add(this_hist_prompt);
	  hs->Add(this_hist_fake);
	  //	  hs->Add(this_hist_cf);

	    
	  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 900, 800);
	  canvas_margin(c_SOnly);
	  c_SOnly->cd();
	  c_SOnly->Draw();
	  c_SOnly->SetLogy();

	  
	  //TH1D *dummy =  new TH1D("hist", "", masses.size(), 0., masses.size());
          //SetBinLabels(dummy,masses);
	  SetBinLabels(this_hist_sig,masses);                                                                                                                       
	  this_hist_sig->Draw("hist");                                                                                                                            
          this_hist_sig->GetYaxis()->SetTitle("Events / bin " );
	  this_hist_sig->GetXaxis()->SetTitle("Mass bins" );
	  this_hist_sig->GetYaxis()->SetRangeUser(0.05, 10000.);
	  
	  TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/" + Years[y] + "/" + _sr+"/hist_highmass_"+sign +"_nevents_HNtypeI_JA_"+_channel+"_"+_chan+_id+".pdf";
	 
	  hs->Draw("histsame");
	  this_hist_sig->Draw("histsame");
          c_SOnly->SaveAs(save_sg,".pdf");	  


	  this_hist_sig->SetLineColor(kRed);
	  this_hist_sig->GetYaxis()->SetTitle("Events / bin " );
	  this_hist_sig->Draw("hist");
          ///this_hist_sig->SetTitle("Events");
	  //this_hist_sig->SetTitle("Mass("+_hist+") (GeV)");

	  

	  this_hist_sig->SetLineColor(kRed);
	  this_hist_sig->SetLineWidth(4.);
	  this_hist_sig->Draw("histsame");

	  TLegend* legendH;
	  legendH = new TLegend(0.65, 0.75, 0.85, 0.9);
	  legendH->SetFillColor(kWhite);
	  legendH->SetTextSize(0.03);
	  legendH->SetBorderSize(0);
	  legendH->SetTextFont(42);
	  
	  legendH->AddEntry(this_hist_sig, "m_{N} Bin GeV","l");
	  legendH->AddEntry(this_hist_prompt,"Prompt","f");
	  legendH->AddEntry(this_hist_fake,"Fake","f");
	  
	  
	  //AllLegendEntry(legend,this_hist,_id,"l");
	  
	  legendH->Draw();
          cout << "Make stack4" << endl;

	  //dummy->Draw("histsame");
	  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + Years[y]);
	  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + Years[y]+  "/" + _sr);

	  delete hs;
	  delete this_hist_sig;
	  delete this_hist_fake;
	  delete this_hist_prompt;
	  
	  //TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/" + Years[y] + "/" + _sr+"/hist_highmass_"+sign +"_nevents_HNtypeI_JA_"+_channel+"_"+_chan+_id+".pdf";
	  
	  
	  //c_SOnly->SaveAs(save_sg,".pdf");
	  
	  
	}
      }
      
    }
  }
}
