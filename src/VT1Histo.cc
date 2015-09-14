// VT1 Histo implementation file
// By R. C. Alfredson

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "VT1Histo.hh"
#include "VT1HistoMessenger.hh"
#include "G4UnitsTable.hh"

VT1Histo::VT1Histo()
  : fRootFile(0), fNtuple(0), fTotalEnergy(0), fLowerBound(0), fUpperBound(0)
{
  fHisto = 0;
  fNtuple = 0;
  fHistoMessenger = new VT1HistoMessenger(this);
}

VT1Histo::~VT1Histo()
{
  if (fRootFile) delete fRootFile;
  delete fHistoMessenger;
}

void VT1Histo::setHistoTitle(G4String val)
{
  fHistoTitle = val;
}

void VT1Histo::setLowerBound(G4double val)
{
  fLowerBound = val;
}

void VT1Histo::setUpperBound(G4double val)
{
  fUpperBound = val;
}

void VT1Histo::book()
{
  G4String fileName = "VT1Output.root";

  fRootFile = new TFile(fileName, "RECREATE");

  fHisto = new TH1D("CrystalHistogram", fHistoTitle, 200, fLowerBound, fUpperBound);

  fNtuple = new TTree("VT1Tree", "Energy Deposition TTree");
  fNtuple->Branch("TotalEnergy", &fTotalEnergy, "Event Energies");
}

void VT1Histo::save()
{
  if (fRootFile)
    {
      fRootFile->Write();
      fRootFile->Close();
    }
}

void VT1Histo::FillHisto(G4double bin, G4double weight)
{
  fHisto->Fill(bin, weight);
}

void VT1Histo::Normalize(G4double fac)
{
  fHisto->Scale(fac);
}

void VT1Histo::FillNtuple(G4double totalEnergy)
{
  fTotalEnergy = totalEnergy;
  fNtuple->Fill();
}

void VT1Histo::PrintStatistic()
{
  G4cout << "\n.......Energy deposition ticker.......\n" << G4endl;
  G4cout << "Mean energy = " << G4BestUnit(fHisto->GetMean(), "Energy") << " RMS of energy = " << G4BestUnit(fHisto->GetRMS(), "Energy") << G4endl;
}
