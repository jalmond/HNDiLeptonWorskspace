#include "Macros.h"
#include "canvas_margin.h"

//==== ReturnWhat = 0 : Obs
//==== ReturnWhat = 1 : Exp
//==== ReturnWhat = 2 : +- 1sd
//==== ReturnWhat = 3 : +- 2sd


TGraphAsymmErrors*  GetTGraph(TString input_path, int nbins, int i);

void  CompareShapeCombindedLimitSR1EECutCount(int i=0, int j=0, TString dirname="", int ReturnWhat=0, bool RunFullCLs=true){

  bool DrawObserved = false;

  setTDRStyle();

  //gStyle->SetOptStat(0);
  
  TString WORKING_DIR =   getenv("HNDILEPTONWORKSPACE_DIR");  
  TString version = getenv("FLATVERSION");
  TString dataset = "";//getenv("CATANVERSION");
  TString ENV_FILE_PATH = WORKING_DIR;
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  //out/HNTypeI_JA/2016/MuMu_SR1/result_combined_HNTight2016.txt
  TString filepath = ENV_FILE_PATH+dataset+"/Limits/ReadLimits/out_v2/HNTypeI_JA/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limits/";
  ///data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/ReadLimits/out_v2
  if(dirname!=""){
  
    filepath = ENV_FILE_PATH+dataset+"Limit/"+dirname+"/";
    }

  TString WhichYear = "2016";
  if (j==1) WhichYear = "2017";
  if (j==2) WhichYear = "2018";
  if (j==3) WhichYear = "CombinedYears";

  
  TString WhichDirectoryInCutop = "EE_SR1_SR2";
  if (i == 1) WhichDirectoryInCutop = "EE_SR1";
  if (i == 2) WhichDirectoryInCutop = "EE_SR2";;
  if (i == 3) WhichDirectoryInCutop = "EE_SR1_SR2";

  //result_combined_HNTight2016.txt  result_combined_passTightID.txt  result_combined_passTightID_nocc.txt  result_combined_passTightID_noccb.txt

  bool EEchannel = (i < 2);

  //  if(EEchannel) IDs = {"HNTight2016","passTightID","passTightID_nocc","passTightID_noccb"};
  filepath = filepath + WhichYear + "/"+ WhichDirectoryInCutop;

  TString channel = "MuMu";
  if(WhichDirectoryInCutop.Contains("EE")) channel = "EE";
  if(WhichDirectoryInCutop.Contains("MuEl")) channel = "MuEl";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  

  TLatex latex_CMSPriliminary, latex_Lumi, latex_title;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_title.SetNDC();

  //=== 13 TeV S-only channel
  //result_combined_HNTight2016.txt  result_combined_passTightID_nocc.txt
  //result_combined_passTightID.txt  result_combined_passTightID_noccb.txt

  TGraphAsymmErrors*  ee_hn       =  GetTGraph(filepath+ "/result_combined_HNTight2016.txt", 13,1); /// cut and count
  TGraphAsymmErrors*  ee_vtight    =GetTGraph(filepath+ "/result_combined_passTightID.txt", 12,2); /// cut and count
  TGraphAsymmErrors*  ee_vtightnocc    =GetTGraph(filepath+ "/result_combined_passTightID_nocc.txt", 12,2); /// cut and count
  TGraphAsymmErrors*  ee_vtightnoccb    =GetTGraph(filepath+ "/result_combined_passTightID_noccb.txt", 12,2); /// cut and count

  
  
  //======================
  //==== S-ch only limit
  //======================

  //=== Legend
  cout << "S-ch only limit  " << endl;
  TLegend *lg = new TLegend(0.48, 0.15, 0.66, 0.45);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  TH1D *hist_emptylegend = new TH1D("hist_emptylegend","",1,0.,1.);
  hist_emptylegend->SetLineColor(0);

  lg->AddEntry(hist_emptylegend,"","l");

  TLegend *lg_Alt = new TLegend(0.65, 0.15, 0.93, 0.48);
  lg_Alt->SetBorderSize(0);
  lg_Alt->SetFillStyle(0);

  //lg_Alt->AddEntry(gr_17028_exp, "CMS 13 TeV dilepton", "l");
  TLegend *lg_Alt_SandT = (TLegend *)lg_Alt->Clone();

  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 900, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  c_SOnly->SetLogy();

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetYaxis()->SetTitleSize(0.06);
  if(channel=="EE") dummy->GetYaxis()->SetTitle("#||{V_{eN}}^{2}");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("#||{V_{#muN}}^{2}");
  if(channel=="MuEl"){
    dummy->GetYaxis()->SetTitle("#frac{#||{ V_{eN}V_{#muN}^{*}}^{2}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}");
    //dummy->GetYaxis()->SetTitle("#||{ V_{eN}V_{#muN}^{*}}^{2}#/#(){#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}");
    dummy->GetYaxis()->SetTitleOffset(1.95);
    dummy->GetYaxis()->SetTitleSize(0.04);
  }
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetRangeUser(20., 1500);
  dummy->GetYaxis()->SetRangeUser(0.000005, 1.);
  dummy->SetTitle("");
  dummy->Draw("hist");
  lg_Alt->AddEntry(ee_hn,"EXO-17-028","l");
  lg_Alt->AddEntry(ee_vtightnoccb,"POG Tight+CC[EC]","l");
  lg_Alt->AddEntry(ee_vtightnocc,"POG Tight","l");
  lg_Alt->AddEntry(ee_vtight,"POG Tight+CC","l");


  ee_hn->Draw("lsame");
  ee_vtight->Draw("lsame");
  ee_vtightnocc->Draw("lsame");
  ee_vtightnoccb->Draw("lsame");

  
  //gr_17028_exp->Draw("lsame");


  lg->Draw();
  lg_Alt->Draw();

  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.SetTextFont(42);
  TString lumi = "36.5";
  if(j==1) lumi = "41.5";
  if(j==2) lumi = "59.9";
  if(j==3) lumi = "137.9";
  
  latex_title.DrawLatex(0.64, 0.64, WhichDirectoryInCutop);


  latex_Lumi.DrawLatex(0.735, 0.96, lumi+" fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.25, 0.84, "#font[41]{95% CL upper limit}");
  latex_title.SetTextSize(0.05);
  latex_title.DrawLatex(0.25, 0.88, "#font[62]{CMS}");

  c_SOnly->SetLogx();
  dummy->Draw("axissame");

  //==== HighMass
  dummy->GetXaxis()->SetRangeUser(90,1500);
  dummy->GetYaxis()->SetRangeUser(1E-4,1.);
  dummy->Draw("axissame");
  c_SOnly->SaveAs(plotpath+"/SR1_CutCount_"+WhichYear+"_"+channel+"comparison_"+WhichDirectoryInCutop+".pdf"); 


  return;
}


TGraphAsymmErrors*  GetTGraph(TString input_path, int nbins, int i){

  string elline;
  cout << input_path << endl;
  ifstream in(input_path);
  int n_central = nbins; //28, but now removing 80 Gev                                                                                                                                                                                                                                                                                                                  
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];

  int dummyint=0;
  double max_obs = 0., max_obs_mass = 0.;
  double min_obs = 9999., min_obs_mass = 0.;


  while(getline(in,elline)){
    cout << "ell line = " << elline << endl;
    std::istringstream is( elline );
    is >> mass[dummyint];
    is >> obs[dummyint];
    is >> limit[dummyint];
    is >> onesig_right[dummyint];
    is >> onesig_left[dummyint];
    is >> twosig_right[dummyint];
    is >> twosig_left[dummyint];

    cout << limit[dummyint] << endl;
    //==== skip points                                                                                                                                                                                                                                                                                                                                               
    if(obs[dummyint]<=0 || limit[dummyint]<=0 || onesig_left[dummyint]<=0 || onesig_right[dummyint]<=0 || twosig_left[dummyint]<=0 || twosig_right[dummyint]<=0){
      n_central--;
      continue;
    }

    double scale=0.01; //mixing squared is 0.01 now                                                                                                                                                                                                                                                                                                                  
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=200) scale *= 0.001;
    else if(mass[dummyint]<=600) scale *= 0.1;
    else if(mass[dummyint]<=1000) scale *= 1.;
    else scale *= 10.;

    //    scale*=  0.01; //FIXME                                                                                                                                                                                                                                                                                                                                     

    obs[dummyint] *= scale;

    limit[dummyint] *= scale;
    onesig_left[dummyint] *= scale;
    onesig_right[dummyint] *= scale;
    twosig_left[dummyint] *= scale;
    twosig_right[dummyint] *= scale;

    //==== skip points                                                                                                                                                                                                                                                                                                                                               
    if(obs[dummyint]>1.0 || limit[dummyint]>1.0){
      //n_central--;                                                                                                                                                                                                                                                                                                                                                 
      //continue;                                                                                                                                                                                                                                                                                                                                                    
    }

    onesig_left[dummyint] = limit[dummyint]-onesig_left[dummyint];
    onesig_right[dummyint] = onesig_right[dummyint] - limit[dummyint];
    twosig_left[dummyint] = limit[dummyint]-twosig_left[dummyint];
    twosig_right[dummyint] = twosig_right[dummyint] - limit[dummyint];

    if(max_obs<obs[dummyint]){
      max_obs = obs[dummyint];
      max_obs_mass = mass[dummyint];
    }
    if(min_obs>obs[dummyint]){
      min_obs = obs[dummyint];
      min_obs_mass = mass[dummyint];
    }

    dummyint++;
  }

  cout << "n_central = " << n_central << " mass size = " << mass << endl;
  for(unsigned int k = 0; k < n_central ; k++){

    cout << "Mass = " << mass[k] << " expected = " << limit[k] << " + 1sigma = " << onesig_right[k] << " -1sigma = "  << onesig_left[k] << " + 2 sigma = " << twosig_right[k] << " - 2 sigam = " << twosig_left[k] << endl;
  }

  cout << "Max : " << max_obs_mass << "\t" << max_obs << endl;
  cout << "Min : " << min_obs_mass << "\t" << min_obs << endl;

  //TGraph *gr_13TeV_obs = new TGraph(n_central,mass,obs);                                                                                                                                                                                                                                                                                                           
  
  TGraphAsymmErrors *gr_13TeV_exp = new TGraphAsymmErrors(n_central,mass,limit,0,0,0,0);
  gr_13TeV_exp->SetLineWidth(3);
  gr_13TeV_exp->SetFillColor(kWhite);
  if(i==1)   gr_13TeV_exp->SetLineStyle(2);
  if(i==1)   gr_13TeV_exp->SetLineColor(kRed);
  //if(i==2)   gr_13TeV_exp->SetLineStyle(3);
  if(i==2)   gr_13TeV_exp->SetLineColor(kBlue);
  //if(i==3)   gr_13TeV_exp->SetLineStyle(4);
  if(i==3)   gr_13TeV_exp->SetLineColor(kYellow);
  //if(i==4)   gr_13TeV_exp->SetLineStyle(5);
  if(i==4)   gr_13TeV_exp->SetLineColor(kBlack);
  //if(i==5)   gr_13TeV_exp->SetLineStyle(6);
  if(i==5)   gr_13TeV_exp->SetLineColor(kCyan);
  
  return gr_13TeV_exp;


}
