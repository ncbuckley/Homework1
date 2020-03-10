#include <sys/time.h>
#include <gsl/gsl_rng.h>
#include "file2.h"
#include <TLeaf.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBrowser.h>


//Generates n random double presciscion numbers, creates a ROOT file
// and enters the numbers into a ROOT histogram

int main() {
  
  double a = 5;
  double b = 20;
  int n = 100000;
  int bins = 250;
  
  //Creates a TFile containing a TTree t1 with one Branch containing double  n1
  TFile nums("random_nums.root","recreate"); 
  TTree* t1 = new TTree("t1","Tree with random numbers");
  Double_t n1;
  Int_t ev;
  t1->Branch("n1",&n1,"n1/D");
    
  //Creates a 1D Histogram file with random double elements in range (a,b-a)
  TFile* oFile = TFile::Open("Hist_random.root", "recreate");
  TH1D* Hist_n1 = new TH1D("n1", "Random Numbers", bins, a, b-a);
    
  //Fills TTree with n random numbers using the RandomReal function and a,b for n elements
  for (Int_t i=0;i<n;i++) {
    n1 = RandomReal(a,b);
    ev = i;
    t1->Fill();
    }
    
  //Iterates through TTree t1 and fills the histogram Hist_n1 with the n1 values in t1
  for (Int_t j=0;j<n;j++) {
    t1->GetEntry(j);
    Double_t entry = t1->GetLeaf("n1")->GetValue(0);
    Hist_n1->Fill(entry);
    }
    
  oFile->Write();
  oFile->Close();

  return 0;  
}
