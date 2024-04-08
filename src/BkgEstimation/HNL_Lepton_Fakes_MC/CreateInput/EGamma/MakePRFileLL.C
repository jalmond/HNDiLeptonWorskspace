#include "Macros.h"
#include "mylib.h"

void MakePRFile(TString year,TString dataset="EE");
TString DoubleToString(double d);


void MakePRFileLL(){

  MakePRFile("2016preVFP","EE");
  MakePRFile("2016postVFP","EE");
  MakePRFile("2017","EE");
  MakePRFile("2018","EE");

}

void MakePRFile(TString year, TString dataset="EE" ){

  TString path= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRate/"+year+"/RunRatesEE__/HNL_LeptonFakeRate_Data_PromptElectron.root";
  TFile * fdata = new TFile(path);
  
  /// Set Plotting style
  PlottingSetup();
  
  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year = year;
  if( era.Contains("2016")) Year = "2016";

  TString outfile = "PR_EGamma_"+era+"_HNL_ULID.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {"HNL_ULID_FOEE_pt_eta",
                              "HNL_ULID_FOv2EE_pt_eta",
                              "HNL_ULID_FOv3EE_pt_eta",
                              "HNL_ULID_FOv4EE_pt_eta",
                              "HNL_ULID_FOv5EE_pt_eta",
                              "HNL_ULID_FOv6EE_pt_eta"};
  
  for(unsigned int i=0; i < IDs.size(); i++){
   
    
    TString denom = "PrompRate/Prompt_LooseEE_"+IDs[i];
    TString num   = "PrompRate/Prompt_TightEE_"+IDs[i];
    
    TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());

    if (!h_pt_num){
      cout << path << endl;
      cout << num << endl;
      cout << denom << endl;
      cout << "PromptRate\t Fake_TightEE_El_" +IDs[i] +"_EE_40 ptcone_eta"  << "\t" << "central " << outfile << endl;
      cout << h_pt_num << " " << h_pt_denom << endl;
    }

    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TString name = IDs[i] ;

    if(IDs[i] == "HNL_ULID_FOEE_pt_eta")    name ="pt_eta_HNL_ULID_FO";
    if(IDs[i] == "HNL_ULID_FOv2EE_pt_eta") name ="pt_eta_HNL_ULID_FOv2";
    if(IDs[i] == "HNL_ULID_FOv3EE_pt_eta") name ="pt_eta_HNL_ULID_FOv3";
    if(IDs[i] == "HNL_ULID_FOv4EE_pt_eta") name ="pt_eta_HNL_ULID_FOv4";
    if(IDs[i] == "HNL_ULID_FOv5EE_pt_eta") name ="pt_eta_HNL_ULID_FOv5";
    if(IDs[i] ==" HNL_ULID_FOv6EE_pt_eta") name ="pt_eta_HNL_ULID_FOv6";
    

    TH2D* eff_rate   = (TH2D*)h_pt_num->Clone(("HNL_ULID_"+Year+"_"+name+"_PR_cent").Data());
    TH2D* hratedenom = (TH2D*)h_pt_denom->Clone((name +"_denom").Data());
    
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
