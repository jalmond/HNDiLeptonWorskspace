#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeSFFileConfig(TString year, TString hist, TString DateTag, TString InFile, TString OutFile );

void MakeSFFile(){
  
  MakeSFFileConfig("2016a","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version4_AllDY_Electron_");
  MakeSFFileConfig("2016b","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version4_AllDY_Electron_");
  MakeSFFileConfig("2017","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version4_AllDY_Electron_");
  MakeSFFileConfig("2018","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version4_AllDY_Electron_");
  

  MakeSFFileConfig("2016a","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYTop_Rates.root","HNL_CF_Version4_DYTop_Electron_");
  MakeSFFileConfig("2016b","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYTop_Rates.root","HNL_CF_Version4_DYTop_Electron_");
  MakeSFFileConfig("2017","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYTop_Rates.root","HNL_CF_Version4_DYTop_Electron_");
  MakeSFFileConfig("2018","Rates","May8", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYTop_Rates.root","HNL_CF_Version4_DYTop_Electron_");

}

void MakeSFFileConfig(TString era, TString HistDir, TString DateTag, TString InFile, TString OutFile ){

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/Rates/"+DateTag+"/"+era+"/"+InFile;
  cout << path << endl;
  TFile * fmc   = new TFile(path);

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = OutFile +era+"_"+HistDir+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  TString year = era;
  if(era.Contains("16")) year = "2016";
  

  std::vector<TString> IDs={"HNL_TC1_ULID_"+year, "POGTight","HNTightV2", "TopHN"};
			    
  vector<TString> HistBins  = {"CFRate_InvPtEta1","CFRate_PtEta1","CFRate_InvPtEta3","CFRate_PtEta3","CFRate_InvPtEtaBB1","CFRate_InvPtEtaBB2","CFRate_InvPtEta2BB2","CFRate_InvPtEtaEC1","CFRate_InvPtEtaEC2"};

  vector<TString> MethodBins  = {"CS_Central","NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma", "CS_MSigma","CS_PSigma"};


  for(unsigned int i=0; i < IDs.size(); i++){
    for(auto HistBin : HistBins){
      for( auto Method : MethodBins){

	TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";
	cout << num << endl;
	TH2D* h_mc_num   = (TH2D*)fmc->Get(num.Data());
	TH2D* h_mc_denom = (TH2D*)fmc->Get(denom.Data());
	
	TString name = IDs[i] ;
	if(name.Contains("Top")) name  = "TopHNSST";
	if(InFile.Contains("DYTop")) name = "DYTop_"+name;
	if(Method=="NoS") Method="NoS_Central";
	if(name == "HNL_TC1_ULID_"+year) name = "HNL_ULID_"+year;
	TH2D* mc_eff_rate = (TH2D*)h_mc_num->Clone((HistBin+"_"+Method+"_"+name).Data());
	mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	mc_eff_rate->Write();
	
      }
    }
  }



  return;
}

