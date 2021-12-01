#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "TPad.h"

vector<TString> ListVar(TString year);

void ElectronPlotsTypeDefault(TString label, TString var, TString cutdir, TString year , int mode, bool logx, bool logy);

void ElectronPlotsType(){

  vector<TString> list = ListVar("2016");
  int nplots=0;
  for(auto var : list){
    if(!var.Contains("SS")) continue;
    if(var.Contains("SR1")) continue;
    if(var.Contains("SR2")) continue;

    TString cutdir = GetCutDir(var);

    ElectronPlotsTypeDefault("SS_",var,cutdir,"2016",1,false,false); // non log y  : mode 1 = sig vs All bkg
    ElectronPlotsTypeDefault("SS_",var,cutdir,"2016",1,true,true);  // log Y      : mode 1 = sig vs All bkg
  }

}

vector<TString> ListVar(TString year){

  TString analysername="HNtypeI_Dilepton";
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString skim="SkimTree_SSNonIso";
  TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNtypeI_Dilepton_"+skim+"_MC.root";

  TFile * file_mc = new TFile((mc_path).Data());


  vector<TString> vars = GetListFromKeys(file_mc,"NonFakeel","TH1D");


  return vars;
}

void ElectronPlotsTypeDefault(TString label, TString var, TString cutdir,TString year = "-1", int mode=0, bool logx=true, bool logy=true){

  bool m_debug=true;
  
  TString s_mode = "";
  if (mode == 1) s_mode = "sumbkg";

  cout << "Running ElectronPlotsTypeDefault : " << label << " , variable " << var << " year = " << year  << " mode = " << s_mode << " log x.y = " << logx << "," << logy << endl;

  
  
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

  TString sig_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNtypeI_Dilepton_DYTypeI_SS_EE_M100.root";
  TString sig_path1000 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNtypeI_Dilepton_DYTypeI_SS_EE_M1000.root";
  TFile * file_sig100 = new TFile((sig_path).Data());
  TFile * file_sig1000 = new TFile((sig_path1000).Data());

  if(CheckFile(file_sig100) > 0)  return;
  if(CheckFile(file_sig1000) > 0)  return; 
  
  
  int nplot=0;
  int rebin_number=1;

  // create canvas

  TString canvasname= var + s_mode;
  Message("Creating canvas "+canvasname, m_debug);  

  TCanvas *c1 = new TCanvas(var,var,100,500,1400,900);

  if(mode==1) c1->Divide(1,2);
  if(mode==0)c1->Divide(2,4);
  
  c1->cd(1);
  if(logy||logx){   TPad* p1 = (TPad*)(c1->cd(1));  if(logx)p1->SetLogx(); if(logy)p1->SetLogy(); }
  
  
  Message("Setting up histograms" , m_debug);
  
  TH1* hn_dummy          =  (TH1*)GetHist(file_mc,"NonFakeel/"+var)->Clone("DUMMY"+canvasname);

  Message("Rebinning histograms" , m_debug);
  int nrbin = 1;
  if (hn_dummy->GetNbinsX() > 100){
    rebin_number = 2;
    nrbin = 2;
  }
  Message("Rebinning histograms: " + TString(rebin_number) , m_debug);

  bool notrebin=true;
  while(notrebin){
    int nbins = hn_dummy->GetNbinsX();
    while(nbins%nrbin) {
      cout << "Nbins in histogram " << nbins << " nrbin= " << nrbin << endl;
      nrbin++;
    }
    if(nrbin >= rebin_number ) notrebin = false;
  }
  
  hn_dummy->Rebin(nrbin);
  vector<double> newrbins;
  if(mode==1)newrbins    = GetLowStatRebin(hn_dummy, false);
  
  TH1* hn_nonfake        = GetHistFull(newrbins, file_mc,"NonFakeel/"+var, kRed, 1);
  TH1* hn_nonfake_sig100        = GetHistFull(newrbins, file_sig100,"NonFakeel/"+var, kGreen, 1);
  TH1* hn_nonfake_sig1000        = GetHistFull(newrbins, file_sig1000,"NonFakeel/"+var, kViolet, 1);
  TH1* hn_nonfake_cf     = GetHistFull(newrbins,file_mc,"NonFake_CFel/"+var, kGreen, 1);
  TH1* hn_nonfake_conv   = GetHistFull(newrbins,file_mc,"NonFake_Convel/"+var, kGreen, 1);
  TH1* hn_nonfake_cfconv = GetHistFull(newrbins,file_mc,"NonFake_Conv_CFel/"+var, kGreen, 1);
  
  TH1* hn_fake           = GetHistFull(newrbins,file_mc,"Fakeel/"+var, kGreen, 1,7);
  TH1* hn_fake_conv      = GetHistFull(newrbins,file_mc,"Fake_Convel/"+var, kGreen, 1);
  

  Message("Adding hitoragms to map depending on mode" , m_debug);

  map<TString, double> map_histint;
  if(mode == 0){
    hn_fake_conv->Add(hn_nonfake_conv);
    hn_nonfake_cf->Add(hn_nonfake_cfconv);
    
    map_histint["hn_nonfake"]         = hn_nonfake->Integral();
    map_histint["hn_nonfake_sig100"]  = hn_nonfake_sig100->Integral();
    map_histint["hn_nonfake_sig1000"] = hn_nonfake_sig1000->Integral();
    map_histint["hn_nonfake_cf"]      = hn_nonfake_cf->Integral();
    map_histint["hn_fake"]            = hn_fake->Integral();
    map_histint["hn_fake_conv"]       = hn_fake_conv->Integral();
    NormHist(hn_nonfake);
    NormHist(hn_nonfake_sig100);
    NormHist(hn_nonfake_sig1000);
    NormHist(hn_nonfake_cf);
    NormHist(hn_fake);
    NormHist(hn_fake_conv);
    
  }
  
  else if (mode == 1){
    hn_nonfake->Add(hn_fake);
    hn_nonfake->Add(hn_fake_conv);
    hn_nonfake->Add(hn_nonfake_cf);
    hn_nonfake->Add(hn_nonfake_conv);
    hn_nonfake->Add(hn_nonfake_cfconv);
    map_histint["hn_nonfake"]         = hn_nonfake->Integral();
    map_histint["hn_nonfake_sig100"]  = hn_nonfake_sig100->Integral();
    map_histint["hn_nonfake_sig1000"] = hn_nonfake_sig1000->Integral();
    NormHist(hn_nonfake);
    NormHist(hn_nonfake_sig100);
    NormHist(hn_nonfake_sig1000);
    
  }
  
  map<TString, double>::iterator mit;
  
  double ymin = (logy) ?  0.01 : 0;
  double xmin = (logx) ?  0.01 : 0;
  

  Message("Drawing Histogram" , m_debug);
  
  if(mode==1){
    
    if(hn_nonfake_sig100->GetMaximum() > hn_nonfake->GetMaximum()) hn_nonfake->GetYaxis()->SetRangeUser(ymin, 1.7*hn_nonfake_sig100->GetMaximum());
    else if(hn_nonfake_sig1000->GetMaximum() > hn_nonfake->GetMaximum()) hn_nonfake->GetYaxis()->SetRangeUser(ymin, 1.7*hn_nonfake_sig1000->GetMaximum());
    else hn_nonfake->GetYaxis()->SetRangeUser(ymin, 1.7*hn_nonfake->GetMaximum());
    
    
    hn_nonfake->Draw("hist");
    hn_nonfake_sig100->Draw("histsame");
    hn_nonfake_sig1000->Draw("histsame");
    
    map<TString, double>::const_iterator mpos100 = map_histint.find("hn_nonfake_sig100");
    map<TString, double>::const_iterator mpos1000 = map_histint.find("hn_nonfake_sig1000");
    map<TString, double>::const_iterator mpos = map_histint.find("hn_nonfake");
    
    
    TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
    char strs[80];
    sprintf(strs,"%6.1e", mpos->second);legend->AddEntry(hn_nonfake,"Background:        "+TString(strs),"l");
    sprintf(strs,"%6.1e", mpos100->second);legend->AddEntry(hn_nonfake_sig100,"Signal   (100  GeV) : "+TString(strs),"l");
    sprintf(strs,"%6.1e", mpos1000->second);legend->AddEntry(hn_nonfake_sig1000,"Signal (1000 GeV) : "+TString(strs),"l");
    legend->Draw();
    DrawLatexWithLabel(year,year,0.25,0.88);
    
    
    c1->Update();
    c1->cd(2);
    if(logy||logx){   TPad* p1 = (TPad*)(c1->cd(2));  if(logx)p1->SetLogx(); if(logy)p1->SetLogy(); }
    
    
    TH1* hn_nonfake_sig100_clone = (TH1*)hn_nonfake_sig100->Clone("hn_nonfake_sig100_clone"+var);
    TH1* hn_nonfake_sig1000_clone = (TH1*)hn_nonfake_sig1000->Clone("hn_nonfake_sig1000_clone"+var);
    TH1* hn_nonfake_clone = (TH1*)hn_nonfake->Clone("hn_nonfake_clone"+var);    
    GetEfficiencyHist(hn_nonfake_sig100_clone,hn_nonfake_sig100,cutdir);
    GetEfficiencyHist(hn_nonfake_sig1000_clone,hn_nonfake_sig1000,cutdir);
    GetEfficiencyHist(hn_nonfake_clone,hn_nonfake,cutdir);
    
    double binvalue_sig100_090= GetBinValue(0.9, hn_nonfake_sig100_clone,cutdir);
    double binvalue_sig1000_090= GetBinValue(0.9, hn_nonfake_sig1000_clone,cutdir);
    double binvalue_bkg_090= GetBinValue(0.9, hn_nonfake_clone,cutdir);
    double binvalue_sig100_100= GetBinValue(1., hn_nonfake_sig100_clone,cutdir);
    double binvalue_sig1000_100= GetBinValue(1., hn_nonfake_sig1000_clone,cutdir);
    double binvalue_bkg_100= GetBinValue(1., hn_nonfake_clone,cutdir);
    //      hn_nonfake_clone->GetYaxis()->SetRangeUser(0.01, 1.2);
    hn_nonfake_clone->Draw("hist");
    hn_nonfake_sig100_clone->Draw("histsame");
    hn_nonfake_sig1000_clone->Draw("histsame");
    
    
    char strs_binvalue09[80];
    char strs_binvalue10[80];
    sprintf(strs_binvalue09,"%6.2e", binvalue_sig100_090)	;
    sprintf(strs_binvalue10,"%6.2e", binvalue_sig100_100)	;
    DrawLatexLabel("Signal 100 : " +TString(strs_binvalue09) + " - " + TString(strs_binvalue10)  ,0.25,0.88);
    
    
  }
  if(mode==0){
    hn_nonfake->Draw("hist");
    hn_nonfake_sig100->Draw("histsame");
    hn_nonfake_sig1000->Draw("histsame");
    
    if(1){
      map<TString, double>::const_iterator mpos100 = map_histint.find("hn_nonfake_sig100");
      map<TString, double>::const_iterator mpos1000 = map_histint.find("hn_nonfake_sig1000");
      map<TString, double>::const_iterator mpos = map_histint.find("hn_nonfake");
      
      
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_nonfake_sig100,"Signal (100 GeV) : "+TString(std::to_string(round(mpos100->second)))  ,"l");
      legend->AddEntry(hn_nonfake_sig1000,"Signal (1000 GeV) : "+TString(std::to_string(mpos1000->second)),"l");
      char strs[80];
      sprintf(strs,"%6.3e", mpos->second);
      legend->AddEntry(hn_nonfake,"Prompt (W/Z)"+TString(strs),"l");
      legend->Draw();
      DrawLatexWithLabel(year,year,0.25,0.88);
      
    }
    
    
    c1->cd(3);
    if(logy||logx){   TPad* p1 = (TPad*)(c1->cd(3));  if(logx)p1->SetLogx(); if(logy)p1->SetLogy(); }
    
    
    
    //hn_type3->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_type3->GetMaximum()})*1.1);
    hn_nonfake->Draw("hist");
    hn_nonfake_cf->Draw("histsame");
    
    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_nonfake,"Prompt","l");
      map<TString, double>::const_iterator mpos = map_histint.find("hn_nonfake_cf");
      
      legend->AddEntry(hn_nonfake_cf,"Charge flip : "+TString(std::to_string(mpos->second)),"l");
      legend->Draw();
      DrawLatexWithLabel(year,year,0.25,0.88);
      
    }
    
    c1->Update();
    c1->cd(4);
    
    if(logy||logx){   TPad* p1 = (TPad*)(c1->cd(4));  if(logx)p1->SetLogx(); if(logy)p1->SetLogy(); }
    
    
    //hn_typem1->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem1->GetMaximum()})*1.1);
    hn_nonfake->Draw("hist");
    hn_fake->Draw("histsame");
    
    
    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_nonfake,"Prompt","l");
      map<TString, double>::const_iterator mpos = map_histint.find("hn_fake");
      legend->AddEntry(hn_fake,"Fake : "+TString(std::to_string(mpos->second)),"l");
      legend->Draw();
      DrawLatexWithLabel(year,year,0.25,0.88);
      
    }
    
    c1->Update();
    c1->cd(5);
    if(logy||logx){   TPad* p1 = (TPad*)(c1->cd(5));  if(logx)p1->SetLogx(); if(logy)p1->SetLogy(); }
    
    
    
    //hn_typem2->GetYaxis()->SetRngeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem2->GetMaximum()})*1.1);
    hn_nonfake->Draw("hist");
    hn_fake_conv->Draw("histsame");
    
    
    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_nonfake,"Prompt","l");
      map<TString, double>::const_iterator mpos = map_histint.find("hn_fake_conv");
      legend->AddEntry(hn_fake_conv,"Conv.: "+TString(std::to_string(mpos->second)) ,"l");
      legend->Draw();
      DrawLatexWithLabel(year,year,0.25,0.88);
      
    }
  }

  Message("Setting TDR style" , m_debug);

  c1->Update();
  
  setTDRStyle();

  Message("Saving historams" , m_debug);
  
  TString save_sg= output + "/"+label+"ByBkg_"+var+ "_"+year+s_mode;
  if(logx)save_sg+= "_logx";
  if(logy)save_sg+= "_logy";
  save_sg+= ".pdf";
  
  c1->Update();
  c1->SaveAs(save_sg);

  Message("Deleting TCanvas pointers" , m_debug);
  delete c1;

  Message("Deleting TFile pointers" , m_debug);

  file_mc->Close();
  
  delete file_mc;

  file_sig100->Close();
  delete file_sig100;
  file_sig1000->Close();
  delete file_sig1000;
  

  cout << "End of " << var << " loop " << endl;
  return;
}
