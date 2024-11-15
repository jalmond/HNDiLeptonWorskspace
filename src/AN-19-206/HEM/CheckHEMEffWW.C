#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


//vector<double> GetMassListDY = {"85","90", "95","100", "125", "150","200", "250" ,"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
//vector<double> GetMassListWW = {"1000",  "1100", "1300", "1500", "2000",  "2500", "500"};


void DrawConfig(TString DatTag,TString flavour, TString year, TString filepath, TString ID);

void CheckHEMEffWW(){
  
  DrawConfig("Nov8","LL","2018","HNL_SR","HNL_ULID");
  

}

void DrawConfig(TString DateTag,TString Flavour, TString era, TString filepath,  TString ID){

  vector<TString> eras =  {era};

  for (auto year : eras){
    
    cout << "Running Era = " << year << endl;
    HNL_Efficiency_Plotter Plotter("HEM");
    Plotter.SetupPlotter(year,"",Flavour+"_HEM_Presel_Efficiency");
    Plotter.CopyToWebsite = false;
    
    if(year.Contains("2016")) year = "2016";
    //      TString path_mass = path + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M"+GetMassListWW[i] + "_private.root";


    TString path1="/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/"+year+"/RunNoSyst__/";
    TString path2="/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_SignalRegion_Plotter/"+year+"/ScaleHEMJet__RunNoSyst__/";
    
    
    vector<TString> GetMassListDY = {"90","95","100", "125", "150","200", "250",  "300", "400", "500", "600", "700", "800", "900","1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000"};
    vector<TString> GetMassListVBF = {"1000",  "1100", "1200","1300", "1500", "1700", "2000",  "2500", "3000", "300", "400", "500", "600", "700", "800", "900"};
    vector<TString> GetMassListWW = {"500","1000",  "1100", "1300", "1500", "2000",  "2500"};


    for(unsigned int i = 0 ; i < GetMassListWW.size(); i++){
      //      TString path_mass = path + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M"+GetMassListWW[i] + "_private.root";

      TString path1_mass = path1 + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M"+GetMassListWW[i] + "_private.root";   
      TString path2_mass = path2 + "HNL_SignalRegion_Plotter_SkimTree_HNMultiLepBDT_SSWWTypeI_SF_M"+GetMassListWW[i] + "_private.root";   
   

      
      TH1D *hist_Nom = Plotter.ConstructHist(path1_mass,"Preselection/HNL_ULID/LL/SKEvent/Ev_MET2_ST");
      TH1D *hist_JESUp = Plotter.ConstructHist(path1_mass,"Preselection/Syst_JetEnUpHNL_ULID/LL/SKEvent/Ev_MET2_ST");
      TH1D *hist_JESDown = Plotter.ConstructHist(path1_mass,"Preselection/Syst_JetEnDownHNL_ULID/LL/SKEvent/Ev_MET2_ST");
      TH1D *hist_HEM = Plotter.ConstructHist(path2_mass,"Preselection/HNL_ULID/LL/SKEvent/Ev_MET2_ST");
      
      vector<double> vrebin = {0.,5,10,20};

      double TMParray[vrebin.size()];
      std::copy(vrebin.begin(), vrebin.end(), TMParray);
      hist_Nom = (TH1D *)hist_Nom->Rebin(vrebin.size()-1, "hnew1", TMParray);
      hist_JESUp = (TH1D *)hist_JESUp->Rebin(vrebin.size()-1, "hnew2", TMParray);
      hist_JESDown = (TH1D *)hist_JESDown->Rebin(vrebin.size()-1, "hnew3", TMParray);
      hist_HEM = (TH1D *)hist_HEM->Rebin(vrebin.size()-1, "hnew4", TMParray);

      hist_JESUp->Divide(hist_Nom);
      hist_JESDown->Divide(hist_Nom);
      hist_HEM->Divide(hist_Nom);

      TCanvas* c1 = new TCanvas(Flavour+"_WWEff", "", 1200, 800);
      c1->Draw();
      c1->cd();

      canvas_margin(c1);
      c1->SetRightMargin( 0.11 );
    
      
      hist_axis(hist_HEM);
  
      hist_HEM->SetLineWidth(2.0);
      hist_HEM->SetLineStyle(23);      
      hist_HEM->GetXaxis()->SetTitle("MET^{2}/S_{T} (GeV)");
      hist_HEM->GetYaxis()->SetTitle("Shifted/Nominal");
      hist_HEM->GetXaxis()->SetRangeUser(0,20);
      hist_HEM->GetYaxis()->SetRangeUser(0,2);
      hist_HEM->SetLineStyle(4);
      hist_HEM->Draw("hist");
    
      hist_JESUp->SetLineColor(kRed);
      hist_JESUp->SetLineWidth(2);
      hist_JESDown->SetLineColor(kRed);
      hist_JESDown->SetLineWidth(2);

      hist_JESUp->Draw("histsame");
      hist_JESDown->Draw("histsame");

      TLegend *lg = new TLegend(0.55, 0.8, 0.93, 0.93);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->SetTextSize(0.03);
      lg->AddEntry(hist_HEM,"HEM Shift","l");
      lg->AddEntry(hist_JESUp,"JES","l");
      lg->Draw();

      TLatex channelname;
      channelname.SetNDC();
      channelname.SetTextSize(0.03);
      channelname.DrawLatex(0.2, 0.88,"SSWW");
      
      cout << Plotter.plotpath << endl;
      Plotter.mkdir(Plotter.plotpath);
      
      TString HNAME = DateTag+"_SignalEff_WW_"+GetMassListWW[i]+"_"+ID ;
      cout << Plotter.plotpath+"/"+HNAME+".pdf" << endl;
      c1->SaveAs(Plotter.plotpath+"/"+HNAME+".pdf");

    }
  }
  return;
}



