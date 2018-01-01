// make_pdf_psipi.cc

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

using namespace std;
using namespace RooFit;

int main(){

  TFile* fin  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_psipi.root","READ");
  TFile* fout = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/PDF/PDF_psipi.root","RECREATE");

  TNtupleD* nt = (TNtupleD*) fin->Get("nt");

  TH1F* hdata = new TH1F("hdata",";mass;# of event",160,5,5.8);
  nt->Draw("mass >> hdata");

  int Nevt = nt->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooRealVar mass("mass","mass",5.,5.8);
  RooDataSet* data = new RooDataSet("data","data",nt,RooArgSet(mass));

  // build Model : 3-gaussian model
  RooRealVar    mu1("mu1","mu1",5.25,5,5.8);
  RooRealVar    mu2("mu2","mu2",5.45,5,5.8);
  RooRealVar    mu3("mu3","mu3",5.35,5,5.8);
  RooRealVar    sigma1("sigma1","sigma1",0.03,0.5,3.);
  RooRealVar    sigma2("sigma2","sigma2",0.03,0.01,2.);
  RooRealVar    sigma3("sigma3","sigma3",0.03,0.01,2.);
  RooRealVar    frac1("frac1","frac1",0.001,1.);
  RooRealVar    frac2("frac2","frac2",0.001,1.);
  RooGaussModel gaus1("gaus1","gaus1",mass,mu1,sigma1);
  RooGaussModel gaus2("gaus2","gaus2",mass,mu2,sigma2);
  RooGaussModel gaus3("gaus3","gaus3",mass,mu3,sigma3);

  RooAddPdf     model("model","model",RooArgList(gaus1,gaus2,gaus3),RooArgList(frac1,frac2));
//  RooAddPdf     model("model","model",RooArgList(gaus1,gaus2),RooArgList(frac1));
  
  // fit to distribution
  model.fitTo(*data,Minos(true));

  // fix parameters
  mu1.setConstant(kTRUE);
  mu2.setConstant(kTRUE);
  mu3.setConstant(kTRUE);
  sigma1.setConstant(kTRUE);
  sigma2.setConstant(kTRUE);
  sigma3.setConstant(kTRUE);
  frac1.setConstant(kTRUE);
  frac2.setConstant(kTRUE);

  RooPlot* frame = mass.frame();
  data->plotOn(frame);
  model.plotOn(frame);
  model.plotOn(frame,Components(gaus1),LineStyle(kDashed));
  model.plotOn(frame,Components(gaus2),LineStyle(kDashed));
  model.plotOn(frame,Components(gaus3),LineStyle(kDashed));

  fout->cd();
  frame->Write("rooframe");
  model.Write("model_psipi");
  hdata->Write();
  fout->Close();
}
