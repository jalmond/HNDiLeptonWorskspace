#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag);

void CheckHPTPerc(){
  
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
  
  if(GetMassListDY.size() > 0){
    TCanvas* c1 = new TCanvas("HPTDYEff", "", 1200, 800);
    c1->Draw();
    c1->cd();
    canvas_margin(c1);
    c1->SetRightMargin( 0.11 );
    
    TH1D *hist_Nom = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M100_private.root","SS/Muon1_Default_Pt_SR_Muon_ULID_v3");
    TH1D *hist_200 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M200_private.root","SS/Muon1_Default_Pt_SR_Muon_ULID_v3");
    TH1D *hist_500 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M500_private.root","SS/Muon1_Default_Pt_SR_Muon_ULID_v3");
    TH1D *hist_1000 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M1000_private.root","SS/Muon1_Default_Pt_SR_Muon_ULID_v3");
    TH1D *hist_2000 = Plotter.ConstructHist(path+"HNL_HighPtMuon_Studies_SkimTree_HNMultiLepBDT_DYTypeI_DF_M2000_private.root","SS/Muon1_Default_Pt_SR_Muon_ULID_v3");
    
    double percent100 = 100*hist_Nom->Integral(3,11) / hist_Nom->Integral();
    double percent200 = 100*hist_200->Integral(3,11) / hist_200->Integral();
    double percent500 = 100*hist_500->Integral(3,11) / hist_500->Integral();
    double percent1000 = 100*hist_1000->Integral(3,11) / hist_1000->Integral();
    double percent2000 = 100*hist_2000->Integral(3,11) / hist_2000->Integral();
    
    cout << "percent100 = " << percent100 << endl;
    cout << "percent200 = " << percent200 << endl;
    cout << "percent500 = " << percent500 << endl;
    cout << "percent1000 = " << percent1000 << endl;
    cout << "percent2000 = " << percent2000 << endl;

    hist_Nom->Scale(1/hist_Nom->Integral());
    hist_500->Scale(1/hist_500->Integral());
    hist_200->Scale(1/hist_200->Integral());
    hist_1000->Scale(1/hist_1000->Integral());
    hist_2000->Scale(1/hist_2000->Integral());

    hist_axis(hist_Nom);
    hist_Nom->SetLineWidth(2.0);
    //    hist_Nom->SetLineStyle(23);      
    hist_Nom->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
    hist_Nom->GetYaxis()->SetTitle("A.U.");
    //      hist_Nom->GetXaxis()->SetRangeUser(0,20);
    hist_Nom->GetYaxis()->SetRangeUser(0,1.);
    //    hist_Nom->SetLineStyle(4);
    hist_Nom->Draw("hist");
    
    hist_200->SetLineColor(kRed);
    hist_500->SetLineColor(kCyan);
    hist_1000->SetLineColor(kBlue);
    hist_2000->SetLineColor(kOrange);
    hist_200->SetLineWidth(2.0);
    hist_500->SetLineWidth(2.0);
    hist_1000->SetLineWidth(2.0);
    hist_2000->SetLineWidth(2.0);

    hist_200->Draw("histsame");
    hist_500->Draw("histsame");
    hist_1000->Draw("histsame");
    hist_2000->Draw("histsame");
    
    TLegend *lg = new TLegend(0.55, 0.7, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    //string str = std::to_string(int_r); 

    TString leg100 = "m_{N} = 100 GeV : " + TString::Itoa(percent100,10)+"%";
    TString leg200 = "m_{N} = 200 GeV : " + TString::Itoa(percent200,10)+"%";
    TString leg500 = "m_{N} = 500 GeV : " + TString::Itoa(percent500,10)+"%";
    TString leg1000 = "m_{N} = 1000 GeV : " + TString::Itoa(percent1000,10)+"%";
    TString leg2000 = "m_{N} = 2000 GeV : " + TString::Itoa(percent2000,10)+"%";
    
    lg->AddEntry(hist_Nom,leg100,"l");
    lg->AddEntry(hist_200,leg200,"l");
    lg->AddEntry(hist_500,leg500,"l");
    lg->AddEntry(hist_1000,leg1000,"l");
    lg->AddEntry(hist_2000,leg2000,"l");

    
    lg->Draw();
    
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    channelname.DrawLatex(0.2, 0.88,"CCDY");
    
    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);
    
    TString HNAME = DateTag+"_SignalEff_Pt200_DY_"+ID ;
    cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
        
  }
  return;
}



