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

void HiggsPtM(const char *inputFile, const char *outputFile){
     gSystem->Load("libDelphes.so");
     TFile *file_sig = new TFile(inputFile);
     TFile *output = new TFile(outputFile, "recreate");
     TTree *tree_sig = (TTree*)file_sig->Get("Delphes");
     TTree *tree_output = new TTree("tree_output","Delphes");

     Int_t nEntries = tree_sig->GetEntries();
     TH1F *HiggsPTH = new TH1F("HiggsPT", "HiggsPT", 100 , 0, 400); 
     TH1F *HiggsMagH = new TH1F("HiggsInvariantMass", "HiggsInvariantMass", 100 , 0, 20); 
 
     TLeaf *EEta = tree_sig->GetLeaf("Electron.Eta");
     TLeaf *MEta = tree_sig->GetLeaf("Muon.Eta");
     TLeaf *EPhi = tree_sig->GetLeaf("Electron.Phi");
     TLeaf *MPhi = tree_sig->GetLeaf("Muon.Phi");
     TLeaf *EPt = tree_sig->GetLeaf("Electron.PT");
     TLeaf *MPt = tree_sig->GetLeaf("Muon.PT");
     
     TLeaf *Esize = tree_sig->GetLeaf("Electron_size");
     TLeaf *Msize = tree_sig->GetLeaf("Muon_size");

     TLorentzVector Electronjet;
     TLorentzVector Muonjet;
     TLorentzVector Higgsjet;

     Float_t ElectronEta;
     Float_t MuonEta;
     Float_t ElectronPhi;
     Float_t MuonPhi;
     Float_t ElectronPt;
     Float_t MuonPt;
     Float_t HiggsPt;
     Float_t HiggsMag;
     for(Long64_t entry=0; entry < nEntries; entry++){
        tree_sig->GetEntry(entry);
        tree_output->GetEntry(entry);
        Int_t nEsize = Esize->GetValue();
        EEta->GetBranch()->GetEntry(entry);
        MEta->GetBranch()->GetEntry(entry);
        EPhi->GetBranch()->GetEntry(entry);
        MPhi->GetBranch()->GetEntry(entry);
        MPt->GetBranch()->GetEntry(entry);
        EPt->GetBranch()->GetEntry(entry);
        for(Long64_t entry1=0; entry1 < nEsize; entry1++){
	   ElectronEta = EEta->GetValue(entry1);
	   MuonEta = MEta->GetValue(entry1);
	   ElectronPhi = EPhi->GetValue(entry1);
	   MuonPhi= MPhi->GetValue(entry1);	   
	   ElectronPt = EPt->GetValue(entry1);
	   MuonPt = MPt->GetValue(entry1);

	   Electronjet.SetPtEtaPhiM(ElectronPt, ElectronEta, ElectronPhi, 0);
                   Muonjet.SetPtEtaPhiM(MuonPt, MuonEta, MuonPhi, 0);
                   Higgsjet=Electronjet+Muonjet;

               HiggsPt=Higgsjet.Pt();
               HiggsMag=Higgsjet.M();
               HiggsPTH->Fill(HiggsPt);
               HiggsMagH->Fill(HiggsMag);
     }
     }

     TCanvas *mycanvas = new TCanvas("mycanvas","My Canvas",1200,1200);
     HiggsPTH->Draw();
     HiggsPTH->GetXaxis()->SetTitle("GeV");
     HiggsPTH->GetYaxis()->SetTitle("Events");
     mycanvas->SaveAs("HiggsPT.png");
     HiggsMagH->Draw();
     HiggsMagH->GetXaxis()->SetTitle("GeV");
     HiggsMagH->GetYaxis()->SetTitle("Events");
     mycanvas->SaveAs("HiggsMag.png");

     HiggsPTH->Write();
     HiggsMagH->Write();
     tree_output->Write();
     output->Close();
     file_sig->Close();
}
