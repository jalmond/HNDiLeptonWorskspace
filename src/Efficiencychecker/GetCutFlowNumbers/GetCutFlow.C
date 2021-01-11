#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void GetCutFlow(TString channel="MuMu", TString ptbin="_HighPt", TString analysername="HNtypeI_Dilepton" ,  TString year="2016",TString _chan = "Schannel",bool setlog_axis=false, TString x_range="all"){ 

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  
  vector<TString> code_names= {"HNtypeI_Dilepton"};
  vector<TString> channel_names= {"S_Tchannel","Schannel","Tchannel"};


  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  if(std::find(channel_names.begin(), channel_names.end(), _chan) != channel_names.end()) cout <<	"Running with channel " <<  _chan <<	endl;
  else {cout << "Error in input of _chan: " << _chan << endl;  for (auto i: channel_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/CutFlow/";
  MakeDir(output);

  output+="SignalRegions/";
  MakeDir(output);
  output+=year+"/";
  MakeDir(output);



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

  
  vector<TString> muIDs={"HNTightV1","HNTightV2","POGHighPtTight","POGTightPFIsoVeryTight","POGTightPFIsoVeryVeryTight","POGTightPFIsoTight","POGTightPFIsoMedium","POGTightPFIsoLoose","POGTightStandardPFIsoTight"};
 
 
  vector<TString> elIDs={"passMediumID","passMVAID_noIso_WP80","passMVAID_noIso_WP90","passMVAID_iso_WP80","passMVAID_iso_WP90","HEEPv7","HEEP2018"};

  vector<TString> elID2s={"passTightID","passTightID_nocc","HNTightV1","HNTightV2","HNTightV3","HNTightV4","HNMediumV1","HNMediumV2","HNMediumV3"};
  // run over EE/MM plus charge seperation                                                                                                                    
  vector<TString> IDs;
  
  if(channel == "EE")  IDs = elIDs;
  if(channel == "EE2")  IDs = elID2s;
  if(channel == "MuMu")  IDs = muIDs;
  
  vector<TString> ignore_masses ;
  
  if(x_range=="low")  ignore_masses = {"500","600","700","800","900","1000","1100","1200","1300","1500","1400","1700","2000"};
  else if(x_range=="high")  ignore_masses = {"100","125","150","200","250","300","400"};
  else ignore_masses = {};
  
  if (_chan=="Schannel" && channel=="EE" ) ignore_masses.push_back("300");
  if (_chan.Contains("Tchannel")){
    ignore_masses.push_back("100");
    ignore_masses.push_back("125");
    ignore_masses.push_back("150");
    ignore_masses.push_back("200");
    ignore_masses.push_back("250");
    ignore_masses.push_back("300");
  }
  
  vector <TString> masses = GetMassType1Strings(ignore_masses,_chan);
  vector <double> d_masses = GetMassType1Doubles(ignore_masses,_chan);
  
  
  TString _channel = channel;
  if(channel == "EE2") _channel = "EE";
  if(channel == "MuMu2") _channel = "MuMu";
  
  // hist leg
  TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
  // graph leg
  
  TLegend *legend_g = MakeLegend(0.65, 0.65, 0.9, 0.92);
  if(setlog_axis) legend_g = MakeLegend(0.65, 0.2, 0.9, 0.45);
  
    vector<pair<Color_t,int> > histcolors = GetHistColors(IDs.size());
    vector<TGraphAsymmErrors*> _vgraphs;
    
    map<TString, double> map_punzi;

    TString promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSHN_SSPrompt.root";
    TString fakepath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSHN_Fake"+_channel+".root";
    TString cfpath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSHN_CF.root";

    for(unsigned int l = 0 ; l < IDs.size(); l++){
      
      TString _id = IDs[l];
      
      
      // setup hist
      TString histlabel= "_"+_channel +  +"_highmass_"+analysername+"_"+_id+ptbin;
      
      vector<double>  punzis;
      double _bkg(0.);
      for(unsigned int j = 0 ; j < SR.size(); ++j){
	TString _sr = SR[j];
	
	TString n_sr_hist = _sr+"_highmass/"+_sr+"_highmass_njets_"+analysername+"_"+_channel+"_" + _id +ptbin+"_";
	
	TFile * file_prompt = new TFile((promptpath).Data());
	TFile * file_fake = new TFile((fakepath).Data());
	TFile * file_cf = new TFile((cfpath).Data());
	

	double total_p  = GetIntegral(file_prompt, n_sr_hist);
	double total_np =  GetIntegral(file_fake, n_sr_hist);
	double total_cf = GetIntegral(file_cf, n_sr_hist);
	
	TString histlabel= _sr+"_"+_channel +  +"_highmass_"+analysername+"_"+_id+ptbin;
	
	double total_b = total_np + total_p+ total_cf;
	_bkg+= total_b;
	double bkgtmp = total_b + (0.3* total_np)*(0.3* total_np);
	double  denom= 1. + sqrt(bkgtmp);
	punzis.push_back(denom);

	file_prompt->Close();
	file_fake->Close();
	file_cf->Close();
	delete file_prompt;
	delete file_fake;
	delete file_cf;
      }
      
      
	// setup graph
	int _Nbins = d_masses.size();
	vector<double> _x, _y, _xlow, _xup, _ylow, _yup;

	double idpunzi(0.);
	// loop over masses 
	for(unsigned int i = 0 ; i < masses.size(); ++i){
	  if(i % 2 == 1 ) continue;
	  _x.push_back(d_masses[i]);
	  _xlow.push_back(0);
	  _xup.push_back(0);
          TString im = masses.at(i);

	  double _punzi(0.),count(0.);
	  for(unsigned int j = 0 ; j < SR.size(); ++j){
	    
	    TString sigpathS = ENV_MERGEDFILE_PATH+ "/"+analysername+"/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_"+im+"_nlo.root";
	    
	    TFile * filemm = new TFile((sigpathS).Data());
	    //TFile * filett = new TFile((sigpathT).Data());	  
	    if(CheckFile(filemm) > 0) continue;
	    //if(CheckFile(filett) > 0) continue;
	    
	    TString n_all_hist="FillEventCutflow/"+analysername+"_"+_channel+"_"+ _id+"exo_17_028_dimu_same_sign";
	    if(_channel == "EE") n_all_hist="FillEventCutflow/"+analysername+"_"+_channel+"_"+ _id+"exo_17_028_diel_same_sign";
	    
	    TH1* hnsigS = GetHist(filemm,n_all_hist);
	    //TH1* hnsigT = GetHist(filett,n_all_hist);
	    
	    float nsig = float(hnsigS->GetBinContent(1));// + float(hnsigT->GetBinContent(1)) ;
	    // since signal for OS+SS are merged the cutcount is doubled
	    nsig=nsig/2;

	    TString _sr = SR[j];

	    TString n_sr_hist = _sr+"_highmass/"+_sr+"_highmass_njets_"+analysername+"_"+_channel+"_" + _id +ptbin+"_";

	    TH1*  hpass1 = GetHist(filemm, n_sr_hist);

	    
	    double err ;
	    hpass1->IntegralAndError(1, hpass1->GetNbinsX()+1, err    , "");
	    //hpass2->IntegralAndError(1, hpass2->GetNbinsX()+1, err    , "");
	    
	    double  punzi = ((hpass1->Integral()) /(nsig)) /punzis[j];
	    count+=((hpass1->Integral()) /(nsig));
	    _punzi+= punzi;
	    filemm->Close();
	    
	  }
	  
	  cout << "Channel " << _chan << " : "  <<  channel <<  "  ID " << _id << "  Mass = " << masses.at(i) << " Ncounts = " << count << " bkg =  " <<  _bkg << " punzi  " << _punzi << endl;    
	  _y.push_back(_punzi);
	  _ylow.push_back(0);
          _yup.push_back(0);

	  //filett->Close();
	  idpunzi +=  _punzi;
	}// mass loop
	// add entry for legend for each ID hist

	// Create graph
	TGraphAsymmErrors * gtmp = v_to_graph(_Nbins, _x, _xup, _xlow, _y, _yup, _ylow,histcolors[l].first);
	gtmp->SetLineColor(histcolors[l].first);
	gtmp->SetLineStyle(histcolors[l].second);
	gtmp->SetLineWidth(2.);
	_vgraphs.push_back(gtmp);

	map_punzi[_id] = idpunzi;

    } // ID loop
    
    
    cout  << "################################" << endl;
    for(auto im : map_punzi){
      cout << im.first << " toal punzi = " << im.second << endl;
    }
    
    cout  << "################################" << endl;

    
    legend->Draw();
    TString canvasname2="SR1_2_highmass2_njets_"+analysername+"_JA_"+_channel+ptbin+channel;
    TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
    c2->cd();
    if(setlog_axis){
      c2->SetLogx();
      c2->SetLogy();
    }	
    TGraphAsymmErrors*  old_gr = Get2016SigEffHighMass("SR1", _channel,d_masses,x_range);
    
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
    
    cout << _min << " " << _max << endl;
    if(setlog_axis)      old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, _max*1.4);
    else  old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, _max*1.4);
    old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, 0.5);
    if(ptbin.Contains("Low"))    old_gr->GetHistogram()->GetYaxis()->SetRangeUser(_min*0.9, 0.01);
    if(x_range=="low")   old_gr->GetHistogram()->GetXaxis()->SetRangeUser(80., 400.);
    if(x_range=="high")  old_gr->GetHistogram()->GetXaxis()->SetRangeUser(500., 2000.);
    
    setTDRStyle();
    old_gr->GetHistogram()->GetYaxis()->SetTitle("S/sqrt(B)");
    old_gr->Draw("AC*");
    //if(_chan!="Tchannel")AllLegendEntry(legend_g,old_gr,"EXO-17-028","pl");
    for (unsigned int ig = 0 ; ig < _vgraphs.size(); ig++){
      _vgraphs[ig]->Draw("lp0same");
      AllLegendEntry(legend_g,_vgraphs[ig],"SR1_2:"+IDs[ig],"lp");
    }
    
    
    legend_g->Draw();
    
    DrawLatexWithLabel(year,"HighMass SR1+2",0.25,0.88);
    DrawLatexWithLabel(year,_channel+" " + _chan,0.25,0.83);
    
    
    
    TString save_sg= output + "/graph_"+ptbin+"SR1_2"+"highmass_signaloverbackground_CombinedSR1SR2_"+analysername+"_"+_chan+"_"+channel+".pdf";
    //if(setlog_axis) save_sg = output + "graph_"+_sr+"highmass_CombinedSR1SR2_"+analysername+"_"+_chan+"_"+_channel+"_logAxis.pdf";
    
    
    c2->SaveAs(save_sg);
    OutMessage("GetSignalEfficiency",save_sg);
    
  
}
