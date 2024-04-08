#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
 #include "HNLPlotter.cc"                                                                       

void IDEfficiencyRun(TString era, vector<TString>  EtaBins, vector<TString> IDStrings, vector<TString> legNames,TString InDir,TString WebSite_Label);

void IDScanEfficiencyConv(){
  
  vector<TString> Eras = {"2016", "2017" , "2018"};//","2016","2018"};//postVFP","2016preVFP"};//"2016","2017","2018"};

   TString LabelForWeb = "IDEfficiency_2023_ElectronConv_Kuly9";


   for (auto Era : Eras) {

     vector<TString> Cuts = {"slopcut1","slopcut2","slopcut3","slopcut4","slopcut5","slopcut6"};//"neg0p7", "neg0p6","neg0p5","neg0p4","neg0p3","neg0p2","neg0p1","0","0p1","0p2","0p3"};

     vector<TString> IDs = {"Conv_v2","Conv_EDv2"};

     
     for(auto id : IDs) {
       for(auto Cut : Cuts) {
	 IDEfficiencyRun ( Era, {"IB","OB","EC"} , {id+"_"+Cut}, {id+"_"+Cut}, "MVA_DY_IDOPT" ,    LabelForWeb+"_Conv"); 
       }
    }
    
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
      
      TString PromptType="HNL_LeptonIDSF_SkimTree_DileptonBDT_DYJetsMerged.root";
      vector<TH1D*> hists;

      for(auto IDs : IDStrings){      
	
	TH1D *hist_Numerator     = Plotter.ConstructHist(path+"/"+PromptType,
							 "EE/Ptbinned_"+EtaBin+"_"+IDs+"_num");
	
	if(!hist_Numerator) {
	  cout << " --> MISSING EE/Ptbinned_"+EtaBin+"_"+IDs+"_num" << endl;
	  return;
	}

	TH1D *hist_Denominator   = Plotter.ConstructHist(path+"/"+PromptType,
							 "EE/Ptbinned_"+EtaBin+"_"+IDs+"_denom");

	if(!hist_Denominator) return;

	hist_Numerator->Divide(hist_Denominator);
	hists.push_back(hist_Numerator);
      }
      Plotter.DrawEfficiency(  hists  , legNames, "IDEff_"+InDir+"_"+IDStrings[0]+"_"+EtaBin,    WebSite_Label);
	
    }
  }
  
  return;
}

