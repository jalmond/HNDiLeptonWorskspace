#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeSFFileConfig(TString year, TString hist, TString DateTag, TString InFile, TString OutFile );

void MakeSFFile(){
  
  MakeSFFileConfig("2016a","Rates","Oct1", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version6_Electron_");
  MakeSFFileConfig("2016b","Rates","Oct1", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version6_Electron_");
  MakeSFFileConfig("2017","Rates","Oct1", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version6_Electron_");
  MakeSFFileConfig("2018","Rates","Oct1", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version6_Electron_");
  MakeSFFileConfig("Run2","Rates","Oct1", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version6_Electron_");
 
}

void MakeSFFileConfig(TString era, TString HistDir, TString DateTag, TString InFile, TString OutFile ){

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/Rates/"+DateTag+"/"+era+"/"+InFile;
  cout << path << endl;
  TFile * fmc   = new TFile(path);

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = OutFile +era+"_"+HistDir+".root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  TString year = era;
  if(era.Contains("16")) year = "2016";
  

  std::vector<TString> IDs={"POGTight","HNTightV2", "TopHN", "HNL_ULID" ,"passHEEPID_v1","passHEEPID_v2","passHEEPID_v3"};

  //  Make 1D rates
  
  if(1){
    vector<TString> HistBins  = {"CFRate_Eta"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
        for( auto Method : MethodBins){

            TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
            TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";

            TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
            TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
            cout << denom << h_mc_denom << endl;
            cout << num << h_mc_num << endl;
            TString name = IDs[i] ;
            if(name.Contains("Top")) name  = "TopHNSST";
            if(InFile.Contains("DYTop")) name = "DYTop_"+name;

            TString  clonename = HistBin+"_FineEta_"+Method+"_"+name;

            if(Method=="NoS") clonename = HistBin+"_FineEta_"+Method+"_Central_"+name;

            TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(clonename.Data());
            mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");

            mc_eff_rate->Write();

	}
      }
    }
  }


  if(1){
    vector<TString> HistBins  = {"CFRate"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};


    
    vector<TString> EtaBins = {"EtaRegion1_","EtaRegion2_","EtaRegion3_","EtaRegion4_","EtaRegion5_","EtaRegion6_","EtaRegion7_","EtaRegionBB1_","EtaRegionBB2_"};
    
    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
	for( auto Method : MethodBins){
	  for( auto etab : EtaBins){
	    
	    TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/"+etab+"Denom";
	    TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/"+etab+"Num";

	    TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
	    TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
	    cout << denom << h_mc_denom << endl;
	    cout << num << h_mc_num << endl;
	    TString name = IDs[i] ;
	    if(name.Contains("Top")) name  = "TopHNSST";
	    if(InFile.Contains("DYTop")) name = "DYTop_"+name;

	    TString  clonename = HistBin+"_"+Method+"_"+etab+name;

	    if(Method=="NoS") clonename = HistBin+"_"+Method+"_Central_"+etab+name;

	    TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(clonename.Data());
	    mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	    
	    mc_eff_rate->Write();
	    
	  }
	}
      }
    }
  }


  if(1){
    vector<TString> HistBins  = {"CFRateInvNegEta","CFRateInvPosEta"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
        for( auto Method : MethodBins){
	  TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	  TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";
	  
	  TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
	  TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
	  cout << denom << h_mc_denom << endl;
	  cout << num << h_mc_num << endl;
	  TString name = IDs[i] ;
	  if(name.Contains("Top")) name  = "TopHNSST";
	  if(InFile.Contains("DYTop")) name = "DYTop_"+name;
	  
	  TString  clonename = HistBin+"_"+Method+"_"+name;

	  if(Method=="NoS") clonename = HistBin+"_"+Method+"_Central_"+name;
	  
	  TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(clonename.Data());
	  mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	  
	  mc_eff_rate->Write();
	  
        }
      }
    }
  }



  if(1){
    vector<TString> HistBins  = {"CFRate"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};
    
    vector<TString> EtaBins = {"absEta_BB1","absEta_BB2","absEta_EC1","absEta_EC2","absEta_Binning1","absEta_Binning2","absEta_Binning3"};
    
    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
	for( auto Method : MethodBins){
	  for( auto etab : EtaBins){
	    
	    TString denom = IDs[i] +"/"+HistBin+"_"+etab+"/"+Method+"/Denom";
	    TString num   = IDs[i] +"/"+HistBin+"_"+etab+"/"+Method+"/Num";
	    TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
	    TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
	    
	    TString name = IDs[i] ;
	    if(name.Contains("Top")) name  = "TopHNSST";
	    if(InFile.Contains("DYTop")) name = "DYTop_"+name;

            TString  clonename = HistBin+"_"+Method+"_"+etab+name;

            if(Method=="NoS") clonename = HistBin+"_"+Method+"_Central_"+etab+name;

            TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone((clonename).Data());
	    mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	    
	    mc_eff_rate->Write();
	    
	  }
	}
      }
    }
  }



  if(1){
    vector<TString> HistBins  = {"CFRateInv","CFRatePt"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
        for( auto Method : MethodBins){
	  
	  if(1){
	    TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	    TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";
	    TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
	    TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());

            cout << denom << h_mc_denom << endl;
            cout << num << h_mc_num << endl;
	    
	    TString name = IDs[i] ;
	    if(name.Contains("Top")) name  = "TopHNSST";
	    if(InFile.Contains("DYTop")) name = "DYTop_"+name;


            TString  clonename = HistBin+"_"+Method+"_"+name;

            if(Method=="NoS") clonename = HistBin+"_"+Method+"_Central_"+name;

	    
	    TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(clonename.Data());
	    mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	  
	    mc_eff_rate->Write();
	    
	  }
	  if(1){
	    TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/FineBinning_Denom";
            TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/FineBinning_Num";
            TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
            TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());

            TString name = IDs[i] ;
            if(name.Contains("Top")) name  = "TopHNSST";
            if(InFile.Contains("DYTop")) name = "DYTop_"+name;

            TString  clonename = HistBin+"_FineBinning_"+Method+"_"+name;

            if(Method=="NoS") clonename = HistBin+"_FineBinning_"+Method+"_Central_"+name;


            TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone(clonename.Data());
            mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");

            mc_eff_rate->Write();

	  }
        }
      }
    }
  }

  if(1){
    vector<TString> HistBins  = {"CFRateInvNegEta","CFRateInvPosEta","CFRate_Eta"};
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
        for( auto Method : MethodBins){

	  TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	  TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";

	  TH1D* h_mc_num   = (TH1D*)fmc->Get(num.Data());
	  TH1D* h_mc_denom = (TH1D*)fmc->Get(denom.Data());
	  
	  cout << denom << h_mc_denom << endl;
	  cout << num << h_mc_num << endl;

	  TString name = IDs[i] ;
	  if(name.Contains("Top")) name  = "TopHNSST";
	  if(InFile.Contains("DYTop")) name = "DYTop_"+name;
	  if(Method=="NoS") Method="NoS_Central";
	  TH1D* mc_eff_rate = (TH1D*)h_mc_num->Clone((HistBin+"_"+Method+"_"+name).Data());
	  mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	  
	  mc_eff_rate->Write();

        }
      }
    }
  }



  if(1){
    // Make 2D rates
    
    vector<TString> HistBins  = {"CFRate_InvPtEta1",
				 "CFRate_InvPtEta2",
				 "CFRate_InvPtEta3",
				 "CFRate_InvPt2Eta1",
                                 "CFRate_InvPt2Eta2",
                                 "CFRate_InvPt2Eta3",
				 "CFRate_InvPtEtaBB1",
                                 "CFRate_InvPtEtaBB2",
                                 "CFRate_InvPtEtaEC1",
                                 "CFRate_InvPtEtaEC2",
                                 "CFRate_InvPt2EtaBB1",
                                 "CFRate_InvPt2EtaBB2",
                                 "CFRate_InvPt2EtaEC1",
                                 "CFRate_InvPt2EtaEC2",
				 "CFRate_PtEta1",
				 "CFRate_PtEta3" };
    
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","PBSExtrap_MSigma","PBSExtrap_PSigma","CS_Central","CS_MSigma","CS_PSigma"};
    

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
	for( auto Method : MethodBins){
	  
	  TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	  TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";

	  TH2D* h_mc_num   = (TH2D*)fmc->Get(num.Data());
	  TH2D* h_mc_denom = (TH2D*)fmc->Get(denom.Data());

	  cout << denom << h_mc_denom << endl;
	  cout << num << h_mc_num << endl;
	  
	  TString name = IDs[i] ;
	  if(name.Contains("Top")) name  = "TopHNSST";
	  if(InFile.Contains("DYTop")) name = "DYTop_"+name;
	  if(Method=="NoS") Method="NoS_Central";

	  TH2D* mc_eff_rate = (TH2D*)h_mc_num->Clone((HistBin+"_"+Method+"_"+name).Data());
	  mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	  
	  mc_eff_rate->Write();
	  
	}
      }
    }
  }


  return;
}

