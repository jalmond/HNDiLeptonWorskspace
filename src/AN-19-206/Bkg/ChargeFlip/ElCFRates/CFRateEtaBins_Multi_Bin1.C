#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);

void CFRateEtaBinsIndiv(TString etabin);

void CFRateEtaBins_Multi_Bin1(){

  CFRateEtaBinsIndiv("EtaRegion1");

}

void CFRateEtaBinsIndiv(TString etabin){
  
  vector<TString> Eras = {"2016a","2016b", "2016","2017","2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "CFRateEta_2023_AN_Multi";

  for (auto Era : Eras){
    
    TString year = Era;

    TString ID = "HNL_ULID";
    HNLPlotter Plotter("HNL_Lepton_ChargeFlip");
    Plotter.SetupPlotter(year,"","HNL_Lepton_ChargeFlip");
    Plotter.CopyToWebsite = true;
    
    TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/Rates/Oct1/"+year+"/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_AllDY_Rates.root";    
   
    vector<TH1D*> hists;

    cout << path << ID+"/CFrate/Num" << endl;
    TH1D *hist_eta1_Numerator     = Plotter.ConstructHist(path, ID+"/CFRate/PBSExtrap_Central/"+etabin+"_Num");
    TH1D *hist_eta1_Denominator   = Plotter.ConstructHist(path, ID+"/CFRate/PBSExtrap_Central/"+etabin+"_Denom");

    hist_eta1_Numerator->GetXaxis()->SetTitle("1/p_{T} (GeV^{-1})");
    
    hist_eta1_Numerator->GetYaxis()->SetTitle("CF_{Rates}");
    if(!Era.Contains("2016")){
      hist_eta1_Numerator->GetYaxis()->SetRangeUser(0.000001,0.05);
    }
    else{
      hist_eta1_Numerator->GetYaxis()->SetRangeUser(0.000001,0.05);
    }
    hist_eta1_Numerator->GetXaxis()->SetRangeUser(0.00,0.07);

    hist_eta1_Numerator->Divide(hist_eta1_Denominator);

    if(Era == "2016a"){

      for(int i=1; i < hist_eta1_Numerator->GetNbinsX()+1; i++){
        double invpt = hist_eta1_Numerator->GetBinCenter(i) ;
        double pt = 1/invpt;
        if(pt  > 300)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.85);
        else if(pt  < 100)    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.95);
      }
    }

    if(Era == "2016b"){

      for(int i=1; i < hist_eta1_Numerator->GetNbinsX()+1; i++){
        double invpt = hist_eta1_Numerator->GetBinCenter(i) ;
        double pt = 1/invpt;
        if(pt  < 30)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.95);
        else if(pt  < 100)    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.9);
        else if(pt  < 300)    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.95);
        else if(pt  < 400)    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.8);
        else   hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.7);
      }
    }



    if(Era == "2016"){

      for(int i=1; i < hist_eta1_Numerator->GetNbinsX()+1; i++){
        double invpt = hist_eta1_Numerator->GetBinCenter(i) ;
        double pt = 1/invpt;
	if(pt  > 300)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.8);
        else if(pt  > 100)    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.9);
	else   hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.95);
	
      }
    }
    if(Era == "2017"){
      for(int i=1; i < hist_eta1_Numerator->GetNbinsX()+1; i++){
      	double invpt = hist_eta1_Numerator->GetBinCenter(i) ;
      	double pt = 1/invpt;
	if(pt  > 200)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.8);
      	else if(pt  > 100)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.9);
	if(etabin == "EtaRegion3"){
	  if(i == hist_eta1_Numerator->FindBin(0.023,1.2)){
	    hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*1.4);
	  }
	}
      }
    }
    if(Era == "2018"){

      for(int i=1; i < hist_eta1_Numerator->GetNbinsX()+1; i++){
        double invpt = hist_eta1_Numerator->GetBinCenter(i) ;
        double pt = 1/invpt;
        if(pt  > 60 && pt < 90)  hist_eta1_Numerator->SetBinContent(i,hist_eta1_Numerator->GetBinContent(i)*0.95);
      }
    }

    hists.push_back(hist_eta1_Numerator);

    Plotter.SetLogY=true;
    TString Label = Era ;

    SaveHistogram(Plotter, hists, {"|#eta| < 0.8"}, "HNL_Lepton_ChargeFlip_"+ID+"_DATA_"+etabin, LabelForWeb, {Label});
    
  }
  
  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){



  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  cout << plotter.thiscut_plotpath << endl;
  plotter.mkdir(plotter.thiscut_plotpath);


  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size*1.2);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

  TH1D *hist_empty= (TH1D*)hist_default->Clone();

  hist_empty->SetName("DUMMY_FOR_AXIS");

  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();

  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  for(auto i : hists) {
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*1.2;
  }
  hist_axis(hist_empty);

  hist_empty->Draw("samep");

  lg->AddEntry(hist_empty, legname[0],"l");
  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->SetMarkerSize(1.2);
    hists[i]->SetMarkerColor(kBlack);
    hists[i]->Draw("same");
  }
  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors(hist_empty);
  gr_data->SetLineWidth(2.0);
  gr_data->SetMarkerSize(0.);
  gr_data->SetMarkerColor(kBlack);
  gr_data->SetLineColor(kBlack);
  gr_data->Draw("p0same");

  TH1D * hErr = (TH1D*)hist_empty->Clone();
  
  for(int i=1; i < hist_empty->GetNbinsX()+1; i++){
    double ValUp = hist_empty->GetBinContent(i) ;
    double ValDown = hist_empty->GetBinContent(i) ; 
    
    double invpt = hist_empty->GetBinCenter(i) ;
    double pt = 1/invpt;
    double PtErr = 0.15;
    if(pt > 500)  PtErr = 0.5;
    double err = sqrt( hist_empty->GetBinError(i) * hist_empty->GetBinError(i) + hist_empty->GetBinContent(i)*hist_empty->GetBinContent(i)*PtErr*PtErr);
    cout << invpt << " err = " << err/ValUp << endl;
    ValUp = ValUp+err;
    ValDown = ValDown - err;
    
    double newVal = (ValUp + ValDown)/2.;
    hErr->SetBinContent(i,newVal);
    hErr->SetBinError(i,err);
  }

  hErr->SetMarkerColorAlpha(kAzure-9, 0);
  hErr->SetFillStyle(3013);
  hErr->SetFillColor(kBlack);
  hErr->SetLineColor(0);
  hErr->Draw("sameE2");

  lg->Draw();

  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *gr3 = new TGraph(2, x_1, y_1);
  gr3->Draw("same");


  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, Labels[il]);

  if(plotter.SetLogY)c1->SetLogy();

  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;

}
