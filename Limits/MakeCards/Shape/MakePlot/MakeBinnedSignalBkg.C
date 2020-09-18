#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"


void MakeBinnedSignalBkg(TString _chan = "Schannel", TString year="2016",TString flavour = "MuMu", TString _id = "HNTight2016", TString analysername="HNtypeI_JA", TString _sr="SR1", TString mass="100", TString _var="signalbin", TString outpath=""){ 

  
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
  

  TString  input_rootfile = "HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+_sr + "_"+ flavour + "_"+_id + "_"+_var+".root";
  TString  input_filepath = getenv("PLOT_PATH");
  input_filepath = input_filepath + "/Run2Legacy_v4/Limit/Shape/"+ year + "/" + flavour + "_"+ _sr + "/"+ input_rootfile;

  
  
  TFile* file = TFile::Open((input_filepath).Data());	  
  if(CheckFile(file) > 0) return;
  
  TH1* this_hist_sig = GetHist(file,"signal");

  TH1* this_hist_cf;
  bool isee =  (flavour == "EE");
  if(isee) {
    this_hist_cf = GetHist(file,"cf");

  }
  TH1* this_hist_prompt = GetHist(file,"prompt");
  TH1* this_hist_fake = GetHist(file,"fake");
 
  double nsig = double(this_hist_sig->Integral());
  double nprompt = double(this_hist_prompt->Integral());
  double nfake = double(this_hist_fake->Integral());
  
  double scale = 100.;
  
  cout << mass<< " " << nfake << " " << nprompt << " " << scale*nsig << endl;
  this_hist_prompt->SetFillColor(kSpring-1);
  this_hist_prompt->SetLineColor(kSpring-1);
  this_hist_fake->SetFillColor(870);
  this_hist_fake->SetLineColor(870);
  if(isee){
    this_hist_cf->SetFillColor(kBlue-2);
    this_hist_cf->SetLineColor(kBlue-2);
  
  }
  
  
  
  THStack *hs = new THStack(_sr+"_"+flavour +"_highmass_nevent_HNtypeI_JA_"+flavour+"_" + _id,"");
  
  this_hist_prompt->SetFillColor(kSpring-1);
  this_hist_fake->SetFillColor(870);
  
  hs->Add(this_hist_prompt);
  hs->Add(this_hist_fake);
  if(isee)hs->Add(this_hist_cf);
  
  
  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 900, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  c_SOnly->SetLogy();

  

  this_hist_sig->GetYaxis()->SetTitle("Events" );
  this_hist_sig->SetLineColor(kRed);
  this_hist_sig->SetLineWidth(4.);
  this_hist_sig->GetYaxis()->SetRangeUser(0.05, 10000.);

  this_hist_sig->Draw("hist");
  
  TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/" + year + "/" + _sr+"/hist_highmass_var_HNtypeI_JA_"+flavour+"_"+_id+"_"+_var+".pdf";
  if(outpath!="") save_sg=outpath;
  
  hs->Draw("histsame");
  this_hist_sig->Draw("histsame");
   

  TLatex latex_CMSPriliminary, latex_Lumi, latex_title;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_title.SetNDC();

  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.SetTextFont(42);
  TString lumi = "36.5";
  if(year=="2017") lumi = "41.5";
  if(year=="2018") lumi = "59.9";
  if(year=="Combined") lumi = "137.9";

  latex_title.DrawLatex(0.64, 0.64, flavour + " " + _sr);


  latex_Lumi.DrawLatex(0.735, 0.96, lumi+" fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  //latex_title.DrawLatex(0.25, 0.84, "#font[41]{95% CL upper limit}");
  //latex_title.SetTextSize(0.05);
  latex_title.DrawLatex(0.25, 0.96, "#font[62]{CMS}");

  gPad->RedrawAxis();
  
  TLegend* legendH;
  legendH = new TLegend(0.65, 0.75, 0.85, 0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextSize(0.03);
  legendH->SetBorderSize(0);
  legendH->SetTextFont(42);
  
  legendH->AddEntry(this_hist_sig, "m_{N} Bin GeV","l");
  legendH->AddEntry(this_hist_prompt,"Prompt","f");
  legendH->AddEntry(this_hist_fake,"Fake","f");
  if(isee)legendH->AddEntry(this_hist_cf,"CF","f");
  
  //AllLegendEntry(legend,this_hist,_id,"l");
  
  legendH->Draw();
  cout << "Make stack4" << endl;
  
  //dummy->Draw("histsame");
  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + year);
  MakeDir(ENV_PLOT_PATH+FLATVERSION+"/" + year+  "/" + _sr);

  c_SOnly->SaveAs(save_sg,".pdf");	  
  delete hs;
  delete this_hist_sig;
  delete this_hist_fake;
  delete this_hist_prompt;
  
  file->Close();
  
  
}
