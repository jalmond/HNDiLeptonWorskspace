#ifndef mylib_h
#define mylib_h

void SetBinLabels(TH1D* hist, std::vector<TString> list){

  for(unsigned int i = 0 ; i < list.size(); ++i){
    
    TString im = list.at(i);
    hist->GetXaxis()->SetBinLabel(i+1,im);
    
  }
  
  return;
           
}


double GetLumi(TString year){

  if  (year == "2016")  return 35600;
  if  (year == "2017")  return 41540;
  if  (year == "2018")  return 59960;
  
  return 35600+41540+59960;
}

double GetXsec(int mass){

    if(mass==100) return 7.77E-02;
  if(mass==125) return 2.45E-02;
  if(mass==150) return 1.10E-02;
  if(mass==200) return 3.40E-03;
  if(mass==250) return 1.43E-03;
  if(mass==300) return 7.13E-04;
  if(mass==400) return 2.37E-04;
  if(mass==500) return 9.86E-05;
  if(mass==600) return 4.72E-05;
  if(mass==700) return 2.47E-05;
  if(mass==800) return 1.38E-05;
  if(mass==900) return 8.11E-06;
  if(mass==1000) return 4.96E-06;
  if(mass==1100) return 3.12E-06;
  if(mass==1200) return 2.02E-06;
  if(mass==1300) return 1.33E-06;
  if(mass==1400) return 8.91E-07;
  if(mass==1500) return 6.05E-07;
  if(mass==1700) return 2.90E-07;
  if(mass==2000) return 1.02E-07;

  cout << "[GetXsec] Mass Wrong : " << mass << endl;
  return 0.;

}

