#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="MuMu", TString PtType="Pt", TString sFile="MC");
TString DoubleToString(double d);


void MakeMVA_FR_FileLL(){

  MakeFRFile("2017","HNL_ID","Pt","MC");
  MakeFRFile("2017","HNL_ID","PtParton","MC");
  MakeFRFile("2017","HNL_ID","PtCorr","MC");

  MakeFRFile("2017","HNL_ID_Weighted","Pt","MC");
  MakeFRFile("2017","HNL_ID_Weighted","PtParton","MC");
  MakeFRFile("2017","HNL_ID_Weighted","PtCorr","MC");

  MakeFRFile("2017","HNL_IDv2","Pt","MC");
  MakeFRFile("2017","HNL_IDv2","PtParton","MC");
  MakeFRFile("2017","HNL_IDv2","PtCorr","MC");
  
  MakeFRFile("2017","HNL_IDv2_Weighted","Pt","MC");
  MakeFRFile("2017","HNL_IDv2_Weighted","PtParton","MC");
  MakeFRFile("2017","HNL_IDv2_Weighted","PtCorr","MC");

  MakeFRFile("2017","HNL_IDv7","Pt","MC");
  MakeFRFile("2017","HNL_IDv7","PtParton","MC");
  MakeFRFile("2017","HNL_IDv7","PtCorr","MC");

  MakeFRFile("2017","HNL_IDv7_Weighted","Pt","MC");
  MakeFRFile("2017","HNL_IDv7_Weighted","PtParton","MC");
  MakeFRFile("2017","HNL_IDv7_Weighted","PtCorr","MC");


}

void MakeFRFile(TString year, TString dataset="MuMu",TString PtType="Pt" , TString sFile="MC"){

  TString mcpath= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_LeptonFakeRateMC/"+year+"/MCFakes__/HNL_LeptonFakeRateMC_SkimTree_FakeEventSkimBDT_MC.root";


  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_"+sFile+"_Mu_"+dataset+era+"_HNL_ULID_"+PtType+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  std::vector<TString> IDs = {"MCFake_J25_pt_eta",
			      "MCFake_J30_pt_eta",
			      "MCFake_J40_pt_eta",
			      "MCFake_J60_pt_eta",
			      "MCFake_J25_BJet1_pt_eta",
                              "MCFake_J30_BJet1_pt_eta",
                              "MCFake_J40_BJet1_pt_eta",
                              "MCFake_J60_BJet1_pt_eta",
			      "MCFake_J25_BJet2_pt_eta",
                              "MCFake_J30_BJet2_pt_eta",
                              "MCFake_J40_BJet2_pt_eta",
                              "MCFake_J60_BJet2_pt_eta",
			      "MCFake_J25_BJet3_pt_eta",
                              "MCFake_J30_BJet3_pt_eta",
                              "MCFake_J40_BJet3_pt_eta",
                              "MCFake_J60_BJet3_pt_eta",
  };

  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    if(PtType=="PtParton")    ID=ID.ReplaceAll("pt","ptparton");
    if(PtType=="PtCorr")      ID=ID.ReplaceAll("pt","ptcorr");
   
    TString denom = "MuMu_"+dataset+"/"+PtType+"/Fake_"+PtType+"_Loose" +ID;
    TString num   = "MuMu_"+dataset+"/"+PtType+"/Fake_"+PtType+"_Tight" +ID;

    cout << num << endl;
    TH2D* h_pt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fmc->Get(denom.Data());

    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);

    TString name = IDs[i] ;

    if(IDs[i] == "MCFake_J25_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J25";
    if(IDs[i] == "MCFake_J30_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J30";
    if(IDs[i] == "MCFake_J40_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J40";
    if(IDs[i] == "MCFake_J60_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J60";
    
    if(IDs[i] == "MCFake_J25_BJet1_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J25_BJet1";
    if(IDs[i] == "MCFake_J30_BJet1_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J30_BJet1";
    if(IDs[i] == "MCFake_J40_BJet1_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J40_BJet1";
    if(IDs[i] == "MCFake_J60_BJet1_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J60_BJet1";

    if(IDs[i] == "MCFake_J25_BJet2_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J25_BJet2";
    if(IDs[i] == "MCFake_J30_BJet2_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J30_BJet2";
    if(IDs[i] == "MCFake_J40_BJet2_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J40_BJet2";
    if(IDs[i] == "MCFake_J60_BJet2_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J60_BJet2";


    if(IDs[i] == "MCFake_J25_BJet3_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J25_BJet3";
    if(IDs[i] == "MCFake_J30_BJet3_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J30_BJet3";
    if(IDs[i] == "MCFake_J40_BJet3_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J40_BJet3";
    if(IDs[i] == "MCFake_J60_BJet3_pt_eta")          name =  "pt_eta_"+dataset+"_FO_J60_BJet3";


    name = name.ReplaceAll("IDv2_FO","ID_FOv2");
    name = name.ReplaceAll("IDv7_FO","ID_FOv7");

    if(PtType=="PtParton")    name=name.ReplaceAll("pt","ptparton");
    if(PtType=="PtCorr")      name=name.ReplaceAll("pt","ptcorr");

    TH2D* eff_rate = (TH2D*)h_pt_num->Clone(("HNL_ULID_"+Year+"_MC_"+name+"_FR_cent").Data());

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
	cout << x << " " << y  << " " <<  eff_rate->GetBinContent(x,y) << endl;
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
