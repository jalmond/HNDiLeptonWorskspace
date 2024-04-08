#include "Macros.h"
#include "mylib.h"

void MakeFRFile(TString year,TString dataset="EE", TString PtType="Pt");
TString DoubleToString(double d);


void MakeFRFileLL(){

  MakeFRFile("2016preVFP","EE","Pt");
  MakeFRFile("2016preVFP","EE","PtParton");
  MakeFRFile("2016preVFP","EE","PtCorr");


  MakeFRFile("2016postVFP","EE","Pt");
  MakeFRFile("2016postVFP","EE","PtParton");
  MakeFRFile("2016postVFP","EE","PtCorr");

  MakeFRFile("2017","EE","Pt");
  MakeFRFile("2017","EE","PtParton");
  MakeFRFile("2017","EE","PtCorr");

  MakeFRFile("2018","EE","Pt");
  MakeFRFile("2018","EE","PtParton");
  MakeFRFile("2018","EE","PtCorr");

}

void MakeFRFile(TString year, TString dataset="EE",TString PtType="Pt" ){

  TString path= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+year+"/RunRatesEE__/HNL_Lepton_FakeRate_Data_FakeElectron.root";
  TString mcpath= "/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/Run2UltraLegacy_v3/HNL_Lepton_FakeRate/"+year+"/RunRatesEE__/HNL_Lepton_FakeRate_MC.root";

    
  TFile * fdata = new TFile(path);
  TFile * fmc = new TFile(mcpath);

  /// Set Plotting style  
  PlottingSetup();

  TString era=year;
  if( era.Contains("2016pre")) era = "2016a";
  if( era.Contains("2016post")) era = "2016b";
  TString Year=year;
  if( era.Contains("2016"))  Year= "2016";
  TString outfile = "FR_EGamma_"+era+"_HNL_ULID_"+PtType+"_v4.root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();



  std::vector<TString> IDs = {    "HNL_ULID_FO_v0_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v1_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v1_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v1_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v2_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v2_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v2_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v3_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v3_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v3_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v4_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v4_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v4_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v5_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v5_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v5_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v6_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v6_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v6_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v7_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v7_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v7_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v8_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v8_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v8_c_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v9_a_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v9_b_"+Year+"EE_AJ25_pt_eta",
                                  "HNL_ULID_FO_v9_c_"+Year+"EE_AJ25_pt_eta",
                                  
                                  "HNL_ULID_FO_v0_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v1_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v1_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v1_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v2_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v2_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v2_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v3_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v3_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v3_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v4_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v4_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v4_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v5_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v5_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v5_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v6_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v6_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v6_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v7_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v7_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v7_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v8_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v8_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v8_c_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v9_a_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v9_b_"+Year+"EE_AJ30_pt_eta",
                                  "HNL_ULID_FO_v9_c_"+Year+"EE_AJ30_pt_eta",


                                  "HNL_ULID_FO_v0_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v1_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v1_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v1_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v2_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v2_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v2_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v3_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v3_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v3_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v4_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v4_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v4_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v5_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v5_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v5_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v6_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v6_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v6_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v7_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v7_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v7_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v8_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v8_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v8_c_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v9_a_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v9_b_"+Year+"EE_AJ40_pt_eta",
                                  "HNL_ULID_FO_v9_c_"+Year+"EE_AJ40_pt_eta"};
                                  

  
  for(unsigned int i=0; i < IDs.size(); i++){
    
    TString ID = IDs[i];
    if(PtType=="PtParton")    ID=ID.ReplaceAll("pt_eta","ptparton_eta");
    if(PtType=="PtCorr")      ID=ID.ReplaceAll("pt_eta","ptcorr_eta");
    if(PtType=="MotherPt")    ID=ID.ReplaceAll("pt_eta","MJpt_eta");
   
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

    vector<TString> AJs = {"AJ25", "AJ30","AJ40"};
    for (auto ij : AJs){

      if(IDs[i] == "HNL_ULID_FO_v0_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v0_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v1_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v1_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v1_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v1_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v1_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v1_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v2_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v2_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v2_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v2_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v2_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v2_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v3_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v3_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v3_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v3_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v3_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v3_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v4_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v4_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v4_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v4_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v4_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v4_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v5_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v5_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v5_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v5_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v5_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v5_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v6_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v6_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v6_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v6_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v6_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v6_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v7_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v7_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v7_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v7_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v7_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v7_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v8_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v8_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v8_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v8_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v8_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v8_c_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v9_a_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v9_a_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v9_b_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v9_b_"+ij;
      if(IDs[i] == "HNL_ULID_FO_v9_c_"+Year+"EE_"+ij+"_pt_eta") name = "pt_eta_HNL_ULID_FO_v9_c_"+ij;


      if(PtType=="PtParton")    name=name.ReplaceAll("pt_eta","ptparton_eta");
      if(PtType=="PtCorr")      name=name.ReplaceAll("pt_eta","ptcorr_eta");
      if(PtType=="MotherPt")    name=name.ReplaceAll("pt_eta","mjpt_eta");
    }


    TString SaveName = ("HNL_ULID_"+Year+"_"+name);
    if(name.Contains("ULLI")) SaveName = ("HNL_ULLID_"+name);


    TH2D* eff_rate = (TH2D*)h_pt_num->Clone(SaveName.Data());

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
