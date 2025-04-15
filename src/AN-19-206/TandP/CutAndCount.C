#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString HistName, TString HistName2,TString Tag, TString Label);

void CutAndCount(){
  
  for(auto era : {"2016preVFP","2016postVFP","2017","2018"}){

    vector<TString> IDs = {"POGTightWithTightIso","POGHighPtTightWithIP","HNL_ULID","Peking","TopHN"};
    for(auto& ID : IDs){
      DrawConfig("Feb7",ID,era,"HighMass_"+ID+"_Bin1_Eta1", "HighMass_"+ID+"_Bin2_Eta1", "HighMass_"+ID,"HighMass_"+ID+" #eta < 0.9");
      DrawConfig("Feb7",ID,era,"HighMass_"+ID+"_Bin1_Eta2", "HighMass_"+ID+"_Bin2_Eta2", "HighMass_"+ID,"HighMass_"+ID+" 0.9 < #eta < 1.2");
      DrawConfig("Feb7",ID,era,"HighMass_"+ID+"_Bin1_Eta3", "HighMass_"+ID+"_Bin2_Eta3", "HighMass_"+ID,"HighMass_"+ID+" 1.2 < #eta < 2.1");
      DrawConfig("Feb7",ID,era,"HighMass_"+ID+"_Bin1_Eta4", "HighMass_"+ID+"_Bin2_Eta4", "HighMass_"+ID,"HighMass_"+ID+" 2.1 < #eta < 2.4");
      
      DrawConfig("Feb7",ID,era,ID+"_Bin1_Eta1",ID+"_Bin2_Eta1", ID,ID +" #eta < 0.9");
      DrawConfig("Feb7",ID,era,ID+"_Bin1_Eta2",ID+"_Bin2_Eta2", ID,ID +" 0.9 < #eta < 1.2");
      DrawConfig("Feb7",ID,era,ID+"_Bin1_Eta3",ID+"_Bin2_Eta3", ID,ID+" 1.2 < #eta < 2.1");
      DrawConfig("Feb7",ID,era,ID+"_Bin1_Eta4",ID+"_Bin2_Eta4", ID,ID+" 2.1 < #eta < 2.4");
      
    }
  }
}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString HistName, TString HistName2, TString Tag, TString Label){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter(Tag+"_CutAndCount");
    Plotter.SetupPlotter(year,"","Muon_Efficiency");
    Plotter.CopyToWebsite = false;
    
    //    if(year.Contains("2016")) year = "2016";

    TString path="/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_TandP_Efficiency/"+year+"/";

    TString path_dy_mass = path + "HNL_TandP_Efficiency_SkimTree_DileptonBDT_DYJets_Pt.root";         
    TString path_dy_mass_minnlo = path + "HNL_TandP_Efficiency_SkimTree_DileptonBDT_DYJetsToMuMu_MiNNLO.root";
                              
    //"HNL_TandP_Efficiency_SkimTree_DileptonBDT_DYJetsToMuMu_MiNNLO.root";
    //HNL_TandP_Efficiency_SkimTree_DileptonBDT_DYJets_Pt.root";
    
    cout << Flavour+"/"+HistName+"/Num" << endl;
    cout << path_dy_mass  <<endl;
    TH1D *hist_Num = Plotter.ConstructHist(path_dy_mass,Flavour+"/"+HistName2+"/Num");
    TH1D *hist_Den = Plotter.ConstructHist(path_dy_mass,Flavour+"/"+HistName2+"/Denom");
    cout << hist_Num << " " << hist_Den << endl;

    hist_Num->Divide(hist_Num,hist_Den ,1.,1.,"cl=0.683 b(1,1) mode");
  

    ///    TH1D *hist2_Num = Plotter.ConstructHist(path_dy_mass,Flavour+"/"+HistName2+"/Num");
    //    TH1D *hist2_Den = Plotter.ConstructHist(path_dy_mass,Flavour+"/"+HistName2+"/Denom");
    //    hist2_Num->Divide(hist2_Num,hist2_Den ,1.,1.,"cl=0.683 b(1,1) mode");

    TH1D *hist3_Num = Plotter.ConstructHist(path_dy_mass_minnlo,Flavour+"/"+HistName2+"/Num");
    TH1D *hist3_Den = Plotter.ConstructHist(path_dy_mass_minnlo,Flavour+"/"+HistName2+"/Denom");
    hist3_Num->Divide(hist3_Num,hist3_Den ,1.,1.,"cl=0.683 b(1,1) mode");

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
    hist_Num->GetXaxis()->SetRangeUser(100,999);
    hist_Num->GetYaxis()->SetRangeUser(0.9,1.1);
    if(HistName.Contains("Eta4"))    hist_Num->GetYaxis()->SetRangeUser(0.5,1.1);

    hist_Num->Draw("histE");
    //    hist2_Num->SetLineColor(kRed);
    //    hist2_Num->Draw("histEsame");
    
    hist3_Num->SetLineColor(kBlue);
    hist3_Num->Draw("histEsame");
    
    TLegend *lg = new TLegend(0.55, 0.8, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    lg->AddEntry(hist_Num,"DY Merged MC","l");
    //lg->AddEntry(hist2_Num,"DY Merged MC (Bin2)","l");
    lg->AddEntry(hist3_Num,"DY NNLO MC (Bin2)","l");
    lg->Draw();
    
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    channelname.DrawLatex(0.2, 0.88,Label);
    
    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);
    
    TString DYName ="MergedDY_";
    // DYName ="MiNNLO_";

    TString HNAME = DYName+DateTag+"_"+HistName +"_"+era+"_Samebinning" ;
    cout << Plotter.plotpath+"/"+DYName+"_"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
    
    
  }
  return;
}



