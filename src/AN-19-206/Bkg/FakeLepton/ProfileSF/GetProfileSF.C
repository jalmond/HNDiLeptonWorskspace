#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "HNLPlotter.cc"                                                                       

TString SaveProfile2(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales,TString Era,TString DateTag);

void GetProfileSF(){
  
  TString Analyzer = "HNL_Lepton_FakeRate";
  TString Plot_Name = "FakeCRCentral_AJ40_MVA_PtPartonUncorr";
  
  TString DateTag = "Oct9";

  vector<TString> Eras = {"2016", "2017","2018"};

  TString LabelForWeb = "HNL_GetProfileSF_Muon_ANv1";
  for (auto year : Eras){

    vector<TString> Bins = {"MuMu_HNL_ULID_FO_v0_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v1_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v2_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v3_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v4_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v5_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v6_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v7_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_b_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v8_c_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v9_a_"+year+"DATA",
			    "MuMu_HNL_ULID_FO_v9_b_"+year+"DATA"};
    //"MuMu_HNL_ULID_FO_v9_c_"+year+"DATA"};


    Bins = {      "MuMu_HNL_ULID_FODATA"    };

        
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
    

      //MuMu_HNL_LooseID_FO_v1_2018DATA
      Bin = Bin.ReplaceAll("_DATA","_"+year+"DATA");
      TFile* file = new TFile(path);
      TProfile* dataProf   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtPartonUnCorr");
      dataProf->GetXaxis()->SetTitle("MVA Score");
      dataProf->GetYaxis()->SetTitle("Average p^{parton}_{T} (GeV)");
      dataProf->GetYaxis()->SetRangeUser(0, 100);

      TProfile* dataProfCorr   = (TProfile*) file->Get("DATAProfile/"+Bin+"/FakeCRCentral_AJ40_MVA_PtParton");
      
      hists.push_back(dataProf);
      hists.push_back(dataProfCorr);
      
      Plotter.default_y_min = 0;
      Plotter.default_y_max = 100;
      TString SF ="-999";

      //SaveProfile(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales);
      //SaveProfile(HNLPlotter plotter, double Cut, vector<TProfile*>hists, vector<TString> legname, TString HistName, TString dirName, vector<TString> scales)
      if(year == "2016") SF=SaveProfile2(Plotter,0.72, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCDData_"+Bin+"_"+year, LabelForWeb, {""},year,DateTag);
      else SF=SaveProfile2(Plotter,0.64, hists, {"Data Fake "+Bin, "Data - Prompt Fake "+Bin}, "MeasurementRegion_QCDData_"+Bin+"_"+year, LabelForWeb, {""},year,DateTag);      
      
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
  hist_empty->Draw("histsame");


  double SF(0);
  for(int i=0 ; i < hists.size(); i++){
    hists[i]->SetLineColor(plotter.GetColor(i));
    hists[i]->SetLineWidth(3.);
    TF1 *g1    = new TF1("g1","pol1");//,0,Cut);                                                                                                                                                                                                                                                                                                                                                                                                               
    TF1 *g2    = new TF1("g2","pol1");//,Cut,Cut+0.16);                                                                                                                                                                                                                                                                                                                                                                                                        
    hists[i]->Fit(g1,"W","",Cut-0.4, Cut);
    hists[i]->Fit(g2,"W+","",Cut, Cut+0.16);

    Double_t p0=g1->GetParameter(0);
    Double_t p1=g1->GetParameter(1);
    Double_t p20=g2->GetParameter(0);
    Double_t p21=g2->GetParameter(1);

    double X1 = p0 + Cut*p1;
    double X2 = p20 + Cut*p21;

    SF=X2/X1;

    cout << "SF = " << SF << endl;
    hists[i]->Draw("histsameE0");
    hists[i]->Draw("histsame");
    lg->AddEntry(hists[i], legname[i],"l");
  }
  lg->Draw();

  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_CMSPriliminary.SetTextSize(plotter.LatexTextCMS_Size);
  latex_CMSPriliminary.DrawLatex(plotter.LatexTextCMS_X,plotter.LatexTextCMS_Y, plotter.LatexTextCMS);

  TLatex latex_result;
  latex_result.SetNDC();
  latex_result.SetTextSize(0.03);

  for(unsigned int il =0 ; il < scales.size(); il++) latex_result.DrawLatex(0.2, 0.9-0.05*il, scales[il]);
  TString labelSt= "SF = " + to_string(SF);
  latex_result.DrawLatex(0.2, 0.9-0.1, labelSt); 

  c1->SaveAs(plotter.thiscut_plotpath+"/"+HistName+"_"+DateTag+".pdf");
  cout << "Run rsync -av -e \"ssh -p 1240 \" jalmond@147.47.242.42:" << plotter.syncpath <<  " TamsaOutput/Plots/" << endl;


  return to_string(SF);
}

