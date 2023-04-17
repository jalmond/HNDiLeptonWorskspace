#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void MakeIDEfficiencyPlots(){

  
  TString analysername="HNL_LeptonIDSF";  
  vector<TString> eras =  {"2016preVFP"};//,"2016postVFP","2017"};

  vector<TString> datasets = {"Muon"};
  vector<TString> EtaBins = {"IB"};//,"OB","EE"};
  PlottingSetup();

  vector<TString> IDs = {"HNTightV2"};//TopFAKEL_BDTG"};
  for (auto era : eras){
    for (auto dataset : datasets){
      for (auto EtaBin : EtaBins){
	for (auto ID : IDs){
	  
	  SetUpDir(analysername,era);
	  TString output=GetOutPut(analysername,era);
	  
	  TString path= "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data_"+dataset+".root";
	  
	  
	  TString mcpath= "/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MC.root";
	  
	  
	
	  TString tag = dataset+"_"+era+"_"+EtaBin+ID;
	  TCanvas* c1 = MakeCanvas("",tag);
	  c1->Draw();
	  c1->cd();

	  TPad *c1_up;
	  TPad *c1_down;
	  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
	  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
          
	  canvas_margin(c1, c1_up, c1_down);
          
	  c1_up->Draw();
	  c1_down->Draw();
	  c1_up->cd();
	
	  
	  TFile * fdata = new TFile(path);
	  TFile * fmc = new TFile(mcpath);
	  
	  TString year=era;
	  if(era.Contains("2016")) year="2016";
	  TString denom = "MuMu/Pt_"+EtaBin+"_HNL_ULID_"+ID+"_denom";
	  TString num   = "MuMu/Pt_"+EtaBin+"_HNL_ULID_"+ID+"_num";

	  if(ID=="HNTightV2"){
	    denom = "MuMu/Pt_"+EtaBin+"_HNTightV2_denom";
	    num   = "MuMu/Pt_"+EtaBin+"_HNTightV2_num";
	  }

	  //TString denomNP="MuMu/Pt_"+EtaBin+"_HNL_ULID_"+ID+"_NonPrompt_denom";
	  //TString numNP="MuMu/Pt_"+EtaBin+"_HNL_ULID_"+ID+"_NonPrompt_num";
	  
	
	  TH1D* Hist_MC_Num        = GetHist(fmc,num);
	  TH1D* Hist_MC_Den        = GetHist(fmc,denom);
	  
	  //Hist_MC_Num->Add(Hist_FakeMC_Num,-1);
	  //Hist_MC_Den->Add(Hist_FakeMC_Den,-1);
	  
	  TH1D* Hist_DATA_Num        = GetHist(fdata,num);
	  TH1D* Hist_DATA_Den        = GetHist(fdata,denom);
	  
	  FormatHist(Hist_MC_Num   ,1  ,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");
	  FormatHist(Hist_DATA_Num   ,1  ,-999,10,1000., GetHistColor(1),1, "P_{T} GeV","Events ");
	  	  
	  
	  TH1D* Ratio_MC  =  GetRatioHist(Hist_MC_Num,Hist_MC_Den,"");
	  TH1D* Ratio_DATA  =  GetRatioHist(Hist_DATA_Num,Hist_DATA_Den,"");
	  Ratio_MC->GetXaxis()->SetRangeUser(10., 200);
	  Ratio_DATA->GetXaxis()->SetRangeUser(10., 200);
	  
	  TH1D* Ratio_SF  =  GetRatioHist(Ratio_DATA,Ratio_MC,"");
	  Ratio_SF->GetXaxis()->SetRangeUser(10., 200);
	  Ratio_SF->GetYaxis()->SetTitle("#frac{#epsilon_{DATA}}{#epsilon_{MC}}");
	  
	  TLegend *legend = MakeLegend(0.7, 0.5, 0.8, 0.7,0.04);
	  legend->AddEntry(Ratio_MC,"MC","l");
	  legend->AddEntry(Ratio_DATA,"DATA ","l");
	  
	  
	  hist_axis(Ratio_MC);
	  Ratio_MC->GetYaxis()->SetRangeUser(0., 1);
	  Ratio_MC->Draw("histE");
	  Ratio_DATA->Draw("histsameE");
	  
	  legend->Draw();
	  gPad->Update();
	  
	  TString label = dataset+ " EtaBin=" + EtaBin + " "  ;
	  DrawLatexWithLabel(year,label,0.04,0.25,0.18);
	  
	  c1_down->cd();
	  
	  hist_axis(Ratio_MC,Ratio_SF);                   
	  Ratio_SF->GetYaxis()->SetRangeUser(0.7,1.3);
	  Ratio_SF->GetYaxis()->SetNdivisions(6,5,0);
	  
	  Ratio_SF->SetLineColor(kBlack);
	  Ratio_SF->Draw("hist");
	  gPad->Update();
	  
	  TString outpath = output + "/IDSF_"+era+"_"+EtaBin+"_"+dataset+ID;
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  //c1_up->SetLogy();
	  //c1_down->SetLogy();
	  c1->SaveAs(save_png);
	  c1->SaveAs(save_pdf);
	
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"IDSF_MuonV2");
	}
      }
    }
      
  }
  
  return;
}
  
  
  
