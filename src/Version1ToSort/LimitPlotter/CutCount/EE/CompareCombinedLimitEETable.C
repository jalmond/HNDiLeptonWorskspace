#include "Macros.h"
#include "base_functions.h"
#include "mylib.h"
#include "canvas_margin.h"
#include <math.h>

//==== ReturnWhat = 0 : Obs
//==== ReturnWhat = 1 : Exp
//==== ReturnWhat = 2 : +- 1sd
//==== ReturnWhat = 3 : +- 2sd

void MakeTexFile(map<TString, map< TString, double > > hs, TString outp,TString SR);

TGraphAsymmErrors*  GetTGraph(std::map<double,double> map1, std::map<double,double> map2, int i );

std::map<double,double> GetMap(TString input_path, int nbins, int i);
std::map<TString,double>  GetMapString(TString input_path, int nbins, int i);

void CompareCombinedLimitEETable(int j=0, TString dirname="", int ReturnWhat=0, bool RunFullCLs=true){

  bool DrawObserved = false;

  setTDRStyle();

  //gStyle->SetOptStat(0);
  
  TString WORKING_DIR =   getenv("HNDILEPTONWORKSPACE_DIR");  
  TString version = getenv("FLATVERSION");
  TString dataset = "";//getenv("CATANVERSION");
  TString ENV_FILE_PATH = WORKING_DIR;
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limits/ReadLimits/out/HNTypeI_Dilepton/CutCount/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limits/";

  if(dirname!=""){
  
    filepath = ENV_FILE_PATH+dataset+"Limit/"+dirname+"/";
    }

  TString WhichYear = "2016";
  if (j==1) WhichYear = "2017";
  if (j==2) WhichYear = "2018";
  if (j==3) WhichYear = "CombinedYears";

  
  TString WhichDirectoryInCutop = "EE_SR1_SR2";
  filepath = filepath + WhichYear + "/"+ WhichDirectoryInCutop;


  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  

  std::map<TString, std::map<TString,double> > FillMap;
  /*
passTightID,HNTight2016,passTightID_nocc,HNTightV1,HNTightV2,HNTightV3,HNMediumV1,HNMediumV2,HNMediumV3,passMediumID,passMVAID_noIso_WP80,passMVAI\
D_noIso_WP90,passMVAID_iso_WP80,passMVAID_iso_WP90
   */
  
  FillMap["passTightID"] = GetMapString(filepath+ "/result_VBF_passTightID.txt", 13,1);
  FillMap["HNTight2016"] = GetMapString(filepath+ "/result_VBF_HNTight2016.txt", 13,1);
  FillMap["passTightID_nocc"] = GetMapString(filepath+ "/result_VBF_passTightID_nocc.txt", 13,1);
  FillMap["HNTightV1"] = GetMapString(filepath+ "/result_VBF_HNTightV1.txt", 13,1);
  FillMap["HNTightV2"] = GetMapString(filepath+ "/result_VBF_HNTightV2.txt", 13,1);
  FillMap["HNTightV3"] = GetMapString(filepath+ "/result_VBF_HNTightV3.txt", 13,1);
  FillMap["HNMediumV1"] = GetMapString(filepath+ "/result_VBF_HNMediumV1.txt", 13,1);
  FillMap["HNMediumV2"] = GetMapString(filepath+ "/result_VBF_HNMediumV2.txt", 13,1);

  FillMap["HNMediumV3"] = GetMapString(filepath+ "/result_VBF_HNMediumV3.txt", 13,1);
  FillMap["passMediumID"] = GetMapString(filepath+ "/result_VBF_passMediumID.txt", 13,1);
  FillMap["passMVAID_noIso_WP80"] = GetMapString(filepath+ "/result_VBF_passMVAID_noIso_WP80.txt", 13,1);
  FillMap["passMVAID_noIso_WP90"] = GetMapString(filepath+ "/result_VBF_passMVAID_noIso_WP90.txt", 13,1);
  FillMap["passMVAID_iso_WP80"] = GetMapString(filepath+ "/result_VBF_passMVAID_iso_WP80.txt", 13,1);
  FillMap["passMVAID_iso_WP90"] = GetMapString(filepath+ "/result_VBF_passMVAID_iso_WP90.txt", 13,1);
  

  TString output="";
  MakeTexFile(FillMap,output, WhichYear);

  return;
}



