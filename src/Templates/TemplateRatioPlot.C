#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void TemplateRatioPlot(){

  TString analysername="";
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    
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
    TH1D* Hist_Loose        = GetHist(File_sample,sHist_Loose);
    FormatHist(Hist_Loose    ,1  ,-999,10,1000., GetHistColor(0),1, "P_{T} GeV","Events ");


    TH1D* Ratio_HNLIDR   =  GetRatioHist(Hist_HNLID,Hist_Loose);
	    
    FormatHist(Ratio_IDComp  ,1  ,-999,10,100., GetHistColor(0),9, "P_{T} GeV","");
	  
    TLegend *legend = MakeLegend(0.7, 0.75, 0.8, 0.9,0.035);
    legend->AddEntry(Ratio_HNLIDR,"HNL MVA","l");
	    
    legend->Draw();
    gPad->Update();
    
    TString labelV2 = "HNTightV2 Av. Eff. = "+TString(to_string(EffHNLV2))+"%";
    TString labelMVA = "MVA Av. Eff. = "+TString(to_string(EffHNLID))+"%";
    DrawLatexWithLabel(era,labelV2,0.25,0.18);
    
    c1_down->cd();
    
    hist_axis(Ratio_HNLV2IDR,Ratio_IDComp);                                                                                                                                                                            
    Ratio_IDComp->GetYaxis()->SetNdivisions(6,5,0);
    
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
  
  
  return;
}

