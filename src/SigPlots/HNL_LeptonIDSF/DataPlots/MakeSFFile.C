#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


bool CheckHist(TH2* h);
void MakeSFFileConfig(TString year, TString hist);

void MakeSFFile(){
  
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

  TString data_path= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonIDSF/"+year+"/HNL_LeptonIDSF_SkimTree_DileptonBDT_Data.root";
  TString mc_path  = "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonIDSF/"+year+"/HNL_LeptonIDSF_SkimTree_DileptonBDT_DYJets.root";

  TFile * fdata = new TFile(data_path);

  cout << data_path << endl;
  TFile * fmc   = new TFile(mc_path);
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "HNL_LeptonIDSF_Electron_"+year+"_"+hist+".root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs={"HNL_ULID_Run2_CF","HNL_ULID_Run2_Conv","HNL_ULID_Run2_CFPt","HNL_ULID_Run2_Fake",
			    "HNTightV2",
			    "HNL_ULID_Run2T",
                            "HNL_ULID_Run2L",
                            "HNL_ULID_Run2_CF",
                            "HNL_ULID_Run2_CFPt",
                            "HNL_ULID_Run2_Conv",
                            "HNL_ULID_Run2_Fake",
                            "HNL_ULID_2016",
                            "HNL_ULID_2017",
                            "HNL_ULID_2018"};

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
