#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag);

void CheckHPTPerc_WW(){
  
  DrawConfig("Nov8");
  

}

void DrawConfig(TString DateTag){
    
  TString ID = "HNL_ULID";
  TString year = "2018";
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HPT");
  Plotter.SetupPlotter(year,"","Muon_HPT_Efficiency");
  Plotter.CopyToWebsite = false;
  
  
  TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_HighPtMuon_Studies/2018/";
  
  
  vector<TString> GetMassListDY = {"100","500", "1000","2000"};
  vector<TString> GetMassListVBF = {"500", "1000","2000"};
  vector<TString> GetMassListWW = {"1000", "10000"};
  
  if(GetMassListWW.size() > 0){
    TCanvas* c1 = new TCanvas("HPTWWEff", "", 1200, 800);
    c1->Draw();
    c1->cd();
    canvas_margin(c1);
    c1->SetRightMargin( 0.11 );
    
    TH1D *hist_500 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M500_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");
    TH1D *hist_750 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M750_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");
    TH1D *hist_1000 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M1000_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");
    TH1D *hist_2000 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M2000_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");
    TH1D *hist_10000 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M10000_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");

    TH1D *hist_wein = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_SSWWjj_DIM5_WeinbergOpt_MuMu_private.root","SS/Muon1_Default_Pt_Muon_HighPt_v3");
    
    double percent500 = 100*hist_500->Integral(3,11) / hist_500->Integral();
    double percent750 = 100*hist_750->Integral(3,11) / hist_750->Integral();
    double percent1000 = 100*hist_1000->Integral(3,11) / hist_1000->Integral();
    double percent2000 = 100*hist_2000->Integral(3,11) / hist_2000->Integral();
    double percent10000 = 100*hist_10000->Integral(3,11) / hist_10000->Integral();
    double percentwein = 100*hist_wein->Integral(3,11) / hist_wein->Integral();

    
    cout << "percent500 = " << percent500 << endl;
    cout << "percent1000 = " << percent1000 << endl;
    cout << "percent2000 = " << percent2000 << endl;

    hist_500->Scale(1/hist_500->Integral());
    hist_750->Scale(1/hist_750->Integral());
    hist_1000->Scale(1/hist_1000->Integral());
    hist_2000->Scale(1/hist_2000->Integral());
    hist_10000->Scale(1/hist_10000->Integral());
    hist_wein->Scale(1/hist_wein->Integral());

    hist_axis(hist_500);
    hist_500->SetLineWidth(2.0);
    hist_500->SetLineStyle(23);      
    hist_500->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
    hist_500->GetYaxis()->SetTitle("A.U.");
    //      hist_500->GetXaxis()->SetRangeUser(0,20);
    hist_500->GetYaxis()->SetRangeUser(0,0.7);
    //    hist_500->SetLineStyle(4);
    hist_500->Draw("hist");
    
    hist_500->SetLineColor(kRed);
    hist_750->SetLineColor(kBlue);
    hist_1000->SetLineColor(kOrange);
    hist_2000->SetLineColor(kGreen);
    hist_10000->SetLineColor(kViolet);
    hist_wein->SetLineColor(kCyan);
    
    hist_500->SetLineWidth(2.0);
    hist_750->SetLineWidth(2.0);
    hist_1000->SetLineWidth(2.0);
    hist_2000->SetLineWidth(2.0);
    hist_10000->SetLineWidth(2.0);
    hist_wein->SetLineWidth(2.0);

    hist_500->Draw("histsame");
    hist_750->Draw("histsame");
    hist_1000->Draw("histsame");
    hist_2000->Draw("histsame");
    hist_10000->Draw("histsame");
    hist_wein->Draw("histsame");
    
    TLegend *lg = new TLegend(0.55, 0.7, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    lg->AddEntry(hist_500,"m_{N} = 500 GeV : " + TString::Itoa(percent500,10)+"%","l");
    lg->AddEntry(hist_750,"m_{N} = 750 GeV : " + TString::Itoa(percent750,10)+"%","l");
    lg->AddEntry(hist_1000,"m_{N} = 1000 GeV : " + TString::Itoa(percent1000,10)+"%","l");
    lg->AddEntry(hist_2000,"m_{N} = 2000 GeV : " + TString::Itoa(percent2000,10)+"%","l");
    lg->AddEntry(hist_10000,"m_{N} = 10000 GeV : " + TString::Itoa(percent10000,10)+"%","l");
    lg->AddEntry(hist_wein,"dim-5 WO : " + TString::Itoa(percentwein,10)+"%","l");
    
    lg->Draw();
    
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    channelname.DrawLatex(0.2, 0.88,"WW");
    
    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);
    
    TString HNAME = DateTag+"_SignalEff_Pt200_WW_Wein_"+ID ;
    cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
        
  }
  return;
}



