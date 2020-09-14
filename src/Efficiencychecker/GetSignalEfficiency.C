#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void GetSignalEfficiency(TString _chan = "Schannel"){ 

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
  MakeDir(ENV_PLOT_PATH + FLATVERSION+"/SignalEfficiency");
  
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
  
  vector<TString> SR;
  SR.push_back("SR1");
  SR.push_back("SR2");
  SR.push_back("SR3");
  SR.push_back("SR4");
  
  vector <TString> channel;
  channel.push_back("MuMu");
  channel.push_back("EE");

  vector<TString> muIDs;
  muIDs.push_back("POGTightPFIsoLoose");
  muIDs.push_back("POGTightPFIsoMedium");
  muIDs.push_back("POGTightPFIsoTight");
  muIDs.push_back("HNTight2016");
  
  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");


  TString outfile = ENV_PLOT_PATH+ FLATVERSION+"/"+"HNEfficiencies_highmass_"+FLATVERSION+"_"+_chan+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");

  // loop over SR1/2/3/4
  for(unsigned int j = 0 ; j < SR.size(); ++j){

    // run over EE/MM plus charge seperation
    for(unsigned int k = 0 ; k < channel.size(); ++k){
      
      vector<TString> IDs;
      // get efficiencies for each ID ran based on channel
      if ( channel[k].Contains("E") ) IDs = elIDs;
      else IDs =   muIDs;
      
      TString _sr = SR[j];
      TString _channel = channel[k];
      
      // hist leg
      TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
      // graph leg
      TLegend *legend_g = MakeLegend(0.65, 0.75, 0.9, 0.92);

      // canvas for hists
      TString canvasname=_sr+"_"+_channel +"_highmass_njets_"+analysername+"_JA_"+_channel;
      TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

      vector<Color_t> histcolors = GetHistColors(IDs.size());
      vector<TGraphAsymmErrors*> _vgraphs;
      
      
      for(unsigned int l = 0 ; l < IDs.size(); l++){

	TString _id = IDs[l];

	// setup hist
	TString histlabel= _sr+"_"+_channel +  +"_highmass_HNtypeI_JA_"+_id;
	TH1D* this_hist = new TH1D( histlabel , histlabel, masses.size(), 0, masses.size());
	SetBinLabels(this_hist, masses);

	// setup graph
	int _Nbins = d_masses.size();
	vector<double> _x, _y, _xlow, _xup, _ylow, _yup;

	// loop over masses 
	for(unsigned int i = 0 ; i < masses.size(); ++i){

	  _x.push_back(d_masses[i]);
	  _xlow.push_back(0);
	  _xup.push_back(0);
          TString im = masses.at(i);

	  TString sigpath = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_"+im+"_nlo.root";
	  TFile * filemm = new TFile((sigpath).Data());	  
	  if(CheckFile(filemm) > 0) continue;

	  //SR1_highmass_njets_HNtypeI_JA_EE
	  TString n_sr_hist = _sr + "_highmass/"+_sr+"_highmass_njets_HNtypeI_JA_"+_channel+"_" + _id +"_";	  

	  TString n_all_hist="CutFlow/NoCut_HNtypeI_JA_"+_channel + "_"+ _id;
	  TH1* hnsig = GetHist(filemm,n_all_hist);
	  FormatHist(hnsig,false, histcolors[l]);

	  float nsig = float(hnsig->Integral());
	  // since signal for OS+SS are merged the cutcount is doubled
	  nsig=nsig/2.;
	  
	  TH1*  hpass = GetHist(filemm, n_sr_hist);
	  //if(l==0) cout << "--------------------------------------------------------------------------------------- " << endl;
	  cout  << "Channel " << _chan << " : "  << _channel << " SR = " << _sr << "  ID " << _id << "  Mass = " << masses.at(i) << " Ncounts = " << hpass->Integral() << " / " << nsig << " acceptance = " << 100*hpass->Integral()/nsig << endl;
	
	  double err ;
	  hpass->IntegralAndError(1, hpass->GetNbinsX()+1, err    , "");
	  _y.push_back(hpass->Integral()/(nsig));
	  _ylow.push_back(0);
          _yup.push_back(0);
	  this_hist->Fill(im, hpass->Integral()/(nsig));
	  filemm->Close();
	}// mass loop
	// add entry for legend for each ID hist

	// Create graph
	TGraphAsymmErrors * gtmp = v_to_graph(_Nbins, _x, _xup, _xlow, _y, _yup, _ylow,histcolors[l]);
	gtmp->SetLineColor(histcolors[l]);
	gtmp->SetLineWidth(2.);
	_vgraphs.push_back(gtmp);
	AllLegendEntry(legend,this_hist,_id,"l");
	fout->cd();
	this_hist->Write();
	this_hist->GetYaxis()->SetRangeUser(0.01,0.3);
      } // ID loop
      // make output dir if needed
      MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalEfficiency/"+_sr);
      MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalEfficiency/"+_sr+"/"+_channel);

      legend->Draw();
      TString save_s=ENV_PLOT_PATH+FLATVERSION+"/"+ _sr+"/"+_channel +"/hist_highmass_njets_HNtypeI_JA_"+_channel+"_"+_chan+".pdf";
      //OutMessage("GetSignalEfficiency",save_s);
      //c1->SaveAs(save_s);

      TString canvasname2=_sr+"_highmass2_njets_"+analysername+"_JA_"+_channel;
      TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
      c2->cd();
      
      TGraphAsymmErrors*  old_gr = Get2016SigEffHighMass(_sr, _channel,d_masses);

      old_gr->SetLineStyle(10);
      old_gr->SetLineColor(kRed);
      old_gr->SetLineWidth(3.);
      old_gr->SetMarkerColor(kRed);
      if(_sr == "SR1") old_gr->GetHistogram()->SetMaximum(GetMaximum(old_gr,_vgraphs)*1.1);
      if(_sr == "SR2") old_gr->GetHistogram()->SetMaximum(GetMaximum(old_gr,_vgraphs)*1.1);
      
      
      old_gr->Draw("AC*");
      AllLegendEntry(legend_g,old_gr,"EXO-17-028","pl");
      for (unsigned int ig = 0 ; ig < _vgraphs.size(); ig++){
	_vgraphs[ig]->Draw("lp0same");
	AllLegendEntry(legend_g,_vgraphs[ig],_sr+":"+IDs[ig],"lp");
      }


      legend_g->Draw();
      TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/SignalEfficiency/"+ _sr+"/"+_channel +"/graph_highmass_njets_HNtypeI_JA_"+_channel+"_"+_chan+".pdf";
      c2->SaveAs(save_sg);
      
    } // channel 
  } // SR 
  fout->Close();
}
