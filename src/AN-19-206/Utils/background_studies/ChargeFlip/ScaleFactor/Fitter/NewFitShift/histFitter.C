#include "RooDataHist.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "TH1.h"
#include "TSystem.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveText.h"
#include <TStyle.h>
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include <sys/stat.h>

/// include pdfs
#include "RooCBExGaussShape.h"
#include "RooCMSShape.h"

#include <vector>
#include <string>
#ifdef __CINT__
#pragma link C++ class std::vector<std::string>+;
#endif

using namespace RooFit;
using namespace std;

class tnpFitter {
public:
  tnpFitter( TFile *file, std::string histname  );
  tnpFitter( TH1 *hPass, TH1 *hFail, std::string filename, std::string histname  );
  ~tnpFitter(void) {if( _work != 0 ) delete _work; }
  void setZLineShapes(TH1 *hZPass, TH1 *hZFail );
  void setWorkspace(std::vector<std::string>);
  void setOutputFile(TFile *fOut ) {_fOut = fOut;}
  void setTDRStyle() ;
  void fits(bool mcTruth,std::string title = "", TString FilePath="", TString HistName="", TString HistNameOS="");
  void useMinos(bool minos = true) {_useMinos = minos;}
  void textParForCanvas(RooFitResult *resP, RooFitResult *resF, TPad *p);
  
  void fixSigmaFtoSigmaP(bool fix=true) { _fixSigmaFtoSigmaP= fix;}

  void setFitRange(double xMin,double xMax) { _xFitMin = xMin; _xFitMax = xMax; }
private:
  RooWorkspace *_work;
  std::string _filename_base;
  std::string _histname_base;
  TFile *_fOut;
  double _nTotP, _nTotF;
  bool _useMinos;
  bool _fixSigmaFtoSigmaP;
  double _xFitMin,_xFitMax;
};


// this is the original code


void canvas_margin(TCanvas *c1){
  c1->SetTopMargin( 0.05 );
  c1->SetBottomMargin( 0.13 );
  c1->SetRightMargin( 0.05 );
  c1->SetLeftMargin( 0.16 );

}
void hist_axis(TH1 *hist){

  hist->SetTitle("");


  hist->GetYaxis()->SetLabelSize(0.03);
  hist->GetYaxis()->SetTitleSize(0.04);

  if(hist->GetMaximum() < 1000)  hist->GetYaxis()->SetTitleOffset(1.40);
  else  if(hist->GetMaximum()< 100000)   hist->GetYaxis()->SetTitleOffset(1.50);
  else  hist->GetYaxis()->SetTitleOffset(1.60);

  if(hist->GetMaximum() < 0.001)  hist->GetYaxis()->SetTitleOffset(1.60);
  hist->GetYaxis()->SetTitleOffset(1.60);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.04);
  hist->GetXaxis()->SetTitleOffset(1.20);

}
string DToString(double a, int prec=2){
  
  std::ostringstream streamObj2;
  streamObj2 << std::fixed;
  streamObj2 << std::setprecision(prec);
  streamObj2 << a;
  std::string strObj2 = streamObj2.str();
  return strObj2;
}



tnpFitter::tnpFitter(TFile *filein, std::string histname   ) : _useMinos(false),_fixSigmaFtoSigmaP(false) {
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  _histname_base = histname;  

  TH1 *hPass = (TH1*) filein->Get(TString::Format("%s_Pass",histname.c_str()).Data());
  TH1 *hFail = (TH1*) filein->Get(TString::Format("%s_Fail",histname.c_str()).Data());
  _nTotP = hPass->Integral();
  _nTotF = hFail->Integral();
  /// MC histos are done between 50-130 to do the convolution properly
  /// but when doing MC fit in 60-120, need to zero bins outside the range
  for( int ib = 0; ib <= hPass->GetXaxis()->GetNbins()+1; ib++ )
    if(  hPass->GetXaxis()->GetBinCenter(ib) <= 60 || hPass->GetXaxis()->GetBinCenter(ib) >= 120 ) {
      hPass->SetBinContent(ib,0);
      hFail->SetBinContent(ib,0);
    }
  
  _work = new RooWorkspace("w") ;
  _work->factory("x[50,130]");

  RooDataHist rooPass("hPass","hPass",*_work->var("x"),hPass);
  RooDataHist rooFail("hFail","hFail",*_work->var("x"),hFail);
  _work->import(rooPass) ;
  _work->import(rooFail) ;
  _xFitMin = 60;
  _xFitMax = 120;
}