void MakeTexFile(map<TString, map< TString, double > > hs,TString output,TString year){

  TString texfilepath = output+"tex/";

  MakeDir(texfilepath);

  ofstream ofile_tex(texfilepath+"/Yields"+year+".tex",ios::trunc);
  ofile_tex.setf(ios::fixed,ios::floatfield);
  ofile_tex << "\\documentclass[10pt]{article}" << endl;
  ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl,lscape}" << endl;
  ofile_tex << "\\begin{document}" << endl;
  ofile_tex << "\\begin{landscape}" << endl;


  ofile_tex << "\\input{"+texfilepath+"/Table.txt}" << endl;
  ofile_tex << "\\end{landscape}" << endl;

  ofile_tex << "\\end{document}" << endl;

  ofstream ofile(texfilepath+"/Table.txt",ios::trunc);
  ofile.precision(3);
  ofile.setf(ios::fixed,ios::floatfield);
  ofile << "\\begin{table}[!tbh]" << endl;
  ofile << "  \\caption{" << endl;
  ofile << "    Number of events in "<< endl;
  ofile << "  }" << endl;
  ofile << "  \\begin{center}" << endl;
  TString latex_columns = "|c";
  vector<TString> masses = { "100","125","200","250","300","400","500","600","700","800","900","1000","1100","1200","1500","1700","2000"};
  for (auto i :  hs){
    latex_columns+="|c";
  }
  latex_columns+="|";



  ofile << "    \\begin{tabular}{"<< latex_columns.Data() <<"}" << endl;
  ofile << "\\hline" << endl;

  ofile << " Mass " ;
  int counter(1);
  for( auto i :  hs){
    ofile << "& ["<< counter  <<"]"  ;
    counter++;
  }
  ofile << "\\\\" << endl;  
  
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;

  vector<double> _totals;
  for(map<TString, map< TString, double > >::iterator mit = hs.begin(); mit != hs.end(); mit++){
    _totals.push_back(0);
	  
  }
  for (unsigned int i = 0 ; i < masses.size(); i++){

    ofile << masses[i] <<  " " ;


    double average;
    
    int i_id(0);

    for(map<TString, map< TString, double > >::iterator mit = hs.begin(); mit != hs.end(); mit++){
      map< TString, double >::iterator it  =  mit->second.find(masses[i]);
      if(it == mit->second.end()) return;
      average+=it->second ;
      i_id++;
    }
    average=average/double(i_id);
    

    int _counter(0);
    for(map<TString, map< TString, double > >::iterator mit = hs.begin(); mit != hs.end(); mit++){  
      map< TString, double >::iterator it  =  mit->second.find(masses[i]);
      if(it == mit->second.end()) return;
      ofile << " & " <<  it->second ;
      double tmp_tot=_totals[_counter];
      _totals[_counter]=tmp_tot+it->second/average;
      _counter++;
    }
    ofile << "\\\\" << endl;
  }
  ofile << "\\hline" << endl;

  //cout << "Total  ";
  for(unsigned int k=0; k < _totals.size(); k++){
    ofile << " & " << _totals[k] ;
  }
  ofile << " \\\\" << endl; 
  
  //    ofile << it->first << " & $" << it->second  <<"$ \\\\" << endl;
 
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "    \\end{tabular}" << endl;
  ofile << "  \\end{center}" << endl;
  ofile << "\\end{table}" << endl;
  counter =1;
  for( auto i :  hs){
    TString name = i.first ;
    name.ReplaceAll("_","\\_");
	
    ofile << "["<< counter << "]"<< name << "\n"<<  endl; 
    counter++;
  }
  system("latex "+texfilepath+"/Yields"+year+".tex");
  system("dvipdf Yields"+year+".dvi");
  system("rm *aux");
  system("rm *log");
  system("rm *dvi");
  system("mv Yields"+year+".pdf "+texfilepath);
 
}

std::map<TString,double>  GetMapString(TString filepath,int nbins, int i){

  std::map<double,double> _map = GetMap(filepath,nbins,i);
  std::map<TString,double> outmap;
  for (std::map<double,double>::iterator it = _map.begin(); it != _map.end(); it++){

    std::ostringstream strs;
    strs << it->first;
    std::string str = strs.str();

    outmap[TString(str)] = it->second;
    
  }
  return outmap;
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
    //    cout << "ell line = " << elline << endl;
    std::istringstream is( elline );
    is >> mass[dummyint];
    is >> obs[dummyint];
    is >> limit[dummyint];
    is >>onesig_left[dummyint];
    is >>onesig_right[dummyint];
    is >>twosig_left[dummyint];
    is >>twosig_right[dummyint];
    //cout << input_path << " " << mass[dummyint] << " " <<  limit[dummyint] << endl;

    //if (obs[dummyint] == "-")       _map[mass[dummyint]] = 0.;
    //if (obs[dummyint] == "--")       _map[mass[dummyint]] = 0.;
    
    if(obs[dummyint]<=0 || limit[dummyint]<=0 ){
      double mass_D = (double)((int)mass[dummyint]);

      _map[mass_D] = 0.;
    }
    else{

      double mass_D = (double)((int)mass[dummyint]);
      _map[mass_D] = limit[dummyint];
    }
  }

  return _map;


}
  
TGraphAsymmErrors*  GetTGraph(std::map<double,double> map1, std::map<double,double> map2, int i ){

  int n_central =   map1.size();

  int dummyint=0;
  
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];

  //  cout << "n_central = " <<n_central<<endl;
  int counter=0;
  vector<double> scale={0.1,0.1, 0.1, 1,1,1,1,1,10, 10, 10, 10, 100, 100, 100, 100, 100};
  for(std::map<double,double>::iterator it = map1.begin(); it != map1.end(); it++){

    double dmass = it->first;
    //cout << it->first << " " << it->second << endl;
    std::map<double,double>::iterator it2 = map2.find(dmass);
    double limit_r=1.;
    if (it2 != map2.end()) limit_r=it2->second * scale[dummyint]*0.01;
    
    mass[dummyint] = it->first;
    obs[dummyint] = limit_r;
    limit[dummyint] = limit_r;
    onesig_left[dummyint] = limit_r;
    onesig_right[dummyint] = limit_r;
    twosig_left[dummyint] = limit_r;
    twosig_right[dummyint] = limit_r;
    dummyint++;
    continue;
  }

  //  cout << "n_central = " << n_central << " mass size = " << mass << endl;
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