TGraphAsymmErrors*  Get2016SoverSB(bool massbinned, TString year ,TString sr, TString channel, vector<double> masses){
   map<double, double>  tempvec_exo17028_ee_schannel_sr1_Eff;
  tempvec_exo17028_ee_schannel_sr1_Eff[100]= 1.1;
  tempvec_exo17028_ee_schannel_sr1_Eff[125]= 2.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[150]= 3.1;
  tempvec_exo17028_ee_schannel_sr1_Eff[200]= 4.9;
  tempvec_exo17028_ee_schannel_sr1_Eff[250]= 5.9;
  tempvec_exo17028_ee_schannel_sr1_Eff[300]= 7.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[400]= 6.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[500]= 5.5;
  tempvec_exo17028_ee_schannel_sr1_Eff[600]= 3.8;
  tempvec_exo17028_ee_schannel_sr1_Eff[700]= 4.0;
  tempvec_exo17028_ee_schannel_sr1_Eff[800]= 3.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[900]= 3.2 ;
  tempvec_exo17028_ee_schannel_sr1_Eff[1000]= 2.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[1100]= 2.2;
  tempvec_exo17028_ee_schannel_sr1_Eff[1200]= 2.0;
  tempvec_exo17028_ee_schannel_sr1_Eff[1300]= 1.8;
  tempvec_exo17028_ee_schannel_sr1_Eff[1400]= 1.5;
  tempvec_exo17028_ee_schannel_sr1_Eff[1500]= 1.3;

   map<double, double>  tempvec_exo17028_ee_schannel_sr2_Eff;
  tempvec_exo17028_ee_schannel_sr2_Eff[100]= 0.005;
  tempvec_exo17028_ee_schannel_sr2_Eff[125]= 0.04;
  tempvec_exo17028_ee_schannel_sr2_Eff[150]= 0.19;
  tempvec_exo17028_ee_schannel_sr2_Eff[200]= 0.6;
  tempvec_exo17028_ee_schannel_sr2_Eff[250]= 2.2;
  tempvec_exo17028_ee_schannel_sr2_Eff[300]= 3.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[400]= 9.1;
  tempvec_exo17028_ee_schannel_sr2_Eff[500]= 14.3;
  tempvec_exo17028_ee_schannel_sr2_Eff[600]= 17.4;
  tempvec_exo17028_ee_schannel_sr2_Eff[700]= 19.4;
  tempvec_exo17028_ee_schannel_sr2_Eff[800]= 20.8;
  tempvec_exo17028_ee_schannel_sr2_Eff[900]= 19.2;
  tempvec_exo17028_ee_schannel_sr2_Eff[1000]= 21.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[1100]= 20.3;
  tempvec_exo17028_ee_schannel_sr2_Eff[1200]= 20.8;
  tempvec_exo17028_ee_schannel_sr2_Eff[1300]= 20.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[1400]= 19.6;
  tempvec_exo17028_ee_schannel_sr2_Eff[1500]= 19.5;

  map<double, double>  tempvec_exo17028_mm_schannel_sr1_Eff;
  tempvec_exo17028_mm_schannel_sr1_Eff[100]= 2.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[125]= 5.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[150]= 6.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[200]= 8.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[250]= 11;
  tempvec_exo17028_mm_schannel_sr1_Eff[300]= 13.2;
  tempvec_exo17028_mm_schannel_sr1_Eff[400]= 11.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[500]= 8.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[600]= 7.4;
  tempvec_exo17028_mm_schannel_sr1_Eff[700]= 6.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[800]= 6.0;
  tempvec_exo17028_mm_schannel_sr1_Eff[900]= 5.4;
  tempvec_exo17028_mm_schannel_sr1_Eff[1000]= 4.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[1100]= 4.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[1200]= 3.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[1300]= 3.2;
  tempvec_exo17028_mm_schannel_sr1_Eff[1400]= 2.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[1500]= 2.5;

  map<double, double>  tempvec_exo17028_mm_schannel_sr2_Eff;
  tempvec_exo17028_mm_schannel_sr2_Eff[100]= 0.006;
  tempvec_exo17028_mm_schannel_sr2_Eff[125]= 0.08;
  tempvec_exo17028_mm_schannel_sr2_Eff[150]= 0.28;
  tempvec_exo17028_mm_schannel_sr2_Eff[200]= 1.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[250]= 3;
  tempvec_exo17028_mm_schannel_sr2_Eff[300]= 5.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[400]= 13.3;
  tempvec_exo17028_mm_schannel_sr2_Eff[500]= 22.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[600]= 30.2;
  tempvec_exo17028_mm_schannel_sr2_Eff[700]= 34.6;
  tempvec_exo17028_mm_schannel_sr2_Eff[800]= 34.8;
  tempvec_exo17028_mm_schannel_sr2_Eff[900]= 35.8;
  tempvec_exo17028_mm_schannel_sr2_Eff[1000]= 38.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[1100]= 36.7;
  tempvec_exo17028_mm_schannel_sr2_Eff[1200]= 38.5;
  tempvec_exo17028_mm_schannel_sr2_Eff[1300]= 38.5;
  tempvec_exo17028_mm_schannel_sr2_Eff[1400]= 35.9;
  tempvec_exo17028_mm_schannel_sr2_Eff[1500]= 36.4;


  map<double, double>  tempvec_exo17028_ee_tchannel_sr1_Eff;
  tempvec_exo17028_ee_tchannel_sr1_Eff[300]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[400]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[500]= 2.7;
  tempvec_exo17028_ee_tchannel_sr1_Eff[600]= 1.7;
  tempvec_exo17028_ee_tchannel_sr1_Eff[700]= 2.8;
  tempvec_exo17028_ee_tchannel_sr1_Eff[800]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[900]= 2.9;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1000]= 2.4;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1100]= 2.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1200]= 1.8;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1300]= 1.6;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1400]= 1.3;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1500]= 1.2;

  map<double, double>  tempvec_exo17028_ee_tchannel_sr2_Eff;
  tempvec_exo17028_ee_tchannel_sr2_Eff[300]= 0.6;
  tempvec_exo17028_ee_tchannel_sr2_Eff[400]= 2.9;
  tempvec_exo17028_ee_tchannel_sr2_Eff[500]= 6.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[600]= 11;
  tempvec_exo17028_ee_tchannel_sr2_Eff[700]= 13.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[800]= 14;
  tempvec_exo17028_ee_tchannel_sr2_Eff[900]= 13.2;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1000]= 15.3;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1100]= 14.7;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1200]= 15.3;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1300]= 15.5;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1400]= 15.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1500]= 15.2;

  map<double, double>  tempvec_exo17028_mm_tchannel_sr1_Eff;
  tempvec_exo17028_mm_tchannel_sr1_Eff[300]= 5.2;
  tempvec_exo17028_mm_tchannel_sr1_Eff[400]= 5.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[500]= 4.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[600]= 4.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[700]= 3.9;
  tempvec_exo17028_mm_tchannel_sr1_Eff[800]= 5.4;
  tempvec_exo17028_mm_tchannel_sr1_Eff[900]= 5.0;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1000]= 4.2;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1100]= 3.8;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1200]= 3.4;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1300]= 3.0;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1400]= 2.7;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1500]= 2.3;

  map<double, double>  tempvec_exo17028_mm_tchannel_sr2_Eff;
  tempvec_exo17028_mm_tchannel_sr2_Eff[300]= 0.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[400]= 2.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[500]= 6.8;
  tempvec_exo17028_mm_tchannel_sr2_Eff[600]= 20.4;
  tempvec_exo17028_mm_tchannel_sr2_Eff[700]= 24.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[800]= 24.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[900]= 26.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1000]= 28.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1100]= 29.2;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1200]= 30.1;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1300]= 30.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1400]= 29.4;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1500]= 30.0;


  ///////
  map<double, double>  tempvec_exo17028_ee_schannel_sr1_Bkg;
  tempvec_exo17028_ee_schannel_sr1_Bkg[100]= 20.3;
  tempvec_exo17028_ee_schannel_sr1_Bkg[125]= 17.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[150]= 14.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[200]= 12.4;
  tempvec_exo17028_ee_schannel_sr1_Bkg[250]= 6.0;
  tempvec_exo17028_ee_schannel_sr1_Bkg[300]= 8.2;
  tempvec_exo17028_ee_schannel_sr1_Bkg[400]= 2.5;
  tempvec_exo17028_ee_schannel_sr1_Bkg[500]= 1.5;
  tempvec_exo17028_ee_schannel_sr1_Bkg[600]= 0.9;
  tempvec_exo17028_ee_schannel_sr1_Bkg[700]= 1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[800]= 1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[900]= 1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1000]=1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1100]=1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1200]=1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1300]=1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1400]=1.7;
  tempvec_exo17028_ee_schannel_sr1_Bkg[1500]=1.7;

  map<double, double>  tempvec_exo17028_ee_schannel_sr2_Bkg;
  tempvec_exo17028_ee_schannel_sr2_Bkg[100]= 3.4;
  tempvec_exo17028_ee_schannel_sr2_Bkg[125]= 0.2;
  tempvec_exo17028_ee_schannel_sr2_Bkg[150]= 1.3;
  tempvec_exo17028_ee_schannel_sr2_Bkg[200]= 0.8;
  tempvec_exo17028_ee_schannel_sr2_Bkg[250]= 2.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[300]= 1.3;
  tempvec_exo17028_ee_schannel_sr2_Bkg[400]= 3.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[500]= 2.8;
  tempvec_exo17028_ee_schannel_sr2_Bkg[600]= 0.8;
  tempvec_exo17028_ee_schannel_sr2_Bkg[700]= 0.8;
  tempvec_exo17028_ee_schannel_sr2_Bkg[800]= 0.9;
  tempvec_exo17028_ee_schannel_sr2_Bkg[900]= 0.2;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1000]= 0.3;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1100]=0.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1200]=0.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1300]=0.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1400]=0.1;
  tempvec_exo17028_ee_schannel_sr2_Bkg[1500]=0.1;

  map<double, double>  tempvec_exo17028_mm_schannel_sr1_Bkg;
  tempvec_exo17028_mm_schannel_sr1_Bkg[100]= 18.6;
  tempvec_exo17028_mm_schannel_sr1_Bkg[125]= 11.7;
  tempvec_exo17028_mm_schannel_sr1_Bkg[150]= 8.9;
  tempvec_exo17028_mm_schannel_sr1_Bkg[200]= 4.6;
  tempvec_exo17028_mm_schannel_sr1_Bkg[250]= 3.0;
  tempvec_exo17028_mm_schannel_sr1_Bkg[300]= 2.6;
  tempvec_exo17028_mm_schannel_sr1_Bkg[400]= 0.9;
  tempvec_exo17028_mm_schannel_sr1_Bkg[500]= 0.4;
  tempvec_exo17028_mm_schannel_sr1_Bkg[600]= 0.3;
  tempvec_exo17028_mm_schannel_sr1_Bkg[700]= 0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[800]= 0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[900]= 0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1000]=0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1100]=0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1200]=0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1300]=0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1400]=0.2;
  tempvec_exo17028_mm_schannel_sr1_Bkg[1500]=0.2;

  map<double, double>  tempvec_exo17028_mm_schannel_sr2_Bkg;
  tempvec_exo17028_mm_schannel_sr2_Bkg[100]= 1.0;
  tempvec_exo17028_mm_schannel_sr2_Bkg[125]= 0.8;
  tempvec_exo17028_mm_schannel_sr2_Bkg[150]= 1.0;
  tempvec_exo17028_mm_schannel_sr2_Bkg[200]= 1.3;
  tempvec_exo17028_mm_schannel_sr2_Bkg[250]= 0.3;
  tempvec_exo17028_mm_schannel_sr2_Bkg[300]= 0.4;
  tempvec_exo17028_mm_schannel_sr2_Bkg[400]= 0.5;
  tempvec_exo17028_mm_schannel_sr2_Bkg[500]= 0.8;
  tempvec_exo17028_mm_schannel_sr2_Bkg[600]= 0.7;
  tempvec_exo17028_mm_schannel_sr2_Bkg[700]= 0.8;
  tempvec_exo17028_mm_schannel_sr2_Bkg[800]= 0.4;
  tempvec_exo17028_mm_schannel_sr2_Bkg[900]= 0.2;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1000]=0.1;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1100]=0.1;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1200]=0.2;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1300]=0.3;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1400]=0.1;
  tempvec_exo17028_mm_schannel_sr2_Bkg[1500]=0.1;



  
  map<double, double> tmpM ;
  if(sr == "SR1" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr1_Eff;
  if(sr == "SR2" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr2_Eff;
  if(sr == "SR1" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr1_Eff;
  if(sr == "SR2" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr2_Eff;

  map<double, double> tmpMBkg ;
  if(sr == "SR1" && channel == "MuMu") tmpMBkg = tempvec_exo17028_mm_schannel_sr1_Bkg;
  if(sr == "SR2" && channel == "MuMu") tmpMBkg = tempvec_exo17028_mm_schannel_sr2_Bkg;
  if(sr == "SR1" && channel == "EE") tmpMBkg = tempvec_exo17028_ee_schannel_sr1_Bkg;
  if(sr == "SR2" && channel == "EE") tmpMBkg = tempvec_exo17028_ee_schannel_sr2_Bkg;

  int Nbins = masses.size();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];

  for(Int_t i=0; i<Nbins; i++){

    map<double, double>::iterator its = tmpM.find(masses[i]);
    map<double, double>::iterator itb = tmpMBkg.find(masses[i]);
    x[i] = masses[i];
    if(massbinned){
      y[i] = 0.01*its->second / sqrt(itb->second);
      cout << "EXO 17-028 " << masses[i] << " " << its->second  << " " << itb->second <<  " s/sb = " << 0.01*its->second / sqrt(itb->second) <<endl;
    }
    else{
      float bkg = 502.;
      if(sr == "SR1" && channel == "MuMu")bkg = 502.;
      if(sr == "SR1" && channel == "EE")bkg = 382.;
      if(sr == "SR2" && channel == "MuMu")bkg = 13.;
      if(sr == "SR2" && channel == "EE")bkg = 10.;

      y[i] = 0.;//0.01*its->second / sqrt(itb->second);
      cout << "EXO 17-028 " << masses[i] << " " << its->second  << " " << itb->second <<  " s/sb = " << 0.01*its->second / sqrt(bkg) <<endl;
      
    }
    xlow[i]=  0.;
    xup[i] = 0.;
    ylow[i] = 0.;
    yup[i] = 0.;
  }


  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  //out->SetLineWidth(2.0);                                                                                                                                                                                                                   
  //out->SetMarkerSize(0.);                                                                                                                                                                                                                   
  out->GetHistogram()->GetXaxis()->SetTitle("m_{N} (GeV)");
  out->GetHistogram()->GetYaxis()->SetTitle("#epsilon/sqrt(B)");
  out->SetTitle("");
  return out;


}

TGraphAsymmErrors* Get2016SigEff(TString sr, TString channel, vector<double> masses){

  map<double, double>  tempvec_exo17028_ee_schannel_sr1_Eff;
  tempvec_exo17028_ee_schannel_sr1_Eff[100]= 1.1;
  tempvec_exo17028_ee_schannel_sr1_Eff[125]= 2.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[150]= 3.1;
  tempvec_exo17028_ee_schannel_sr1_Eff[200]= 4.9;
  tempvec_exo17028_ee_schannel_sr1_Eff[250]= 5.9;
  tempvec_exo17028_ee_schannel_sr1_Eff[300]= 7.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[400]= 6.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[500]= 5.5;
  tempvec_exo17028_ee_schannel_sr1_Eff[600]= 3.8;
  tempvec_exo17028_ee_schannel_sr1_Eff[700]= 4.0;
  tempvec_exo17028_ee_schannel_sr1_Eff[800]= 3.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[900]= 3.2 ;
  tempvec_exo17028_ee_schannel_sr1_Eff[1000]= 2.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[1100]= 2.2;
  tempvec_exo17028_ee_schannel_sr1_Eff[1200]= 2.0;
  tempvec_exo17028_ee_schannel_sr1_Eff[1300]= 1.8;
  tempvec_exo17028_ee_schannel_sr1_Eff[1400]= 1.5;
  tempvec_exo17028_ee_schannel_sr1_Eff[1500]= 1.3;

  map<double, double>  tempvec_exo17028_ee_schannel_sr2_Eff;
  tempvec_exo17028_ee_schannel_sr2_Eff[100]= 0.005;
  tempvec_exo17028_ee_schannel_sr2_Eff[125]= 0.04;
  tempvec_exo17028_ee_schannel_sr2_Eff[150]= 0.19;
  tempvec_exo17028_ee_schannel_sr2_Eff[200]= 0.6;
  tempvec_exo17028_ee_schannel_sr2_Eff[250]= 2.2;
  tempvec_exo17028_ee_schannel_sr2_Eff[300]= 3.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[400]= 9.1;
  tempvec_exo17028_ee_schannel_sr2_Eff[500]= 14.3;
  tempvec_exo17028_ee_schannel_sr2_Eff[600]= 17.4;
  tempvec_exo17028_ee_schannel_sr2_Eff[700]= 19.4;
  tempvec_exo17028_ee_schannel_sr2_Eff[800]= 20.8;
  tempvec_exo17028_ee_schannel_sr2_Eff[900]= 19.2;
  tempvec_exo17028_ee_schannel_sr2_Eff[1000]= 21.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[1100]= 20.3;
  tempvec_exo17028_ee_schannel_sr2_Eff[1200]= 20.8;
  tempvec_exo17028_ee_schannel_sr2_Eff[1300]= 20.5;
  tempvec_exo17028_ee_schannel_sr2_Eff[1400]= 19.6;
  tempvec_exo17028_ee_schannel_sr2_Eff[1500]= 19.5;

  map<double, double>  tempvec_exo17028_mm_schannel_sr1_Eff;
  tempvec_exo17028_mm_schannel_sr1_Eff[100]= 2.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[125]= 5.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[150]= 6.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[200]= 8.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[250]= 11;
  tempvec_exo17028_mm_schannel_sr1_Eff[300]= 13.2;
  tempvec_exo17028_mm_schannel_sr1_Eff[400]= 11.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[500]= 8.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[600]= 7.4;
  tempvec_exo17028_mm_schannel_sr1_Eff[700]= 6.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[800]= 6.0;
  tempvec_exo17028_mm_schannel_sr1_Eff[900]= 5.4;
  tempvec_exo17028_mm_schannel_sr1_Eff[1000]= 4.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[1100]= 4.1;
  tempvec_exo17028_mm_schannel_sr1_Eff[1200]= 3.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[1300]= 3.2;
  tempvec_exo17028_mm_schannel_sr1_Eff[1400]= 2.7;
  tempvec_exo17028_mm_schannel_sr1_Eff[1500]= 2.5;

  map<double, double>  tempvec_exo17028_mm_schannel_sr2_Eff;
  tempvec_exo17028_mm_schannel_sr2_Eff[100]= 0.006;
  tempvec_exo17028_mm_schannel_sr2_Eff[125]= 0.08;
  tempvec_exo17028_mm_schannel_sr2_Eff[150]= 0.28;
  tempvec_exo17028_mm_schannel_sr2_Eff[200]= 1.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[250]= 3;
  tempvec_exo17028_mm_schannel_sr2_Eff[300]= 5.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[400]= 13.3;
  tempvec_exo17028_mm_schannel_sr2_Eff[500]= 22.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[600]= 30.2;
  tempvec_exo17028_mm_schannel_sr2_Eff[700]= 34.6;
  tempvec_exo17028_mm_schannel_sr2_Eff[800]= 34.8;
  tempvec_exo17028_mm_schannel_sr2_Eff[900]= 35.8;
  tempvec_exo17028_mm_schannel_sr2_Eff[1000]= 38.4;
  tempvec_exo17028_mm_schannel_sr2_Eff[1100]= 36.7;
  tempvec_exo17028_mm_schannel_sr2_Eff[1200]= 38.5;
  tempvec_exo17028_mm_schannel_sr2_Eff[1300]= 38.5;
  tempvec_exo17028_mm_schannel_sr2_Eff[1400]= 35.9;
  tempvec_exo17028_mm_schannel_sr2_Eff[1500]= 36.4;


  map<double, double>  tempvec_exo17028_ee_tchannel_sr1_Eff;
  tempvec_exo17028_ee_tchannel_sr1_Eff[300]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[400]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[500]= 2.7;
  tempvec_exo17028_ee_tchannel_sr1_Eff[600]= 1.7;
  tempvec_exo17028_ee_tchannel_sr1_Eff[700]= 2.8;
  tempvec_exo17028_ee_tchannel_sr1_Eff[800]= 3.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[900]= 2.9;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1000]= 2.4;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1100]= 2.0;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1200]= 1.8;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1300]= 1.6;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1400]= 1.3;
  tempvec_exo17028_ee_tchannel_sr1_Eff[1500]= 1.2;

  map<double, double>  tempvec_exo17028_ee_tchannel_sr2_Eff;
  tempvec_exo17028_ee_tchannel_sr2_Eff[300]= 0.6;
  tempvec_exo17028_ee_tchannel_sr2_Eff[400]= 2.9;
  tempvec_exo17028_ee_tchannel_sr2_Eff[500]= 6.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[600]= 11;
  tempvec_exo17028_ee_tchannel_sr2_Eff[700]= 13.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[800]= 14;
  tempvec_exo17028_ee_tchannel_sr2_Eff[900]= 13.2;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1000]= 15.3;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1100]= 14.7;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1200]= 15.3;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1300]= 15.5;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1400]= 15.1;
  tempvec_exo17028_ee_tchannel_sr2_Eff[1500]= 15.2;

  map<double, double>  tempvec_exo17028_mm_tchannel_sr1_Eff;
  tempvec_exo17028_mm_tchannel_sr1_Eff[300]= 5.2;
  tempvec_exo17028_mm_tchannel_sr1_Eff[400]= 5.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[500]= 4.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[600]= 4.1;
  tempvec_exo17028_mm_tchannel_sr1_Eff[700]= 3.9;
  tempvec_exo17028_mm_tchannel_sr1_Eff[800]= 5.4;
  tempvec_exo17028_mm_tchannel_sr1_Eff[900]= 5.0;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1000]= 4.2;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1100]= 3.8;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1200]= 3.4;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1300]= 3.0;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1400]= 2.7;
  tempvec_exo17028_mm_tchannel_sr1_Eff[1500]= 2.3;

  map<double, double>  tempvec_exo17028_mm_tchannel_sr2_Eff;
  tempvec_exo17028_mm_tchannel_sr2_Eff[300]= 0.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[400]= 2.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[500]= 6.8;
  tempvec_exo17028_mm_tchannel_sr2_Eff[600]= 20.4;
  tempvec_exo17028_mm_tchannel_sr2_Eff[700]= 24.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[800]= 24.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[900]= 26.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1000]= 28.9;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1100]= 29.2;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1200]= 30.1;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1300]= 30.7;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1400]= 29.4;
  tempvec_exo17028_mm_tchannel_sr2_Eff[1500]= 30.0;

  map<double, double> tmpM ;
  if(sr == "SR1" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr1_Eff;
  if(sr == "SR2" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr2_Eff;
  if(sr == "SR1" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr1_Eff;
  if(sr == "SR2" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr2_Eff;

  int Nbins = masses.size();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];

  for(Int_t i=0; i<Nbins; i++){

    map<double, double>::iterator it = tmpM.find(masses[i]);
    x[i] = masses[i];
    y[i] = it->second/100.;
    xlow[i]=  0.;
    xup[i] = 0.;
    ylow[i] = 0.;
    yup[i] = 0.;
  }


  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  //out->SetLineWidth(2.0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //out->SetMarkerSize(0.);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  out->GetHistogram()->GetXaxis()->SetTitle("m_{N} (GeV)");
  out->GetHistogram()->GetYaxis()->SetTitle("#epsilon");
  out->SetTitle("");
  return out;


}



TGraphAsymmErrors* Get2016SigEffHighMass(TString sr, TString channel, vector<double> masses){

  map<double, double>  tempvec_exo17028_ee_schannel_sr1_Eff;
  tempvec_exo17028_ee_schannel_sr1_Eff[100]= 3.6;
  tempvec_exo17028_ee_schannel_sr1_Eff[125]= 10;
  tempvec_exo17028_ee_schannel_sr1_Eff[150]= 14.;
  tempvec_exo17028_ee_schannel_sr1_Eff[200]= 19.;
  tempvec_exo17028_ee_schannel_sr1_Eff[250]= 22.;
  tempvec_exo17028_ee_schannel_sr1_Eff[300]= 24.;
  tempvec_exo17028_ee_schannel_sr1_Eff[400]= 27.;
  tempvec_exo17028_ee_schannel_sr1_Eff[500]= 28.;
  tempvec_exo17028_ee_schannel_sr1_Eff[600]= 30;
  tempvec_exo17028_ee_schannel_sr1_Eff[700]= 30.;
  tempvec_exo17028_ee_schannel_sr1_Eff[800]= 30.;
  tempvec_exo17028_ee_schannel_sr1_Eff[900]= 29.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1000]= 29.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1100]=28.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1200]=28.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1300]=27.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1400]=26.;
  tempvec_exo17028_ee_schannel_sr1_Eff[1500]=26.;
  
  map<double, double>  tempvec_exo17028_mm_schannel_sr1_Eff;
  tempvec_exo17028_mm_schannel_sr1_Eff[100]= 7.6;
  tempvec_exo17028_mm_schannel_sr1_Eff[125]= 17.;
  tempvec_exo17028_mm_schannel_sr1_Eff[150]= 23.;
  tempvec_exo17028_mm_schannel_sr1_Eff[200]= 30.;
  tempvec_exo17028_mm_schannel_sr1_Eff[250]= 35.;
  tempvec_exo17028_mm_schannel_sr1_Eff[300]= 40.;
  tempvec_exo17028_mm_schannel_sr1_Eff[400]= 45.;
  tempvec_exo17028_mm_schannel_sr1_Eff[500]= 48.;
  tempvec_exo17028_mm_schannel_sr1_Eff[600]= 51.;
  tempvec_exo17028_mm_schannel_sr1_Eff[700]= 51.;
  tempvec_exo17028_mm_schannel_sr1_Eff[800]= 52.;
  tempvec_exo17028_mm_schannel_sr1_Eff[900]= 52.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1000]=52.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1100]=51.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1200]=51.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1300]=51.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1400]=50.;
  tempvec_exo17028_mm_schannel_sr1_Eff[1500]=49;


  map<double, double> tmpM ;
  if(sr == "SR1" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr1_Eff;
  else if(sr == "SR2" && channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr1_Eff;
  else if(sr == "SR1" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr1_Eff;
  else if(sr == "SR2" && channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr1_Eff;
  else if (channel == "MuMu") tmpM = tempvec_exo17028_mm_schannel_sr1_Eff;
  else if (channel == "EE") tmpM = tempvec_exo17028_ee_schannel_sr1_Eff;
  
  int Nbins = masses.size();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];

  for(Int_t i=0; i<Nbins; i++){

    map<double, double>::iterator it = tmpM.find(masses[i]);
    x[i] = masses[i];
    y[i] = it->second/100.;
    xlow[i]=  0.;
    xup[i] = 0.;
    ylow[i] = 0.;
    yup[i] = 0.;
  }
  
  
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  //out->SetLineWidth(2.0);
  //out->SetMarkerSize(0.);
  out->GetHistogram()->GetXaxis()->SetTitle("m_{N} (GeV)");
  out->GetHistogram()->GetYaxis()->SetTitle("#epsilon");
  out->SetTitle("");
  return out;
  
  
}

void FormatHist(TH1* h , TString fill, Color_t t){


  if(fill.Contains("f")){
    h->SetFillColor(t);
    h->SetLineColor(t);
  h->SetLineWidth(10);    
  }
  if(fill.Contains("l")){

    h->SetLineWidth(10);

    h->SetLineColor(t);
  }
  if(fill.Contains("p")){

  h->SetMarkerColor(t);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.6);
  h->SetLineWidth(10);
  }
  
}

bool FileHasDir(TFile* file, TString name){

    TList* list = file->GetListOfKeys() ;
    TIter next(list) ;
    TKey* key ;
    TObject* obj ;
    
    bool dir_found=false;
    while ( (key = (TKey*)next()) ) {
      obj = key->ReadObj() ;
      TString hname = obj->GetName();
      TString objname= obj->ClassName();
      if(hname == name && objname.Contains("Dir")) dir_found=true;
    }
    if(dir_found) return true;
    //scout << "File " << file->GetName() << " missing directory " << name << endl;

    TIter next2(list) ;
    TKey* key2 ;
    TObject* obj2 ;
    
    while ( (key2 = (TKey*)next2()) ) {
        obj2 = key2->ReadObj() ;
        TString hname2 = obj2->GetName();
        TString objname2= obj2->ClassName();
        //cout << "Possible directory names are " << hname2 << endl;

      }

    return false;
}

 
bool CheckHist(TFile* file, TString name ){
  
  TString name_fix = name;
  name_fix = name_fix.ReplaceAll("/"," ");
  TH1* h;
  vector<string> v{_getsplit(string(name_fix), ' ')};
  TList* list ;
  if(v.size() == 2){
    if(FileHasDir(file, TString(v[0])))list = file->GetDirectory(TString(v[0]))->GetListOfKeys() ;
    //name= v[1];                                                                                                                 
    else return false;
  }
  else{
    list = file->GetListOfKeys() ;
  }
  
  
  TIter next(list) ;
  TKey* key ;
  TObject* obj ;

  bool hist_found=false;
  while ( (key = (TKey*)next()) ) {
    obj = key->ReadObj() ;
    TString hname = obj->GetName();
    TString objname= obj->ClassName();
    if(hname == name) hist_found=true;
  }
  if(!hist_found) return false;
  return true;
}

TH1D* GetHist(TFile* file, TString name , bool return_void=true, bool debug=false){
  
  TString name_fix = name;
  name_fix = name_fix.ReplaceAll("/"," ");
  //TH1* h = new TH1(name);
  vector<string> v{_getsplit(string(name_fix), ' ')};
  TList* list ;
  if(v.size() == 2){
    if(FileHasDir(file, TString(v[0])))list = file->GetDirectory(TString(v[0]))->GetListOfKeys() ;
    //name= v[1];
    else {
      TH1D* this_hist = new TH1D(name+"__"+file->GetName(), name+"__"+file->GetName(),1,0.,1);
      return this_hist;

    }
  }
  else{
    list = file->GetListOfKeys() ;
  }

  TIter next(list) ;
  TKey* key ;
  TObject* obj ;

  bool hist_found=false;
  while ( (key = (TKey*)next()) ) {
    obj = key->ReadObj() ;
    TString hname = obj->GetName();
    TString objname= obj->ClassName();
    if(hname == name) hist_found=true;
  }
  if(!hist_found){

    cout << "File " << file->GetName() << " missing file " << name << endl;

    TH1D* this_hist = new TH1D(name+"__"+file->GetName(), name+"__"+file->GetName(),1,0.,1);
    return this_hist;
    

    vector<TList*> lists;
    TList* list2  = file->GetListOfKeys() ;
    if(v.size() > 0) lists.push_back(list);
    lists.push_back(list2);    
    for(unsigned int il=0; il < lists.size();il++){
      TIter next(lists[il]) ;
      TKey* key ;
      TObject* obj ;
      
      while ( (key = (TKey*)next()) ) {
	obj = key->ReadObj() ;
	TString hname = obj->GetName();
	TString objname= obj->ClassName();
	//if(debug)cout << "Possible hist names are " << hname << endl;
	
      }
      double ml1jbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
      
      TH1D* this_hist = new TH1D(name+"__"+file->GetName(), "", 6, ml1jbins);

      TH1D* this_hist2 = new TH1D(name+"__2"+file->GetName(), name+"__",1,0.,1);
      if(return_void) return this_hist2;
      else       return this_hist;
    }
  }
  TH1* h = (TH1F*)(file->Get(name));

  TH1D* h_C = (TH1D*)h_C->Clone(name+"clone"+file->GetName());

  return h_C;
  
  
}

double GetSignalIntegral( double mass, TString year, TString sigpath,  TString n_sr_hist, TString hist_all){
  
  TFile * filemm = new TFile((sigpath).Data());
  if(CheckFile(filemm) > 0)  return 0.;
  TH1*  hpass = GetHist(filemm, n_sr_hist);
  TH1*  hall = GetHist(filemm, hist_all);

  return ( hpass->Integral()/hall->Integral()) * GetLumi(year)*GetXsec(mass) ;

}
double GetIntegral( TString sigpath,  TString n_sr_hist){

  TFile * filemm = new TFile((sigpath).Data());
  if(CheckFile(filemm) > 0)  return 0.;
  if(!CheckHist(filemm, n_sr_hist)) return 0.;
  TH1*  hpass = GetHist(filemm, n_sr_hist,true);
  double tot = hpass->Integral();
  filemm->Close();
  delete filemm;

  return tot;

}


double SignalScale(TString year, TString mass){

  float scale = 1.;
  if(mass == "100") scale = 0.001;
  if(mass == "200") scale = 0.001;
  if(mass == "300") scale = 0.1;
  if(mass == "400") scale = 0.1;
  if(mass == "500") scale = 0.1;
  if(mass == "600") scale = 0.1;
  if(mass == "700") scale = 1.;
  if(mass == "800") scale = 1.;
  if(mass == "900") scale = 1.;
  if(mass == "1000") scale = 1.;
  if(mass == "1100") scale = 1.;
  if(mass == "1200") scale = 10.;
  if(mass == "1300") scale = 10.;
  if(mass == "1400") scale = 10.;
  if(mass == "1500") scale = 10.;

  if (year == "2017") scale *= 41.54/36.47;
  if (year == "2018") scale *= 59.96/36.47;

  return scale;

  
}
void WriteToFile(TString mass, TString year, TString signal, TFile* fo, TString path_, vector<pair<TString,TString> > samples, TString histname, vector<TString> systs){

  for (unsigned int i = 0 ; i < samples.size(); i++){
    for(const auto& _syst: systs) {
      
      if(samples[i].first.Contains("data") && _syst!= "")continue;
      TString h_path =  path_ + samples[i].second + ".root";
      TFile * file_ = new TFile((h_path).Data());
      
      TString _systname = "";
      if (_syst != "") _systname = "_"+_syst;
      cout << histname+_syst << endl;
      bool ishist=CheckHist(file_, histname+_syst);
      if (!ishist){
	double ml1jbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
	double ml2jbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
	double mlljbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
	TH1D* this_hist = new TH1D(histname+"__", "", 6, ml1jbins);
	fo->cd();
	this_hist->SetName(samples[i].first+_systname);
	this_hist->Write();
	delete this_hist;
      }
      else{
	TH1* hist = GetHist(file_, histname+_syst);
	fo->cd();
	cout << "Writing " << samples[i].first+_systname << endl;
	cout << hist->Integral() << endl;
	hist->SetName(samples[i].first+_systname);
	hist->Scale(0.8);
	hist->Write();
	cout << h_path << " " << samples[i].first+_systname << " " << hist->Integral() << endl;
      }
      file_->Close();
    }
  }
  
  for(const auto& _syst: systs) {

    TString h_path = signal;
    TFile * file_ = new TFile((h_path).Data());

    TString _systname =	"";
    if (_syst != "") _systname = "_"+_syst;

    bool ishist=CheckHist(file_, histname+_syst);

    if (!ishist){
      double ml1jbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
      double ml2jbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
      double mlljbins[7] = { 0., 100.,200.,300.,500., 1000., 2000.};
      TH1D* this_hist = new TH1D(histname+"__", "", 6, ml1jbins);
      fo->cd();
      this_hist->SetName("signal"+_systname);
      this_hist->Write();
      delete this_hist;
    }
    else{
    TH1* hist = GetHist(file_, histname+_syst);
    TH1* hist_tmp = (TH1*)hist->Clone(histname+_syst+"_nocale");

      fo->cd();
      hist->SetName("signal" +_systname+"_noscale");
      double _scale= SignalScale(year,mass);
      hist->Write();
      hist_tmp->Scale(_scale);
      hist_tmp->SetName("signal" +_systname);
      hist_tmp->Write();
    }
    file_->Close();
    }

}

double GetMaximum(TGraphAsymmErrors* g1, vector<TGraphAsymmErrors*> grs){

  double _max= g1->GetHistogram()->GetMaximum();
  for(unsigned int ig=0; ig < grs.size(); ig++){
    if (grs[ig]->GetHistogram()->GetMaximum() > _max) _max = grs[ig]->GetHistogram()->GetMaximum();
  }
  return _max;
}

TGraphAsymmErrors* v_to_graph(int Nbins,  vector<double> vx,  vector<double> vxup, vector<double> vxdown, vector<double> vy,  vector<double> vyup,  vector<double> vydown, Color_t col){

  TH1::SetDefaultSumw2(true);


  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];

  for(Int_t i=0; i<Nbins; i++){
    x[i] =vx[i];
    y[i] = vy[i];
    xlow[i] = vxdown[i];
    xup[i] = vxup[i];
    ylow[i] = vydown[i];
    yup[i] = vyup[i];

  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetLineWidth(2.0);
  //out->SetMarkerSize(0.);
  out->SetLineColor(col);
  out->SetMarkerColor(col);

  out->SetTitle("");
  return out;

}


TGraphAsymmErrors* hist_to_graph(TH1D* hist, bool YErrorZero=false){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=0; i<Nbins; i++){
    x[i] = xaxis->GetBinCenter(i+1);
    y[i] = hist->GetBinContent(i+1);
    xlow[i] = xaxis->GetBinCenter(i+1)-xaxis->GetBinLowEdge(i+1);
    xup[i] = xaxis->GetBinUpEdge(i+1)-xaxis->GetBinCenter(i+1);
    ylow[i] = hist->GetBinError(i+1);
    yup[i] = hist->GetBinError(i+1);
    if(YErrorZero){
      ylow[i] = 0;
      yup[i] = 0;
    }
    //ylow[i] = 0;
    //yup[i] = 0;
    //cout << "x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}


TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);
    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}

TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left, int n_x_shift, int i_x_shift){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);

    double dx = (xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left))/double(n_x_shift+1);
    x[i-1] = xaxis->GetBinLowEdge(i+n_skip_x_left) + double(i_x_shift+1) * dx;
    xlow[i-1] = double(i_x_shift+1) * dx;
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-x[i-1];

    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}


TGraphAsymmErrors* GraphSubtract(TGraphAsymmErrors *a, TGraphAsymmErrors *b, bool Rel){

  //==== do a-b

  int NX = a->GetN();
  TGraphAsymmErrors* gr_out = (TGraphAsymmErrors*)a->Clone();

  for(int i=0; i<NX; i++){

    double a_x, a_y, b_x, b_y;

    a->GetPoint(i, a_x, a_y);
    b->GetPoint(i, b_x, b_y);

    if(Rel==true){
      gr_out->SetPoint( i, a_x, (a_y-b_y)/b_y );
    }
    else{
      gr_out->SetPoint( i, a_x, a_y-b_y );
    }

  }

  return gr_out;

}

void RemoveLargeError(TGraphAsymmErrors *a){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if(y+yerr_high==1.){
      a->SetPointEYhigh( i, yerr_low );
    }

  }

}

void ScaleGraph(TGraphAsymmErrors *a, double c){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    a->SetPoint(i, x, c*y);
    a->SetPointEYlow(i, c*yerr_low);
    a->SetPointEYhigh(i, c*yerr_high);

  }

}



