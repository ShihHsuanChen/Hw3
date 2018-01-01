// make_pdf_psihadrons.cc

#include <stdio.h>

#include "TFile.h"
#include "TH1F.h"
#include "TNtupleD.h"
#include "TCanvas.h"

#include "RooFit.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooCBShape.h"

using namespace std;
using namespace RooFit;

int main(){

  TFile* fin  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_psihadrons.root","READ");
  TFile* fout = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/PDF/PDF_psihadrons.root","RECREATE");

  TNtupleD* nt = (TNtupleD*) fin->Get("nt");

  TH1F* hdata = new TH1F("hdata",";mass;# of event",160,5,5.8);
  nt->Draw("mass >> hdata");

  int Nevt = nt->GetEntries();

  // RooDataSet
  printf("Access data from file\n");

  RooRealVar mass("mass","mass",5.,5.8);
  RooDataSet* data = new RooDataSet("data","data",nt,RooArgSet(mass));

  // build Model : crystal ball
  RooRealVar mu("mu","mu",5.1,5,5.8);
  RooRealVar sigma("sigma","sigma",0.001,0.1);
  RooRealVar alpha("alpha","alpha",0.1,0.0001,1);
  RooRealVar n("n","n",1,0,10);

  RooCBShape model("model","model",mass,mu,sigma,alpha,n);
 
  // fit to distribution
  model.fitTo(*data,Minos(true));

  // fix parameters
  mu.setConstant(kTRUE);
  sigma.setConstant(kTRUE);
  alpha.setConstant(kTRUE);
  n.setConstant(kTRUE);

  RooPlot* frame = mass.frame();
  data->plotOn(frame);
  model.plotOn(frame);

  fout->cd();
  frame->Write("rooframe");
  model.Write("model_psihad");
  hdata->Write();
  fout->Close();
}
