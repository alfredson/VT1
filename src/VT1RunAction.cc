// VT1 RunAction implementation file
// By R. C. Alfredson

#include "VT1RunAction.hh"
#include "VT1Histo.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

VT1RunAction::VT1RunAction(VT1Histo* histo)
  : G4UserRunAction(), fHisto(histo), fSumTotalEnergy(0.)
{}

VT1RunAction::~VT1RunAction()
{}

void VT1RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  fSumTotalEnergy = 0.;

  fHisto->book();
}

void VT1RunAction::FillPerEvent(G4double energyAddition)
{
  fSumTotalEnergy += energyAddition;
}

void VT1RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int numberOfEvents = aRun->GetNumberOfEvent();
  if (numberOfEvents == 0) return;
    
  fHisto->PrintStatistic();
  fHisto->save();
}
