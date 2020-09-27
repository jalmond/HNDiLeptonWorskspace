#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MakeTexFile(map< TString, TH1D * > hs, TString outp,TString SR);

void GetBkgYields_HighMassSRs(TString analysername="HNtypeI_Dilepton" ){
  
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();
  

  vector<TString> code_names= {"HNtypeI_Dilepton","HNtypeI_JA"};
  vector<TString> channel_names= {"Schannel","Tchannel"};
  vector<TString> range_names = {"all","low","high"};
  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/BkgYields/";
  MakeDir(output);
  
  
  cout << "GetSignalEfficiency_combinedSR::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  vector <TString>   SRs   = {"SR1","SR2"};
  vector <TString>  years = {"2016"};
  vector <TString> channel ={"MuMu","EE"};

  vector<TString> muIDs  = { "POGTightPFIsoVeryTight","HNTight2016","HNTightV1","POGTightPFIsoTight","POGTightPFIsoMedium","POGTightPFIsoLoose","POGTightPFIsoVeryVeryTight","POGHighPtMixTight","POGHighPtTight"};
  vector<TString> elIDs = {"passTightID","passMediumID","HNTight2016","passTightID_noccb","passTightID_nocc","passMVAID_iso_WP90","passMVAID_iso_WP80","HNTightV1"};

  if (analysername=="HNtypeI_Dilepton"){
    muIDs  = { "POGTightPFIsoVeryTight","HNTightV1", "POGHighPtMixTight"};
    elIDs = {"passTightID","passTightID_noccb","HNTightV1"};
  }


  
  // run over EE/MM plus charge seperation
  for (auto year: years ){
    
    for(unsigned int k = 0 ; k < channel.size(); ++k){
      
      vector<TString> IDs;

      if ( channel[k].Contains("E") ) IDs = elIDs;
      else IDs =   muIDs;
      
      
      vector<TString> ignore_masses ;
      
      TString _channel = channel[k];
    
      // hist leg
      TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
      // graph leg
      
      TLegend *legend_g = MakeLegend(0.6, 0.7, 0.9, 0.92);
      
      // canvas for hists
      TString canvasname="SR1_SR2_"+_channel +"_highmass_njets_"+analysername+"_JA_"+_channel;
      
      vector<pair<Color_t,int> > histcolors = GetHistColors(IDs.size());
      vector<TH1D*> _vhists;
      
      TString histlabel1= "SR1_"+_channel +  +"_highmass_"+analysername+"_";
      TH1D* this_hist_exo_17_028 = new TH1D( histlabel1 , histlabel1, SRs.size(), 0, SRs.size());
      SetBinLabels(this_hist_exo_17_028, SRs);
      if(_channel=="EE")this_hist_exo_17_028->Fill("SR1",422.);
      if(_channel=="EE")this_hist_exo_17_028->Fill("SR2",11.);
      if(_channel=="MuMu")this_hist_exo_17_028->Fill("SR1",410.);
      if(_channel=="MuMu")this_hist_exo_17_028->Fill("SR2",12.);

      for(unsigned int l = 0 ; l < IDs.size(); l++){
	
	TString _id = IDs[l];
	
	// setup hist
	TString histlabel= "SR1_"+_channel +  +"_highmass_"+analysername+"_"+_id;

	TH1D* this_hist = new TH1D( histlabel , histlabel, SRs.size(), 0, SRs.size());
	for (auto SR: SRs ){
	  
	  //	  SetBinLabels(this_hist, SRs);
	  TString n_sr_hist = SR+"_highmass/"+SR+"_highmass_njets_"+analysername+"_"+_channel+"_" + _id +"_";
	  
	  TString promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_SSPrompt.root";
	  TString fakepath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSNonIso_Fake"+_channel+".root";
	  TString cfpath = ENV_MERGEDFILE_PATH+analysername+ "/"+year+"/"+analysername+"_SkimTree_SSNonIso_CF.root";
	
	  double total_b = GetIntegral(promptpath, n_sr_hist);
	  total_b += GetIntegral(fakepath, n_sr_hist);
	  total_b += GetIntegral(cfpath, n_sr_hist);

	  this_hist->Fill(SR,total_b);
	}
	
	this_hist->SetLineColor(histcolors[l].first);
	this_hist->SetLineStyle(histcolors[l].second);
	this_hist->SetLineWidth(2.);
	_vhists.push_back(this_hist);
      } // ID loop
      
      TString canvasname2="SR1_SR2_highmass2_njets_"+analysername+"_JA_"+_channel;
      TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
      c2->cd();


      this_hist_exo_17_028->GetYaxis()->SetTitle("Events");
      this_hist_exo_17_028->SetLineStyle(10);
      this_hist_exo_17_028->SetLineColor(kRed);
      
      float _max(0.),_min(9999999999.);
      for (auto i: _vhists) if(_max < i->GetMaximum()) _max = i->GetMaximum();
      for (auto i: _vhists) if(_min > i->GetMinimum()) _min = i->GetMinimum();
      
     this_hist_exo_17_028->GetYaxis()->SetRangeUser(_min*0.9, _max*1.4);
     map<TString, TH1D*> histmap;
     histmap["17_028"] = this_hist_exo_17_028;
     
     setTDRStyle();
     
      this_hist_exo_17_028->Draw("hist");
      for (unsigned int ig = 0 ; ig < _vhists.size(); ig++){
	histmap[IDs[ig]] = _vhists[ig],IDs[ig];
	
	_vhists[ig]->Draw("histsame");
	AllLegendEntry(legend_g,_vhists[ig],IDs[ig],"l");
      }
      
      legend_g->Draw();
      
      DrawLatexWithLabel("2016","HighMass SR",0.25,0.88);
      DrawLatexWithLabel("2016",_channel,0.25,0.83);

  
      MakeTexFile(histmap,output,"SR1+SR2");
      TString save_sg= output + "/hist_SR1_SR2_highmass_event_yields_"+analysername+"_"+_channel+".pdf";

      c2->SetLogy();
      c2->SaveAs(save_sg);
      OutMessage("GetSignalEfficiency",save_sg);
    } // channel 
  }
}