double GetMaximum(TH1D* hist){

  TAxis *xaxis = hist->GetXaxis();

  double maxval(-1.);
  for(int i=1; i<=xaxis->GetNbins(); i++){
    if( hist->GetBinContent(i) + hist->GetBinError(i) > maxval ){
      maxval = hist->GetBinContent(i) + hist->GetBinError(i);
    }
  }

  return maxval;

}

double GetMaximum(TGraphAsymmErrors *a){

  int NX = a->GetN();

  double maxval(-9999.);
  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if( y+yerr_high > maxval ){
      maxval = y+yerr_high;
    }

  }

  return maxval;

}

double GetYieldSystematics(TH1D *hist){

  int n_syst = hist->GetXaxis()->GetNbins();
  int n_source = (n_syst-1)/2;

  //==== Bin index
  //==== i=1 : central
  //==== i=2 : _MuonEn_up
  //==== i=3 : _MuonEn_down
  //==== -> n_syst = 3
  //==== -> n_source = (n_syst-1)/2 = (3-1)/2 = 1

  double y_central = hist->GetBinContent(1);

  double sum_syst = 0.;
  for(int i=1; i<=n_source; i++){
    double yield_up = hist->GetBinContent(i*2);
    double yield_down = hist->GetBinContent(i*2+1);

    double syst_up = fabs(yield_up-y_central);
    double syst_down = fabs(yield_down-y_central);

    sum_syst += 0.5*(syst_up*syst_up+syst_down*syst_down);

  }

  return sqrt(sum_syst);

}

