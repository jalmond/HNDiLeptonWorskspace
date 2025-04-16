#include "HNLPlotter.h"
#include <stdlib.h>

HNLPlotter::HNLPlotter(TString macroname){

  VERBOSE=false;
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  setTDRStyle();


  DateFileTag="";
  RunScan=false;
  RatioRange=1.5;
  DrawSmallLegend=false;
  DrawRatioLegend= true;

  ////// Setup Plotting para
  LatexTextLabel_Size=0.02;
  LatexTextLabel_X=0.2;   LatexTextLabel_Y=0.88;
  LatexTextCMS_Size=0.035;
  LatexTextCMS_X=0.15;  LatexTextCMS_Y=0.96;
  LatexTextCMS="#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}";
  LatexTextCMSSimulation="#font[62]{CMS} #font[42]{#it{#scale[0.8]{Simulation}}}";
  
  Legend_X1=0.65;
  Legend_X2=0.9;
  Legend_Y1=0.75;
  Legend_Y2=0.85;
  Legend_Size=0.03;

  Canvas_X=1000;  Canvas_Y=800;

  XAxisTitle="";  YAxisTitle="";
  Hist_YAxis_MaxScale=1.4;

  default_y_max=-1;

  ////Hist options

  XaxisMin=-999;  XaxisMax=-999;
  RebinX= 1;
  Normalise = -1.;

  SetLogY=false;
  SetLabels=false;
  gStyle->SetOptStat(0);
  DoDebug = false;
  gErrorIgnoreLevel = kError;

  AnalyserName="HNL_Validation";                                                                                                    
  MacroName=macroname;
  Era="2017";
  filename_prefix=AnalyserName;
  filename_suffix=".root";

  infilepath="./";
  def_infilepath="./";
  def_histpath="";

  MakePaperPlot = false;  

  //// clear vecs
  RegionType.clear();
  LeptonChannels.clear();
  HistPath.clear();
  ApplyMCNormSF.clear();
  HistNames.clear();
  LegendNames.clear();
  HistResults.clear();
  map_sample_string_to_scale.clear();

  log_of_generation_mixing=0;
  VarBins=false;
  MergeZeroBins= false;
  CopyToWebsite=true;
  comp_default_set=false;
}



void HNLPlotter::DrawStackPlots(){
  DrawDataAll(false);
  make_bkglist();
  draw_hist();
  return;
}


void HNLPlotter::DrawStackPlotsWithData(){

  DrawDataAll(true);
  make_bkglist();
  draw_hist();
  return;
}



void HNLPlotter::SetupDefaultHist(TString sample, TString hn, TString histtag, TString legend, TString htype, TString hunit, vector<double> rb, double Xmin, double Xmax, double Ymax){
  
  if(comp_default_set) return;
  comp_default_set=true;
  def_infilepath = infilepath + "/"+filename_prefix + "_"+SkimName+"_"+sample+".root";
  def_histpath=hn;
  
  x_title.push_back(GetTitleByType(htype));
  units.push_back(hunit);
  Rebins.push_back(rb);
  Xmins.push_back(Xmin);
  Xmaxs.push_back(Xmax);
  Ymaxs.push_back(Ymax);

  HistNames.push_back(histtag);
  LegendNames.push_back(legend);

}

void HNLPlotter::AddAK8(TString CR){

  //  AddHist("AK8/AK8J_Tagger_particleNet_WvsQCD" ,"PNET WvsQCD", "",{2},0,1);
  //  AddHist("AK8/AK8J_Mass/l1J" ,"m_{l_{1}J} GeV", "GeV", {0,100,200,300,400,800,1200,2500},0.,2500.);
  //  AddHist("AK8/AK8J_Mass/l2J" ,"m_{l_{2}J} GeV", "GeV", {0,400,800,1200,2500},0.,2500.);
  //  AddHist("AK8/AK8J_Mass/llJ" ,"m_{llJ} GeV", "GeV", {0,400,800,1200,2500},0.,2500.);
  //  AddHist("AK8/AK8J_Eta" ,"#eta AK8", "int", {2},-3.,3.);
  AddHist("Master/M1J","m_{l_{1}J} GeV", "GeV", {1},0.,2500.);
}
void HNLPlotter::AddVBF(TString CR){
  AddHist("VBF/MaxDEta_jet1_jet2","#Delta (#eta) JJ","int", {10},0,10);
  AddHist("VBF/Lead_MJJ","m_{JJ} GeV","GeV", {500,750,1200,1700,3000},0,3000);
  AddHist("VBF/Lead_zeppenfeld","zeppenfeld","int", {10},0,5);
  AddHist("VBF/MaxDEtaJets_MJJ","m_{JJ} GeV [MaxDeta]","GeV", {0,500,1200,1700,3000},0,3000);
}
void HNLPlotter::AddMisc(TString CR){
  AddHist("DeltaR/dR_ll" ,"#DeltaR_{LL}"  , "", {5.}, 0, 5);
  AddHist("DeltaPhi/dPhi_lep1_lep2" ,"#Delta#phi_{LL}"  , "", {5.}, 0, 5);
  AddHist("DeltaR/Jet_dR_jj" ,"#Delta#phi_{jj}"  , "", {5.}, 0, 5);
  AddHist("Standard/N_AK4J"  ,"N_{AK4J}"  , "",    {1.}, 4, 10);
  AddHist("NObj/N_BJet"  ,"N_{BJ}"  , "",    {1.}, 0, 4);
  AddHist("SKEvent/Ev_MET"  ,"Ev_MET"  , "",    {2.}, 0, 400);
  AddHist("AK4Jets/Jet_eta"  ,"Jet Eta"  , "",    {5.}, -5, 5);
  AddHist("AK4Jets/Jet_pt"  ,"Jet Pt"  , "",    {1.}, 0, 200);
  

  //  AddHist("SKEvent/Ev_MET2_ST"  ,"MET^{2}/S_{T}","GeV",  {0,2,4,6,8,10,15,20,30,40}, 0, 40);
  AddHist("MainPlots/Ev_MET2_ST"  ,"MET^{2}/S_{T}","GeV",  {0,5,10,15,20,30,40,50,75,100}, 0, 100);
  AddHist("MainPlots/HT_PT1","H_{T}/p^{lep_{1}}_{T} GeV", "GeV", {0,2,3,4,5,10},0, 10);
  AddHist("MainPlots/L_T","L_{T}  GeV", "GeV", {0,50,100,200,500,1000},0, 1000);
}

