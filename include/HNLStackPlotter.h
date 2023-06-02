#ifndef HNLStackPlotter_h
#define HNLStackPlotter_h

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

class HNLStackPlotter{
public:
  //==== constructors
  HNLStackPlotter(TString macroname);
  ~HNLStackPlotter();

  enum SetupHelper{
    NoLOGY=100,
    LOGY=101,
    NoDrawRatio=102,
    DrawRatio=103,
  };
  
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
  vector<double> GetRebinVariableBins();
  void MakeRebins();
  void MakeYAxis();
  void MakeXAxis();
  AnalysisInputs analysisInputs;
  //void SetMCSF(TString filepath);
  //void SetCalculatedSysts(TString filepath);

  //==== functions for drawing
  void DrawStackPlots();
  void DrawStackPlotsWithData();
  void DrawComparisonPlots();
  void draw_hist();
  void draw_comphist();
  void make_cutflow(TString Hist_For_CutFlow="NEvents");
  TString find_MCsector();
  void clear_legend_info();
  double coupling_constant(int mass);
  void fill_legend(TLegend *lg, TH1D *hist);
  void draw_legend(TLegend *lg, bool DrawData);
  void draw_canvas(THStack *mc_stack, TH1D *mc_staterror, TH1D *mc_allerror, TH1D *hist_data, vector<TH1D *> hist_signal, TLegend *legend, bool DrawData, TFile *outputf);
  void draw_comp_canvas(TH1D *hist_def, TH1D *hist_comp, TLegend *legend ,TFile *outputf);


  void AddHist(TString hn, TString htype, TString hunit,  vector<double> rb, double Xmin, double Xmax, double Ymax=1000000.);
  void SetupDefaultHist(TString sample, TString hn, TString histtag, TString legendname, TString htype, TString hunit,  vector<double> rb, double Xmin, double Xmax, double Ymax=1000000.);
  void SetupComparisonHist(TString sample, TString hist, TString histtag,TString legendname );
  TH1D* MakeHist(TString filepath, TString fullhistname);
  void Summary();
  TString FixLatex(TString origSt);

  int n_rebin();
  double y_max();
  void SetXaxisRange(TH1D* hist);
  void SetXaxisRange(THStack* mc_stack);
  void SetXaxisRangeBoth(THStack* mc_stack, TH1D* hist);
  TH1D* MakeOverflowBin(TH1D* hist);
  TString DoubleToString(double dx);

  void SetupPlotter();
  void SetupPlotter(TString era, TString skim, TString Analyzer);

  void mkdir(TString path);
  void make_plot_directory();
  TString legend_coupling_label(int mass);

  double GetHistValue(TH1D * ht, TString hn);
  double GetHistError(TH1D * ht, TString hn);
  void MakeTexFile(map< TString, TH1D * > hs, TString Hist_For_CutFlow);

  inline void SetSkim(TString skimname) { SkimName=skimname; }
  inline void SetAnalyser(TString anname) { AnalyserName=anname; }
  inline void SetMacroName(TString macname) { MacroName=macname; }
  inline void SetEra(TString eraname) { Era=eraname; }

  void BasicSetup(SetupHelper logy, SetupHelper ratio, TString channel);
  
  //==== variables
  bool DoDebug;
  bool comp_default_set;
  unsigned int i_cut, i_var, i_file;
  TString infilepath, filename_prefix, filename_suffix, data_class, plotpath, thiscut_plotpath, def_infilepath, def_histpath;
  vector<TString> HistPath, bkglist, samples_to_use, HistNames, x_title, units, PrimaryDataset, FullHistNames,SamplePaths, LegendNames;
  vector<int> Xmins,Xmaxs,Ymaxs;
  vector<vector<double> > Rebins;
  vector<bool> drawdata, ApplyMCNormSF, drawratio;
  vector<TString> CutFlowResults, HistResults;
  vector<TString> LxplusCutFlowResults, LxplusHistResults;

  //==== channel type
  vector<int> LeptonChannels;
  vector<TString> RegionType;
  TString GetStringChannel(int A);
  TString GetStringRegion(TString B);
  TString GetStringChannelRegion(int A, TString B);

  TString GetTitleByType(TString htype );
  void UseLogyAll(double b);
  void DrawRatioAll( bool b);
  void DrawDataAll( bool b);
  void ApplyMCNormSFAll(bool v);

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
  map< TString, vector<double> > temp_vrebins;
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
  bool MergeZeroBins;
  bool VarBins;
  bool CopyToWebsite;
};
#endif
