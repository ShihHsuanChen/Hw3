// Fit_test.cc

#include <stdio.h>

#include "TFile.h"
#include "TH1F.h"
#include "TNtupleD.h"
#include "TCanvas.h"

#include "RooFit.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooGaussModel.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooPolynomial.h"
#include "RooFitResult.h"

using namespace std;
using namespace RooFit;

int main(){

  TFile* ofp = new TFile("result.root","RECREATE");
  RooRealVar mass("mass","mass",5.,5.8);

// Fit Signal
  TFile* fin_signal  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_signal.root","READ");

  TNtupleD* nt_signal = (TNtupleD*) fin_signal->Get("nt");

  TH1F* hdata_signal = new TH1F("hdata_signal",";mass;# of event",160,5,5.8);
  nt_signal->Draw("mass >> hdata_signal");

  int Nevt_signal = nt_signal->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooDataSet* data_signal = new RooDataSet("data_signal","data",nt_signal,RooArgSet(mass));

  // build Model : 3-gaussian model
  RooRealVar    mu1_signal("mu1_signal","mu1",5.25,5,5.8);
  RooRealVar    mu2_signal("mu2_signal","mu2",5.25,5,5.8);
  RooRealVar    mu3_signal("mu3_signal","mu3",5.25,5,5.8);
  RooRealVar    sigma1_signal("sigma1_signal","sigma1",0.03,0,0.5);
  RooRealVar    sigma2_signal("sigma2_signal","sigma2",0.03,0,0.5);
  RooRealVar    sigma3_signal("sigma3_signal","sigma3",0.03,0,0.5);
  RooRealVar    frac1_signal("frac1_signal","frac1",0.,1.);
  RooRealVar    frac2_signal("frac2_signal","frac2",0.,1.);
  RooGaussModel gaus1_signal("gaus1_signal","gaus1",mass,mu1_signal,sigma1_signal);
  RooGaussModel gaus2_signal("gaus2_signal","gaus2",mass,mu2_signal,sigma2_signal);
  RooGaussModel gaus3_signal("gaus3_signal","gaus3",mass,mu3_signal,sigma3_signal);

  RooAddPdf     model_signal("model_signal","model",RooArgList(gaus1_signal,gaus2_signal,gaus3_signal),RooArgList(frac1_signal,frac2_signal));
  
  // fit to distribution
  model_signal.fitTo(*data_signal,Minos(true));

  // fix parameters
  mu1_signal.setConstant(kTRUE);
  mu2_signal.setConstant(kTRUE);
  mu3_signal.setConstant(kTRUE);
  sigma1_signal.setConstant(kTRUE);
  sigma2_signal.setConstant(kTRUE);
  sigma3_signal.setConstant(kTRUE);
  frac1_signal.setConstant(kTRUE);
  frac2_signal.setConstant(kTRUE);

  RooPlot* frame_signal = mass.frame();
  data_signal->plotOn(frame_signal);
  model_signal.plotOn(frame_signal);
  model_signal.plotOn(frame_signal,Components(gaus1_signal),LineStyle(kDashed));
  model_signal.plotOn(frame_signal,Components(gaus2_signal),LineStyle(kDashed));
  model_signal.plotOn(frame_signal,Components(gaus3_signal),LineStyle(kDashed));

  fin_signal->Close();
  fin_signal = NULL;

// Fit psipi

  TFile* fin_psipi  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_psipi.root","READ");

  TNtupleD* nt_psipi = (TNtupleD*) fin_psipi->Get("nt");

  TH1F* hdata_psipi = new TH1F("hdata_psipi",";mass;# of event",160,5,5.8);
  nt_psipi->Draw("mass >> hdatapsipi");

  int Nevt_psipi = nt_psipi->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooDataSet* data_psipi = new RooDataSet("data_psipi","data",nt_psipi,RooArgSet(mass));

  // build Model : 3-gaussian model
  RooRealVar    mu1_psipi("mu1_psipi","mu1",5.25,5,5.8);
  RooRealVar    mu2_psipi("mu2_psipi","mu2",5.45,5,5.8);
  RooRealVar    mu3_psipi("mu3_psipi","mu3",5.35,5,5.8);
  RooRealVar    sigma1_psipi("sigma1_psipi","sigma1",0.03,0.5,3.);
  RooRealVar    sigma2_psipi("sigma2_psipi","sigma2",0.03,0.01,2.);
  RooRealVar    sigma3_psipi("sigma3_psipi","sigma3",0.03,0.01,2.);
  RooRealVar    frac1_psipi("frac1_psipi","frac1",0.001,1.);
  RooRealVar    frac2_psipi("frac2_psipi","frac2",0.001,1.);
  RooGaussModel gaus1_psipi("gaus1_psipi","gaus1",mass,mu1_psipi,sigma1_psipi);
  RooGaussModel gaus2_psipi("gaus2_psipi","gaus2",mass,mu2_psipi,sigma2_psipi);
  RooGaussModel gaus3_psipi("gaus3_psipi","gaus3",mass,mu3_psipi,sigma3_psipi);

  RooAddPdf     model_psipi("model_psipi","model",RooArgList(gaus1_psipi,gaus2_psipi,gaus3_psipi),RooArgList(frac1_psipi,frac2_psipi));
  
  // fit to distribution
  model_psipi.fitTo(*data_psipi,Minos(true));

  // fix parameters
  mu1_psipi.setConstant(kTRUE);
  mu2_psipi.setConstant(kTRUE);
  mu3_psipi.setConstant(kTRUE);
  sigma1_psipi.setConstant(kTRUE);
  sigma2_psipi.setConstant(kTRUE);
  sigma3_psipi.setConstant(kTRUE);
  frac1_psipi.setConstant(kTRUE);
  frac2_psipi.setConstant(kTRUE);

  RooPlot* frame_psipi = mass.frame();
  data_psipi->plotOn(frame_psipi);
  model_psipi.plotOn(frame_psipi);
  model_psipi.plotOn(frame_psipi,Components(gaus1_psipi),LineStyle(kDashed));
  model_psipi.plotOn(frame_psipi,Components(gaus2_psipi),LineStyle(kDashed));
  model_psipi.plotOn(frame_psipi,Components(gaus3_psipi),LineStyle(kDashed));

  fin_psipi->Close();
  fin_psipi = NULL;

// Fit psihadrons

  TFile* fin_psihad  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_psihadrons.root","READ");

  TNtupleD* nt_psihad = (TNtupleD*) fin_psihad->Get("nt");

  TH1F* hdata_psihad = new TH1F("hdata_psihad",";mass;# of event",160,5,5.8);
  nt_psihad->Draw("mass >> hdata_psihad");

  int Nevt_psihad = nt_psihad->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooDataSet* data_psihad = new RooDataSet("data_psihad","data",nt_psihad,RooArgSet(mass));

  // build Model : crystal ball
  RooRealVar mu_psihad("mu_psihad","mu",5.1,5,5.8);
  RooRealVar sigma_psihad("sigma_psihad","sigma",0.001,0.1);
  RooRealVar alpha_psihad("alpha_psihad","alpha",0.1,0.0001,1);
  RooRealVar n_psihad("n_psihad","n",1,0,10);

  RooCBShape model_psihad("model_psihad","model",mass,mu_psihad,sigma_psihad,alpha_psihad,n_psihad);
 
  // fit to distribution
  model_psihad.fitTo(*data_psihad,Minos(true));

  // fix parameters
  mu_psihad.setConstant(kTRUE);
  sigma_psihad.setConstant(kTRUE);
  alpha_psihad.setConstant(kTRUE);
  n_psihad.setConstant(kTRUE);

  RooPlot* frame_psihad = mass.frame();
  data_psihad->plotOn(frame_psihad);
  model_psihad.plotOn(frame_psihad);

  fin_psihad->Close();
  fin_psihad = NULL;

// Fit all

  TFile* ifp = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_exdata.root","READ");
  TNtupleD* nt = (TNtupleD*) ifp->Get("nt");

  RooDataSet* data = new RooDataSet("data","data",nt,RooArgSet(mass));

  // build extened likelihood model
  RooRealVar ns("ns","signal"       ,100,1.,20000.);
  RooRealVar np("np","psipi"        ,100,0.,20000.);
  RooRealVar nh("nh","psihadrons"   ,100,1.,20000.);
  RooRealVar nc("nc","combinatorial",100,0.,20000.);

  RooRealVar slope("slope","slope",10.,-100.,100.);

  RooPolynomial model_comb("model_comb","model_comb",mass,RooArgSet(slope));

  RooAddPdf  model("model","model",RooArgList(model_signal,model_psipi,model_psihad,model_comb),RooArgList(ns,np,nh,nc));
  
  // fit to distribution
  RooFitResult* result = model.fitTo(*data,Minos(true),Extended(),Save());
  result->Print();

  printf("\nfinish!!!\n");

  ofp->cd();

  RooPlot* frame = mass.frame();
  data->plotOn(frame);
  model.plotOn(frame);
  model.plotOn(frame,Components(model_signal),LineStyle(kDashed));
  model.plotOn(frame,Components(model_psipi ),LineStyle(kDashed));
  model.plotOn(frame,Components(model_psihad),LineStyle(kDashed));
  model.plotOn(frame,Components(model_comb  ),LineStyle(kDashed));

  frame_signal->Write("frame_signal");
  frame_psipi ->Write("frame_psipi");
  frame_psihad->Write("frame_psihad");
  frame->Write("rooframe");
  model.Write("model");

  ofp->Close();

  ifp->Close();
}
