#include "base_functions.h"
#include <cmath>
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString SaveHist2(HNLPlotter plotter,  vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales,TString Era,TString DateTag);

TH1D * GetFakeHist(TString hist_T, TString hist_L, TString fdata, TString fmc);


TH1D * GetFakeHist(HNLPlotter Plotter, TString hist_T, TString hist_L, TString fdata, TString fmc){

  cout << hist_T << " " << fdata<<  endl;
  TH1D *hist_data_T  = Plotter.ConstructHist( fdata,hist_T);
  TH1D *hist_data_L  = Plotter.ConstructHist( fdata,hist_L);

  TH1D *hist_mc_T  = Plotter.ConstructHist( fmc,hist_T);
  TH1D *hist_mc_L  = Plotter.ConstructHist( fmc,hist_L);
  
  hist_data_T->Add(hist_mc_T,-1);
  hist_data_L->Add(hist_mc_L,-1);

  hist_data_T->Divide(hist_data_L);
  
  return hist_data_T;
 
}



void Syst_Muon(){
  
  TString Analyzer = "HNL_Lepton_FakeRate";
  
  TString DateTag = "Oct11";
  
  vector<TString> Eras = {"Run2"};

  TString LabelForWeb = "HNL_GetFake_Syst_Muon_ANv1";


  for (auto year : Eras){
    
    TString Era = year;

    TString data_path = "/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/src/AN-19-206/Bkg/FakeLepton/Syst/Data/FakeSystData_"+Era+".root";

    vector<TString> Bins = {      ""    };
        
    for( auto Bin : Bins){
      
      HNLPlotter Plotter("Fake");
      Plotter.SetupPlotter(year,"",Analyzer);
      Plotter.CopyToWebsite = true;
      
      cout << "Accessing file " << data_path << endl;
      ifstream f(data_path.Data());
      if(!f.good()) {
	cout << "No File found..." << endl;
	return;
      }

      TString Pre_Nom = "ChannelCutFlow/HNL_ULID/MuMu/ChannelDependant_Presel";
      TH1D *Pre_hist_nom  = Plotter.ConstructHist(data_path,Pre_Nom );

      TString Nom = "ChannelCutFlow/HNL_ULID/MuMu/SR_Summary";
      TH1D *hist_nom  = Plotter.ConstructHist(data_path,Nom );


      vector<TString> Sys = {"Syst_LIDUp","Syst_LIDDown","Syst_AJ30","Syst_AJ60","Syst_FRUp","Syst_FRDown","Syst_PSFUp","Syst_PSFDown"};
      for(auto is : Sys){
	TString Pre_Sys = "ChannelCutFlow/"+is+"HNL_ULID/MuMu/ChannelDependant_Presel";
     
	TH1D *Pre_hist_Syst  = Plotter.ConstructHist(data_path,Pre_Sys );
	Pre_hist_Syst->Divide(Pre_hist_nom);
	
	for(int i = 1; i < Pre_hist_Syst->GetNbinsX()+1; i++){
	  if(i==1) cout << is << "  Presel error = " << Pre_hist_Syst->GetBinContent(i) << endl;
	}
	
      
	TString SysName = "ChannelCutFlow/"+is+"HNL_ULID/MuMu/SR_Summary";
	TH1D *hist_Syst  = Plotter.ConstructHist(data_path,SysName );
	
	hist_Syst->Divide(hist_nom);


	for(int i = 1; i < hist_Syst->GetNbinsX()+1; i++){
	  if(i==1) cout << is << "  SR1 error = " << hist_Syst->GetBinContent(i) << endl;
	  if(i==2) cout << is << "  SR2 error = " << hist_Syst->GetBinContent(i) << endl;
	  if(i==3) cout << is << " SR3 error = " << hist_Syst->GetBinContent(i) << endl;
	} 
      }

      /*TString dirName="PtParton_Fake_Muon_Syst";
      Plotter.thiscut_plotpath = Plotter.plotpath+"/"+ dirName;
      Plotter.mkdir(Plotter.thiscut_plotpath);
      
      TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->SetTextSize(Plotter.Legend_Size);

      TString HistName = Era+"_SystFake_Muon";

      
      SaveHist2(Plotter, {hist_Syst_IDUp,hist_Syst_IDDown,hist_Syst_AJUp,hist_Syst_AJDown}, {"DeepJet Up","DeepJet Down","AJ30","AK40"}, HistName, dirName, {}, "2018", "Oct11");
      */

    }
  }
  
  return;
}



TString SaveHist2(HNLPlotter plotter,  vector<TH1D*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, TString Era, TString DateTag){

  cout
    << endl
    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl
    << endl;



  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  TH1D* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

  TH1D *hist_empty= (TProfile*)hist_default->Clone();
  hist_empty->SetName("DUMMY_FOR_AXIS");
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);

  double Ymin = plotter.default_y_min+0.000001;
  double YmaxScale =0.000001;

  for(auto i : hists)  if(i->GetMaximum() > YmaxScale) YmaxScale = i->GetMaximum()*plotter.Hist_YAxis_MaxScale;

  if(plotter.default_y_max > 0) YmaxScale = plotter.default_y_max;

  cout << "Ymin = " << Ymin << " YmaxScale = " << YmaxScale << endl;
  hist_empty->GetYaxis()->SetRangeUser(Ymin, YmaxScale);

  hist_axis(hist_empty);

  hists[0]->SetLineStyle(4);
  //  hists[1]->SetLineColor(plotter.GetColor(i));
  hist_empty->Draw("histsame");

  double SF(0);
  for(int i=0 ; i < hists.size(); i++){

    hists[i]->SetLineWidth(3.);
    hists[i]->Draw("histsame");

  }


  lg->AddEntry(hists[0], legname[0],"l");
  lg->AddEntry(hists[1], legname[1],"l");
  lg->Draw();

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(0.03);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMS);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.025);

  
  for(unsigned int il =0 ; il < scales.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, scales[il]);
  TString labelSt= "Correction factor = " + to_string(SF);
  labelSt=labelSt.ReplaceAll("000","");

    

  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf");
  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;


  return to_string(SF);
}

