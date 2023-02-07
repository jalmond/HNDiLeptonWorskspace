#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void SignalRegionPlot(){
  
  vector<TString> eras =  {"2017"};
  
  for (auto year : eras){
      
    TString skim="";
    // check which pc is running script to setup local paths
    TString s_hostname = GetHostname();
    
    TString analysername="HNL_SignalRegionPlotter";
    
    // local path names
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    TString ENV_PLOT_PATH = getenv("PLOT_PATH");
    TString FLATVERSION = getenv("FLATVERSION");
    
    
    MakeDir(ENV_PLOT_PATH + FLATVERSION);
    TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
    TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
    
    MakeDir(output);
    output+="/SignalRegionPlot/";
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
      
    
    TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_Bkg.root";
    
    TFile * file_bkg = new TFile((mc_path).Data());
    
    if(CheckFile(file_bkg) > 0) {
      continue;
    }
    
    
    TString sr_hist= "LimitInputBDT/HNL_UL/100/FillEventCutflow/MuonSR";
    
    
    TString sig_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNL_SignalRegionPlotter_DYTypeI_DF_M100_private.root";

    TFile * file_sig = new TFile((sig_path).Data());
    
    if(CheckFile(file_sig) > 0) {
      continue;
    }
    
    cout << sr_hist << endl;
    TH1* hn_sig        = GetHist(file_sig,sr_hist);
    hn_sig->GetYaxis()->SetTitle("Events / SR bin");
    if (!hn_sig) continue;
    
    TH1* hn_bkg        = GetHist(file_bkg,sr_hist);
    if (!hn_bkg) continue;

    TString canvasname= sr_hist+"100BDT";

    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
    
    c1->cd();
    hn_sig->Scale(hn_bkg->Integral() / hn_sig->Integral());

    hn_sig->GetYaxis()->SetRangeUser(0.8, hn_sig->GetMaximum()*1.5);
    hn_sig->SetLineColor(kRed);
    hn_sig->Draw("hist");

    hn_bkg->SetFillColor(kOrange);
    hn_bkg->Draw("histsame");
    hn_sig->Draw("histsame");
    TString binlabel="Muon Channel";
    DrawLatexWithLabel(year,binlabel,0.25,0.68);

    TLegend *legend = MakeLegend(0.25, 0.75, 0.5, 0.92);
    legend->AddEntry(hn_sig,"mN=100 GeV","l");
    legend->AddEntry(hn_bkg,"Sum Bkg","f");
    legend->Draw();


    TString save_pdf= output + "/LimitMuonBDT100_"+year+"_.pdf";
    TString save_png= output + "/LimitMuonBDT100_"+year+"_.png";
    
    c1->SetLogy();
    c1->SaveAs(save_pdf);
    c1->SaveAs(save_png);

    //system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/'");

    system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/'");

    system("scp " + output+"/LimitMuonBDT100_"+year+"_.pdf jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/");
    system("scp " + output+"/LimitMuonBDT100_"+year+"_.png jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalRegionLimitInput/");

    cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/SignalRegionLimitInput/" << endl;

    delete c1;


    delete file_sig;
    
    file_bkg->Close();
    
    delete file_bkg;
    
    
  }
    

  return;
}

