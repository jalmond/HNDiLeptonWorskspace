#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MakeLatexFile(TString latex_file, TString latex_path,
		   vector<pair<TString, vector<pair< TString, double> > > >  siglist,
		   vector<pair<TString, vector<pair< TString, double> > > >  bkglist);

void GetSignalOverB_combinedSR(TString _chan = "Schannel"){ 

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();


  // local path names
  TString ENV_FILE_PATH= getenv("INFILE_PATH");

  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  TString analysername="HNtypeI_JA";
  TString analyzer=analysername;
  ENV_FILE_PATH = ENV_FILE_PATH +"/"+analyzer;
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  MakeDir(ENV_PLOT_PATH + FLATVERSION+"/SignalOverB");
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    

  
  // list all masses even tho not all signals are made currently

  vector<TString> ignore_masses = {"100","125","150","200","250","300"};
  if (_chan=="Schannel") ignore_masses = {"300"};
  vector <TString> masses = GetMassType1Strings(ignore_masses);
  vector <double> d_masses = GetMassType1Doubles(ignore_masses);
  
  vector<pair< TString, pair<TString, TString>  > > SR;
  SR.push_back(make_pair("SS", make_pair("SR1","SR2")));
  //SR.push_back(make_pair("OS", make_pair("SR3","SR4")));


  
  vector <TString> channel;
  channel.push_back("MuMu");
  channel.push_back("EE");

  vector<TString> muIDs;
  muIDs.push_back("POGTightPFIsoLoose");
  muIDs.push_back("POGTightPFIsoMedium");
  muIDs.push_back("POGTightPFIsoTight");
  muIDs.push_back("POGTightPFIsoVeryTight");
  muIDs.push_back("HNTightV1");
  muIDs.push_back("HNTight2016");
  
  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("passTightID_noccb");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");

  vector<TString> Years = {"2016","2017","2018"};

  TString outfile = ENV_PLOT_PATH+ FLATVERSION+"/"+"HNEfficiencies_highmass_"+FLATVERSION+"_"+_chan+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");

  // loop over SR1/2/3/4
  for(unsigned int y = 0 ; y < Years.size(); y++){
    
    for(unsigned int j = 0 ; j < SR.size(); ++j){
      
      // run over EE/MM plus charge seperation
      for(unsigned int k = 0 ; k < channel.size(); ++k){
	
	vector<TString> IDs;
	// get efficiencies for each ID ran based on channel
	if ( channel[k].Contains("E") ) IDs = elIDs;
	else IDs =   muIDs;
	
	TString sr = SR[j].first;
	TString _channel = channel[k];
	
	// hist leg
	TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
	// graph leg

	
	// canvas for hists
	TString canvasname=Years[y]+ sr+"_"+_channel +"_highmass_njets_"+analysername+"_JA_"+_channel;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	for(unsigned int _sr =0; _sr <2; _sr++){
	  
	  TString _sr_s = SR[j].second.first;
	  if (_sr == 1) _sr_s = SR[j].second.second;
	  vector<Color_t> histcolors = GetHistColors(IDs.size());
	  vector<TGraphAsymmErrors*> _vgraphs;
	  

	  vector<pair<TString, vector<pair< TString, double> > > >  siglist;
	  vector<pair<TString, vector<pair< TString, double> > > >  bkglist;

	  for(unsigned int l = 0 ; l < IDs.size(); l++){
	    
	    TString _id = IDs[l];
	    
	    /// get bkg numbers
	    
	    // setup hist                                                                                                                                                                
	    TString histlabel= _sr_s+"_"+_channel +  +"_highmass_HNtypeI_JA_"+_id;
	    TH1D* this_hist = new TH1D( histlabel+Years[y] , histlabel, masses.size(), 0, masses.size());
	    SetBinLabels(this_hist, masses);
	    
	    // setup graph                                                                                                                                                               
	    int _Nbins = d_masses.size();
	    vector<double> _x, _y, _xlow, _xup, _ylow, _yup;
	    
	    
	    TString n_sr_hist = _sr_s + "_highmass/"+_sr_s+"_highmass_njets_HNtypeI_JA_"+_channel+"_" + _id +"_";
	    
	    /*TString promptpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root";
	    TString fakepath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_Fake"+_channel+".root";
	    TString cfpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_CF.root";
	    double total_b = GetIntegral(promptpath, n_sr_hist);
	    total_b += GetIntegral(fakepath, n_sr_hist);
	    total_b += GetIntegral(cfpath, n_sr_hist);
	    
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " prompt = " << GetIntegral(promptpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " cf     = " << GetIntegral(cfpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " fake   = " << GetIntegral(fakepath, n_sr_hist) << endl;

	    */
	    vector<pair< TString, double> > siglist_id;
	    vector<pair< TString, double> > bkglist_id;
	

	    TString VVpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_Diboson.root";
	    TString Tribosonpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_VVV.root";
	    TString WWpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_WWpp.root";
	    TString XGpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_XG.root";
	    TString Toppath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_top.root";

	    TString fakepath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_Fake"+_channel+".root";
	    TString cfpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_CF.root";                                                                              
	    
	    double total_b = GetIntegral(VVpath, n_sr_hist);                                                                                                                     
	    total_b += GetIntegral(Tribosonpath ,n_sr_hist);
	    total_b += GetIntegral(WWpath ,n_sr_hist);
	    total_b += GetIntegral(XGpath ,n_sr_hist);
	    total_b += GetIntegral(Toppath ,n_sr_hist);
	    total_b += GetIntegral( fakepath,n_sr_hist);
	    if ( channel[k].Contains("E") )  total_b += GetIntegral(cfpath ,n_sr_hist);

	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " diboson = " << GetIntegral(VVpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " triboson = " << GetIntegral(Tribosonpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " WWpp = " << GetIntegral(WWpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " XG = " << GetIntegral(XGpath, n_sr_hist) << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " top = " << GetIntegral(Toppath, n_sr_hist) << endl;   
	    cout << "------------------" << endl;
	    cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  "Total prompt =" << GetIntegral(VVpath, n_sr_hist) + GetIntegral(Tribosonpath, n_sr_hist)  + GetIntegral(WWpath, n_sr_hist) + GetIntegral(Toppath, n_sr_hist)  + GetIntegral(XGpath, n_sr_hist) << endl;

	    if ( channel[k].Contains("E") ) cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " cf     = " << GetIntegral(cfpath, n_sr_hist) << endl;       
            cout <<  Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id <<  " fake   = " << GetIntegral(fakepath, n_sr_hist) << endl;     


	    // loop over masses and fill s/b
	    for(unsigned int i = 0 ; i < masses.size(); ++i){


	      _x.push_back(d_masses[i]);
	      _xlow.push_back(0);
	      _xup.push_back(0);
	      TString im = masses.at(i);
	      
	      bkglist_id.push_back(make_pair(im, total_b));
	      TString sigpath = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_"+im+"_nlo.root";
	      TFile * filemm = new TFile((sigpath).Data());	  
	      if(CheckFile(filemm) > 0) continue;
	      
	      //SR1_highmass_njets_HNtypeI_JA_EE
	      //	      TString n_all_hist="CutFlow/NoCut_HNtypeI_JA_"+_channel + "_"+ _id;
	      TString n_all_hist="FillEventCutflow/HNtypeI_JA_"+_channel+"_"+ _id+"exo_17_028_dimu_same_sign";
	      if(_channel == "EE") n_all_hist="FillEventCutflow/HNtypeI_JA_"+_channel+"_"+ _id+"exo_17_028_diel_same_sign";

	      TH1* hnsig = GetHist(filemm,n_all_hist);
	      FormatHist(hnsig,false, histcolors[l]);
	      
	      //float nsig = float(hnsig->Integral());
	      float nsig = float(hnsig->GetBinContent(1));
	      // since signal for OS+SS are merged the cutcount is doubled
	      nsig=nsig/2.;
	      
	      TH1*  hpass1 = GetHist(filemm, n_sr_hist);
	      
	      //if(l==0) cout << "--------------------------------------------------------------------------------------- " << endl;
	      cout  << Years[y] << " channel " << _chan << " : "  << _channel << " SR = " << _sr_s << "  ID " << _id << "  Mass = " << masses.at(i) << " Ncounts = " << (hpass1->Integral()) << " / " << nsig << " s/sqrt(b) = " << (( hpass1->Integral()/nsig) / (sqrt(total_b))) << endl;
	      
	      double err ;
	      hpass1->IntegralAndError(1, hpass1->GetNbinsX()+1, err    , "");
	      _y.push_back((hpass1->Integral())/(nsig)/ (sqrt(total_b)) );
	      _ylow.push_back(0);
	      _yup.push_back(0);
	      this_hist->Fill(im, ((hpass1->Integral()/nsig) / (sqrt(total_b)) ));
	      double sigeff=(hpass1->Integral()/nsig);
	      siglist_id.push_back(make_pair(im, (hpass1->Integral()/nsig)));

	      filemm->Close();
	    }// mass loop
	    // add entry for legend for each ID hist
	    siglist.push_back(make_pair(_id, siglist_id));
	    bkglist.push_back(make_pair(_id, bkglist_id));

	    // Create graph
	    TGraphAsymmErrors * gtmp = v_to_graph(_Nbins, _x, _xup, _xlow, _y, _yup, _ylow,histcolors[l]);
	    gtmp->SetLineColor(histcolors[l]);
	    gtmp->SetLineWidth(2.);
	    _vgraphs.push_back(gtmp);
	    AllLegendEntry(legend,this_hist,_id,"l");
	    fout->cd();
	    this_hist->Write();
	    this_hist->GetYaxis()->SetRangeUser(0.01,0.5);
	  } // ID loop
	  
	  // make output dir if needed
	  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalOverB/"+Years[y]);
	  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalOverB/"+Years[y]+ "/"+_sr_s);
	  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalOverB/"+Years[y]+ +"/"+_sr_s+"/"+_channel);

	  
	  TString ENV_FILE_PATH= getenv("HNDILEPTONWORKSPACE_DIR");
	  TString workdir = ENV_FILE_PATH+ "/Latex/workspace/";

	  MakeLatexFile(workdir + _sr + _channel + ".tex",workdir + _sr + _channel + ".txt",siglist, bkglist);
	  cout << "Making   " << workdir + _sr + _channel + ".tex" << "  " << workdir + _sr + _channel + ".txt" << endl;
	  
	  MakeLatex(_sr+_channel,workdir + _sr + _channel + ".txt",ENV_PLOT_PATH+FLATVERSION+"/SignalOverB/"+Years[y]+ "/"+ _sr_s+"/"+_channel +"/" +_sr + _channel + ".pdf");
		    
	


	  legend->Draw();
	  TString save_s=ENV_PLOT_PATH+FLATVERSION+"/"+Years[y]+ +"/"+ _sr_s+"/"+_channel +"/combined_hist_highmass_njets_HNtypeI_JA_"+_channel+"_"+_chan+".pdf";
	  
	  TString canvasname2=Years[y]+ _sr_s+"_highmass2_njets_"+analysername+"_JA_"+_channel;
	  TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
	  c2->cd();
	  
	  TGraphAsymmErrors*  old_gr =Get2016SoverSB(false,Years[y],_sr_s, _channel,d_masses);
	  
	  old_gr->SetLineStyle(10);
	  old_gr->SetLineColor(kRed);
	  old_gr->SetLineWidth(3.);
	  old_gr->SetMarkerColor(kRed);
	  old_gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 0.3);
	  old_gr->Draw("AC*");
	  TLegend *legend_g = MakeLegend(0.65, 0.75, 0.9, 0.92);
	  AllLegendEntry(legend_g,old_gr,"EXO-17-028","pl");
	  
	  for (unsigned int ig = 0 ; ig < _vgraphs.size(); ig++){
	    _vgraphs[ig]->Draw("lp0same");
	    AllLegendEntry(legend_g,_vgraphs[ig],_sr_s+":"+IDs[ig],"lp");
	  }
	  
	  
	  legend_g->Draw();
	  TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/SignalOverB/"+Years[y]+ "_"+ _sr_s+"_"+_channel +"_highmass_soverb_"+analysername+"_"+_channel+"_"+_chan+".pdf";
	  c2->SetLogy();
	  c2->SaveAs(save_sg);
	}
      }
    } // channel 
  } // SR 
  fout->Close();
}

void MakeLatexFile(TString latex_file, TString latex_path,
		   vector<pair<TString, vector<pair< TString, double> > > > siglist,
		   vector<pair<TString, vector<pair< TString, double> > > > bkglist){
  //// Make TEX file                                                        
  ofstream ofile_tex;
  ofile_tex.open(latex_file.Data());
  ofile_tex.setf(ios::fixed,ios::floatfield);
  ofile_tex << "\\documentclass[10pt]{article}" << endl;
  ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl,lscape,pdflscape}" << endl;
  ofile_tex << "\\usepackage{pdflscape}"<<endl;
  ofile_tex << "\\begin{document}" << endl;

  ofile_tex << "\\input{" <<  latex_path  << "}" << endl;
  ofile_tex << "\\end{document}" << endl;
  
  /// Make text file                                                        
  ofstream ofile;
  ofile.open(latex_path.Data());
  ofile.setf(ios::fixed,ios::floatfield);


  ofile.precision(4);
  ofile << "\\begin{table}[h]" << endl;
  //  ofile << "\\begin{center}" << endl;
  TString lates_col = "";
  for (unsigned int isig =0; isig < siglist.size(); isig++)lates_col+="ll";

  ofile << "\\begin{adjustbox}{angle=90} "<< endl;



  ofile << "\\begin{tabular}{lll"<< lates_col.Data()<<"r@{\\hspace{0.5mm}}c@{\\hspace{0.5mm}}c@{\\hspace{0.5mm}}l}" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;

  TString IDs =  "";

  /*  muIDs.push_back("POGTightPFIsoLoose");
  muIDs.push_back("POGTightPFIsoMedium");
  muIDs.push_back("POGTightPFIsoTight");
  muIDs.push_back("HNTight2016");

  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");*/

  vector<TString>  vid;
  vector<TString> nums = {"1","2","3","4","5","6","7","8"};
  for (unsigned int id=0; id < siglist.size(); id++) {
    TString _id = "["+nums[id]+"]";//siglist[id].first;
    TString _id2 =siglist[id].first;
    _id2 = _id2.ReplaceAll("_","\\_");
    vid.push_back(_id2);
    IDs+= _id + " (sig)  &";
    IDs+= _id + " (bkg) &";
  }
  ofile<< "$m_{N}$ GeV & " <<  IDs.Data() <<  "\\"<< "\\" <<  endl;
  ofile << "\\hline" << endl;

  int nmasses = siglist[0].second.size();
  for (unsigned int imass =0; imass < nmasses; imass++){
    ofile <<  siglist[0].second[imass].first << " & "; 
    for (unsigned int isig =0; isig < siglist.size(); isig++){
      ofile <<  siglist[isig].second[imass].second << " & " << bkglist[isig].second[imass].second << " & " ;
    }
    ofile << "\\"<< "\\" <<  endl;
  }
  
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\end{tabular}" << endl;
  ofile << "\\end{adjustbox}" << endl;

  ofile << "\\caption{""}" << endl;
  //ofile << "\\end{center}" << endl;
  ofile << "\\end{table}" << endl;

  for (unsigned int id=0; id < vid.size(); id++) {
    ofile << nums[id] << " =  " << vid[id]  << "\\"<< "\\"<< endl;
  }
  return;
  
  
}