void MakeTexFile(map< TString, TH1D * > hs,TString output,TString SR){

  TString texfilepath = output+"/tex/";
  MakeDir(texfilepath);

  ofstream ofile_tex(texfilepath+"/Yields.tex",ios::trunc);
  ofile_tex.setf(ios::fixed,ios::floatfield);
  ofile_tex << "\\documentclass[10pt]{article}" << endl;
  ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}" << endl;
  ofile_tex << "\\begin{document}" << endl;
  ofile_tex << "\\input{"+texfilepath+"/Table.txt}" << endl;
  ofile_tex << "\\end{document}" << endl;

  ofstream ofile(texfilepath+"/Table.txt",ios::trunc);
  ofile.precision(3);
  ofile.setf(ios::fixed,ios::floatfield);
  ofile << "\\begin{table}[!tbh]" << endl;
  ofile << "  \\caption{" << endl;
  ofile << "    Number of events in " << SR << endl;
  ofile << "  }" << endl;
  ofile << "  \\begin{center}" << endl;
  ofile << "    \\begin{tabular}{c|c|c}" << endl;
  ofile << "\\hline" << endl;
  ofile << " ID & SR1 & SR2 \\\\" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;

  TH1D *hist_bkgd = new TH1D("hist_bkgd", "", 1., 0., 1.);
  bool HasSignal = false;
  for(map< TString, TH1D * >::iterator it = hs.begin(); it != hs.end(); it++){
    TString name = it->first;

    name.ReplaceAll("_","\\_");
    if(name == "X + #gamma") name = "$X + \\gamma$";
    if(name == "Z + #gamma") name = "Z $+ \\gamma$";
    if(name == "W + #gamma") name = "W $+ \\gamma$";
    if(name == "top + #gamma") name = "top $+ \\gamma$";
    TH1D *h_bkgd = it->second;
    ofile << name << " & $"<<h_bkgd->GetBinContent(1)<< "$  & $" << h_bkgd->GetBinContent(2)  <<"$ \\\\" << endl;
    hist_bkgd->Add(h_bkgd);
  }
  ofile << "\\hline" << endl;
  //  ofile << "Total & $" << hist_bkgd->GetBinContent(1) << " \\pm " << hist_bkgd->GetBinError(1) << "$ \\\\" << endl;
  //ofile << "\\hline" << endl;


  //double signif = (hist_data->GetBinContent(1) - hist_bkgd->GetBinContent(1)) / sqrt( (hist_bkgd->GetBinError(1))*(hist_bkgd->GetBinError(1)) + (hist_data->GetBinError(1))*(hist_data->GetBinError(1)) );

  //ofile << "Significance & $" <<signif<<" \\sigma$ \\\\" << endl;

  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "    \\end{tabular}" << endl;
  ofile << "  \\end{center}" << endl;
  ofile << "\\end{table}" << endl;

  system("latex "+texfilepath+"/Yields.tex");
  system("dvipdf Yields.dvi");
  system("rm *aux");
  system("rm *log");
  system("rm *dvi");
  system("mv Yields.pdf "+texfilepath);

}

