#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString EtaBin, TString Sample,TString LabelForOutPut, vector<double> rbins);

void PlotClosureFake_BJet_Top(){

  HNLPlotter Plotter("MCClosureTest");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;


  vector<TString> vec =  {"2016preVFP", "2016postVFP","2017","2018" };

  for(auto era : vec) {
    TString year = (era.Contains("16")) ? "2016" : era;

    for(auto etabin :  {""}){
      Plotter.XaxisMin = 0.;  Plotter.XaxisMax = 2;

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v0_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v1_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v1_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v1_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v2_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v2_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v2_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v3_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v3_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v3_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v4_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v4_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v4_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v5_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v5_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v5_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v6_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v6_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v6_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v7_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v7_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v7_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v8_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v8_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v8_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v9_a_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v9_b_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});
      RunClosure(Plotter, "MuMu_HNL_ULID_FO_v9_c_"+year+"_MC",era, etabin,"Top","HNL_Fake_BJET_Top_MCClosure_MuMu_"+TString(etabin), {2});

    }
  }
}

void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString EtaBin, TString Sample,TString LabelForOutPut,vector<double> vrebin){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_FakeRate_MC");

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_FakeRate_MC/"+Era+"/MCClosure__/HNL_Lepton_FakeRate_MC_"+Sample+".root";

  cout << path << " " << "MCClosure/"+ID+"/SampleSum_SSTight" << endl;
  TH1D *hist_Tight             = Plotter.ConstructHist(path,"MCClosure/"+ID+"/TrailingPt_CloseJet_BScore_SSTight"+EtaBin, vrebin);
  TH1D *hist_Loose40           = Plotter.ConstructHist(path,"MCClosure/"+ID+"/TrailingPt_CloseJet_BScore_SSLoose"+EtaBin+"_40", vrebin);

  TH1D *hist_mTight             = Plotter.ConstructHist(path,"MCClosure/"+ID+"/TrailingPt_CloseJet_BScore_Weighted_SSTight"+EtaBin, vrebin);
  TH1D *hist_mLoose40           = Plotter.ConstructHist(path,"MCClosure/"+ID+"/TrailingPt_CloseJet_BScore_Weighted_SSLoose"+EtaBin+"_40", vrebin);

  hist_Tight->Add(hist_mTight,-1);
  hist_Loose40->Add(hist_mLoose40,-1);
  
  cout << hist_Tight << " " << hist_Loose40 << endl;
  
  hist_Tight->GetYaxis()->SetTitle("Events");
  hist_Tight->GetXaxis()->SetTitle("DeepJet BvsL score ");

  //  double chi2 = hist_Tight->Chi2Test(hist_Prompt,Chi2Prompt);

  //  int precisionValCHI2=2;
  //std::string trimmedString1 = std::to_string(chi2).substr(0, std::to_string(chi2).find(".") + precisionValCHI2 + 1); 
  //TString Chi2Label =  "#Chi^{2}    = "+trimmedString1 ;

  SaveHistogram( Plotter,{hist_Tight,hist_Loose40}, {"Fake Lepton (Tight)", "Fake Lepton (Loose)"}, ID+"_Fake_BJET_Top_MCClosure_"+EtaBin+"_"+Era, LabelForOutPut, {});
  

  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*1.5;
  }
  hist_axis(hist_empty);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);
  //  hist_empty->GetXaxis()->SetRangeUser(0,300);
  hist_empty->Draw("histsame");
  hist_empty->Draw("sameE");

  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    hists[i]->Draw("histsameE");
    lg->AddEntry(hists[i], legname[i],"l");
  }

  TH1D *pred_unc = (TH1D *)hists[1]->Clone();
  int n_bins = pred_unc->GetXaxis()->GetNbins();

  for(int i=1; i<=n_bins; i++){

    double error_syst = 0.3*(pred_unc->GetBinContent(i));
    double error_sumw2 = pred_unc->GetBinError(i);
    double error_combined = sqrt( error_syst*error_syst + error_sumw2*error_sumw2 );
    if(pred_unc->GetBinContent(i) > 0)pred_unc->SetBinError(i, error_combined);
    else pred_unc->SetBinError(i,0);
  }

  pred_unc->SetMarkerColorAlpha(kAzure-9, 0);
  pred_unc->SetFillStyle(3013);
  pred_unc->SetFillColor(kBlack);
  pred_unc->SetLineColor(0);
  //pred_unc->Draw("E2same");

  ///  lg->AddEntry(pred_unc,"Stat err + 30% Syst.","f");


  lg->Draw();

  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;

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
