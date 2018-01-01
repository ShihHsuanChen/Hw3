// Fit_extended.cc

#include <stdio.h>

#include "TFile.h"
#include "TH1F.h"
#include "TNtupleD.h"
#include "TCanvas.h"

#include "RooFit.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooPolynomial.h"
#include "RooAbsPdf.h"
#include "RooCBShape.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"

using namespace std;
using namespace RooFit;

int main(){

  TFile* fin  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_exdata.root","READ");
  TFile* fout = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/Fit_Extended/result.root","RECREATE");

  TNtupleD* nt = (TNtupleD*) fin->Get("nt");

  TH1F* hdata = new TH1F("hdata",";mass;# of event",160,5,5.8);
  nt->Draw("mass >> hdata");

  int Nevt = nt->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooRealVar mass("mass","mass",5,5.8);
  RooDataSet* data = new RooDataSet("data","data",nt,RooArgSet(mass));

  // build Model : signal, psipi, psihadrons from PDF root file + 2nd order polynomial combinatorial background
  RooRealVar ns("ns","signal"       ,100,1.,20000.);
  RooRealVar np("np","psipi"        ,100,0.,20000.);
  RooRealVar nh("nh","psihadrons"   ,100,1.,20000.);
  RooRealVar nc("nc","combinatorial",100,0.,20000.);

  RooRealVar slope("slope","slope",10.,-100.,100.);

  RooPolynomial* model_comb = new RooPolynomial("model_comb","model_comb",mass,RooArgSet(slope));

  // import pdf
  TFile* fpdf1 = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/PDF/PDF_signal.root","READ");
  TFile* fpdf2 = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/PDF/PDF_psipi.root","READ");
  TFile* fpdf3 = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/PDF/PDF_psihadrons.root","READ");

  RooAddPdf*  model_signal     = (RooAddPdf*)  fpdf1->Get("model_signal");
  RooAddPdf*  model_psipi      = (RooAddPdf*)  fpdf2->Get("model_psipi");
  RooCBShape* model_psihadrons = (RooCBShape*) fpdf3->Get("model_psihad");

  RooAddPdf  model("model","model",RooArgList(*model_signal,*model_psipi,*model_psihadrons,*model_comb),RooArgList(ns,np,nh,nc));
  
  // fit to distribution
  RooFitResult* result = model.fitTo(*data,Minos(true),Extended(),Save());
  result->Print();

  RooPlot* frame = mass.frame();
  data->plotOn(frame);
  model.plotOn(frame);
  model.plotOn(frame,Components(*model_signal    ),LineStyle(kDashed));
  model.plotOn(frame,Components(*model_psipi     ),LineStyle(kDashed));
  model.plotOn(frame,Components(*model_psihadrons),LineStyle(kDashed));
  model.plotOn(frame,Components(*model_comb      ),LineStyle(kDashed));

  fout->cd();
  frame->Write("rooframe");
  model.Write("model");
  hdata->Write();
  fout->Close();
  fpdf1->Close();
  fpdf2->Close();
  fpdf3->Close();
  fin->Close();
}
