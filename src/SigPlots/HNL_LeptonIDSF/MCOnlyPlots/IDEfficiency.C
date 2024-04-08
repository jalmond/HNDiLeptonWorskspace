#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void IDEfficiencyRun(TString era, vector<TString>  EtaBins, vector<TString> IDStrings, vector<TString> legNames,TString InDir,TString WebSite_Label);

void IDEfficiency(){
  
  vector<TString> Eras = {"2017"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "IDEfficiency_2023_July4_ElectronConv";
  
  //for (auto Era : Eras) IDEfficiencyRun ( Era, {"IB"} , {"HNTightV2","MVALoose_ElectronFakev4_neg0p4","MVALoose_ElectronFakev4_neg0p1", "MVALoose_ElectronFakev4_0p2"}, {"HNTightV2","BDT_{Fake v4} > - 0.4", "BDT_{Fake v4} > -0.1","BDT_{Fake v4} > 0.2"},  LabelForWeb);

  //for (auto Era : Eras) IDEfficiencyRun ( Era, {"IB","OB","EC"} , {"HNTightV2",	"HNL_ULID_CF",	"HNL_ULID_Conv",	"HNL_ULID_Fake"},    {"HNTightV2", 	"HNL_ULID_CF",	"HNL_ULID_Conv",	"HNL_ULID_Fake"},    "MVA_Template",    LabelForWeb);    

  //for (auto Era : Eras) IDEfficiencyRun ( Era, {"IB","OB","EC"} , {"MVALoose_ElectronCFv2_0","MVALoose_ElectronCFEDv2_0","MVALoose_ElectronCFEDv2p1_0","MVALoose_ElectronCFEDv2p2_0", "MVALoose_ElectronCFEDv2p1_0","MVALoose_ElectronCFEDv2p2_0"},    {"MVALoose_ElectronCFv2_0","MVALoose_ElectronCFEDv2_0","MVALoose_ElectronCFEDv2p1_0","MVALoose_ElectronCFEDv2p2_0", "MVALoose_ElectronCFEDv2p1_0","MVALoose_ElectronCFEDv2p2_0"},    "MVA_CF_Template",    LabelForWeb);    

  
  for (auto Era : Eras) {

    vector<TString> IDs = {"HNL_ULID_"+Era+"_OPT","HNL_ULID_2016","HNL_ULID_Run2_OPT","HNTightV2"};
    

    
    //IDEfficiencyRun ( Era, {"IB","OB","EC"} , ConvIDs,ConvIDs, "MVA_DY_CF_Template_IDOPT" ,    LabelForWeb+"_Conv");
    
    vector<TString> FakeIDs = {"HNL_ULID_Fake_VL","HNL_ULID_Fake_L","HNL_ULID_Fake_M", "HNL_ULID_Fake_T", "HNL_ULID_Fake_VT"};
    //IDEfficiencyRun ( Era, {"IB","OB","EC"} , FakeIDs,FakeIDs, "MVA_DY_CF_Template_IDOPT" ,    LabelForWeb+"_Fake");                                                                                                                                                        

    vector<TString> CFIDs = {"HNL_ULID_CFv2","HNL_ULID_CFv2p1","HNL_ULID_CFv2p2", "HNL_ULID_CFEDv2","HNL_ULID_CFEDv2p1","HNL_ULID_CFEDv2p2"};//"HNL_ULID_CF_VL","HNL_ULID_CF_L","HNL_ULID_CF_M","HNL_ULID_CF_T"};
    IDEfficiencyRun ( Era, {"IB","OB","EC"} , CFIDs,CFIDs, "MVA_DY_CF_Template_IDOPT" ,    LabelForWeb+"_CFv2");

    
  }

}


void IDEfficiencyRun(TString era, vector<TString>  EtaBins, vector<TString> IDStrings, vector<TString> legNames, TString InDir, TString WebSite_Label){
  
  vector<TString> eras =  {era};
  
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      
      HNLPlotter Plotter("IDEfficiency");
      Plotter.SetupPlotter(year,"","HNL_LeptonIDSF");
      Plotter.CopyToWebsite = true;
      
      TString path="/data6/Users/jalmond/SKFlatOutput//Run2UltraLegacy_v3/HNL_LeptonIDSF/"+year;
      
      TString PromptType="HNL_LeptonIDSF_SkimTree_DileptonBDT_DYJets.root";
      vector<TH1D*> hists;

      for(auto IDs : IDStrings){      
	
	TH1D *hist_Numerator     = Plotter.ConstructHist(path+"/"+PromptType,
							 "EE/Ptbinned_"+EtaBin+"_"+IDs+"_num");
	
	if(!hist_Numerator) {
	  cout << " --> MISSING EE/Ptbinned_"+EtaBin+"_"+IDs+"_num" << endl;
	  return;
	}

	TH1D *hist_Denominator   = Plotter.ConstructHist(path+"/"+PromptType,
							 "EE/Ptbinned_"+EtaBin+"_MVALoose_denom");

	if(!hist_Denominator) return;

	hist_Numerator->Divide(hist_Denominator);
	hists.push_back(hist_Numerator);
      }
      Plotter.DrawEfficiency(  hists  , legNames, "IDEff_"+InDir+"_"+EtaBin,    WebSite_Label);
	
    }
  }
  
  return;
}

