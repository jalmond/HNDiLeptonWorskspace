#ifndef HNLPlotter_h
#define HNLPlotter_h

#include "TSystem.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TString.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>
#include <vector>
#include <map>
#include "canvas_margin.h"
#include "AnalysisInputs.h"
#include "mylib.h"

using namespace std;

class HNLPlotter{
public:
  //==== constructors
  HNLPlotter(TString macroname);
  ~HNLPlotter();

  enum signal_class{
    no_class = -1,
    SR1 = 10,
    SR2 = 11,
    SR3 = 12,
    BDTSR3 = 13,
    
  };
  vector<signal_class> AllSignalClasses;
  signal_class CurrentSC;
  
  //==== functions for setting
  void make_bkglist();
  void SetRebins(TString filepath);
  void SetYAxis(TString filepath);
  void SetXAxis(TString filepath);
  void MakeRebins();
  void MakeYAxis();
  void MakeXAxis();
  AnalysisInputs analysisInputs;
  //void SetMCSF(TString filepath);
  //void SetCalculatedSysts(TString filepath);

  //==== functions for drawing
  void draw_hist();
  TString find_MCsector();
  void clear_legend_info();
  double coupling_constant(int mass);
  void fill_legend(TLegend *lg, TH1D *hist);
  void draw_legend(TLegend *lg, bool DrawData);
  void draw_canvas(THStack *mc_stack, TH1D *mc_staterror, TH1D *mc_allerror, TH1D *hist_data, vector<TH1D *> hist_signal, TLegend *legend, bool DrawData, TFile *outputf);

  int n_rebin();
  double y_max();
  void SetXaxisRange(TH1D* hist);
  void SetXaxisRange(THStack* mc_stack);
  void SetXaxisRangeBoth(THStack* mc_stack, TH1D* hist);
  TH1D* MakeOverflowBin(TH1D* hist);
  TString DoubleToString(double dx);

  void SetupPlotter();

  void mkdir(TString path);
  void make_plot_directory();
  TString legend_coupling_label(int mass);

  void MakeTexFile(map< TString, TH1D * > hs);

  inline void SetSkim(TString skimname) { SkimName=skimname; }
  inline void SetAnalyser(TString anname) { AnalyserName=anname; }
  inline void SetMacroName(TString macname) { MacroName=macname; }
  inline void SetEra(TString eraname) { Era=eraname; }

  
  //==== variables
  bool DoDebug;
  unsigned int i_cut, i_var, i_file;
  TString infilepath, filename_prefix, filename_suffix, data_class, plotpath, thiscut_plotpath;
  vector<TString> HistPath, bkglist, samples_to_use, histname, x_title, units, PrimaryDataset;
  vector<int> Rebins,Xmins,Xmaxs,Ymaxs;
  vector<bool> drawdata, ApplyMCNormSF, drawratio;

  //==== channel type
  vector<int> LeptonChannels;
  vector<TString> RegionType;
  TString GetStringChannel(int A);
  TString GetStringRegion(TString B);
  TString GetStringChannelRegion(int A, TString B);

  void UseLogyAll(double b);
  void DrawRatioAll( bool b);
  void DrawDataAll( bool b);


  vector<double> UseLogy;
  //map<TString, double> MCNormSF, MCNormSF_uncert, CalculatedSysts;
  vector< pair<TString, TString> > CutVarSkips;
  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> signal_survive_mass;
  vector<int> MCsector_first_index;
  vector<int> signal_mass;
  vector<bool > signal_draw;
  map< signal_class, vector<int> > map_class_to_signal_mass;
  vector<Color_t> signal_color;
  map< pair<TString, int>, double > coupling_constants;
  map<TString, bool> MCsector_survive;
  TH1D *hist_for_legend_data;
  vector<TH1D*> hist_for_legend_bkg;
  vector<TH1D*> hist_for_legend_signal;

  TString path_rebins, path_y_axis, path_x_axis;

  void SetupSampleInfo();
  void LeptonChannel(TString ch);

  map< TString, int > temp_rebins;
  map< TString, double > temp_y_maxs, temp_x_mins, temp_x_maxs;

  double default_y_max = 1000, default_y_min = 0.;
  double k_factor;
  double log_of_generation_mixing;

  bool ZeroDataCheckCut(double xlow, double xhigh);
  vector<double> GetRebinZeroBackground(THStack *mc_stack, TH1D *mc_staterror, TH1D *mc_allerror, TH1D *hist_data, vector<TH1D *> &hist_signal);

  TString SkimName;
  TString MacroName;
  TString AnalyserName;
  TString Era;
  bool MakePaperPlot;

};
#endif