void HNLPlotter::AddMass(int nlep, TString CR){
  if(CR.Contains("ZZ"))AddHist("Standard/M_ll"  ,"M_{ll}"  , "GeV",    {2},0,500);
  else AddHist("Standard/M_ll"  ,"M_{ll}"  , "GeV",    {2},0,200);
  AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2500);
  AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2500);
  AddHist("Mass/DiJet_M_llW"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2500);
  AddHist("Mass/DiJet_M_l1jj"  ,"M_{l1W}"  , "GeV",    {0,150,200,300,400,600,1000}, 0, 1000);
  AddHist("Mass/DiJet_M_lljj"  ,"M_{llW}"  , "GeV",    {0,150,200,300,400,600,1000}, 0, 1000);
  if(nlep==3)   AddHist("Mass/M_lll"  ,"M_{lll}"  , "GeV",   {1},70,105);
  if(nlep==4)   AddHist("Mass/M_llll"  ,"M_{llll}"  , "GeV",    {2},0,400);
  if(nlep==4)   AddHist("Mass/M_BestZ"  ,"M_{bestZ}"  , "GeV",    {1}, 0, 400);
  if(nlep==4)   AddHist("Mass/M_OtherZ"  ,"M_{OtherZ}"  , "GeV",    {1}, 0, 400);
  if(nlep==3)   AddHist("Mass/M_minOSSF"  ,"M_{minOS}"  , "GeV",    {2}, 0, 400);
  if(nlep==3)   AddHist("Mass/M_minSSSF"  ,"M_{minSS}"  , "GeV",    {2}, 0, 400);
  if(nlep==3)   AddHist("Mass/Mt_minSSSF"  ,"MT_{minSS}"  , "GeV",    {2}, 0, 400);
  if(nlep==3)   AddHist("Mass/Mt_minOSSF"  ,"MT_{minSS}"  , "GeV",    {2}, 0, 400);


}
void HNLPlotter::AddLepton(int nlep,TString CR){

  AddHist("Master/Lep1_pt" ,"P^{1}_{T} GeV" , "GeV", {0, 20., 50.,75.,100.,125., 200.,500}, 0, 500);
  AddHist("Master/Lep2_pt" ,"P^{2}_{T} GeV" , "GeV", {0.,10.,15., 25.,30,40,50,75,100., 200.}, 0, 200);
  if(nlep==3) AddHist("Leptons/Lep_3_pt" ,"P^{3}_{T} GeV" , "GeV", {0.,10.,15., 25.,50,75,100., 200.}, 0, 200);
  if(nlep==4) AddHist("Leptons/Lep_3_pt" ,"P^{3}_{T} GeV" , "GeV", {0.,10.,15., 25.,50,75,100., 200.}, 0, 200);
  if(nlep==4) AddHist("Leptons/Lep_4_pt" ,"P^{4}_{T} GeV" , "GeV", {0.,10.,15., 25.,50,75,100., 200.}, 0, 200);
  AddHist("Leptons/Lepton_pt" ,"P_{T} " , "int", {0.,15.,20.,30.,40., 60.,100.,250.}, 10, 250);
  AddHist("Leptons/Lepton_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);

  AddHist("Leptons/Lepton_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
  AddHist("Leptons/Lep_1_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
  AddHist("Leptons/Lep_2_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
  if(nlep==3)AddHist("Leptons/Lep_3_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);

  AddHist("Leptons/Lep_1_phi" ,"#phi Lepton" , "int", {2},-5,5);
  AddHist("Leptons/Lep_2_phi" ,"#phi Lepton" , "int", {2},-5,5);
  if(nlep==3)AddHist("Leptons/Lep_3_phi" ,"#phi Lepton" , "int", {2},-5,5);
  AddHist("Leptons/SumQ" ,"Sum Charge" , "int", {1},-5,5);

}

void HNLPlotter::AddHist(TString hn, TString htype, TString hunit, vector<double> rb, double Xmin, double Xmax, double Ymax){

  HistNames.push_back(hn);
  x_title.push_back(GetTitleByType(htype));
  units.push_back(hunit);
  Rebins.push_back(rb);
  Xmins.push_back(Xmin);
  Xmaxs.push_back(Xmax);
  Ymaxs.push_back(Ymax);

  return;
}
void HNLPlotter::BasicSetup(SetupHelper logy, SetupHelper ratio,  TString channel){
  
  /// setups up default options
  
  if(logy==LOGY) UseLogyAll(true);
  else UseLogyAll(false);
  if(ratio==DrawRatio) DrawRatioAll(true) ;
  else DrawRatioAll(false);

  LeptonChannel(channel);
}

void HNLPlotter::SetupPlotter(TString era, TString Skim, TString Analyzer, TString FlagDir){
  SkimName=Skim;
  Era=era;
  AnalyserName=Analyzer;
  filename_prefix=AnalyserName;
  SetupPlotter(FlagDir);
}

void HNLPlotter::SetupPlotter(TString FlagDir=""){
  
  TString s_hostname = GetHostname(); 
  TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH"); 
  TString ENV_PLOT_PATH = getenv("PLOT_PATH"); 
  TString FLATVERSION = getenv("FLATVERSION"); 
  TString input_path = ENV_MERGEDFILE_PATH +"/"+AnalyserName+"/SSControl/"; 

  TString output = ENV_PLOT_PATH + "/"+AnalyserName+"/"; 
  cout << "SetupPlotter [output] = " << output << endl;

  MakeDir(output);

  if(DateFileTag != ""){
    MakeDir(output);
    output+=DateFileTag+"/";
  }
  MakeDir(output);  output+="/"+MacroName+"/"; 
  MakeDir(output);  output+=Era+"/";                                                                                                          
  MakeDir(output);                                                                                                                                 
  plotpath=output;
  
  syncpath = ENV_PLOT_PATH + "/"+AnalyserName+"/";

  if(DoDebug)cout << MacroName << " Output dir = " << output << endl;

  infilepath = ENV_MERGEDFILE_PATH + "/"+AnalyserName+"/SSControl/"+ DateFileTag + "/"+ Era+FlagDir;


  SetupSampleInfo();
                                 
  return;

}

TString HNLPlotter::GetTitleByType(TString htype ){
  
  if(htype == "MET")   return "#slash{E}_{T}^{miss} [GeV]";
  if(htype == "METPhi") return "#phi(#slash{E}_{T}^{miss})";
  if(htype == "LPT1")  return "p^{l1}_{T} [GeV]";
  if(htype == "LPT2")  return "p^{l2}_{T} [GeV]";
  if(htype == "MLL")   return "m_{ll} (GeV)";
  if(htype == "NJ4") return "N^{AK4}_{j}";
  if(htype == "NJ8") return "N^{AK8}_{j}";
  if(htype == "NBJ") return "N^{AK4}_{bj}";
  return htype; 
  
}



HNLPlotter::~HNLPlotter(){

  system("rm -rf "+path_rebins);
  system("rm -rf "+path_y_axis);
  system("rm -rf "+path_x_axis);
  
}



TH1D* HNLPlotter::ConstructHist(TString filepath, TString fullhistname, bool DEBUGout){

  TH1D* hist_temp;
  
  //==== get root file                                                                                                                     
  DoDebug=false;
  if(DoDebug) cout << "ConstructHist " << endl;

  if(gSystem->AccessPathName(filepath)){
    if(DoDebug)     cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  TFile* file = new TFile(filepath);
  if( !file ){
    if(DoDebug)    cout << "No file : " << filepath << endl;
    return hist_temp;
  }
  
  //==== get histogram                                                                                                                                                                                                                                                                
  hist_temp = (TH1D*)file->Get(fullhistname);
  if(!hist_temp || hist_temp->GetEntries() == 0){
    if(DoDebug){
      cout << "No histogram : " << fullhistname << endl;
    }
    file->Close();
    delete file;
    return hist_temp;
  }

  //==== set histogram name, including sample name                                                                                                                                                                                                                                    
  hist_temp->SetName(fullhistname);

  if(XaxisMin != -999) hist_temp->GetXaxis()->SetRangeUser(XaxisMin, XaxisMax);
  hist_temp->Rebin(RebinX);

  if(Normalise > 0) hist_temp->Scale(Normalise / hist_temp->Integral());
  //==== make overflows bins                                                                                                                                                                                                                                                          
  TH1D *hist_final = MakeOverflowBin(hist_temp);

  //==== Remove Negative bins                                                                                                                                                                                                                                                         
  TAxis *xaxis = hist_final->GetXaxis();
  for(int ccc=1; ccc<=xaxis->GetNbins(); ccc++){
    if(DoDebug&&DEBUGout) cout << fullhistname << "\t["<<xaxis->GetBinLowEdge(ccc) <<", "<<xaxis->GetBinUpEdge(ccc) << "] : " << hist_final->GetBinContent(ccc) << endl;
    if(hist_final->GetBinContent(ccc)<0){
      hist_final->SetBinContent(ccc, 0.);
      hist_final->SetBinError(ccc, 0.);
    }
  }

  
  file->Close();
  return hist_final;
  
}





TH1D* HNLPlotter::ConstructHist(TString filepath, TString fullhistname, vector<double> vrebinTMP,  bool DEBUGout){

  TH1D* hist_temp;

  //==== get root file                                                                                                                                                                                                                                                                                                        
  DoDebug=false;
  if(DoDebug) cout << "ConstructHist " << endl;

  if(gSystem->AccessPathName(filepath)){
    if(DoDebug)     cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  TFile* file = new TFile(filepath);
  if( !file ){
    if(DoDebug)    cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  //==== get histogram                                                                                                                                                                                                                                                                                                        
  hist_temp = (TH1D*)file->Get(fullhistname);
  if(!hist_temp || hist_temp->GetEntries() == 0){
    if(DoDebug){
      cout << "No histogram : " << fullhistname << endl;
    }
    file->Close();
    delete file;
    return hist_temp;
  }

  //==== set histogram name, including sample name                                                                                                                                                                                                                                                                            
  hist_temp->SetName(fullhistname);

  if(XaxisMin != -999) hist_temp->GetXaxis()->SetRangeUser(XaxisMin, XaxisMax);

  if(vrebinTMP.size()==1) hist_temp->Rebin(vrebinTMP[0]);
  else{
    double TMParray[vrebinTMP.size()];
    std::copy(vrebinTMP.begin(), vrebinTMP.end(), TMParray);
    hist_temp = (TH1D *)hist_temp->Rebin(vrebinTMP.size()-1, "hnew1", TMParray);

  }
  if(Normalise > 0) hist_temp->Scale(Normalise / hist_temp->Integral());
  //==== make overflows bins                                                                                                                                                                                                                                                                                                  
  TH1D *hist_final = MakeOverflowBin(hist_temp);

  //==== Remove Negative bins                                                                                                                                                                                                                                                                                                 
  TAxis *xaxis = hist_final->GetXaxis();
  for(int ccc=1; ccc<=xaxis->GetNbins(); ccc++){
    if(DoDebug&&DEBUGout) cout << fullhistname << "\t["<<xaxis->GetBinLowEdge(ccc) <<", "<<xaxis->GetBinUpEdge(ccc) << "] : " << hist_final->GetBinContent(ccc) << endl;
    if(hist_final->GetBinContent(ccc)<0){
      hist_final->SetBinContent(ccc, 0.);
      hist_final->SetBinError(ccc, 0.);
    }
  }


  file->Close();
  return hist_final;

}

TH2D* HNLPlotter::Construct2DHist(TString filepath, TString fullhistname){

  TH2D* hist_temp;

  //==== get root file                                                                                                                                                                                                                                                                                                     

  if(DoDebug) cout << "ConstructHist " << endl;

  if(gSystem->AccessPathName(filepath)){
    if(DoDebug)     cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  TFile* file = new TFile(filepath);
  if( !file ){
    if(DoDebug)    cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  //==== get histogram                                                                                                                                                                                                                                                                                                     
  hist_temp = (TH2D*)file->Get(fullhistname);
  if(!hist_temp || hist_temp->GetEntries() == 0){
    if(DoDebug){
      cout << "No histogram : " << fullhistname << endl;
    }
    file->Close();
    delete file;
    return hist_temp;
  }

  //==== set histogram name, including sample name                                                                                                                                                                                                                                                                         
  hist_temp->SetName(fullhistname);

  //==== make overflows bins                                                                                                                                                                                                                                                                                               
  file->Close();
  return hist_temp;

}


TH1D* HNLPlotter::MakeHist(TString filepath, TString fullhistname){

  TH1D* hist_temp;

  //==== get root file                                                                                                                                       
  if(gSystem->AccessPathName(filepath)){
    if(DoDebug)     cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  TFile* file = new TFile(filepath);
  if( !file ){
    if(DoDebug)    cout << "No file : " << filepath << endl;
    return hist_temp;
  }

  //==== get histogram                                                                                                                                       
  hist_temp = (TH1D*)file->Get(fullhistname);
  if(!hist_temp || hist_temp->GetEntries() == 0){
    if(DoDebug){
      cout << "No histogram : " << fullhistname << endl;
    }
    file->Close();
    delete file;
    return hist_temp;
  }
  
  //==== set histogram name, including sample name                                                                                                           
  hist_temp->SetName(fullhistname);

  //==== rebin here                                                                                                                                         
  if(Rebins.size() != 1)  exit (EXIT_FAILURE);
;
  vector<double> vrebin= Rebins[0];
  if(vrebin.size() > 1){

    if(DoDebug){
      cout << "Using Variable binning" << endl;
      for(auto rb : vrebin) cout << "--- " << rb << endl;
    }

    double TMParray[vrebin.size()];
    std::copy(vrebin.begin(), vrebin.end(), TMParray);
    hist_temp = (TH1D *)hist_temp->Rebin(vrebin.size()-1, "hnew1", TMParray);
  }
  else hist_temp->Rebin( vrebin[0] );

  //==== set X-axis range                                                                                                                                    
  SetXaxisRange(hist_temp);

  //==== make overflows bins                                                                                                                                 
  TH1D *hist_final = MakeOverflowBin(hist_temp);

  //==== Remove Negative bins                                                                                                                                
  TAxis *xaxis = hist_final->GetXaxis();
  for(int ccc=1; ccc<=xaxis->GetNbins(); ccc++){
    if(DoDebug) cout << fullhistname << "\t["<<xaxis->GetBinLowEdge(ccc) <<", "<<xaxis->GetBinUpEdge(ccc) << "] : " << hist_final->GetBinContent(ccc) << endl;
    if(hist_final->GetBinContent(ccc)<0){
      hist_final->SetBinContent(ccc, 0.);
      hist_final->SetBinError(ccc, 0.);
    }
  }  

  file->Close();

  return hist_final;
}


void HNLPlotter::draw_hist(){
  
  /// Loop over Cut/Regions set in Plotter.HistPath
  for(i_cut = 0; i_cut < HistPath.size(); i_cut++){

    thiscut_plotpath = plotpath+"/"+HistPath[i_cut];
    mkdir(thiscut_plotpath);

    TFile *outputfile = new TFile(thiscut_plotpath+"/hists.root", "RECREATE");
    
    cout
      << endl
      << "################### Writing in Directory " << HistPath[i_cut] << " ###################" << endl
      << endl;

    //==== Make rebin/y_axis/x_axis file for this cut here
    MakeRebins();
    MakeYAxis();
    MakeXAxis();
    
    
    TString temp_suffix = HistPath[i_cut];
    TString DirName = temp_suffix;//.Remove(0,1);
    

    for(i_var = 0; i_var < HistNames.size(); i_var++){

      if( find( CutVarSkips.begin(), CutVarSkips.end(), make_pair(HistPath[i_cut], HistNames[i_var]) ) != CutVarSkips.end() ){
        continue;
      }
      
      if(VERBOSE)cout << "[Drawing " << HistNames[i_var] << "]" << endl;
      
      TH1D* MC_stacked_staterr = NULL;
      TH1D* MC_stacked_allerr = NULL;
      THStack* MC_stacked = new THStack("MC_stacked", "");
      TH1D* hist_data = NULL;
      vector<TH1D*> hist_signal;
     

      TLegend *lg;
      if(drawratio.at(i_cut)){
        //==== CR
        if(signal_mass.size()==0) lg = new TLegend(0.60, 0.55, 0.96, 0.92);
        //==== SR
        else lg = new TLegend(0.60, 0.35, 0.96, 0.92);
      }
      else{
        //==== CR
        if(signal_mass.size()==0) lg = new TLegend(0.60, 0.55, 0.95, 0.92);
        //==== SR
        else lg = new TLegend(0.55, 0.50, 0.93, 0.90);
      }

      clear_legend_info();
      
      signal_survive_mass.clear();

      bool AnyEntry = false;
      map< TString, TH1D * > map_hist_y;
      
      for(i_file = 0; i_file < bkglist.size()+1+signal_mass.size(); i_file++){ // +1 for data
	
        TString filepath, current_sample, signal_name_for_tex;
        
        //==== root file path name
        //==== bkg
        if( i_file < bkglist.size() ){
	  //cout << bkglist[i_file] << endl;
          TString tmp = bkglist[i_file];
          if(bkglist[i_file].Contains("fake") || bkglist[i_file].Contains("chargeflip")) tmp += "_"+PrimaryDataset[i_cut];
          filepath = infilepath + "/"+filename_prefix+"_"+SkimName+"_"+tmp+filename_suffix;
	  //	  cout << "filepath = " << filepath << endl;
          current_sample = bkglist[i_file];
        }
        //==== data for i_file = bkglist.size()
        else if( i_file == bkglist.size() ){
          filepath = infilepath + "/"+filename_prefix + "_"+SkimName+"_data.root";
          current_sample = "data";
	  //	  cout << "filepath =  " << filepath <<endl;
	    
        }
        //==== signal starting from i_file = bkglist.size()+1
        else{

          int signal_index = i_file-bkglist.size()-1;

          //==== if cut is optimized cut, only draw that signal
          if(HistPath[i_cut].Contains("cutHN")){
            TString tmpcut = "_cutHN"+TString::Itoa(signal_mass[signal_index],10);
            if(HistPath[i_cut]!=tmpcut) continue;
          }
          //==== else, follow signal_draw
          else{
            if(!signal_draw[signal_index]) continue;
          }

          if(DoDebug) cout << "signal_index = " << signal_index << " => mass = " << signal_mass[signal_index] << endl;

          TString WhichChannel = "MuMu1";
          if(HistPath[i_cut].Contains("DiElectron")) WhichChannel = "ElEl";
          if(HistPath[i_cut].Contains("EMu")) WhichChannel = "MuEl";

          TString WhichChannel_for_tex = WhichChannel;

          //==== TChannel
          if( signal_mass[signal_index] < 0 ){
            WhichChannel = "HeavyNeutrinoTo"+WhichChannel+"_Tchannel_M";
          }
          else{
            WhichChannel = "HN"+WhichChannel+"_";
          }
          TString string_signal_mass = WhichChannel+TString::Itoa(abs(signal_mass[signal_index]),10);

          signal_name_for_tex = "SchHN"+WhichChannel_for_tex+TString::Itoa(abs(signal_mass[signal_index]),10);
          if(signal_mass[signal_index] < 0 ) signal_name_for_tex = "TchHN"+WhichChannel_for_tex+TString::Itoa(abs(signal_mass[signal_index]),10);

          filepath = "./rootfiles/"+data_class+"/Signal/"+filename_prefix+"_SK"+string_signal_mass+filename_suffix;
          //cout << filepath << endl;
          current_sample = string_signal_mass;
        }
	
        if(DoDebug){
          cout
	    << "filepath = " << filepath << endl
	    << "hisname = " << HistPath[i_cut]+"/"+HistNames[i_var] << endl;
        }

        //==== get root file
        if(gSystem->AccessPathName(filepath)){
          if(DoDebug){
            cout << "No file : " << filepath << endl;
          }
          continue;
        }
        TFile* file = new TFile(filepath);
        if( !file ){
          if(DoDebug){
            cout << "No file : " << filepath << endl;
          }
          continue;
        }

        TDirectory *dir = (TDirectory *)file->Get(DirName);
        if(!dir){
          if(DoDebug){
            cout << "No Directory : " << file->GetName() << "\t  :" << DirName << ":" << endl;
            file->ls();
          }
          file->Close();
          delete file;
          continue;
        }
        file->cd(DirName);

        //==== full histogram name
        TString fullhistname = HistNames[i_var];
	
        //==== get histogram
        TH1D* hist_temp = (TH1D*)dir->Get(fullhistname);
        if(!hist_temp || hist_temp->GetEntries() == 0){
          if(DoDebug){
            cout << "No histogram : " << current_sample << endl;
          }
          file->Close();
          delete file;
          continue;
        }
        AnyEntry = true;

        //==== set histogram name, including sample name
        hist_temp->SetName(fullhistname+"_"+current_sample);

        //==== rebin here
	
	vector<double> vrebin= GetRebinVariableBins();
	if(vrebin.size() > 1){

	  if(DoDebug){
	    cout << "Using Variable binning" << endl;
	    for(auto rb : vrebin) cout << "--- " << rb << endl;
	  }

	  double TMParray[vrebin.size()];
	  std::copy(vrebin.begin(), vrebin.end(), TMParray);
	  hist_temp = (TH1D *)hist_temp->Rebin(vrebin.size()-1, "hnew1", TMParray);
	}
	else hist_temp->Rebin( n_rebin() );
        
      
        //==== set X-axis range
        SetXaxisRange(hist_temp);

        //==== make overflows bins

	SetLabels=false;
        TH1D *hist_final = MakeOverflowBin(hist_temp);
	
	double ScaleBkg = (i_file < bkglist.size()) ? GetScale(bkglist[i_file]) : 1 ;
	//cout << "Scale " << bkglist[i_file]  << endl;
	//cout << "Scalinging histogram " << bkgScale[i_file] << endl;
	hist_final->Scale(ScaleBkg);
	

        //==== Remove Negative bins
        TAxis *xaxis = hist_final->GetXaxis();
        for(int ccc=1; ccc<=xaxis->GetNbins(); ccc++){
          if(DoDebug) cout << current_sample << "\t["<<xaxis->GetBinLowEdge(ccc) <<", "<<xaxis->GetBinUpEdge(ccc) << "] : " << hist_final->GetBinContent(ccc) << endl;
          if(hist_final->GetBinContent(ccc)<0){
            hist_final->SetBinContent(ccc, 0.);
            hist_final->SetBinError(ccc, 0.);
          }
        }
	
        TString current_MCsector = "";
        //==== Set Attributes here
        //==== bkg
        if( i_file < bkglist.size() ){
          //==== get which MC sector
          current_MCsector = find_MCsector();
          int n_bins = hist_final->GetXaxis()->GetNbins();
          if(!MC_stacked_allerr){

            const Double_t *xcopy=hist_final->GetXaxis()->GetXbins()->GetArray();
            MC_stacked_allerr = new TH1D("MC_stacked_allerr", "", n_bins, xcopy);
            MC_stacked_staterr = new TH1D("MC_stacked_staterr", "", n_bins, xcopy);

          }
          hist_final->SetFillColor(map_sample_string_to_legendinfo[current_MCsector].second);
          hist_final->SetLineColor(map_sample_string_to_legendinfo[current_MCsector].second);

	  //==== MC Norm Scaling

          //==== Add star error histogram now, just before adding systematic
          MC_stacked_staterr->Add(hist_final);

          //==== Now Add systematic to histograms

	  
          double ThisSyst = 0.;
          if( current_sample.Contains("NonPrompt") ) ThisSyst = 0.3;
          else if( current_sample.Contains("chargeflip") ) ThisSyst = 0.2;
          else{
            double mcnorm = 0.2;
	    double lumi =  0.04;///analysisInputs.CalculatedSysts["Luminosity"];
            ThisSyst = sqrt( mcnorm*mcnorm + lumi*lumi );
	  }

          for(int i=1; i<=n_bins; i++){

            double error_syst = ThisSyst*(hist_final->GetBinContent(i));
            double error_sumw2 = hist_final->GetBinError(i);
            double error_combined = sqrt( error_syst*error_syst + error_sumw2*error_sumw2 );

            hist_final->SetBinError(i, error_combined);
          }

          MC_stacked->Add(hist_final);
          MC_stacked_allerr->Add(hist_final);
        }

        //==== data for i_file = bkglist.size()
        else if( i_file == bkglist.size() ){
          hist_final->SetMarkerStyle(20);
          hist_final->SetMarkerSize(1.6);
          TString temp_hist_name(hist_final->GetName());
          hist_data = (TH1D*)hist_final->Clone();
        }
        //==== signal starting from i_file = bkglist.size()+1
        else if( i_file > bkglist.size() ){
          int signal_index = i_file-bkglist.size()-1;
          if(DoDebug) cout << "signal index = " << signal_index << ", mass = " << signal_mass[signal_index] << endl;
          hist_final->SetLineColor(signal_color[signal_index]);
          hist_final->SetLineWidth(3);
          if( signal_mass[signal_index] < 0 ) hist_final->SetLineStyle(3);
          TString temp_hist_name(hist_final->GetName());
          //hist_final->SetName(temp_hist_name+"_signal_"+TString::Itoa(signal_mass[signal_index], 10));
          //hist_final->SetName(temp_hist_name+"_signal_"+TString::Itoa(signal_mass[signal_index], 10));
          //==== scaling signal
          double this_coupling_constant = coupling_constant(signal_mass[signal_index]);
	  /*
  if( HistPath[i_cut].Contains("High_OneFatJet") || histname[i_var].Contains("fj") ){
            this_coupling_constant *= 0.1;
          }
	  */
          hist_final->Scale( k_factor*this_coupling_constant/(1.*TMath::Power(10,log_of_generation_mixing)) );
          hist_signal.push_back( (TH1D*)hist_final->Clone() );
          signal_survive_mass.push_back(signal_mass[signal_index]);
        }
        else{
          cout << "[Warning] attirubte setting, i_file > total sample size? This should not happen!" << endl;
        }
	
	// JOHN
	//	for(unsigned int nbin =1; nbin <hist_data->GetXaxis()->GetNBins()+1; nbin++)MC_stacked->GetXaxis()->SetBinLabel(nbin,hist_data->GetBinLabel(nbin));
	
	fill_legend(lg, hist_final);

        if(HistNames[i_var]=="NJets"){
          cout << "current_sample = " << current_sample << endl;
          TString alias = "";
          if(current_sample.Contains("data")) alias = "data";
          else if(current_sample.Contains("HN")) alias = signal_name_for_tex;
          else{
            alias = map_sample_string_to_legendinfo[current_MCsector].first;
          }
          cout << "==> alias = " << alias << endl;

          if( map_hist_y.find(alias) == map_hist_y.end() ){
            map_hist_y[alias] = new TH1D(alias, "", 1, 0., 1);
          }

          map_hist_y[alias]->Add(hist_final);
        }
        
        file->Close();
        delete file;
        
        if(DoDebug) cout << "end of this sample" << endl;
        
      } // END loop over samples

      if(!AnyEntry) continue;
      if(DoDebug) cout << "[Draw Canvas]" << endl;
      
      if(!drawdata.at(i_cut) && hist_data){
        TString tmpname = hist_data->GetName();
        hist_data = (TH1D*)MC_stacked_allerr->Clone();
        hist_data->SetName(tmpname);
        hist_data->SetMarkerStyle(20);
        hist_data->SetMarkerSize(1.6);
        hist_data->SetMarkerColor(kBlack);
        hist_data->SetLineColor(kBlack);
      }
      
      draw_canvas(MC_stacked, MC_stacked_staterr, MC_stacked_allerr, hist_data, hist_signal, lg, drawdata.at(i_cut), outputfile);

      //==== legend is already deleted in draw_canvas()
      //delete lg; 
      
    } // END loop over variables

    outputfile->Close();
    system("rm "+thiscut_plotpath+"/hists.root");


  } // END loop over cuts
  
  
}



void HNLPlotter::make_bkglist(){
  
  if(bkglist.size() > 0) {
    cout << "NOTE make_bkglist called multiple times, exiting..." << endl;
    return;
  }
  
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    MCsector_first_index.push_back( bkglist.size() );
    if(DoDebug) cout << "[make_bkglist] " << "MCsector_first_index.push_back(" <<  bkglist.size() << ")" << endl;
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );

  }

  cout << "We will use :" << endl;
  for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;
}

void HNLPlotter::SetRebins(TString filepath){

  cout << "[HNLPlotter::SetRebins] Get rebins from " << filepath << endl;

  map< TString, map<TString, int> > ALL_rebins;

  string elline;
  ifstream in(filepath);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString cut;
    TString histname;
    double value;
    is >> cut;
    is >> histname;
    is >> value;
    (ALL_rebins[cut])[histname] = value;
  }

  path_rebins = filepath+"tmp/";
  gSystem->mkdir(path_rebins, kTRUE);
  for(map< TString, map<TString, int> >::iterator thiscut=ALL_rebins.begin(); thiscut!=ALL_rebins.end(); thiscut++){
    ofstream skeleton_rebins(path_rebins+thiscut->first, ios::trunc);
    for(map<TString, int>::iterator thishistname=(thiscut->second).begin(); thishistname!=(thiscut->second).end(); thishistname++){
      skeleton_rebins<<(thishistname->first)<<"\t"<<(thishistname->second)<<endl;
    }
    skeleton_rebins.close();
  }

}


void HNLPlotter::SetYAxis(TString filepath){

  cout << "[HNLPlotter::SetYAxis] Get Yaxis from " << filepath << endl;

  map< TString, map<TString, double> > ALL_y_maxs;

  string elline;
  ifstream in(filepath);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString cut;
    TString histname;
    double value;
    is >> cut;
    is >> histname;
    is >> value;
    (ALL_y_maxs[cut])[histname] = value;
  }

  path_y_axis = filepath+"tmp/";
  gSystem->mkdir(path_y_axis, kTRUE);
  for(map< TString, map<TString, double> >::iterator thiscut=ALL_y_maxs.begin(); thiscut!=ALL_y_maxs.end(); thiscut++){
    ofstream skeleton_y_maxs(path_y_axis+thiscut->first, ios::trunc);
    for(map<TString, double>::iterator thishistname=(thiscut->second).begin(); thishistname!=(thiscut->second).end(); thishistname++){
      skeleton_y_maxs<<(thishistname->first)<<"\t"<<(thishistname->second)<<endl;
    }
    skeleton_y_maxs.close();
  }
  
}

void HNLPlotter::SetXAxis(TString filepath){

  cout << "[HNLPlotter::SetXAxis] Get Xaxis from " << filepath << endl;

  map< TString, map<TString, vector<double>> > ALL_x_axis;

  string elline;
  ifstream in(filepath);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString cut;
    TString histname;
    double value_min, value_max;
    is >> cut;
    is >> histname;
    is >> value_min;
    is >> value_max;
    (ALL_x_axis[cut])[histname].push_back(value_min);
    (ALL_x_axis[cut])[histname].push_back(value_max);
  }

  path_x_axis = filepath+"tmp/";

  gSystem->mkdir(path_x_axis, kTRUE);
  for(map< TString, map<TString, vector<double>> >::iterator thiscut=ALL_x_axis.begin(); thiscut!=ALL_x_axis.end(); thiscut++){
    ofstream skeleton_x_axis(path_x_axis+thiscut->first, ios::trunc);
    for(map<TString, vector<double>>::iterator thishistname=(thiscut->second).begin(); thishistname!=(thiscut->second).end(); thishistname++){
      skeleton_x_axis<<(thishistname->first)<<"\t"<<(thishistname->second).at(0)<<"\t"<<(thishistname->second).at(1)<<endl;
    }
    skeleton_x_axis.close();
  }

}

vector<double> HNLPlotter::GetRebinVariableBins(){

  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];

  map< TString, vector<double> >::iterator it = temp_vrebins.find( var );
  if( it != temp_vrebins.end() ){
    vector<double> TORETURN = it->second;
    return TORETURN;
  }
  else return {1.};
}

void HNLPlotter::MakeRebins(){

  temp_rebins.clear();
  temp_vrebins.clear();
  //  cout << "Rebins.size() = " << Rebins.size() << endl;
  //  if(Rebins.size() > 0){
  //  for(unsigned int i =0; i < Rebins.size(); i++) temp_rebins[HistNames[i]] = Rebins[i];
  //  return;
  // }
  
  if(Rebins.size() > 0){ 
    for(unsigned int i =0; i < Rebins.size(); i++)  {
      temp_vrebins[HistNames[i]] = Rebins[i];       
      if (Rebins[i].size()<1) temp_rebins[HistNames[i]] = 1;
      else  if (Rebins[i].size()== 1) temp_rebins[HistNames[i]] = Rebins[i].at(0);
      else temp_rebins[HistNames[i]] = -1;
    }
  }
  

  string elline;
  ifstream in(path_rebins+HistPath[i_cut]);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString histname;
    double value;
    is >> histname;
    is >> value;
    //==== if -999, don't set
    if(value!=-999){
      temp_rebins[histname] = value;
    }
  }

}

void HNLPlotter::MakeYAxis(){


 temp_y_maxs.clear();
 
 
 if(Ymaxs.size() > 0){
   for(unsigned int i =0; i < Ymaxs.size(); i++) temp_y_maxs[HistNames[i]] = Ymaxs[i];
   return;
 }


  string elline;
  ifstream in(path_y_axis+HistPath[i_cut]);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString histname;
    double value;
    is >> histname;
    is >> value;
    //==== if -999, don't set
    if(value!=-999){
      temp_y_maxs[histname] = value;
    }
  }

}

void HNLPlotter::MakeXAxis(){

  temp_x_mins.clear();
  temp_x_maxs.clear();

  if(Xmaxs.size() > 0){
    for(unsigned int i =0; i < Xmins.size(); i++) temp_x_mins[HistNames[i]] = Xmins[i];
    for(unsigned int i =0; i < Xmaxs.size(); i++) temp_x_maxs[HistNames[i]] = Xmaxs[i];
    return;
  }

  string elline;
  ifstream in(path_x_axis+HistPath[i_cut]);
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString histname;
    double value_min, value_max;
    is >> histname;
    is >> value_min;
    is >> value_max;
    //==== if -999, don't set
    if(value_min!=-999){
      temp_x_mins[histname] = value_min;
    }
    if(value_max!=-999){
      temp_x_maxs[histname] = value_max;
    }
  }

}

TString HNLPlotter::find_MCsector(){
  for(unsigned int i=0; i<MCsector_first_index.size()-1; i++){
    if(MCsector_first_index.at(i) <= i_file && i_file < MCsector_first_index.at(i+1)){
      if(DoDebug) cout << "[find_MCsector] returned MCsector is " << samples_to_use.at(i) << endl;
      return samples_to_use.at(i);
    }
  }
  if(DoDebug) cout << "[find_MCsector] returned MCsector is " << samples_to_use.back() << endl;
  return samples_to_use.back();
}

void HNLPlotter::clear_legend_info(){
  hist_for_legend_bkg.clear();
  hist_for_legend_signal.clear();
  MCsector_survive.clear();
  for(int i=0; i<samples_to_use.size(); i++){
    MCsector_survive[samples_to_use.at(i)] = false;
  }

}

double HNLPlotter::coupling_constant(int mass){

  TString cut = HistPath[i_cut];

  double scale(1.);
  if(CurrentSC==SR2){  }

  if( coupling_constants.find( make_pair(cut, mass) ) != coupling_constants.end() ){
    if(DoDebug) cout << "cut = " << cut << ", mass = " << mass << " => coupling constant = " << coupling_constants[make_pair(cut, mass)] << endl;
    return coupling_constants[make_pair(cut, mass)];
  }
  else return TMath::Power(10,log_of_generation_mixing);

}

void HNLPlotter::fill_legend(TLegend* lg, TH1D* hist){
  //==== here, hist_for_legned = {"A", "B", "D"}
  //==== now, push_back data and signal to make
  //==== hist_for_legned = {"A", "B", "D", "data", "HN40", "HN50", "HN60"}
  
  //==== bkg
  if( i_file < bkglist.size() ){
    TString current_MCsector = find_MCsector();
    if(DoDebug) cout << "[fill_legend] current_MCsector is " << current_MCsector << endl;
    if( !MCsector_survive[current_MCsector] ){
      if(DoDebug) cout << "[fill_legend] => is saved" << endl;
      hist_for_legend_bkg.push_back((TH1D*)hist->Clone());
      MCsector_survive[current_MCsector] = true;
    }
  }
  //==== data
  else if( i_file == (int)bkglist.size() ){
    hist_for_legend_data = (TH1D*)hist->Clone();
    if(DoDebug) cout << "Data added in hist_for_legend" << endl;
  }
  //==== signals
  else if( i_file > (int)bkglist.size() ){
    hist_for_legend_signal.push_back((TH1D*)hist->Clone());
    if(DoDebug) cout << "Signal added in hist_for_legend" << endl;
  }
  else{
    cout << "[Warning] fill_legend, i_file > total sample size? This should not happen!" << endl;
  }


}

void HNLPlotter::draw_legend(TLegend* lg, bool DrawData){
  // Example :
  //                      0    1    2    3
  // samples_to_use   = {"A", "B", "C", "D"}
  // MCsector_survive = { T ,  T ,  F ,  T }
  //
  //                       0    1    2      3        4          5
  // hist_for_legend are {"A", "B", "D", "data", "signal1", "signal2"}
  // i_data = 6 - 2 - 1 = 3
  
  if(DoDebug) cout << "[draw_legend] printing MCsector_survive" << endl;
  for(auto it = MCsector_survive.begin(); it != MCsector_survive.end(); ++it){
    if(DoDebug) cout << "[draw_legend] " << it->first << " is " << it->second << endl;
  }
  for(int i=samples_to_use.size()-1, j=hist_for_legend_bkg.size()-1; i>=0; i--){
    if(MCsector_survive[samples_to_use.at(i)]){
      if(DoDebug) cout << "[draw_legend] " << samples_to_use.at(i) << " is added in legend" << endl;
      lg->AddEntry(hist_for_legend_bkg.at(j), map_sample_string_to_legendinfo[samples_to_use.at(i)].first, "f");
      j--;
    }
  }

  //==== Signal
  if(CurrentSC==no_class){
    for(unsigned int i=0; i<signal_survive_mass.size(); i++){
      int this_mass = signal_survive_mass.at(i);
      if( find(signal_mass.begin(), signal_mass.end(), this_mass) != signal_mass.end()){
        lg->AddEntry(hist_for_legend_signal.at(i), legend_coupling_label(this_mass), "l");
      }
    }

  }
  else{

    for(int i_sigcl=0; i_sigcl<AllSignalClasses.size(); i_sigcl++){

      signal_class this_cl = AllSignalClasses.at(i_sigcl);

      if(CurrentSC==this_cl){

        for(unsigned int i=0; i<signal_survive_mass.size(); i++){
          int this_mass = signal_survive_mass.at(i);
          if( find(map_class_to_signal_mass[this_cl].begin(), map_class_to_signal_mass[this_cl].end(), this_mass) != map_class_to_signal_mass[this_cl].end()){
            lg->AddEntry(hist_for_legend_signal.at(i), legend_coupling_label(this_mass), "l");
          }
        }

      }

    }

  }

  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->Draw();
}



void HNLPlotter::draw_canvas(THStack *mc_stack, TH1D *mc_staterror, TH1D *mc_allerror, TH1D *hist_data, vector<TH1D *> hist_signal, TLegend *legend, bool DrawData, TFile *outputf){

  if(!hist_data) return;

  for(unsigned int i=1; i < mc_staterror->GetNbinsX()+1; i++){
    if(VERBOSE)cout << "PreBin " << i << " Get Bin Content " << mc_staterror->GetBinContent(i) << endl;
  }


  //==== signal_class
  CurrentSC = no_class;
  
  //==== y=0 line
  double x_0[2], y_0[2];
  x_0[0] = -5000;  y_0[0] = 0;
  x_0[1] = 5000;  y_0[1] = 0;
  TGraph *g0 = new TGraph(2, x_0, y_0);
  //==== y=1 line
  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);

  //==== If we draw data, prepare top/bottom pads
  
  TCanvas* c1 = new TCanvas(HistNames[i_var], "", Canvas_X,Canvas_Y);
  c1->Draw();
  c1->cd();

  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

  if(drawratio.at(i_cut)){
    canvas_margin(c1, c1_up, c1_down);

    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();
  }
  else{
    canvas_margin(c1);
  }

  //==== HOTFIX Rebin zero-bkgd
  bool IsMergeZeroBackground = false;
  if(MergeZeroBins){
    vector<double> new_binval = GetRebinZeroBackground(mc_stack, mc_staterror, mc_allerror, hist_data, hist_signal);
    if(new_binval.size()>0){
      IsMergeZeroBackground = true;

      const int new_nbins = new_binval.size()-1;
      double new_binvals[new_nbins+1];
      for(int i=0;i<new_nbins+1;i++) new_binvals[i] = new_binval.at(i);

      THStack *new_mc_stack = new THStack("new_mc_stack", "");
      TList *list_stack = mc_stack->GetHists();
      for(int i=0; i<list_stack->Capacity(); i++){
        TH1D *this_hist = (TH1D *)list_stack->At(i);
        this_hist = (TH1D *)this_hist->Rebin(new_nbins, "hnew1", new_binvals);
        new_mc_stack->Add(this_hist);
      }
      mc_stack = new_mc_stack;

      mc_staterror = (TH1D *)mc_staterror->Rebin(new_nbins, "hnew1", new_binvals);
      mc_allerror = (TH1D *)mc_allerror->Rebin(new_nbins, "hnew1", new_binvals);
      hist_data = (TH1D *)hist_data->Rebin(new_nbins, "hnew1", new_binvals);

      for(unsigned int i=0; i<hist_signal.size(); i++){
        hist_signal.at(i) = (TH1D *)hist_signal.at(i)->Rebin(new_nbins, "hnew1", new_binvals);
      }
    }
  }
  
  //==== empty histogram for axis
  TH1D *hist_empty = (TH1D*)mc_stack->GetHists()->At(0)->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");
  //=== get dX
  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();
  TString YTitle = DoubleToString(dx);
  if(IsMergeZeroBackground) YTitle = "Events / bin";
  //  if(Rebins[i_cut].size() > 1) YTitle = "Events / bin";
  
  hist_empty->GetYaxis()->SetTitle(YTitle);
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = default_y_min;
  double YmaxScale = 2.;
  //  cout << UseLogy.size() << endl;
  if(UseLogy.at(i_cut)>0){
    Ymin = UseLogy.at(i_cut);
    YmaxScale = 100;
    hist_empty->SetMinimum(UseLogy.at(i_cut));

    //    cout << "SET LOG Y " << drawratio.at(i_cut) << endl;
    //    c1->SetLogy();
    //    c1_up->SetLogy();

    if(drawratio.at(i_cut)) c1_up->SetLogy();
    else c1->SetLogy();
  }
  hist_empty->Draw("histsame");
  //==== hide X Label for top plot
  if(drawratio.at(i_cut)) hist_empty->GetXaxis()->SetLabelSize(0);
  
  //==== bkg
  if(!mc_stack->GetHists()){
    cout << "[No Background]" << endl;
    return;
  }
  mc_stack->Draw("histsame");

  //==== signal
  if(CurrentSC==no_class){

    for(unsigned int i=0; i<signal_survive_mass.size(); i++){
      int this_mass = signal_survive_mass.at(i);
      if( find(signal_mass.begin(), signal_mass.end(), this_mass) != signal_mass.end()){
        hist_signal[i]->Draw("histsame");
      }
    }

  }
  else{

    for(int i_sigcl=0; i_sigcl<AllSignalClasses.size(); i_sigcl++){

      signal_class this_cl = AllSignalClasses.at(i_sigcl);

      if(CurrentSC==this_cl){

        for(unsigned int i=0; i<signal_survive_mass.size(); i++){
          int this_mass = signal_survive_mass.at(i);
          if( find(map_class_to_signal_mass[this_cl].begin(), map_class_to_signal_mass[this_cl].end(), this_mass) != map_class_to_signal_mass[this_cl].end()){
            hist_signal[i]->Draw("histsame");
          }
        }

      }

    }

  }

  //==== background err
  mc_allerror->SetMarkerColorAlpha(kAzure-9, 0);
  mc_allerror->SetFillStyle(3013);
  mc_allerror->SetFillColor(kBlack);
  mc_allerror->SetLineColor(0);
  mc_allerror->Draw("sameE2");

  //==== Draw Data at last
  vector<float> err_up_tmp;
  vector<float> err_down_tmp;
  const double alpha = 1 - 0.6827;
  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors(hist_data);
  for(int i=0; i<gr_data->GetN(); ++i){
    int N = gr_data->GetY()[i];
    double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    double U =  (N==0) ? ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) : ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
    if( N!=0 ){
      gr_data->SetPointEYlow(i, N-L );
      gr_data->SetPointEXlow(i, 0);
      gr_data->SetPointEYhigh(i, U-N );
      gr_data->SetPointEXhigh(i, 0);
      err_down_tmp.push_back(N-L);
      err_up_tmp.push_back(U-N);
     }
    else{
      double zerodata_err_low = 0.1;
      double zerodata_err_high = 1.8;

      double xlow = gr_data->GetX()[i]-gr_data->GetEXlow()[i];
      double xhigh = gr_data->GetX()[i]+gr_data->GetEXhigh()[i];
      if(ZeroDataCheckCut(xlow,xhigh)){
        zerodata_err_low = 0.;
        zerodata_err_high = 0.;
      }

      gr_data->SetPointEYlow(i, zerodata_err_low);
      gr_data->SetPointEXlow(i, 0.);
      gr_data->SetPointEYhigh(i, zerodata_err_high);
      gr_data->SetPointEXhigh(i, 0.);
      err_down_tmp.push_back(zerodata_err_low);
      err_up_tmp.push_back(zerodata_err_high);
    }
  }
  gr_data->SetLineWidth(2.0);
  gr_data->SetMarkerSize(0.);
  gr_data->SetMarkerColor(kBlack);
  gr_data->SetLineColor(kBlack);
  hist_data->Draw("phistsame");
  gr_data->Draw("p0same");

  //==== ymax
  double AutoYmax = max( GetMaximum(gr_data), GetMaximum(mc_allerror) );
  //hist_empty->GetYaxis()->SetRangeUser( default_y_min, y_max() );
  hist_empty->GetYaxis()->SetRangeUser( Ymin, YmaxScale*AutoYmax );
  
  if(DrawSmallLegend)   hist_empty->GetYaxis()->SetRangeUser( Ymin, 5*AutoYmax );

  
  //==== legend
  legend->AddEntry(mc_allerror, "Stat.+syst. uncert.", "f");
  if(DrawData){
    legend->AddEntry(hist_data, "Data", "pe");
  }
  else{
    legend->AddEntry(hist_data, "Total Background", "pe");
  }

  if(drawratio.at(i_cut)) c1_up->cd();
  if(DoDebug) cout << "draw_legend " << endl;

  draw_legend(legend, DrawData);
  if(DoDebug) cout << "END draw_legend " <<endl;

  hist_empty->Draw("axissame");

  //==== Ratio
  if(DoDebug) cout << "drawratio " << drawratio.size() << " " << i_cut <<endl;

  if(!drawratio.at(i_cut)){
    hist_axis(hist_empty);
    hist_empty->GetXaxis()->SetTitle(x_title[i_var]);
  }
  else{
    //==== MC-DATA
    c1_down->cd();
    TString name_suffix = hist_data->GetName();
    TH1D *ratio_point = (TH1D *)hist_data->Clone();
    ratio_point->SetName(name_suffix+"_central");

    TH1D *tmp_ratio_point = (TH1D *)hist_data->Clone();
    tmp_ratio_point->Divide(mc_allerror);
    TGraphAsymmErrors *gr_ratio_point = new TGraphAsymmErrors(tmp_ratio_point);
    gr_ratio_point->SetName("gr_"+name_suffix+"_central");
    gr_ratio_point->SetLineWidth(2.0);
    gr_ratio_point->SetMarkerSize(0.);
    gr_ratio_point->SetLineColor(kBlack);

    TH1D *ratio_staterr = (TH1D *)hist_data->Clone();
    ratio_staterr->SetName(name_suffix+"_staterr");
    TH1D *ratio_allerr = (TH1D *)hist_data->Clone();
    ratio_allerr->SetName(name_suffix+"_allerr");
    for(int i=1; i<=ratio_point->GetXaxis()->GetNbins(); i++){
      
      if(VERBOSE) cout << "DATA bin " << i << hist_data->GetBinContent(i) << " bkg = " << mc_allerror->GetBinContent(i) << endl;
      
      //==== FIXME for zero? how?
      if(mc_allerror->GetBinContent(i)!=0){

        //==== ratio point
        //==== BinContent = Data/Bkgd
        //==== BinError = DataError/Bkgd
        ratio_point->SetBinContent( i, ratio_point->GetBinContent(i) / mc_allerror->GetBinContent(i) );
        ratio_point->SetBinError ( i, ratio_point->GetBinError(i) / mc_allerror->GetBinContent(i) );

        if(err_down_tmp.at(i-1)  !=0.) {
          gr_ratio_point->SetPointEYlow(i-1, err_down_tmp.at(i-1) / mc_allerror->GetBinContent(i) );
          gr_ratio_point->SetPointEXlow(i-1, 0);
          gr_ratio_point->SetPointEYhigh(i-1, err_up_tmp.at(i-1) /mc_allerror->GetBinContent(i));
          gr_ratio_point->SetPointEXhigh(i-1, 0);
        }
        else{
          gr_ratio_point->SetPointEYlow(i-1, 0);
          gr_ratio_point->SetPointEXlow(i-1, 0);
          gr_ratio_point->SetPointEYhigh(i-1, 1.8 / mc_allerror->GetBinContent(i));
          gr_ratio_point->SetPointEXhigh(i-1, 0);
        }
        //==== ratio staterr
        //==== BinContent = 1
        //==== BinError = Bkgd(Stat)Error/Bkgd
        ratio_staterr->SetBinContent( i, 1. );
        ratio_staterr->SetBinError( i, mc_staterror->GetBinError(i)/ mc_staterror->GetBinContent(i) );
        //==== ratio allerr
        //==== BinContent = 1
        //==== BinError = Bkgd(Stat+Syst)Error/Bkgd
        ratio_allerr->SetBinContent( i, 1. );
        ratio_allerr->SetBinError( i, mc_allerror->GetBinError(i)/ mc_allerror->GetBinContent(i) );
	if(VERBOSE) cout << "ratio_allerr bin " << i << " mc_allerror->GetBinError(i)/ mc_allerror->GetBinContent(i) = " << mc_allerror->GetBinError(i)/ mc_allerror->GetBinContent(i) << " mc_allerror->GetBinContent(i) = " << mc_allerror->GetBinContent(i) << endl;
      }
    }


    if(DoDebug) cout << "g1->Draw" << endl;

    ratio_allerr->SetMaximum(RatioRange);  
    ratio_allerr->SetMinimum(2-RatioRange);
    
    if(DoDebug) cout << "x_title " << x_title.size() << " " << i_var << endl;

    if(x_title[i_var] != ""){
      if(VERBOSE)  cout << "x_title[i_var]  = " << x_title[i_var]  << endl;
      ratio_allerr->GetXaxis()->SetTitle(x_title[i_var]);
    }
    ratio_allerr->GetYaxis()->SetTitle("#frac{Obs.}{Pred.}");
    ratio_allerr->SetFillColor(kOrange);
    ratio_allerr->SetMarkerSize(0);
    ratio_allerr->SetMarkerStyle(0);
    ratio_allerr->SetLineColor(kWhite);
    ratio_allerr->Draw("E2same");
    hist_axis(hist_empty, ratio_allerr);

    ratio_staterr->SetFillColor(kCyan);
    ratio_staterr->SetMarkerSize(0);
    ratio_staterr->SetMarkerStyle(0);
    ratio_staterr->SetLineColor(kWhite);
    ratio_staterr->Draw("E2same");

    ratio_point->Draw("p9histsame");
    gr_ratio_point->Draw("p0same");

    TLegend *lg_ratio = new TLegend(0.7, 0.8, 0.9, 0.9);
    //lg_ratio->SetFillStyle(0);
    //lg_ratio->SetBorderSize(0);
    lg_ratio->SetNColumns(2);
    if(DrawRatioLegend)lg_ratio->AddEntry(ratio_staterr, "Stat.", "f");
    if(DrawRatioLegend)lg_ratio->AddEntry(ratio_allerr, "Stat.+Syst.", "f");
    //lg_ratio->AddEntry(ratio_point, "Obs./Pred.", "p");
    if(DrawRatioLegend)lg_ratio->Draw();

    ratio_allerr->Draw("axissame");

    //==== y=1 line
    g1->Draw("same");

  }

  //==== write lumi on the top
  c1->cd();
  if(DoDebug) cout << "MakePaperPlot " << MakePaperPlot << endl;

  if(!MakePaperPlot){
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(LatexTextCMS_Size);
    latex_CMSPriliminary.DrawLatex(LatexTextCMS_X,LatexTextCMS_Y, LatexTextCMS);
    latex_Lumi.SetTextSize(0.035);
    if(Era=="2016preVFP")latex_Lumi.DrawLatex(0.7, 0.96, "19.5 fb^{-1} (13 TeV)");
    if(Era=="2016postVFP")latex_Lumi.DrawLatex(0.7, 0.96, "16.8 fb^{-1} (13 TeV)");
    if(Era=="2016") latex_Lumi.DrawLatex(0.7, 0.96, "36.3 fb^{-1} (13 TeV)");
    if(Era=="2017") latex_Lumi.DrawLatex(0.7, 0.96, "41.5 fb^{-1} (13 TeV)");
    if(Era=="2018") latex_Lumi.DrawLatex(0.7, 0.96, "59.9 fb^{-1} (13 TeV)");
    if(Era=="Run2") latex_Lumi.DrawLatex(0.7, 0.96, "137.9 fb^{-1} (13 TeV)"); 

    if(VERBOSE) cout << i_cut << " LeptonChannels " << LeptonChannels.size() << " " << RegionType.size() << endl;
    TString str_channel = GetStringChannelRegion(LeptonChannels.at(i_cut), RegionType.at(i_cut));
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.037);
    channelname.DrawLatex(LatexTextLabel_X, LatexTextLabel_Y, str_channel);
  }
  else{
    //==== This is for Paper
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.050);
    latex_CMSPriliminary.DrawLatex(0.20, 0.89, "#font[62]{CMS}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.SetTextFont(42);
    if(Era=="2016preVFP")latex_Lumi.DrawLatex(0.72, 0.96, "19.5 fb^{-1} (13 TeV)");
    if(Era=="2016postVFP")latex_Lumi.DrawLatex(0.72, 0.96, "16.8 fb^{-1} (13 TeV)");
    if(Era=="2016") latex_Lumi.DrawLatex(0.72, 0.96, "36.3 fb^{-1} (13 TeV)");
    if(Era=="2017") latex_Lumi.DrawLatex(0.72, 0.96, "41.5 fb^{-1} (13 TeV)");
    if(Era=="2018") latex_Lumi.DrawLatex(0.72, 0.96, "59.9 fb^{-1} (13 TeV)");
    if(Era=="Run2") latex_Lumi.DrawLatex(0.72, 0.96, "137.9 fb^{-1} (13 TeV)");


  }
  if(DoDebug) cout << "thiscut_plotpath "<< endl;

  mkdir(thiscut_plotpath);

  TString HistNames_NoDir = HistNames[i_var];
  HistNames_NoDir=HistNames_NoDir.ReplaceAll("/","_");
  
  
  cout << thiscut_plotpath+"/"+HistNames_NoDir+".pdf" << endl;
  c1->SaveAs(thiscut_plotpath+"/"+HistNames_NoDir+".pdf");
  //c1->SaveAs(thiscut_plotpath+"/"+HistNames[i_var]+".png");
  //  cout << "Saving " << thiscut_plotpath+"/"+HistNames[i_var]+".png" << endl;
  //  HistResults.push_back(thiscut_plotpath+"/"+HistNames[i_var]+".pdf");
  
  outputf->cd();
  c1->Write();


  
  delete legend;
  delete c1;
}

