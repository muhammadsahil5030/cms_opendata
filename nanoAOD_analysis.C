#include <iostream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

TH1F *hPt_jets = new TH1F("hPt_jets", "Jets Pt", 100, 0.0, 500.0);
TH1F *hEta_jets = new TH1F("hEta_jets", "Jets Eta", 100, -6.0, 6.0);
TH1F *hPhi_jets = new TH1F("hPhi_jets", "Jets Phi", 100, -3.14, 3.14);
TH1F *hN_jets = new TH1F("hN_jets", "Jets Multiplicity", 10, 0.0, 20);

TH1F *hPt_bjets = new TH1F("hPt_bjets", "b Jets Pt", 100, 0.0, 500.0);
TH1F *hEta_bjets = new TH1F("hEta_bjets", "b Jets Eta", 100, -6.0, 6.0);
TH1F *hPhi_bjets = new TH1F("hPhi_bjets", "b Jets Phi", 100, -3.14, 3.14);
TH1F *hN_bjets = new TH1F("hN_bjets", "b Jets Multiplicity", 10, 0.0, 20);

// Histogram for Jet_btagDEEPB values
TH1F *hBtagCSVV2 = new TH1F("hBtagCSVV2", "Jet b-tag CSVV2 values", 100, 0.0, 1.0);
TH1F *hBtagDEEPB = new TH1F("hBtagDeepB", "Jet b-tag DeepB values", 100, 0.0, 1.0);
TH1F *hBtagDEEPCvB = new TH1F("hBtagDeepCvB", "Jet b-tag DeepCvB values", 100, 0.0, 1.0);
TH1F *hBtagDEEPCvL = new TH1F("hBtagDeepCvL", "Jet b-tag DeepCvL values", 100, 0.0, 1.0);
TH1F *hBtagDEEPFlavB = new TH1F("hBtagDeepFlavB", "Jet b-tag DeepFlavB values", 100, 0.0, 1.0);
TH1F *hBtagDEEPFlavCvB = new TH1F("hBtagDeepFlavCvB", "Jet b-tag DeepFlavCvB values", 100, 0.0, 1.0);
TH1F *hBtagDEEPFlavCvL = new TH1F("hBtagDeepFlavCvL", "Jet b-tag DeepFlavCvL values", 100, 0.0, 1.0);
TH1F *hBtagDEEPFlavQG = new TH1F("hBtagDeepFlavQG", "Jet b-tag DeepFlavQG values", 100, 0.0, 1.0);