tnpFitter::tnpFitter(TH1 *hPass, TH1 *hFail, std::string filename, std::string histname  ) : _useMinos(false),_fixSigmaFtoSigmaP(false) {
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  _filename_base = filename; //JH
  _histname_base = histname;
  
  hPass->Rebin(2);
  hFail->Rebin(2);

  _nTotP = hPass->Integral();
  _nTotF = hFail->Integral();
  /// MC histos are done between 50-130 to do the convolution properly
  /// but when doing MC fit in 60-120, need to zero bins outside the range
  //for( int ib = 0; ib <= hPass->GetXaxis()->GetNbins()+1; ib++ )
  /// if(  hPass->GetXaxis()->GetBinCenter(ib) <= 60 || hPass->GetXaxis()->GetBinCenter(ib) >= 120 ) {
  //  hPass->SetBinContent(ib,0);
  //   hFail->SetBinContent(ib,0);
  //}
  
  _work = new RooWorkspace("w") ;
  _work->factory("x[50,130]");
  
  RooDataHist rooPass("hPass","hPass",*_work->var("x"),hPass);
  RooDataHist rooFail("hFail","hFail",*_work->var("x"),hFail);
  _work->import(rooPass) ;
  _work->import(rooFail) ;
  _xFitMin = 60;
  _xFitMax = 120;
  
}


//


void tnpFitter::setZLineShapes(TH1 *hZPass, TH1 *hZFail ) {
  RooDataHist rooPass("hGenZPass","hGenZPass",*_work->var("x"),hZPass);
  RooDataHist rooFail("hGenZFail","hGenZFail",*_work->var("x"),hZFail);
  _work->import(rooPass) ;
  _work->import(rooFail) ;  
}

void tnpFitter::setWorkspace(std::vector<std::string> workspace) {
  for( unsigned icom = 0 ; icom < workspace.size(); ++icom ) {
    _work->factory(workspace[icom].c_str());
  }

  _work->factory("HistPdf::sigPhysPass(x,hGenZPass)");
  _work->factory("HistPdf::sigPhysFail(x,hGenZFail)");
  _work->factory("FCONV::sigPass(x, sigPhysPass , sigResPass)");
  _work->factory("FCONV::sigFail(x, sigPhysFail , sigResFail)");
  //_work->factory(TString::Format("nSigP[%f,0.5,%f]",_nTotP*0.9,_nTotP*1.5));
  //_work->factory(TString::Format("nBkgP[%f,0.5,%f]",_nTotP*0.1,_nTotP*1.5));
  //_work->factory(TString::Format("nSigF[%f,0.5,%f]",_nTotF*0.9,_nTotF*1.5));
  //_work->factory(TString::Format("nBkgF[%f,0.5,%f]",_nTotF*0.1,_nTotF*1.5));
  //_work->factory("SUM::pdfPass(nSigP*sigPass,nBkgP*bkgPass)");
  //_work->factory("SUM::pdfFail(nSigF*sigFail,nBkgF*bkgFail)");
  _work->factory(TString::Format("nSigOS[%f,0.5,%f]",_nTotP*0.9,_nTotP*1.5));
  _work->factory(TString::Format("nBkgOS[%f,0.5,%f]",_nTotP*0.1,_nTotP*1.5));
  _work->factory(TString::Format("nSigSS[%f,0.5,%f]",_nTotF*0.9,_nTotF*1.5));
  _work->factory(TString::Format("nBkgSS[%f,0.5,%f]",_nTotF*0.1,_nTotF*1.5));
  _work->factory("SUM::pdfPass(nSigOS*sigPass,nBkgOS*bkgPass)");
  _work->factory("SUM::pdfFail(nSigSS*sigFail,nBkgSS*bkgFail)");
  _work->Print();         
}

