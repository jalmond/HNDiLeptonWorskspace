#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void MVACRPlots(){

  TString analysername="HNL_LeptonIDSF";
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    vector<TString> histnames = {"CF_BDT_EE","Conv_BDT_EE","Fake_BDT_EE"};                                                                                              
    for (auto histname : histnames){
    
      TString Histname="EE_OS/"+histname;

      TString canvasname= Histname;
      TCanvas* c1 = MakeCanvas("",canvasname);
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


      
      TString pre="/data6/Users/jalmond/2020/HL_SKFlatAnalyzer_ULv3/SKFlatAnalyzer/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonIDSF/";
      TFile* File_sampleMC = GetFile(pre+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MC.root");
      TFile* File_sampleDATA = GetFile(pre+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data_Electron.root");

      
      
      TH1D* hData       = GetHist(File_sampleDATA,Histname);
      TH1D* hMC         = GetHist(File_sampleMC,Histname);
      hData->Scale(1./hData->Integral());
      hMC->Scale(1./hMC->Integral());

      TH1D* Ratio_SF  =  GetRatioHist(hData,hMC,Histname);
      //Ratio_SF->GetXaxis()->SetRangeUser(10., 200);
      Ratio_SF->GetYaxis()->SetTitle("#frac{#epsilon_{DATA}}{#epsilon_{MC}}");


      FormatHist(hMC,1,-999,0,10.,0,1, "H_{T}/P_{T}","Events / Bin ");
      hMC->SetLineColor(kBlue);
      hMC->SetLineWidth(2);
      //hMC->SetFillColor(kOrange);
      //hMC->SetFillStyle(3354);
    
      FormatHist(hData,1,-999, 0,10., GetHistColor(0),9, "P_{T} GeV","Events / GeV");
      
      TLegend *legend = MakeLegend(0.6, 0.55, 0.8, 0.7,0.025);
      legend->AddEntry(hMC,"MC","f");
      legend->AddEntry(hData,"DATA","l");
      hist_axis(hMC);

      gPad->Update();
      
      //DrawLatex(era);
      //CMS_lumi(c1,4,0);
      
      //hMC->GetYaxis()->SetRangeUser(0., 20.);
      hMC->Draw("hist");
      
      hData->Draw("histsame");
      
      legend->Draw();
      
      gPad->Update();
      c1_down->cd();

      hist_axis(hMC,Ratio_SF);
      Ratio_SF->GetYaxis()->SetRangeUser(0.,2.);
      Ratio_SF->GetYaxis()->SetNdivisions(6,5,0);

      Ratio_SF->SetLineColor(kBlack);
      Ratio_SF->Draw("hist");
      gPad->Update();

      TString label = "Electron Channel";
      DrawLatexWithLabel(era,label,0.03,0.65,0.88);
      gPad->Update();
      
      
      TString outpath = output + "/"+era+histname;
      
      TString save_pdf= outpath+".pdf";
      TString save_png= outpath+".png";
      
      c1->SaveAs(save_png);
      c1->SaveAs(save_pdf);
      
      SaveAndCopyLXPLUS(c1,outpath,analysername,"MVA_ElectronControl");
      
    
    }
  }
    
  
  return;
}

