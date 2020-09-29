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
  map<TString,TString> bkgmap    = BkgConfigMap(config_file);
  map<TString,Color_t> colormap  = BkgColorMap(config_file);
  map<TString,Color_t> sigcolormap  = SigColorMap(config_file);
  map<TString,TString>  sigmap   = SigConfigMap(config_file);
  if(configmap.size()==0) return;
  
  
  TString analysername = configmap["analysername"];
  if(!CheckInput(code_names,configmap["analysername"], "analysername"))  return;
  
  TString plot_dir     = configmap["plot_dir"];
  TString cut_dir      = configmap["cut_dir"];
  TString data_file    = configmap["data_file"];
  if(!CheckFileInput(configmap["data_file"] ))  return;
  vector<TString> dir_name = GetDirName(configmap["data_file"]);
  if(!CheckInput(dir_name,configmap["cut_dir"], "cutname" ))  return;
  
  
  TString year         = configmap["year"];
  TString id           = configmap["id"];
  TString flavour      = configmap["flavour"];
  vector<TString> id_name  = GetIDNames(configmap["data_file"],cut_dir,analysername,flavour);
  if(!CheckInput(id_name, id, "ID" ))  return;  
  TString histname           = configmap["histname"];
  vector<TString> hist_names = GetHistNames(configmap["data_file"],cut_dir,analysername,flavour);
  //if(!CheckInput(hist_names, histname, "histname" ))  return;

  cout << "-------------------------------------------" << endl;
  cout << "analysername = " << analysername << endl;
  cout << "plot_dir     = " << plot_dir << endl;
  cout << "cut_dir      = " << cut_dir << endl;
  cout << "data_file    = " << data_file << endl;
  cout << "year         = " << year << endl;
  cout << "ID           = " << id   << endl;
  cout << "histname     = " << histname   << endl;
  


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
  
  
  cout << "MakeRegionPlots::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local"){
    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";
  }

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  TLegend *legend_g = MakeLegend(0.6, 0.75, 0.9, 0.92);
  legend_g->SetTextSize(0.02);
  // canvas for hists
  TString canvasname=histname;
  
  //vector<pair<Color_t,int> > histcolors = GetHistColors(1);
  //vector<TH1D*> _vhists;
  
  TString n_sr_hist = plot_dir+"/"+plot_dir+"_"+ histname + "_"+analysername+"_"+flavour+"_"+ id;


  THStack * hs = MakeStack(legend_g,bkgmap,n_sr_hist, colormap);
  double stack_count = GetIntegral(bkgmap,n_sr_hist);
  
  TString canvasname2=plot_dir+"_"+ histname + "_"+analysername+"_"+flavour+"_"+ id;
  TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
  c2->cd();
  

  vector<pair<Color_t,int> > histcolors = GetHistColors(sigcolormap.size());
  float _max(0.),_min(9999999999.);
  if(_max < hs->GetMaximum()) _max = hs->GetMaximum();

  int counter (0);
  for (map<TString,TString>::iterator it = sigmap.begin(); it != sigmap.end(); it++){
    map<TString,Color_t>::iterator colit = sigcolormap.find(it->first);
    TH1D* sig = GetSignalHist(legend_g,it->first,it->second,n_sr_hist, histcolors[counter],false);
    sig->Scale(stack_count/sig->Integral());
    if(_max < sig->GetMaximum()) _max = sig->GetMaximum();
    counter+=1;
	
    
  }
  
  setTDRStyle();
  hs->SetMaximum(_max*1.4);
  hs->Draw("hist");

  TString x_axis;
  TString y_axis;
  //  TH1D* GetSignalHist(TLegend* legend_g,TString current_sample, TString filepath, TString fullhistname,Color_t _col){

  counter =0;

  for (map<TString,TString>::iterator it = sigmap.begin(); it != sigmap.end(); it++){
    map<TString,Color_t>::iterator colit = sigcolormap.find(it->first);
    TH1D* sig = GetSignalHist(legend_g,it->first,it->second,n_sr_hist, histcolors[counter],true);
    sig->Scale(stack_count/sig->Integral());
    if(_max < sig->GetMaximum()) _max = sig->GetMaximum();
    x_axis= sig->GetXaxis()->GetTitle();
    y_axis= sig->GetYaxis()->GetTitle();
    //sig->Rebin(2);
    sig->Draw("histsame");
    counter+=1;
  }


      

  hs->GetXaxis()->SetTitle(x_axis);
  hs->GetYaxis()->SetTitle(y_axis);
  c2->Modified();
  
  legend_g->Draw();
      
  DrawLatexWithLabel(year,"HighMass SR",0.25,0.88);
  DrawLatexWithLabel(year,flavour,0.25,0.83);
  
  //MakeTexFile(histmap,output,"SR1+SR2");
  TString save_sg= output + "/hist_"+histname+"_highmass_"+analysername+"_"+flavour+".pdf";

  //c2->SetLogy();
  c2->SaveAs(save_sg);
  OutMessage("GetSignalEfficiency",save_sg);
  
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

