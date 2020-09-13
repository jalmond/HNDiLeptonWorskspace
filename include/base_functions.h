#ifndef base_functions_h
#define base_functions_h

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>  
#include <iomanip>
#include "TString.h"
#include "TSystem.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TH1D.h"

//using namespace std;

int CheckFile(TFile* f){
  if (f->IsZombie()) return 1;
  if (f->TestBit(1024)) return 2;

  return 0;
}

TLegend* MakeLegend(double x1, double x2, double y1, double y2){

  TLegend *lg = new TLegend(x1, x2, y1, y2);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);

  return lg;
  
}



Color_t GetHistColor(int nth_samples){
  vector <Color_t > _colors;
  _colors.push_back(kRed);
  _colors.push_back(800);
  _colors.push_back(870);
  _colors.push_back(kSpring-1);
  _colors.push_back(kGray);
  _colors.push_back(kViolet);
  _colors.push_back(kYellow+4);

  if(nth_samples > _colors.size()) return _colors[0];
  return _colors[nth_samples];
  
}

vector<Color_t>  GetHistColors(int nsamples){
  
  vector<Color_t> _colors;
  for(unsigned int i = 0 ; i < nsamples; i++) _colors.push_back(GetHistColor(i));
  
  return _colors;
  
}
 
void MakeLatex(TString name, TString input , TString output ){

  TString ENV_FILE_PATH= getenv("OUTFILE_PATH");
  
  TString workdir = ENV_FILE_PATH+ "Latex/workspace/";
  TString texfile = ENV_FILE_PATH+ "Latex/workspace/"+name+".tex";
  TString dvifile = ENV_FILE_PATH+ "Latex/workspace/"+name+".dvi"; 
  TString pdffile = ENV_FILE_PATH+ "Latex/workspace/"+name+".pdf"; 

  //// Make TEX file
  ofstream ofile_tex;

  ofile_tex.open(texfile.Data());
  ofile_tex.setf(ios::fixed,ios::floatfield);
  ofile_tex << "\\documentclass[10pt]{article}" << endl;
  ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}" << endl;

  ofile_tex << "\\begin{document}" << endl;
  ofile_tex << "\\input{" + input << endl;
  ofile_tex << "\\end{document}" << endl;

  string latex_command = "latex " + texfile;
  string dvi_command = "dvipdf " + dvifile;
  string mv_command = "mv " + pdffile + " " + output;

  system((latex_command.c_str()));
  system((dvi_command.c_str()));
  system((mv_command.c_str()));
  system(("rm *aux"));
  system(("rm " + workdir + "/*aux"));
  system(("rm *log"));
  system(("rm " + workdir + "/*log"));
  system(("rm *dvi"));
  system(("rm " + workdir + "/*dvi"));

}

void AllLegendEntry(TLegend* leg, TGraphAsymmErrors* g, TString name, TString type){
    leg->AddEntry(g, name, type);
}
void AllLegendEntry(TLegend* leg, TH1* h, TString name, TString type){
  leg->AddEntry(h, name, type);

}
		    
const vector<string> _getsplit(const string& s, const char& c)
{
  string buff{""};
  vector<string> v;
  
  for(auto n:s)
    {
      if(n != c) buff+=n; else
	if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
  if(buff != "") v.push_back(buff);
  
  return v;
}


void           OutMessage(TString s_code, TString  s_file){
  cout << s_code << " : created file " << s_file << endl;
}

vector<TString> GetMassType1Strings(vector<TString> ignore_masses){

  //TString split_string = ignore_masses;
  //split_string= split_string.ReplaceAll("/"," ");
  TH1* h;
  //vector<TString> v//{_getsplit(string(split_string), ' ')};


  vector <TString> masses ;
  masses.push_back("100");
  masses.push_back("125");
  masses.push_back("200");
  masses.push_back("250");
  masses.push_back("300");
  masses.push_back("400");
  masses.push_back("500");
  masses.push_back("600");
  masses.push_back("700");
  masses.push_back("800");
  masses.push_back("900");
  masses.push_back("1000");
  masses.push_back("1100");
  masses.push_back("1200");
  masses.push_back("1500");
  vector <TString> _masses ;
  for(unsigned int i=0; i < masses.size(); i++){
    bool ignore=false;
    for(unsigned int j=0; j < ignore_masses.size(); j++){
      if(masses[i] == ignore_masses[j]) ignore=true;
    }
    if (!ignore) _masses.push_back(masses[i]);
  }
  return _masses;

}

double Stod(string word){

  double lol = atof(word.c_str());
  return lol;
}

vector<double> GetMassType1Doubles(vector<TString> ignore_masses){

  //TString split_string = ignore_masses;
  //split_string= split_string.ReplaceAll("/"," ");
  TH1* h;
  //vector<string> v{_getsplit(string(split_string), ' ')};
  
  
  vector <TString> masses ;
  masses.push_back("100");
  masses.push_back("125");
  masses.push_back("200");
  masses.push_back("250");
  masses.push_back("300");
  masses.push_back("400");
  masses.push_back("500");
  masses.push_back("600");
  masses.push_back("700");
  masses.push_back("800");
  masses.push_back("900");
  masses.push_back("1000");
  masses.push_back("1100");
  masses.push_back("1200");
  masses.push_back("1500");
  vector <double> _masses ;
  for(unsigned int i=0; i < masses.size(); i++){
    bool ignore=false;
    for(unsigned int j=0; j < ignore_masses.size(); j++){
      if(masses[i] == ignore_masses[j]) ignore=true;
    }
    if (!ignore) _masses.push_back(atof(masses[i]));
  }
  return _masses;

}

TString GetHostname(){
  char hostbuffer[256];
  int hostname = gethostname(hostbuffer, sizeof(hostbuffer));

  TString s_hostname = TString(hostname);
  return s_hostname;
}

void sMakeDir(const std::string &s)
{

  struct stat buffer;
  if( (stat (s.c_str(), &buffer) == 0)) return;
  gSystem->mkdir(TString(s));

}
void MakeDir(TString a){
  sMakeDir(string(a));
}

bool IsPathExist(const std::string &s)
{

  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}


#endif

