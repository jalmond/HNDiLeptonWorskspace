#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="EE", TString PtType="Pt");
TString DoubleToString(double d);


void MakeFRFileLL_1D(){

  //  MakeFRFile("2016preVFP","EE","Pt");
  MakeFRFile("2016preVFP","EE","PtParton");
  //  MakeFRFile("2016postVFP","EE","Pt");
  MakeFRFile("2016postVFP","EE","PtParton");
  //  MakeFRFile("2017","EE","Pt");
  MakeFRFile("2017","EE","PtParton");
  //  MakeFRFile("2018","EE","Pt");
  MakeFRFile("2018","EE","PtParton");


}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" ){


  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/April19/"+year+"/RunRatesEE__/HNL_Lepton_FakeRate_Data_FakeElectron.root";
  TString mcpath= TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/April19/"+year+"/RunRatesEE__/HNL_Lepton_FakeRate_MC.root";

    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_EGamma_"+era+"_HNL_ULID_"+PtType+"_1D.root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();


  std::vector<TString> IDs = {    "HNL_ULID_FO_v0_"+Year+"EE_AJ40_pt_BB",
                                  "HNL_ULID_FO_v9_a_"+Year+"EE_AJ40_pt_BB",
				  "HNL_ULID_FO_v0_"+Year+"EE_AJ40_pt_EC",
                                  "HNL_ULID_FO_v9_a_"+Year+"EE_AJ40_pt_EC"};



  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    if(PtType=="PtParton")    ID=ID.ReplaceAll("pt_eta","ptparton_eta");
    if(PtType=="PtCorr")      ID=ID.ReplaceAll("pt_eta","ptcorr_eta");
    if(PtType=="MotherPt")    ID=ID.ReplaceAll("pt_eta","MJpt_eta");
   
    TString denom = PtType+"/Fake_"+PtType+"_LooseEE_" +ID;
    TString num   = PtType+"/Fake_"+PtType+"_TightEE_" +ID;
    
    TH1D* h_pt_num= (TH1D*)fdata->Get(num.Data());
    TH1D* h_pt_denom= (TH1D*)fdata->Get(denom.Data());
    TH1D* h_mcpt_num= (TH1D*)fmc->Get(num.Data());
    TH1D* h_mcpt_denom= (TH1D*)fmc->Get(denom.Data());

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
    vector<TString> AJs = {"AJ40"};

    name = IDs[i];
    name = name.ReplaceAll(Year+"MuMu_","");


    TH1D* eff_rate = (TH1D*)h_pt_num->Clone(("HNL_ULID_"+Year+"_"+name).Data());
    eff_rate->Add(h_mcpt_num,-1.);
    TH1D* hratedenom = (TH1D*)h_pt_denom->Clone((name +"_denom").Data());
    hratedenom->Add(h_mcpt_denom,-1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write(); 


    TH1D* eff_rate_MCSubSys = (TH1D*)h_pt_num->Clone(("HNL_ULID_MCSubSys_"+Year+"_"+name).Data());
    eff_rate_MCSubSys->Add(h_mcpt_num,-1.2);
    TH1D* hratedenom_MCSubSys = (TH1D*)h_pt_denom->Clone((name +"_MCSubSys_denom").Data());
    hratedenom_MCSubSys->Add(h_mcpt_denom,-1.2);
    eff_rate_MCSubSys->Divide(eff_rate_MCSubSys,hratedenom_MCSubSys,1.,1.,"cl=0.683 b(1,1) mode");
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
