#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void IDEfficiencyRun(TString era, vector<TString>  EtaBins, vector<TString> IDStrings, vector<TString> legNames,TString InDir,TString WebSite_Label, TString Dir);

void IDScanEfficiency(){
  
  vector<TString> Eras = {"2016"};//, "2017","2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};

  TString LabelForWeb = "IDEfficiency_2023_July14_Electron";
  

  for (auto Era : Eras) {

    //vector<TString> IDs = {"HNL_ULID_OPT1", "HNL_ULID_OPT2","HNL_ULID_OPT3","HNL_ULID_OPT4","HNL_ULID_OPT5","HNL_ULID_OPT6","HNL_ULID_OPT7","HNL_ULID_OPT8","HNL_ULID_OPT9","HNL_ULID_OPT10","HNL_ULID_OPT11","HNL_ULID_OPT12","HNL_ULID_OPT13","HNL_ULID_OPT14","HNL_ULID_OPT_POG1","HNL_ULID_OPT_POG2","HNL_ULID_OPT_POG3","HNL_ULID_OPT_POG4","HNL_ULID_Run2_OPT","HNL_ULID_2016_OPT","HNL_ULID_2017_OPT","HNL_ULID_2018_OPT","HNL_ULID_2016"};    
    
    vector<TString> BarrelIDs = {"BBv1","BBv2","BBv3","BBv4","BBv5","BBv6","BBv7","BBv8","BBv9","BBv10","BBv11","BBv12","BBv13","BBv14","BBv15","BBv16","BBv17","BBv18","BBv19","BBv20","BBv21","BBv22","BBv23","BBv24","BBv25","BBv26","BBv27","BBv28","BBv29","BBv30","BBv31","BBv32","BBv33","BBv34","BBv35","BBv36","BBv37","BBv38","BBv39"};
    vector<TString> EndcapIDs = {"ECv1","ECv2","ECv3","ECv4","ECv5","ECv6","ECv7","ECv8","ECv9","ECv10","ECv11","ECv12","ECv13","ECv14","ECv15","ECv16","ECv17","ECv18","ECv19","ECv20","ECv21","ECv22","ECv23","ECv24","ECv25","ECv26","ECv27","ECv28","ECv29","ECv30","ECv31","ECv32","ECv33","ECv34","ECv35","ECv36","ECv37","ECv38","ECv39","ECv40", "ECv41","ECv42","ECv43","ECv44","ECv45","ECv46","ECv47","ECv48","ECv49","ECv50","ECv51","ECv52","ECv53","ECv54"};

    for(auto id : BarrelIDs) IDEfficiencyRun ( Era, {"IB","OB"} , {"FINAL_BBID"+id+"_ECIDECv1","HNTightV2", "HNL_Peking_2016"}, {id,"HNTightV2","Peking"}, "MVA_DY_IDOPT" ,    LabelForWeb+"_FinalID","EE_Prompt");                                                                           
    for(auto id : EndcapIDs) IDEfficiencyRun ( Era, {"EC"} , {"FINAL_ECID"+id+"_BBIDBBv1","HNTightV2", "HNL_Peking_2016"}, {id,"HNTightV2","Peking"}, "MVA_DY_IDOPT" ,    LabelForWeb+"_FinalID","EE_Prompt");     


    //for(auto id : IDs) IDEfficiencyRun ( Era, {"IB","OB","EC"} , {id,"HNTightV2", "HNL_Peking_2016"}, {id,"HNTightV2","Peking"}, "MVA_DY_IDOPT" ,    LabelForWeb+"_FinalID","EE_CF");                                                                                                                                                        
    
  }

}


void IDEfficiencyRun(TString era, vector<TString>  EtaBins, vector<TString> IDStrings, vector<TString> legNames, TString InDir, TString WebSite_Label, TString Dir){
  
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
	
	cout << path+"/"+PromptType << " " << Dir+"/Ptbinned_"+EtaBin+"_"+IDs+"_num" << endl;
	TH1D *hist_Numerator     = Plotter.ConstructHist(path+"/"+PromptType,
							 Dir+"/Ptbinned_"+EtaBin+"_"+IDs+"_num");
	
	if(!hist_Numerator) {
	  cout << " --> MISSING "+Dir+"/Ptbinned_"+EtaBin+"_"+IDs+"_num" << endl;
	  return;
	}

	TH1D *hist_Denominator   = Plotter.ConstructHist(path+"/"+PromptType,
							Dir+ "/Ptbinned_"+EtaBin+"_"+IDs+"_denom");

	if(!hist_Denominator) return;

	hist_Numerator->Divide(hist_Denominator);
	hists.push_back(hist_Numerator);
      }
      Plotter.DrawEfficiency(  hists  , legNames, "IDEff_"+InDir+"_"+IDStrings[0]+"_"+EtaBin,    WebSite_Label);
	
    }
  }
  
  return;
}

