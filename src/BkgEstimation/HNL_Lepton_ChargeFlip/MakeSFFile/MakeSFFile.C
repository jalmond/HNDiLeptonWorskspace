#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeSFFileConfig(TString year, TString hist);

void MakeSFFile(){
  
  //MakeSFFileConfig("2016a","Rates");
  //MakeSFFileConfig("2016b","Rates");
  MakeSFFileConfig("2017","Rates");
  // MakeSFFileConfig("2018","Rates");

}

void MakeSFFileConfig(TString era, TString HistDir){

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/"+era+"/Rates/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_Rates.root";

  TFile * fmc   = new TFile(path);

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "HNL_CF_Electron_"+era+"_"+HistDir+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  TString year = era;
  if(era.Contains("16")) year = "2016";
  

  std::vector<TString> IDs={"HNL_ULID_"+year};
			    
  vector<TString> HistBins  = {"CFRate_InvPtEta", "CFRate_InvPtEta2", "CFRate_InvPtEta3","CFRate_PtEta","CFRate_PtEta2","CFRate_PtEta3"};
  vector<TString> MethodBins  = {"CS","NoS","PBS"};

  for(unsigned int i=0; i < IDs.size(); i++){
    for(auto HistBin : HistBins){
      for( auto Method : MethodBins){

	TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";
      
	TH2D* h_mc_num   = (TH2D*)fmc->Get(num.Data());
	TH2D* h_mc_denom = (TH2D*)fmc->Get(denom.Data());
	
	TString name = IDs[i] ;
	
	TH2D* mc_eff_rate = (TH2D*)h_mc_num->Clone((HistBin+"_"+Method+"_"+name).Data());
	mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	mc_eff_rate->Write();
	
      }
    }
  }



  return;
}

