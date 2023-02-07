#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void BDTInputVariablesJetDisc_Fits(TString era="2017",TString histDir="TopJets_TightMu/", TString histpath="CJ_JetDisc_DeepJet_Electron_LooseMuE", TString label ="p_{T} > 35 GeV", double xmin=0, double xmax=1,double _rebin=1,TString xtitle="");

void BDTInputVariablesJetDisc_Fit(){

  //BDTInputVariablesJetDisc_Fits("2016postVFP", "TopJets_TightMu/","CJ_JetDisc_DeepJet_Electron_LooseMuE");  
  //BDTInputVariablesJetDisc_Fits("2016preVFP", "TopJets_TightMu/","CJ_JetDisc_DeepJet_Electron_LooseMuE");  
  //BDTInputVariablesJetDisc_Fits("2017", "TopJets_TightMu/","CJ_JetDisc_DeepJet_Electron_LooseMuE");  
  //BDTInputVariablesJetDisc_Fits("2018", "TopJets_TightMu/","CJ_JetDisc_DeepJet_Electron_LooseMuE");  

  BDTInputVariablesJetDisc_Fits("2016postVFP", "TopJets_TightEl/","CJ_JetDisc_DeepJet_Muon_LooseEMu");                                                                      
  BDTInputVariablesJetDisc_Fits("2016preVFP", "TopJets_TightEl/","CJ_JetDisc_DeepJet_Muon_LooseEMu");                                                                       
  BDTInputVariablesJetDisc_Fits("2017", "TopJets_TightEl/","CJ_JetDisc_DeepJet_Muon_LooseEMu");                                                                             
  BDTInputVariablesJetDisc_Fits("2018", "TopJets_TightEl/","CJ_JetDisc_DeepJet_Muon_LooseEMu");                                                                             

  //BDTInputVariablesJetDisc_Fits("2016postVFP", "ZJets_EE/","CJ_JetDisc_DeepJet_Electron_LooseEMu");                                                                        
  //BDTInputVariablesJetDisc_Fits("2016preVFP", "ZJets_EE/","CJ_JetDisc_DeepJet_Electron_LooseEMu");                                                                           
  //BDTInputVariablesJetDisc_Fits("2017", "ZJets_EE/","CJ_JetDisc_DeepJet_Electron_LooseEMu");                                                                                 
  //BDTInputVariablesJetDisc_Fits("2018", "ZJets_EE/","CJ_JetDisc_DeepJet_Electron_LooseEMu");                                                                                 

  
}

