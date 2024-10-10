#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
TString CF_EnergyShift_Proccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut, vector<double> rbins);

void PlotEnergyCFIndividualShift_Rebinned(){

  TString DateTag = "Sep16";
  cout << "This code Is to check energy shift in BB/EC " << endl;

  HNLPlotter Plotter("EnergyShift");
  Plotter.CopyToWebsite = false;
  vector<TString> Eras = {"2016","2017","2018"};

  vector<TString> MinChiResults;  
  for(auto era : Eras){
    TString year = (era.Contains("16")) ? "2016" : era;

    vector<TString>  etabins = {"BB","EC"};
    for(auto etabin :  etabins){
      Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.09999;

      vector <TString> HistStrings = {"Bin1","Bin2","Bin3","Bin4","Bin5"};
      if(etabin == "EC") HistStrings = {"Bin1","Bin2","Bin3","Bin4","Bin5","Bin6","Bin7","Bin8","Bin9"};


      vector<double> rebin = {-0.2, -0.19, -0.18,  -0.17, -0.16, -0.15, -0.14, -0.13, -0.12, -0.11, -0.10,  -0.09,-0.08,-0.07,-0.06,-0.05,-0.04,-0.03,-0.02,-0.01,0.0, 0.01, 0.02, 0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1};
      

      for(auto x :HistStrings)	MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "POGTight", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "HNL_ULID", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "HNTightV2", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "TopHN", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)        MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "passHEEPID_v1", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)        MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "passHEEPID_v2", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)        MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "passHEEPID_v3", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      
    }
    
    for(auto i : MinChiResults) cout  << i << endl;
  }
  
}