int HNLPlotter::n_rebin(){
  
  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];
  
  map< TString, int >::iterator it = temp_rebins.find( var );
  if( it != temp_rebins.end() ){
    int TORETURN = it->second;
    //temp_rebins.erase( it );
    if(DoDebug) cout << "cut = " << cut << ", var = " << var << " => rebins = " << TORETURN << endl;
    return TORETURN;
  }
  else return 1;
  
}

double HNLPlotter::y_max(){
  
  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];

  map< TString, double >::iterator it = temp_y_maxs.find( var );
  if( it != temp_y_maxs.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => rebins = " << temp_rebins[cut] << endl;
    double TORETURN = it->second;
    //temp_y_maxs.erase( it );
    return TORETURN;
  }
  else return default_y_max;

}

void HNLPlotter::SetXaxisRange(TH1D* hist){
  
  if(FullHistNames.size() > 0) {
    hist->GetXaxis()->SetRangeUser(Xmins[0], Xmaxs[0]);
    if(VERBOSE) cout << "SetXaxisRange {Init} " << Xmins[0] << " --- " << Xmins[1] << endl;

    return;
  }
  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];
  
  double this_x_min = hist->GetXaxis()->GetBinLowEdge(1);
  double this_x_max = hist->GetXaxis()->GetBinUpEdge( hist->GetXaxis()->GetNbins() );

  map< TString, double >::iterator it = temp_x_mins.find( var );
  if( it != temp_x_mins.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_min = " << temp_x_mins[var] << endl;
    this_x_min = it->second;
    //temp_x_mins.erase( it );
  }
  it = temp_x_maxs.find( var );
  if( it != temp_x_maxs.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_max = " << temp_x_maxs[var] << endl;
    this_x_max = it->second;
    //temp_x_maxs.erase( it );
  }
  if(VERBOSE) cout << "SetXaxisRange " << this_x_min << " --- " << this_x_max << endl;
  hist->GetXaxis()->SetRangeUser(this_x_min, this_x_max);
}

