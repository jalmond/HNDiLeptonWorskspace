#include "Macros.h"
#include "canvas_margin.h"

//==== ReturnWhat = 0 : Obs
//==== ReturnWhat = 1 : Exp
//==== ReturnWhat = 2 : +- 1sd
//==== ReturnWhat = 3 : +- 2sd


TGraphAsymmErrors*  GetTGraph(TString input_path, int nbins, int i);

void  CompareShapeCombindedLimitSR1EECutCount(int i=0, int j=0, TString style="CutCount",TString filename="result_VBF_HNTightV1.txt", TString tag="", int ReturnWhat=0, bool RunFullCLs=true){

  bool DrawObserved = false;

  setTDRStyle();

  //gStyle->SetOptStat(0);
  
  TString WORKING_DIR =   getenv("HNDILEPTONWORKSPACE_DIR");  
  TString version = getenv("FLATVERSION");
  TString dataset = "";//getenv("CATANVERSION");
  TString ENV_FILE_PATH = WORKING_DIR;
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString filepath = ENV_FILE_PATH+dataset+"/Limits/ReadLimits/out/HNtypeI_DiLepton/"+style+"/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limits/";
  ///data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/ReadLimits/out_v2

  TString WhichYear = "2016";
  if (j==1) WhichYear = "2017";
  if (j==2) WhichYear = "2018";
  if (j==3) WhichYear = "CombinedYears";

  
  TString WhichDirectoryInCutop = "EE_SR1_SR2";
  if (i == 1) WhichDirectoryInCutop = "EE_SR1";
  if (i == 2) WhichDirectoryInCutop = "EE_SR2";;
  if (i == 3) WhichDirectoryInCutop = "EE_SR1_SR2";

  if (i == 4) WhichDirectoryInCutop = "MuMu_SR1";
  if (i == 5) WhichDirectoryInCutop = "MuMu_SR2";;
  if (i == 6) WhichDirectoryInCutop = "MuMu_SR1_SR2";

  
  //result_combined_HNTight2016.txt  result_combined_passTightID.txt  result_combined_passTightID_nocc.txt  result_combined_passTightID_noccb.txt

  //result_VBF_HNTight2016.txt
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

  //result_VBF_passMVAID_noIso_WP90V16
  
  TGraphAsymmErrors*  ee_hn       =  GetTGraph(filepath+ "/"+filename, 20,1); /// cut and count

  TGraphAsymmErrors *gr_band_1sigma = GetTGraph(filepath+ "/"+filename, 20,2);
  TGraphAsymmErrors *gr_band_2sigma = GetTGraph(filepath+ "/"+filename, 20,3);


  
  
  //=== EXO-17-028 overlay                                                                                                                                                                                  
  const int nm_17028 = 20;
  double mass_17028[nm_17028] = {
    100, 125, 150,200,
    250, 300, 400, 500,
    600, 700, 800, 900,
    1000, 1100, 1200, 1300,
    1400, 1500, 1700,2000
  };


  double obs_17028[nm_17028], exp_17028[nm_17028];
  vector<double> tempvec_obs_17028, tempvec_exp_17028;
  vector<double> scales_17028;
  if(channel=="MuMu"){
    tempvec_exp_17028 = {
      175.333, 21.5041, 32.925, 56.3397,
      70.8081, 95.0624, 18.8665, 38.4947,
      42.8618, 74.4406, 8.4652, 12.594,
      16.3718, 23.4646, 32.9925, 43.0679,
      61.6472, 74.073, 135.185, 304.058
    } ;
    scales_17028 = {
      0.001, 0.01, 0.01,0.01,0.01,0.01,0.1, 0.1,0.1,0.1,1,1,1,1,1,1,1,1,1,1
    };
    tempvec_obs_17028 = {
      215.218, 23.0424,41.8101,49.4399,57.1134,84.404,39.6932,
      44.5303,81.4561,195.31,16.3137,42.605,61.6358,103.589,150.295,
      220.286, 365.037, 516.2, 1408.5

    };
  }
  else   if(channel=="EE"){
    //https://github.com/jedori0228/HiggsAnalysis-CombinedLimit/blob/2016Data_HNDilepton_Limit/data/2016_HNDiLepton/Outputs_Tool/EE_Combined/result.txt                                                     
    tempvec_exp_17028 = {
			 467.448, 65.4099, 90.4068, 159.838,216.957, 268.406, 53.8654,78.1765,
      76.2341, 118.242, 17.2123, 24.2464, 31.61, 46.3963, 64.5734,
			 89.4366, 115.964,147.772, 279.822,632.318
    };
    scales_17028 = {
      0.001, 0.01, 0.01,0.01,0.01,0.01,0.1, 0.1,0.1,0.1,1,1,1,1,1,1,1,1,1,1
    };
    tempvec_obs_17028 = {
      368.924, 63.3389, 61.9159, 151.2,
      206.654, 235.791, 63.261, 79.9909,
      91.403, 174.955, 14.6124, 23.4109,
      43.3134, 64.2114, 86.8003, 117.953,
      112.79, 143.465, 276.02,626.971

    };
  }
  for(unsigned int j=0; j<tempvec_obs_17028.size(); j++){

    obs_17028[j] = scales_17028[j]*tempvec_obs_17028.at(j)*0.01;
    exp_17028[j] = scales_17028[j]*tempvec_exp_17028.at(j)*0.01;
  }

  TGraph *gr_17028_exp = new TGraph(nm_17028, mass_17028, exp_17028);
  gr_17028_exp->SetLineColor(kRed);
  //gr_8TeV_exp->SetLineStyle(10);                                                                                                                                                                          
  gr_17028_exp->SetLineWidth(3);

  gr_17028_exp->SetLineStyle(2);


  
  
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

  lg->AddEntry(gr_band_1sigma,"68% expected", "f");
  lg->AddEntry(gr_band_2sigma,"95% expected", "f");
  lg->AddEntry(ee_hn,"expected","l");
  lg->AddEntry(hist_emptylegend,"","l");
  
  TLegend *lg_Alt = new TLegend(0.65, 0.15, 0.93, 0.48);
  lg_Alt->SetBorderSize(0);
  lg_Alt->SetFillStyle(0);

  lg_Alt->AddEntry(gr_17028_exp, "CMS 13 TeV dilepton", "l");
  TLegend *lg_Alt_SandT = (TLegend *)lg_Alt->Clone();

  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 900, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  c_SOnly->SetLogy();
  c_SOnly->SetLogx();

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
  dummy->GetXaxis()->SetRangeUser(20., 2000);
  dummy->GetYaxis()->SetRangeUser(0.000005, 100.);
  dummy->SetTitle("");
  dummy->Draw("hist");

  //  lg_Alt->AddEntry(ee_hn2,"MVA NonIso WP90","l");
  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");

  ee_hn->Draw("lsame");
  
  gr_17028_exp->Draw("lsame");


  lg->Draw();
  lg_Alt->Draw();

  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.SetTextFont(42);
  TString lumi = "36.5";
  if(j==1) lumi = "41.5";
  if(j==2) lumi = "59.9";
  if(j==3) lumi = "137.9";

  latex_title.SetTextSize(0.04);
  latex_title.DrawLatex(0.2, 0.3, tag);

  latex_title.SetTextSize(0.035);

  latex_Lumi.DrawLatex(0.735, 0.96, lumi+" fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.25, 0.84, "#font[41]{95% CL upper limit}");
  latex_title.SetTextSize(0.05);
  latex_title.DrawLatex(0.25, 0.88, "#font[62]{CMS}");

  //  c_SOnly->SetLogx();
  dummy->Draw("axissame");

  //==== HighMass
  dummy->GetXaxis()->SetRangeUser(90,1500);
  dummy->GetYaxis()->SetRangeUser(1E-4,1.);
  dummy->Draw("axissame");
  c_SOnly->SaveAs(plotpath+"/"+style+"_"+WhichYear+"_"+channel+"comparison_"+WhichDirectoryInCutop+tag+".pdf"); 


  return;
}


TGraphAsymmErrors*  GetTGraph(TString input_path, int nbins, int i){

  string elline;
  cout << input_path << endl;
  ifstream in(input_path);
  ifstream in2(input_path);
  int n_central = 0;

  

  int dummyint=0;
  double max_obs = 0., max_obs_mass = 0.;
  double min_obs = 9999., min_obs_mass = 0.;


  while(getline(in,elline)){
    if (TString(elline).Contains("END")) continue;
    n_central++;
  }
  cout << "n_central = " << n_central << endl;
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];
  while(getline(in2,elline)){
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
    /*
    scale_ = 1.
    if int(mass) <= 200:
        scale_ = 0.1
    elif int(mass) <= 600:
        scale_ = 1
    elif int(mass) <=1000:
        scale_ = 10.
    else:
        scale_ = 100.

     */
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=200) scale *= 0.1;
    else if(mass[dummyint]<=600) scale *= 1;
    else if(mass[dummyint]<=1000) scale *= 10.;
    else scale *= 100.;

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

  TGraphAsymmErrors *gr_band_1sigma = new TGraphAsymmErrors(n_central, mass, limit, 0, 0, onesig_left, onesig_right);
  gr_band_1sigma->SetFillColor(kGreen+1);
  gr_band_1sigma->SetLineColor(kGreen+1);
  gr_band_1sigma->SetMarkerColor(kGreen+1);

  TGraphAsymmErrors *gr_band_2sigma = new TGraphAsymmErrors(n_central, mass, limit, 0, 0, twosig_left, twosig_right);
  gr_band_2sigma->SetFillColor(kOrange);
  gr_band_2sigma->SetLineColor(kOrange);
  gr_band_2sigma->SetMarkerColor(kOrange);



  if(i==1)  return gr_13TeV_exp;
  if(i==2)  return gr_band_1sigma;
  if(i==3)  return gr_band_2sigma;


}
