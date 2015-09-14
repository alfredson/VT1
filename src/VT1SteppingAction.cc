// VT1 SteppingAction implementation file
// By R. C. Alfredson

#include "VT1SteppingAction.hh"
#include "VT1EventAction.hh"
#include "VT1DetectorConstruction.hh"

#include "G4Step.hh"

VT1SteppingAction::VT1SteppingAction(VT1DetectorConstruction* detector, VT1EventAction* event)
  : G4UserSteppingAction(), fEventAction(event), fDetector(detector)
{}

VT1SteppingAction::~VT1SteppingAction()
{}

void VT1SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4double eDep = aStep->GetTotalEnergyDeposit();

  if (volume == fDetector->GetGermaniumCyl()) fEventAction->AddEdep(eDep);
}
