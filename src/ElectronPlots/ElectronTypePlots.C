#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void ElectronTypePlots(TString year = "2016"){
  

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
  vector<TString> vars = GetListFromKeys(file_mc,"FillEventFullType","TH2D");

  
  for (auto var: vars){
    
    TString canvasname= var;
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

    TString s_mc = "FillEventFullType/"+var;


    TH2D* hn_dummy          =  (TH2D*)file_mc->Get(s_mc);
    hn_dummy->GetXaxis()->SetTitle("lepton_{1}");
    hn_dummy->GetYaxis()->SetTitle("lepton_{2}");

    double total_hist(0);

    for(unsigned int ix =0; ix  < hn_dummy->GetNbinsX() +1 ; ix++){
      for(unsigned int iy =0; iy  < hn_dummy->GetNbinsY() +1 ; iy++){
	total_hist+= hn_dummy->GetBinContent(ix,iy);
      }
    }

    for(unsigned int ix =0; ix  < hn_dummy->GetNbinsX() +1 ; ix++){
      for(unsigned int iy =0; iy  < hn_dummy->GetNbinsY() +1 ; iy++){
    	
	hn_dummy->SetBinContent(ix,iy,hn_dummy->GetBinContent(ix,iy)/total_hist);
	//	hn_dummy->SetBinContent(128, -2.);
      }
    }

    c1->cd();

    
    hn_dummy->Draw("colztext");


    
    TString save_sg= output + "/FullType"+var+ "_"+year+".pdf";
    
    c1->SaveAs(save_sg);

    delete c1;
  }
  
  file_mc->Close();
  
  delete file_mc;
    
  return;
}
