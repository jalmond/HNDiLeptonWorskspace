#include "Plotter.cc"
#include <fstream>

void Draw_CR(int Year=2016, int WhichRegion=0, bool ScaleMC=false){

  bool UsePromptMC = false;

  //==============
  //==== get env
  //==============
  
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("SKANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  //====================
  //==== decalre class
  //====================
  
  Plotter m;
  m.DoDebug = false;
  m.DataYear = Year;
  
  //=====================
  //==== set data class
  //=====================

  TString str_Year = TString::Itoa(Year,10);
  m.data_class = dataset+"/Regions/"+str_Year+"/";
  if(Year<0){
    str_Year = "YearCombined";
    m.data_class = dataset+"/Regions/";
  }

  //================================
  //==== set prefixes and suffixes
  //================================
  
  m.filename_prefix = "HNtypeI_Dilepton";
  m.filename_suffix = ".root";
  m.filename_skim = "_SkimTree_HNMultiLep";

  //=========================
  //==== set sample mapping
  //=========================

  if(Year==2016){

      m.map_sample_string_to_list["DY"] = {"DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets_MG"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_mll0p1_powheg",
    "ZZTo4L_powheg", "ggZZto4e", "ggZZto4mu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ_pythia", "ZZ_pythia", "WW_pythia"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_mll0p1_powheg"};
  m.map_sample_string_to_list["WZ_excl2"] = {"WZTo3LNu_amcatnlo"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_m_1toInf_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["ZZ_excl2"] = {"ZZTo4L_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTLL_powheg","TTLJ_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttWToLNu", "ttWToQQ","ttZToLLNuNu","ttZToQQ"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["Xgamma"] = {"ZGTo2LG_01J", "WGToLNuG"};
  m.map_sample_string_to_list["Xgamma2"] = {"ZGTo2LG_01J", "WGToLNuG_MG"};
  m.map_sample_string_to_list["Xgamma_noDY"] = {"WGToLNuG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["WW_double2"] = {"SSWW"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLLNuNu"};
  //m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};


  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["WZ_excl2"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["ZZ_excl2"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma2"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma_noDY"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["WW_double2"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);


  }
  else if(Year==2017){

  m.map_sample_string_to_list["DY"] = {"DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets_MG"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_mll0p1_powheg",
    "ZZTo4L_powheg", "ggZZto4e", "ggZZto4mu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ_pythia", "ZZ_pythia", "WW_pythia"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_mll0p1_powheg"};
  m.map_sample_string_to_list["WZ_excl2"] = {"WZTo3LNu_amcatnlo"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_m_1toInf_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["ZZ_excl2"] = {"ZZTo4L_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTLL_powheg","TTLJ_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttWToLNu", "ttWToQQ","ttZToLLNuNu","ttZToQQ"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["Xgamma"] = {"ZGTo2LG_01J", "WGToLNuG"};
  m.map_sample_string_to_list["Xgamma2"] = {"ZGTo2LG_01J", "WGToLNuG_MG"};
  m.map_sample_string_to_list["Xgamma_noDY"] = {"WGToLNuG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["WW_double2"] = {"SSWW"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLLNuNu"};
  //m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};


  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["WZ_excl2"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["ZZ_excl2"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma2"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma_noDY"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["WW_double2"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);


  }
  else if(Year==2018){

  m.map_sample_string_to_list["DY"] = {"DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets_MG"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_mll0p1_powheg",
    "ZZTo4L_powheg", "ggZZto4e", "ggZZto4mu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ_pythia", "ZZ_pythia", "WW_pythia"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_mll0p1_powheg"};
  m.map_sample_string_to_list["WZ_excl2"] = {"WZTo3LNu_amcatnlo"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_m_1toInf_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["ZZ_excl2"] = {"ZZTo4L_powheg",  "ggZZto4e", "ggZZto4mu"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTLL_powheg","TTLJ_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttWToLNu", "ttWToQQ","ttZToLLNuNu","ttZToQQ"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["Xgamma"] = {"ZGTo2LG_01J", "WGToLNuG"};
  m.map_sample_string_to_list["Xgamma2"] = {"ZGTo2LG_01J", "WGToLNuG_MG"};
  m.map_sample_string_to_list["Xgamma_noDY"] = {"WGToLNuG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["WW_double2"] = {"SSWW"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLLNuNu"};
  //m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};


  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["WZ_excl2"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["ZZ_excl2"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma2"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma_noDY"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["WW_double2"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);


  }
  else if(Year<0){

    m.map_sample_string_to_list["ZJets_MG_HT"]  = {
      "2016 DYJets10to50_MG", "2016 DYJets_MG_HT",
      "2017 DYJets10to50_MG", "2017 DYJets_MG_HT",
      "2018 DYJets10to50_MG", "2018 DYJets_MG_HT",
    };
    m.map_sample_string_to_list["ZJets_MG_HT_Reweighted"]  = {
      "2016 DYJets10to50_MG_Reweighted", "2016 DYJets_MG_HT_Reweighted",
      "2017 DYJets10to50_MG_Reweighted", "2017 DYJets_MG_HT_Reweighted",
      "2018 DYJets10to50_MG_Reweighted", "2018 DYJets_MG_HT_Reweighted",
    };
    m.map_sample_string_to_list["WJets_MG_HT"] = {
      "2016 WJets_MG_HT",
      "2017 WJets_MG_HT",
      "2018 WJets_MG_HT",
    };
    m.map_sample_string_to_list["VV_incl"] = {
      "2016 VV",
      "2017 VV",
      "2018 VV",
    };
    m.map_sample_string_to_list["VVV"] = {
      "2016 VVV",
      "2017 VVV",
      "2018 VVV",
    };
    m.map_sample_string_to_list["Multiboson"] = {
      "2016 VV",
      "2017 VV",
      "2018 VV",
      "2016 VVV",
      "2017 VVV",
      "2018 VVV",
    };
    m.map_sample_string_to_list["SingleTop"] = {
      "2016 SingleTop",
      "2017 SingleTop",
      "2018 SingleTop",
    };
    m.map_sample_string_to_list["ttX"] = {
      "2016 ttX",
      "2017 ttX",
      "2018 ttX",
    };
    m.map_sample_string_to_list["ttbar"] = {
      "2016 TTLL_powheg", "2016 TTLJ_powheg",
      "2017 TTLL_powheg", "2017 TTLJ_powheg",
      "2018 TTLL_powheg", "2018 TTLJ_powheg",
    };
    m.map_sample_string_to_list["EMuMethod"]     = {
      "2016 EMuMethod_LowWRCR_TTLX_powheg",
      "2017 EMuMethod_LowWRCR_TTLX_powheg",
      "2018 EMuMethod_LowWRCR_TTLX_powheg",
    };

    m.map_sample_string_to_legendinfo["ZJets_MG_HT"] = make_pair("Z+Jets", kYellow);
    m.map_sample_string_to_legendinfo["ZJets_MG_HT_Reweighted"] = make_pair("Z+Jets", kYellow);
    m.map_sample_string_to_legendinfo["WJets_MG_HT"] = make_pair("W+Jets", 870);
    m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
    m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kMagenta);
    m.map_sample_string_to_legendinfo["Multiboson"] = make_pair("Multiboson", kSpring-1);
    m.map_sample_string_to_legendinfo["SingleTop"] = make_pair("Single top", kRed+2);
    m.map_sample_string_to_legendinfo["ttX"] = make_pair("ttV", kOrange+2);
    m.map_sample_string_to_legendinfo["EMuMethod"] = make_pair("t#bar{t}", kRed);
    m.map_sample_string_to_legendinfo["ttbar"] = make_pair("t#bar{t}", kRed);

  }

  //===============================
  //==== set and make sample list
  //===============================

  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>

  //==== DY CR, log scale
  if(WhichRegion==0){

    m.samples_to_use = {"VV_incl", "DY","Xgamma", "VVV", "top", "WW_double","ttbar"};

    m.histname_suffix = {

      "HNL_ZZ_FourLepton_CR_DiElectron_HN2018"


    };

  }

  //==== EMu
  if(WhichRegion==1){

    m.samples_to_use = {"Multiboson", "ttX", "SingleTop", "WJets_MG_HT", "ZJets_MG_HT", "ttbar"};

    m.histname_suffix = {

      //==== Resolved EMu
      "HNWR_EMu_Resolved_SR",

      //==== Boosted EMu
      "HNWR_SingleElectron_EMu_Boosted_CR",
      "HNWR_SingleMuon_EMu_Boosted_CR",

      //==== Resolved EMu, but DYCR. This is dominated by ttbar, so it is here..
      //==== This region is not important
      "HNWR_EMu_Resolved_DYCR",

      //==== LowWRCR emu regions
      "HNWR_EMu_Resolved_LowWRCR",
      "HNWR_SingleElectron_EMu_Boosted_LowWRCR",
      "HNWR_SingleMuon_EMu_Boosted_LowWRCR",

    };

  }

  //==== EMu Validation (i.e., LowWR)
  if(WhichRegion==2){

    m.samples_to_use = {"WJets_MG_HT", "Multiboson", "ttX", "SingleTop", "ZJets_MG_HT", "ttbar"};

    m.histname_suffix = {

      //==== Resolved LowWRCR for validation
      "HNWR_SingleElectron_Resolved_LowWRCR",
      "HNWR_SingleMuon_Resolved_LowWRCR",

      //==== Boosted LowWRCR for validation
      "HNWR_SingleElectron_Boosted_LowWRCR",
      "HNWR_SingleMuon_Boosted_LowWRCR",

    };

  }

  //============================
  //==== set variables to draw
  //============================

  m.histname = {
    //"NEvent", "nPileUp", "nPV", "N_VTX",
		"met", "ht","lep1_pt","nPV"
  };

  m.x_title = {
    //"# of events", "# of PU", "# of PV", "# of vtx",
	       //"Leading lepton p_{T} (GeV)",// "Leading lepton #eta", "Leading lepton TrkRelIso",
	       ///"Subleading lepton p_{T} (GeV)", "Subleading lepton #eta", "Subleading lepton TrkRelIso",
	       //"#DeltaR(l_{1},l_{2})",
	       //"Leading jet p_{T} (GeV)", "Leading jet #eta",
	       //"Subleading jet p_{T} (GeV)", "Subleading jet #eta",
	       //"Away AK8 jet p_{T} (GeV)", "Away AK8 jet #eta", "Away AK8 jet Mass", "Away AK8 jet SFMass",
	       //"p_{T} of dilepton (GeV)", "m(ll) (GeV)", "#DeltaR(ll)",
    "#slash{E}_{T}^{miss} (GeV)", "H_{T} (GeV)",  "Leading lepton p_{T} (GeV)", "# of PV"
//    "m_{T} (GeV)",
//    "# of jets", "# of b-tagged jets",
 //   "m_{N} (GeV)", "m_{W_{R}} (GeV)",
  //  "p_{T} of N (GeV)", "p_{T} of W (GeV)",
   // "# of merged jets",
  };

  m.units = {
    //"int", "int", "int", "int",
    "GeV", "GeV", "GeV", "int"

  };



  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    TString this_region = m.histname_suffix.at(i);
    //==== PD
    if(this_region.Contains("Electron")){
      m.PrimaryDataset.push_back("Electron");
    }
    else if(this_region.Contains("Muon")){
      m.PrimaryDataset.push_back("Muon");
    }
    else if(this_region.Contains("EMu")){
      m.PrimaryDataset.push_back("SingleMuon");
    }
    else{
      cout << "ERROR : PD not correct" << endl;
      return;
    }

    if(this_region.Contains("HNL_ZZ_FourLepton_CR_DiElectron")){
      m.LeptonChannels.push_back(41);
      m.RegionType.push_back(20);
    }


    else{
      cout << "Wrong region = " << this_region << endl;
      return;
    }

    //==== Log plot boolean
    if(WhichRegion==0) m.UseLogy.push_back(1);
    if(WhichRegion==1){
      m.UseLogy.push_back(1);
    }
    if(WhichRegion==2) m.UseLogy.push_back(-1);
    if(WhichRegion==3) m.UseLogy.push_back(1);

    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);

    m.drawdata.push_back(true);

    m.drawratio.push_back(true);

  }


/*
  //==== FIXME test
  m.histname = {"m_lljj_lljjWclosest", "m_llj"};
  m.x_title = {"m(l^{#pm}l^{#pm}W_{jet}) (GeV)", "m(l^{#pm}l^{#pm}W_{jet}) (GeV)"};
  m.units = {"GeV", "GeV"};
*/

  cout << "m.histname.size() = " <<  m.histname.size() << endl;
  cout << "m.x_title.size() = " << m.x_title.size() << endl;
  cout << "m.units.size() = " << m.units.size() << endl;
  if(m.histname.size()==m.x_title.size() && m.x_title.size()==m.units.size()){
    cout << "--> OKAY" << endl;
  }
  else{
    cout << "--> WRONG" << endl;
    return;
  }
  cout << "Histname\tXTitle\tUnit" << endl;
  for(unsigned int i=0; i<m.histname.size(); i++){
    cout << m.histname.at(i) << "\t" << m.x_title.at(i) << "\t" << m.units.at(i) << endl;
  }

  //====================
  //==== make bkg list
  //====================

  m.make_bkglist();

  //=====================
  //==== Fill MCNorm SF
  //=====================

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/"+str_Year+"/MCSF.txt", m.bkglist);

  //======================
  //==== Get Systematics
  //======================

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/"+str_Year+"/Syst.txt");
  m.Systs = {
    "JetRes",
    "JetEn",
    "MuonRecoSF",
    "MuonEn",
    "MuonIDSF",
    "MuonISOSF",
    "MuonTriggerSF",
    "ElectronRecoSF",
    "ElectronRes",
    "ElectronEn",
    "ElectronIDSF",
    "ElectronTriggerSF",
    "LSFSF",
    "PU",
    "ZPtRw",
    "Prefire",
  };

  //=============
  //==== rebins
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_rebins("./data/tmp_CR_rebins.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_rebins
      //<< "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_rebins.close();

  m.SetRebins(WORKING_DIR+"/data/"+dataset+"/"+str_Year+"/CR_rebins.txt");

  //=============
  //==== y_maxs
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_y_maxs("./data/tmp_CR_yaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_y_maxs
      //<< "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_y_maxs.close();


  //==== default max
  m.default_y_max = 20.;
  m.default_y_min = 0.;

  m.SetYAxis(WORKING_DIR+"/data/"+dataset+"/"+str_Year+"/CR_yaxis.txt"); 

  //=============
  //==== x_mins
  //=============

  //==== script to generate rebins
  ofstream skeleton_x_mins("./data/tmp_CR_xaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_x_mins
      //<< "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<"\t"<<-999<<endl;
    }
  }
  skeleton_x_mins.close();

  m.SetXAxis(WORKING_DIR+"/data/"+dataset+"/"+str_Year+"/CR_xaxis.txt");

  //===============
  //==== k-factor
  //===============
  
  m.k_factor = 1;
  
  //=================================
  //==== mixing at generation level
  //=================================
  
  m.log_of_generation_mixing = 1.;
  
  //===============================
  //==== prepare plot directories
  //===============================

  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/FromCPP_CR/"+str_Year+"/";

  if(UsePromptMC) m.plotpath += "/UsePromptMC/";

  m.make_plot_directory();

  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






