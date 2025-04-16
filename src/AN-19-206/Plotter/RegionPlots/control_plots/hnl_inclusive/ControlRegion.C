#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"

void RunFunction(bool runPlotter,TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag, vector<TString> Bkgs, TString Region,TString InputList);

void ControlRegionJob(bool runPlotter,TString  DateTag,int nlep,vector<TString> Eras, TString Channel, vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList, TString Flag);


void ControlRegion(){

  // Parse arguments
  bool runPlotter = true;

  
  // Main macro functionality
  if (runPlotter) {
    std::cout << "Running plotter code..." << std::endl;
  }
  
   
  

  TString DATE = "April14";
  vector<TString> Eras =  {"2016postVFP","2017","2018","2016preVFP"};//,"Run2"};


  vector<TString> TriLepReg ={"HNL_TopNP_ThreeLepton_CR", "HNL_WZB_ThreeLepton_CR", "HNL_WZVBF2_ThreeLepton_CR" , 
			      "HNL_WZVBF_ThreeLepton_CR", "HNL_WZ_HighPt_ThreeLepton_CR", "HNL_WZ_SR1_ThreeLepton_CR", 
			      "HNL_WZ_SR3_ThreeLepton_CR", "HNL_ZG_ThreeLepton_CR", "HNL_ZNPEl_ThreeLepton_CR", "HNL_ZNPMu_ThreeLepton_CR","HNL_ZG_HighPt_ThreeLepton_CR",
			      "HNL_WZVBF_METST_ThreeLepton_CR","HNL_WZ_SR1_Inclusive_ThreeLepton_CR","HNL_WZ_SR1_METST_ThreeLepton_CR"};


  vector<TString> QuadLepReg ={"HNL_ZZLoose_FourLepton_CR", "HNL_ZZVBF_FourLepton_CR","HNL_ZZ_FourLepton_CR","HNL_ZZ_HighPt_FourLepton_CR","HNL_ZZ_SR1_FourLepton_CR"};
  
  
  TString Flag = "MultiLepton__";

  for(auto iflav : {"LLL","MuMuMu","EEE","EMuL"}){
    ControlRegionJob(runPlotter,"April14",3, Eras, iflav,{"WZ","WG","ZG","Other_Conv","qqZZ","ggZZ","WW","Top","Other_SS","NonPrompt"}  ,   TriLepReg , "HNL_ControlRegion_CRPlots", "List1","MultiLepton__");
    ControlRegionJob(runPlotter,"April14",3, Eras, iflav,{"WZ_Alt","WG","ZG","Other_Conv","qqZZ","ggZZ","WW","Top","Other_SS","NonPrompt"}  ,   TriLepReg , "HNL_ControlRegion_CRPlots", "List3","MultiLepton__");
  }

  for(auto iflav : {"LLLL","MuMuMuMu","EEEE","EMuLL"}){
    ControlRegionJob(runPlotter, "April14",4, Eras, iflav,{"WZ","WG","ZG","Other_Conv","qqZZ","ggZZ","WW","Top","Other_SS","NonPrompt"} ,   {"HNL_ZZ_FourLepton_CR","HNL_ZZVBF_FourLepton_CR","HNL_ZZ_AK8_FourLepton_CR"} , "HNL_ControlRegion_CRPlots", "List3", "MultiLepton__");      
  }


}

void ControlRegionJob(bool runPlotter, TString  DateTag,int nlep,vector<TString> Eras, TString Channel,vector<TString> Bkgs, vector<TString> Regions, TString Label,TString InputList,TString Flag){
  

  Label = Label + "_"+Flag;
  for (auto ir : Regions)    RunFunction(runPlotter,DateTag,nlep,Eras, {Channel}, Label,Flag, Bkgs,ir, InputList);   
  
}