//-------------------------------------------------* End Histogram Definition* ------------------------------------//
void nanoAOD_analysis()
{
    // Open the nanoAOD ROOT file
    TFile *file = TFile::Open("cms_nanoAOD_13TeV_2016_opendata.root", "READ");
    if (!file || file->IsZombie())
    {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    // Access the tree
    TTree *Events_tree;
    file->GetObject("Events", Events_tree);
    if (!Events_tree)
    {
        std::cerr << "Error getting tree from file!" << std::endl;
        file->Close();
        return;
    }
    
//-----------------------------------------------------------------------------------------------------------------//
    // Debug: Print tree structure to verify branches and types
    //tree->Print();

    // Prepare for Jet_pt branch
    float Jet_pt[100], Jet_eta[100], Jet_phi[100]; // Assuming the maximum number of jets per event is 100
    float Jet_btagCSVV2[100], Jet_btagDEEPB[100], Jet_btagDEEPCvB[100], Jet_btagDEEPCvL[100], Jet_btagDEEPFlavB[100], Jet_btagDEEPFlavCvB[100], Jet_btagDEEPFlavCvL[100], Jet_btagDEEPFlavQG[100];

    unsigned int nJet; // Number of jets in the event

    Events_tree->SetBranchAddress("nJet", &nJet);
    Events_tree->SetBranchAddress("Jet_pt", Jet_pt);
    Events_tree->SetBranchAddress("Jet_eta", Jet_eta);
    Events_tree->SetBranchAddress("Jet_phi", Jet_phi);
    Events_tree->SetBranchAddress("Jet_btagCSVV2", Jet_btagCSVV2);
    Events_tree->SetBranchAddress("Jet_btagDeepB", Jet_btagDEEPB);
    Events_tree->SetBranchAddress("Jet_btagDeepCvB", Jet_btagDEEPCvB);
    Events_tree->SetBranchAddress("Jet_btagDeepCvL", Jet_btagDEEPCvL);
    Events_tree->SetBranchAddress("Jet_btagDeepFlavB", Jet_btagDEEPFlavB);
    Events_tree->SetBranchAddress("Jet_btagDeepFlavCvB", Jet_btagDEEPFlavCvB);
    Events_tree->SetBranchAddress("Jet_btagDeepFlavCvL", Jet_btagDEEPFlavCvL);
    Events_tree->SetBranchAddress("Jet_btagDeepFlavQG", Jet_btagDEEPFlavQG);
    
//----------------------------------------------* End of Branches Address * --------------------------------------//
    // Loop over the entries
    Long64_t nEntries = Events_tree->GetEntries();
    std::cout << "Total number of entries: " << nEntries << std::endl;

    for (Long64_t i = 0; i < nEntries; ++i)
    {
        Events_tree->GetEntry(i);
        unsigned int nBjets = 0;
        for (unsigned int j = 0; j < nJet; ++j)
        {

            //cout<<"Jet Pt: "<<Jet_pt[j]<<"\t"<<"Jet Eta: "<<Jet_eta[j]<<"\t"<<"Jet Phi: "<<Jet_phi[j]<<endl;
            hPt_jets->Fill(Jet_pt[j]);
            hEta_jets->Fill(Jet_eta[j]);
            hPhi_jets->Fill(Jet_phi[j]);
            
            // Fill the Jet_btag histograms
            hBtagCSVV2->Fill(Jet_btagCSVV2[j]);
            hBtagDEEPB->Fill(Jet_btagDEEPB[j]);
            hBtagDEEPCvB->Fill(Jet_btagDEEPCvB[j]);
            hBtagDEEPCvL->Fill(Jet_btagDEEPCvL[j]);
            hBtagDEEPFlavB->Fill(Jet_btagDEEPFlavB[j]);
            hBtagDEEPFlavCvB->Fill(Jet_btagDEEPFlavCvB[j]);
            hBtagDEEPFlavCvL->Fill(Jet_btagDEEPFlavCvL[j]);
            hBtagDEEPFlavQG->Fill(Jet_btagDEEPFlavQG[j]);
            
            if (Jet_btagDEEPB[j] > 0.6)
            { 
                hPt_bjets->Fill(Jet_pt[j]);
                hEta_bjets->Fill(Jet_eta[j]);
                hPhi_bjets->Fill(Jet_phi[j]);
                nBjets++;
            }
        }
        
        hN_jets->Fill(nJet);
        hN_bjets->Fill(nBjets);
    } //end of for loop:
    
//--------------------------------------------------------***------------------------------------------------------//

// Save the histogram to a file
TFile outputFile("nanoAOD_output_histograms.root", "RECREATE");

TCanvas *canvas = new TCanvas("my canvas", "Jets plots", 600, 800);
canvas->Divide(2, 2);
    canvas->cd(1);
    hPt_jets->Draw();
    
    canvas->cd(2);
    hEta_jets->Draw();
    
    canvas->cd(3);
    hPhi_jets->Draw();
    
    canvas->cd(4);
    hN_jets->Draw();
    
    canvas->Draw();
    canvas->SaveAs("jets_kinematics.png");
    canvas->Update();
    
TCanvas *canvas1 = new TCanvas("my canvas1", "bJets plots", 600, 800);
canvas1->Divide(2, 2);
    canvas1->cd(1);
    hPt_bjets->Draw();
    
    canvas1->cd(2);
    hEta_bjets->Draw();
    
    canvas1->cd(3);
    hPhi_bjets->Draw();
    
    canvas1->cd(4);
    hN_bjets->Draw();
    
    canvas1->Draw();
    canvas->SaveAs("bjets_kinematics.png");
    canvas1->Update();

TCanvas *canvas2 = new TCanvas("my canvas2", "bJets plots", 500, 800);
    
    hBtagCSVV2->SetLineColor(kRed);
    hBtagDEEPB->SetLineColor(kBlue);
    hBtagDEEPCvB->SetLineColor(kGreen);
    hBtagDEEPCvL->SetLineColor(kBlack);
    hBtagDEEPFlavB->SetLineColor(kPink);
    hBtagDEEPFlavCvB->SetLineColor(kOrange);
    hBtagDEEPFlavCvL->SetLineColor(kMagenta);
    hBtagDEEPFlavQG->SetLineColor(kSpring);
    
    hBtagCSVV2->SetLineWidth(2);
    hBtagDEEPB->SetLineWidth(2);
    hBtagDEEPCvB->SetLineWidth(2);
    hBtagDEEPCvL->SetLineWidth(2);
    hBtagDEEPFlavB->SetLineWidth(2);
    hBtagDEEPFlavCvB->SetLineWidth(2);
    hBtagDEEPFlavCvL->SetLineWidth(2);
    hBtagDEEPFlavQG->SetLineWidth(2);
    
    
    hBtagDEEPFlavB->Draw();
    hBtagCSVV2->Draw("same");
    hBtagDEEPB->Draw("same");
    hBtagDEEPCvB->Draw("same");
    hBtagDEEPCvL->Draw("same");
    hBtagDEEPFlavCvB->Draw("same");
    hBtagDEEPFlavCvL->Draw("same");
    hBtagDEEPFlavQG->Draw("same");
    
    // Create a legend and add entries
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Position of the legend
    legend->AddEntry(hBtagCSVV2, "hBtagCSVV2", "l");
    legend->AddEntry(hBtagDEEPB, "hBtagDEEPB", "l");
    legend->AddEntry(hBtagDEEPCvB, "hBtagDEEPCvB", "l");
    legend->AddEntry(hBtagDEEPCvL, "hBtagDEEPCvL", "l");
    legend->AddEntry(hBtagDEEPFlavB, "hBtagDEEPFlavB", "l");
    legend->AddEntry(hBtagDEEPFlavCvB, "hBtagDEEPFlavCvB", "l");
    legend->AddEntry(hBtagDEEPFlavCvL, "hBtagDEEPFlavCvL", "l");
    legend->AddEntry(hBtagDEEPFlavQG, "hBtagDEEPFlavQG", "l");

    // Draw the legend on the canvas
    legend->Draw();

    canvas2->Draw();
    canvas->SaveAs("bjets_tagging_algorithms.png");
    canvas2->Update();
    
        
    hPt_jets->Write();
    hEta_jets->Write();
    hPhi_jets->Write();
    hN_jets->Write();
    
    hPt_bjets->Write();
    hEta_bjets->Write();
    hPhi_bjets->Write();
    hN_bjets->Write();
    hBtagDEEPB->Write();

    
    outputFile.Close();

    file->Close();
}

// This macro can be run with "root -l nanoAOD_analysis.C"
void run() 
{
    nanoAOD_analysis();
}