void HNLPlotter::SetXaxisRange(THStack* mc_stack){
  
  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];
  
  double this_x_min = mc_stack->GetXaxis()->GetBinLowEdge(1);
  double this_x_max = mc_stack->GetXaxis()->GetBinUpEdge( mc_stack->GetXaxis()->GetNbins() );
  
  map< TString, double >::iterator it = temp_x_mins.find( var );
  if( it != temp_x_mins.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_min = " << temp_x_mins[var] << endl;
    this_x_min = it->second;
    //temp_x_mins.erase( it );
  }
  it = temp_x_maxs.find( var );
  if( it != temp_x_maxs.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_max = " << temp_x_maxs[var] << endl;
    this_x_max = it->second;
    //temp_x_maxs.erase( it );
  }
 
  mc_stack->GetXaxis()->SetRangeUser(this_x_min, this_x_max);
}

void HNLPlotter::SetXaxisRangeBoth(THStack* mc_stack, TH1D* hist){

  TString cut = HistPath[i_cut];
  TString var = HistNames[i_var];
  
  double this_x_min = mc_stack->GetXaxis()->GetBinLowEdge(1);
  double this_x_max = mc_stack->GetXaxis()->GetBinUpEdge( mc_stack->GetXaxis()->GetNbins() );
  
  map< TString, double >::iterator it = temp_x_mins.find( var );
  if( it != temp_x_mins.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_min = " << temp_x_mins[var] << endl;
    this_x_min = it->second;
    //temp_x_mins.erase( it );
  }
  it = temp_x_maxs.find( var );
  if( it != temp_x_maxs.end() ){
    //cout << "cut = " << cut << ", var = " << var << " => x_max = " << temp_x_maxs[var] << endl;
    this_x_max = it->second;
    //temp_x_maxs.erase( it );
  }

  mc_stack->GetXaxis()->SetRangeUser(this_x_min, this_x_max);
  hist->GetXaxis()->SetRangeUser(this_x_min, this_x_max);
}

