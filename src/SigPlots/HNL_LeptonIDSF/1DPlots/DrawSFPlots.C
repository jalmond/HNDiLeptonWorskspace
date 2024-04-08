#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNL_Efficiency_Plotter.cc"                                                                       


void DrawConfig(TString year);

void DrawSFPlots(){
  
  DrawConfig("2018");

}

void DrawConfig(TString year){


  vector<TString> eras =  {era};
  
  for (auto year : eras){
    for (auto EtaBin : EtaBins){
      
      HNL_Efficiency_Plotter Plotter("IDEfficiency");
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
      Plotter.DrawIDEfficiencyMuon(  hists  , legNames, "IDEff_"+InDir+"_"+IDStrings[0]+"_"+EtaBin,    WebSite_Label);
        
    }
  }
  




  return;
}



