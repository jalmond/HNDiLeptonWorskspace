#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(TString Era,TString DateTag,HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString DateTag,TString channel, TString reg,TString LabelForOutPut);

void PlotClosureConv(){

  HNLPlotter Plotter("ConvStudy");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  vector<TString> Eras = {"2017","2018"};

  //cout << 'List 1 = ["WG","TG","ZG","DYJets_MG."]' << endl;
  //  cout << 'List 4 =["WG","TG","ZG","MiNNLO","WJetsToLNu_HT"]' << endl;

  for(auto era : Eras) {
    TString year = (era.Contains("16")) ? "2016" : era;

    RunClosure(Plotter, "HNL_ULID_"+year, era, "May18", "MuMuMu","HNL_ZG_ThreeLepton_CR","ConvCheck");
    RunClosure(Plotter, "HNL_ULID_"+year, era, "May18", "EEE","HNL_ZG_ThreeLepton_CR","ConvCheck");
    RunClosure(Plotter, "HNL_ULID_"+year, era, "May18", "EMuL","HNL_ZG_ThreeLepton_CR","ConvCheck");
    
  }
  
}

void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString  DateTag, TString channel, TString reg, TString LabelForOutPut){
  
  cout << " " << endl;
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");


  TString path0= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_ControlRegion_Plotter/May12/"+Era+"/SSMultiLep/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_Conv.root";

  TString path1= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_ControlRegion_Plotter/"+DateTag+"/"+Era+"/SSMultiLep/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ConvV1.root";
  TString path4= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_ControlRegion_Plotter/"+DateTag+"/"+Era+"/SSMultiLep/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ConvV4.root";
  TString pathG1= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_ControlRegion_Plotter/"+DateTag+"/"+Era+"/SSMultiLep/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ConvGENTV1.root";
  TString pathG4= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_ControlRegion_Plotter/"+DateTag+"/"+Era+"/SSMultiLep/HNL_ControlRegion_Plotter_SkimTree_HNMultiLepBDT_ConvGENTV4.root";
    
  vector<double> vrebin = {1.};
  TH1D *hist_Conv0      = Plotter.ConstructHist(path0,""+reg+"/HNL_ULID/"+channel+"/Mass/M_ll",vrebin);

  TH1D *hist_Conv1      = Plotter.ConstructHist(path1,""+reg+"/HNL_ULID/"+channel+"/Mass/M_ll",vrebin);
  TH1D *hist_Conv4      = Plotter.ConstructHist(path4,""+reg+"/HNL_ULID/"+channel+"/Mass/M_ll",vrebin);


  TH1D *hist_ConvG1      = Plotter.ConstructHist(pathG1,""+reg+"/HNL_ULID/"+channel+"/Mass/M_ll",vrebin);
  TH1D *hist_ConvG4      = Plotter.ConstructHist(pathG4,""+reg+"/HNL_ULID/"+channel+"/Mass/M_ll",vrebin);

  cout << "Era = " << Era  << " channel = " << channel << " region = " << reg<< endl;
  cout << "hist_Con May12 int = " << hist_Conv0->Integral() << endl;

  cout << "hist_Conv1 int = " << hist_Conv1->Integral() << endl;
  cout << "hist_Conv4 int = " << hist_Conv4->Integral() << endl;
  
  cout << "hist_Conv1 [GENT] int = " << hist_ConvG1->Integral() << endl;
  cout << "hist_Conv4 [GENT] int = " << hist_ConvG4->Integral() << endl;

  return;
  
  SaveHistogram(Era,DateTag, Plotter,{hist_Conv1,hist_Conv4,hist_ConvG1,hist_ConvG4}, {"1","4","G1","G4"}, "Conversion_"+Era, LabelForOutPut, {""});
  

  return;
}

void SaveHistogram(TString Era,TString DateTag,HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.7, 0.93, 0.85);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();

  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

  if(plotter.SetLogY)c1->SetLogy();
  //  canvas_margin(c1);
  canvas_margin(c1, c1_up, c1_down);

  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();


  TH1D *hist_empty= (TH1D*)hist_default->Clone();

  hist_empty->SetName("DUMMY_FOR_AXIS");

  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();

  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  for(int i = 0 ; i < 3; i++) {
    if(hists[i]->GetMaximum() > YmaxScale) YmaxScale = hists[i]->GetMaximum()*1.5;
  }
  hist_axis(hist_empty, hist_default);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale*1.2);

  //  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);
  hist_empty->SetLineColor(kBlack);
  hist_empty->Draw("histsame");

  //  lg->AddEntry(gr_data, legname[0],"lp");


  for(int i=1 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  latex_Lumi.SetTextSize(plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);
  if(Era=="2016a")latex_Lumi.DrawLatex(0.72, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(Era=="2016b")latex_Lumi.DrawLatex(0.72, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(Era=="2016") latex_Lumi.DrawLatex(0.72, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(Era=="2017") latex_Lumi.DrawLatex(0.72, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(Era=="2018") latex_Lumi.DrawLatex(0.72, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(Era=="Run2") latex_Lumi.DrawLatex(0.72, 0.96, "137.9 fb^{-1} (13 TeV)");

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.85-0.05*il, Labels[il]);


  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