TH1D* HNLPlotter::MakeOverflowBin(TH1D* hist){


  //==== 0    1                                    n_bin_origin
  //====      |---------------------------------------|
  //====             bin_first      bin_last
  //====                |-------------|  
  //==== |   |                                        |   |
  //==== under                                         over
  //==== flow                                          flow
  //==== |<------------>|             |<----------------->|
  //====  all underflow                   all overflow

  //==== Original NBins
  int n_bin_origin = hist->GetXaxis()->GetNbins();
  //==== Changed NBins
  int bin_first = hist->GetXaxis()->GetFirst();
  int bin_last = hist->GetXaxis()->GetLast();
  int n_bin_inrange = bin_last-bin_first+1;
  
  TString XTitle=hist->GetXaxis()->GetTitle();
  TString YTitle=hist->GetYaxis()->GetTitle();

  vector<TString> labels;
  

  double x_first_lowedge = hist->GetXaxis()->GetBinLowEdge(bin_first);
  double x_last_upedge = hist->GetXaxis()->GetBinUpEdge(bin_last);

  
  double Allunderflows = hist->Integral(0, bin_first-1);
  double Allunderflows_error = hist->GetBinError(0);
  Allunderflows_error = Allunderflows_error*Allunderflows_error;

  if(SetLabels){
    for(unsigned int i=1; i<= n_bin_origin+1; i++){
      labels.push_back(hist->GetXaxis()->GetBinLabel(i));
    }
  }
  if(bin_first != 0){
    for(unsigned int i=1; i<=bin_first-1; i++){
      Allunderflows_error += (hist->GetBinError(i))*(hist->GetBinError(i));
    }
    Allunderflows_error = sqrt(Allunderflows_error);
  }

  double Alloverflows = hist->Integral(bin_last+1, n_bin_origin+1);
  double Alloverflows_error = hist->GetBinError(n_bin_origin+1);
  Alloverflows_error = Alloverflows_error*Alloverflows_error;
  for(unsigned int i=bin_last+1; i<=n_bin_origin; i++){
    Alloverflows_error += (hist->GetBinError(i))*(hist->GetBinError(i));
  }
  Alloverflows_error = sqrt(Alloverflows_error);

  //==== Make X-bin array
  Double_t temp_xbins[n_bin_inrange+1];
  int counter=0;
  for(int i=bin_first;i<=bin_last;i++){
    temp_xbins[counter] = hist->GetXaxis()->GetBinLowEdge(i);
    counter++;
  }
  temp_xbins[n_bin_inrange+1-1] = hist->GetXaxis()->GetBinUpEdge(bin_last);
  const Double_t *xcopy=temp_xbins;

  TH1D *hist_out = new TH1D(hist->GetName(), hist->GetTitle(), n_bin_inrange, xcopy);
  for(unsigned int i=1; i<=n_bin_inrange; i++){
    double this_content = hist->GetBinContent(bin_first-1+i);
    double this_error = hist->GetBinError(bin_first-1+i);
    //cout << "["<<hist_out->GetXaxis()->GetBinLowEdge(i)<<", "<<hist_out->GetXaxis()->GetBinUpEdge(i)<<"] : "<<this_content<<endl;

    //==== underflows
    if(i==1){
      this_content += Allunderflows;
      this_error = TMath::Sqrt( this_error*this_error + Allunderflows_error*Allunderflows_error );
    }

    //==== overflows
    if(i==n_bin_inrange){
      this_content += Alloverflows;
      this_error = TMath::Sqrt( this_error*this_error + Alloverflows_error*Alloverflows_error );
    }
    
    hist_out->SetBinContent(i, this_content);
    hist_out->SetBinError(i, this_error);
  }
  
  if(SetLabels){
    for(unsigned int i=1; i<= n_bin_origin; i++){
      hist_out->GetXaxis()->SetBinLabel(i,labels[i-1]);
    }
  }


  return hist_out;
  
}

