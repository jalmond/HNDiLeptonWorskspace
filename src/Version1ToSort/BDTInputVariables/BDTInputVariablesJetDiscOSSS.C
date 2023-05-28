#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void BDTInputVariablesJetDiscOSSSs(TString era, double xmin, double xmax,double rebin, bool ismuon);

void BDTInputVariablesJetDiscOSSS(){
  BDTInputVariablesJetDiscOSSSs("2017", 0, 1, 20, true);
  BDTInputVariablesJetDiscOSSSs("2017", 0, 1, 20, false);
  BDTInputVariablesJetDiscOSSSs("2018", 0, 1, 20, true);
  BDTInputVariablesJetDiscOSSSs("2018", 0, 1, 20, false);
}


void BDTInputVariablesJetDiscOSSSs(TString era, double xmin, double xmax,double rebin, bool ismuon){


  if (ismuon) cout << "MUON " << endl;
  else cout << "ELECTRON " << endl;
  TString analysername="HNL_LeptonIDBDTStudies";  

  TCanvas* c1 = MakeCanvas("","");

  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);


  TString pathOSData= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data.root";
  TString pathSSData= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_HNMultiLep_data.root";

  TString pathOSMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MCAll.root";
  TString pathSSMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_HNMultiLep_MCAll.root";
  
  TFile* File_OSDatasample   = GetFile(pathOSData);
  TFile* File_SSDatasample   = GetFile(pathSSData);
  TFile* File_OSMCsample = GetFile(pathOSMC);
  TFile* File_SSMCsample = GetFile(pathSSMC);

  SetUpDir(analysername,era);
  TString output=GetOutPut(analysername,era);
  
  // Set Plotting style
  PlottingSetup();
  
      
  TString xlabel = "";
      
  c1->Draw();
  c1->cd();
  
  canvas_margin(c1, c1_up, c1_down);
      
  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();
  
  
  TString HistName = (ismuon) ? "CJ_JetDisc_DeepJet_Muon" : "CJ_JetDisc_DeepJet_Electron";

  
  //TString FullHistNameElectron="TopJets_TightMu/CJ_JetDisc_DeepJet_Electron_LooseMuE";
  TString FullHistName    = (ismuon) ? "TopJets_TightEl/CJ_JetDisc_DeepJet_Muon_LooseEMu" : "TopJets_TightMu/CJ_JetDisc_DeepJet_Electron_LooseMuE";

  TH1D* Hist_OS_El_DATA= (TH1D*)(File_OSDatasample->Get(FullHistName))->Clone(FullHistName+"DATA");
  TH1D* Hist_OS_El_MC= (TH1D*)(File_OSMCsample->Get(FullHistName))->Clone(FullHistName+"MC");
  
  TH1D* Hist_SS_El_DATA= (TH1D*)(File_SSDatasample->Get(FullHistName))->Clone(FullHistName+"DATA");
  TH1D* Hist_SS_El_MC= (TH1D*)(File_SSMCsample->Get(FullHistName))->Clone(FullHistName+"MC");

  Hist_OS_El_DATA->Rebin(rebin);  Hist_OS_El_MC->Rebin(rebin);
  Hist_SS_El_DATA->Rebin(rebin);  Hist_SS_El_MC->Rebin(rebin);

  Hist_OS_El_DATA->Scale(1./Hist_OS_El_DATA->Integral());  Hist_OS_El_MC->Scale(1./Hist_OS_El_MC->Integral());
  Hist_SS_El_DATA->Scale(1./Hist_SS_El_DATA->Integral());  Hist_SS_El_MC->Scale(1./Hist_SS_El_MC->Integral());

  //  Hist_OS_El_DATA->Add(Hist_SS_El_DATA);  Hist_OS_El_MC->Add(Hist_SS_El_MC);
  Hist_OS_El_DATA->GetXaxis()->SetRangeUser(xmin,xmax);

  /// Make Ratio Plots
  Hist_OS_El_DATA->GetXaxis()->SetTitle(xlabel);
  TH1D* Ratio_Hist   =  GetRatioHist(Hist_OS_El_MC,Hist_OS_El_DATA,"");
  Ratio_Hist->GetYaxis()->SetTitle("#frac{#epsilon_{Zmc}}{#epsilon_{Zdata}}");
  Ratio_Hist->GetYaxis()->SetNdivisions(6,5,0);
  
  gPad->Update();
  
  double axis_format_upper = 1.2;
  double Max = Hist_OS_El_MC->GetMaximum();
  if (Hist_OS_El_DATA->GetMaximum() > Max) Max = Hist_OS_El_DATA->GetMaximum() ;
  Max*= axis_format_upper;
  
  
  TH1D* Hist_MC_OverFlow= MakeOverflowBin(Hist_OS_El_MC,"OverFlow");
  Hist_MC_OverFlow->GetYaxis()->SetRangeUser(0.01, Max);
  hist_axis(Hist_MC_OverFlow);

  TH1D* Hist_DATA_OverFlow= MakeOverflowBin(Hist_OS_El_DATA,"OverFlow");
  

  FormatHistLine(Hist_MC_OverFlow    ,1  , GetHistColor(0),1);
  FormatHistLine(Hist_DATA_OverFlow  ,1  , GetHistColor(2),1);
  Hist_MC_OverFlow->Draw("hist");
  Hist_DATA_OverFlow->Draw("histsame");
  
  TLegend *legend = MakeLegend(0.7, 0.75, 0.9, 0.9,0.04);
  legend->AddEntry(Hist_MC_OverFlow  ,"MC ","l");
  legend->AddEntry(Hist_DATA_OverFlow,"DATA ","l");
  
  legend->Draw();
  //DrawLatexWithLabel(era,label,0.03,0.2,0.85);
  
  c1_down->cd();
  
  hist_axis(Hist_MC_OverFlow,Ratio_Hist);                                                                                                                                                                            
  Ratio_Hist->GetYaxis()->SetRangeUser(0.5,1.5);
  Ratio_Hist->Draw("histE");
  TLine *devz = new TLine(Ratio_Hist->GetBinLowEdge(Ratio_Hist->GetXaxis()->GetFirst()),1.0,Ratio_Hist->GetBinLowEdge(Ratio_Hist->GetXaxis()->GetLast()+1),1.0  );
  devz->SetLineWidth(1);
  devz->SetLineStyle(1);
  devz->Draw("SAME");
  
  
  gPad->Update();
  
  TString outpath =  output + "/"+HistName+"_"+era;
  
  TString save_pdf= outpath+".pdf";
  TString save_png= outpath+".png";
  
  c1->SaveAs(save_png);
  c1->SaveAs(save_pdf);
  
  SaveAndCopyLXPLUS(c1,outpath,analysername,"BDTvariables_JetDiscCorr");
  
  delete devz;
  delete Hist_MC_OverFlow;
  delete Hist_DATA_OverFlow;
  delete Ratio_Hist;
  
  File_SSDatasample->Close();
  File_OSDatasample->Close();
  delete File_SSDatasample;
  delete File_OSDatasample;
  
  File_SSMCsample->Close();
  File_OSMCsample->Close();
  delete File_OSMCsample;
  delete File_SSMCsample;
  
  return;
}

