#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="EE", TString PtType="Pt", TString sFile="MC");
TString DoubleToString(double d);


void MakeMVA_FR_FileLL(){
  
  for(auto iera : {"2016preVFP","2016postVFP","2017","2018"}){



    TString sEra = iera;
    if(sEra.Contains("2016")) sEra = "2016";


    vector<TString> vIDs = {
      "HNL_ULID_FO_v0_"+sEra+"_MC",
      "HNL_ULID_FO_v1_a_"+sEra+"_MC",
      "HNL_ULID_FO_v1_b_"+sEra+"_MC",
      "HNL_ULID_FO_v1_c_"+sEra+"_MC",
      "HNL_ULID_FO_v2_a_"+sEra+"_MC",
      "HNL_ULID_FO_v2_b_"+sEra+"_MC",
      "HNL_ULID_FO_v2_c_"+sEra+"_MC",
      "HNL_ULID_FO_v3_a_"+sEra+"_MC",
      "HNL_ULID_FO_v3_b_"+sEra+"_MC",
      "HNL_ULID_FO_v3_c_"+sEra+"_MC",
      "HNL_ULID_FO_v4_a_"+sEra+"_MC",
      "HNL_ULID_FO_v4_b_"+sEra+"_MC",
      "HNL_ULID_FO_v4_c_"+sEra+"_MC",
      "HNL_ULID_FO_v5_a_"+sEra+"_MC",
      "HNL_ULID_FO_v5_b_"+sEra+"_MC",
      "HNL_ULID_FO_v5_c_"+sEra+"_MC",
      "HNL_ULID_FO_v6_a_"+sEra+"_MC",
      "HNL_ULID_FO_v6_b_"+sEra+"_MC",
      "HNL_ULID_FO_v6_c_"+sEra+"_MC",
      "HNL_ULID_FO_v7_a_"+sEra+"_MC",
      "HNL_ULID_FO_v7_b_"+sEra+"_MC",
      "HNL_ULID_FO_v7_c_"+sEra+"_MC",
      "HNL_ULID_FO_v8_a_"+sEra+"_MC",
      "HNL_ULID_FO_v8_b_"+sEra+"_MC",
      "HNL_ULID_FO_v8_c_"+sEra+"_MC",
      "HNL_ULID_FO_v9_a_"+sEra+"_MC",
      "HNL_ULID_FO_v9_b_"+sEra+"_MC",
      "HNL_ULID_FO_v9_c_"+sEra+"_MC",

    };

    for (auto id : vIDs){
      MakeFRFile(iera,id,"Pt","MC");
      MakeFRFile(iera,id,"PtParton","MC");
    }
  }
}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" , TString sFile="MC"){

  TString mcpath= "/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_FakeRate_MC/"+year+"/MCFakes__/HNL_Lepton_FakeRate_MC_QCDEl.root";

  cout << mcpath << endl;
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_"+sFile+"_El_"+dataset+"_"+era+"_HNL_ULID_"+PtType+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();


  std::vector<TString> IDs = {"MCFake_AJ25_pt_eta",
			      "MCFake_AJ30_pt_eta",
			      "MCFake_AJ40_pt_eta",
			      "MCFake_AJ60_pt_eta" };

  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    if(PtType=="PtParton")    ID=ID.ReplaceAll("pt","ptparton");
   
    TString denom = "EE_"+dataset+"/"+PtType+"/Fake_"+PtType+"_Loose" +ID;
    TString num   = "EE_"+dataset+"/"+PtType+"/Fake_"+PtType+"_Tight" +ID;

    cout << num << endl;
    TH2D* h_pt_num= (TH2D*)fmc->Get(num.Data());
    TH2D* h_pt_denom= (TH2D*)fmc->Get(denom.Data());

    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);

    TString name = IDs[i] ;

    if(IDs[i] == "MCFake_AJ25_pt_eta")          name =  "pt_eta_"+dataset+"_AJ25";
    if(IDs[i] == "MCFake_AJ30_pt_eta")          name =  "pt_eta_"+dataset+"_AJ30";
    if(IDs[i] == "MCFake_AJ40_pt_eta")          name =  "pt_eta_"+dataset+"_AJ40";
    if(IDs[i] == "MCFake_AJ60_pt_eta")          name =  "pt_eta_"+dataset+"_AJ60";
    
    if(PtType=="PtParton")    name=name.ReplaceAll("pt","ptparton");
    if(PtType=="PtCorr")      name=name.ReplaceAll("pt","ptcorr");
    name=name.ReplaceAll("HNL_ID","HNL_ULID");


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
