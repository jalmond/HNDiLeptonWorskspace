#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void FakerateType1(TString channel="Muon", TString year="2016"){
  

  TString skim="SkimTree_HNFake";
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  TString analysername="FakeRateHN";

  vector<TString> code_names= {"FakeRateHN"};
  vector<TString> channel_names= {"Muon","Electron"};

  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  if(std::find(channel_names.begin(), channel_names.end(), channel) != channel_names.end()) cout <<	"Running with channel " <<  channel <<	endl;
  else {cout << "Error in input of _chan: " << channel << endl;  for (auto i: channel_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/FakeRates/";
  MakeDir(output);

  output+=channel+"/";
  MakeDir(output);
  output+=year+"/";
  MakeDir(output);

  cout << "FakerateType1::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  vector<TString> muIDs={"POGTightPFIsoVeryTight","HNTight2016","POGHighPtMixTight","POGTightPFIsoVeryVeryTight","POGTightPFIsoTight","POGTightPFIsoMedium","POGTightPFIsoLoose","HNTightV1","HNTightV2","POGHighPtTight","POGTightStandardPFIsoTight"};
   vector<TString> elIDs={"passTightID","HNTight2016","passTightID_nocc","HNTightV1","HNTightV2","HNTightV3","HNTightV4","HNMediumV1","HNMediumV2","HNMediumV3","passMediumID","passMVAID_noIso_WP80","passMVAID_noIso_WP90","passMVAID_iso_WP80","passMVAID_iso_WP90"};

   cout << "List of IDs : " << endl;
   for (auto i: muIDs) cout << i << endl;
  for (auto i: elIDs) cout << i << endl;

  
  vector<TString> SR = {"_barrel_ptcorr1","_endcap_ptcorr1"};

  TString data_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/FakeRateHN_"+skim+"_"+channel+".root";
  TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/FakeRateHN_"+skim+"_MC.root";
  TFile * file_data = new TFile((data_path).Data());
  TFile * file_mc = new TFile((mc_path).Data());
  if(CheckFile(file_data) > 0) return;
  if(CheckFile(file_mc) > 0)  return;

  for(unsigned int j = 0 ; j < SR.size(); ++j){

    vector<TString> IDs;
    // get efficiencies for each ID ran based on channel
    if ( channel.Contains("E") ) IDs = elIDs;
    else IDs =   muIDs;

    // hist leg

    // graph leg
    
    // canvas for hists
    TString canvasname= channel+SR[j];
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
    
    TString data_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/FakeRateHN_"+skim+"_"+channel+".root";
    TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/FakeRateHN_"+skim+"_MC.root";
    TFile * file_data = new TFile((data_path).Data());
    TFile * file_mc = new TFile((mc_path).Data());
    if(CheckFile(file_data) > 0) continue;
    if(CheckFile(file_mc) > 0) continue;
    
    for(unsigned int l = 0 ; l < IDs.size(); l++){
      
      TString _id = IDs[l];

      //TightMuFakeRateHN_MuMu_POGTightStandardPFIsoTight_40_ptcorr_eta LooseMuFakeRateHN_MuMu_POGTightStandardPFIsoTight_40_ptcorr_eta

      // setup hist
      TString channel_tag="Mu";
      if(channel == "Electron") channel_tag="EE";

      //TightMuFakeRateHN_MuMu_HNTight2016_20_barrel_ptcorr1;1
      TString histlabel20_tight= "Tight"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_20"+SR[j];
      TString histlabel20_loose= "Loose"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_20"+SR[j];
      TString histlabel30_tight= "Tight"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_30"+SR[j];
      TString histlabel30_loose= "Loose"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_30"+SR[j];
      TString histlabel40_tight= "Tight"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_40"+SR[j];
      TString histlabel40_loose= "Loose"+channel_tag+"FakeRateHN_"+channel_tag+channel_tag+"_"+_id+"_40"+SR[j];

      
      
      TH1D* data_hist20_tight = GetHist(file_data,histlabel20_tight);
      TH1D* mc_hist20_tight = GetHist(file_mc,histlabel20_tight);
      TH1D* data_hist20_loose = GetHist(file_data,histlabel20_loose);
      TH1D* mc_hist20_loose = GetHist(file_mc,histlabel20_loose);

      data_hist20_tight->Add(mc_hist20_tight,-1.1);
      data_hist20_loose->Add(mc_hist20_loose,-1.1);

      
      TH1D* data_hist30_tight = GetHist(file_data,histlabel30_tight);
      TH1D* mc_hist30_tight = GetHist(file_mc,histlabel30_tight);
      TH1D* data_hist30_loose = GetHist(file_data,histlabel30_loose);
      TH1D* mc_hist30_loose = GetHist(file_mc,histlabel30_loose);

      data_hist30_tight->Add(mc_hist30_tight,-1.1);
      data_hist30_loose->Add(mc_hist30_loose,-1.1);


      TH1D* data_hist40_tight = GetHist(file_data,histlabel40_tight);
      TH1D* mc_hist40_tight = GetHist(file_mc,histlabel40_tight);
      TH1D* data_hist40_loose = GetHist(file_data,histlabel40_loose);
      TH1D* mc_hist40_loose = GetHist(file_mc,histlabel40_loose);

      data_hist40_tight->Add(mc_hist40_tight,-1.1);
      data_hist40_loose->Add(mc_hist40_loose,-1.1);
      
      data_hist20_tight->SetLineColor(kRed);
      data_hist20_tight->SetLineWidth(2.);
      data_hist30_tight->SetLineWidth(2.);
      data_hist40_tight->SetLineWidth(2.);
      data_hist20_tight->Divide(data_hist20_loose);
      data_hist20_tight->GetYaxis()->SetTitle("#epsilon");


      data_hist30_tight->SetLineColor(kGreen);
      data_hist30_tight->Divide(data_hist30_loose);
      data_hist40_tight->SetLineColor(kBlue-2);
      data_hist40_tight->Divide(data_hist40_loose);

      TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
      legend->AddEntry(data_hist20_tight,"20 GeV Away jet","l");
      legend->AddEntry(data_hist30_tight,"30 GeV Away jet","l");
      legend->AddEntry(data_hist40_tight,"40 GeV Away jet","l");
      c1->cd();
      data_hist20_tight->Draw("hist");
      data_hist30_tight->Draw("histsame");
      data_hist40_tight->Draw("histsame");
      
      legend->Draw();

      setTDRStyle();
      
      DrawLatexWithLabel(year,channel,0.25,0.88);
      DrawLatexWithLabel(year,SR[j],0.25,0.83);
      DrawLatexWithLabel(year,_id,0.25,0.78);
      
      TString save_sg= output + "/fake_rate_"+channel + "_"+SR[j]+"_"+_id+"_"+year+".pdf";
      
      c1->SaveAs(save_sg);
      OutMessage("GetSignalEfficiency",save_sg);
      
    } // SR 
  } // channel 
  file_data->Close();
  file_mc->Close();
    
  delete file_data;
  delete file_mc;

  return;
}
