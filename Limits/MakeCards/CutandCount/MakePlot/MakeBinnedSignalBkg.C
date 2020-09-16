#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MakeBinnedSignalBkg(TString _chan = "Schannel", TString year="2016",TString flavour = "MuMu", TString _id = "HNTight2016", TString analysername="HNtypeI_JA", TString _sr="SR1", TString mass="100"){ 

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();
  
  // local path names
  TString ENV_FILE_PATH= getenv("INFILE_PATH");
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
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
  
  TString canvasname=_sr+"_"+flavour +"_highmass_njets_"+analysername+"_JA_"+flavour;
  TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
  c1->SetLogy();
  vector<Color_t> sighistcolors = GetHistColors(1);
  vector<TGraphAsymmErrors*> _vgraphs;
  
  
  TString histlabel= _sr+analysername+"_"+flavour+"_"+_id+"exo_17_028_EE_SR4";

  
  TString promptpath = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_SSPrompt.root";
  TString fakepath = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/"+analysername+"_SkimTree_SSNonIso_Fake"+flavour+".root";
  
  
  TString sigpath = ENV_MERGEDFILE_PATH+ +analysername+"/2016/SIG/"+analysername+"_HN_"+_chan+"_"+flavour+"_200_nlo.root";
  
  TFile* filemm = TFile::Open((sigpath).Data());	  
  if(CheckFile(filemm) > 0) return;
  
  TString n_sr_hist=histlabel;
  TH1* this_hist_sig = GetHist(filemm,n_sr_hist);
  
  TFile*  file_prompt  = TFile::Open((promptpath).Data());
  TFile*  file_fake = TFile::Open((fakepath).Data());
  TH1* this_hist_prompt = GetHist(file_prompt,n_sr_hist);
  TH1* this_hist_fake = GetHist(file_fake,n_sr_hist);
  
  double nsig = double(this_hist_sig->Integral());
  double nprompt = double(this_hist_prompt->Integral());
  double nfake = double(this_hist_fake->Integral());
  
  double scale = 100.;
  
  cout << mass<< " " << nfake << " " << nprompt << " " << scale*nsig << endl;
  this_hist_prompt->SetFillColor(kSpring-1);
  this_hist_prompt->SetLineColor(kSpring-1);
  this_hist_fake->SetFillColor(870);
  this_hist_fake->SetLineColor(870);
  
  
  
  
  THStack *hs = new THStack(_sr+"_"+flavour +"_highmass_nevent_HNtypeI_JA_"+flavour+"_" + _id,"");
  
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
  
  this_hist_sig->Draw("hist");                                                                                                                            
  this_hist_sig->GetYaxis()->SetTitle("Events / bin " );
  this_hist_sig->GetYaxis()->SetRangeUser(0.05, 10000.);
  
  TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/" + year + "/" + _sr+"/hist_highmass_nevents_HNtypeI_JA_"+flavour+"_"+_id+".pdf";
	 
  hs->Draw("histsame");
  this_hist_sig->Draw("histsame");
  c_SOnly->SaveAs(save_sg,".pdf");	  
  
  
  this_hist_sig->SetLineColor(kRed);
  this_hist_sig->GetYaxis()->SetTitle("Events / bin " );
  this_hist_sig->Draw("hist");
  
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
  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + year);
  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + year+  "/" + _sr);

  delete hs;
  delete this_hist_sig;
  delete this_hist_fake;
  delete this_hist_prompt;
  
  file_prompt->Close();
  file_fake->Close();
  filemm->Close();
  
  
}