TString HNLPlotter::DoubleToString(double dx){

  //==== onebin
  if(units[i_var]=="int"){
    return "Events";
  }
  else{

    int dx_int = int(dx);
    int dx_first_two_digits = int((dx-dx_int)*100);
    int dx_first_three_digits = int((dx-dx_int)*1000);

    //==== has integer
    if(dx_int!=0){
      //==== but no digits
      if(dx_first_two_digits==0){
        return "Events / "+TString::Itoa(dx_int,10)+" "+units[i_var];
      }
      //=== also has digits
      else{
        return "Events / "+TString::Itoa(dx_int,10)+"."+TString::Itoa(dx_first_two_digits,10)+" "+units[i_var];
      }
    }
    //=== no integer
    else{
      return "Events / 0."+TString::Itoa(dx_first_two_digits,10)+" "+units[i_var];
    }
  }

  return "Events";

}


TString HNLPlotter::legend_coupling_label(int mass){
 
  //cout << "mass = " << mass << endl;
  //cout << " coupling = " << coupling_const.at(signal_survive_index[mass]) << endl;
  double log_scale = TMath::Log10(coupling_constant(mass)/(1.*TMath::Power(10,log_of_generation_mixing)));
  double log_coupling = TMath::Log10(coupling_constant(mass));
  //cout << " log coupling = " << log_scale << endl;

  TString channel = "s-ch.";
  if(mass<0) channel = "t-ch.";

  mass = abs(mass);

  TString V2 = "#||{V_{N#mu}}^{2}";
  if(PrimaryDataset[i_cut]=="DoubleEG") V2 = "#||{|V_{Ne}}^{2}";
  if(PrimaryDataset[i_cut]=="MuonEG") V2 = "#||{V_{Nl}}^{2}";

  //if(log_coupling == 0) return channel+" HN"+TString::Itoa(mass, 10)+", "+V2+"=1";
  //else return channel+" HN"+TString::Itoa(mass, 10)+", "+V2+"=10^{"+TString::Itoa(log_coupling, 10)+"}";

  if(log_coupling == 0) return "m_{N} = "+TString::Itoa(mass, 10)+" GeV, "+V2+"=1";
  else return "m_{N} = "+TString::Itoa(mass, 10)+" GeV, "+V2+"=10^{"+TString::Itoa(log_coupling, 10)+"}";

  //==== FIXME FOR NEXT UPDATE
  //if(log_coupling == 0) return "m_{N} = "+TString::Itoa(mass, 10)+" GeV ("+channel+"), "+V2+"=1";
  //else return "m_{N} = "+TString::Itoa(mass, 10)+" GeV ("+channel+"), "+V2+"=10^{"+TString::Itoa(log_coupling, 10)+"}";

}

