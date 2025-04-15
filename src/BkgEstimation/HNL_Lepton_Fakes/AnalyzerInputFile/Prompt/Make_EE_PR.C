#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="EE", TString PtType="Pt");
TString DoubleToString(double d);


void Make_EE_PR(){

  MakeFRFile("2016preVFP","EE","PtParton");
  MakeFRFile("2016postVFP","EE","PtParton");
  MakeFRFile("2017","EE","PtParton");
  MakeFRFile("2018","EE","PtParton");


}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" ){


  TString mcpath= "/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/" +year+"/RunPromptRatesEE__/HNL_Lepton_FakeRate_SkimTree_DileptonBDT_DYJetsToEE_MiNNLO.root";

    
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "PR_El_"+era+"_HNL_HighPt_ULID_"+PtType+"_v1.root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {    
    "HNL_HighPt_ULID_"+Year+"EE_pt_eta",
    "HNTightV2EE_pt_eta"
  };
  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];

    TString denom = "PrompRate/Prompt_LooseEE_" +ID;
    TString num   = "PrompRate/Prompt_TightEE_" +ID;
    
    TH2D* h_pt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fmc->Get(denom.Data());

    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);

    TString name = IDs[i] ;

    TH2D* eff_rate = (TH2D*)h_pt_num->Clone(name);
    
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
