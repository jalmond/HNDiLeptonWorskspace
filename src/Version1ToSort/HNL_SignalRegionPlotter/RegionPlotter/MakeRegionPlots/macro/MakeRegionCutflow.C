#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void MakeTexFile(map< TString, TH1D * > hs, TString outp,TString SR);

void MakeRegionPlots(TString config_file="config.txt"){
  
  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();
  
  vector<TString> code_names= {"HNtypeI_Dilepton","HNtypeI_JA"};

  vector<TString> channel_names= {"Schannel","Tchannel"};
  vector<TString> range_names = {"all","low","high"};
  
  map<TString,TString> configmap = ConfigMap(config_file);
  
  map<TString,int> configmapInt = ConfigMapInt(config_file);
  map<TString,double> configmapDouble = ConfigMapDouble(config_file);
  map<TString,TString> bkgmap    = BkgConfigMap(config_file);
  map<TString,Color_t> colormap  = BkgColorMap(config_file);
  map<TString,Color_t> sigcolormap  = SigColorMap(config_file);
  map<TString,TString>  sigmap   = SigConfigMap(config_file);
  if(configmap.size()==0) return;
  

  TString savetag      = configmap["savetag"];
  TString showdata     = configmap["showdata"];
  TString plotsig      = configmap["plotsig"];
  TString analysername = configmap["analysername"];
  if(!CheckInput(code_names,configmap["analysername"], "analysername"))  return;
  
  TString plot_dir     = configmap["plot_dir"];
  TString cut_dir      = configmap["cut_dir"];
  TString data_file    = configmap["data_file"];
  if(!CheckFileInput(configmap["data_file"] ))  return;
  vector<TString> dir_name = GetDirName(configmap["data_file"]);
  if(!CheckInput(dir_name,configmap["cut_dir"], "cutname" ))  return;

  
  int  rbin         = configmapInt["rebin"];
  int  logy         = configmapInt["logy"];
  
  // double inouts
  double  xmin         = configmapDouble["xmin"];
  double  xmax         = configmapDouble["xmax"];


  TString year         = configmap["year"];
  TString id           = configmap["id"];
  TString flavour      = configmap["flavour"];
  vector<TString> id_name  = GetIDNames(configmap["data_file"],cut_dir,analysername,flavour);
  if(!CheckInput(id_name, id, "ID" ))  return;  
  TString histname           = configmap["histname"];
  vector<TString> hist_names = GetHistNames(configmap["data_file"],cut_dir,analysername,flavour,id_name[0]);


  if(!CheckInput(hist_names, histname, "histname" ))  return;

  cout << "-------------------------------------------" << endl;
  cout << "analysername = " << analysername << endl;
  cout << "plot_dir     = " << plot_dir << endl;
  cout << "cut_dir      = " << cut_dir << endl;
  cout << "data_file    = " << data_file << endl;
  cout << "year         = " << year << endl;
  cout << "ID           = " << id   << endl;
  cout << "histname     = " << histname   << endl;
  cout << "showdata     = " << showdata<< endl;
  cout << "logy         = " << logy<< endl;
  cout << "plotsig      = " << plotsig<< endl;
  cout << "Range xmin   = " << xmin << endl;
  cout << "Range xmax   = " << xmax << endl;

  bool PlotSig = (plotsig=="true");
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");

  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/RegionPlots/";
  MakeDir(output);
  output+=plot_dir+"/";
  MakeDir(output);
  output+=year+"/";
  MakeDir(output);
  
  cout << "MakeRegionPlots::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  TLegend *legend_g = MakeLegend(0.75, 0.75, 0.95, 0.92);
  legend_g->SetTextSize(0.02);
  // canvas for hists
  TString canvasname=histname;
  
  //vector<pair<Color_t,int> > histcolors = GetHistColors(1);
  //vector<TH1D*> _vhists;

  TString postfix="_noconv";
  postfix="";
  TString n_sr_hist = plot_dir+"/"+plot_dir+"_"+ histname + "_"+analysername+"_"+flavour+"_"+ id+ postfix;

  THStack * hs       = MakeStack(legend_g,bkgmap,n_sr_hist, colormap,rbin,0);
  THStack * hs_up    = MakeStack(legend_g,bkgmap,n_sr_hist, colormap,rbin,2);
  THStack * hs_down  = MakeStack(legend_g,bkgmap,n_sr_hist, colormap,rbin,-2);
  THStack * hs_up_nostat    = MakeStack(legend_g,bkgmap,n_sr_hist, colormap,rbin,1);
  THStack * hs_down_nostat  = MakeStack(legend_g,bkgmap,n_sr_hist, colormap,rbin,-1);

  TH1D* h_nominal = MakeSumHist2(hs);
  TH1D* h_up      = MakeSumHist2(hs_up);
  TH1D* h_down    = MakeSumHist2(hs_down);
  TH1D* h_up_nostat      = MakeSumHist2(hs_up_nostat);
  TH1D* h_down_nostat    = MakeSumHist2(hs_down_nostat);


  TString x_axis = GetXTitle(sigmap,n_sr_hist);
  TString y_axis = GetYTitle(sigmap,n_sr_hist);

  if(showdata!="true"){
    hs->GetXaxis()->SetTitle(x_axis);
    hs->GetYaxis()->SetTitle(y_axis);
  }

  SetNomBinError(h_nominal, h_up, h_down);

  cout<<  "bkgmap = " << bkgmap.size() << endl;
  double stack_count = GetIntegral(bkgmap,n_sr_hist);
  
  TString canvasname2=plot_dir+"_"+ histname + "_"+analysername+"_"+flavour+"_"+ id;
  TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
  if(logy==1) c2->SetLogy();
  c2->cd();

  vector<pair<Color_t,int> > histcolors = GetHistColors(sigcolormap.size());

  float _max(0.),_min(9999999999.);
  if(_max < hs->GetMaximum()) _max = hs->GetMaximum();

  int counter (0);
  if(PlotSig){
    for (map<TString,TString>::iterator it = sigmap.begin(); it != sigmap.end(); it++){
      map<TString,Color_t>::iterator colit = sigcolormap.find(it->first);
      TH1D* sig = GetSignalHist(legend_g,it->first,it->second,n_sr_hist, histcolors[counter],false);
      if (!sig) continue;
      sig->Scale(stack_count/sig->Integral());
      if(_max < sig->GetMaximum()) _max = sig->GetMaximum();
      counter+=1;
    }
  }
  setTDRStyle();

  TFile* f_data ;
  TH1D* hist_data;
  if(showdata=="true"){

    f_data = new TFile(data_file);
    hist_data = GetHist(f_data,n_sr_hist);
    x_axis = hist_data->GetXaxis()->GetTitle();

    if(!hist_data || hist_data->GetEntries() == 0 ) {
      f_data->Close();
      delete f_data;
      cout << "Missing data file" << endl;
      return;
    }

    vector<double> err_up_tmp;
    vector<double> err_down_tmp;

    // set data hist 
    SetupHist(hist_data, rbin,_max);

    // get graph with data errors
    TGraphAsymmErrors * g_data = GetDataGraph(hist_data,err_up_tmp,err_down_tmp);

    // range
    if(xmin != 999)    hist_data->GetXaxis()->SetRangeUser(xmin,xmax);

    
    // data is ploytted first
    if(x_axis)    hist_data->GetXaxis()->SetTitle(x_axis);
    if(x_axis)    hist_data->GetYaxis()->SetTitle(y_axis);
    if(_max < hist_data->GetMaximum()) _max = hist_data->GetMaximum();
    hist_data->GetYaxis()->SetRangeUser(0., _max*1.4);
    if(logy==1)    hist_data->GetYaxis()->SetRangeUser(0.1, _max*1.4);
    hist_data->Draw( ("p9hist"));
    legend_g->AddEntry(hist_data,"data","pl");
    hs->Draw("histsame");
    g_data->Draw(" p0" );
    
    TH1D* errorband = MakeErrorBand(h_nominal,h_up, h_down) ;
    legend_g->AddEntry(errorband, "stat. + syst.","f");
    errorband->Draw("E2same");  
  
    hist_data->Draw("axis same");
    hist_data->Draw( ("same9p9hist"));


    counter =0;

    if(PlotSig){
      for (map<TString,TString>::iterator it = sigmap.begin(); it != sigmap.end(); it++){
	map<TString,Color_t>::iterator colit = sigcolormap.find(it->first);
	TH1D* sig = GetSignalHist(legend_g,it->first,it->second,n_sr_hist, histcolors[counter],true);
	
	if(!sig) continue;
	
	sig->Rebin(rbin);
	sig->Scale(stack_count/sig->Integral());
	if(_max < sig->GetMaximum()) _max = sig->GetMaximum();
	x_axis= sig->GetXaxis()->GetTitle();
	y_axis= sig->GetYaxis()->GetTitle();
	sig->Scale(0.2);
	sig->Draw("histsame");
	counter+=1;
      }
    }
    c2->Update();
    c2->RedrawAxis();
    

    /// now draw ratio

    double FIGURE2_RATIO = 0.25;
    double SUBFIGURE_MARGIN = 0.;
    c2->SetBottomMargin(FIGURE2_RATIO);
    TPad *p = GetPad(SUBFIGURE_MARGIN,FIGURE2_RATIO);
    p->Draw();
    p->cd();
    p->SetTicks(0,1);

    TH1D* h_ratio         = GetMCDataRatio(hist_data,h_nominal);
    TH1D* h_ratio_err     = GetDataError(hist_data,h_nominal,h_up_nostat, h_down_nostat);
    TH1D* h_ratio_staterr = GetDataError(hist_data,h_nominal,h_up, h_down);


    TGraphAsymmErrors * gratio = GetratioGraph(h_ratio,h_nominal,err_up_tmp,err_down_tmp);


    h_ratio->GetYaxis()->SetLabelSize(0.035);
    h_ratio->GetYaxis()->SetTitleSize(0.035);
    h_ratio->GetYaxis()->SetTitleOffset(1.3);
    
    h_ratio->GetYaxis()->SetTitle( "Data / #Sigma Bkg" );
    h_ratio->GetYaxis()->SetRangeUser(0.25,+1.75);
    h_ratio->GetYaxis()->SetNdivisions(3);
    h_ratio->GetXaxis()->SetNdivisions(5);
    
    h_ratio->SetMarkerStyle(20);
    h_ratio->SetLineColor(kBlack);
    h_ratio_err->SetMarkerSize(0.);
    h_ratio_staterr->SetMarkerSize(0.);
    h_ratio_err->SetFillColor(kRed);
    h_ratio_err->SetLineColor(kRed);
    h_ratio_err->SetFillStyle(3444);

    h_ratio_staterr->SetMarkerSize(0.);
    h_ratio_staterr->SetFillColor(kOrange-9);
    h_ratio_staterr->SetLineColor(kOrange-9);


    // draw
    h_ratio->Draw("p hist");
    h_ratio_staterr->Draw("sameE4");
    h_ratio_err->Draw("sameE4");

    gratio->SetLineWidth(2.0);
    h_ratio->Draw("same 9p hist ");

    gratio->Draw(" p0" );
    TLine *devz = new TLine(h_ratio->GetBinLowEdge(h_ratio->GetXaxis()->GetFirst()),1.0,h_ratio->GetBinLowEdge(h_ratio->GetXaxis()->GetLast()+1),1.0  );
    devz->SetLineWidth(1);
    devz->SetLineStyle(1);
    devz->Draw("SAME");
    TLegend* legendr = MakeRatioLegend(h_ratio_staterr,h_ratio_err);
    legendr->Draw();
    c2->Update();
    c2->RedrawAxis();
    gPad->RedrawAxis();

  }
  else{
    hs->SetMaximum(_max*1.4);
    hs->Draw("hist");
 counter =0;

    if(PlotSig){
      for (map<TString,TString>::iterator it = sigmap.begin(); it != sigmap.end(); it++){
        map<TString,Color_t>::iterator colit = sigcolormap.find(it->first);
        TH1D* sig = GetSignalHist(legend_g,it->first,it->second,n_sr_hist, histcolors[counter],true);

        if(!sig) continue;

        sig->Rebin(rbin);
        sig->Scale(stack_count/sig->Integral());
        if(_max < sig->GetMaximum()) _max = sig->GetMaximum();
        x_axis= sig->GetXaxis()->GetTitle();
        y_axis= sig->GetYaxis()->GetTitle();
        sig->Scale(0.2);
        sig->Draw("histsame");
        counter+=1;
      }
    }
    c2->Update();
    c2->RedrawAxis();


    TH1D* errorband = MakeErrorBand(h_nominal,h_up, h_down) ;
    legend_g->AddEntry(errorband, "stat. + syst.","f");
    errorband->Draw("E2same");  
  }

  

  hs->GetXaxis()->SetTitle(x_axis);
  hs->GetYaxis()->SetTitle(y_axis);


  c2->Modified();
  
  legend_g->Draw("same");
      
  DrawLatexWithLabel(year,plot_dir,0.25,0.88);
  DrawLatexWithLabel(year,flavour,0.25,0.83);
  DrawLatexWithLabel(year,id,0.25,0.78);
  DrawLatexWithLabel(year,postfix,0.25,0.73);

  DrawLatex(year);
  
  
  //MakeTexFile(histmap,output,"SR1+SR2");
  TString save_sg= output + "/"+savetag+"_hist_"+histname+"_highmass_"+analysername+"_"+flavour+"_"+id+postfix+".pdf";

  //c2->SetLogy();
  c2->SaveAs(save_sg);
  OutMessage("MakeRegionPlots",save_sg);


  if(f_data) {
    f_data->Close();
  }
  return;
  
}

