#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void GetSignalEfficiency(){ 

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

  MakeDir(ENV_FILE_PATH + FLATVERSION);
  MakeDir(input_path);
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  MakeDir(output);
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }
  MakeDir(input_path);

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    

  
  // list all masses even tho not all signals are made currently

  TString ignore_masses = "300";
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


  TString outfile = "HNEfficiencies_highmass_"+FLATVERSION+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");

  // loop over SR1/2/3/4
  for(unsigned int j = 0 ; j < SR.size(); ++j){

    // run over EE/MM plus charge seperation
    for(unsigned int k = 0 ; k < channel.size(); ++k){
      
      vector<TString> IDs;
      // get efficiencies for each ID ran based on channel
      if ( channel[k].Contains("E") ) IDs = elIDs;
      else IDs =   muIDs;
      
      //cout << "TEST " << endl;
      
      TString _sr = SR[j];
      TString _channel = channel[k];
      
      TString sign = "same_sign";
      if(_sr == "SR3") { _sr = "SR1"; sign = "opposite_sign";}
      if(_sr == "SR4") { _sr = "SR2"; sign= "opposite_sign"; }


      TLegend *legend = MakeLegend(0.69, 0.65, 0.96, 0.92);
      TLegend *legend_g = MakeLegend(0.69, 0.65, 0.96, 0.92);
      
      TString canvasname=_sr+"_"+_channel +"_highmass_"+sign +"_njets_"+analysername+"_JA_"+_channel;
      TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

      vector<Color_t> histcolors = GetHistColors(IDs.size());
      vector<TGraphAsymmErrors*> _vgraphs;
      
      for(unsigned int l = 0 ; l < IDs.size(); l++){

	cout << IDs[l] << endl;
	TString _id = IDs[l];
	TString histlabel= _sr+"_"+_channel +  +"_highmass_HNtypeI_JA_"+_id;
	TH1D* this_hist = new TH1D( histlabel , histlabel, masses.size(), 0, masses.size());
	SetBinLabels(this_hist, masses);

	int _Nbins = d_masses.size();
	vector<double> _x, _y, _xlow, _xup, _ylow, _yup;

	for(unsigned int i = 0 ; i < masses.size(); ++i){

	  _x.push_back(d_masses[i]);
	  _xlow.push_back(0);
	  _xup.push_back(0);
          TString im = masses.at(i);
	  TFile * filemm = new TFile((ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_Schannel_"+_channel+"_"+im+"_nlo.root").Data());	  
	  if(CheckFile(filemm) > 0) continue;
	  
	  TString hist = _sr + "_"+_channel + "_highmass_"+sign +"/"+_sr+"_"+_channel +"_highmass_"+sign +"_njets_HNtypeI_JA_"+_channel+"_" + _id +"_";	  
	  TH1* hnsig = GetHist(filemm,"CutFlow/NoCut_HNtypeI_JA_"+_channel + "_"+ _id);
	  FormatHist(hnsig,false, histcolors[l]);
	  float nsig = float(hnsig->Integral());
	  
	  TH1*  hpass = GetHist(filemm, hist);
	  
	  //cout  << "Channel " << _channel << " SR = " << _sr << " Charge = " << sign << "  ID " << _id << "  Mass = " << masses.at(i) << " acceptance = " << hpass->Integral()/nsig << endl;
	
	  double err ;
	  hpass->IntegralAndError(1, hpass->GetNbinsX()+1, err    , "");
	  _y.push_back(hpass->Integral()/(nsig));
	  _ylow.push_back(0);
          _yup.push_back(0);
	  this_hist->Fill(im, hpass->Integral()/(nsig));
	  filemm->Close();
	}
	// add entry for legend for each ID hist
	cout << "Graph " << endl;
	TGraphAsymmErrors * gtmp = v_to_graph(_Nbins, _x, _xup, _xlow, _y, _yup, _ylow,histcolors[l]);
	gtmp->SetLineColor(histcolors[l]);
	gtmp->SetLineWidth(2.);
	_vgraphs.push_back(gtmp);
	AllLegendEntry(legend,this_hist,_id,"l");
	fout->cd();
	this_hist->Write();
	this_hist->GetYaxis()->SetRangeUser(0.01,0.3);
	//	if(l == 0)this_hist->Draw("hist");
	//else this_hist->Draw("histsame");

	MakeDir(ENV_PLOT_PATH+FLATVERSION+"/"+_sr);
	MakeDir(ENV_PLOT_PATH+FLATVERSION+"/"+_sr+"/"+_channel);
      }
      //legend->Draw();
      TString save_s=ENV_PLOT_PATH+FLATVERSION+"/"+ _sr+"/"+_channel +"/hist_highmass_"+sign +"_njets_HNtypeI_JA_"+_channel+".pdf";
      OutMessage("GetSignalEfficiency",save_s);
      c1->SaveAs(save_s);

      TString canvasname2=_sr+"_"+_channel +"_highmass2_"+sign +"_njets_"+analysername+"_JA_"+_channel;
      TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
      c2->cd();
      
      TGraphAsymmErrors*  old_gr = Get2016SigEff(_sr, _channel,d_masses);

      old_gr->SetLineStyle(10);
      old_gr->SetLineColor(kRed);
      old_gr->SetLineWidth(3.);
      old_gr->SetMarkerColor(kRed);
      if(_sr == "SR1") old_gr->GetHistogram()->SetMaximum(0.2);
      if(_sr == "SR2") old_gr->GetHistogram()->SetMaximum(0.5);
      
      old_gr->Draw("AC*");
      //old_gr->Draw("p0Al");
      AllLegendEntry(legend_g,old_gr,"EXO-17-028","pl");
      for (unsigned int ig = 0 ; ig < _vgraphs.size(); ig++){
	_vgraphs[ig]->Draw("lp0same");
	AllLegendEntry(legend_g,_vgraphs[ig],IDs[ig],"lp");
      }


      legend_g->Draw();
      TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/"+ _sr+"/"+_channel +"/grapgh_highmass_"+sign +"_njets_HNtypeI_JA_"+_channel+".pdf";
      c2->SaveAs(save_sg);

      
    }
  }
  fout->Close();
}
