#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void ElectronPlots(TString year = "2016"){
  

  TString skim="SkimTree_SSNonIso";
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  //HNtypeI_Dilepton_SkimTree_SSNonIso_DYJets.root
  TString analysername="HNtypeI_Dilepton";

  vector<TString> code_names= {"HNtypeI_Dilepton"};

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
  output+="/ElectronPlots/";
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
    

  // MC file is list of hadd files for BKG
  // - DY
  // - TT
  
  TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNtypeI_Dilepton_"+skim+"_MC.root";

  TFile * file_mc = new TFile((mc_path).Data());

  if(CheckFile(file_mc) > 0)  return;
  

  
  // canvas for hists
  vector<TString> vars = GetListFromKeys(file_mc,"NonFakeel","TH1D");

  
  for (auto var: vars){
    
    TString canvasname= var;
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
    c1->SetLogy();

    TString s_fake = "Fakeel/"+var;
    TString s_fake_conv = "Fake_Convel/"+var;

    // Get TH1 for each type

    TH1* hn_dummy          =  (TH1*)GetHist(file_mc,"NonFakeel/"+var)->Clone("DUMMY");
    vector<double> newrbins = GetLowStatRebin(hn_dummy);
    Double_t array_newrbins[newrbins.size()];
    
    TH1* hn_nonfake        = GetHistFull(newrbins, file_mc,"NonFakeel/"+var, kRed, 3.);
    TH1* hn_nonfake_cf     = GetHistFull(newrbins,file_mc,"NonFake_CFel/"+var, kGreen, 3.);
    TH1* hn_nonfake_conv   = GetHistFull(newrbins,file_mc,"NonFake_Convel/"+var, kBlue, 3.);
    TH1* hn_nonfake_cfconv = GetHistFull(newrbins,file_mc,"NonFake_Conv_CFel/"+var, kCyan, 3.);
    
    TH1* hn_fake           = GetHistFull(newrbins,file_mc,"Fakeel/"+var, kRed, 3.,7);
    TH1* hn_fake_conv      = GetHistFull(newrbins,file_mc,"Fake_Convel/"+var, kBlue, 3.,7);
    // add conversions for fake and non fake due to stats
    hn_fake_conv->Add(hn_nonfake_conv);
    

    //PrintBins("hn_nonfake_rb",hn_nonfake_rb);

    c1->cd();

    NormHist(hn_nonfake);
    NormHist(hn_nonfake_cf);
    NormHist(hn_nonfake_cfconv);
    NormHist(hn_fake);
    NormHist(hn_fake_conv);

    
    hn_nonfake->Draw("hist");
    hn_nonfake_cf->Draw("histsame");
    hn_fake->Draw("histsame");
    hn_fake_conv->Draw("histsame");

    TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
    legend->AddEntry(hn_nonfake,"NonFake El","l");
    legend->AddEntry(hn_fake,"Fake El","l");
    legend->AddEntry(hn_nonfake_cf, "CF El","l");
    legend->AddEntry(hn_fake_conv,"Convertion el","l");
    
    legend->Draw();
    
    setTDRStyle();
    
    TString save_sg= output + "/"+var+ "_"+year+".pdf";
    
    c1->SaveAs(save_sg);

    delete c1;
  }
  
  file_mc->Close();
  
  delete file_mc;
    
  return;
}