// JH //
// sigPass : convol. of sigPhysPass and sigResPass (e.g. mcNom histo and Gaussian, for altBkg)
// pdfPass : weighted sum of sigPass and bkgPass(RooCMS for NominalFit & data altSigFit, 0 for mcaltSig, Exponential for altBkg)

void tnpFitter::fits(bool mcTruth,string title, TString FilePath, TString HistName, TString HistNameOS) {

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  setTDRStyle();


  cout << " title : " << title << endl;

  
  RooAbsPdf *pdfPass = _work->pdf("pdfPass"); 
  RooAbsPdf *pdfFail = _work->pdf("pdfFail");

  if( mcTruth ) {
    _work->var("nBkgP")->setVal(0); _work->var("nBkgP")->setConstant();
    _work->var("nBkgF")->setVal(0); _work->var("nBkgF")->setConstant();
    if( _work->var("sosP")   ) { _work->var("sosP")->setVal(0);
      _work->var("sosP")->setConstant(); }
    if( _work->var("sosF")   ) { _work->var("sosF")->setVal(0);
      _work->var("sosF")->setConstant(); }
    if( _work->var("acmsP")  ) _work->var("acmsP")->setConstant();
    if( _work->var("acmsF")  ) _work->var("acmsF")->setConstant();
    if( _work->var("betaP")  ) _work->var("betaP")->setConstant();
    if( _work->var("betaF")  ) _work->var("betaF")->setConstant();
    if( _work->var("gammaP") ) _work->var("gammaP")->setConstant();
    if( _work->var("gammaF") ) _work->var("gammaF")->setConstant();
  }

  /// FC: seems to be better to change the actual range than using a fitRange in the fit itself (???)
  /// FC: I don't know why but the integral is done over the full range in the fit not on the reduced range
  _work->var("x")->setRange(_xFitMin,_xFitMax);
  _work->var("x")->setRange("fitMassRange",_xFitMin,_xFitMax);
  RooFitResult* resPass = pdfPass->fitTo(*_work->data("hPass"),Minos(_useMinos),SumW2Error(kTRUE),Save(),Range("fitMassRange"));
  //RooFitResult* resPass = pdfPass->fitTo(*_work->data("hPass"),Minos(_useMinos),SumW2Error(kTRUE),Save());
  if( _fixSigmaFtoSigmaP ) {
    _work->var("sigmaF")->setVal( _work->var("sigmaP")->getVal() );
    _work->var("sigmaF")->setConstant();
  }

  //_work->var("sigmaF")->setVal(_work->var("sigmaP")->getVal());
  //_work->var("sigmaF")->setRange(0.8* _work->var("sigmaP")->getVal(), 3.0* _work->var("sigmaP")->getVal());
  _work->var("sigmaSS")->setVal(_work->var("sigmaOS")->getVal());
  _work->var("sigmaSS")->setRange(0.8* _work->var("sigmaOS")->getVal(), 3.0* _work->var("sigmaOS")->getVal());
  RooFitResult* resFail = pdfFail->fitTo(*_work->data("hFail"),Minos(_useMinos),SumW2Error(kTRUE),Save(),Range("fitMassRange"));
  //RooFitResult* resFail = pdfFail->fitTo(*_work->data("hFail"),Minos(_useMinos),SumW2Error(kTRUE),Save());

  RooPlot *pPass = _work->var("x")->frame(60,120);
  RooPlot *pFail = _work->var("x")->frame(60,120);
  //RooPlot *pPass = _work->var("x")->frame(50,150);
  //RooPlot *pFail = _work->var("x")->frame(50,150);

  pPass->SetTitle("OS fit");
  pFail->SetTitle("SS fit");
  
  _work->data("hPass") ->plotOn( pPass );
  _work->pdf("pdfPass")->plotOn( pPass, LineColor(kRed) );
  _work->pdf("pdfPass")->plotOn( pPass, Components("bkgPass"),LineColor(kBlue),LineStyle(kDashed));
  _work->data("hPass") ->plotOn( pPass );
  
  _work->data("hFail") ->plotOn( pFail );
  _work->pdf("pdfFail")->plotOn( pFail, LineColor(kRed) );
  _work->pdf("pdfFail")->plotOn( pFail, Components("bkgFail"),LineColor(kBlue),LineStyle(kDashed));
  _work->data("hFail") ->plotOn( pFail );
  
  RooAddPdf* SSsigComponent=(RooAddPdf*)_work->pdf("pdfFail")->getComponents()->find("sigFail");

  TH1* histSS=SSsigComponent->createHistogram("x",30,60,120);

  RooAddPdf* OSsigComponent=(RooAddPdf*)_work->pdf("pdfPass")->getComponents()->find("sigPass");
  TH1* histOS=OSsigComponent->createHistogram("x",30,60,120);
  histOS->SetLineColor(kOrange);
  histOS->SetFillColor(kOrange);
  histSS->SetLineColor(kBlack);
  
  //  histSS->SetLineStyle(kDashed );

  cout << histSS->Integral() << " " << histOS->Integral()  << endl;
  cout << "_work->var(SigSS)->getVal() = " << _work->var("nSigSS")->getVal() << endl;
  cout << "_work->var(nSigOS)->getVal() = " << _work->var("nSigOS")->getVal() << endl;

  double nSS = _work->var("nSigSS")->getVal();
  double nOS = _work->var("nSigOS")->getVal();

  histSS->Scale(nSS);
  histOS->Scale(nOS);
  
  cout << " nSS = " << nSS << endl;
  cout << "FilePath = " << FilePath << endl;
  TFile* file = new TFile(FilePath);
  if( !file ){
      cout << "No file : " << FilePath << endl;
      return;
  }

  cout << "HistNameOS " << HistNameOS << endl;
  cout << "HistName " << HistName << endl;

  TH1D* histOS_NoFit = (TH1D*)file->Get(HistNameOS);
  TH1D* hist_unshifted = (TH1D*)file->Get(HistName);
  hist_unshifted->SetLineColor(kBlue);
  hist_unshifted->SetLineStyle(kDashed );
  hist_unshifted->GetXaxis()->SetRangeUser(60,120);

  cout << "nOS = " << nOS << " hist_unshifted = " << hist_unshifted->Integral() << endl;
  

  TCanvas c("c","c",1100,600);
  //  c.Divide(3,1);
  TPad *padText = (TPad*)c.GetPad(1);
  c.cd(1);
  //textParForCanvas( resPass,resFail, padText );
  //c.cd(2); pFail->Draw();

  c.cd(3); 
  
  //// Set up Main Hist to plot canvas styel
  double Max = histSS->GetMaximum()*1.2;
  if(hist_unshifted->GetMaximum()*1.2 > Max) Max = hist_unshifted->GetMaximum()*1.2 ;
  if(histOS->GetMaximum()*1.2 >Max) Max = histOS->GetMaximum()*1.2 ;
  histSS->GetYaxis()->SetRangeUser(0,Max);
  histSS->GetYaxis()->SetTitle("Event / GeV");
  histSS->GetXaxis()->SetTitle("Mass_{ll} GeV");

  histSS->SetMarkerStyle(20);
  histSS->SetMarkerSize(1.3);
  histSS->SetMarkerColor(kBlack);
  histSS->SetLineColor(kBlack);

  const double alpha = 1 - 0.6827;
  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors(histSS);
  /*for(int i=0; i<gr_data->GetN(); ++i){
    int N = gr_data->GetY()[i];
    double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    double U =  (N==0) ? ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) : ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
    if( N!=0 ){
      gr_data->SetPointEYlow(i, N-L );
      gr_data->SetPointEXlow(i, 0);
      gr_data->SetPointEYhigh(i, U-N );
      gr_data->SetPointEXhigh(i, 0);
    }
    else{
      double zerodata_err_low = 0.1;
      double zerodata_err_high = 1.8;

      double xlow = gr_data->GetX()[i]-gr_data->GetEXlow()[i];
      double xhigh = gr_data->GetX()[i]+gr_data->GetEXhigh()[i];
      if(ZeroDataCheckCut(xlow,xhigh)){
	zerodata_err_low = 0.;
        zerodata_err_high = 0.;
      }

      gr_data->SetPointEYlow(i, zerodata_err_low);
      gr_data->SetPointEXlow(i, 0.);
      gr_data->SetPointEYhigh(i, zerodata_err_high);
      gr_data->SetPointEXhigh(i, 0.);
    }
    }*/

  gr_data->SetLineWidth(2.0);
  gr_data->SetMarkerSize(0.);
  gr_data->SetMarkerColor(kBlack);
  gr_data->SetLineColor(kBlack);
  
  // Draw  HJists on Canvas

  hist_axis(histSS);

  /// Set Bin Error
  for(int i=1 ; i < histSS->GetNbinsX()+1; i++){
    histSS->SetBinError(i,sqrt(histSS->GetBinContent(i)));
    histOS->SetBinError(i,histOS_NoFit->GetBinError(i));
  }


  histSS->Draw();
  histOS->Draw("histsame");
  hist_unshifted->Draw("histsame");
  histSS->Draw("phistsame");
  gr_data->Draw("p0same");


  for(int i=1 ; i < histSS->GetNbinsX()+1; i++){
    cout << "hSS bin value = " << histSS->GetBinContent(i) << " Bin error = " << histSS->GetBinError(i)  << endl;
    cout << "hWOS bin value = " << histOS->GetBinContent(i) << " Bin error = " << histOS->GetBinError(i)  << endl;

  }
  TString Chi2Prompt = "CHI2 WW";
  double chi2_1 = histSS->Chi2Test(histOS,Chi2Prompt);
  //  double chi2_2 = histSS->Chi2Test(hist_unshifted,Chi2Prompt);

  int precisionValCHI2=3;
  std::string trimmedString1 = std::to_string(chi2_1).substr(0, std::to_string(chi2_1).find(".") + precisionValCHI2 + 1);   
  //std::string trimmedString2 = std::to_string(chi2_2).substr(0, std::to_string(chi2_2).find(".") + precisionValCHI2 + 1);   
  TString labelChi2 = "Chi2 =" + TString(trimmedString1) ;
  
  //  TString label2Chi2 = "Chi2 [NoShift]=" + TString(trimmedString2) ;
  TLatex channelname;
  channelname.SetNDC();
  channelname.SetTextSize(0.03);
  channelname.DrawLatex(0.2, 0.55, labelChi2);
  //  channelname.DrawLatex(0.2, 0.5, label2Chi2);
  TString EtaBin = "BB ";
  if(HistName.Contains("EE")) EtaBin = "EE ";
  if(HistName.Contains("BE")) EtaBin = "BE ";
  if(HistName.Contains("2016a")) EtaBin += " 2016a";
  if(HistName.Contains("2016b")) EtaBin += " 2016b";
  if(HistName.Contains("2017")) EtaBin += " 2017";
  if(HistName.Contains("2018")) EtaBin += " 2018";
				
  channelname.DrawLatex(0.2, 0.85, EtaBin);
  TString snSS = DToString(nSS,2);
  TString snOS = DToString(nOS,2);
  TString snOSUncor = DToString(hist_unshifted->Integral(),2);
  TLegend *lg= new TLegend(0.65, 0.6, 0.93, 0.85);
  lg->SetTextSize(0.03);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  lg->AddEntry(histSS,"SS Observed ["+snSS+"]","p");
  lg->AddEntry(histOS,"SS Predicted ["+snOS+"]","f");
  lg->Draw();


  TLegend *lg_left= new TLegend(0.2, 0.65, 0.35, 0.90);
  lg_left->SetTextSize(0.03);
  lg_left->SetFillStyle(0);
  lg_left->SetBorderSize(0);
  lg_left->AddEntry(hist_unshifted,"#splitline{SS Predicted }{ no SF/E_{shift}} ["+snOSUncor+"]","l");
  lg_left->Draw();


  _fOut->cd();



  c.Write(TString::Format("%s_Canv",_histname_base.c_str()),TObject::kOverwrite);
  resPass->Write(TString::Format("%s_resP",_histname_base.c_str()),TObject::kOverwrite);
  resFail->Write(TString::Format("%s_resF",_histname_base.c_str()),TObject::kOverwrite);

  c.SaveAs(TString::Format("%s/%s_Canv.pdf",_filename_base.c_str(),_histname_base.c_str())); // JH
  
}





