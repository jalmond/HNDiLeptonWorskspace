#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString filepath, TString ID);

void DrawHEMEff_WW(){
  
  DrawConfig("Oct9","EE","2018","HNL_SR","HNL_ULID");


}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString filepath,  TString ID){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter("HEM_Efficiency");
    Plotter.SetupPlotter(year,"",Flavour+"_HEM_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";

    TString path="/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/"+year+"/RunNoSyst__HEMJet__/";
    
    
    vector<TString> GetMassListDY  = {"90","95","100", "125", "150","200", "250",  "300", "400", "500", "600", "700", "800", "900","1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000"};
    vector<TString> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
    vector<TString> GetMassListWW  = {"500","1000",  "1100", "1300", "1500", "2000",  "2500"};

   
    TH1D * h_eff_WW = new TH1D ("","",GetMassListWW.size(),0,GetMassListWW.size());
    h_eff_WW->GetXaxis()->SetTitle("m_{N} (GeV)");
    h_eff_WW->GetYaxis()->SetRangeUser(0.7,1);
    h_eff_WW->GetYaxis()->SetTitle("m_{N} Selection efficiency for HEM cleaning");

    TH1D * h_eff_WW_SR1 = new TH1D ("","",GetMassListWW.size(),0,GetMassListWW.size());
    TH1D * h_eff_WW_SR2 = new TH1D ("","",GetMassListWW.size(),0,GetMassListWW.size());
    TH1D * h_eff_WW_SR3 = new TH1D ("","",GetMassListWW.size(),0,GetMassListWW.size());

    TH1D * h_eff_WW_SR = new TH1D ("","",GetMassListWW.size(),0,GetMassListWW.size());

    for(unsigned int i = 0 ; i < GetMassListWW.size() ; i++) h_eff_WW->GetXaxis()->SetBinLabel(i+1,GetMassListWW[i]);

    for(unsigned int i = 0 ; i < GetMassListWW.size(); i++){
      TString path_mass = path + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M"+GetMassListWW[i] + "_private.root";
      
      double  NoCutValue (0);
      double  Presel (0);
      double  SR1 (0);
      double  SR2 (0);
      double  SR3 (0);

      
      TH2D *hist_Inc        = Plotter.Construct2DHist(path_mass,"HNL_ULID/EE/Inclusive_El_HEM_EtaPhi");
      TH2D *hist_Fail       = Plotter.Construct2DHist(path_mass,"HNL_ULID/EE/HEM_Region_Fail_El_HEM_EtaPhi");

      cout << path_mass << endl;
      cout << "WW " << GetMassListWW[i] << endl;

      cout << "hist_Inc " << hist_Inc << endl;
      cout << "hist_Fail " << hist_Fail << endl;
      cout << "Integral  " << hist_Inc->Integral() << endl;
      double EffHEM = (hist_Inc->Integral() > 0)    ?  (hist_Inc->Integral() -hist_Fail->Integral()) / hist_Inc->Integral() : 0;
      
      cout << "Bin " << i+1 << " EffHEM = " << EffHEM << endl;
      h_eff_WW->SetBinContent(i+1,  EffHEM);
    }
    
    
    TCanvas* c1 = new TCanvas(Flavour+"_WWEff", "", 1200, 800);
    c1->Draw();
    c1->cd();
    canvas_margin(c1);
    c1->SetRightMargin( 0.11 );
    
    //    h_eff_WW->GetYaxis()->SetTitle("#epsilon_{Signal}");

    hist_axis(h_eff_WW);
  
    h_eff_WW->SetLineWidth(2.0);
    h_eff_WW->SetLineStyle(23);
    h_eff_WW->Draw("l");
    
    TLegend *lg = new TLegend(0.55, 0.8, 0.93, 0.93);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    lg->SetTextSize(0.03);
    lg->AddEntry(h_eff_WW,"Electron HEM","l");
    lg->Draw();

    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.03);
    channelname.DrawLatex(0.2, 0.8,"WW");

    cout << Plotter.plotpath << endl;
    Plotter.mkdir(Plotter.plotpath);

    TString HNAME = "SignalEff_WW_"+Flavour + "_"+ID ;
    cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
    c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");
    
  }
  
  return;
}



