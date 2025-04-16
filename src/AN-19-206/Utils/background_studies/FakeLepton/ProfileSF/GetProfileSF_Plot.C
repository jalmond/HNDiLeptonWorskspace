#include "base_functions.h"
#include <cmath>
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString SaveProfile2(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales,TString Era,TString DateTag);

void GetProfileSF_Plot(){
  
  TString Analyzer = "HNL_Lepton_FakeRate";
  TString Plot_Name = "FakeCRCentral_AJ40_MVA_PtPartonUncorr";
  
  TString DateTag = "Oct9";

  vector<TString> Eras = {"2016", "2017","2018"};

  TString LabelForWeb = "HNL_GetProfileSF_Muon_ANv1";
  for (auto year : Eras){

    vector<TString> Bins = {      "MuMu_HNL_ULID_FODATA"    };

        
    for( auto Bin : Bins){
      HNLPlotter Plotter(Analyzer);
      Plotter.SetupPlotter(year,"",Analyzer);
      Plotter.CopyToWebsite = true;
      
      TString path="/data6/Users/jalmond/2020/Plotter/HNDiLeptonWorskspace/InputFiles/MergedFiles/"+Analyzer+"/CheckProfile__/"+DateTag+"/"+year+"/"+Analyzer+"_Data_Muon.root";
      cout << "Accessing file " << path << endl;
      ifstream f(path.Data());
      if(!f.good()) {
	cout << "No File found..." << endl;
	return;
      }

      vector<TProfile*> hists;
   
      cout << "DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtPartonUnCorr" << endl;
      Bin = Bin.ReplaceAll("_DATA","_"+year+"DATA");
      TFile* file = new TFile(path);

      TProfile* dataProf   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtPartonUncorr");
      
      dataProf->GetXaxis()->SetTitle("MVA Score");
      dataProf->GetYaxis()->SetTitle("Average p^{parton}_{T} (GeV)");
      dataProf->GetYaxis()->SetRangeUser(0, 100);

      TProfile* dataProfCorr   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtParton");
      
      hists.push_back(dataProfCorr);
      hists.push_back(dataProf);
      
      Plotter.default_y_min = 0;
      Plotter.default_y_max = 100;
      TString SF ="-999";

      //SaveProfile(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
      //SaveProfile(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales)
      if(year == "2016") SF=SaveProfile2(Plotter,0.72, hists, {"With correction", "Without correction"}, "MeasurementRegion_QCDData_"+Bin+"_"+year, LabelForWeb, {""},year,DateTag);
      else SF=SaveProfile2(Plotter,0.64, hists, {"With correction", "Without correction"}, "MeasurementRegion_QCDData_"+Bin+"_"+year, LabelForWeb, {""},year,DateTag);      
      
      TString IDPrefix = Bin;
      IDPrefix=IDPrefix.ReplaceAll(year+"DATA","");
      
      TString outline = "if(DataYear == "+year;
      outline+=" && IsMuon && (LooseID == \""+IDPrefix + "\"+GetYearString())) return "+SF+";";
      
      cout <<  outline << endl;
      
    }
  }
  
  return;
}



TString SaveProfile2(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales, TString Era, TString DateTag){

  cout    << "################### SaveProfile [" << HistName << "] cut =" <<Cut << "  ###################" << endl;
  cout
    << endl
    << "################### Writing in Directory " << plotter.thiscut_plotpath << " ###################" << endl
    << endl;



  plotter.thiscut_plotpath = plotter.plotpath+"/"+ dirName;
  plotter.mkdir(plotter.thiscut_plotpath);

  TProfile* hist_default = hists[0];

  TLegend *lg = new TLegend(0.55, 0.80, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->SetTextSize(plotter.Legend_Size);

  TCanvas* c1 = new TCanvas(HistName, "", plotter.Canvas_X,plotter.Canvas_Y);
  c1->Draw();
  c1->cd();
  if(plotter.SetLogY)c1->SetLogy();
  canvas_margin(c1);

  TProfile *hist_empty= (TProfile*)hist_default->Clone();
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


  if(1){
    TF1 *g1    = new TF1("g1","pol1");//,0,Cut);                                                                                                                                                                                                                              
    TF1 *g2    = new TF1("g2","pol1");//,Cut,Cut+0.16);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    hists[1]->Fit(g1,"W","",Cut-0.4, Cut);
    hists[1]->Fit(g2,"W+","",Cut, Cut+0.16);

    Double_t p0=g1->GetParameter(0);
    Double_t p1=g1->GetParameter(1);
    Double_t p20=g2->GetParameter(0);
    Double_t p21=g2->GetParameter(1);

    double X1 = p0 + Cut*p1;
    double X2 = p20 + Cut*p21;

    SF=X2/X1;

    double  b = round(SF * 1000.0) / 1000.0;
    SF = b;
    cout << "SF = " << SF << endl;
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

  if(Era == "2016"){
    latex_result.DrawLatex(0.2, 0.7-0.05, Era); 
    latex_result.DrawLatex(0.2, 0.7-0.1, labelSt); 
    latex_result.DrawLatex(0.2, 0.7-0.15, "muon");
    latex_result.DrawLatex(0.2, 0.7-0.2, "WP (0.72)");
  }
  
  else {
    latex_result.DrawLatex(0.2, 0.4-0.05, Era);
    latex_result.DrawLatex(0.2, 0.4-0.1, labelSt);
    latex_result.DrawLatex(0.2, 0.4-0.15, "muon");
    latex_result.DrawLatex(0.2, 0.4-0.2, "WP (0.64)");
  }
    

  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf");
  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;


  return to_string(SF);
}