/////// Stupid parameter dumper /////////
void tnpFitter::textParForCanvas(RooFitResult *resP, RooFitResult *resF,TPad *p) {

  double eff = -1;
  double e_eff = 0;

  //RooRealVar *nSigP = _work->var("nSigP");
  //RooRealVar *nSigF = _work->var("nSigF");
  RooRealVar *nSigP = _work->var("nSigOS");
  RooRealVar *nSigF = _work->var("nSigSS");
  
  double nP   = nSigP->getVal();
  double e_nP = nSigP->getError();
  double nF   = nSigF->getVal();
  double e_nF = nSigF->getError();
  double nTot = nP+nF;
  //eff = nP / (nP+nF);
  eff = nF / nP; //JH
  //e_eff = 1./(nTot*nTot) * sqrt( nP*nP* e_nF*e_nF + nF*nF * e_nP*e_nP );
  e_eff = eff * sqrt( 1./nF + 1./nP );

  TPaveText *text1 = new TPaveText(0,0.8,1,1);
  text1->SetFillColor(0);
  text1->SetBorderSize(0);
  text1->SetTextAlign(12);

  text1->AddText(TString::Format("* fit status OS: %d, SS : %d",resP->status(),resF->status()));
  text1->AddText(TString::Format("* Scalefactor = %1.4f #pm %1.4f",eff,e_eff));

  //  text->SetTextSize(0.06);

  //  text->AddText("* Passing parameters");
  TPaveText *text = new TPaveText(0,0,1,0.8);
  text->SetFillColor(0);
  text->SetBorderSize(0);
  text->SetTextAlign(12);
  text->AddText("    --- parmeters " );
  RooArgList listParFinalP = resP->floatParsFinal();
  for( int ip = 0; ip < listParFinalP.getSize(); ip++ ) {
    TString vName = listParFinalP[ip].GetName();
    text->AddText(TString::Format("   - %s \t= %1.3f #pm %1.3f",
				  vName.Data(),
				  _work->var(vName)->getVal(),
				  _work->var(vName)->getError() ) );
  }

  //  text->AddText("* Failing parameters");
  RooArgList listParFinalF = resF->floatParsFinal();
  for( int ip = 0; ip < listParFinalF.getSize(); ip++ ) {
    TString vName = listParFinalF[ip].GetName();
    text->AddText(TString::Format("   - %s \t= %1.3f #pm %1.3f",
				  vName.Data(),
				  _work->var(vName)->getVal(),
				  _work->var(vName)->getError() ) );
  }

  p->cd();
  text1->Draw();
  text->Draw();
}


