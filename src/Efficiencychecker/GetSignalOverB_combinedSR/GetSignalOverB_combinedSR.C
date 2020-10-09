#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void GetSignalOverB_combinedSR(TString ptbin, TString analysername="HNtypeI_Dilepton" ,  TString year="2016",TString _chan = "Schannel",bool setlog_axis=false, TString x_range="all"){ 

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  
  vector<TString> code_names= {"HNtypeI_Dilepton","HNtypeI_JA"};
  vector<TString> channel_names= {"Schannel","Tchannel"};
  vector<TString> range_names = {"all","low","high"};

  vector<TString> ptbin_names= {"","_HighPt","_LowPt"};
  
  if(std::find(ptbin_names.begin(), ptbin_names.end(), ptbin) != ptbin_names.end()) cout << "Running with ptbin " << ptbin << endl;
  else {cout << "Error in input of ptbin: " << ptbin << endl; for (auto i: ptbin_names)   std::cout << i << ' '; return; }


  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  if(std::find(channel_names.begin(), channel_names.end(), _chan) != channel_names.end()) cout <<	"Running with channel " <<  _chan <<	endl;
  else {cout << "Error in input of _chan: " << _chan << endl;  for (auto i: channel_names)   std::cout << i << ' '; return; }

  
  if(std::find(range_names.begin(), range_names.end(), x_range) != range_names.end()) cout <<       "Running with range " <<  x_range <<    endl;
  else {cout << "Error in input of x_range: " << x_range << endl;  for (auto i: range_names)   std::cout << i << ' '; return; }


  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/SignalOverBackground/";
  MakeDir(output);

  output+="SignalRegions/";
  MakeDir(output);

  if(x_range=="all") {
    output+="AllMassRange";
    if(setlog_axis) output+="_logaxis/";
    MakeDir(output);
  }
  
  if(x_range=="low") {
    output+="LowMassRange";
    if(setlog_axis) output+="_logaxis/";
    MakeDir(output);
  }
  if(x_range=="high") {output+="HighMassRange";
    if(setlog_axis) output+="_logaxis/";
    MakeDir(output);
  }

  cout << "GetSignalEfficiency_combinedSR::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    

  
  vector<TString> SR;
  SR.push_back("SR1");
  SR.push_back("SR2");

  //SR.push_back(make_pair("OS", make_pair("SR3","SR4")));

  
  vector <TString> channel ={"MuMu","MuMu","EE","EE"};
  vector <TString> channel2 ={"MuMu","MuMu2","EE","EE2"};

  vector<TString> muIDs={"HNTight2016","POGHighPtMixTight","HNTightV1","HNTightV2","POGHighPtTight"};
  vector<TString> muID2s={"POGHighPtMixTight","POGTightPFIsoVeryTight","POGHighPtMixTight","POGTightPFIsoVeryVeryTight","POGTightPFIsoTight","POGTightPFIsoMedium","POGTightPFIsoLoose","POGTightStandardPFIsoTight"};
 
 
 vector<TString> elIDs={"passMediumID","passMVAID_noIso_WP80","passMVAID_noIso_WP90","passMVAID_iso_WP80","passMVAID_iso_WP90","HEEPv7","HNTight2016"};

 vector<TString> elID2s={"passTightID","passTightID_nocc","HNTightV1","HNTightV2","HNTightV3","HNTightV4","HNMediumV1","HNMediumV2","HNMediumV3"};
  // run over EE/MM plus charge seperation                                                                                                                    
  for(unsigned int k = 0 ; k < channel.size(); ++k){

    vector<TString> IDs;

    if ( channel2[k] == "EE" ) IDs = elIDs;
    else  if ( channel2[k] == "MuMu")  IDs =   muIDs;
    else  if ( channel2[k] == "MuMu2")  IDs =   muID2s;
    else  if ( channel2[k] == "EE2")  IDs =   elID2s;


    // loop over SR1/2/3/4
    for(unsigned int j = 0 ; j < SR.size(); ++j){
      
      vector<TString> IDs;
      // get efficiencies for each ID ran based on channel
      if ( channel[k].Contains("E") ) IDs = elIDs;
      else IDs =   muIDs;

      
      vector<TString> ignore_masses ;

      if(x_range=="low")  ignore_masses = {"500","600","700","800","900","1000","1100","1200","1300","1500","1400","1700","2000"};
      else if(x_range=="high")  ignore_masses = {"100","125","150","200","250","300","400"};
      else ignore_masses = {};
      
      if (_chan=="Schannel" && channel[k]=="EE" ) ignore_masses.push_back("300");
      if (_chan=="Tchannel") {
	ignore_masses.push_back("100");
	ignore_masses.push_back("125");
	ignore_masses.push_back("150");
	ignore_masses.push_back("200");
	ignore_masses.push_back("250");
	ignore_masses.push_back("300");
      }

      vector <TString> masses = GetMassType1Strings(ignore_masses,_chan);
      vector <double> d_masses = GetMassType1Doubles(ignore_masses,_chan);

      TString _sr = SR[j];
      TString _channel = channel[k];
      TString _channel2 = channel2[k];
      
      // hist leg
      TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
      // graph leg
      
      TLegend *legend_g = MakeLegend(0.65, 0.65, 0.9, 0.92);
      if(setlog_axis) legend_g = MakeLegend(0.65, 0.2, 0.9, 0.45);

      // canvas for hists
      TString canvasname=_sr+"_"+_channel2 +"_highmass_njets_"+analysername+"_JA_"+_channel+ptbin;
      TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

      vector<pair<Color_t,int> > histcolors = GetHistColors(IDs.size());
      vector<TGraphAsymmErrors*> _vgraphs;
      
      
      for(unsigned int l = 0 ; l < IDs.size(); l++){

	TString _id = IDs[l];

	cout  << ptbin << " " << _id << " " <<  _channel << " " << _channel2 << endl;
	
	// setup hist
	TString histlabel= _sr+"_"+_channel +  +"_highmass_"+analysername+"_"+_id+ptbin;
	TH1D* this_hist = new TH1D( histlabel , histlabel, masses.size(), 0, masses.size());
	SetBinLabels(this_hist, masses);


	TString promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSHN_SSPrompt.root";
	TString fakepath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSHN_Fake"+_channel+".root";
	TString cfpath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSHN_CF.root";

	TString n_sr_hist = _sr+"_highmass/"+_sr+"_highmass_njets_"+analysername+"_"+_channel+"_" + _id +ptbin+"_";

	double total_p = GetIntegral(promptpath, n_sr_hist);
	double total_np = GetIntegral(fakepath, n_sr_hist);
	double total_cf = GetIntegral(cfpath, n_sr_hist);
		
	double total_b = total_np + total_np+ total_cf;

	double bkgtmp = total_b + (0.3* total_np)*(0.3* total_np);
	double  denom= 1. + sqrt(bkgtmp);


	cout << "Total bkg ("<<_id<<") = " << total_b << endl;
	// setup graph
	int _Nbins = d_masses.size();
	vector<double> _x, _y, _xlow, _xup, _ylow, _yup;

	// loop over masses 
	for(unsigned int i = 0 ; i < masses.size(); ++i){

	  _x.push_back(d_masses[i]);
	  _xlow.push_back(0);
	  _xup.push_back(0);
          TString im = masses.at(i);

	  TString sigpath = ENV_MERGEDFILE_PATH+ "/"+analysername+"/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_"+im+"_nlo.root";
	  TFile * filemm = new TFile((sigpath).Data());	  
	  if(CheckFile(filemm) > 0) continue;
	  
	  TString n_all_hist="FillEventCutflow/"+analysername+"_"+_channel+"_"+ _id+"exo_17_028_dimu_same_sign";
          if(_channel == "EE") n_all_hist="FillEventCutflow/"+analysername+"_"+_channel+"_"+ _id+"exo_17_028_diel_same_sign";

	  TH1* hnsig = GetHist(filemm,n_all_hist);

	  float nsig = float(hnsig->GetBinContent(1));
	  // since signal for OS+SS are merged the cutcount is doubled
	  nsig=nsig/2;
	  
	  TH1*  hpass1 = GetHist(filemm, n_sr_hist);
	  //if(l==0) cout << "--------------------------------------------------------------------------------------- " << endl;
	  cout  << "Channel " << _chan << " : "  << _channel << " SR = " << _sr << "  ID " << _id << "  Mass = " << masses.at(i) << " Ncounts = " << (hpass1->Integral()) << " / " << nsig << " acceptance = " << 100*(hpass1->Integral())/nsig << " " <<  total_b << endl;

	  //cout << "SR1 eff = "  << 100*(hpass1->Integral() / nsig) << " SR2 eff = " << 100*(hpass2->Integral() / nsig)  << endl;
	  
	  double err ;
	  hpass1->IntegralAndError(1, hpass1->GetNbinsX()+1, err    , "");

	  double  punzi = (hpass1->Integral()/(nsig)) /denom;
	  
	  
	  //_y.push_back(((hpass1->Integral())/(nsig)) / sqrt(total_b));
	  _y.push_back(punzi);
	  _ylow.push_back(0);
          _yup.push_back(0);
	  this_hist->Fill(im, ((hpass1->Integral())/(nsig))/sqrt(total_b));
	  filemm->Close();
	}// mass loop
	// add entry for legend for each ID hist

	// Create graph
	TGraphAsymmErrors * gtmp = v_to_graph(_Nbins, _x, _xup, _xlow, _y, _yup, _ylow,histcolors[l].first);
	gtmp->SetLineColor(histcolors[l].first);
	gtmp->SetLineStyle(histcolors[l].second);
	gtmp->SetLineWidth(2.);
	_vgraphs.push_back(gtmp);
	AllLegendEntry(legend,this_hist,_id,"l");
	//this_hist->Write();
	this_hist->GetYaxis()->SetRangeUser(0.01,0.3);
      } // ID loop
      // make output dir if needed
      //MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalEfficiency/"+_sr);
      //MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalEfficiency/"+_sr+"/"+_channel);

      
      legend->Draw();
      TString canvasname2=_sr+"_highmass2_njets_"+analysername+"_JA_"+_channel+_id;
      TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
      c2->cd();
      if(setlog_axis){
	c2->SetLogx();
	c2->SetLogy();
      }	
      TGraphAsymmErrors*  old_gr = Get2016SigEffHighMass(_sr, _channel,d_masses,x_range);

      old_gr->SetLineStyle(10);
      old_gr->SetLineColor(kRed);
      old_gr->SetLineWidth(3.);
      old_gr->SetLineWidth(0.);
      old_gr->SetMarkerSize(0.);
      old_gr->SetMarkerColor(kRed);
      //old_gr->GetHistogram()->SetMaximum(GetMaximum(old_gr,_vgraphs)*1.1);
      float _max(0.),_min(9999999999.);
      for (auto i: _vgraphs) if(_max < i->GetHistogram()->GetMaximum()) _max = i->GetHistogram()->GetMaximum();
      for (auto i: _vgraphs) if(_min > i->GetHistogram()->GetMinimum()) _min = i->GetHistogram()->GetMinimum();
      
      if(setlog_axis)      old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, _max*1.4);
      else  old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, _max*1.4);

      if(x_range=="low")   old_gr->GetHistogram()->GetXaxis()->SetRangeUser(80., 400.);
      if(x_range=="high")  old_gr->GetHistogram()->GetXaxis()->SetRangeUser(500., 2000.);

      setTDRStyle();
      old_gr->GetHistogram()->GetYaxis()->SetTitle("S/sqrt(B)");
      old_gr->Draw("AC*");
      //if(_chan!="Tchannel")AllLegendEntry(legend_g,old_gr,"EXO-17-028","pl");
      for (unsigned int ig = 0 ; ig < _vgraphs.size(); ig++){
	_vgraphs[ig]->Draw("lp0same");
	AllLegendEntry(legend_g,_vgraphs[ig],_sr+":"+IDs[ig],"lp");
      }


      legend_g->Draw();

      DrawLatexWithLabel("2016","HighMass "+_sr,0.25,0.88);
      DrawLatexWithLabel("2016",_channel+" " + _chan,0.25,0.83);


    
      TString save_sg= output + "/graph_"+ptbin+_sr+"highmass_signaloverbackground_CombinedSR1SR2_"+analysername+"_"+_chan+"_"+_channel2+".pdf";
      //if(setlog_axis) save_sg = output + "graph_"+_sr+"highmass_CombinedSR1SR2_"+analysername+"_"+_chan+"_"+_channel+"_logAxis.pdf";


      c2->SaveAs(save_sg);
      OutMessage("GetSignalEfficiency",save_sg);
      
    } // SR 
  } // channel 

  
}
