#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString Chi2Prompt = "CHI2/NDF WW";

void Draw_Graph(HNLPlotter plotter, TString Era,vector<TGraph*> vgr , vector<TString> legNames,  TString HistName,TString dirName, vector<TString> tlat);

TString CF_EnergyShift_Proccessor(HNLPlotter Plotter,TString ID, TString Era, TString HistTag, TString LabelForOutPut, vector<double> rbins);

///// NOTE LOOP ON SHIFT NEEDS TO BE consistnt

void PlotEnergyCF_MinChiGraph(){

  TString DateTag = "Sep16";
  cout << "This code Is to check energy shift in BB/EC " << endl;

  HNLPlotter Plotter("EnergyShift");
  Plotter.CopyToWebsite = false;
  vector<TString> Eras = {"2016","2017","2018"};

  vector<double> rebin = {-0.2, -0.19, -0.18,  -0.17, -0.16, -0.15, -0.14, -0.13, -0.12, -0.11, -0.10,  -0.09,-0.08,-0.07,-0.06,-0.05,-0.04,-0.03,-0.02,-0.01,0.0, 0.01, 0.02, 0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1};

  vector<TString> MinChiResults;  
  for(auto era : Eras){
    TString year = (era.Contains("16")) ? "2016" : era;

    vector<TString>  etabins = {"BB","EC"};
    for(auto etabin :  etabins){
      Plotter.XaxisMin = -0.2;  Plotter.XaxisMax = 0.1;

      vector <TString> HistStrings = {"Bin1","Bin2","Bin3","Bin4","Bin5"};
      if(etabin == "EC") HistStrings = {"Bin1","Bin2","Bin3","Bin4","Bin5","Bin6","Bin7","Bin8","Bin9"};


      for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "POGTight", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "HNL_ULID", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      //for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "HNTightV2", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
      //for(auto x :HistStrings)  MinChiResults.push_back(era + " "+CF_EnergyShift_Proccessor(Plotter, "TopHN", era,TString(etabin+"_Pt_"+x), "AN_2019_206_HNL_ChargeFlip_EnergyShift_rebinned_"+TString(etabin+x), rebin));
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

  vector <double> Arraychi2,ArraykolS;

  for (unsigned int ishift = 0 ; ishift < nMax; ishift++){
    double shiftEl = 1.025 - double(ishift)*0.001;
    TString shift_string = DToS(shiftEl);
    ShiftVals.push_back(shift_string);
  }

  Plotter.Normalise = 1;
  				   
  int precisionVal=4;

  TH1D *hist_CF             = Plotter.ConstructHist(pathCF,ID+"/EnergyShift/"+HistString+"_CF", vrebin);
  hist_CF->Scale(1./hist_CF->Integral());

  
  for(auto ShiftVal : ShiftVals){

    TH1D *hist_PromptScaled   = Plotter.ConstructHist(pathP,ID+"/EnergyShift/"+HistString+"_PromptShifted_"+ShiftVal, vrebin);
    hist_PromptScaled->Scale(1./hist_PromptScaled->Integral());


    ///// Calulcate Chi2 for multiple x axis ranges -0.2 -> 0.1
    hist_CF->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);
    hist_PromptScaled->GetXaxis()->SetRangeUser(Plotter.XaxisMin,Plotter.XaxisMax);

    double chi2 = hist_CF->Chi2Test(hist_PromptScaled,Chi2Prompt);
    Arraychi2.push_back(chi2);
  }

  double minChi2 = 999999;
  double maxChi2 = 0;

  TString minChi2St="";
  int ng = Arraychi2.size();
  double x_1[ng], y_1[ng];

  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {
    if(Arraychi2[i]  < minChi2){
      minChi2 = Arraychi2[i];
      minChi2St = ShiftVals[i];
    }
    if(Arraychi2[i]  > maxChi2){
      maxChi2 = Arraychi2[i];
    }
  }
  for(unsigned int i = 0 ; i < Arraychi2.size(); i++) {

    double xi = 1.025 - double(i) * 0.001;
    x_1[i]  = xi;
    y_1[i]  = Arraychi2[i]/maxChi2;
  }
  
  vector <TGraph*> vgr;
  vector<TString> labels;

  TGraph *gr1 = new TGraph(ng, x_1,y_1);
  vgr.push_back(gr1);

  cout << ID + "/EnergyShift/"+HistString + " Min chi2 = " << minChi2St << " " << minChi2 << endl;

  
  Plotter.LatexTextLabel_Size=0.025;

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

  labels.push_back(ID + " " + BinLabel +  ": MinChi2 = "+minChi2St);

  minChi2St=minChi2St.ReplaceAll("p",".");
  Draw_Graph(Plotter,Era,vgr, labels, ID + "_CF_EnergyShift_Chi2_MERGED_"+HistString, "Chi2_EnergyShift", {BinLabel,"MinChi2 = "+minChi2St});

  return ID + " " + BinLabel +  ": MinChi2 = "+minChi2St;
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

  hist_empty->GetYaxis()->SetTitle("min #chi2 [normalised]");
  hist_empty->GetXaxis()->SetTitle("Energy Shift");
  hist_empty->GetYaxis()->SetRangeUser(plotter.default_y_min+0.01, Ymax*plotter.Hist_YAxis_MaxScale);
  hist_axis(hist_empty);

  hist_empty->Draw("histsame");

  gr1->SetLineWidth(4.0);
  gr1->SetMarkerSize(1.);
  gr1->SetMarkerStyle(22);
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
  //  lg->Draw();

  for(unsigned int il =0 ; il < tlat.size(); il++) latex_result.DrawLatex(plotter.LatexTextLabel_X, plotter.LatexTextLabel_Y-0.1 - 0.05*(il), tlat[il]);


  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+".pdf");

  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;


}
