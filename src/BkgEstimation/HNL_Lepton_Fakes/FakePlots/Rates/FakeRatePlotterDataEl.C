#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);


void FakeRatePlotterDataEl(){
  
  vector<TString> Eras = {"2018","2017","2016a","2016b"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "HNL_LeptonFakeRates_2024_FakeRates";

  vector<TString> Vars = {""};
  
  for (auto Era : Eras){

    TString year = (Era.Contains("16")) ? "2016" : Era;

    vector<TString> IDs = {"HNL_ULID_"+year+"_HNL_ULID_FO_v9_a_"+year+"EE_AJ40_pt_"};
    for( auto ID : IDs){
      for( auto  var : Vars){
	HNLPlotter Plotter("HNL_Lepton_FakeRate");
	Plotter.SetupPlotter(Era,"","HNL_Lepton_FakeRate");
	Plotter.CopyToWebsite = true;
	
	TString pathData="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/BkgEstimation/HNL_Lepton_Fakes/AnalyzerInputFile/EGamma/FR_EGamma_"+Era+"_HNL_ULID_PtParton_1D.root";

	  
	vector<TH1D*> hists;
	  
	TString VARBB = ID + "BB";
	TString VAREC = ID + "EC";
	cout << pathData << " " << VARBB << endl;
	TH1D *hist_BB     = Plotter.ConstructHist(pathData, VARBB);
	TH1D *hist_EC    = Plotter.ConstructHist(pathData, VAREC);
	

	///// Set up axis 
	hist_BB->GetYaxis()->SetTitle("Fake Rates");
	hist_BB->GetYaxis()->SetRangeUser(0,0.6);
	hist_BB->GetXaxis()->SetRangeUser(15,80.);


	hists.push_back(hist_BB);
	hists.push_back(hist_EC);


	TString LabelForWeb = "FRate_2024_ANv3";
	TString Label = Era+" (AJ40)" ;

	SaveHistogram(Plotter, hists, {"Barrel","Endcap"}, "HNL_Lepton_Fake_1D_"+Era+"_DATA", LabelForWeb, {Label});

	
      }
    }
  }
  return;
}


void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname,  TString HistName, TString dirName, vector<TString> Labels){



  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  cout << plotter.thiscut_plotpath << endl;
  plotter.mkdir(plotter.thiscut_plotpath);

  TH1D* hist_default = hists[0];

  //const char * format = (char*)'4.3f';                                                                                                                                                                                                                                                                                                                                                                                                                       
  //  gStyle->SetPaintTextFormat((char*)'4.1f');                                                                                                                                                                                                                                                                                                                                                                                                               

  TCanvas* c1 = new TCanvas(HistName, "Data fake rate map for electrons ID ",1100, 800);

  c1->Draw();
  c1->cd();

  c1->SetTopMargin( 0.1);
  c1->SetBottomMargin( 0.12 );
  c1->SetRightMargin( 0.12 );
  c1->SetLeftMargin( 0.12 );


  TH1D *hist_empty= (TH1D*)hist_default->Clone();
  hist_empty->SetTitle("Data fake rate map for  electrons ID ");

  hist_empty->GetXaxis()->SetRangeUser(15,80);
  hist_empty->SetName("DUMMY_FOR_AXIS");
  hist_empty->SetMarkerSize(0.8);
  hist_empty->SetLineColor(kRed);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 0.4), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 1.4), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 2.), 0);
  hist_empty->SetBinContent(hist_empty->FindBin(5, 2.4), 0);
  //  hist_axis(hist_empty);                                                                                                                                                                                                                                                                                                                                                                                                                                  
  hist_empty->GetYaxis()->SetLabelSize(0.03);
  hist_empty->GetYaxis()->SetTitleSize(0.04);
  hist_empty->GetYaxis()->SetTitleOffset(1.20);
  hist_empty->GetXaxis()->SetLabelSize(0.03);
  hist_empty->GetXaxis()->SetTitleSize(0.04);
  hist_empty->GetXaxis()->SetTitleOffset(1.20);

  hist_empty->SetName("Data fake rate map for electrons ID");
  gStyle->SetPaintTextFormat("4.2f");

  c1->Update();
  hist_empty->SetTitle("Data fake rate map for electrons ID");
  hist_empty->GetXaxis()->SetTitle("p^{parton}_{T} (GeV) ");
  hist_empty->SetLineWidth(2.);
  hist_empty->Draw("colzE");
  
  hists[1]->SetLineWidth(2.);
  hists[1]->SetLineColor(kBlack);
  
  hists[1]->Draw("histsameE");

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  //  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);                                                                                        
  TLegend *lg = new TLegend(0.55, 0.70, 0.93, 0.8);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);
  
  lg->AddEntry(hist_empty, legname[0],"l");
  for(int i=1 ; i < hists.size(); i++)  lg->AddEntry(hists[i], legname[i],"l");

  lg->Draw();
    
  TLatex latex_title;
  latex_title.SetNDC();
  latex_title.SetTextSize(plotter.LatexTextCMS_Size);
  latex_title.DrawLatex(0.25, 0.95, "Data fake rate map for electrons ID " );

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);


  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.15, 0.8-0.05*il, Labels[il]);


  c1->SetTitle("Data fake rate map for  electrons ID ");
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_electron.pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;

}
