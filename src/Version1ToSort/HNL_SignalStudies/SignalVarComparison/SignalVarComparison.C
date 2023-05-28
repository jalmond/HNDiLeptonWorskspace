#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void SignalVarComparison(){
  
  vector<TString> eras =  {"2017"};
  
  for (auto year : eras){
    
    TString ENV_MERGEDFILE_PATH = getenv("FILE_MERGED_PATH");
    
    TString analysername="HNL_SignalStudies";
    

    TString channel ="Muon";
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
    output+="/SignalVarComparison/";
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
    
    
    TString sig_pathDY = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNL_SignalStudies_DYTypeI_DF.root";
    TFile * file_sigDY = new TFile((sig_pathDY).Data());	if(CheckFile(file_sigDY) > 0) 	  continue;
    
    TString sig_pathVBF = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNL_SignalStudies_VBFTypeI_DF.root";
    TFile * file_sigVBF = new TFile((sig_pathVBF).Data());  if(CheckFile(file_sigVBF) > 0)    continue;
    
    TString sig_pathSSWW = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/HNL_SignalStudies_SSWWTypeI.root";
    TFile * file_sigSSWW = new TFile((sig_pathSSWW).Data());  if(CheckFile(file_sigSSWW) > 0)    continue;

    
    
    vector<TString> vars = {"Reliso_mu"};
    vector<TString> bins = {"barrel_ptbin1","barrel_ptbin2","barrel_ptbin3", "endcap_ptbin1","endcap_ptbin2","endcap_ptbin3"};
    
    for (auto var : vars){
      for (auto bin : bins){
      
	TString save_var = var;
	TString sr_histNom=  "Muons/"+var+"_muonSignal_"+bin;
	TString sr_hist=  "Muons/"+var+"_muonSignal";
	cout << sr_histNom << endl;
	
	
	TH1* hn_sigDYNom        = GetHist(file_sigDY,sr_histNom);
	TH1* hn_sigVBFNom        = GetHist(file_sigVBF,sr_histNom);
	TH1* hn_sigSSWWNom        = GetHist(file_sigSSWW,sr_histNom);

	TH1* hn_sigDY        = GetHist(file_sigDY,sr_hist);
	TH1* hn_sigVBF        = GetHist(file_sigVBF,sr_hist);
	TH1* hn_sigSSWW        = GetHist(file_sigSSWW,sr_hist);
	
	cout << "Fraction  of DY GeV DY [" << bin << " <<] is " << hn_sigDYNom->Integral()/hn_sigDY->Integral()<< endl;
	cout << "Fraction  of VBF GeV DY [" << bin << " <<] is " << hn_sigVBFNom->Integral()/hn_sigVBF->Integral()<< endl;
	cout << "Fraction  of SSWW GeV DY [" << bin << " <<] is " << hn_sigSSWWNom->Integral()/hn_sigSSWW->Integral()<< endl;
	
	double fracDY = 100*hn_sigDYNom->Integral()/hn_sigDY->Integral();
	double fracVBF = 100*hn_sigVBFNom->Integral()/hn_sigVBF->Integral();
	double fracSSWW = 100*hn_sigSSWWNom->Integral()/hn_sigSSWW->Integral();
	
	hn_sigDYNom->Scale(1./hn_sigDYNom->Integral());
	hn_sigVBFNom->Scale(1./hn_sigVBFNom->Integral());
	hn_sigSSWWNom->Scale(1./hn_sigSSWWNom->Integral());
	
	
	hn_sigDYNom->SetLineColor(kRed);
	hn_sigVBFNom->SetLineColor(kBlue);
	hn_sigSSWWNom->SetLineColor(kGreen+2);
	
	TString canvasname= sr_histNom+channel;
	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	
	c1->cd();

	hn_sigDYNom->SetLineWidth(2.);
	hn_sigVBFNom->SetLineWidth(2.);
	hn_sigSSWWNom->SetLineWidth(2.);
	
	hn_sigDYNom->GetXaxis()->SetRangeUser(0., 0.4);
	hn_sigDYNom->GetYaxis()->SetRangeUser(0., 1);
	hn_sigDYNom->Draw("hist");
	hn_sigVBFNom->Draw("histsameE");
	if(!bin.Contains("ptbin1"))hn_sigSSWWNom->Draw("histsame");
	DrawLatexWithLabel(year,bin ,0.65,0.81);
	DrawLatexWithLabel(year,"% DY GeV=" +TString(to_string(fracDY)) ,0.65,0.71);
	DrawLatexWithLabel(year,"% VBF GeV=" +TString(to_string(fracVBF)) ,0.65,0.65);
	if(!bin.Contains("ptbin1"))DrawLatexWithLabel(year,"% SSWW GeV=" +TString(to_string(fracSSWW)) ,0.65,0.60);
	
	TLegend *legend = MakeLegend(0.45, 0.35, 0.9, 0.55);
	legend->AddEntry(hn_sigDYNom,"DY Mean=" + TString(to_string(hn_sigDYNom->GetMean(1))+"+/- "+to_string(hn_sigDYNom->GetMeanError(1))),"l");
	legend->AddEntry(hn_sigVBFNom,"VBF Mean=" + TString(to_string(hn_sigVBFNom->GetMean(1))+"+/- "+to_string(hn_sigVBFNom->GetMeanError(1))),"l");
	if(!bin.Contains("ptbin1"))legend->AddEntry(hn_sigSSWWNom,"SSWW Mean=" + TString(to_string(hn_sigSSWWNom->GetMean(1))+"+/- "+to_string(hn_sigSSWWNom->GetMeanError(1))),"l");
	
	
	legend->Draw();
	
	TString save_pdf= output + "/"+save_var+bin+"_"+channel+"_"+year+".pdf";
	TString save_png= output + "/"+save_var+bin+"_"+channel+"_"+year+".png";
	
	c1->SaveAs(save_pdf);
	c1->SaveAs(save_png);
	
	system("ssh jalmond@lxplus.cern.ch 'mkdir -p /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalVarComparison/'");
	
	system("ssh jalmond@lxplus.cern.ch 'cp  /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalStudies/SignalSplit/index.php /afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalVarComparison/'");
	
	system("scp " +save_pdf+" jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalVarComparison/");
	system("scp " +save_png + " jalmond@lxplus.cern.ch:/afs/cern.ch/user/j/jalmond/www/SNU/WebPlots/HNL/SignalVarComparison/");
	
	cout << "https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/HNL/SignalVarComparison/" << endl;
      }
    }
    
    
    file_sigDY->Close();	delete file_sigDY;
    file_sigVBF->Close();	delete file_sigVBF;
    file_sigSSWW->Close();	delete file_sigSSWW;
    
  }
  
  
  return;
}