TString CF_EnergyShift_Proccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut,vector<double> vrebin){
  
  cout << endl;
  cout << "###################################" << endl;
  cout << "Running CF_EnergyShift_Proccessor " << endl;
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");
  TString pathP= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/Sep16/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_Prompt.root";
  TString pathCF= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/Sep16/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_CF.root";

  cout << "CF_EnergyShift_Proccessor:: Path Prompt = " << pathP << endl;
  cout << "CF_EnergyShift_Proccessor:: Path CF = " << pathCF << endl;

  vector<TString> ShiftVals = {};
  int nMax = 75;
  if(HistString.Contains("Bin1")) nMax = 125;
  if(HistString.Contains("Bin2")) nMax = 125;
  if(HistString.Contains("Bin3") && HistString.Contains("EC")) nMax = 125;
  if(HistString.Contains("Bin4") && HistString.Contains("EC")) nMax = 125;

  for (unsigned int ishift = 0 ; ishift < nMax; ishift++){
    double shiftEl = 1.025 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  Plotter.Normalise = 1;
  				   
  double minChi2 = 9999;  double min_mean_diff = 9999;
  TString string_minShiftVal = "";
  TString string_minShiftVal_mean = "";

  int precisionVal=4;

  cout << "CF_EnergyShift_Proccessor:: " << ID+"/EnergyShift/"+HistString+"_CF" << endl;
  TH1D *hist_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/"+HistString+"_CF", vrebin);
  hist_CF->Scale(1./hist_CF->Integral());

  TH1D *hist_Prompt         = Plotter.ConstructHist(pathP,ID+"/EnergyShift/"+HistString+"_PromptShifted_1", vrebin);
  hist_Prompt->Scale(1./hist_Prompt->Integral());

  double chi2_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
  
  for(auto ShiftVal : ShiftVals){
    cout << "CF_EnergyShift_Proccessor:: Set up shift  " << ShiftVal << endl;
    
    cout << "CF_EnergyShift_Proccessor:: " << ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal << endl;
    TH1D *hist_PromptScaled   = Plotter.ConstructHist(pathP,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal, vrebin);
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());

    ///// Calulcate Chi2 for multiple x axis ranges
    hist_CF->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_Prompt->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_PromptScaled->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);

    double chi2_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
    double chi2_2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);
    if(chi2_2 < minChi2) {
      minChi2 = chi2_2;
      string_minShiftVal=ShiftVal;
    }
    
    double mean_diff = fabs((hist_PromptScaled->GetMean()/hist_CF->GetMean() )  - 1);
    if(mean_diff < min_mean_diff){
      min_mean_diff = mean_diff;
      string_minShiftVal_mean=ShiftVal;
    }
    
    hist_CF->GetXaxis()->SetRangeUser(-0.2,0.1);
    hist_Prompt->GetXaxis()->SetRangeUser(-0.2,0.1);
    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2,0.1);
    double chi2v3_1 = hist_CF->Chi2Test(hist_Prompt,Chi2Prompt);
    double chi2v3_2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);

    /// Reset 

    hist_CF->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_Prompt->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_PromptScaled->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);


    std::string trimmedStringMean1 = std::to_string(hist_CF->GetMean()).substr(0, std::to_string(hist_CF->GetMean()).find(".") + precisionVal + 1);
    std::string trimmedStringMean3 = std::to_string(hist_PromptScaled->GetMean()).substr(0, std::to_string(hist_PromptScaled->GetMean()).find(".") + precisionVal + 1);


    hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
    hist_CF->GetXaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Truth}) / p_{T}^{Truth}");
     

    int precisionValCHI2=2;

    std::string trimmedString1 = std::to_string(chi2_1).substr(0, std::to_string(chi2_1).find(".") + precisionValCHI2 + 1);    std::string trimmedString2 = std::to_string(chi2_2).substr(0, std::to_string(chi2_2).find(".") + precisionValCHI2 + 1);

    TString LabelBin = "#Chi^{2}_{X_{min},X_{max}} = [Non Shifted-->Shifted] "; 
    //    TString Chi2Label =  "#Chi^{2}_{-0.5,0.1} = [" +trimmedString1 + "-->"+trimmedString2+"]" ;
    //cout << Chi2Label << endl;

    
    TString MeanLabel = "#sigma = ["+trimmedStringMean1+","+trimmedStringMean3+"]";
    

    std::string trimmedString1_v3 = std::to_string(chi2v3_1).substr(0, std::to_string(chi2v3_1).find(".") + precisionValCHI2 + 1);    std::string trimmedString2_v3 = std::to_string(chi2v3_2).substr(0, std::to_string(chi2v3_2).find(".") + precisionValCHI2 + 1);

    TString Chi2Label3 =  "#Chi^{2}_{-0.2,0.1} = [" +trimmedString1_v3 + "-->"+trimmedString2_v3+"]" ;


    TString BinLabel ="";
    if(HistString.Contains("EC")){
      if(HistString.Contains("Bin1")) BinLabel="EC P_{T} < 20 GeV";
      if(HistString.Contains("Bin2")) BinLabel="EC 20 < P_{T} < 30 GeV";
      if(HistString.Contains("Bin3")) BinLabel="EC 30 < P_{T} < 40 GeV";
      if(HistString.Contains("Bin4")) BinLabel="EC 40 < P_{T} < 50 GeV";
      if(HistString.Contains("Bin5")) BinLabel="EC 50 < P_{T} < 60 GeV";
      if(HistString.Contains("Bin6")) BinLabel="EC 60 < P_{T} < 70 GeV";
      if(HistString.Contains("Bin7")) BinLabel="EC 70 < P_{T} < 80 GeV";
      if(HistString.Contains("Bin8")) BinLabel="EC 80 < P_{T} < 100 GeV";
      if(HistString.Contains("Bin9")) BinLabel="EC 100 < P_{T} < 200 GeV";
      if(HistString.Contains("Bin10")) BinLabel="EC 200 < P_{T} < 1000 GeV";
    }
    else {
      if(HistString.Contains("Bin1")) BinLabel="Barrel P_{T} < 35 GeV";
      if(HistString.Contains("Bin2")) BinLabel="Barrel 35 < P_{T} < 50 GeV";
      if(HistString.Contains("Bin3")) BinLabel="Barrel 50 < P_{T} < 70 GeV";
      if(HistString.Contains("Bin4")) BinLabel="Barrel 70 < P_{T} < 100 GeV";
      if(HistString.Contains("Bin5")) BinLabel="Barrel 100 < P_{T} < 1000 GeV";
    }
    TString corr_ShiftVal = ShiftVal;
    corr_ShiftVal=corr_ShiftVal.ReplaceAll("p",".");
    SaveHistogram( Plotter,{hist_CF,hist_PromptScaled,hist_Prompt}, {"El_{CF}", "El_{Prompt}*Shift","El_{Prompt}"}, ID+"_CF_EnergyShift_"+ShiftVal+"_"+HistString, LabelForOutPut, {"El_{shift} = " +corr_ShiftVal,BinLabel,MeanLabel}, HistString);
  }
  
  TString string_minShiftVal_corr = string_minShiftVal;
  TString string_minShiftVal_mean_corr = string_minShiftVal_mean;
  string_minShiftVal_corr = string_minShiftVal_corr.ReplaceAll("p",".");
  string_minShiftVal_mean_corr = string_minShiftVal_mean_corr.ReplaceAll("p",".");

  TString res = HistString + " " +   ID + " " + string_minShiftVal_corr + " " + string_minShiftVal_mean_corr;
  //string_minShiftVal + " minChi2 = " + minChi2 + " string_minShiftVal[mean] = " + string_minShiftVal_mean;
  //cout <<  "ID = " << ID <<  " string_minShiftVal = " << string_minShiftVal << " minChi2 = " << minChi2 << endl;

  return res;
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
