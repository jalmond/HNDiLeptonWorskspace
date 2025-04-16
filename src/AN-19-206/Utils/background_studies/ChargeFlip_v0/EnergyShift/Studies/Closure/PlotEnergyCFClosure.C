#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

void PlotEnergyCFClosure(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;
  
  
  for(auto era : Plotter.Eras("2017")) {
    TString year = (era.Contains("16")) ? "2016" : era;
    
    for(auto etabin :  {"EC"}){
      EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift_Closure");
      vector <TString> HistStrings = {"_Pt_EC_Bin1","_Pt_EC_Bin2","_Pt_EC_Bin3","_Pt_EC_Bin4","_Pt_EC_Bin5","_Pt_EC_Bin6"};
      for(auto HistString : HistStrings )     EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin+HistString, "HNL_ChargeFlip_EnergyShift_Closure");
    }
    for(auto etabin :  {"BB"}){
      EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift_Closure");
      vector <TString> HistStrings = {"_Pt_BB_Bin1","_Pt_BB_Bin2","_Pt_BB_Bin3","_Pt_BB_Bin4"};
      for(auto HistString : HistStrings )     EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin+HistString, "HNL_ChargeFlip_EnergyShift_Closure");
    }

  }
}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");
  
  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/"+Era+"/Shift/HNL_Lepton_ChargeFlip_SkimTreeBDT_Shift.root";

  vector<TString> ShiftVals = {"GetShiftCFEl"};
  
  Plotter.RebinX    = 1;
  Plotter.Normalise = 1;
   				   
  double minChi2 = 9999;
  TString string_minShiftVal = "";
  for(auto ShiftVal : ShiftVals){
    cout << "Set up shift  " << ShiftVal << endl;
    TH1D *hist_CF             = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_CF");
    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal);
    TH1D *hist_Prompt         = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_1");
    
    //hist_CF->Rebin(5);
    //hist_PromptScaled->Rebin(5);

    hist_CF->Scale(1./hist_CF->Integral());
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());
    hist_Prompt->Scale(1./hist_Prompt->Integral());

    hist_CF->GetXaxis()->SetRangeUser(-0.2,0.1);
    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2,0.1);
    hist_Prompt->GetXaxis()->SetRangeUser(-0.2,0.1);
    
    //hist_CF->Chi2Test(hist_PromptScaled,"p WW");
    
    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2/NDF WW");
    if(chi2 < minChi2) {
      minChi2 = chi2;
      string_minShiftVal=ShiftVal;
    }

    hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
    hist_CF->GetXaxis()->SetTitle("Reco - Gen / Gen");
    
    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
    cout << "Chi2Label = " << Chi2Label << endl;

    TString MeanLabel = "Mean CF = " + TString(to_string(hist_CF->GetMean())) + " Mean Prompt*X =  " + TString(to_string(hist_PromptScaled->GetMean()));
    SaveHistogram( Plotter,{hist_CF,hist_PromptScaled,hist_Prompt}, {"El_{CF} " , "El_{Prompt}*Shift ", "El_{Prompt}"}, ID+"_CF_EnergyShift_"+ShiftVal+"_"+HistString, LabelForOutPut, {Chi2Label}, "");
  }
  cout << "string_minShiftVal = " << string_minShiftVal << " minChi2 = " << minChi2 << endl;

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
    if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*plotter.Hist_YAxis_MaxScale;
  }
  hist_axis(hist_empty);

  YmaxScale=0.3;
  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);

  if(plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(plotter.XaxisMin, plotter.XaxisMax);

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
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
