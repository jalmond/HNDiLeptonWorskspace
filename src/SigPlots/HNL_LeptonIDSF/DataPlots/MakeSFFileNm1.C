#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


bool CheckHist(TH2* h);
void MakeSFFileConfig(TString year, TString hist);

void MakeSFFileNm1(){
  
  MakeSFFileConfig("2016postVFP","Pt16_Eta");
  MakeSFFileConfig("2016preVFP","Pt16_Eta");
  MakeSFFileConfig("2016","Pt16_Eta");
  MakeSFFileConfig("2017","Pt_Eta");
  MakeSFFileConfig("2018","Pt_Eta");

  MakeSFFileConfig("2016postVFP","Eta_Pt16");
  MakeSFFileConfig("2016preVFP","Eta_Pt16");
  MakeSFFileConfig("2016","Eta_Pt16");
  MakeSFFileConfig("2017","Eta_Pt");
  MakeSFFileConfig("2018","Eta_Pt");
}

void MakeSFFileConfig(TString year, TString hist){

  cout << " ---> year = " << year << "  : --> hist = " << hist << endl;

  TString data_path= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonIDSF/"+year+"/HNL_LeptonIDSF_SkimTree_DileptonBDT_Data.root";
  TString mc_path  = "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonIDSF/"+year+"/HNL_LeptonIDSF_SkimTree_DileptonBDT_DYJets.root";

  TFile * fdata = new TFile(data_path);

  cout << data_path << endl;
  TFile * fmc   = new TFile(mc_path);
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "HNL_Nm1_LeptonIDSF_Electron_"+year+"_"+hist+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs={"HNL_ULID_ScanCFVT_BDTG",
                            "HNL_ULID_ScanCFT_BDTG",
                            "HNL_ULID_ScanCFM_BDTG",
                            "HNL_ULID_ScanCFL_BDTG",
                            "HNL_ULID_ScanCFVL_BDTG",

                            "HNL_ULID_ScanCFVTPt_BDTG",
                            "HNL_ULID_ScanCFTPt_BDTG",
                            "HNL_ULID_ScanCFMPt_BDTG",
                            "HNL_ULID_ScanCFLPt_BDTG",
                            "HNL_ULID_ScanCFVLPt_BDTG",

                            "HNL_ULID_ScanFAKEVVT_BDTG",
                            "HNL_ULID_ScanFAKEVT_BDTG",
                            "HNL_ULID_ScanFAKET_BDTG",
                            "HNL_ULID_ScanFAKEM_BDTG",
                            "HNL_ULID_ScanFAKEL_BDTG",
                            "HNL_ULID_ScanFAKEVL_BDTG",
                            "HNL_ULID_ScanFAKEVVL_BDTG",

                            "HNL_ULID_ScanCONVVT_BDTG",
                            "HNL_ULID_ScanCONVT_BDTG",
                            "HNL_ULID_ScanCONVM_BDTG",
                            "HNL_ULID_ScanCONVL_BDTG",
			    "HNL_ULID_Run2"};

  
  for(unsigned int i=0; i < IDs.size(); i++){
      
    TString denom = "EE/"+hist+"_"+IDs[i] +"_denom";
    TString num   = "EE/"+hist+"_"+IDs[i] +"_num";
    cout << denom <<  " " << num << endl;
    
    TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());
    cout << h_pt_num << " " << h_pt_denom << endl;
    TH2D* h_mcpt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_mcpt_denom= (TH2D*)fmc->Get(denom.Data());
    
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);

    TString name = IDs[i] ;
    cout << h_pt_num << " " << h_mcpt_num << endl;

    
    TH2D* data_eff_rate = (TH2D*)h_pt_num->Clone(("Data_Eff_"+name).Data());
    data_eff_rate->Divide(data_eff_rate,h_pt_denom,1.,1.,"cl=0.683 b(1,1) mode");
    data_eff_rate->Write();
    
    TH2D* mc_eff_rate = (TH2D*)h_mcpt_num->Clone(("MC_Eff_"+name).Data());
    mc_eff_rate->Divide(mc_eff_rate,h_mcpt_denom,1.,1.,"cl=0.683 b(1,1) mode");
    mc_eff_rate->Write();
    
    TH2D* data_mc_SF= (TH2D*)data_eff_rate->Clone(("Data_MC_SF_"+hist+"_"+name).Data());
    data_mc_SF->Divide(data_mc_SF,mc_eff_rate,1.,1.,"cl=0.683 b(1,1) mode");
    data_mc_SF->Write();
    
    
  }

  return;
}




bool CheckHist(TH2* h ){
  bool hist_exist = true;
  if(!h){
    cout << "No histogram with name " << h->GetName() << endl;
    hist_exist= false;
  }
  return hist_exist;
}
