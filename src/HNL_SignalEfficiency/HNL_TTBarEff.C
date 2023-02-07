#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void HNL_TTBarEff(){

  TString analysername="HNL_SignalEfficiency";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    
    vector<TString> samples =  {"HNL_SignalEfficiency_TTLJ_powheg","HNL_SignalEfficiency_DYJets_MG","HNL_SignalEfficiency_WJets_MG"};
    vector<TString> sources = {"Fake","Conv"};
    
    for(auto sample : samples){
    
      vector<TString> EtaBins = {""};
  
      for( auto EtaBin: EtaBins){

        for(auto itype : sources){
	  
	  
	  TCanvas* c1 = MakeCanvas("",sample+"_"+EtaBin);
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
	  

	  TFile* File_sample = GetFile("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+sample+".root");
	  
	  TString LepType = "Muon";
	  TString DirName= itype+ "_MuMu/";
	  
	  TString sHist_Loose    = DirName+LepType+"_pt"+EtaBin+"_POGLoose";
	  TString sHist_HNLID    = DirName+LepType+"_pt"+EtaBin+"_HNL_TopMVA_MM";
	  TString sHist_HNLV2    = DirName+LepType+"_pt"+EtaBin+"_HNTightV2";
	  
	  
	  TH1D* Hist_Loose        = GetHist(File_sample,sHist_Loose);
	  TH1D* Hist_HNLID        = GetHist(File_sample,sHist_HNLID);
	  TH1D* Hist_HNLV2        = GetHist(File_sample,sHist_HNLV2);
	    
	    
	  FormatHist(Hist_Loose    ,1  ,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");
	  FormatHist(Hist_HNLID    ,1  ,-999,10,1000., GetHistColor(2),1, "P_{T} GeV","Events ");
	  FormatHist(Hist_HNLV2    ,1  ,-999,10,1000., GetHistColor(3),1, "P_{T} GeV","Events ");
	    
	    
	  /// Get Integrals
	  double LooseInt    = Hist_Loose->Integral(0.,Hist_Loose->GetNbinsX()+1 );
	  double HNLIDInt    = Hist_HNLID->Integral(0.,Hist_HNLID->GetNbinsX()+1 );
	  double HNLV2Int    = Hist_HNLV2->Integral(0.,Hist_HNLV2->GetNbinsX()+1 );
	    
	  double EffHNLID = 100*HNLIDInt/LooseInt;
	  double EffHNLV2 = 100*HNLV2Int/LooseInt;
	  
	  /// Make Ratio Plots
	  TH1D* Ratio_HNLIDR   =  GetRatioHist(Hist_HNLID,Hist_Loose);
	  TH1D* Ratio_HNLV2IDR =  GetRatioHist(Hist_HNLV2,Hist_Loose);
	    
	  /// Ratio of ratio
	  TH1D* Ratio_IDComp   =  GetRatioHist(Hist_HNLV2,Hist_HNLID);
          FormatHist(Ratio_IDComp  ,1  ,-999,10,100., GetHistColor(0),9, "P_{T} GeV","");
	  Ratio_IDComp->GetYaxis()->SetTitle("#frac{#epsilon_{HNTightV2}}{#epsilon_{MVA}}");
	  
	  TLegend *legend = MakeLegend(0.7, 0.75, 0.8, 0.9,0.035);
	  legend->AddEntry(Ratio_HNLIDR,"HNL MVA","l");
	  legend->AddEntry(Ratio_HNLV2IDR,"HNTightV2 ","l");
	  
	  if(itype=="Fake"){
	    Ratio_HNLV2IDR->SetMaximum(.1);
	    Ratio_HNLV2IDR->SetMinimum(0.0001);
	  }
	  else{
	    Ratio_HNLV2IDR->SetMaximum(1);
            Ratio_HNLV2IDR->SetMinimum(0.1);
	  }
	  Ratio_HNLV2IDR->GetYaxis()->SetNdivisions(6,5,0);
	  Ratio_HNLV2IDR->GetYaxis()->SetTitle("ID Efficiency (vs POG Loose)");
	  Ratio_HNLV2IDR->GetXaxis()->SetRangeUser(10., 100);
	  hist_axis(Ratio_HNLV2IDR);
	  Ratio_HNLV2IDR->Draw("histE");
	  Ratio_HNLIDR->Draw("histsameE");
	    
	  legend->Draw();
	  gPad->Update();
	    
	  TString labelV2 = "HNTightV2 Av. Eff. = "+TString(to_string(EffHNLV2))+"%";
	  TString labelMVA = "MVA Av. Eff. = "+TString(to_string(EffHNLID))+"%";
	  DrawLatexWithLabel(era,labelV2,0.25,0.18);
	  DrawLatexWithLabel(era,labelMVA,0.25,0.28);
	  
	  c1_down->cd();
	  
	  hist_axis(Ratio_HNLV2IDR,Ratio_IDComp);                                                                                                                                                                            
          Ratio_IDComp->GetYaxis()->SetNdivisions(6,5,0);
	  
	  //Ratio_IDComp->GetYaxis()->SetTitle("#frac{#epsilon_{HNTightV2}}{#epsilon_{MVA}}");

	  Ratio_IDComp->Draw("hist");
	  gPad->Update();
	  
	  TString outpath = output + "/"+sample+"_"+era+"_"+EtaBin+"_"+itype;
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  c1_up->SetLogy();
	  //c1_down->SetLogy();
	  c1->SaveAs(save_png);
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"TTBar");
	  
	
	  File_sample->Close();
	  delete File_sample;
	}
      }
    }
  }
    
  
  return;
}

