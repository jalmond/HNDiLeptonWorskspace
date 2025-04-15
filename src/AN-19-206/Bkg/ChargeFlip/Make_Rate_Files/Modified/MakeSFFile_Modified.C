#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void MakeSFFileConfig(TString year, TString hist, TString DateTag, TString InFile, TString OutFile );

void MakeSFFile_Modified(){
  
  MakeSFFileConfig("2016a","Rates","Jan3", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version8_Electron_");
  MakeSFFileConfig("2016b","Rates","Jan3", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version8_Electron_");
  MakeSFFileConfig("2017","Rates","Jan3", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version8_Electron_");
  MakeSFFileConfig("2018","Rates","Jan3", "HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root","HNL_CF_Version8_Electron_");
 
}


TH2D* GetSystHist(TH2D* hdef, TString clonename, int sys){

  
  TH2D* hnum_cl = (TH2D*)hdef->Clone(clonename.Data());	
  
  for(int biny =1; biny < hdef->GetNbinsY()+1; biny++){
    for(int binx =1; binx < hdef->GetNbinsX()+1; binx++){
      double val = hdef->GetBinContent(binx,biny);
      double err = hdef->GetBinError(binx,biny);

      double defErr = 0.15*val;
      if(clonename.Contains("Inv")) {
	if(hdef->GetXaxis()->GetBinCenter(binx) < 0.003)  defErr = 0.25*val;
	if(hdef->GetXaxis()->GetBinCenter(binx)< 0.002)   defErr = 0.5*val;
      }
      else{
	if(hdef->GetXaxis()->GetBinCenter(binx)> 300)  defErr = 0.25*val;
	if(hdef->GetXaxis()->GetBinCenter(binx)> 500)   defErr = 0.5*val;
      }
      
      err = sqrt(defErr*defErr + err*err);      

      if(sys>0)hnum_cl->SetBinContent(binx,biny,val+err);
      else if(sys<0)hnum_cl->SetBinContent(binx,biny,val-err);

    }
  }
  return hnum_cl;

}
void  GetModifiedHist(TH2D* hnum, TH2D* hden, TString clonename){
  
  TH2D* hnum_cl = (TH2D*)hnum->Clone(clonename.Data());                                                                                         
  hnum_cl->Divide(hnum_cl,hden,1.,1.,"cl=0.683 b(1,1) mode");                                                                             

  for(int biny =1; biny < hnum_cl->GetNbinsY()+1; biny++){
    double x_val = 0;
    if(clonename.Contains("Inv")) x_val = 1;
    for(int binx =1; binx < hnum_cl->GetNbinsX()+1; binx++){
      
      if(hnum_cl->GetYaxis()->GetBinCenter(biny) == 1.5001) continue;

      if(clonename.Contains("Inv")){
	if(hnum_cl->GetBinContent(binx, biny) > x_val) {
	  
	  cout << clonename << " Bin " << (1./ double(hnum_cl->GetXaxis()->GetBinCenter(binx))) << " eta " << hnum_cl->GetYaxis()->GetBinCenter(biny)  << "  Value " << hnum_cl->GetBinContent(binx, biny) << " +/- " << hnum_cl->GetBinError(binx, biny) << endl;
	  if(binx < hnum_cl->GetNbinsX()) {
	    double Val = hnum_cl->GetBinContent(binx, biny);
	    double bin1V = hnum_cl->GetBinContent(binx-1, biny);
	    double bin1E = hnum_cl->GetBinError(binx-1, biny);
	    double bin2V = hnum_cl->GetBinContent(binx+1, biny);
	    double bin2E = hnum_cl->GetBinError(binx+1, biny);
	    /// Set Value extrap
	    double newVal = (bin1V + bin2V)/2.;
	    double newErr = sqrt(bin1E*bin1E + bin2E*bin2E);
	    if(newErr < fabs(Val - newVal)) newErr = fabs(Val - newVal);
	    hnum_cl->SetBinContent(binx, biny, newVal);
	    hnum_cl->SetBinError(binx, biny, newErr);
	  }
	  else {
	    double bin1V = hnum_cl->GetBinContent(binx-1, biny);
            double bin1E = hnum_cl->GetBinError(binx-1, biny);
            hnum_cl->SetBinContent(binx, biny, bin1V);
            hnum_cl->SetBinError(binx, biny, bin1E*1.5);

	    ///cout << clonename << " X bin " << hnum_cl->GetXaxis()->GetBinCenter(binx) << "  yBin " << hnum_cl->GetYaxis()->GetBinCenter(biny) << " value = " << hnum_cl->GetBinContent(binx, biny) << " error = " << hnum_cl->GetBinError(binx, biny) << endl;                                                                                                       

	  }
	  cout << "Updated to Value " << hnum_cl->GetBinContent(binx, biny) << " +/- " << hnum_cl->GetBinError(binx, biny) << endl;
	}

	x_val = hnum_cl->GetBinContent(binx, biny);
	
      }
      else{
	if(hnum_cl->GetBinContent(binx, biny) < x_val) {
	 
	  //	  cout << "Bin Value " << hnum_cl->GetBinContent(binx, biny) << " +/- " << hnum_cl->GetBinError(binx, biny) << endl;
	  if(binx < hnum_cl->GetNbinsX()) {
            double Val = hnum_cl->GetBinContent(binx, biny);
            double bin1V = hnum_cl->GetBinContent(binx-1, biny);
            double bin1E = hnum_cl->GetBinContent(binx-1, biny);
            double bin2V = hnum_cl->GetBinContent(binx+1, biny);
            double bin2E = hnum_cl->GetBinContent(binx+1, biny);
            double newVal = (bin1V + bin2V)/2.;
            double newErr = sqrt(bin1E*bin1E + bin2E*bin2E);
	    if(newErr < fabs(Val - newVal)) newErr = fabs(Val - newVal);
	    
            hnum_cl->SetBinContent(binx, biny, newVal);
            hnum_cl->SetBinError(binx, biny, newErr);

          }
          else {
            double bin1V = hnum_cl->GetBinContent(binx-1, biny);
            double bin1E = hnum_cl->GetBinContent(binx-1, biny);
            hnum_cl->SetBinContent(binx, biny, bin1V);
            hnum_cl->SetBinError(binx, biny, bin1E*1.5);
            //cout << "WARNING " << endl;
          }
          //cout << "Updated to Value " << hnum_cl->GetBinContent(binx, biny) << " +/- " << hnum_cl->GetBinError(binx, biny) << endl;

	  //  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1Increases from Val = " << x_val << " " ;
	  //cout << clonename << " X bin " << hnum_cl->GetXaxis()->GetBinCenter(binx) << "  yBin " << hnum_cl->GetYaxis()->GetBinCenter(biny) << " value = " << hnum_cl->GetBinContent(binx, biny) << " error = " << hnum_cl->GetBinError(binx, biny) << endl;
	  // cout << clonename << " " << hnum_cl->GetBinContent(binx, biny) / x_val << endl;;
	 
        }
	x_val = hnum_cl->GetBinContent(binx, biny);
        //else    cout << clonename << " X bin " << hnum_cl->GetXaxis()->GetBinCenter(binx) << "  yBin " << hnum_cl->GetYaxis()->GetBinCenter(biny) << " value = " << hnum_cl->GetBinContent(binx, biny) << " error = " << hnum_cl->GetBinError(binx, biny) << endl;

      }
    }
  }

  return ;
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
  

  std::vector<TString> IDs={"POGTight","HNTightV2", "TopHN", "HNL_ULID", "HNL_HighPt_ULID" ,"passHEEPID_v1","passHEEPID_v3"};

  //  Make 1D rates
  
  
  if(1){
    // Make 2D rates
    
    vector<TString> HistBins  = {"CFRate_InvPtEta3",
				 "CFRate_PtEta3" };
    
    vector<TString> MethodBins  = {"NoS","PBSExtrap_Central","CS_Central","PBSExtrap_PSigma","CS_PSigma","PBSExtrap_MSigma","CS_MSigma",};
    

    for(unsigned int i=0; i < IDs.size(); i++){
      for(auto HistBin : HistBins){
	for( auto Method : MethodBins){
	  
	  TString denom = IDs[i] +"/"+HistBin+"/"+Method+"/Denom";
	  TString num   = IDs[i] +"/"+HistBin+"/"+Method+"/Num";

	  TH2D* h_mc_num   = (TH2D*)fmc->Get(num.Data());
	  TH2D* h_mc_denom = (TH2D*)fmc->Get(denom.Data());
	  
	  TString name = IDs[i] ;
	  if(name.Contains("Top")) name  = "TopHNSST";
	  if(InFile.Contains("DYTop")) name = "DYTop_"+name;
	  if(Method=="NoS") Method="NoS_Central";

	  
	  TH2D* mc_eff_rate = (TH2D*)h_mc_num->Clone((HistBin+"_"+Method+"_"+name).Data());
	  mc_eff_rate->Divide(mc_eff_rate,h_mc_denom,1.,1.,"cl=0.683 b(1,1) mode");
	  mc_eff_rate->Write();

	  GetModifiedHist(h_mc_num,h_mc_denom,HistBin+"_"+Method+"_"+name);
	  
	  if(Method.Contains("Central")){

            TString MethodUp = Method;
	    MethodUp = MethodUp.ReplaceAll("Central","SystUp");
            TString MethodDown = Method;
	    MethodDown = MethodDown.ReplaceAll("Central","SystDown");

	    
            TH2D* mc_eff_rate_Up_mod = GetSystHist(mc_eff_rate,
						   HistBin+"_"+MethodUp+"_"+name,1);
	    TH2D* mc_eff_rate_Down_mod = GetSystHist(mc_eff_rate,
						     HistBin+"_"+MethodDown+"_"+name,-1);

	    mc_eff_rate_Up_mod->Write();
            mc_eff_rate_Down_mod->Write();

	    //    TH2D* mc_eff_rate_Up_mod_ratio   = (TH2D*)mc_eff_rate_Up_mod->Clone((HistBin+"_"+Method+"_SystUp_ratio_"+name).Data());
	    //TH2D* mc_eff_rate_Down_mod_ratio = (TH2D*)mc_eff_rate_Down_mod->Clone((HistBin+"_"+Method+"_SystDown_ratio_"+name).Data());
	    //mc_eff_rate_Up_mod_ratio->Divide(mc_eff_rate_Up_mod,mc_eff_rate_mod,1.,1.,"cl=0.683 b(1,1) mode");     
	    //mc_eff_rate_Down_mod_ratio->Divide(mc_eff_rate_Down_mod,mc_eff_rate_mod,1.,1.,"cl=0.683 b(1,1) mode");     
	    //mc_eff_rate_Up_mod_ratio->Write();
	    //mc_eff_rate_Down_mod_ratio->Write();
          }
	}
      }
    }
  }


  return;
}

