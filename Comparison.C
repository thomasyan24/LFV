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

void Comparison(const char *inputFile, const char *inputFile2, const char *outputFile){
     gSystem->Load("libDelphes.so");
     TFile *file_sig = new TFile(inputFile);
     TFile *file_bg = new TFile(inputFile2);
     TFile *output = new TFile(outputFile, "recreate");
     TTree *tree_sig = (TTree*)file_sig->Get("Delphes");
     TTree *tree_bg = (TTree*)file_bg->Get("Delphes");
     TTree *tree_output = new TTree("tree_output","Delphes");

     Int_t nEntries = tree_sig->GetEntries();
     TH1F *EPtCompareH = new TH1F("EPtCompare", "EPtCompare", 100 , -3, 3); 
     TH1F *EEtaCompareH = new TH1F("EEtaCompare", "EEtaCompare", 100 , -3, 3); 
     TH1F *EPhiCompareH = new TH1F("EPhiCompare", "EPhiCompare", 100 , -3, 3); 
     TH1F *MPtCompareH = new TH1F("MPtCompare", "MPtCompare", 100 , -3, 3); 
     TH1F *MEtaCompareH = new TH1F("MEtaCompare", "MEtaCompare", 100 , -3, 3); 
     TH1F *MPhiCompareH = new TH1F("MPhiCompare", "MPhiCompare", 100 , -3, 3); 
     TH1F *EPtCompareH1 = new TH1F("EPtCompare1", "EPtCompare1", 100 , -3, 3); 
     TH1F *EEtaCompareH1 = new TH1F("EEtaCompare1", "EEtaCompare1", 100 , -3, 3); 
     TH1F *EPhiCompareH1 = new TH1F("EPhiCompare1", "EPhiCompare1", 100 , -3, 3); 
     TH1F *MPtCompareH1 = new TH1F("MPtCompare1", "MPtCompare1", 100 , -3, 3); 
     TH1F *MEtaCompareH1 = new TH1F("MEtaCompare1", "MEtaCompare1", 100 , -3, 3); 
     TH1F *MPhiCompareH1 = new TH1F("MPhiCompare1", "MPhiCompare1", 100 , -3, 3); 


     TLeaf *EEtaSig = tree_sig->GetLeaf("Electron.Eta");
     TLeaf *MEtaSig = tree_sig->GetLeaf("Muon.Eta");
     TLeaf *EPhiSig = tree_sig->GetLeaf("Electron.Phi");
     TLeaf *MPhiSig = tree_sig->GetLeaf("Muon.Phi");
     TLeaf *EPtSig = tree_sig->GetLeaf("Electron.PT");
     TLeaf *MPtSig = tree_sig->GetLeaf("Muon.PT");
     TLeaf *EEtaBg = tree_bg->GetLeaf("Electron.Eta");
     TLeaf *MEtaBg = tree_bg->GetLeaf("Muon.Eta");
     TLeaf *EPhiBg = tree_bg->GetLeaf("Electron.Phi");
     TLeaf *MPhiBg = tree_bg->GetLeaf("Muon.Phi");
     TLeaf *EPtBg = tree_bg->GetLeaf("Electron.PT");
     TLeaf *MPtBg = tree_bg->GetLeaf("Muon.PT");
     
     TLeaf *EsizeSig = tree_sig->GetLeaf("Electron_size");
     TLeaf *MsizeSig = tree_sig->GetLeaf("Muon_size");
     TLeaf *EsizeBg = tree_bg->GetLeaf("Electron_size");
     TLeaf *MsizeBg = tree_bg->GetLeaf("Muon_size");

     Float_t ElectronEtaSig;
     Float_t MuonEtaSig;
     Float_t ElectronPhiSig;
     Float_t MuonPhiSig;
     Float_t ElectronPtSig;
     Float_t MuonPtSig;
     Float_t ElectronEtaBg;
     Float_t MuonEtaBg;
     Float_t ElectronPhiBg;
     Float_t MuonPhiBg;
     Float_t ElectronPtBg;
     Float_t MuonPtBg;

     for(Long64_t entry=0; entry < nEntries; entry++){
        tree_sig->GetEntry(entry);
        tree_bg->GetEntry(entry);
        tree_output->GetEntry(entry);

        Int_t nEsize = EsizeSig->GetValue();
        Int_t nMsize=MsizeSig->GetValue();
        Int_t nEsize1 = EsizeBg->GetValue();
        Int_t nMsize1 =MsizeBg->GetValue();

        EEtaSig->GetBranch()->GetEntry(entry);
        MEtaSig->GetBranch()->GetEntry(entry);
        EPhiSig->GetBranch()->GetEntry(entry);
        MPhiSig->GetBranch()->GetEntry(entry);
        MPtSig->GetBranch()->GetEntry(entry);
        EPtSig->GetBranch()->GetEntry(entry);
        EEtaBg->GetBranch()->GetEntry(entry);
        MEtaBg->GetBranch()->GetEntry(entry);
        EPhiBg->GetBranch()->GetEntry(entry);
        MPhiBg->GetBranch()->GetEntry(entry);
        MPtBg->GetBranch()->GetEntry(entry);
        EPtBg->GetBranch()->GetEntry(entry);

        for(Long64_t entry1=0; entry1 < nEsize; entry1++){
             if (nEsize!=0){

                   ElectronEtaSig = EEtaSig->GetValue(entry1);
	   ElectronPhiSig = EPhiSig->GetValue(entry1);  
	   ElectronPtSig = EPtSig->GetValue(entry1);

                   EPtCompareH ->Fill(ElectronPtSig);
                   EEtaCompareH ->Fill(ElectronEtaSig);
                   EPhiCompareH ->Fill(ElectronPhiSig);
 
     }
     }

        for(Long64_t entry1=0; entry1 < nEsize1; entry1++){
             if (nEsize1!=0){

                   ElectronEtaBg = EEtaBg->GetValue(entry1);
	   ElectronPhiBg = EPhiBg->GetValue(entry1);  
	   ElectronPtBg = EPtBg->GetValue(entry1);

                   EPtCompareH1 ->Fill(ElectronPtBg);
                   EEtaCompareH1 ->Fill(ElectronEtaBg);
                   EPhiCompareH1 ->Fill(ElectronPhiBg);
 
     }
     }

        for(Long64_t entry1=0; entry1 < nMsize; entry1++){
             if (nMsize!=0){

                   MuonEtaSig = MEtaSig->GetValue(entry1);
	   MuonPhiSig = MPhiSig->GetValue(entry1);  
	   MuonPtSig = MPtSig->GetValue(entry1);

                   MPtCompareH ->Fill(MuonPtSig);
                   MEtaCompareH ->Fill(MuonEtaSig);
                   MPhiCompareH ->Fill(MuonPhiSig);
 
     }
     }

        for(Long64_t entry1=0; entry1 < nMsize1; entry1++){
             if (nMsize1!=0){

                   MuonEtaBg = MEtaBg->GetValue(entry1);
	   MuonPhiBg = MPhiBg->GetValue(entry1);  
	   MuonPtBg = MPtBg->GetValue(entry1);

                   MPtCompareH1 ->Fill(MuonPtBg);
                   MEtaCompareH1 ->Fill(MuonEtaBg);
                   MPhiCompareH1 ->Fill(MuonPhiBg);
 
     }
     }



     }

     EPtCompareH->Scale(3.961e-07);
     EPtCompareH1->Scale(0.02215);
     EPhiCompareH->Scale(3.961e-07);
     EPhiCompareH1->Scale(0.02215);
     EEtaCompareH->Scale(3.961e-07);
     EEtaCompareH1->Scale(0.02215);
     MPtCompareH->Scale(3.961e-07);
     MPtCompareH1->Scale(0.02215);
     MPhiCompareH->Scale(3.961e-07);
     MPhiCompareH1->Scale(0.02215);
     MEtaCompareH->Scale(3.961e-07);
     MEtaCompareH1->Scale(0.02215);

     TCanvas *mycanvas = new TCanvas("mycanvas","My Canvas",1200,1200);

     EPtCompareH->Draw();
     EPtCompareH->GetXaxis()->SetTitle("GeV");
     EPtCompareH->GetYaxis()->SetTitle("Events");
     EPtCompareH1->Draw("same");
     mycanvas->SaveAs("ElectronPtCompare.png");
     EPhiCompareH->Draw();
     EPhiCompareH->GetXaxis()->SetTitle("Degree");
     EPhiCompareH->GetYaxis()->SetTitle("Events");
     EPhiCompareH1->Draw("same");
     mycanvas->SaveAs("ElectronPhiCompare.png");
     EEtaCompareH->Draw();
     EEtaCompareH->GetXaxis()->SetTitle("None");
     EEtaCompareH->GetYaxis()->SetTitle("Events");
     EEtaCompareH1->Draw("same");
     mycanvas->SaveAs("ElectronEtaCompare.png");

     MPtCompareH->Draw();
     MPtCompareH->GetXaxis()->SetTitle("GeV");
     MPtCompareH->GetYaxis()->SetTitle("Events");
     MPtCompareH1->Draw("same");
     mycanvas->SaveAs("MuonPtCompare.png");
     MPhiCompareH->Draw();
     MPhiCompareH->GetXaxis()->SetTitle("Degree");
     MPhiCompareH->GetYaxis()->SetTitle("Events");
     MPhiCompareH1->Draw("same");
     mycanvas->SaveAs("MuonPhiCompare.png");
     MEtaCompareH->Draw();
     MEtaCompareH->GetXaxis()->SetTitle("None");
     MEtaCompareH->GetYaxis()->SetTitle("Events");
     MEtaCompareH1->Draw("same");
     mycanvas->SaveAs("MuonEtaCompare.png");

     EPtCompareH->Write();
     EPtCompareH1->Write();
     EPhiCompareH->Write();
     EPhiCompareH1->Write();
     EEtaCompareH->Write();
     EEtaCompareH1->Write();
     MPtCompareH->Write();
     MPtCompareH1->Write();
     MPhiCompareH->Write();
     MPhiCompareH1->Write();
     MEtaCompareH->Write();
     MEtaCompareH1->Write();

     tree_output->Write();
     output->Close();
     file_sig->Close();
}