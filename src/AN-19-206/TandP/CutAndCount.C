#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString HistName, TString Tag, TString Label);

void CutAndCount(){
  
  TString Era = "2018";
  DrawConfig("Nov12","LL",Era,"HighPt_Bin1_Eta1", "HighPt","HighPt #eta < 0.9");
  DrawConfig("Nov12","LL",Era,"HighPt_Bin1_Eta2", "HighPt","HighPt 0.9 < #eta < 1.2");
  DrawConfig("Nov12","LL",Era,"HighPt_Bin1_Eta3", "HighPt","HighPt 1.2 < #eta < 2.4");

  DrawConfig("Nov12","LL",Era,"HighPt_Bin2_Eta1", "HighPt","HighPt #eta < 0.9");
  DrawConfig("Nov12","LL",Era,"HighPt_Bin2_Eta2", "HighPt","HighPt 0.9 < #eta < 1.2");
  DrawConfig("Nov12","LL",Era,"HighPt_Bin2_Eta3", "HighPt","HighPt 1.2 < #eta < 2.4");

  DrawConfig("Nov12","LL",Era,"Peking_Bin1_Eta1", "Peking","Peking #eta < 0.9");
  DrawConfig("Nov12","LL",Era,"Peking_Bin1_Eta2", "Peking","Peking 0.9 < #eta < 1.2");
  DrawConfig("Nov12","LL",Era,"Peking_Bin1_Eta3", "Peking","Peking 1.2 < #eta < 2.4");

  DrawConfig("Nov12","LL",Era,"Peking_Bin2_Eta1", "Peking","Peking #eta < 0.9");
  DrawConfig("Nov12","LL",Era,"Peking_Bin2_Eta2", "Peking","Peking 0.9 < #eta < 1.2");
  DrawConfig("Nov12","LL",Era,"Peking_Bin2_Eta3", "Peking","Peking 1.2 < #eta < 2.4");


  //  DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin1_Eta1", "HNL_ULID_Bin1","HNL_ULID_Bin1 #eta < 0.9");
  //DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin1_Eta2", "HNL_ULID_Bin1","HNL_ULID_Bin1 0.9 < #eta < 1.2");
  //DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin1_Eta3", "HNL_ULID_Bin1","HNL_ULID_Bin1 1.2 < #eta < 2.4");

  DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin2_Eta1", "HNL_ULID","HNL_ULID #eta < 0.9");
  DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin2_Eta2", "HNL_ULID","HNL_ULID 0.9 < #eta < 1.2");
  DrawConfig("Nov12","LL",Era,"HNL_ULID_Bin2_Eta3", "HNL_ULID","HNL_ULID 1.2 < #eta < 2.4");
}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString HistName,TString Tag, TString Label){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter(Tag+"_CutAndCount");
    Plotter.SetupPlotter(year,"","Muon_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";

    TString path="/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_TandP_Efficiency/"+year+"/";

    TString path_dy_mass = path + "HNL_TandP_Efficiency_SkimTree_DileptonBDT_DYJetsToMuMu_MiNNLO.root";
    TString path_data_mass = path + "DATA/Data.root";
    
    cout << path_dy_mass << " path_data_mass = " << path_data_mass << endl;
    cout << HistName+"/Num" << endl;
    TH1D *hist_Num = Plotter.ConstructHist(path_dy_mass,HistName+"/Num");
    TH1D *hist_Den = Plotter.ConstructHist(path_dy_mass,HistName+"/Denom");
    cout << hist_Num << " " << hist_Den << endl;

    hist_Num->Divide(hist_Num,hist_Den ,1.,1.,"cl=0.683 b(1,1) mode");
    
    TH1D *hist_data_Num = Plotter.ConstructHist(path_data_mass,HistName+"/Num");
    TH1D *hist_data_Den = Plotter.ConstructHist(path_data_mass,HistName+"/Denom");

    hist_data_Num->Divide(hist_data_Num,hist_data_Den ,1.,1.,"cl=0.683 b(1,1) mode");
    cout << hist_data_Num <<" " << hist_data_Den<< endl;

    TCanvas* c1 = new TCanvas(Flavour+"_Eff", "", 1200, 800);
    c1->Draw();
    c1->cd();
    
    canvas_margin(c1);
    c1->SetRightMargin( 0.11 );
    
    
    hist_axis(hist_Num);
    
    hist_Num->SetLineWidth(2.0);
    hist_Num->SetLineStyle(23);      
    hist_Num->GetXaxis()->SetTitle("P_{T} (GeV)");
    hist_Num->GetYaxis()->SetTitle("#epsilon_{ID}");
    hist_Num->GetXaxis()->SetRangeUser(0,1000);
    hist_Num->GetYaxis()->SetRangeUser(0.7,1.3);
    hist_Num->Draw("histE");
    
    hist_data_Num->SetLineWidth(2.0);
    hist_data_Num->SetLineStyle(4);
    
    hist_data_Num->Draw("histsameE");

    TLegend *lg = new TLegend(0.55, 0.8, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    lg->AddEntry(hist_data_Num,"Data","l");
    lg->AddEntry(hist_Num,"DY MC","l");
    lg->Draw();
    
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    channelname.DrawLatex(0.2, 0.88,Label);
    
    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);
    
    TString HNAME = DateTag+"_"+HistName ;
    cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
    
    
  }
  return;
}



