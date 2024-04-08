#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       
double pol3(double *x, double *par){
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
}

double pol1(double *x, double *par){
  return par[0] + par[1]*x[0];
}

double expo(double *x, double *par){
  return exp(par[0] + par[1]*x[0]);
}

double gaus(double *x, double *par){
  return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2));
}

double BW(double *x, double *par){
  return par[0]*par[1]/((x[0]+par[2])*(x[0]+par[2])+(0.5*par[1])*(0.5*par[1]));
}

double gaus_pol1(double *x, double *par){
  return gaus(x,par) + pol1(x,&par[3]);
}

double gaus_pol3(double *x, double *par){
  return gaus(x,par) + pol3(x,&par[3]);
}

double gaus_expo(double *x, double *par){
  return gaus(x,par) + expo(x,&par[3]);
}

double BW_pol1(double *x, double *par){
  return BW(x,par) + pol1(x,&par[3]);
}

double BW_pol3(double *x, double *par){
  return BW(x,par) + pol3(x,&par[3]);
}

double BW_expo(double *x, double *par){
  return BW(x,par) + expo(x,&par[3]);
}


Double_t mygauss(Double_t * x, Double_t * par)
{
  Double_t arg = 0;
  if (par[2]<0) par[2]=-par[2];  // par[2]: sigma
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];  // par[1]: mean
 
  //return par[0]*BIN_SIZE*TMath::Exp(-0.5*arg*arg)/
  //   (TMath::Sqrt(2*TMath::Pi())*par[2]); 
  return par[0]*TMath::Exp(-0.5*arg*arg)/
    (TMath::Sqrt(2*TMath::Pi())*par[2]); // par[0] is constant
 
}

Double_t mybw(Double_t* x, Double_t* par)
{
  Double_t arg1 = 14.0/22.0; // 2 over pi
  Double_t arg2 = par[1]*par[1]*par[2]*par[2]; //Gamma=par[1]  M=par[2]
  Double_t arg3 = ((x[0]*x[0]) - (par[2]*par[2]))*((x[0]*x[0]) - (par[2]*par[2]));
  Double_t arg4 = x[0]*x[0]*x[0]*x[0]*((par[1]*par[1])/(par[2]*par[2]));
  return par[0]*arg1*arg2/(arg3 + arg4);
}



void SaveHistogram(HNLPlotter Plotter, vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, bool drawError);
void Runmain(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut);

void FitCFShift(){

  HNLPlotter Plotter("FitShift");
  Plotter.DoDebug=false;
  Plotter.CopyToWebsite = false;
  Plotter.XaxisMin = -0.5;  Plotter.XaxisMax = 0.5;

  for(auto era : Plotter.Eras()) {
    TString year = (era.Contains("16")) ? "2016" : era;
    for(auto etabin :  {"BB","EC"}){
      //_main(Plotter, "HNTightV2", era,etabin, "HNL_ChargeFlip_EnergyShift");
      Runmain(Plotter, "POGTight", era,etabin, "HNL_ChargeFlip_EnergyShift");
      //_main(Plotter, "HNL_ULID_"+year, era,etabin, "HNL_ChargeFlip_EnergyShift");
      //vector <TString> HistStrings = {"_Pt1" ,"_Pt2", "_Pt3"};
      //      for(auto HistString : HistStrings ) _main(Plotter, "HNL_ULID_"+year, era,etabin+HistString, "HNL_ChargeFlip_EnergyShift");
      //for(auto HistString : HistStrings ) _main(Plotter, "POGTight", era,etabin+HistString, "HNL_ChargeFlip_EnergyShift");
      
      
    }
  }
}

void Runmain(HNLPlotter Plotter,TString ID, TString Era, TString HistString, TString LabelForOutPut){
  
  Plotter.SetupPlotter(Era,"","ChargeFlip");

  TString path="/data6/Users/jalmond/2020/HNDiLeptonWorskspace/InputFiles/MergedFiles/HNL_Lepton_ChargeFlip/"+Era+"/Shift/HNL_Lepton_ChargeFlip_SkimTreeBDT_Shift.root";


  Plotter.XaxisMin  = -1.;  Plotter.XaxisMax  = 1.;
  Plotter.RebinX    = 1;  Plotter.Normalise = 1;
   				   
  TH1D *hist_PromptScaled   = Plotter.ConstructHist(path,ID+"/EnergyShift/"+HistString+"_PromptShifted_1");
    
  
  hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());
  
  

  TString HistName = ID+"_CF_EnergyShift_"+HistString;
 
  TString dirName = "HNL_ChargeFlip_EnergyShift";
  vector<TString> legname = {"",""};

  Plotter.thiscut_plotpath = Plotter.plotpath+"/"+ dirName;
  Plotter.mkdir(Plotter.thiscut_plotpath);
  
  
  TH1D* hist_default =hist_PromptScaled;
  
  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(Plotter.Legend_Size);
  
  TCanvas* c1 = new TCanvas(HistName, "", Plotter.Canvas_X,Plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(Plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

  TH1D *hist_empty= (TH1D*)hist_default->Clone();

  hist_empty->SetName("DUMMY_FOR_AXIS");

  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();

  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = Plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  hist_axis(hist_empty);

  YmaxScale=0.3;
  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);

  if(Plotter.XaxisMin != -999) hist_empty->GetXaxis()->SetRangeUser(Plotter.XaxisMin, Plotter.XaxisMax);

  hist_empty->Draw("histsame");
  //awError)hist_empty->Draw("histsameE0");


  /// FIT  OS HIST
  int   division = hist_PromptScaled->GetNbinsX();
  float massMIN = hist_PromptScaled->GetBinLowEdge(1);
  float massMAX = hist_PromptScaled->GetBinLowEdge(division+1);
  float BIN_SIZE = hist_PromptScaled->GetBinWidth(1);
  TF1 *func = new TF1("mybw",mybw,massMIN, massMAX,3); 
  func->SetParameter(0,1.0);   func->SetParName(0,"const");  
  func->SetParameter(2,0.1);   func->SetParName(2,"sigma");  
  func->SetParameter(1,0.0);     func->SetParName(1,"mean");

  hist_PromptScaled->Fit("mybw","QR");
  TF1 *fit = hist_PromptScaled->GetFunction("mybw");
  fit->SetLineColor(4);
  fit->SetLineWidth(3);

  hist_PromptScaled->SetMarkerStyle(20);
  hist_PromptScaled->SetMarkerSize(1.0);
  hist_PromptScaled->SetMarkerColor(2);
  hist_PromptScaled->SetLineWidth(2.0);
  hist_PromptScaled->SetXTitle("Z Mass (in GeV/c^{2})"); 
  // hist_PromptScaled->GetXaxis()->SetTitleOffset(1.0);


  hist_PromptScaled->Draw("PE0");

    
    /*
  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(Plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");
    //if(drawError)hists[i]->Draw("histsameE0");
    lg->AddEntry(hists[i], legname[i],"l");
  }
    */
  lg->Draw();

  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *gr3 = new TGraph(2, x_1, y_1);
  gr3->Draw("same");


  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(Plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(Plotter.LatexTextCMS_X,Plotter.LatexTextCMS_Y, Plotter.LatexTextCMS);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);


 
 if(Plotter.SetLogY)c1->SetLogy();
  c1->SaveAs(Plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << Plotter.syncpath <<  " TamsaOutput/Plots/" << endl;
  
}
