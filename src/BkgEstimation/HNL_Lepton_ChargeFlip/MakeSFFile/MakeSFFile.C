#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeSFFileConfig(TString year, TString hist);

void MakeSFFile(){
  
  MakeSFFileConfig("2016a","Rates");
  MakeSFFileConfig("2016b","Rates");
  MakeSFFileConfig("2017","Rates");
  MakeSFFileConfig("2018","Rates");

}

void MakeSFFileConfig(TString era, TString HistDir){

  TString mc_path  = "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_ChargeFlip/"+era +"/"+HistDir+"/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";

  TFile * fmc   = new TFile(mc_path);
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "HNL_CF_Electron_"+era+"_"+HistDir+".root";
  cout <<  mc_path << endl;
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  TString year = era;
  if(era.Contains("16")) year = "2016";
  

  std::vector<TString> IDs={"POGTight",
			    "HNL_ULID_"+year,
			    "HNTightV2"};
  vector<TString> EtaBins  = {"MergedEtaRegion1","MergedEtaRegion2","MergedEtaRegion3",
			      "EtaRegion1","EtaRegion2","EtaRegion3",
			      "EtaRegion4","EtaRegion5","EtaRegion6",
			      "EtaRegion7","EtaRegion8","EtaRegion9"};

  for(unsigned int i=0; i < IDs.size(); i++){
    for(auto iEta : EtaBins){
      
      TString denom = IDs[i] +"/CFrate/"+iEta+"_Denom";
      TString num   = IDs[i] +"/CFrate/"+iEta+"_Num";
      
      TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
      TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
      
      
      TString name = IDs[i] ;
      
      TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(("CFRate_PtInv_"+iEta+"_"+name).Data());
      mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
      mc_eff_rate->Write();
      
    }
    
    for(auto iEta : EtaBins){
      
      TString denom = IDs[i] +"/CFratePt/"+iEta+"_Denom";
      TString num   = IDs[i] +"/CFratePt/"+iEta+"_Num";
      
      TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
      TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
      
      TString name = IDs[i] ;
      TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(("CFRate_Pt_"+iEta+"_"+name).Data());
      mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
      mc_eff_rate->Write();
      
    }

    
  }



  return;
}

