#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"
#include "classes/DelphesStream.h"
#include "classes/SortableObject.h"
#include "modules/Delphes.h"
#include "external/ExRootAnalysis/ExRootProgressBar.h"
#include "external/ExRootAnalysis/ExRootTreeBranch.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootTreeWriter.h"
#include "external/ExRootAnalysis/ExRootTask.h"
#endif
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TH1.h>
#include <TCanvas.h>

void deltaPhiH(const char *inputFile, const char *outputFile){
     gSystem->Load("libDelphes.so");
     TFile *file_sig = new TFile(inputFile);
     TFile *output = new TFile(outputFile, "recreate");
     TTree *tree_sig = (TTree*)file_sig->Get("Delphes");
     TTree *tree_output = new TTree("tree_output","Delphes");

     Int_t nEntries = tree_sig->GetEntries();
     TH1F *DeltaPhiH = new TH1F("DeltaPhi", "DeltaPhi", 100 , -4, 4); 
   
 

     TLeaf *EPhi = tree_sig->GetLeaf("Electron.Phi");
     TLeaf *MPhi = tree_sig->GetLeaf("Muon.Phi");
     TLeaf *Esize = tree_sig->GetLeaf("Electron_size");
     TLeaf *Msize = tree_sig->GetLeaf("Muon_size");


     Float_t ElectronPhi;
     Float_t MuonPhi;
     Float_t DeltaPhi;
     for(Long64_t entry=0; entry < nEntries; entry++){
        tree_sig->GetEntry(entry);
        tree_output->GetEntry(entry);
        Int_t nEsize = Esize->GetValue();
        MPhi->GetBranch()->GetEntry(entry);
        EPhi->GetBranch()->GetEntry(entry);
        for(Long64_t entry1=0; entry1 < nEsize; entry1++){
	   ElectronPhi = EPhi->GetValue(entry1);
	   MuonPhi = MPhi->GetValue(entry1);
	   DeltaPhi = ElectronPhi-MuonPhi;
               DeltaPhiH->Fill(DeltaPhi);
     }
     }
     TCanvas *mycanvas = new TCanvas("mycanvas","My Canvas",1200,1200);
     DeltaPhiH->Draw();
     DeltaPhiH->GetXaxis()->SetTitle("Radians");
     DeltaPhiH->GetYaxis()->SetTitle("number of events");
     mycanvas->SaveAs("DeltaPhi.png");

     DeltaPhiH->Write();
     tree_output->Write();
     output->Close();
     file_sig->Close();
}