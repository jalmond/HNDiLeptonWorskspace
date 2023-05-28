#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void LeptonVarEffPlotsMVAMuMu(){
  
  vector<TString> eras =  {"2017"};
  vector<TString> channels = {"Muons"};//,"EE","EMu"};
  vector<TString> masses= {""};
  
  for (auto year : eras){
    
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    
    TString analysername="HNL_SignalStudies";
    
    TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_Bkg.root";
    
    TFile * file_bkg = new TFile((mc_path).Data());
    
    if(CheckFile(file_bkg) > 0) {
      continue;
    }
    
    for (auto channel : channels){
      for (auto mass : masses){
	
	TString skim="";
	// check which pc is running script to setup local paths
	TString s_hostname = GetHostname();
	
	// local path names
	
	TString ENV_PLOT_PATH = getenv("PLOT_PATH");
	TString FLATVERSION = getenv("FLATVERSION");
	
	
	MakeDir(ENV_PLOT_PATH + FLATVERSION);
	TString input_path = ENV_MERGEDFILE_PATH +"/"+analysername+"/";
	TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";
	
	MakeDir(output);
	output+="/LeptonVarPlotMuons/";
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
	
	
	TString mc_path = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/HNL_SignalStudies_Bkg.root";
	
	TString sig_path100 = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIGMerged/HNL_SignalStudies_Type1_SS.root";

	TFile * file_sig100 = new TFile((sig_path100).Data());

	if(CheckFile(file_sig100) > 0) {
	  continue;
	}
	
	vector<TString> vars = {"B/LepPt_MVA", "EC/LepPt_MVA"};
	
	for (auto var : vars){

	  vector<TString> binlabels = {"15-20","20-30","30-50","50-Inf"};
	  vector<int> low_edge = {3,4, 5 ,7,};
	  vector<int> upper_edge = {3,4,7 ,11};
	  for(int ibin = 0; ibin < 4;  ibin++){
	 
	    TString binlabel = binlabels[ibin];
	    
	    TString save_var = var;
	    save_var = save_var.ReplaceAll("/","_");
	    TString sr_histNom=  "OptMuMu/Sig"+var+"_NoCut";
	    TH1* hn_sig100Nom        = GetHist(file_sig100,sr_histNom);
	    

	    double nom_int = hn_sig100Nom->Integral(low_edge[ibin], upper_edge[ibin]);

	    for(unsigned int ibin=1; ibin < hn_sig100Nom->GetNbinsX()+1; ibin++){
	      cout << ibin << " " << hn_sig100Nom->GetBinLowEdge(ibin) << " "  << hn_sig100Nom->GetBinContent(ibin) <<  endl;
	    }
	    cout <<binlabel  << " nom_int = " << nom_int << endl;
	    TString sr_histFakeNom=  "OptMuMu/Fake"+var+"_NoCut";
	    TH1* hn_FakeNom        = GetHist(file_bkg,sr_histFakeNom);
	    
	    TString sr_histConvNom=  "OptMuMu/Conv"+var+"_NoCut";
	    TH1* hn_ConvNom        = GetHist(file_bkg,sr_histConvNom);
	    
	    double nom_fake_int = hn_FakeNom->Integral(low_edge[ibin], upper_edge[ibin]);
	    double nom_conv_int = hn_ConvNom->Integral(low_edge[ibin], upper_edge[ibin]);
	    
	    //TH1F* h_dummy = new TH1F ("LepPt_DXY","", 46, 0., 46);
	    
	    int n=200;
	    double x[n], y[n], yFake[n],  yConv[n];
	    
	    TString sr_hist_99(""),sr_hist_995(""), sr_hist_95("");

	    for( int j1=0; j1 < n; j1++){
	      double MVA_1 = double(-1+0.01*double(j1));
	      std::string MVA1= std::to_string(MVA_1);


	      TString sr_hist=  "OptMuMu/Sig"+var+"_"+TString(MVA1);
	      TString sr_Fakehist=  "OptMuMu/Fake"+var+"_"+TString(MVA1);
	      TString sr_Convhist=  "OptMuMu/Conv"+var+"_"+TString(MVA1);
	      cout << sr_hist << " " << sig_path100 << endl;
	      TH1* hn_sig100        = GetHist(file_sig100,sr_hist);
	      TH1* hn_Fake        = GetHist(file_bkg,sr_Fakehist);
	      TH1* hn_Conv        = GetHist(file_bkg,sr_Convhist);
	      
	      double binned_int = hn_sig100->Integral(low_edge[ibin], upper_edge[ibin]);
	      double binned_fake_int = hn_Fake->Integral(low_edge[ibin], upper_edge[ibin]);
	      double binned_conv_int = hn_Conv->Integral(low_edge[ibin], upper_edge[ibin]);
	      //h_dummy->SetBinContent(j1+1, 100*(binned_int / nom_int));
	      x[j1] = MVA_1;
	      y[j1]  = 100*(binned_int / nom_int);
	      yFake[j1] =  100*(binned_fake_int / nom_fake_int);
	      yConv[j1] =  100*(binned_conv_int / nom_conv_int);
	      cout << sr_hist << " " << 100*(binned_int / nom_int) << endl;
	      if( (100*(binned_int / nom_int) ) < 95. && sr_hist_95=="") sr_hist_95=TString(MVA1);
	      if( (100*(binned_int / nom_int) ) < 99. && sr_hist_99=="") sr_hist_99=TString(MVA1);
	      if( (100*(binned_int / nom_int) ) < 99.5 && sr_hist_995=="") sr_hist_995=TString(MVA1);
	    }
	    
	    
	    
	    auto g = new TGraph(n,x,y);
	    g->SetLineColor(2);
	    g->SetLineWidth(4);
	    g->SetMarkerColor(kRed);
	    g->SetMarkerSize(1.5);
	    g->SetMarkerStyle(21);
	    
	    auto gFake = new TGraph(n,x,yFake);
	    gFake->SetLineColor(870);
	    gFake->SetLineWidth(4);
	    gFake->SetMarkerColor(870);
	    gFake->SetMarkerSize(1.5);
	    gFake->SetMarkerStyle(21);
	    
	    
	    
	    auto gconv = new TGraph(n,x,yConv);
	    gconv->SetLineColor(kGray);
	    gconv->SetLineWidth(4);
	    gconv->SetMarkerColor(kGray);
	    gconv->SetMarkerSize(1.5);
	    gconv->SetMarkerStyle(21);
	    
	    
	    
	    TString canvasname= sr_histNom+channel;
	    TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	    
	    c1->cd();
	    
	    //h_dummy->Draw("hist");
	    g->Draw("AC");
	    g->GetYaxis()->SetRangeUser(20, 100.);	
	    g->Draw("AC");
	    gFake->Draw("C");
	    gconv->Draw("C");
	    TString cbinlabel=channel;
	    DrawLatexWithLabel(year,cbinlabel,0.65,0.28);
	    
	    DrawLatexWithLabel(year,"99.5% Sig Eff = "+sr_hist_995,0.65,0.24);
	    DrawLatexWithLabel(year,"99% Sig Eff = "+sr_hist_99,0.65,0.21);
	    DrawLatexWithLabel(year,"95% Sig Eff = "+sr_hist_95,0.65,0.18);
	    
	    TLegend *legend = MakeLegend(0.65, 0.35, 0.9, 0.55);
	    legend->AddEntry(g,"Signal","l");
	    legend->AddEntry(gFake,"Fake","l");
	    legend->AddEntry(gconv,"Conv.","l");
	    legend->Draw();
	    
	    TString save_pdf= output + "/LeptonVarEff_"+save_var+"_"+channel+"_"+year+"_"+binlabel+".pdf";
	    TString save_png= output + "/LeptonVarEff_"+save_var+"_"+channel+"_"+year+"_"+binlabel+".png";
	    
	    c1->SaveAs(save_pdf);
	    c1->SaveAs(save_png);
	    
	    system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlotsMuons/'");
	    
	    system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlotsMuons/'");
	    
	    system("scp " +save_pdf+" jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlotsMuons/");
	    system("scp " +save_png + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/LeptonVarEffPlotsMuons/");
	    
	    cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/LeptonVarEffPlots/" << endl;
	  }
	}

	file_sig100->Close();
	delete file_sig100;
	
      }
    }
    
    file_bkg->Close();
    
    delete file_bkg;
  }
  
  
  return;
}

