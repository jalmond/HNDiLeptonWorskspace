#include "Macros.h"
#include "canvas_margin.h"

//==== ReturnWhat = 0 : Obs
//==== ReturnWhat = 1 : Exp
//==== ReturnWhat = 2 : +- 1sd
//==== ReturnWhat = 3 : +- 2sd


TGraphAsymmErrors*  GetTGraph(std::map<double,double> map1, std::map<double,double> map2, int i );
std::map<double,double> GetMap(TString input_path, int nbins, int i);

void  CompareCombindedLimitSR1_SR2MuMuCutCount_rel(int j=0, TString dirname="", int ReturnWhat=0, bool RunFullCLs=true){

  bool DrawObserved = false;

  setTDRStyle();

  //gStyle->SetOptStat(0);
  
  TString WORKING_DIR =   getenv("HNDILEPTONWORKSPACE_DIR");  
  TString version = getenv("FLATVERSION");
  TString dataset = "";//getenv("CATANVERSION");
  TString ENV_FILE_PATH = WORKING_DIR;
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limits/ReadLimits/out/HNTypeI_JA/CutCount/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limits/";

  if(dirname!=""){
  
    filepath = ENV_FILE_PATH+dataset+"Limit/"+dirname+"/";
    }

  TString WhichYear = "2016";
  if (j==1) WhichYear = "2017";
  if (j==2) WhichYear = "2018";
  if (j==3) WhichYear = "CombinedYears";

  
  TString WhichDirectoryInCutop = "MuMu_SR1_SR2";
  filepath = filepath + WhichYear + "/"+ WhichDirectoryInCutop;

  TString channel = "MuMu";

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
  /*
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_HNTight2016.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_HNTightV1.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGHighPtMixTight.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGHighPtTight.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGTightPFIsoLoose.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGTightPFIsoMedium.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGTightPFIsoTight.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGTightPFIsoVeryTight.txt
ReadLimits/out/HNtypeI_JA/CutCount/2016/MuMu_SR1_SR2/result_VBF_POGTightPFIsoVeryVeryTight.txt

   */  //result_combined_passTightID.txt  result_combined_passTightID_noccb.txt


  std::map<double,double> map_HNTight2016 = GetMap(filepath+ "/result_VBF_HNTight2016.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightV1 = GetMap(filepath+ "/result_VBF_HNTightV1.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGHighPtMixTight = GetMap(filepath+ "/result_VBF_POGHighPtMixTight.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGHighPtTight = GetMap(filepath+ "/result_VBF_POGHighPtTight.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGTightPFIsoMedium = GetMap(filepath+ "/result_VBF_POGTightPFIsoMedium.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGTightPFIsoTight = GetMap(filepath+ "/result_VBF_POGTightPFIsoTight.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGTightPFIsoVeryTight = GetMap(filepath+ "/result_VBF_POGTightPFIsoVeryTight.txt", 13,1); /// cut and count
  std::map<double,double> map_HNTightPOGTightPFIsoVeryVeryTight = GetMap(filepath+ "/result_VBF_POGTightPFIsoVeryVeryTight.txt", 13,1); /// cut and count


  std::map<double,double> map_average;
  for(std::map<double,double>::iterator it = map_HNTight2016.begin(); it != map_HNTight2016.end(); it++){

    std::map<double,double>::iterator it2 = map_HNTightV1.find(it->first);
    std::map<double,double>::iterator it3 = map_HNTightPOGHighPtMixTight.find(it->first);
    std::map<double,double>::iterator it4 = map_HNTightPOGHighPtTight.find(it->first);
    std::map<double,double>::iterator it5 = map_HNTightPOGTightPFIsoMedium.find(it->first);
    std::map<double,double>::iterator it6 = map_HNTightPOGTightPFIsoTight.find(it->first);
    std::map<double,double>::iterator it7 = map_HNTightPOGTightPFIsoVeryTight.find(it->first);
    std::map<double,double>::iterator it8 = map_HNTightPOGTightPFIsoVeryVeryTight.find(it->first);
    cout << "Average " << it->first << " : " << (it->second + it2->second +it3->second +it5->second +it6->second +it7->second +it8->second)/7. << endl; 
    map_average[it->first] = (it->second +
			      it2->second +
			      it3->second +
			      //it4->second +
			      it5->second +
			      it6->second +
			      it7->second +
			      it8->second ) / 7.;
  }

  TGraphAsymmErrors*  ee_hn1       =  GetTGraph(map_average,map_HNTight2016,8);
  TGraphAsymmErrors*  ee_hn2       =  GetTGraph(map_average,map_HNTightV1,1);
  TGraphAsymmErrors*  ee_hn3       =  GetTGraph(map_average,map_HNTightPOGHighPtMixTight,2);
  TGraphAsymmErrors*  ee_hn4       =  GetTGraph(map_average,map_HNTightPOGHighPtTight,3);
  TGraphAsymmErrors*  ee_hn5       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoMedium,4);
  TGraphAsymmErrors*  ee_hn6       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoTight,5);
  TGraphAsymmErrors*  ee_hn7       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoVeryTight,6);
  TGraphAsymmErrors*  ee_hn8       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoVeryVeryTight,7);

  
    
  //=== EXO-17-028 overlay                                                                                                                                                                                  
  const int nm_17028 = 19;
  double mass_17028[nm_17028] = {
    100, 125, 150,200,
    250, 300, 400, 500,
    600, 700, 800, 900,
    1000, 1100, 1200, 1300,
    1400, 1500, 1700
  };


  double obs_17028[nm_17028], exp_17028[nm_17028];
  vector<double> tempvec_obs_17028, tempvec_exp_17028;
  vector<double> scales_17028;
  if(channel=="MuMu"){
    tempvec_exp_17028 = {
      175.333, 21.5041, 32.925, 56.3397,
      70.8081, 99.3095, 20.4264, 42.5126,
      60.1695, 116.721, 15.8605, 25.8407,
      38.43, 64.346, 100.265, 151.699,
      247.709, 340.424, 1340.34
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
      467.448, 65.4099, 90.4068, 159.838,216.957, 284.563, 59.74, 94.6793,
      104.302, 183.121, 30.189, 47.1442, 72.0759, 117.305, 183.214,
      285.811, 434.08, 644.258, 2506.94
    };
    scales_17028 = {
      0.001, 0.01, 0.01,0.01,0.01,0.01,0.1, 0.1,0.1,0.1,1,1,1,1,1,1,1,1,1,1
    };
    tempvec_obs_17028 = {
      368.924, 63.3389, 61.9159, 151.2,
      206.654, 254.261, 68.8604, 95.9664,
      123.0, 274.57, 24.8148, 46.0243,
      95.1426, 164.011, 252.706, 379.988,
      419.316, 631.767, 2486.31

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

  lg->AddEntry(hist_emptylegend,"","l");

  TLegend *lg_Alt = new TLegend(0.65, 0.15, 0.93, 0.48);
  lg_Alt->SetBorderSize(0);
  lg_Alt->SetFillStyle(0);

  //  lg_Alt->AddEntry(gr_17028_exp, "CMS 13 TeV dilepton", "l");
  TLegend *lg_Alt_SandT = (TLegend *)lg_Alt->Clone();

  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 900, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  //c_SOnly->SetLogy();

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
  dummy->GetYaxis()->SetRangeUser(0.01, 2.);
  dummy->SetTitle("");
  dummy->Draw("hist");
  /*
  TGraphAsymmErrors*  ee_hn1       =  GetTGraph(map_average,map_HNTight2016,1);
  TGraphAsymmErrors*  ee_hn2       =  GetTGraph(map_average,map_HNTightV1,1);
  TGraphAsymmErrors*  ee_hn3       =  GetTGraph(map_average,map_HNTightPOGHighPtMixTight,2);
  TGraphAsymmErrors*  ee_hn4       =  GetTGraph(map_average,map_HNTightPOGHighPtTight,3);
  TGraphAsymmErrors*  ee_hn5       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoMedium,4);
  TGraphAsymmErrors*  ee_hn6       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoTight,5);
  TGraphAsymmErrors*  ee_hn7       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoVeryTight,6);
  TGraphAsymmErrors*  ee_hn8       =  GetTGraph(map_average,map_HNTightPOGTightPFIsoVeryVeryTight,7);


   */
  lg_Alt->AddEntry(ee_hn1,"EXO-17-028 ID","l");
  lg_Alt->AddEntry(ee_hn2,"EXO-17-028 ID looser IP","l");
  lg_Alt->AddEntry(ee_hn3,"Tight_VTIso+HighPt","l");
  lg_Alt->AddEntry(ee_hn4,"HighPt","l");
  lg_Alt->AddEntry(ee_hn5,"Tight_MIso","l");
  lg_Alt->AddEntry(ee_hn6,"Tight_TIso","l");
  lg_Alt->AddEntry(ee_hn7,"Tight_VTIso","l");
  lg_Alt->AddEntry(ee_hn8,"Tight_VVTIso","l");
  
  ee_hn1->Draw("lsame");
  ee_hn2->Draw("lsame");
  ee_hn3->Draw("lsame");
  ee_hn4->Draw("lsame");
  ee_hn5->Draw("lsame");
  ee_hn6->Draw("lsame");
  ee_hn7->Draw("lsame");
  ee_hn8->Draw("lsame");
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

  //  c_SOnly->SetLogx();
  dummy->Draw("axissame");

  //==== HighMass
  dummy->GetXaxis()->SetRangeUser(90,2000);
  dummy->GetYaxis()->SetRangeUser(1E-4,2.);
  dummy->Draw("axissame");
  cout << plotpath+"/MuMu_SR1_SR2_ID_Ratio_CutCount_"+WhichYear+"_"+channel+"comparison_"+WhichDirectoryInCutop+".pdf" << endl;
  c_SOnly->SaveAs(plotpath+"/MuMu_SR1_SR2_ID_Ratio_CutCount_"+WhichYear+"_"+channel+"comparison_"+WhichDirectoryInCutop+".pdf"); 


  return;
}



std::map<double,double>  GetMap(TString input_path, int nbins, int i){

  string elline;
  ifstream in(input_path);
  ifstream in2(input_path);

  int n_central = 0;
  
  while(getline(in,elline)){
    if (TString(elline).Contains("END")) continue;
    n_central++;
  }

  int dummyint=0;

  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];
  std::map<double,double> _map;
  while(getline(in2,elline)){
    cout << "ell line = " << elline << endl;
    std::istringstream is( elline );
    is >> mass[dummyint];
    is >> obs[dummyint];
    is >> limit[dummyint];
    is >>onesig_left[dummyint];
    is >>onesig_right[dummyint];
    is >>twosig_left[dummyint];
    is >>twosig_right[dummyint];
    cout << input_path << " " << mass[dummyint] << " " <<  limit[dummyint] << endl;

    //if (obs[dummyint] == "-")       _map[mass[dummyint]] = 0.;
    //if (obs[dummyint] == "--")       _map[mass[dummyint]] = 0.;
    
    if(obs[dummyint]<=0 || limit[dummyint]<=0 ){
      _map[mass[dummyint]] = 0.;
    }
    else{
      _map[mass[dummyint]] = limit[dummyint];
    }
  }

  return _map;


}
  
