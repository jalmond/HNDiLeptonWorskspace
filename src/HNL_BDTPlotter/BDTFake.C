#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void BDTFake(){
  
  vector<TString> eras =  {"2017"};

  
  for (auto year : eras){
    
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    
    TString analysername="HNL_SignalStudies";
    
    TString mc_path = "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalStudies/2017/HNL_SignalStudies_TTLJ_powheg.root";///data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_ObjectStudies/2017/HNL_ObjectStudies_TTLJ_powheg.root";
    
    TFile * file_bkg = new TFile((mc_path).Data());
    
    if(CheckFile(file_bkg) > 0) {
      continue;
    }
    

    // check which pc is running script to setup local paths
    TString s_hostname = GetHostname();
    
    // local path names
    
    TString ENV_PLOT_PATH = getenv("PLOT_PATH");
    TString FLATVERSION = getenv("FLATVERSION");
    
    
    MakeDir(ENV_PLOT_PATH + FLATVERSION);
    TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
    TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
    
    MakeDir(output);
    output+="/FakeBDT/";
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
    
    
    TString canvasname= "BDT";
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
    
    TString varCF = "Electrons/Fake_Mva_Electron_CF";
    TString varFake = "Electrons/Fake_Mva_Electron_Fake";
    TString varConv = "Electrons/Fake_Mva_Electron_Conv";
    TString varPrompt = "Electrons/Fake_Mva_Electron_Prompt";


    TH1* hCF             = GetHist(file_bkg,varCF);
    TH1* hPrompt         = GetHist(file_bkg,varPrompt);
    TH1* hFake         = GetHist(file_bkg,varFake);
    TH1* hConv         = GetHist(file_bkg,varConv);
    cout << hCF << " " << varCF << endl;

    cout << hCF->Integral() << endl;

    hCF->Scale(1./hCF->Integral());
    hPrompt->Scale(1./hPrompt->Integral());
    hFake->Scale(1./hFake->Integral());
    hConv->Scale(1./hConv->Integral());

    hCF->GetYaxis()->SetTitle("Events");
    hCF->GetYaxis()->SetRangeUser(0.001,0.75);
    hCF->GetXaxis()->SetRangeUser(-1.,1);
    hCF->SetLineColor(kRed);
    hCF->SetLineWidth(4);
    hPrompt->SetLineWidth(4);
    hFake->SetLineWidth(4);
    hConv->SetLineWidth(4);
    
    hPrompt->SetLineColor(kBlue);
    hFake->SetLineColor(kGreen);
    hConv->SetLineColor(kCyan);
    hCF->Draw("hist");

    hCF->Draw("histsame");
    hPrompt->Draw("histsame");
    hConv->Draw("histsame");
    hFake->Draw("histsame");

    TLegend *legend = MakeLegend(0.75, 0.55, 0.9, 0.85);
    legend->AddEntry(hCF,"TT CF","l");
    legend->AddEntry(hPrompt,"TT Prompt","l");
    legend->AddEntry(hFake,"TT Fake","l");
    legend->AddEntry(hConv,"TT Conv.","l");
    legend->Draw();
	    
    TString outpath = output + "/FakeBDT_"+year;

    TString save_pdf= outpath+".pdf";
    TString save_png= outpath+".png";
    

    c1->SetLogy();
    c1->SaveAs(save_pdf);
    c1->SaveAs(save_png);
    SaveAndCopyLXPLUS(c1,outpath,analysername,"BDTID");

    //system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlots/'");
    
    //system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlots/'");
    
    //ystem("scp " +save_pdf+" jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlots/");
    //system("scp " +save_png + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlots/");
    
    //cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/LeptonVarEffPlots/" << endl;
    
    file_bkg->Close();
    
    delete file_bkg;
  }
  
  
  return;
}

