#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag);

void ElectronSignalPlots(){
  
  DrawConfig("No9");
  

}

void DrawConfig(TString DateTag){
    
  TString ID = "HNL_ULID";
  TString year = "2017";
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("Electron_signals");
  Plotter.SetupPlotter(year,"","Electron_Signals");
  Plotter.CopyToWebsite = false;
  
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_SignalRegion_Plotter/Results/Nov9/2017/SIG/";
  
  
    TCanvas* c1 = new TCanvas("HPTDYEff", "", 1200, 800);
    c1->Draw();
    c1->cd();
    canvas_margin(c1);
    c1->SetRightMargin( 0.11 );
    
    TH1D *hist_Nom = Plotter.ConstructHist(path+"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DY_MN100.root","AllSR/HNL_ULID/EE/Leptons/Lepton_eta");
    
    TH1D *hist_500 = Plotter.ConstructHist(path+"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DY_MN500.root","AllSR/HNL_ULID/EE/Leptons/Lepton_eta");
    TH1D *hist_1000 = Plotter.ConstructHist(path+"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_DY_MN1000.root","AllSR/HNL_ULID/EE/Leptons/Lepton_eta");
    TH1D *hist_2000 = Plotter.ConstructHist(path+"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWW_MN2000.root","AllSR/HNL_ULID/EE/Leptons/Lepton_eta");
    TH1D *hist_10000 = Plotter.ConstructHist(path+"HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWW_MN10000.root","AllSR/HNL_ULID/EE/Leptons/Lepton_eta");
    
    hist_Nom->Rebin(2);
    hist_500->Rebin(2);
    hist_1000->Rebin(2);
    hist_2000->Rebin(2);
    hist_10000->Rebin(2);

    hist_Nom->Scale(1/hist_Nom->Integral());
    hist_500->Scale(1/hist_500->Integral());
    hist_1000->Scale(1/hist_1000->Integral());
    hist_2000->Scale(1/hist_2000->Integral());
    hist_10000->Scale(1/hist_10000->Integral());

    hist_axis(hist_Nom);
    hist_Nom->SetLineWidth(2.0);
    hist_Nom->GetXaxis()->SetTitle("Lepton #eta");
    hist_Nom->GetYaxis()->SetTitle("A.U.");
    //      hist_Nom->GetXaxis()->SetRangeUser(0,20);
    hist_Nom->GetYaxis()->SetRangeUser(0,.15);
    //    hist_Nom->SetLineStyle(4);
    hist_Nom->Draw("hist");
    
    hist_500->SetLineColor(kCyan);
    hist_1000->SetLineColor(kBlue);
    hist_2000->SetLineColor(kOrange);
    hist_10000->SetLineColor(kRed);
    hist_500->SetLineWidth(2.0);
    hist_1000->SetLineWidth(2.0);
    hist_2000->SetLineWidth(2.0);
    hist_10000->SetLineWidth(2.0);

    hist_500->Draw("histsame");
    hist_1000->Draw("histsame");
    hist_2000->Draw("histsame");
    hist_10000->Draw("histsame");
    
    TLegend *lg = new TLegend(0.55, 0.7, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    //string str = std::to_string(int_r); 

    TString leg100 = "m_{N} = 100 GeV " ;
    TString leg500 = "m_{N} = 500 GeV " ;
    TString leg1000 = "m_{N} = 1000 GeV" ;
    TString leg2000 = "m_{N} = 2000 GeV" ;
    TString leg10000 = "m_{N} = 10000 GeV" ;
    
    lg->AddEntry(hist_Nom,leg100,"l");
    lg->AddEntry(hist_500,leg500,"l");
    lg->AddEntry(hist_1000,leg1000,"l");
    lg->AddEntry(hist_2000,leg2000,"l");
    lg->AddEntry(hist_10000,leg10000,"l");

    
    lg->Draw();
    
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    //    channelname.DrawLatex(0.2, 0.88,"CCDY");
    
    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);
    
    TString HNAME = DateTag+"_Signal_eta_"+ID ;
    cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
    
    return;
}