void tnpFitter::setTDRStyle() {

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  char* ch = "4.4f";
  tdrStyle->SetPaintTextFormat(ch);
  // For the canvas:                                                                                                                                                                                                                       
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas                                                                                                                                                                                         
  tdrStyle->SetCanvasDefW(600); //Width of canvas                                                                                                                                                                                          
  tdrStyle->SetCanvasDefX(0);   //POsition on screen                                                                                                                                                                                       
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:                                                                                                                                                                                                                          
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the histo:                                                                                                                                                                                                                        
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);

  tdrStyle->SetEndErrorSize(2);
  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:                                                                                                                                                                                                                  
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);
  //For the date:                                                                                                                                                                                                                          
  tdrStyle->SetOptDate(0);

  // For the statistics box:                                                                                                                                                                                                               
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");                                                                                                                                                             
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);

  // Margins:                                                                                                                                                                                                                              
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

  // For the Global title:                                                                                                                                                                                                                 

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // For the axis titles:                                                                                                                                                                                                                  
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleColor(4, "Z");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(1.2);
  //  tdrStyle->SetTitleXOffset(1.5);                                                                                                                                                                                                      
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);

  // For the axis labels:                                                                                                                                                                                                                  
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");


  // For the axis:                                                                                                                                                                                                                         
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame                                                                                                                                                        
  tdrStyle->SetPadTickY(1);
  // Change for log plots:                                                                                                                                                                                                                 
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:                                                                                                                                                                                                                   
  tdrStyle->SetPaperSize(20.,20.);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);
  tdrStyle->cd();

}