void RunFunction(bool runPlotter,TString DateFileTag,int nlep,vector<TString> eras,vector<TString> channels, TString PlotterTag, TString Flag,vector<TString> Bkgs, TString Region, TString InputList){
  
 
  for (auto year : eras){
    for (auto channel : channels){
      
      /// list of IDs
      vector<TString> Dirs = {  "HNL_ULIDv2"};

      //// Run Yield print code
      for (const auto& ID : Dirs) {
        // Build the command using a string stream
        std::ostringstream command;
        command << "python3 python/PrintBackgrounds_Run2.py -f " << Flag 
                << " -e " << year 
                << " -r " << Region 
                << " -i " << ID 
                << " -c " << channel 
                << " -d " << DateFileTag 
                << " -a HNL_ControlRegion_Plotter" 
                << " -p " << PlotterTag 
                << " -l " << InputList;
        
        std::string cmd = command.str();
        
        // Output the command for debugging
        std::cout << cmd << std::endl;

        // Execute the command
        int result = std::system(cmd.c_str());
        if (result != 0) {
            std::cerr << "Error: Command failed with status " << result << std::endl;
        }
      }

      if(!runPlotter)  continue;
      
      HNLPlotter Plotter(PlotterTag);
      //// change def
      Plotter.DoDebug=false;
      Plotter.MergeZeroBins = false;
      Plotter.CopyToWebsite = false;
      Plotter.DateFileTag = DateFileTag;

      //// Setup plotter
      Plotter.SetupPlotter(year,"SkimTree_HNMultiLepBDT", "HNL_ControlRegion_Plotter","/"+Flag);
      
      Plotter.samples_to_use = Bkgs;
      
      vector<TString> HPaths,RegionTypes;
      for(auto id : Dirs) HPaths.push_back( Region+"/"+id + "/"+channel);
      for(auto id : Dirs) RegionTypes.push_back( id.ReplaceAll("HNL_ULID_HNL_ULID_","").ReplaceAll("/MuMu","").ReplaceAll("/EE",""));                   
      for(auto ipath : HPaths) cout << "Add " << ipath << endl;
      for(auto ipath :RegionTypes) cout << "RegionTypes" << ipath << endl;
      
      
      Plotter.HistPath= HPaths;
      Plotter.RegionType = RegionTypes;
      
      Plotter.BasicSetup(HNLPlotter::NoLOGY, HNLPlotter::DrawRatio, channel); //// If same setup for all hists in HistPath then use InitialSetup else need to set vector individually
      
      ///// HISTs Setup

      Plotter.AddHist("MainPlots/Lepton_pt" ,"P^{2}_{T} GeV" , "GeV", {0.,10.,15., 25.,30,40,50,75,100., 200.}, 0, 200);

      /*
      Plotter.AddHist("MainPlots/Lepton_1_pt" ,"P^{1}_{T} GeV" , "GeV", {0, 20., 50.,75.,100.,125., 200.,500}, 0, 500);
      Plotter.AddHist("MainPlots/Lepton_2_pt" ,"P^{2}_{T} GeV" , "GeV", {0.,10.,15., 25.,30,40,50,75,100., 200.}, 0, 200);

      
      Plotter.AddHist("Leptons/Lep_1_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
      Plotter.AddHist("Leptons/Lep_2_eta" ,"#eta Lepton" , "int", {2},-2.5,2.5);
      
      Plotter.AddHist("Leptons/SumQ" ,"Sum Charge" , "int", {1},-5,5);

      Plotter.AddHist("Standard/M_ll"  ,"M_{ll}"  , "GeV",    {2},0,500);
      Plotter.AddHist("Mass/DiJet_M_l1W"  ,"M_{l1W}"  , "GeV",    {1}, 0, 2500);
      Plotter.AddHist("Mass/DiJet_M_l2W"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2500);
      Plotter.AddHist("Mass/DiJet_M_llW"  ,"M_{l2W}"  , "GeV",    {1}, 0, 2500);
      Plotter.AddHist("Mass/DiJet_M_l1jj"  ,"M_{l1W}"  , "GeV",    {0,150,200,300,400,600,1000}, 0, 1000);
      Plotter.AddHist("Mass/DiJet_M_lljj"  ,"M_{llW}"  , "GeV",    {0,150,200,300,400,600,1000}, 0, 1000);
      if(nlep==3)   Plotter.AddHist("Mass/M_lll"  ,"M_{lll}"  , "GeV",   {1},70,105);
      if(nlep==4)   Plotter.AddHist("Mass/M_llll"  ,"M_{llll}"  , "GeV",    {2},0,400);
      if(nlep==4)   Plotter.AddHist("Mass/M_BestZ"  ,"M_{bestZ}"  , "GeV",    {1}, 0, 400);
      if(nlep==4)   Plotter.AddHist("Mass/M_OtherZ"  ,"M_{OtherZ}"  , "GeV",    {1}, 0, 400);
      if(nlep==3)   Plotter.AddHist("Mass/M_minOSSF"  ,"M_{minOS}"  , "GeV",    {2}, 0, 400);
      if(nlep==3)   Plotter.AddHist("Mass/M_minSSSF"  ,"M_{minSS}"  , "GeV",    {2}, 0, 400);
      if(nlep==3)   Plotter.AddHist("Mass/Mt_minSSSF"  ,"MT_{minSS}"  , "GeV",    {2}, 0, 400);
      if(nlep==3)   Plotter.AddHist("Mass/Mt_minOSSF"  ,"MT_{minSS}"  , "GeV",    {2}, 0, 400);
      
      Plotter.AddHist("DeltaR/dR_ll" ,"#DeltaR_{LL}"  , "", {5.}, 0, 5);
      Plotter.AddHist("DeltaPhi/dPhi_lep1_lep2" ,"#Delta#phi_{LL}"  , "", {5.}, 0, 5);
      Plotter.AddHist("DeltaR/Jet_dR_jj" ,"#Delta#phi_{jj}"  , "", {5.}, 0, 5);
      Plotter.AddHist("Standard/N_AK4J"  ,"N_{AK4J}"  , "",    {1.}, 0, 10);
      Plotter.AddHist("NObj/N_BJet"  ,"N_{BJ}"  , "",    {1.}, 0, 4);
      Plotter.AddHist("SKEvent/Ev_MET"  ,"Ev_MET"  , "",    {2.}, 0, 400);
      Plotter.AddHist("AK4Jets/Jet_eta"  ,"Jet Eta"  , "",    {5.}, -5, 5);
      Plotter.AddHist("AK4Jets/Jet_pt"  ,"Jet Pt"  , "",    {1.}, 0, 200);
      Plotter.AddHist("SKEvent/Ev_MET2_ST"  ,"MET^{2}/S_{T}","GeV",  {0,2,4,6,8,10,15,20,30,40}, 0, 40);                                                                                                                                              
      Plotter.AddHist("MainPlots/Ev_MET2_ST"  ,"MET^{2}/S_{T}","GeV",  {0,5,10,15,20,30,40,50,75,100}, 0, 100);
      Plotter.AddHist("MainPlots/HT_PT1","H_{T}/p^{lep_{1}}_{T} GeV", "GeV", {0,2,3,4,5,10},0, 10);
      Plotter.AddHist("MainPlots/L_T","L_{T}  GeV", "GeV", {0,50,100,200,500,1000},0, 1000);

      */
      ////// Make list and run plotting
      Plotter.DrawStackPlotsWithData();
      
    }
  }
  
  
  return;
}