void MakeTexFile(map< TString, TH1D * > hs,TString output,TString SR){

  TString texfilepath = output+"/tex/";
  MakeDir(texfilepath);

  ofstream ofile_tex(texfilepath+"/Yields.tex",ios::trunc);
  ofile_tex.setf(ios::fixed,ios::floatfield);
  ofile_tex << "\\documentclass[10pt]{article}" << endl;
  ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}" << endl;
  ofile_tex << "\\begin{document}" << endl;
  ofile_tex << "\\input{"+texfilepath+"/Table.txt}" << endl;
  ofile_tex << "\\end{document}" << endl;

  ofstream ofile(texfilepath+"/Table.txt",ios::trunc);
  ofile.precision(3);
  ofile.setf(ios::fixed,ios::floatfield);
  ofile << "\\begin{table}[!tbh]" << endl;
  ofile << "  \\caption{" << endl;
  ofile << "    Number of events in " << SR << endl;
  ofile << "  }" << endl;
  ofile << "  \\begin{center}" << endl;
  ofile << "    \\begin{tabular}{c|c|c}" << endl;
  ofile << "\\hline" << endl;
  ofile << " ID & SR1 & SR2 \\\\" << endl;
  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;

  TH1D *hist_bkgd = new TH1D("hist_bkgd", "", 1., 0., 1.);
  bool HasSignal = false;
  for(map< TString, TH1D * >::iterator it = hs.begin(); it != hs.end(); it++){
    TString name = it->first;

    name.ReplaceAll("_","\\_");
    if(name == "X + #gamma") name = "$X + \\gamma$";
    if(name == "Z + #gamma") name = "Z $+ \\gamma$";
    if(name == "W + #gamma") name = "W $+ \\gamma$";
    if(name == "top + #gamma") name = "top $+ \\gamma$";
    TH1D *h_bkgd = it->second;
    ofile << name << " & $"<<h_bkgd->GetBinContent(1)<< "$  & $" << h_bkgd->GetBinContent(2)  <<"$ \\\\" << endl;
    hist_bkgd->Add(h_bkgd);
  }
  ofile << "\\hline" << endl;
  //  ofile << "Total & $" << hist_bkgd->GetBinContent(1) << " \\pm " << hist_bkgd->GetBinError(1) << "$ \\\\" << endl;
  //ofile << "\\hline" << endl;


  //double signif = (hist_data->GetBinContent(1) - hist_bkgd->GetBinContent(1)) / sqrt( (hist_bkgd->GetBinError(1))*(hist_bkgd->GetBinError(1)) + (hist_data->GetBinError(1))*(hist_data->GetBinError(1)) );

  //ofile << "Significance & $" <<signif<<" \\sigma$ \\\\" << endl;

  ofile << "\\hline" << endl;
  ofile << "\\hline" << endl;
  ofile << "    \\end{tabular}" << endl;
  ofile << "  \\end{center}" << endl;
  ofile << "\\end{table}" << endl;

  system("latex "+texfilepath+"/Yields.tex");
  system("dvipdf Yields.dvi");
  system("rm *aux");
  system("rm *log");
  system("rm *dvi");
  system("mv Yields.pdf "+texfilepath);

}

