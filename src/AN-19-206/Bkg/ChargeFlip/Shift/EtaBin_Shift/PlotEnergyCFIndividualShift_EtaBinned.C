#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

void Draw_Graph(HNLPlotter plotter, TString Era,vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat);

void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

TString dateTag = "Sep16";

void PlotEnergyCFIndividualShift_EtaBinned(){

  HNLPlotter Plotter("EnergyShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;



  for(auto era : {"2016a","2016b"}) {
    //    TString year = (era.Contains("16")) ? "2016" : era;

    vector <TString> HistStrings = {"Eta_Bin1","Eta_Bin2","Eta_Bin3","Eta_Bin4","Eta_Bin5","Eta_Bin6","Eta_Bin7","Eta_Bin8","Eta_Bin9","Eta_Bin10","Eta_Bin11","Eta_Bin12","Eta_Bin13"};
    for(auto HistString : HistStrings ) EnergyCFShiftProccessor(Plotter, "POGTight", era,HistString, "AN-19-206_HNL_ChargeFlip_EtaBinned_EnergyShift_"+HistString);
    
  }

}

void EnergyCFShiftProccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString pathP= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/"+dateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_Prompt.root";
  TString pathCF= TString(std::getenv("FILE_MERGED_PATH")) + "/HNL_Lepton_ChargeFlip/EnergyShift/"+dateTag+"/"+Era+"/HNL_Lepton_ChargeFlip_SkimTree_BDT_CF.root";


  vector<TString> ShiftVals = {};
  for (unsigned int ishift = 0 ; ishift < 100; ishift++){
    double shiftEl = 1.05 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  Plotter.RebinX    = 1;
  Plotter.Normalise = 1;

  vector <TGraph*> vgr;
  vector<TString> labels;

   				   
  double minChi2 = 9999;
  TString string_minShiftVal = "";
  vector <double> Arraychi2,ArraykolS;
  double MaxChi2=0;

  for(auto ShiftVal : ShiftVals){
    cout << "Set up shift  " << ShiftVal << endl;
    TH1D *hist_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/"+HistString+"_CF");
    TH1D *hist_PromptScaled   = Plotter.ConstructHist(pathP,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal);


    cout << ID+"/EnergyShift/"+HistString+"_CF" << endl;
    //hist_CF->Rebin(5);
    //hist_PromptScaled->Rebin(5);

    hist_CF->Scale(1./hist_CF->Integral());
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());

    hist_CF->GetXaxis()->SetRangeUser(-0.2,0.1);
    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2,0.1);
    
    //hist_CF->Chi2Test(hist_PromptScaled,"p WW");
    
    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2/NDF WW");
    Arraychi2.push_back(chi2);
    if(chi2 > MaxChi2) MaxChi2=chi2;

    if(chi2 < minChi2) {
      minChi2 = chi2;
      string_minShiftVal=ShiftVal;
      if(string_minShiftVal.Contains("1p"))string_minShiftVal= "1";
    }

    hist_CF->GetYaxis()->SetTitle("Events [Normalised]");
    hist_CF->GetXaxis()->SetTitle("Reco - Gen / Gen");
    
    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
    cout << "Chi2Label = " << Chi2Label << endl;

    TString MeanLabel = "Mean CF = " + TString(to_string(hist_CF->GetMean())) + " Mean Prompt*X =  " + TString(to_string(hist_PromptScaled->GetMean()));
    //SaveHistogram( Plotter,{hist_CF,hist_PromptScaled}, {"El_{CF} "+HistString, "El_{Prompt} "+HistString}, ID+"_CF_EnergyShift_"+ShiftVal+"_"+HistString, LabelForOutPut, {Chi2Label}, "");
  }
  
  int ng = Arraychi2.size();
  double x_1[ng], y_1[ng];


  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {

    double xi = 1.05 - double(i) * 0.001;
    x_1[i]  = xi;
    y_1[i]  = Arraychi2[i]/MaxChi2;
    cout << " ShiftVals " << ShiftVals[i] << " chi2 = " << Arraychi2[i] <<  " "  << string_minShiftVal << endl;               
  }

  TGraph *gr1 = new TGraph(ng, x_1,y_1);
  vgr.push_back(gr1);

  TString Pt_Eta_Reg = "";
  if(HistString.Contains("BB")){
    if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 50";
    if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 30 < Pt < 150";
    if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 150 < Pt" ;

  }
  else{
    if(HistString.Contains("Pt1")) Pt_Eta_Reg+= " 10 < Pt < 30";
    if(HistString.Contains("Pt2")) Pt_Eta_Reg+= " 30 < Pt < 50";
    if(HistString.Contains("Pt3")) Pt_Eta_Reg+= " 50 < Pt < 75";
    if(HistString.Contains("Pt4")) Pt_Eta_Reg+= " 75 < Pt < 100";
    if(HistString.Contains("Pt5")) Pt_Eta_Reg+= " 100 < Pt ";
  }
  if(HistString.Contains("BB")) Pt_Eta_Reg+= " BB";
  if(HistString.Contains("EC")) Pt_Eta_Reg+= " EC";

  labels.push_back(ID +" " +Pt_Eta_Reg + ": MinChi2 = "+string_minShiftVal);

  Draw_Graph(Plotter,Era,vgr, labels, ID + "_CF_EnergyShift_Chi2_MERGED_"+HistString, "Chi2_EnergyShift", {"HistString : " +HistString});

  cout << "string_minShiftVal = " << string_minShiftVal << " minChi2 = " << string_minShiftVal << endl;

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


}
