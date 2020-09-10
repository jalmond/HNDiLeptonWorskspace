#ifndef mylib_h
#define mylib_h

void SetBinLabels(TH1D* hist, std::vector<TString> list){

  for(unsigned int i = 0 ; i < list.size(); ++i){
    
    TString im = list.at(i);
    hist->GetXaxis()->SetBinLabel(i+1,im);
    
  }
  
  return;
           
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

void FormatHist(TH1* h , bool fill, Color_t t){

  if(fill){
    h->SetFillColor(t);
  }
  h->SetLineColor(t);
  h->SetMarkerColor(t);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.6);
  h->SetLineWidth(10);
  
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
    cout << "File " << file->GetName() << " missing directory " << name << endl;

    TIter next2(list) ;
    TKey* key2 ;
    TObject* obj2 ;
    
    while ( (key2 = (TKey*)next2()) ) {
        obj2 = key2->ReadObj() ;
        TString hname2 = obj2->GetName();
        TString objname2= obj2->ClassName();
        cout << "Possible directory names are " << hname2 << endl;

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

TH1* GetHist(TFile* file, TString name , bool debug=false){
  
  TString name_fix = name;
  name_fix = name_fix.ReplaceAll("/"," ");
  TH1* h;
  vector<string> v{_getsplit(string(name_fix), ' ')};
  TList* list ;
  if(v.size() == 2){
    if(FileHasDir(file, TString(v[0])))list = file->GetDirectory(TString(v[0]))->GetListOfKeys() ;
    //name= v[1];
    else return h;
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
	if(debug)cout << "Possible hist names are " << hname << endl;
	
      }
      return h;
    }
  }
  h =   (TH1F*)file->Get(name);
  
  return h;
  
  
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
