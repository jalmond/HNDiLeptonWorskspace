#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"

void BDTInputVariablesConv(){

  TString analysername="HNL_LeptonIDBDTStudies";  
  vector<TString> eras =  {"2016preVFP","2016postVFP","2017","2018"};

  for (auto era : eras){

    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    
    vector<TString> EtaBins = {""};

    
    
    for( auto EtaBin: EtaBins){
    
      map< TString, vector<double> > HistNames;
      map< TString, TString> HistNamesTitle;
      HistNames["Electron_E15_Electron"+EtaBin+"_OSElectron"] = {0,200.,5};
      HistNamesTitle["Electron_E15_Electron"+EtaBin+"_OSElectron"] = "e15";
      

      if(1){
      HistNames["Electron_E25_Electron"+EtaBin+"_OSElectron"] = {0,200.,5};
      HistNamesTitle["Electron_E25_Electron"+EtaBin+"_OSElectron"] = "e25";

      HistNames["Electron_E55_Electron"+EtaBin+"_OSElectron"] = {0,200.,5};
      HistNamesTitle["Electron_E55_Electron"+EtaBin+"_OSElectron"] = "e55";

      HistNames["Electron_EoverP_Electron"+EtaBin+"_OSElectron"] = {0,10.,2};
      HistNamesTitle["Electron_EoverP_Electron"+EtaBin+"_OSElectron"] = "EoverP";

      HistNames["Electron_EtaWidth_Electron"+EtaBin+"_OSElectron"] = {-0.04,0.04,1};
      HistNamesTitle["Electron_EtaWidth_Electron"+EtaBin+"_OSElectron"] = "EtaWidth";

      HistNames["Electron_FBrem_Electron"+EtaBin+"_OSElectron"] = {-0.2,1.,1};
      HistNamesTitle["Electron_FBrem_Electron"+EtaBin+"_OSElectron"] = "FBrem";

      HistNames["Electron_Full5x5_sigmaIetaIeta_Electron"+EtaBin+"_OSElectron"] = {0,0.035,1};
      HistNamesTitle["Electron_Full5x5_sigmaIetaIeta_Electron"+EtaBin+"_OSElectron"] = "Full5x5_sigmaIetaIeta";

      HistNames["Electron_HoverE_Electron"+EtaBin+"_OSElectron"] = {0,0.1,1};
      HistNamesTitle["Electron_HoverE_Electron"+EtaBin+"_OSElectron"] = "HoverE";

      HistNames["Electron_InvEminusInvP_Electron"+EtaBin+"_OSElectron"] = {0,0.04,1};
      HistNamesTitle["Electron_InvEminusInvP_Electron"+EtaBin+"_OSElectron"] = "InvEminusInvP";


      HistNames["Electron_IsGsfCtfChargeConsistent_Electron"+EtaBin+"_OSElectron"] = {0,0,1};
      HistNamesTitle["Electron_IsGsfCtfChargeConsistent_Electron"+EtaBin+"_OSElectron"] = "IsGsfCtfChargeConsistent";

      HistNames["Electron_IsGsfCtfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron"] = {0,0,1};
      HistNamesTitle["Electron_IsGsfCtfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron"] = "IsGsfCtfScPixChargeConsistent";


      HistNames["Electron_IsGsfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron"] = {0,0,1};
      HistNamesTitle["Electron_IsGsfScPixChargeConsistent_Electron"+EtaBin+"_OSElectron"] = "IsGsfScPixChargeConsistent";


      HistNames["Electron_LogEoverP_Electron"+EtaBin+"_OSElectron"] = {-1,2,1};
      HistNamesTitle["Electron_LogEoverP_Electron"+EtaBin+"_OSElectron"] = "LogEoverP";


      HistNames["Electron_MissingHits_Electron"+EtaBin+"_OSElectron"] = {0,4,1};
      HistNamesTitle["Electron_MissingHits_Electron"+EtaBin+"_OSElectron"] = "MissingHits";


      HistNames["Electron_NoIsoMvaResponse_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Electron_NoIsoMvaResponse_Electron"+EtaBin+"_OSElectron"] = "NoIsoMvaResponse";


      HistNames["Electron_NoIsoMva_Electron"+EtaBin+"_OSElectron"] = {0,0,5};
      HistNamesTitle["Electron_NoIsoMva_Electron"+EtaBin+"_OSElectron"] = "NoIsoMva";


      HistNames["Electron_PassConversionVeto_Electron"+EtaBin+"_OSElectron"] = {0,0,1};
      HistNamesTitle["Electron_PassConversionVeto_Electron"+EtaBin+"_OSElectron"] = "PassConversionVeto";

      HistNames["Electron_PhiWidth_Electron"+EtaBin+"_OSElectron"] = {0,0.12,1};
      HistNamesTitle["Electron_PhiWidth_Electron"+EtaBin+"_OSElectron"] = "PhiWidth";



      HistNames["Electron_R9_Electron"+EtaBin+"_OSElectron"] = {0.2,0,1};
      HistNamesTitle["Electron_R9_Electron"+EtaBin+"_OSElectron"] = "R9";



      HistNames["Electron_SCEta_Electron"+EtaBin+"_OSElectron"] = {0,0,1};
      HistNamesTitle["Electron_SCEta_Electron"+EtaBin+"_OSElectron"] = "SCEta";



      HistNames["Electron_TrkIso_Electron"+EtaBin+"_OSElectron"] = {0,10,2};
      HistNamesTitle["Electron_TrkIso_Electron"+EtaBin+"_OSElectron"] = "TrkIso";



      HistNames["Electron_dEtaIn_Electron"+EtaBin+"_OSElectron"] = {-0.05,0.05,2};
      HistNamesTitle["Electron_dEtaIn_Electron"+EtaBin+"_OSElectron"] = "dEtaIn";



      HistNames["Electron_dEtaSeed_Electron"+EtaBin+"_OSElectron"] = {-0.02,0.02,2};
      HistNamesTitle["Electron_dEtaSeed_Electron"+EtaBin+"_OSElectron"] = "dEtaSeed";

      HistNames["Electron_dPhiIn_Electron"+EtaBin+"_OSElectron"] = {-0.1,0.1,2};
      HistNamesTitle["Electron_dPhiIn_Electron"+EtaBin+"_OSElectron"] = "dPhiIn";

      HistNames["Electron_dr03EcalRecHitSumEt_Electron"+EtaBin+"_OSElectron"] = {0,10,2};
      HistNamesTitle["Electron_dr03EcalRecHitSumEt_Electron"+EtaBin+"_OSElectron"] = "dr03EcalRecHitSumEt";

      HistNames["Electron_dr03HcalDepth1TowerSumEt_Electron"+EtaBin+"_OSElectron"] = {0,6,2};
      HistNamesTitle["Electron_dr03HcalDepth1TowerSumEt_Electron"+EtaBin+"_OSElectron"] = "dr03HcalDepth1TowerSumEt";


      HistNames["Electron_dr03HcalTowerSumEt_Electron"+EtaBin+"_OSElectron"] = {0,6,2};
      HistNamesTitle["Electron_dr03HcalTowerSumEt_Electron"+EtaBin+"_OSElectron"] = "dr03HcalTowerSumEt";

      HistNames["Electron_dr03TkSumPt_Electron"+EtaBin+"_OSElectron"] = {0,0.1,2};
      HistNamesTitle["Electron_dr03TkSumPt_Electron"+EtaBin+"_OSElectron"] = "dr03TkSumPt";

      HistNames["Electron_e1x5OverE5x5_Electron"+EtaBin+"_OSElectron"] = {0.3,0,1};
      HistNamesTitle["Electron_e1x5OverE5x5_Electron"+EtaBin+"_OSElectron"] = "e1x5OverE5x5";

      HistNames["Electron_e2x5OverE5x5_Electron"+EtaBin+"_OSElectron"] = {0.4,0,1};
      HistNamesTitle["Electron_e2x5OverE5x5_Electron"+EtaBin+"_OSElectron"] = "e2x5OverE5x5";

      HistNames["Electron_ecalPFClusterIso_Electron"+EtaBin+"_OSElectron"] = {0,0.3,2};
      HistNamesTitle["Electron_ecalPFClusterIso_Electron"+EtaBin+"_OSElectron"] = "ecalPFClusterIso";

      HistNames["Electron_hcalPFClusterIso_Electron"+EtaBin+"_OSElectron"] = {0,0.3,2};
      HistNamesTitle["Electron_hcalPFClusterIso_Electron"+EtaBin+"_OSElectron"] = "hcalPFClusterIso";


      HistNames["Lepton_CEMFracCJ_Electron"+EtaBin+"_OSElectron"] = {0,0,2};
      HistNamesTitle["Lepton_CEMFracCJ_Electron"+EtaBin+"_OSElectron"] = "CEMFracCJ";

      HistNames["Lepton_CHFracCJ_Electron"+EtaBin+"_OSElectron"] = {0,0,2};
      HistNamesTitle["Lepton_CHFracCJ_Electron"+EtaBin+"_OSElectron"] = "CHFracCJ";

      HistNames["Lepton_Dxy_Electron"+EtaBin+"_OSElectron"] = {0,0.05,2};
      HistNamesTitle["Lepton_Dxy_Electron"+EtaBin+"_OSElectron"] = "Dxy";


      HistNames["Lepton_Dz_Electron"+EtaBin+"_OSElectron"] = {0,0.1,2};
      HistNamesTitle["Lepton_Dz_Electron"+EtaBin+"_OSElectron"] = "Dz";


      HistNames["Lepton_IP3D_Electron"+EtaBin+"_OSElectron"] = {0,10,2};
      HistNamesTitle["Lepton_IP3D_Electron"+EtaBin+"_OSElectron"] = "IP3D";


      HistNames["Lepton_JetDiscCJ_Electron"+EtaBin+"_OSElectron"] = {0,1,2};
      HistNamesTitle["Lepton_JetDiscCJ_Electron"+EtaBin+"_OSElectron"] = "JetDiscCJ";


      HistNames["Lepton_LogDxy_Electron"+EtaBin+"_OSElectron"] = {-10,5,1};
      HistNamesTitle["Lepton_LogDxy_Electron"+EtaBin+"_OSElectron"] = "LogDxy";


      HistNames["Lepton_MiniIsoChHad_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniIsoChHad_Electron"+EtaBin+"_OSElectron"] = "MiniIsoChHad";

      HistNames["Lepton_MiniIsoNhHad_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniIsoNhHad_Electron"+EtaBin+"_OSElectron"] = "MiniIsoNhHad";

      HistNames["Lepton_MiniIsoPhHad_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniIsoPhHad_Electron"+EtaBin+"_OSElectron"] = "MiniIsoPhHad";

      HistNames["Lepton_MiniReliso_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniReliso_Electron"+EtaBin+"_OSElectron"] = "MiniReliso";

      HistNames["Lepton_MiniReliso_ch_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniReliso_ch_Electron"+EtaBin+"_OSElectron"] = "MiniReliso_ch";

      HistNames["Lepton_MiniReliso_neu_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_MiniReliso_neu_Electron"+EtaBin+"_OSElectron"] = "MiniReliso_neu";

      HistNames["Lepton_NEMFracCJ_Electron"+EtaBin+"_OSElectron"] = {0,1,2};
      HistNamesTitle["Lepton_NEMFracCJ_Electron"+EtaBin+"_OSElectron"] = "NEMFracCJ";

      HistNames["Lepton_NFracCJ_Electron"+EtaBin+"_OSElectron"] = {0,1,2};
      HistNamesTitle["Lepton_NFracCJ_Electron"+EtaBin+"_OSElectron"] = "NFracCJ";

      HistNames["Lepton_PtBinned_Electron"+EtaBin+"_OSElectron"] = {0,1000,1};
      HistNamesTitle["Lepton_PtBinned_Electron"+EtaBin+"_OSElectron"] = "PtBinned";


      HistNames["Lepton_PtRatio_Electron"+EtaBin+"_OSElectron"] = {0,2,1};
      HistNamesTitle["Lepton_PtRatio_Electron"+EtaBin+"_OSElectron"] = "PtRatio";


      HistNames["Lepton_PtRel_Electron"+EtaBin+"_OSElectron"] = {0,100,2};
      HistNamesTitle["Lepton_PtRel_Electron"+EtaBin+"_OSElectron"] = "Lepton_PtRel";


      HistNames["Lepton_SIP3D_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_SIP3D_Electron"+EtaBin+"_OSElectron"] = "SIP3D";


      HistNames["Lepton_dXYSig_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_dXYSig_Electron"+EtaBin+"_OSElectron"] = "dXYSig";


      HistNames["Lepton_dZSig_Electron"+EtaBin+"_OSElectron"] = {0,10,1};
      HistNamesTitle["Lepton_dZSig_Electron"+EtaBin+"_OSElectron"] = "dZSig";
      }




      TString path= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data_Electron.root";
      TString pathMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MC.root";
      TString pathAllMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MCAll.root";
      TFile* File_sample   = GetFile(path);

      TFile* File_MCsample = GetFile(pathMC);
      TFile* File_AllMCsample = GetFile(pathAllMC);
      
      
      for(auto  mHistName:  HistNames){
	vector<bool> LogOpt = {false,true};
        for (auto iLog : LogOpt){
	  
	  TString HistName = mHistName.first;
	  double xmin = mHistName.second[0];
	  double xmax = mHistName.second[1];
	  int rebin   = int(mHistName.second[2]);
	  map< TString, TString>::iterator mapit = HistNamesTitle.find(HistName);
	  
	  TString ref= (iLog) ? EtaBin+ HistName+"Log" : EtaBin+ HistName;
	  TString xlabel = mapit->second;
	  TCanvas* c1 = MakeCanvas(ref,ref);
	  c1->Draw();
	  c1->cd();
	  
	  
	  TPad *c1_up;
	  TPad *c1_down;
	  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
	  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
	  
	  canvas_margin(c1, c1_up, c1_down);
	  
	  c1_up->Draw();
	  c1_down->Draw();
	  c1_up->cd();
	  
	  
	  TString FullHistName="Z/"+HistName;
	  TH1D* Hist_MC       = GetHist(File_sample,FullHistName,ref+"MC");
	  TH1D* Hist_DATA     = GetHist(File_MCsample,FullHistName,ref+"D");
	  Hist_MC->Rebin(rebin);
	  Hist_DATA->Rebin(rebin);
	  

	  TString LepTypeTag = HistName;
	  LepTypeTag=LepTypeTag.ReplaceAll("_OSElectron","_ConvElectron");
	  TString FullHistNameConv="MC_Electrons/"+LepTypeTag;
	  TH1D* Hist_Conv       = GetHist(File_AllMCsample,FullHistNameConv,ref+"F");
	  Hist_Conv->Rebin(rebin);
	  
	  Hist_MC->GetXaxis()->SetRangeUser(xmin,xmax);
	  Hist_MC->Scale(Hist_DATA->Integral()/Hist_MC->Integral());
	  Hist_Conv->Scale(Hist_DATA->Integral()/Hist_Conv->Integral());
	  
	  
	  /// Make Ratio Plots
	  Hist_MC->GetXaxis()->SetTitle(xlabel);
	  TH1D* Ratio_Hist   =  GetRatioHist(Hist_MC,Hist_DATA);
	  Ratio_Hist->GetYaxis()->SetTitle("#frac{#epsilon_{Zmc}}{#epsilon_{Zdata}}");
	  Ratio_Hist->GetYaxis()->SetNdivisions(6,5,0);
	  
	  gPad->Update();
	  
	  
	  double axis_format_upper = (iLog) ? 20 : 1.2;
	  double Max = Hist_MC->GetMaximum();
	  if (Hist_DATA->GetMaximum() > Max) Max = Hist_DATA->GetMaximum() ;
	  if (Hist_Conv->GetMaximum() > Max) Max = Hist_Conv->GetMaximum() ;
	  Max*= axis_format_upper;

	  TH1D* Hist_MC_OverFlow= MakeOverflowBin(Hist_MC,"OverFlow");
	  Hist_MC_OverFlow->GetYaxis()->SetRangeUser(0.01, Max);
	  hist_axis(Hist_MC_OverFlow);
	  TH1D* Hist_DATA_OverFlow= MakeOverflowBin(Hist_DATA,"OverFlow");

 
	  TH1D* Hist_Conv_OverFlow= MakeOverflowBin(Hist_Conv,"OverFlow");

          FormatHistLine(Hist_MC_OverFlow    ,1  , GetHistColor(0),1);
          FormatHistLine(Hist_DATA_OverFlow  ,1  , GetHistColor(2),1);
          FormatHistLine(Hist_Conv_OverFlow  ,1  , GetHistColor(0),9);

	  Hist_MC_OverFlow->Draw("hist");
	  Hist_DATA_OverFlow->Draw("histsame");
	  Hist_Conv_OverFlow->Draw("histsame");
	  
	  TLegend *legend = MakeLegend(0.7, 0.75, 0.9, 0.9,0.04);
          legend->AddEntry(Hist_MC_OverFlow  ,"MC ","l");
          legend->AddEntry(Hist_DATA_OverFlow,"DATA ","l");
          legend->AddEntry(Hist_Conv_OverFlow,"Conv El ","l");

	  legend->Draw();
	  
	  
	  TString label = EtaBin;
	  if(EtaBin=="") label = "Inclusive Eta/Pt";
	  else label = label.ReplaceAll("__"," ");
	  DrawLatexWithLabel(era,label,0.03,0.2,0.85);
	  
	  c1_down->cd();
	  
	  hist_axis(Hist_MC_OverFlow,Ratio_Hist);                                                                                                                                                                            
	  Ratio_Hist->GetYaxis()->SetRangeUser(0.5,1.5);
	  Ratio_Hist->Draw("histE");
	  TLine *devz = new TLine(Ratio_Hist->GetBinLowEdge(Ratio_Hist->GetXaxis()->GetFirst()),1.0,Ratio_Hist->GetBinLowEdge(Ratio_Hist->GetXaxis()->GetLast()+1),1.0  );
	  devz->SetLineWidth(1);
	  devz->SetLineStyle(1);
	  devz->Draw("SAME");
	  

	  gPad->Update();
	  	  
	  if(iLog) c1_up->SetLogy();
	  TString outpath = (iLog) ?  output + "/"+HistName+"_"+era+"_"+EtaBin +"_log" : output + "/"+HistName+"_"+era+"_"+EtaBin;
	  
	  TString save_pdf= outpath+".pdf";
	  TString save_png= outpath+".png";
	  
	  c1->SaveAs(save_png);
	  c1->SaveAs(save_pdf);
	  
	  SaveAndCopyLXPLUS(c1,outpath,analysername,"BDTvariables_conv");

	  delete Hist_MC;
	  delete Hist_MC_OverFlow;
	  delete Hist_DATA;
	  delete Hist_Conv;
	  delete Ratio_Hist;
	}
      }
      File_sample->Close();
      delete File_sample;
      delete File_MCsample;
      delete File_AllMCsample;
    }
  }
    
  
  return;
}

