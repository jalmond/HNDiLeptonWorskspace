#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString EtaBin, TString HistTag, TString Method,TString LabelForOutPut, vector<double> rbins);

void PlotClosureCF_Eta(){

  HNLPlotter Plotter("ClosureTest");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;


  for(auto era : Plotter.Eras("2017")) {
    TString year = (era.Contains("16")) ? "2016" : era;

    for(auto etabin :  {"BB","EC"}){

      RunClosure(Plotter, "HNL_ULID_"+year, era,etabin, "NonCF_LepEta__W1","Closure","HNL_ChargeFlip_Closure_Z_LeptonEta_"+TString(etabin), {2});
      RunClosure(Plotter, "HNL_ULID_"+year, era,etabin, "NonCF_LepEta__W2","Closure","HNL_ChargeFlip_Closure_Z_LeptonEta_"+TString(etabin), {2});
      RunClosure(Plotter, "HNL_ULID_"+year, era,etabin, "NonCF_LepEta__W3","Closure","HNL_ChargeFlip_Closure_Z_LeptonEta_"+TString(etabin), {2});
      RunClosure(Plotter, "HNL_ULID_"+year, era,etabin, "NonCF_LepEta__W4","Closure","HNL_ChargeFlip_Closure_Z_LeptonEta_"+TString(etabin), {2});
    }
  }
  
}

void RunClosure(HNLPlotter Plotter,TString ID, TString Era, TString EtaBin,TString HistString, TString Method, TString LabelForOutPut,vector<double> vrebin){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/"+Era+"/ClosureTest/HNL_Lepton_ChargeFlip_SkimTree_DileptonBDT_DYJetsToEE_MiNNLO.root";

  TH1D *hist_mass_CF             = Plotter.ConstructHist(path,ID+"/"+Method+"/CF_LepEta", vrebin);
  TH1D *hist_Prompt              = Plotter.ConstructHist(path,ID+"/"+Method+"/"+HistString, vrebin);

  TString HistStringNS = HistString;
  HistStringNS = HistStringNS.ReplaceAll("LepPt","LepPt_NoShift");

  TH1D *hist_Prompt_NoShift      = Plotter.ConstructHist(path,ID+"/"+Method+"/"+HistStringNS, vrebin);
  cout << ID+"/"+Method+"/"+HistStringNS << endl;
  hist_Prompt_NoShift->SetLineStyle(4);
  hist_mass_CF->GetYaxis()->SetTitle("Events / GeV");
  hist_mass_CF->GetXaxis()->SetTitle("M_{Z} [GeV] ");
 
  double chi2 = hist_mass_CF->Chi2Test(hist_Prompt,Chi2Prompt);

  int precisionValCHI2=2;
  std::string trimmedString1 = std::to_string(chi2).substr(0, std::to_string(chi2).find(".") + precisionValCHI2 + 1); 
  TString Chi2Label =  "#Chi^{2}    = "+trimmedString1 ;

  SaveHistogram( Plotter,{hist_mass_CF,hist_Prompt,hist_Prompt_NoShift}, {"SS Observed", "OS*R_{CF} Predicted","OS*R_{CF} Predicted [no shift]"}, ID+"_CF_Closure_"+HistString+"_"+Method+"_"+EtaBin+"_"+Era, LabelForOutPut, {Method,Chi2Label});
  

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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*1.2;
  }
  hist_axis(hist_empty);

  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);

  //  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

  hist_empty->Draw("histsame");
  hist_empty->Draw("sameE");

  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }
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
