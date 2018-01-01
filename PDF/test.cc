
void test(){

  using namespace RooFit;

  TFile* fin  = new TFile("/home/user/workspace/projects/StatisitcParticle_HW_executable/Hw3/example_exdata.root","READ");
  TNtupleD* nt = (TNtupleD*) fin->Get("nt");

  RooRealVar mass("mass","mass",5.,5.8);
  RooDataSet* data = new RooDataSet("data","data",nt,RooArgSet(mass));

  TFile* f2 = new TFile("PDF_signal.root","READ");
  RooAbsPdf* model = (RooAbsPdf*) f2->Get("model");

  model->fitTo(*data,Minos(true));
  RooPlot* frame = mass.frame();
  data->plotOn(frame);
  model->plotOn(frame);
  frame->Draw();
}
