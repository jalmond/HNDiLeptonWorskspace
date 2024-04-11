#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut, vector<double> rbins);

void PlotEnergyCFIndividualShift(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;


  for(auto era : Plotter.Eras("2017")) {
    TString year = (era.Contains("16")) ? "2016" : era;

    for(auto etabin :  {"BB","EC"}){
      Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.09999;

      vector<double> vrebin = {};
      for(int i =0; i < 31; i++) vrebin.push_back(-0.2+(double(i)*0.01));

      EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift_FullXAxisRange"+TString(etabin),{1});
      EnergyCFShiftProccessor(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift_Rebinned_"+TString(etabin), vrebin);
     
    }
  }
  
}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut,vector<double> vrebin){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString path= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/"+Era+"/Shift/HNL_Lepton_ChargeFlip_SkimTreeBDT_Shift.root";

  vector<TString> ShiftVals = {};
  int nMax = 50;
  if (HistString.Contains("Bin1")) nMax = 100;
  if (HistString.Contains("_Pt3Bin2")) nMax = 100;
  for (unsigned int ishift = 0 ; ishift < nMax; ishift++){
    double shiftEl = 1.0 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  Plotter.Normalise = 1;
  				   
  double minChi2 = 9999;
  TString string_minShiftVal = "";

  int precisionVal=4;

  
  TH1D *hist_CF             = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_CF", vrebin);
  hist_CF->Scale(1./hist_CF->Integral());

  TH1D *hist_Prompt         = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_1", vrebin);
  hist_Prompt->Scale(1./hist_Prompt->Integral());

  double chi2_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
  
  for(auto ShiftVal : ShiftVals){
    cout << "Set up shift  " << ShiftVal << endl;
    

    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal, vrebin);
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());

    ///// Calulcate Chi2 for multiple x axis ranges
    hist_CF->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_Prompt->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_PromptScaled->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);

    std::string trimmedStringMean1v2 = std::to_string(hist_CF->GetMean()).substr(0, std::to_string(hist_CF->GetMean()).find(".") + precisionVal + 1);
    std::string trimmedStringMean2v2 = std::to_string(hist_Prompt->GetMean()).substr(0, std::to_string(hist_Prompt->GetMean()).find(".") + precisionVal + 1);
    std::string trimmedStringMean3v2 = std::to_string(hist_PromptScaled->GetMean()).substr(0, std::to_string(hist_PromptScaled->GetMean()).find(".") + precisionVal + 1);

    double chi2_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
    double chi2_2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);
    if(chi2_2 < minChi2) {
      minChi2 = chi2_2;
      string_minShiftVal=ShiftVal;
    }


    hist_CF->GetXaxis()->SetRangeUser(-1,1);
    hist_Prompt->GetXaxis()->SetRangeUser(-1,1);
    hist_PromptScaled->GetXaxis()->SetRangeUser(-1,1);
    double chi2v2_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
    double chi2v2_2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);

    std::string trimmedStringMean1 = std::to_string(hist_CF->GetMean()).substr(0, std::to_string(hist_CF->GetMean()).find(".") + precisionVal + 1);
    std::string trimmedStringMean2 = std::to_string(hist_Prompt->GetMean()).substr(0, std::to_string(hist_Prompt->GetMean()).find(".") + precisionVal + 1);
    std::string trimmedStringMean3 = std::to_string(hist_PromptScaled->GetMean()).substr(0, std::to_string(hist_PromptScaled->GetMean()).find(".") + precisionVal + 1);


    hist_CF->GetXaxis()->SetRangeUser(-0.3,0.2);
    hist_Prompt->GetXaxis()->SetRangeUser(-0.3,0.2);
    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.3,0.2);
    double chi2v3_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
    double chi2v3_2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);

    /// Reset 

    hist_CF->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_Prompt->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_PromptScaled->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);


    hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
    hist_CF->GetXaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Truth}) / p_{T}^{Truth}");
 
    

    int precisionValCHI2=2;

    std::string trimmedString1 = std::to_string(chi2_1).substr(0, std::to_string(chi2_1).find(".") + precisionValCHI2 + 1);    std::string trimmedString2 = std::to_string(chi2_2).substr(0, std::to_string(chi2_2).find(".") + precisionValCHI2 + 1);
    TString Chi2Label =  "#Chi^{2}_{-0.1,0.2} = [" +trimmedString2 + ","+trimmedString1+"]" ;
    cout << Chi2Label << endl;

    std::string trimmedString1_v2 = std::to_string(chi2v2_1).substr(0, std::to_string(chi2v2_1).find(".") + precisionValCHI2 + 1);    std::string trimmedString2_v2 = std::to_string(chi2v2_2).substr(0, std::to_string(chi2v2_2).find(".") + precisionValCHI2 + 1);
    std::string trimmedString1_v3 = std::to_string(chi2v3_1).substr(0, std::to_string(chi2v3_1).find(".") + precisionValCHI2 + 1);    std::string trimmedString2_v3 = std::to_string(chi2v3_2).substr(0, std::to_string(chi2v3_2).find(".") + precisionValCHI2 + 1);
    TString Chi2Label2 =  "#Chi^{2}_{-1,1}     = [" +trimmedString2_v2 + ","+trimmedString1_v2+"]" ;
    TString Chi2Label3 =  "#Chi^{2}_{-0.3,0.2} = [" +trimmedString2_v3 + ","+trimmedString1_v3+"]" ;

    TString MeanLabel  = "#sigma_{-1,1} = ["+trimmedStringMean1+","+trimmedStringMean3+","+trimmedStringMean2+"]";
    TString MeanLabel2 = "#sigma_{-0.1,0.2} = ["+trimmedStringMean1v2+","+trimmedStringMean3v2+","+trimmedStringMean2v2+"]";
    SaveHistogram( Plotter,{hist_CF,hist_PromptScaled,hist_Prompt}, {"El_{CF} [1]", "El_{Prompt}*Shift [2]","El_{Prompt} [3]"}, ID+"_CF_EnergyShift_"+ShiftVal+"_"+HistString, LabelForOutPut, {Chi2Label,Chi2Label2,Chi2Label3,"",MeanLabel,MeanLabel2}, HistString);
  }
  cout << "string_minShiftVal = " << string_minShiftVal << " minChi2 = " << minChi2 << endl;

  return;
}

void SaveHistogram(HNLPlotter plotter,vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> Labels, bool drawError){
 

 
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
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMSSimulation);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < Labels.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, Labels[il]);

  if(plotter.SetLogY)c1->SetLogy();
  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