void HNLPlotter::mkdir(TString path){
  
  if( !gSystem->mkdir(path, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << path << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  
}

double HNLPlotter::GetHistValue(TH1D * ht, TString hn){
  
  if(hn=="NEvents") return ht->GetBinContent(1);
  else return ht->Integral(0,ht->GetNbinsX()+1);
  
}

double HNLPlotter::GetHistError(TH1D * ht, TString hn){

  if(hn=="NEvents") return ht->GetBinError(1);
  else {
    Double_t err;
    Double_t hint = ht->IntegralAndError(0,ht->GetNbinsX()+1, err);
    return err;
  }
  return 0;

}
TString HNLPlotter::FixLatex(TString origSt){
  TString fixSt=origSt;
  if(fixSt.Contains("P_T")) fixSt.ReplaceAll("P_T","$\\mathrm{P}_{T}$");
  return fixSt;
}




TString HNLPlotter::GetStringChannelRegion(int A, TString B){

  //==== channel type

  TString channel = "";
  //==== A = 1 : mm
  //==== A = 2 : ee
  //==== A = 3 : em

  if(A==20) channel = "l^{#pm}l^{#pm}";
  if(A==21) channel = "#mu^{#pm}#mu^{#pm}";
  if(A==22) channel = "e^{#pm}e^{#pm}";
  if(A==23) channel = "e^{#pm}#mu^{#pm}";
  if(A==24) channel = "#mu^{#pm}e^{#pm}";
  
  if(A==30) channel = "3l";
  if(A==40) channel = "4l";
  if(A==32) channel = "eee";
  if(A==31) channel = "#mu#mu#mu";
  if(A==33) channel = "e#mul";

  if(A==42) channel = "eeee";
  if(A==41) channel = "#mu#mu#mu#mu";
  if(A==43) channel = "e#mull";



  TString region = "";
  //==== B = 1 : Preselection 
  //==== B = 20 : Low
  //==== B = 21 : Low + two jet
  //==== B = 22 : Low + one jet
  //==== B = 30 : High
  //==== B = 31 : High + two jet
  //==== B = 32 : High + fat jet
  if(B=="1") region = "Preselection";
  else if(B=="31") region = "High Mass SR1";
  else if(B=="32") region = "High Mass SR2";
  else if(B=="WZ") region = "WZ CR";
  else if(B=="ZZ") region = "ZZ CR";
  else region = B;

  //return channel+" "+region;
  return channel;

  //return "#splitline{"+channel+"}{"+region+"}";
  

}

bool HNLPlotter::ZeroDataCheckCut(double xlow, double xhigh){

  if(HistPath[i_cut].Contains("_Low_")){
    if(HistNames[i_var]=="m_lljj_lljjWclosest"){
      if(xlow>=300) return true;
    }
    if(HistNames[i_var]=="m_llj"){
      if(xlow>=300) return true;
    }
  }

  return false;

}

void HNLPlotter::ScaleSample(TString samplename, double scale_value){

  map_sample_string_to_scale[samplename]=scale_value;
  

}
double HNLPlotter::GetScale(TString samplename){

  map<TString, double>::iterator it = map_sample_string_to_scale.find(samplename);

  if(it != map_sample_string_to_scale.end()) {
    //    cout << "Scale " << samplename <<  " -->" << it->second << endl;
    return it->second;
  }
  //  cout << "Scale " <<samplename <<  " -->" << 1 << endl;

  return 1;
}

void HNLPlotter::SetupSampleInfo(){

  map_sample_string_to_list.clear();
  map_sample_string_to_legendinfo.clear();


  map_sample_string_to_list["Prompt"] = {"Prompt"};
  map_sample_string_to_list["Prompt1"] = {"Prompt"};
  map_sample_string_to_list["Prompt2"] = {"Prompt2"};
  map_sample_string_to_list["Prompt3"] = {"Prompt3"};
  map_sample_string_to_list["Prompt4"] = {"Prompt4"};
  map_sample_string_to_list["Prompt5"] = {"Prompt5"};
  map_sample_string_to_list["Prompt6"] = {"Prompt6"};

  ////// Split 
  map_sample_string_to_list["qqZZ"] = {"qqZZ"};
  map_sample_string_to_list["ggZZ"] = {"ggZZ"};
  map_sample_string_to_list["WZ"] = {"WZ"};   map_sample_string_to_list["WZ_Alt"] = {"WZAlt"};
  map_sample_string_to_list["WW"] = {"WW"};
  map_sample_string_to_list["Top"] = {"Top"};  map_sample_string_to_list["Top_Alt"] = {"TopAlt"};
  map_sample_string_to_list["Other_SS"] = {"Other"};

  //map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "ZZZ"}; // WZZ
  //map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  // map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  //map_sample_string_to_list["VVV"] = {"VVV"};
  
  /// Fake
  map_sample_string_to_list["NonPrompt"] = {"NonPrompt"};
  // CF
  map_sample_string_to_list["chargeflip"] = {"CF"};

  /// conversion 
  map_sample_string_to_list["Conv"] = {"Conv"};
  map_sample_string_to_list["WG"] = {"WG"};
  map_sample_string_to_list["ZG"] = {"ZG"};
  map_sample_string_to_list["Other_Conv"] = {"Other_Conv"};

  map_sample_string_to_legendinfo["Prompt"] = make_pair("Prompt", kGreen);
  map_sample_string_to_legendinfo["Prompt1"] = make_pair("Prompt", kGreen);
  map_sample_string_to_legendinfo["Prompt2"] = make_pair("Prompt2", kGreen);
  map_sample_string_to_legendinfo["Prompt3"] = make_pair("Prompt3", kGreen);
  map_sample_string_to_legendinfo["Prompt4"] = make_pair("Prompt4", kGreen);
  map_sample_string_to_legendinfo["Prompt5"] = make_pair("Prompt5", kGreen);
  map_sample_string_to_legendinfo["Prompt6"] = make_pair("Prompt6", kGreen);
  ///// Split                                                                                                                                                                                                                                
  map_sample_string_to_legendinfo["WZ"] = make_pair("WZ", kGreen);  map_sample_string_to_legendinfo["WZ_Alt"] = make_pair("WZAlt", kGreen);
  map_sample_string_to_legendinfo["WW"] = make_pair("W^{+}W^{+}", kOrange);
  map_sample_string_to_legendinfo["qqZZ"] = make_pair("qqZZ", kRed);
  map_sample_string_to_legendinfo["ggZZ"] = make_pair("ggZZ", kSpring-7);
  map_sample_string_to_legendinfo["Top"] = make_pair("Top", kRed-6);  map_sample_string_to_legendinfo["Top_Alt"] = make_pair("TopAlt", kRed-6);
  map_sample_string_to_legendinfo["Other_SS"] = make_pair("Other", kCyan);

  //map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  //map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  //map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  //map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["Conv"] = make_pair("TX/W + #gamma", kSpring-7);
  map_sample_string_to_legendinfo["Other_Conv"] = make_pair("X+ #gamma", kSpring-7);
  map_sample_string_to_legendinfo["WG"] = make_pair("W#gamma", 72);
  map_sample_string_to_legendinfo["ZG"] = make_pair("Z#gamma", 74);

  map_sample_string_to_legendinfo["NonPrompt"] = make_pair("Misid. lepton bkgd.", 870);
  map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge bkgd.", kYellow);

}


void HNLPlotter::LeptonChannel(TString ch){

  LeptonChannels.clear();
  for(int i=0; i < HistPath.size() ; i++){
    if(ch=="MuMu") LeptonChannels.push_back(21);
    if(ch=="EE") LeptonChannels.push_back(22);
    if(ch=="EMu") LeptonChannels.push_back(23);
    if(ch=="LL") LeptonChannels.push_back(20);
    if(ch=="MuMuMu") LeptonChannels.push_back(31);
    if(ch=="EEE") LeptonChannels.push_back(32);
    if(ch=="EMuL") LeptonChannels.push_back(33);
    if(ch=="LLL") LeptonChannels.push_back(30);
    if(ch=="EEEE") LeptonChannels.push_back(42);
    if(ch=="MuMuMuMu") LeptonChannels.push_back(41);
    if(ch=="EMuLL") LeptonChannels.push_back(43);
    if(ch=="LLLL") LeptonChannels.push_back(40);

  }
  for(auto i  : LeptonChannels) cout << "Added LeptonChannels " << i << endl;
}
void HNLPlotter::UseLogyAll(double v){
  UseLogy.clear();
  for(int i=0; i < HistPath.size() ; i++) UseLogy.push_back(v);
}

void HNLPlotter::ApplyMCNormSFAll(bool v){
  ApplyMCNormSF.clear();
  for(int i=0; i < HistPath.size()  ; i++)ApplyMCNormSF.push_back(v);
}
void HNLPlotter::DrawRatioAll(bool v){

  drawratio.clear();
  for(int i=0; i < HistPath.size()  ; i++) drawratio.push_back(v);

}

void HNLPlotter::DrawDataAll(bool v){

  drawdata.clear();
  for(int i=0; i < HistPath.size()  ; i++) drawdata.push_back(v);
}

vector<double> HNLPlotter::GetRebinZeroBackground(THStack *mc_stack, TH1D *mc_staterror, TH1D *mc_allerror, TH1D *hist_data, vector<TH1D *> &hist_signal){

  int original_nbins = mc_allerror->GetXaxis()->GetNbins();
  vector<double> original_binval;
  vector<double> new_binval;

  for(int i=1; i<=original_nbins; i++){
    original_binval.push_back(mc_allerror->GetXaxis()->GetBinLowEdge(i));
  }
  original_binval.push_back(mc_allerror->GetXaxis()->GetBinUpEdge(original_nbins));

  int next_nonzero_bin = 2;
  //==== PUSH1) first bin low-edge
  new_binval.push_back(original_binval.at(0));
  for(int i=2; i<=original_nbins; i++){
    if(mc_allerror->GetBinContent(i)>0){
      next_nonzero_bin = i;
      break;
    }
  }

  int next_zero_bin = -999;
  //cout << "[Plotter::GetRebinZeroBackground] mc_allerror->GetBinContent(original_nbins) = " << mc_allerror->GetBinContent(original_nbins) << endl;
  for(int i=next_nonzero_bin+1; i<=original_nbins; i++){

    //==== HOTFIX ee mll has empty bins at Z-peak
    if(HistNames[i_var]=="m_ll"){
      if(original_binval.at(i)<150) continue;
    }

    if(mc_allerror->GetBinContent(i)<=0){
      next_zero_bin = i;
      break;
    }
  }

  //cout << "[Plotter::GetRebinZeroBackground] next_zero_bin = " << next_zero_bin << endl;
  //==== PUSH Rest
  if(next_zero_bin<0){
    for(int j=next_nonzero_bin; j<original_binval.size(); j++){
      new_binval.push_back(original_binval.at(j));
    }
  }
  else{

    if(next_nonzero_bin+1==next_zero_bin){
      new_binval.push_back(original_binval.at( original_binval.size()-1 ));
    }
    else{

      for(int j=next_nonzero_bin; j<next_zero_bin-2; j++){
	new_binval.push_back(original_binval.at(j));
      }
      new_binval.push_back(original_binval.at( original_binval.size()-1 ));

    }

  }

  /*
    cout << "[Plotter::GetRebinZeroBackground] Printing new bin vals" << endl;
  for(int i=0;i<new_binval.size(); i++){
  cout << new_binval.at(i) << endl;
  }
  */

  return new_binval;

}



void HNLPlotter::draw_hist_canvas(TH1D *hist_default,  TString HistName){

  
  cout    << "################### draw_hist_canvas [" << HistName << "]  ###################" << endl;


  cout
    << endl
    << "################### Writing in Directory " << thiscut_plotpath << " ###################" << endl
    << endl;

  
  thiscut_plotpath = plotpath+"/"+ HistName;
  mkdir(thiscut_plotpath);

  

  hist_axis(hist_default);

  TLegend *lg= new TLegend(0.2, 0.80, 0.3, 0.90);
  lg->SetFillStyle(0);                                                                                                                            
  lg->SetBorderSize(0);                                                                                                                    
  lg->SetTextSize(Legend_Size);


  TCanvas* c1 = new TCanvas(HistName, "", Canvas_X,Canvas_Y);
  c1->Draw();
  c1->cd();

  canvas_margin(c1);
  
  TH1D *hist_empty = (TH1D*)hist_default->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");
  
  double dx = (hist_empty->GetXaxis()->GetXmax() - hist_empty->GetXaxis()->GetXmin())/hist_empty->GetXaxis()->GetNbins();
  
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  double Ymin = default_y_min;
  double YmaxScale = 2.;

  
  hist_empty->Draw("histsame");
  //hist_default->Draw("hist");
						
  
  TGraphAsymmErrors *gr_ratio_point = new TGraphAsymmErrors(hist_default);
  gr_ratio_point->SetLineWidth(2.0);
  gr_ratio_point->SetMarkerSize(0.);
  gr_ratio_point->SetLineColor(kRed);
  gr_ratio_point->Draw("p0same");
  
  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(LatexTextCMS_X,LatexTextCMS_Y, LatexTextCMS);
  latex_Lumi.SetTextSize(LatexTextLabel_Size);
  if(Era=="2016preVFP")latex_Lumi.DrawLatex(0.7, 0.96, "19.5 fb^{-1} (13 TeV)");
  if(Era=="2016postVFP")latex_Lumi.DrawLatex(0.7, 0.96, "16.8 fb^{-1} (13 TeV)");
  if(Era=="2016") latex_Lumi.DrawLatex(0.7, 0.96, "36.3 fb^{-1} (13 TeV)");
  if(Era=="2017") latex_Lumi.DrawLatex(0.7, 0.96, "41.5 fb^{-1} (13 TeV)");
  if(Era=="2018") latex_Lumi.DrawLatex(0.7, 0.96, "59.9 fb^{-1} (13 TeV)");
  if(Era=="Run2") latex_Lumi.DrawLatex(0.7, 0.96, "137.9 fb^{-1} (13 TeV)");


  lg->SetNColumns(2);
  lg->AddEntry(gr_ratio_point, HistName, "pl");
  lg->Draw();
  mkdir(thiscut_plotpath);

  c1->SaveAs(thiscut_plotpath+"/"+HistName+".png");
  c1->SaveAs(thiscut_plotpath+"/"+HistName+".pdf");

  
}
