#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "TPad.h"


void ElectronPlotsByTypeDefault(TString year , bool logy);

void ElectronPlotsByType(){

  ElectronPlotsByTypeDefault("2016",true);
  ElectronPlotsByTypeDefault("2016",false);
}

void ElectronPlotsByTypeDefault(TString year = "2016", bool logy=true){
  

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
  TFile * file_sig = new TFile((sig_path).Data());
  TFile * file_sig1000 = new TFile((sig_path1000).Data());

  if(CheckFile(file_sig) > 0)  return;
  if(CheckFile(file_sig1000) > 0)  return; 


  
  // canvas for hists
  vector<TString> vars = GetListFromKeys(file_mc,"Type1el","TH1D");

  int nplot=0;
  for (auto var: vars){

    if(var.Contains("SS")) continue;
    if(var.Contains("OS")) continue;

    if (nplot > 1 ) return;

    TString canvasname= var;

    TCanvas *c1 = new TCanvas(var,var,100,500,1400,900);

    c1->Divide(3,3);
    c1->cd(1);
    if(logy){   TPad* p1 = (TPad*)(c1->cd(1));  p1->SetLogy();}

    TString s_type1 = "Type1el/"+var;
    TString s_type2 = "Type2el/"+var;
    TString s_type3 = "Type3el/"+var;
    TString s_type4 = "Type4el/"+var;
    TString s_type5 = "Type5el/"+var;

    TString s_typem1 = "TypeMinus1el/"+var;
    TString s_typem2 = "TypeMinus2el/"+var;
    TString s_typem3 = "TypeMinus3el/"+var;
    TString s_typem4 = "TypeMinus4el/"+var;
    TString s_typem5 = "TypeMinus5el/"+var;
    TString s_typem6 = "TypeMinus6el/"+var;
    
  

    // Get TH1 for each type

    TH1* hn_dummy          =  (TH1*)GetHist(file_mc,"Type1el/"+var)->Clone("DUMMY");
    hn_dummy->Rebin(2);
    vector<double> newrbins = GetLowStatRebin(hn_dummy);
    
    
    Double_t array_newrbins[newrbins.size()];
    
    TH1* hn_type1        = GetHistFull(newrbins, file_mc,s_type1, kRed, 1.);
    TH1* hn_type2        = GetHistFull(newrbins, file_sig,s_type2,  kBlue, 1.,2.);
    TH1* hn_type2b        = GetHistFull(newrbins,file_sig1000,s_type2, kOrange, 1.,2.);
    TH1* hn_type3        = GetHistFull(newrbins, file_mc, s_type3, kGreen, 1.);
    TH1* hn_type4        = GetHistFull(newrbins, file_mc, s_type4, kBlue, 1.);
    TH1* hn_type5        = GetHistFull(newrbins, file_mc, s_type5, kCyan, 1.);
    hn_type4->Add(hn_type5);
    
    TH1* hn_typem1           = GetHistFull(newrbins,file_mc,s_typem1, kOrange, 1);
    TH1* hn_typem2           = GetHistFull(newrbins,file_mc,s_typem2, kBlack, 1);
    TH1* hn_typem3           = GetHistFull(newrbins,file_mc,s_typem3, kGreen, 1);
    TH1* hn_typem4           = GetHistFull(newrbins,file_mc,s_typem4, kBlue, 1);
    TH1* hn_typem5           = GetHistFull(newrbins,file_mc,s_typem5, kCyan, 1.);
    TH1* hn_typem6           = GetHistFull(newrbins,file_mc,s_typem6, kViolet, 1.);



    //    PrintBins("hn_type1",hn_type1);
    //PrintBins("hn_type2",hn_type2);
    //PrintBins("hn_type3 rebin",hn_type3);
    //PrintBins("hn_type4",hn_type4);
    //PrintBins("hn_type5",hn_type5);
    //PrintBins("hn_typem1",hn_typem1);
    //PrintBins("hn_typem2",hn_typem2);
    //PrintBins("hn_typem3",hn_typem3);
    //PrintBins("hn_typem4",hn_typem4);
    //PrintBins("hn_typem5",hn_typem5);
    //PrintBins("hn_typem6",hn_typem6);
    

    NormHist(hn_type1);
    NormHist(hn_type2);
    NormHist(hn_type2b);
    NormHist(hn_type3);
    NormHist(hn_type4);
    //    NormHist(hn_type5);

    NormHist(hn_typem1);
    NormHist(hn_typem2);
    NormHist(hn_typem3);
    NormHist(hn_typem4);
    NormHist(hn_typem5);
    NormHist(hn_typem6);

    double ymin = (logy) ?  0.01 : 0;
    
    hn_type1->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_type2->GetMaximum(),hn_type2b->GetMaximum()})*1.1);
    hn_type1->Draw("hist");
    hn_type2->Draw("histsame");
    hn_type2b->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type2,"Signal (100 GeV)","l");
      legend->AddEntry(hn_type2b,"Signal (1000 GeV)","l");
      legend->AddEntry(hn_type1,"Prompt (W/Z)","l");
      legend->Draw();
      DrawLatexWithLabel(year,year,0.25,0.88);

    }
    c1->Update();
    c1->cd(2);
    if(logy){TPad* p2 = (TPad*)(c1->cd(2));  p2->SetLogy();}


    hn_type3->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_type3->GetMaximum()})*1.1);
    hn_type3->Draw("hist");
    hn_type1->Draw("histsame");


    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_type3,"Tau daughter","l");
      legend->Draw();
    }

    c1->Update();
    c1->cd(3);
    if(logy){TPad* p3 = (TPad*)(c1->cd(3));  p3->SetLogy();}

    hn_type4->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_type4->GetMaximum()})*1.1);
    hn_type4->Draw("hist");
    hn_type1->Draw("histsame");


    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_type4,"Int Conv from EW+HS","l");
      legend->Draw();
    }
    
    c1->Update();
    c1->cd(4);

    if(logy){TPad* p4 = (TPad*)(c1->cd(4));  p4->SetLogy();}

    hn_typem1->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem1->GetMaximum()})*1.1);
    hn_typem1->Draw("hist");
    hn_type1->Draw("histsame");

    
    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem1,"Unmatched","l");
      legend->Draw();
    }

    c1->Update();
    c1->cd(5);
    if(logy){TPad* p5 = (TPad*)(c1->cd(5));  p5->SetLogy();}

    
    hn_typem2->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem2->GetMaximum()})*1.1);
    hn_typem2->Draw("hist");
    hn_type1->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem2,"Hadron daughter","l");
      legend->Draw();
    }

    c1->Update();
    c1->cd(6);
    if(logy){TPad* p6 = (TPad*)(c1->cd(6));  p6->SetLogy();}

    
    hn_typem3->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem3->GetMaximum()})*1.1);
    hn_typem3->Draw("hist");
    hn_type1->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem3,"Tau daughter had.","l");
      legend->Draw();
    }

    c1->Update();
    c1->cd(7);
    if(logy){    TPad* p7 = (TPad*)(c1->cd(7));  p7->SetLogy();}

    
    hn_typem4->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem4->GetMaximum()})*1.1);
    hn_typem4->Draw("hist");
    hn_type1->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem4,"Int conv had.","l");
      legend->Draw();
    }


    c1->Update();
    c1->cd(8);
    if(logy){    TPad* p8 = (TPad*)(c1->cd(8));  p8->SetLogy();}

    hn_typem5->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem5->GetMaximum()})*1.1);
    hn_typem5->Draw("hist");
    hn_type1->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem5,"Ext conv from hs","l");
      legend->Draw();
    }

    c1->Update();
    c1->cd(9);
    if(logy){TPad* p9 = (TPad*)(c1->cd(9));  p9->SetLogy();}

    hn_typem6->GetYaxis()->SetRangeUser(ymin, GetMax({hn_type1->GetMaximum(), hn_typem6->GetMaximum()})*1.1);
    hn_typem6->Draw("hist");
    hn_type1->Draw("histsame");

    if(1){
      TLegend *legend = MakeLegend(0.65, 0.75, 0.9, 0.92);
      legend->AddEntry(hn_type1,"Prompt","l");
      legend->AddEntry(hn_typem6,"Ext conv from EW","l");
      legend->Draw();
    }

    
    setTDRStyle();
    
    TString save_sg= output + "/ByType_"+var+ "_"+year+".pdf";
    if(logy)save_sg= output + "/ByType_"+var+ "_"+year+"_logy.pdf";

    c1->Update();
    c1->SaveAs(save_sg);

    delete c1;

    //    nplot++;
  }
  
  file_mc->Close();
  
  delete file_mc;

  file_sig->Close();
  delete file_sig;
  
  return;
}
