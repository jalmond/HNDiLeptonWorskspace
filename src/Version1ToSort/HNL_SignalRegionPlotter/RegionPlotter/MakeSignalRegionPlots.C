#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"
#include "CMS_lumi.h"

void MakeSignalRegionPlots(TString _chan = "Schannel"){ 

  //SR2_MuMu_highmass_same_sign_reco_mllJ_HNtypeI_JA_MuMu_HNTightV1_
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();
  
  // local path names
  TString ENV_FILE_PATH= getenv("INFILE_PATH");
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  TString analysername="HNtypeI_JA";
  
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  // list all masses even tho not all signals are made currently

  vector<TString> ignore_masses = {"100","125","150","200","250","300"};
  if (_chan=="Schannel") ignore_masses = {"125","250","300","500"};
  vector <TString> masses = GetMassType1Strings(ignore_masses);
  vector <double> d_masses = GetMassType1Doubles(ignore_masses);
  
  vector<TString> SR;
  SR.push_back("SR1");
  SR.push_back("SR2");
  //  SR.push_back("SR3");
  //SR.push_back("SR4");
  
  vector <TString> channel;
  //channel.push_back("MuMu");
  //channel.push_back("MupMup");
  //channel.push_back("MumMum");
  channel.push_back("EE");
  //channel.push_back("EpEp");
  //channel.push_back("EmEm");

  vector<TString> muIDs;
  //muIDs.push_back("HNTightV1");
  //muIDs.push_back("HNTightV2");
  muIDs.push_back("POGTightWithTightIso");
  
  vector<TString> elIDs;
  elIDs.push_back("passTightID_nocc");
  elIDs.push_back("HNTight2016");
  elIDs.push_back("passMVAID_iso_WP80");
  elIDs.push_back("passMVAID_iso_WP90");
  elIDs.push_back("passMediumID");
  elIDs.push_back("passTightID");

  vector<TString>  Years = {"2016","2017","2018"};

  //vector<TString>  Hists = {"reco_ml1jj","reco_ml2jj","reco_mlljj","signalbin"};
  vector<TString>  Hists = {"signalbin"};
  
  // loop over SR1/2/3/4
  for(unsigned int y = 0 ; y < Years.size(); ++y){
    for(unsigned int j = 0 ; j < SR.size(); ++j){
      
      // run over EE/MM plus charge seperation
      for(unsigned int k = 0 ; k < channel.size(); ++k){
	
	vector<TString> IDs;
	// get efficiencies for each ID ran based on channel
	if ( channel[k].Contains("E") ) IDs = elIDs;
	else IDs =   muIDs;
	
	TString _sr = SR[j];
	TString _channel = channel[k];
	
	TString sign = "same_sign";
	if(_sr == "SR3") { _sr = "SR1"; sign = "opposite_sign";}
	if(_sr == "SR4") { _sr = "SR2"; sign= "opposite_sign"; }
	
	// canvas for hists
	TString canvasname=_sr+"_highmass_"+sign +"_njets_"+analysername+"_JA_"+_channel;
	//	TCanvas* c1 = new TCanvas(canvasname,canvasname, 800,800);
	//c1->SetLogy();
	vector<Color_t> sighistcolors = GetHistColors(masses.size());
	vector<TGraphAsymmErrors*> _vgraphs;
	
	for(unsigned int l = 0 ; l < IDs.size(); l++){
	  
	  TString _id = IDs[l];

	  for(unsigned int h = 0 ; h < Hists.size(); h++){
	    // setup hist


	    TString histlabel= _sr+"_"+_channel +  +"_nevent_HNtypeI_JA_"+_channel+"_"+_id+"_"+Hists[h];
	    
	    TString sigpath1 = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_100_nlo.root";
	    TString sigpath2 = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_400_nlo.root";
	    TString sigpath3 = ENV_MERGEDFILE_PATH+ "/2016/SIG/"+analysername+"_HN_"+_chan+"_"+_channel+"_1000_nlo.root";
	    TString promptpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_SSPrompt.root";
	    TString cfpath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_CF.root";
	    TString fakepath = ENV_MERGEDFILE_PATH+ "/"+Years[y]+"/HNtypeI_JA_SkimTree_SSNonIso_Fake"+_channel+".root";
	    
	    TFile * fileS1 = new TFile((sigpath1).Data());
	    TFile * fileS2 = new TFile((sigpath2).Data());
	    TFile * fileS3 = new TFile((sigpath3).Data());	  
	    if(CheckFile(fileS1) > 0) continue;
	    if(CheckFile(fileS2) > 0) continue;
	    if(CheckFile(fileS3) > 0) continue;
	    TFile * file_prompt = new TFile((promptpath).Data());
	    TFile * file_fake = new TFile((fakepath).Data());
	    TFile * file_cf = new TFile((cfpath).Data());

	    if(CheckFile(file_prompt) > 0) continue;
	    if(CheckFile(file_fake) > 0) continue;
	    if(CheckFile(file_cf) > 0) continue;

	    //SR2_MuMu_highmass_same_sign_reco_mllJ_HNtypeI_JA_MuMu_HNTightV1_

	    
	    TString _hist = Hists[h];
	    if (_sr == "SR2") _hist = _hist.ReplaceAll("jj","J");
	    TString n_sr_hist = _sr + "_"+_channel + "_highmass/" + _sr + "_highmass_"+_hist+"_HNtypeI_JA_" + _channel + "_"+_id + "_";
	    //SR1_highmass_signalbin_HNtypeI_JA_EE

	    TH1* hnsig1 = GetHist(fileS1,n_sr_hist);
	    TH1* hnsig2 = GetHist(fileS2,n_sr_hist);
	    TH1* hnsig3 = GetHist(fileS3,n_sr_hist);
	    //FormatHist(hnsig,false, sighistcolors[l]);

	    TH1* hnprompt = GetHist(file_prompt,n_sr_hist);
	    TH1* hncf = GetHist(file_cf,n_sr_hist);
	    //FormatHist(hnprompt,false, 870);
	    TH1* hnfake = GetHist(file_fake,n_sr_hist);
	    //FormatHist(hnfake,false, 900);
	    hnprompt->SetFillColor(kSpring-1);
	    hnprompt->SetLineColor(kSpring-1);
	    hncf->SetFillColor(kOrange-1);
            hncf->SetLineColor(kOrange-1);


	    hnfake->SetFillColor(870);
	    hnfake->SetLineColor(870);
	    
	    hnsig1->SetLineColor(kRed);
	    hnsig2->SetLineColor(kBlue);
	    hnsig3->SetLineColor(kGray);

	    hnsig1->SetLineWidth(3.);
	    hnsig2->SetLineWidth(3.);
	    hnsig3->SetLineWidth(3.);

	    hnsig2->Scale(10.);
	    hnsig3->Scale(1000.);

	    THStack *hs = new THStack(_sr+"_"+_channel +"_highmass"+sign +"_nevent_HNtypeI_JA_"+_channel+"_" + _id+"_"+Hists[h],"");
	    
	    hs->Add(hnprompt);
	    hs->Add(hnfake);
	    
	    TCanvas *c_SOnly = new TCanvas(canvasname, canvasname, 900, 800);
	    canvas_margin(c_SOnly);
	    c_SOnly->cd();
	    c_SOnly->Draw();
	    c_SOnly->SetLogy();

	    
	    //CMS_lumi( c_SOnly, 4, 11 );
	    //TH1D *dummy = new TH1D("hist", "", 10000, 0., 100000);
	    //dummy->Draw("hist");

	    float max1=hnfake->GetMaximum();
	    float max2=hnprompt->GetMaximum();

	    if (max1 > max2) hnsig1->GetYaxis()->SetRangeUser(0.1, max1*100);
	    else hnsig1->GetYaxis()->SetRangeUser(0.1, max2*100);

	    
	    hnsig1->GetYaxis()->SetTitle("Events / bin " );
	    hnsig1->Draw("hist");
	    hnsig1->SetTitle("Events");
	    hnsig1->SetTitle("Mass("+_hist+") (GeV)");
	    //hist_axis(dummy);
	    //dummy->GetYaxis()->SetTitleSize(0.06);
	    //dummy->GetYaxis()->SetTitle("Events");
	    //dummy->GetXaxis()->SetTitle("Mass("+_hist+") (GeV)");
	    //dummy->GetXaxis()->SetRangeUser(100., 2000);
	    //dummy->GetYaxis()->SetRangeUser(0.05, 10000.);
	    //dummy->SetTitle("");
	    //dummy->Draw("hist");
	    
	    hs->Draw("histsame");

	    //hnsig1->Draw("lsame");
	    hnsig2->Draw("histsame");
	    hnsig3->Draw("histsame");
	    hnsig1->Draw("histsame");
	    TLegend* legendH;
	    legendH = new TLegend(0.65, 0.75, 0.85, 0.9);
	    legendH->SetFillColor(kWhite);
	    legendH->SetTextSize(0.03);
	    legendH->SetBorderSize(0);
	    legendH->SetTextFont(42);
	    
	    legendH->AddEntry(hnsig1, "m_{N} 100 GeV","l");
	    legendH->AddEntry(hnsig2, "m_{N} 400 GeV","l");
	    legendH->AddEntry(hnsig3, "m_{N} 1000 GeV","l");
	    legendH->AddEntry(hnprompt,"Prompt","f");
	    //legendH->AddEntry(this_hist_cf,"Charge Flip","f");
	    legendH->AddEntry(hnfake,"Fake","f");
	    
	    //AllLegendEntry(legend,this_hist,_id,"l");
	    
	    legendH->Draw();
	    
	    TLatex latex_CMSPriliminary, latex_Lumi;
            latex_CMSPriliminary.SetNDC();
            latex_Lumi.SetNDC();
            latex_CMSPriliminary.SetTextSize(0.035);

            latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS}");

            latex_Lumi.SetTextSize(0.035);
            latex_Lumi.SetTextFont(42);
            if(Years[y]=="2016")latex_Lumi.DrawLatex(0.72, 0.96, "35.9 fb^{-1} (13 TeV)");


	    TString str_channel = _channel + " ("+_id+")";
	    TLatex channelname;
	    channelname.SetNDC();
	    channelname.SetTextSize(0.037);
	    channelname.DrawLatex(0.2, 0.88, str_channel);
	    
	    
	    //dummy->Draw("histsame");
	    MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalPlots/");
	    MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalPlots/" + Years[y]);
	    MakeDir(ENV_PLOT_PATH+FLATVERSION+"/SignalPlots/" + Years[y]+  "/" + _sr);
	    
	    TString save_sg=ENV_PLOT_PATH+FLATVERSION+"/SignalPlots/" + Years[y] + "/" + _sr+"/hist_highmass_"+sign +"_nevents_HNtypeI_JA_"+_channel+"_"+_chan+_id+"_"+_hist+".pdf";
	    c_SOnly->SaveAs(save_sg);
	  }
	}
      }
    } 
  }
}




