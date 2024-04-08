#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       


void Draw_Graph(HNLPlotter plotter, TString Era,vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat);

TString EnergyCFShiftChi2(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

void PlotEnergyCFMinChi2Shift(){

  HNLPlotter Plotter("EnergyShiftMinChi2");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;

  vector<TString> Results;
  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;
    for(auto etabin :  {"EC"}){
      //EnergyCFShiftChi2(Plotter, "HNTightV2", era,etabin, "HNL_ChargeFlip_EnergyShift");
      //EnergyCFShiftChi2(Plotter, "POGTight", era,etabin, "HNL_ChargeFlip_EnergyShift");
      TString MinChi2String = EnergyCFShiftChi2(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift");
      Results.push_back( "MinChi2String = " + MinChi2String + " EtaBin = " + etabin +" era = "+era);
    }
  }
  for(auto i : Results ) cout << i << endl;
}

TString EnergyCFShiftChi2(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  

  Plotter.SetupPlotter(Era,"","HNL_Lepton_ChargeFlip");

  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/Shift/HNL_Lepton_ChargeFlip_SkimTreeBDT_Shift.root";
  cout << "Era = " << Era  << " HistString = " << HistString << " path = " << path <<  endl;
  vector<TString> ShiftVals = {};
  for (unsigned int ishift = 0 ; ishift < 100; ishift++){
    double shiftEl = 1.05 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }
   

  vector <TGraph*> vgr;
  vector<TString> labels;

  Plotter.RebinX    = 1;
  Plotter.Normalise = 1;

  TH1D *hist_CF             = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_CF");

  hist_CF->Scale(1./hist_CF->Integral());
  hist_CF->GetXaxis()->SetRangeUser(-0.2,0.1);

  vector <double> Arraychi2,ArraykolS;
  double MaxChi2=0;


  for(auto ShiftVal : ShiftVals) cout << "ShiftVal = " << ShiftVal << endl;
  for(auto ShiftVal : ShiftVals){
    
    TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal);

    if(!hist_PromptScaled) cout << ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal << endl;
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());
    hist_PromptScaled->GetXaxis()->SetRangeUser(-0.2,0.1);
    
    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,"CHI2 NORM");
    
    TString Chi2Label = "Chi2 = " + TString(to_string(chi2));
    Arraychi2.push_back(chi2);
    if(chi2 > MaxChi2) MaxChi2=chi2;
  }

  double minChi2 = 999999;
  TString minChi2St="";
  int ng = Arraychi2.size();
  double x_1[ng], y_1[ng];

  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {
    if(Arraychi2[i]  < minChi2){
      minChi2 = Arraychi2[i];
      minChi2St = ShiftVals[i];
      if(minChi2St.Contains("1p")) minChi2St = "1";
    }
    double xi = 1.05 - double(i) * 0.001;
    x_1[i]  = xi;
    y_1[i]  = Arraychi2[i]/MaxChi2;
    cout << " ShiftVals " << ShiftVals[i] << " chi2 = " << Arraychi2[i] <<  " "  << minChi2St << endl;               
  }
  TGraph *gr1 = new TGraph(ng, x_1,y_1);
  vgr.push_back(gr1);

  Plotter.LatexTextLabel_Size=0.025;

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

  labels.push_back(ID +" " +Pt_Eta_Reg + ": MinChi2 = "+minChi2St);
  
  Plotter.LatexTextLabel_Y=0.95;
  Plotter.Legend_X1=0.2;
  Plotter.Legend_X2=0.6;
  Plotter.Legend_Y1=0.7;
  Plotter.Legend_Y2=0.9;
  Plotter.XAxisTitle="Energy Shift (Prompt -> CF)";
  Plotter.YAxisTitle="min #chi ^{2} [norm]";
  Plotter.LatexTextLabel_X=0.8;
  Plotter.LatexTextLabel_Y=0.9;
  
  Draw_Graph(Plotter,Era,vgr, labels, ID + "_CF_EnergyShift_Chi2_MERGED_"+HistString, "Chi2_EnergyShift", {"HistString : " +HistString});



  return minChi2St;

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
