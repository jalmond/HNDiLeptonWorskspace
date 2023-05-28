#include "Macros.h"
#include "mylib.h"
#include "CMS_lumi.C"


void BDTInputVariablesFake(TString era, TString EtaBin, TString histpath, double xmin, double xmax, double _rebin, TString xtitle){


  TString analysername="HNL_LeptonIDBDTStudies";  
  vector<TString> eras =  {"2016preVFP","2016postVFP","2017","2018"};


  SetUpDir(analysername,era);
  TString output=GetOutPut(analysername,era);
  
  // Set Plotting style
  PlottingSetup();
  

  map< TString, vector<double> > HistNames;
  map< TString, TString> HistNamesTitle;
  HistNames[histpath] = {xmin, xmax, _rebin};
  HistNamesTitle[histpath] = xtitle;

  
  TString path= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_data_Electron.root";
  TString pathMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MC.root";
  TString pathAllMC= TString(getenv("FILE_MERGED_PATH"))+"/"+analysername+"/"+era+"/"+analysername+"_SkimTree_DileptonBDT_MCAll.root";
  TFile* File_sample   = GetFile(path);
  
  TFile* File_MCsample = GetFile(pathMC);
  TFile* File_AllMCsample = GetFile(pathAllMC);
  
  
  for(auto  mHistName:  HistNames){
    vector<bool> LogOpt = {false};
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
      
      
      cout << "Making MC/DATA" << endl;
      TString FullHistName="ZTight/"+HistName;
      TH1D* Hist_MC       = GetHist(File_MCsample,FullHistName,ref+"DATA");
      TH1D* Hist_DATA     = GetHist(File_sample,FullHistName,ref+"MC");
      Hist_MC->Rebin(rebin);
      Hist_DATA->Rebin(rebin);
      
      
      cout << "Making Fake Hist " << endl;
      TString LepTypeTag = HistName;
      LepTypeTag=LepTypeTag.ReplaceAll("_OSElectron","_FakeElectron");
      TString FullHistNameFake="MC_Electrons/"+LepTypeTag;
      TH1D* Hist_Fake       = GetHist(File_AllMCsample,FullHistNameFake,ref+"F");
      Hist_Fake->Rebin(rebin);
      Hist_Fake->Scale(Hist_DATA->Integral()/Hist_Fake->Integral());

      cout << "Making CF Hist "<< endl;

      TString LepTypeTagCF = HistName;
      LepTypeTagCF=LepTypeTagCF.ReplaceAll("_OSElectron","_CFElectron");
      TString FullHistNameCF="MC_Electrons/"+LepTypeTagCF;
      TH1D* Hist_CF       = GetHist(File_AllMCsample,FullHistNameCF,ref+"CF");
      Hist_CF->Rebin(rebin);
      Hist_CF->Scale(Hist_DATA->Integral()/Hist_CF->Integral());
      
      Hist_MC->Scale(Hist_DATA->Integral()/Hist_MC->Integral());

      Hist_MC->GetXaxis()->SetRangeUser(xmin,xmax);
      Hist_DATA->GetXaxis()->SetRangeUser(xmin,xmax);
      Hist_CF->GetXaxis()->SetRangeUser(xmin,xmax);
      Hist_Fake->GetXaxis()->SetRangeUser(xmin,xmax);

      cout <<"Making Ratio " << endl;
      
      
      /// Make Ratio Plots
      Hist_MC->GetXaxis()->SetTitle(xlabel);
      TH1D* Ratio_Hist   =  GetRatioHist(Hist_MC,Hist_DATA,ref);
      Ratio_Hist->GetYaxis()->SetTitle("#frac{#epsilon_{Zmc}}{#epsilon_{Zdata}}");
      Ratio_Hist->GetYaxis()->SetNdivisions(6,5,0);
      
      gPad->Update();
      
      
      double axis_format_upper = (iLog) ? 20 : 1.2;
      double Max = Hist_MC->GetMaximum();
      if (Hist_DATA->GetMaximum() > Max) Max = Hist_DATA->GetMaximum() ;
      if (Hist_Fake->GetMaximum() > Max) Max = Hist_Fake->GetMaximum() ;
      if (Hist_CF->GetMaximum() > Max) Max = Hist_CF->GetMaximum() ;
      Max*= axis_format_upper;
      
      TH1D* Hist_MC_OverFlow= MakeOverflowBin(Hist_MC,"OverFlow");
      Hist_MC_OverFlow->GetYaxis()->SetRangeUser(0.01, Max);
      hist_axis(Hist_MC_OverFlow);

      TH1D* Hist_DATA_OverFlow= MakeOverflowBin(Hist_DATA,"OverFlowDATA");
      TH1D* Hist_Fake_OverFlow= MakeOverflowBin(Hist_Fake,"OverFlowFake");
      TH1D* Hist_CF_OverFlow  = MakeOverflowBin(Hist_CF,  "OverFlowCF");
      
      FormatHistLine(Hist_MC_OverFlow    ,1  , GetHistColor(0),1);
      FormatHistLine(Hist_DATA_OverFlow  ,1  , GetHistColor(2),1);
      FormatHistLine(Hist_Fake_OverFlow  ,1  , kOrange,9);
      FormatHistLine(Hist_CF_OverFlow  ,1  ,   kGreen,9);
      
      Hist_MC_OverFlow->Draw("hist");
      Hist_DATA_OverFlow->Draw("histsame");
      Hist_Fake_OverFlow->Draw("histsame");
      Hist_CF_OverFlow->Draw("histsame");
      
      TLegend *legend = MakeLegend(0.7, 0.75, 0.9, 0.9,0.04);
      legend->AddEntry(Hist_MC_OverFlow  ,"MC ","l");
      legend->AddEntry(Hist_DATA_OverFlow,"DATA ","l");
      legend->AddEntry(Hist_Fake_OverFlow,"Fake El ","l");
      legend->AddEntry(Hist_CF_OverFlow,"CF El ","l");
      
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
      
      SaveAndCopyLXPLUS(c1,outpath,analysername,"BDTvariables_PtRelCheck");
      
      delete Hist_MC;
      delete Hist_MC_OverFlow;
      delete Hist_DATA;
      delete Hist_Fake;
      delete Ratio_Hist;
    }
  }
  File_sample->Close();
  delete File_sample;
  delete File_MCsample;
  delete File_AllMCsample;
     
  
  return;
}

