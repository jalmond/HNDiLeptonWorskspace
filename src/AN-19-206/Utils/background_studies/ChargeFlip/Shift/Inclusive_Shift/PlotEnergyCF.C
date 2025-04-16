#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void Draw_Graph(HNLPlotter plotter, TString Era,vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat);

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

TString dateTag = "Sep16";

void PlotEnergyCF(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;
  
  for(auto era : {"2016a","2016b","2017","2018"}) {
    
    vector <TString> HistStrings = {"Pt","Eta","Phi"};
    for(auto HistString : HistStrings ) EnergyCFShiftProccessor(Plotter, "POGTight", era,HistString, "AN-19-206_HNL_ChargeFlip_InclusiveBinned_EnergyShift");
    for(auto HistString : HistStrings ) EnergyCFShiftProccessor(Plotter, "HNL_ULID", era,HistString, "AN-19-206_HNL_ChargeFlip_InclusiveBinned_EnergyShift");
   
  }

}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString pathP= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/"+dateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_Prompt.root";
  TString pathCF= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/"+dateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_CF.root";

  
  cout << pathCF << endl;
  Plotter.RebinX    = 1;
  Plotter.Normalise = 1;

  vector <TGraph*> vgr;
  vector<TString> labels;


  TH1D *hist_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/BB_"+HistString+"_CF");
  TH1D *hist_EC_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/EC_"+HistString+"_CF");

  TH1D *hist_PromptScaled   = Plotter.ConstructHist(pathP,ID+"/EnergyShift/BB_"+HistString+"_Prompt");
  TH1D *hist_EC_PromptScaled   = Plotter.ConstructHist(pathP,ID+"/EnergyShift/EC_"+HistString+"_Prompt");
  
  hist_CF->Add(hist_EC_CF);
  
  hist_PromptScaled->Add(hist_EC_PromptScaled);

  hist_CF->Scale(1./hist_CF->Integral());
  hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());

  hist_CF->GetXaxis()->SetRangeUser(-0.2,0.1);
  hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2,0.1);
  //  hist_PromptScaled->Rebin(2);
  hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
  if(HistString=="Pt") hist_CF->GetXaxis()->SetTitle("P_{T} (Reco-Gen)/Gen");
  if(HistString=="Eta") hist_CF->GetXaxis()->SetTitle("#eta (Reco-Gen)/Gen");
  if(HistString=="Phi") hist_CF->GetXaxis()->SetTitle("#phi (Reco-Gen)/Gen");
    
  SaveHistogram( Plotter,{hist_CF,hist_PromptScaled}, {"Electron_{Flipped} ", "Electron_{Prompt} "}, ID+"_CF_EnergyShift_"+HistString, LabelForOutPut, {}, "");
  

  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError){
 

 
  cout    << "################### SaveHist [" << HistName << "]  ###################" << endl;
  cout    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl;


  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  
  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size*1.4);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  //  if(dirName.Contains("Phi")) c1->SetLogx();
  //  if(dirName.Contains("Eta")) c1->SetLogx();
 
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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*plotter.Hist_YAxis_MaxScale;
  }
  hist_axis(hist_empty);


  if(HistName.Contains("Pt"))  YmaxScale=0.3;
  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);
  

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

  if(HistName.Contains("Phi"))   hist_empty->GetXaxis()->SetRangeUser(-0.01,0.01);
  hist_empty->Draw("histsame");
  if(drawError)hist_empty->Draw("histsameE0");



  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    if(drawError)hists[i]->Draw("histsameE0");
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
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMS);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < scales.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, scales[il]);

  if(plotter.SetLogY)c1->SetLogy();
  //  if(HistName.Contains("Phi"))c1->SetLogx();
  cout << plotter.thiscut_plotpath+"/"+HistName+".pdf" << endl;
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}

void Draw_Graph(HNLPlotter plotter, TString Era, vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat){

  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  TLegend *lg= new TLegend(plotter.Legend_X1,plotter.Legend_Y1,plotter.Legend_X2,plotter.Legend_Y2);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(0.025);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X, plotter.Canvas_Y);
  c1->Draw();
  c1->cd();

  if(plotter.SetLogY)c1->SetLogy();

  canvas_margin(c1);

  TGraph* gr1 = vgr[0];
  TH1D *hist_empty = (TH1D*)gr1->GetHistogram();
  hist_empty->SetName("DUMMY_FOR_AXIS");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();
  double Ymax = hist_empty->GetMaximum();

  hist_empty->GetYaxis()->SetTitle(plotter.YAxisTitle);
  hist_empty->GetXaxis()->SetTitle(plotter.XAxisTitle);
  hist_empty->GetYaxis()->SetRangeUser(plotter.default_y_min+0.01, Ymax*plotter.Hist_YAxis_MaxScale);
  hist_axis(hist_empty);

  hist_empty->Draw("histsame");

  gr1->SetLineWidth(4.0);
  gr1->SetMarkerSize(0.);
  gr1->SetLineColor(kRed);
  gr1->Draw("plsame");

  lg->AddEntry(gr1, legNames[0], "pl");

  for(unsigned int ig=1; ig < vgr.size(); ig++){
    cout << "Adding Graph " << ig << " " << vgr[ig] <<endl;
    TGraph *gr = vgr[ig];
    gr->SetLineWidth(4.0);
    gr->SetMarkerSize(0.);
    gr->SetLineColor(plotter.GetColor(ig));
    gr->Draw("plsame");
    lg->AddEntry(gr, legNames[ig], "pl");
    TH1F* h = gr->GetHistogram();
    if(h->GetMaximum() > Ymax) Ymax=h->GetMaximum();

  }
  cout << "Graphs added" << endl;
  hist_empty->GetYaxis()->SetRangeUser(plotter.default_y_min, Ymax*plotter.Hist_YAxis_MaxScale);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(plotter.LatexTextLabel_Size);

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMS);
  latex_Lumi.SetTextSize(plotter.LatexTextLabel_Size);
  if(Era=="2016preVFP")latex_Lumi.DrawLatex(0.7, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(Era=="2016postVFP")latex_Lumi.DrawLatex(0.7, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(Era=="2016") latex_Lumi.DrawLatex(0.7, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(Era=="2017") latex_Lumi.DrawLatex(0.7, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(Era=="2018") latex_Lumi.DrawLatex(0.7, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(Era=="Run2") latex_Lumi.DrawLatex(0.7, 0.96, "137.9 fb^{-1} (13 TeV)");

  //  lg->SetNColumns(2);                                                                                                                                                                                                                
  lg->Draw();

  for(unsigned int il =0 ; il < tlat.size(); il++) latex_result.DrawLatex(plotter.LatexTextLabel_X, plotter.LatexTextLabel_Y-0.1 - 0.05*(il), tlat[il]);


  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".png");
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;

  cout << plotter.thiscut_plotpath+"/"+HistName+".png" << endl;

}
