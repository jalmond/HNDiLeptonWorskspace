#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="MuMu", TString PtType="Pt");
TString DoubleToString(double d);


void MakeMVA_FR_FileLL_1D(){

  //  MakeFRFile("2016preVFP","MuMu","Pt");
  MakeFRFile("2016preVFP","MuMu","PtParton");
  //  MakeFRFile("2016postVFP","MuMu","Pt");
  MakeFRFile("2016postVFP","MuMu","PtParton");
 
  // MakeFRFile("2017","MuMu","Pt");
  MakeFRFile("2017","MuMu","PtParton");
  
  //  MakeFRFile("2018","MuMu","Pt");
  MakeFRFile("2018","MuMu","PtParton");


}

void MakeFRFile(TString year, TString dataset="MuMu",TString PtType="Pt" ){


  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/"+year+"/RunRates__/HNL_Lepton_FakeRate_Data_FakeMuon.root";
  TString mcpath= TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/"+year+"/RunRates__/HNL_Lepton_FakeRate_MC.root"; 

    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_Mu_"+era+"_HNL_ULID_"+PtType+"_1D.root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {    "HNL_ULID_FO_v0_"+Year+"MuMu_AJ40_pt_BB",
				  "HNL_ULID_FO_v1_a_"+Year+"MuMu_AJ40_pt_BB",
				  "HNL_ULID_FO_v2_a_"+Year+"MuMu_AJ40_pt_BB",
				  "HNL_ULID_FO_v3_a_"+Year+"MuMu_AJ40_pt_BB",
				  "HNL_ULID_FO_v0_"+Year+"MuMu_AJ40_pt_EC",
                                  "HNL_ULID_FO_v1_a_"+Year+"MuMu_AJ40_pt_EC",
                                  "HNL_ULID_FO_v2_a_"+Year+"MuMu_AJ40_pt_EC",
                                  "HNL_ULID_FO_v3_a_"+Year+"MuMu_AJ40_pt_EC"};
				  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    //    if(PtType=="PtParton")    ID=ID.ReplaceAll("pt","ptparton_eta");

    TString denom = PtType+"/Fake_"+PtType+"_LooseMuMu_" +ID;
    TString num   = PtType+"/Fake_"+PtType+"_TightMuMu_" +ID;
    
    TH1D* h_pt_num= (TH1D*)fdata->Get(num.Data());
    TH1D* h_pt_denom= (TH1D*)fdata->Get(denom.Data());
    TH1D* h_mcpt_num= (TH1D*)fmc->Get(num.Data());
    TH1D* h_mcpt_denom= (TH1D*)fmc->Get(denom.Data());

    if (!h_pt_num){
      cout << path << endl;
      cout << mcpath << endl;
      cout << num << endl;
      cout << denom << endl;
      cout << "FakeRate Fake_" +ID +"_MuMu_40 ptcone_eta"  << "\t" << "central " << outfile << endl;
      
      cout << h_pt_num << " " << h_pt_denom << endl;
      cout << h_mcpt_num << " " << h_mcpt_denom << endl;
    }
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TString name = IDs[i] ;
    vector<TString> AJs = {"AJ40"};
    
    name = IDs[i];
    name = name.ReplaceAll(Year+"MuMu_","");
    
    TH1D* eff_rate = (TH1D*)h_pt_num->Clone(("HNL_ULID_"+Year+"_"+name).Data());
    eff_rate->Add(h_mcpt_num,-1.);
    TH1D* hratedenom = (TH1D*)h_pt_denom->Clone((name +"_denom").Data());
    hratedenom->Add(h_mcpt_denom,-1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
        

    TH1D* eff_rate_MCSubSys = (TH1D*)h_pt_num->Clone(("HNL_ULID_MCSubSys_"+Year+"_"+name).Data());
    eff_rate_MCSubSys->Add(h_mcpt_num,-1.2);
    TH1D* hratedenom_MCSubSys = (TH1D*)h_pt_denom->Clone((name +"_MCSubSys_denom").Data());
    hratedenom_MCSubSys->Add(h_mcpt_denom,-1.2);
    eff_rate_MCSubSys->Divide(eff_rate_MCSubSys,hratedenom_MCSubSys,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
    eff_rate_MCSubSys->Write();

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