TDirectory *MakeTemporaryDirectory(){

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}

void AddPhantomZero(double a, TString align, int digit_int, int digit_frac){

  if(align=="r"){
    int number_maxdigit = 0;
    for(int i=10; i>=0; i--){
      if(a/pow(10,i)>=1.){
        number_maxdigit = i;
        break;
      }
    }
    //cout << "number_maxdigit = " << number_maxdigit << endl;
    for(int i=0; i<digit_int-(number_maxdigit+1); i++) cout << "\\phantom{0}";
    cout << std::fixed<<std::setprecision(digit_frac) << a;
  }

  else if(align=="l"){
    int target_total_digit = digit_int+digit_frac;
    int number_maxdigit = 0;
    for(int i=10; i>=0; i--){
      if(a/pow(10,i)>=1.){
        number_maxdigit = i;
        break;
      }
    }
    //cout << "target_total_digit = " << target_total_digit << endl;
    //cout << "number_maxdigit = " << number_maxdigit << endl;
    //cout << "--> # of \\phantom{0} = " << target_total_digit-digit_int-(number_maxdigit+1) << endl;

    cout << std::fixed<<std::setprecision(digit_frac) << a;
    for(int i=0; i<target_total_digit-(number_maxdigit+1)-digit_frac; i++) cout << "\\phantom{0}";
  }

}




#endif