void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  if(iPosX!=2) t*= 0.7;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV_2016;
      lumiText += " (13 TeV)";
    }
    else if ( iPeriod==5 )
    {
      lumiText += lumi_13TeV_2017;
      lumiText += " (13 TeV)";
    }

  else if ( iPeriod==6 )
    {
      lumiText += lumi_13TeV_2018;
      lumiText += " (13 TeV)";
    }

  else if ( iPeriod==7 )
    {
      lumiText += lumi_13TeV_combined;
      lumiText += " (13 TeV)";
    }


  else if ( iPeriod==8 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV_2016;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if(iPosX==2)  latex.DrawLatex(1-r-0.22,1-t+lumiTextOffset*t, "#mu^{#pm}#mu^{#pm} channel,");
  else  latex.DrawLatex(1-r-0.4,1-t+lumiTextOffset*t, "#mu^{#pm}#mu^{#pm} channel,");



  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(11);
  latex.SetTextSize(cmsTextSize*t);
  latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);



  float posY_ = 1-t+lumiTextOffset*t;


  latex.SetTextAlign(11);
  float posX_ = l +  relPosX*(1-l-r) + 0.06;
  latex.SetTextFont(extraTextFont);
  latex.SetTextSize(extraTextSize*t);
  //latex.SetTextAlign(align_);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  latex.DrawLatex(posX_, posY_, extraText);

return;
}
