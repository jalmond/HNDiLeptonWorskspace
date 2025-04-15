#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="EE", TString PtPartonType="PtParton");
TString DoubleToString(double d);


void MakeFRFileLLOther(){

  MakeFRFile("2018","EE","PtParton");

}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" ){


  TString path = TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/Jan27_HEM/HEMJetFakesEE__/" + year + "/HNL_Lepton_FakeRate_Data_FakeElectron.root";
  TString mcpath = TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/Jan27_HEM/HEMJetFakesEE__/" + year + "/HNL_Lepton_FakeRate_MC.root";

    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_EGamma_HEM_"+era+"_HNL_"+PtType+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {"HNL_ULID_2018EE_AJ40_ptparton_eta"};
  //Fake_PtParton_LooseEE_HNL_ULID_2018EE_AJ40_ptparton_eta
  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    
    if(PtType=="PtCone")      ID=ID.ReplaceAll("pt_eta","ptcone_eta");
   
    TString denom = PtType+"/Fake_"+PtType+"_LooseEE_" +ID;
    TString num   = PtType+"/Fake_"+PtType+"_TightEE_" +ID;
    
    TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());
    TH2D* h_mcpt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_mcpt_denom= (TH2D*)fmc->Get(denom.Data());

    if (!h_pt_num){
      cout << path << endl;
      cout << mcpath << endl;
      cout << num << endl;
      cout << denom << endl;
      cout << "FakeRate\t Fake_|_" +ID +"_EE_40 ptcone_eta"  << "\t" << "central " << outfile << endl;
      
      cout << h_pt_num << " " << h_pt_denom << endl;
      cout << h_mcpt_num << " " << h_mcpt_denom << endl;
    }
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TString name = IDs[i] ;
    if(IDs[i] == "PekingEE_Central_pt_eta")    name = "Peking_pt_eta";
    if(IDs[i] == "HNTightV2EE_Central_pt_eta") name = "HNTightV2_pt_eta";
    if(IDs[i] == "passHEEPID_v1EE_AJ40_pt_eta") name = "passHEEPID_v1_pt_eta";
    if(IDs[i] == "passHEEPID_v2EE_AJ40_pt_eta") name = "passHEEPID_v2_pt_eta";
    if(IDs[i] == "passHEEPID_v3EE_AJ40_pt_eta") name = "passHEEPID_v3_pt_eta";


    if(PtType=="PtCone")    name=name.ReplaceAll("pt_eta","ptcone_eta");

    TH2D* eff_rate = (TH2D*)h_pt_num->Clone((name+"_FR_cent").Data());

    eff_rate->Add(h_mcpt_num,-1.);
    
    TH2D* hratedenom = (TH2D*)h_pt_denom->Clone((name +"_denom").Data());
    hratedenom->Add(h_mcpt_denom,-1.);
    
    for(int x = 1 ; x < eff_rate->GetNbinsX()+1 ; x++){
      for(int y = 1 ; y < eff_rate->GetNbinsY()+1 ; y++){
	if(eff_rate->GetBinContent(x,y) <= 0) eff_rate->SetBinContent(x,y,1);
      }
    }
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
        
    cout << "-----------------------------------------------------" << endl;
    cout << name << endl;
    for(int x = 1 ; x < eff_rate->GetNbinsX()+1 ; x++){
      for(int y = 1 ; y < eff_rate->GetNbinsY()+1 ; y++){
	cout << x << " : " << y << " " << eff_rate->GetBinContent(x,y) << endl;

      }
    }
    cout << "-----------------------------------------------------" << endl;

    eff_rate->Write();
    


  }


  return;
}
  
  
  


TString DoubleToString(double d){

  std::string str = std::to_string (d);
  str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
  str.erase ( str.find_last_not_of('.') + 1, std::string::npos );

  TString ts_str = TString(str);
  ts_str = ts_str.ReplaceAll(".","p");
  ts_str = ts_str.ReplaceAll("-","neg");

  return ts_str;

  
}