void BDTInputVariablesJetDisc_Fits(TString era="2017",TString histDir="TopJets_TightMu/", TString histpath="CJ_JetDisc_DeepJet_Electron_LooseMuE", TString label ="p_{T} > 35 GeV", double xmin=0, double xmax=1,double _rebin=1,TString xtitle=""){


  //Processing BDTInputVariablesJetDisc.C("2018","TopJets_TightMu","CJ_NonPromptLep_JetDisc_DeepJet_gt35_Electron_TightMuE","p_{T} > 35 GeV",0,1,10.,"CJ_NonPromptLep_JetDisc_DeepJet_gt35_Electron_TightMuE")...

  TString analysername="HNL_LeptonIDBDTStudies";  

  TCanvas* c1 = MakeCanvas("","");

  TString path= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data.root";
  TString pathAllMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MCAll.root";
  
  TFile* File_sample   = GetFile(path);
  TFile* File_MCsample = GetFile(pathAllMC);

  SetUpDir(analysername,era);
  TString output=GetOutPut(analysername,era);
  
  // Set Plotting style
  PlottingSetup();
  
  
    
  map< TString, vector<double> > HistNames;
  map< TString, TString> HistNamesTitle;
  HistNames[histpath] = {xmin, xmax, _rebin};
  HistNamesTitle[histpath] = xtitle;

  
  for(auto  mHistName:  HistNames){
    vector<bool> LogOpt = {false,true};
    for (auto iLog : LogOpt){
      
      
      TString HistName = mHistName.first;

      double xmin = mHistName.second[0];
      double xmax = mHistName.second[1];
      int rebin   = int(mHistName.second[2]);


      map< TString, TString>::iterator mapit = HistNamesTitle.find(HistName);
      
      TString ref= (iLog) ?  HistName+"Log" : HistName;
      TString xlabel = mapit->second;
      

      c1->Draw();
      c1->cd();
      
      canvas_margin(c1);
      
      TString FullHistName=histDir+HistName;
      cout << FullHistName << endl;
      TH1D* Hist_DATA= (TH1D*)(File_sample->Get(FullHistName))->Clone(FullHistName+"DATA");

      TH1D* Hist_MC = (TH1D*)(File_MCsample->Get(FullHistName))->Clone(FullHistName+"MC");
      Hist_MC->Scale(Hist_DATA->Integral()/Hist_MC->Integral());

      int n_central = 750;
      double data_val[n_central], mc_val[n_central], mc_val2[n_central];
      int j=0;
      double cut =1;

      double IntMC= Hist_MC->Integral() ;
      double IntDATA= Hist_DATA->Integral() ;
      double CumuMC(0.), CumuDATA(0.);
      vector<double> VDATA, VMC;
      for (unsigned int ibin = 1; ibin < Hist_DATA->GetNbinsX()+1; ibin++){
	CumuMC=CumuMC+Hist_MC->GetBinContent(ibin);
	CumuDATA=CumuDATA+Hist_DATA->GetBinContent(ibin);
	VDATA.push_back(CumuDATA/IntDATA);
	VMC.push_back(CumuMC/IntMC);
	//if(ibin < 251)cout << "ibin " << Hist_DATA->GetBinLowEdge(ibin)  <<  " " << CumuDATA/IntDATA << "  MC " << CumuMC/IntMC << endl;


      }
      
      for (unsigned int ibin = 1; ibin <  n_central+1; ibin++){
	
	double cut = Hist_DATA->GetBinLowEdge(ibin);
	double vol = VDATA[ibin-1];
	for(int i =0 ; i < VMC.size(); i++){
	  if(vol >= VMC[i] && vol < VMC[i+1]) {
	    data_val[ibin-1] = Hist_DATA->GetBinLowEdge(ibin);
	    mc_val2[ibin-1]  = Hist_MC->GetBinLowEdge(ibin);
	    mc_val[ibin-1] = Hist_MC->GetBinLowEdge(i);
	    break;
	  }
	}
      }


      for (unsigned int ibin = 0; ibin < n_central; ibin++){
	if(ibin==0) continue;
      	if(!(ibin%20)) cout << "if(jetdisc < " << data_val[ibin] << ")  SF= " <<data_val[ibin]/mc_val[ibin] << " ; " << endl;
      }
      
      
      
      TGraphAsymmErrors *gr_jetdisc = new TGraphAsymmErrors(n_central,mc_val2,data_val,0,0,0,0);
      gr_jetdisc->SetLineWidth(3);
      gr_jetdisc->SetLineColor(kRed);


      TGraphAsymmErrors *gr_jetdisc2 = new TGraphAsymmErrors(n_central,mc_val,data_val,0,0,0,0);
      gr_jetdisc2->SetLineWidth(3);
      gr_jetdisc2->SetLineColor(kOrange);

      TLegend *legend = MakeLegend(0.7, 0.75, 0.9, 0.9,0.04);
      legend->AddEntry(gr_jetdisc," ","l");
      gr_jetdisc->GetXaxis()->SetTitle("DATA Disc");
      gr_jetdisc->GetYaxis()->SetTitle("MC corr Disc");
      gr_jetdisc->Draw("AC");
      gr_jetdisc2->Draw("lsame");
      legend->Draw();

      TString outpath = (iLog) ?  output + "/"+HistName+"_"+era+"_log" : output + "/"+HistName+"_"+era;
     
      TString save_pdf= outpath+".pdf";
      TString save_png= outpath+".png";
      
      c1->SaveAs(save_png);
      c1->SaveAs(save_pdf);
      
      SaveAndCopyLXPLUS(c1,outpath,analysername,"BDTvariables_JetDiscFit");

      delete Hist_MC;
      delete Hist_DATA;

    }
    
    File_sample->Close();
    delete File_sample;
    delete File_MCsample;
    
  }
  
  
  return;
}

