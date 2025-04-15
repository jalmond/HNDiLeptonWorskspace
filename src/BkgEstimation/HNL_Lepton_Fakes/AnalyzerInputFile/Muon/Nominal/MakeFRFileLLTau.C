#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="MuMu", TString PtType="Pt");
TString DoubleToString(double d);


void MakeFRFileLLTau(){

  MakeFRFile("2016preVFP","MuMu","PtCone");
  MakeFRFile("2016postVFP","MuMu","PtCone");
  MakeFRFile("2017","MuMu","PtCone");
  MakeFRFile("2018","MuMu","PtCone");

}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" ){


  
  TString path= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+year+"/RunRatesTauAnalysis__/HNL_Lepton_FakeRate_Data_FakeMuon.root";

  TString mcpath= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+year+"/RunRatesTauAnalysis__/HNL_Lepton_FakeRate_MC.root";

    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_WRTau_Mu_"+era+"_HNL_"+PtType+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {"WRTau_ResolvedMuMu_AJ40_pt_eta"};
  //Fake_PtCone_LooseMuMu_WRTau_Resolved_MuMu_AJ40_ptcone_eta
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    
    if(PtType=="PtCone")      ID=ID.ReplaceAll("pt_eta","ptcone_eta");
   
    TString denom = PtType+"/Fake_"+PtType+"_LooseMuMu_" +ID;
    TString num   = PtType+"/Fake_"+PtType+"_TightMuMu_" +ID;
    cout << "denom = " << denom << endl;
    
    TH2D* h_pt_num= (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fdata->Get(denom.Data());
    TH2D* h_mcpt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_mcpt_denom= (TH2D*)fmc->Get(denom.Data());

    if (!h_pt_num){
      cout << path << endl;
      cout << mcpath << endl;
      cout << num << endl;
      cout << denom << endl;
      cout << "FakeRate\t Fake_|_" +ID +"_MuMu_40 ptcone_eta"  << "\t" << "central " << outfile << endl;
      
      cout << h_pt_num << " " << h_pt_denom << endl;
      cout << h_mcpt_num << " " << h_mcpt_denom << endl;
    }
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TString name = IDs[i] ;
    if(IDs[i] == "PekingMuMu_Central_pt_eta") name = "Peking_pt_eta";
    if(IDs[i] == "HNTightV2MuMu_Central_pt_eta") name = "HNTightV2_pt_eta";
    
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
