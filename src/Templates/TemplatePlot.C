#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void TemplatePlot(){

  TString analysername="HNL";
  vector<TString> eras =  {"2017"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    TString histname="";                                                                                                    
    
    TString Histname="EE/MVAUL_UL/RegionPlots_PassSR2/"+histname;

    TString canvasname= Histname;
    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800)    ;

    canvas_margin(c1);
    c1->cd();
    
    TString pre=getenv("FILE_MERGED_PATH")+"/"+analysername+"/";

    TFile* File_sample = GetFile(pre+"/"+era+"/HNL_SignalRegionPlotter_SkimTree_HNMultiLep_NonPrompt.root");
    TH1D* hNP  = GetHist(File_sample,Histname);
    
    TH1D* hBkg       = GetHist(File_sampleBkg,Histname);
    FormatHist(hBkg,5,-999,0,10.,0,1, "H_{T}/P_{T}","Events / Bin ");

    TLegend *legend = MakeLegend(0.6, 0.55, 0.8, 0.7,0.025);
    //legend->AddEntry(hBkg,"SS Bkg.","f");
    
    gPad->Update();
    
    hBkg->Draw("hist");
    legend->Draw();

    TString label = "";
    DrawLatexWithLabel(era,label,0.65,0.88);
    gPad->Update();
    
    TString outpath = output + "/"+era+histname;

    TString save_pdf= outpath+".pdf";
    TString save_png= outpath+".png";
    
    c1->SaveAs(save_png);
    c1->SaveAs(save_pdf);
    
    SaveAndCopyLXPLUS(c1,outpath,analysername,"EXAMPLE");
    
    
  }
    
  
  return;
}

