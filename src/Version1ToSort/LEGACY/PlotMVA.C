#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void PlotMVA(TString channel="muon", TString year="2017"){
  

  TString skim="SkimTree_HNMultiLep";
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  TString analysername="HNL_Signal";

  vector<TString> code_names= {"HNL_Signal"};
  vector<TString> channel_names= {"muon","electron"};

  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  if(std::find(channel_names.begin(), channel_names.end(), channel) != channel_names.end()) cout <<	"Running with channel " <<  channel <<	endl;
  else {cout << "Error in input of _chan: " << channel << endl;  for (auto i: channel_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("SKFLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/CutOpt/";
  MakeDir(output);

  output+=channel+"/";
  MakeDir(output);
  output+=year+"/";
  MakeDir(output);

  cout << "FakerateType1::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  TString data_path ="/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_Signal/"+year+"/HNL_Signal_SkimTree_HNMultiLep_bkg.root";
  TString signal_path ="/Users/john/GIT/HNDiLeptonWorskspace/InputFiles/rootfiles/Run2UltraLegacy_v2_Default/HNL_Signal/"+year+"/HNL_Signal.root";
  
  TFile * file_data = new TFile((data_path).Data());
  if(CheckFile(file_data) > 0) {
    file_data->Close();
    delete file_data;
    return;
  }

  TFile * file_sig = new TFile((signal_path).Data());
  if(CheckFile(file_sig) > 0) {
    file_sig->Close();
    delete file_sig;
    return;
  }
  
  vector <TString> etabins = {"eta1","eta2","eta3"};
  vector <TString> ptbins  = {"10_15","15_20","20_30","30_40","40_50","50_100","100_2000"};
  vector <TString> selections = {"MVA_J","MVA_WW","MVA_AK8"};
  for (auto ieta : etabins){
    for (auto ipt : ptbins){
      for (auto isel : selections){


	// canvas for hists                                                                                                                                                         
	TString canvasname= channel+ieta+ipt+isel;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 1200,800);
	c1->cd();
	
	TString histname="MVA_"+ieta+"_pt_"+ipt;
	TH1D* data_hist = GetHist(file_data,isel+"/"+histname);
	TH1D* data_hist_clone = (TH1D*)(data_hist->Clone(isel+"_"+histname+"clone"));
	TH1D* sig_hist = GetHist(file_sig,"MVA/"+histname);
	NormHist(data_hist);
	NormHist(sig_hist);

	sig_hist->SetLineColor(kRed);
	data_hist->SetLineColor(kBlue);
	data_hist->SetLineWidth(3.);

	TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
	legend->AddEntry(data_hist, "Bkg "+isel,"l");
	legend->AddEntry(sig_hist, "Sum Sig. "+isel,"l");
	c1->cd();

	if(data_hist->GetMaximum() > sig_hist->GetMaximum()) sig_hist->GetYaxis()->SetRangeUser(0., data_hist->GetMaximum()*1.1);

	sig_hist->GetXaxis()->SetTitle("MVA score");
	//	sig_hist->SetTitle
	sig_hist->Draw("hist");
	data_hist->Draw("histsame");
	
	TString _leptype = "Lep Type " ;

	c1->Update();
        c1->RedrawAxis();
	string s_max ="";
	string s_lr ="";
	string s_hr ="";
	if(1){
	  double FIGURE2_RATIO = 0.25;
	  double SUBFIGURE_MARGIN = 0.0;
	  c1->SetBottomMargin(FIGURE2_RATIO);
	  TPad *p = GetPad(SUBFIGURE_MARGIN,FIGURE2_RATIO);
	  p->Draw();
	  p->cd();
	  p->SetTicks(0,1);

	  cout << sig_hist->GetMaximum() << " s max " << " bin = " << sig_hist->GetMaximumBin() << endl;

	  TH1D* sob_hist_clone = (TH1D*)(sig_hist->Clone(isel+"_"+histname+"clone_sob"));
	
	  double max_sob=0.;
	  double max_binV=0.;
	  double lowrange_binV=0.;
	  double highrange_binV=0.;
	  for(unsigned int ibin=1; ibin < data_hist->GetXaxis()->GetNbins()+1; ibin++){
	    double S= sig_hist->Integral(ibin,data_hist->GetXaxis()->GetNbins());
	    double B= sqrt(data_hist_clone->Integral(ibin,data_hist->GetXaxis()->GetNbins()) +1);

	    if (S/B > max_sob){
	      cout << "S/B = " << S/B << endl;
	      max_sob = S/B;
	      max_binV = data_hist_clone->GetBinLowEdge(ibin);
	    }
	    cout << "bin " << ibin << " S/sqrtB = " <<   S/B  << endl;
	    sob_hist_clone->SetBinContent(ibin,S/B);
	    
	  }

          for(unsigned int ibin=1; ibin < data_hist->GetXaxis()->GetNbins()+1; ibin++){

	    double s_b = sob_hist_clone->GetBinContent(ibin);
	    cout << ibin << " s_b = " << s_b << " " <<  "0.95*max_sob = " << 0.95*max_sob << endl;
	    if (s_b > 0.95*max_sob){
	      if(lowrange_binV==0)lowrange_binV=data_hist_clone->GetBinLowEdge(ibin);
	      highrange_binV=data_hist_clone->GetBinLowEdge(ibin);
	    }	    
	  }
	  
	  s_max = std::to_string(max_binV);
	  s_lr = std::to_string(lowrange_binV);
	  s_hr = std::to_string(highrange_binV);
	  
          for(unsigned int ibin=1; ibin < data_hist->GetXaxis()->GetNbins()+1; ibin++) cout << ibin << " sob = " << sob_hist_clone->GetBinContent(ibin) << endl;

	  
	  TGraphAsymmErrors * gratio = new TGraphAsymmErrors(sob_hist_clone);
	  sob_hist_clone->GetYaxis()->SetRangeUser(0., max_sob*1.1);
	  sob_hist_clone->GetYaxis()->SetTitle("S/sqrt(B)");
	  sob_hist_clone->GetYaxis()->SetNdivisions(3);
	  sob_hist_clone->GetXaxis()->SetNdivisions(5);

	  sob_hist_clone->Draw("p hist");
	  sob_hist_clone->Draw("same 9p hist ");
	  
	  gratio->SetLineWidth(2.0);
	  gratio->SetMarkerSize(0.);
	  gratio->Draw(" p0" );
	
	  c1->Update();
	  c1->RedrawAxis();
	  //gPad->RedrawAxis();
	}

	c1->Modified();
	
        DrawLatexWithLabel(year,"S/B range = "+s_lr + " - " +s_hr + "("+s_max+")",0.25,0.83);
        DrawLatexWithLabel(year,ieta + "_pt"+ipt,0.25,0.78);
        DrawLatexWithLabel(year,isel,0.25,0.73);

	legend->Draw();
	
      
	TString save_sg= output + "/histname_"+channel + "_"+year+"_"+ieta+"_"+ipt+"_"+isel+".pdf";


	
	c1->SaveAs(save_sg);
	OutMessage("GetSignalEfficiency",save_sg);
	delete c1;
      }
    }
  }
  file_data->Close();
  
  delete file_data;

  return;
}
