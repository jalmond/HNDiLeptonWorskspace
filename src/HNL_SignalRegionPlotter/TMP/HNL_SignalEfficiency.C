#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"


void HNL_SignalEfficiency(){

  TString analysername="HNL_SignalEfficiency";  
  vector<TString> eras =  {"2017"};

  for (auto era : eras){
    
    SetUpDir(analysername,era);
    TString output=GetOutPut(analysername,era);

    // Set Plotting style
    PlottingSetup();
    
    vector<TString> samples = {"HNL_SignalEfficiency_SSWWTypeI_private","HNL_SignalEfficiency_VBFTypeI_private","HNL_SignalEfficiency_DYTypeI_private"};
    
    for(auto sample : samples){
      
      //TCanvas* c1 = MakeCanvas("",sample);
      TString canvasname= sample;
      TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);

      TFile* File_sample = GetFile("/data6/Users/jalmond/SKFlatOutput/Run2UltraLegacy_v3/"+analysername+"/"+era+"/"+sample+".root");
      
      TString LepType = "Muon";
      TString DirName="SignalRecoMuMu/";
      
      TString Hist_NoCut = DirName+LepType+"_pt_BB_NoCut";
      TString Hist_MVALoose = DirName+LepType+"_pt_BB_MVALoose";
      
      TH1D* hNoCut        = GetHist(File_sample,Hist_NoCut);
      TH1D* hMVALoose        = GetHist(File_sample,Hist_MVALoose);

      
      
      if(1){

	FormatHist(hNoCut,1,-999, 10., 2000., kBlue,1, "P_{T} GeV",LepType +" Efficiency [%]");
	FormatHist(hMVALoose,1,-999,10., 2000., kRed,9, "P_{T} GeV",LepType +" Efficiency [%]");

	hNoCut->Draw("histE");
        hMVALoose->Draw("histsameE");
	
	TLegend *legend = MakeLegend(0.75, 0.55, 0.9, 0.85,0.03);
	legend->AddEntry(hMVALoose,"MVALoose ID","l");
	legend->AddEntry(hNoCut,"No Selection","l");
	legend->Draw();
	gPad->Update();
	
	TString outpath = output + "/"+sample+"_"+era+"_MVALoose";
	TString save_pdf= outpath+".pdf";
	TString save_png= outpath+".png";
        c1->SetLogx();                                                                                                                                                                                                                                                    

	c1->SaveAs(save_png);
	c1->SaveAs(save_pdf);

	SaveAndCopyLXPLUS(c1,outpath,analysername,"V1");
      }
      if(1){
	
	TH1D* hMVALooseR =  GetRatioHist(hMVALoose,hNoCut);
	FormatHist(hMVALooseR,1,-999, kRed, "P_{T} GeV",LepType +" Efficiency [%]");
	hMVALooseR->Draw("histE");
     
	TLegend *legend = MakeLegend(0.75, 0.55, 0.9, 0.85,0.03);
	legend->AddEntry(hMVALoose,"Eff. MVALoose","l");
	legend->Draw();
	gPad->Update();
	
	TString outpath = output + "/"+sample+"_"+era+"_MVALoose_efficiency";
	TString save_pdf= outpath+".pdf";
	TString save_png= outpath+".png";
	
	c1->SetLogx();                                                                                                                                                                                                                                                        

	cout << " Saving 1" << endl;
	c1->SaveAs(save_png);
	cout << " Saving 2" << endl;
	c1->SaveAs(save_pdf);
	
	SaveAndCopyLXPLUS(c1,outpath,analysername,"V1");
      }

      File_sample->Close();
      delete File_sample;
    }
  }
    
  
  return;
}

