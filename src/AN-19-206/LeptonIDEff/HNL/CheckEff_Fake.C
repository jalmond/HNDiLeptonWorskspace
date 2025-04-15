#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       

void DrawConfig(TString Era, TString Type, TString sNum, TString sDen,TString lNum, TString lDen);

void CheckEff_Fake(){
  vector<TString> Etas = {"BB","EC"};
  vector<TString> TypesEl = {"Prompt_EE","CF_EE","Conv_EE","Fake_EE"};
  vector<TString> TypesMu = {"Prompt_MuMu","Conv_MuMu","Fake_MuMu"};
  for (auto ieta : Etas){
    for (auto itype : {"Fake_EE"}){
      DrawConfig("2016",itype,"Electron_pt_"+ieta+"_HNL_HighPt_ULID_2016","Electron_pt_"+ieta+"_HNL_HighPt_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
      DrawConfig("2016",itype,"Electron_pt_"+ieta+"_HNL_ULID_2016","Electron_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);

      DrawConfig("2017",itype,"Electron_pt_"+ieta+"_HNL_HighPt_ULID_2017","Electron_pt_"+ieta+"_HNL_HighPt_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
      DrawConfig("2017",itype,"Electron_pt_"+ieta+"_HNL_ULID_2017","Electron_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);

      DrawConfig("2018",itype,"Electron_pt_"+ieta+"_HNL_HighPt_ULID_2018","Electron_pt_"+ieta+"_HNL_HighPt_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
      DrawConfig("2018",itype,"Electron_pt_"+ieta+"_HNL_ULID_2018","Electron_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);

    }
    for (auto itype : {"Fake_MuMu"}){

      DrawConfig("2016",itype,"Muon_pt_"+ieta+"_HNL_ULID_2016","Muon_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
      DrawConfig("2017",itype,"Muon_pt_"+ieta+"_HNL_ULID_2017","Muon_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
      DrawConfig("2018",itype,"Muon_pt_"+ieta+"_HNL_ULID_2018","Muon_pt_"+ieta+"_HNL_ULID_FO","HNL ULID "+ieta,"HNL ULID "+ieta);
    }
  }  

}

void DrawConfig(TString Era, TString Type, TString sNum,TString sDen,TString lNum, TString lDen){
    
  TString ID = "HNL_ULID";
  TString year = Era;
  cout << "Running Era = " << year << endl;
  HNL_Efficiency_Plotter Plotter("HNL_ULID_Fake_QCD");
  Plotter.SetupPlotter(year,"","ID_Rates");
  Plotter.CopyToWebsite = false;
  
  TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/LeptonIDEff/Samples/Fake/";

  
  TCanvas* c1 = new TCanvas("HPTEff", "", 800, 800);
  c1->Draw();
  c1->cd();

  canvas_margin(c1);

  TString filePath=path+"Fake_"+year+".root";
  std::ifstream file(filePath);
  if (!file) {
    std::cerr << "Error: File " << path+"MC_DY_TT.root" << " does not exist.\n";
    return 1; // Exit with a non-zero status code.
  }
  else cout << "Accessing " << filePath << endl;

  TH1D *hist_num = Plotter.ConstructHist(filePath,Type+"/"+sNum);
  TH1D *hist_denom = Plotter.ConstructHist(filePath,Type+"/"+sDen);
  hist_num->GetXaxis()->SetRangeUser(20,500);
  hist_denom->GetXaxis()->SetRangeUser(20,500);


  cout << "Num = " << Type+"/"+sNum <<  " denom = " << Type+"/"+sDen << endl;
  double int_highpt = hist_num->Integral();
  double int_tight = hist_denom->Integral();
  double int_r = int_tight/int_highpt;
  string str = std::to_string(int_r); 

  cout << "Setup hist " << endl;

  TH1D *hist_empty = (TH1D*)hist_num->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");

  hist_empty->GetXaxis()->SetTitle("p_{T}^{l1} (GeV)");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  
  if(hist_num->GetMaximum() > hist_denom->GetMaximum() )hist_empty->GetYaxis()->SetRangeUser(1,hist_empty->GetMaximum()*1.4);
  else hist_empty->GetYaxis()->SetRangeUser(1,hist_denom->GetMaximum()*1.4);
  
  hist_empty->GetXaxis()->SetRangeUser(1,500);

  hist_empty->GetXaxis()->SetLabelSize(0);
  //  hist_empty->Draw("hist");


  hist_num->SetLineWidth(2.0);
  //  hist_num->SetLineStyle(23);      
  //  hist_num->SetLineStyle(4);
  //  hist_num->Draw("histsame");
  
  hist_denom->SetLineColor(kRed);
  
  //  hist_denom->Draw("histsame");
    
  TLegend *lg = new TLegend(0.6, 0.75, 0.93, 0.9);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.025);
  //  lg->AddEntry(hist_num, lNum,"l");
  //lg->AddEntry(hist_denom,lDen,"l");  
  //  lg->Draw();
  
  cout << "Legend " << endl;
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.035);
  
  //  channelname.DrawLatex(0.2, 0.8,"Tight/HPT = " +TString(str));
  
  TH1D *ratio_point = (TH1D *)hist_num->Clone();
  ratio_point->GetXaxis()->SetLabelSize(0);
  
  //  hist_axis(hist_empty, ratio_point);

  ratio_point->Divide(hist_denom);

  ratio_point->GetYaxis()->SetRangeUser(0.01,0.5);

  ratio_point->GetYaxis()->SetTitle("#epsilon_{Fake}");
  ratio_point->GetXaxis()->SetTitle("p_{T} (GeV)");
  hist_axis(ratio_point);
  ratio_point->Draw("hist");

  double FR_100 = 0;
  for(int x = 1; x < ratio_point->GetXaxis()->GetNbins()+1; x++){
    if(x==9) FR_100 = ratio_point->GetBinContent(x);
    cout << "Bin " << x << " bin value = " << ratio_point->GetBinLowEdge(x) <<  " value=" << ratio_point->GetBinContent(x) << endl;
  }

  double frx_1[2], fry_1[2],frx_err_1[2],fry_err_1[2],frx_err_2[2],fry_err_2[2];
  frx_1[0] = 100;
  frx_1[1] = 500;

  fry_1[0] = FR_100;
  fry_1[1] = FR_100;
  
  frx_err_1[0]=0.1;
  frx_err_1[1]=0.1;
  

  frx_err_2[0]=0.1;
  frx_err_2[1]=0.1;

  if(sNum.Contains("Muon")){
    fry_err_1[0]= 0.25*FR_100;
    fry_err_1[1]= 0.25*FR_100;

    fry_err_2[0]= 0.25*FR_100;
    fry_err_2[1]= 0.25*FR_100;

  }
  else{
    if(sNum.Contains("BB")){
      fry_err_2[0]= 0.8*FR_100;
      fry_err_2[1]= 0.8*FR_100;
    }
    else{
      fry_err_2[0]= 0.5*FR_100;
      fry_err_2[1]= 0.5*FR_100;
    }
    fry_err_1[0]= 0.4*FR_100;
    fry_err_1[1]= 0.4*FR_100;

  }
  
  TGraphAsymmErrors* grfr = new TGraphAsymmErrors(2,frx_1,fry_1,frx_err_1,frx_err_2,fry_err_1,fry_err_2);
  grfr->SetFillColor(kCyan);
  grfr->SetFillStyle(3002);
  //  grfr->SetMarkerSize(0);
  //  grfr->SetMarkerStyle(0);
  //  grfr->SetLineColor(kWhite);
  grfr->Draw("E3same");
  ratio_point->Draw("same");

  double x_1[2], y_1[2];
  x_1[0] = 100;  y_1[0] = FR_100;
  x_1[1] = 500;  y_1[1] = FR_100;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->SetLineStyle(4);
  g1->Draw("same");

  if(sNum.Contains("Muon")){
    lg->AddEntry(g1, "FR(extrap. 100 GeV)","l");
    lg->AddEntry(grfr, "FR(100 GeV) #pm 25%","f");
  }
  else{
    lg->AddEntry(g1, "FR(100 GeV)","l");
    lg->AddEntry(grfr, "FR(100 GeV) + 80 - 25%","f");

  }
  lg->Draw();                  

  TString Flavour = (sNum.Contains("Muon")) ? "Muon" : "Electron";
  channelname.DrawLatex(0.2, 0.88,Flavour);
  channelname.DrawLatex(0.2, 0.83,year);

  cout << Plotter.plotpath << endl;
  Plotter.mkdir(Plotter.plotpath);
    
  TString HNAME = Type + "_ID_Eff__"+sNum +"_"+sDen +"_"+year;
  cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
  c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
  
  cout << "END" << endl;
  return;
}



