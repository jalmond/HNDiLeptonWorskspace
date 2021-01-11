#include "base_functions.h"
#include "Macros.h"
#include "mylib.h"
#include "canvas_margin.h"

void GetSignalOverB_combinedSR(TString suffix="ipB",TString channel="EE"){ 

  bool debug(true);
  // basic declarations 
  TString ptbin="";  TString _chan = "Schannel"; TString analysername="HNDilepton" ;

  // check which pc is running script to setup local paths
  TString s_hostname = GetHostname();

  
  vector<TString> code_names= {"HNDilepton"};

  if(std::find(code_names.begin(), code_names.end(), analysername) != code_names.end()) cout << "Running with code " << analysername << endl;
  else {cout << "Error in input of analyzer: " << analysername << endl; for (auto i: code_names)   std::cout << i << ' '; return; }

  
  // local path names
  TString ENV_FILE_PATH= (getenv("INFILE_PATH"));
  TString ENV_MERGEDFILE_PATH = getenv("INFILE_MERGED_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");
  TString FLATVERSION = getenv("FLATVERSION");
  
  MakeDir(ENV_PLOT_PATH + FLATVERSION);
  TString input_path = ENV_FILE_PATH + FLATVERSION+"/"+analysername+"/";
  TString output = ENV_PLOT_PATH + FLATVERSION + "/"+analysername+"/";

  MakeDir(output);
  output+="/SignalOverBackground/";  MakeDir(output);
  output+="/Combined/";              MakeDir(output);
  output+="SignalRegions/";          MakeDir(output);

  cout << "GetSignalEfficiency_combinedSR::LOG Output dir = " << output << endl;
  
  if(s_hostname == "JohnMB2018s-MacBook-Pro.local")    input_path = "/Users/john/HNDiLeptonWorskspace/OutputTool/MergedFiles/";

  // Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);



  //************************************************************************************
  //************************************************************************************
  // MACRO STARTS HERE
  //************************************************************************************
  //************************************************************************************

  // combine punzi for rach signal regions
  vector<TString> SR = {"SR1","SR2"};
  // combine punzi for different pt bins
  vector<TString> PTBins = {"_HighPt","_LowPt"};


  vector<TString> IDs = {};  
  
  vector <TString> masses = {"100","300"};//,"500","1000"};
  vector <double> d_masses = {100.,300.};//,500.,1000.};
  
  TString _channel = channel;
  
  // hist leg
  TLegend *legend = MakeLegend(0.65, 0.65, 0.9, 0.92);
  // graph leg
  TLegend *legend_g = MakeLegend(0.65, 0.65, 0.9, 0.92);

  std::string input_user;
  
  TString promptpath1 = ENV_MERGEDFILE_PATH+ analysername+"/2016/"+analysername+"_SkimTree_SSHN_Muon.root";
  if(channel=="EE") promptpath1 = ENV_MERGEDFILE_PATH+ analysername+"/2016/"+analysername+"_SkimTree_SSHN_DoubleEG.root";

  cout << "---------------------------------------------------------" << endl;
  cout << "Channel : " << channel << " , datafile = " << promptpath1 << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "Is this correct? Type Y if correct. " << endl;

  if(!debug){
    cin >> input_user ;
    
    if( TString(input_user) != "Y") return;
  }
  
  TFile * _file1 = new TFile(promptpath1);
  TDirectory* _dir1 = _file1->GetDirectory("presel_EE_same_sign");
  TList* list1 = _dir1->GetListOfKeys() ;
  TIter next(list1) ;
  TKey* key1 ;
  TObject* obj1 ;

  vector<TString> histlist;
  
  cout << "---------------------------------------------------------" << endl;
  cout << "List of signals = " << endl;
  vector<TString> years={"2016","2017","2018"};  
  for (auto y : years)  for (auto im : masses) {
      TString sigpathS = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+y+"/SIG/"+analysername+"_DYTypeI_SS_"+_channel+"_M"+im+".root";
      cout << sigpathS << endl;
    }
  
  cout << "Is this correct? Type Y if correct. " << endl;
  if(!debug){
    cin >> input_user ;
    if( TString(input_user) != "Y") return;
  }
  while ( (key1 = (TKey*)next()) ) {
    obj1 = key1->ReadObj() ;
    TString hname = obj1->GetName();
    TString objname= obj1->ClassName();

    if(!hname.Contains(suffix)) continue;
    histlist.push_back(hname);
    if(!hname.Contains("LowPt")) continue;



    hname = hname.ReplaceAll("_HighPt","");
    hname = hname.ReplaceAll("_LowPt","");
    hname = hname.ReplaceAll("presel_EE_same_sign_SR2_njets_HNDilepton_EE_","");
    hname = hname.ReplaceAll("presel_EE_same_sign_SR1_njets_HNDilepton_EE_","");
    hname = hname.ReplaceAll("presel_EE_same_sign/","");
	
    IDs.push_back(hname);
  }

  cout << "Number of IDs  = " << IDs.size() << endl;


  //* Loop over years 2-16/17/18
  for (auto year : years){
    
    vector<double> binvalues;
    
    //-- loop over masses and IDs to fill all 2D bin values as 0.;
    for (auto  id: IDs)   for (auto  im: masses) binvalues.push_back(0.);
    
    //-- Simply naming the 2D histogram
    TString histlabel= year+"_"+_channel +  +"_highmass_"+analysername;
    TH2D* hist2 = new TH2D(histlabel,histlabel,masses.size()+1,0,masses.size()+1., IDs.size(),0., IDs.size());

    //-- create map with ID/mass punzi value and string connected 
    map<double, TString> map_punzi;
    map<TString, double> map_id;

    //** Loop over SRs [SR1+SR2]
    for(auto _sr : SR){

      //*** loop over low and high pt bins
      for(auto ptbin : PTBins){
	
	//-- to make processing faster some assumptions can be made and some bins skipped

	if(ptbin == "_LowPt" && _sr == "SR2") continue;
	
	//if(d_masses[i] <= 200. &&  _sr == "SR2") continue;
	//if(d_masses[i] >= 1000. &&  _sr == "SR1") continue;
	//if(d_masses[i] >= 300. &&  ptbin == "_LowPt") continue;
	

	//-- vector of IDvalues
	vector<double> IDvalues;	

	//-- Make string for data file
	TString promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSHN_Muon.root";
	if(channel=="EE") promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSHN_DoubleEG.root";
	if(channel=="EE"&&year=="2018") promptpath = ENV_MERGEDFILE_PATH+ analysername+"/"+year+"/"+analysername+"_SkimTree_SSHN_EGamma.root";
	
	TFile * file_prompt = new TFile((promptpath).Data());

	
	//**** loop over IDs to get integrate hists
	int id_counter(0);
	for(auto _id : IDs){
	  id_counter++;

	  //-- set Y axis label of 2D hist
	  hist2->GetYaxis()->SetBinLabel(id_counter, _id);

	  //-- Get hist name for current histogram
	  TString n_sr_hist ="preselMuMu_same_sign/preselMuMu_same_sign_"+_sr+"_njets_HNDilepton_"+channel+"_"+_id+ptbin;
	  if(channel=="EE")n_sr_hist ="presel_EE_same_sign/presel_EE_same_sign_"+_sr+"_njets_HNDilepton_"+channel+"_"+_id+ptbin;

	  //-- access histogram in bkg file
	  TH1D* hpass = (TH1D*)(file_prompt->Get(n_sr_hist));

	  //-- get bkg number from hist
	  double total_p = hpass->Integral();
	  double total_b = sqrt(total_p);

	  //-- useful OUTPUT message showing ID and sqrtB
	  cout << _sr << " " << ptbin << " : " <<  id_counter << " / " << IDs.size() << " "  << _id << " sqrt B = "  << total_b << endl;
	  IDvalues.push_back(total_b);
	  //-- IDvalues  contains bkg numbers for this SR/ptbin  

	}//**** END ID loop
      

	//-- ibin int keeps track of 2D bin number                                                                                                                                                                
	int ibin(0);
	
	//**** Loop over the masses 
	int mass_counter(0);
	for (auto im : masses){

	  mass_counter++;
	  
	  //-- mass_values gets signal yield for this mass 
	  vector<double> mass_values;

	  double total_mass_value(0.);

	  //-- set x axis label
	  hist2->GetXaxis()->SetBinLabel(mass_counter, im);


	  ///-- Get signal file
	  TString sigpathS = ENV_MERGEDFILE_PATH+ "/"+analysername+"/"+year+"/SIG/"+analysername+"_DYTypeI_SS_"+_channel+"_M"+im+".root";
	  TFile * filemm = new TFile((sigpathS).Data());

	  //-- Check file is ok to read IF not set mass value to 0.
	  if(CheckFile(filemm) > 0) {
	    mass_values.push_back(0.);

	    filemm->Close();
	    delete filemm;

	    continue; 	    
	  }
	  
	  
	  //***** loop over IDs for this signal mass
	  
	  int sig_id_counter(0);
	  for(auto _id : IDs){
	    sig_id_counter++;

	    ///-- set histogram name for signal
	    TString n_sr_hist ="preselMuMu_same_sign/preselMuMu_same_sign_"+_sr+"_njets_HNDilepton_"+channel+"_"+_id+ptbin;
	    if(channel=="EE")n_sr_hist ="presel_EE_same_sign/presel_EE_same_sign_"+_sr+"_njets_HNDilepton_"+channel+"_"+_id+ptbin;

	    //-- Get number of signal events
	    float nsig= 1.;
	    TH1D* hpass1 = (TH1D*)(filemm->Get(n_sr_hist));

	    double err ;  double  punzi = 0.;
	    if(hpass1){
      
	      hpass1->IntegralAndError(1, hpass1->GetNbinsX()+1, err    , "");
	      punzi = (IDvalues[sig_id_counter-1] > 0) ?  ((hpass1->Integral()) /(nsig)) /IDvalues[sig_id_counter-1] : 0.;
	      
	      //-- useful OUTPUT message showing ID and punzi                                                                                                                                                           
	      cout << _sr << " " << ptbin << " : " << _id << " " << hpass1->Integral() << " / " << IDvalues[sig_id_counter-1] <<  " punzi =" << punzi<< endl;
	    }
	    else {
	      
	      cout << _sr << " " << ptbin << " : " << _id << " 0.  " << IDvalues[sig_id_counter-1] <<  " " << punzi<< endl;
	      
              //cout << "Missing file " << n_sr_hist << " in signal " << endl;
	      // for(auto _hist : histlist) cout << _hist << endl;

	    }
	    mass_values.push_back(punzi);
	    total_mass_value+= punzi;

	    //map_punzi[punzi] = _id;
	    map<TString, double>::iterator mit = map_id.find(_id);
	    if (mit == map_id.end())     map_id[_id]      = punzi;
	    else  map_id[_id]      = punzi + mit->second;
	    
	  }//***** end of signal ID loop

	  ///-- close file
	  filemm->Close();
	  delete filemm;
	  
	  for(unsigned int l = 0 ; l < IDs.size(); l++){
	    
	    binvalues[ibin] = binvalues[ibin] + mass_values[l];
	    ibin++;
	  }
	  
	} //**** mass loop
	hist2->GetXaxis()->SetBinLabel(masses.size()+1, "Sum");
	
      } //*** ptbin loop
      
      
    }//** SR loop
    

    // Now redo histogram to get average
    int counter(0);

    //** mass loop
    int _mass_counter(0);
    for(auto im : masses){
      
      double _average(0.);
      double _count(0.);
      _mass_counter++;
      //*** ID loop
      int counter_tmp=counter;
      for(unsigned int l = 0 ; l < IDs.size(); l++){
	_average+=binvalues[counter_tmp];
	if(binvalues[counter_tmp] > 0.) _count=_count+1.;
	counter_tmp++;
      } //*** ID loop
       
      _average=_average/_count;

      //*** ID loop
      for(unsigned int l = 0 ; l < IDs.size(); l++){
	cout << "HIST " << _mass_counter << " " << l+1 << " " << binvalues[counter]/_average << endl;
	hist2->SetBinContent(_mass_counter, l+1, binvalues[counter]/_average);
	counter++;
      }      //*** ID loop
    }//** mass loop
    

  

    counter=0;
    double max_punzi = -999.;
    int _max_id=-1;
    for(unsigned int l = 0 ; l < IDs.size(); l++){
      
      double total_id(0);
      for(unsigned int i = 0 ; i < masses.size(); ++i){
	total_id+= hist2->GetBinContent(i+1, l+1);
	cout << hist2->GetBinContent(i+1, l+1) << endl;
	counter++;
      }
      hist2->SetBinContent(masses.size()+1, l+1, total_id/masses.size());
      if(total_id/masses.size() > max_punzi) {
	max_punzi = total_id/masses.size();
	_max_id = l;
      }
    } //** ID loop


    for(auto mit : map_id) map_punzi[mit.second] = mit.first;
    
    cout << year  << " MAX ID = " << IDs[_max_id] << "  " << max_punzi  << endl;
    
    for (auto i: map_punzi) cout << year  << " " << i.first << " " << i.second << endl;
      
    TString canvasname2="SR12_highmass_njets_"+analysername+"_JA_"+_channel+ptbin+channel+year;
    TCanvas* c2 = new TCanvas(canvasname2,canvasname2, 800,800);
    c2->cd();
    
    TString outfile = output  +  "/TH2D_"+ptbin+"SR12highmass_signaloverbackground_"+analysername+"_"+_chan+"_"+channel+year+suffix+".root";
    TFile* fout = new TFile(outfile.Data(),"RECREATE");
    
    hist2->Draw("colztext");
    hist2->Write();
    
    TString save_sg= output + "/TH2D_"+ptbin+"SR12highmass_signaloverbackground_"+analysername+"_"+_chan+"_"+channel+year+suffix+".pdf";
    
    c2->SaveAs(save_sg);
    
  }
  return;
      
    
}