TGraphAsymmErrors*  GetTGraph(std::map<double,double> map1, std::map<double,double> map2, int i ){

  int n_central =   map1.size();

  int dummyint=0;
  
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];

  cout << "n_central = " <<n_central<<endl;
  for(std::map<double,double>::iterator it = map1.begin(); it != map1.end(); it++){

    double dmass = it->first;
    cout << it->first << " " << it->second << endl;
    std::map<double,double>::iterator it2 = map2.find(dmass);
    double limit_r=1.;
    if (it2 != map2.end()) limit_r=it2->second;

    mass[dummyint] = it->first;
    obs[dummyint] = limit_r/it->second;
    limit[dummyint] = limit_r/it->second;
    onesig_left[dummyint] = limit_r/it->second;
    onesig_right[dummyint] = limit_r/it->second;
    twosig_left[dummyint] = limit_r/it->second;
    twosig_right[dummyint] = limit_r/it->second;
    dummyint++;
    continue;
  }

  cout << "n_central = " << n_central << " mass size = " << mass << endl;
  for(unsigned int k = 0; k < n_central ; k++){

    cout << "Mass = " << mass[k] << " expected = " << limit[k] << " + 1sigma = " << onesig_right[k] << " -1sigma = "  << onesig_left[k] << " + 2 sigma = " << twosig_right[k] << " - 2 sigam = " << twosig_left[k] << endl;
  }


  //TGraph *gr_13TeV_obs = new TGraph(n_central,mass,obs);                                                                                                                                                                                                                                                                                                           
  
  TGraphAsymmErrors *gr_13TeV_exp = new TGraphAsymmErrors(n_central,mass,limit,0,0,0,0);
  gr_13TeV_exp->SetLineWidth(3);
  gr_13TeV_exp->SetFillColor(kWhite);
  if(i==1)   gr_13TeV_exp->SetLineStyle(2);
  if(i==1)   gr_13TeV_exp->SetLineColor(kRed);
  //if(i==2)   gr_13TeV_exp->SetLineStyle(3);
  if(i==2)   gr_13TeV_exp->SetLineColor(kBlue);
  //if(i==3)   gr_13TeV_exp->SetLineStyle(4);
  if(i==3)   gr_13TeV_exp->SetLineColor(kGreen-2);
  //if(i==4)   gr_13TeV_exp->SetLineStyle(5);
  if(i==4)   gr_13TeV_exp->SetLineColor(kBlack);
  //if(i==5)   gr_13TeV_exp->SetLineStyle(6);
  if(i==5)   gr_13TeV_exp->SetLineColor(kCyan);
  if(i==6)   gr_13TeV_exp->SetLineColor(kOrange);
  if(i==7)   gr_13TeV_exp->SetLineColor(kViolet);
  if(i==7)   gr_13TeV_exp->SetLineStyle(6);
  if(i==8)   gr_13TeV_exp->SetLineStyle(5);
  
  return gr_13TeV_exp;


}
