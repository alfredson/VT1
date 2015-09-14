// VT1 EventAction implementation file
// By R. C. Alfredson

#include "VT1EventAction.hh"
#include "VT1RunAction.hh"
#include "VT1Histo.hh"

#include "G4Event.hh"

VT1EventAction::VT1EventAction(VT1RunAction* run, VT1Histo* histo)
  : G4UserEventAction(), fRunAction(run), fHisto(histo),
    fTotalEnergy(0.), fEventModulo(0)
{
  fEventModulo = 10000;
} 

VT1EventAction::~VT1EventAction()
{}

void VT1EventAction::BeginOfEventAction(const G4Event*)
{    
  fTotalEnergy = 0.;
}

void VT1EventAction::EndOfEventAction(const G4Event* anEvent)
{
  G4int eventNumber = anEvent->GetEventID();
  if (eventNumber%fEventModulo == 0)
    {
      G4cout << "\nThis marks the start of event " << eventNumber << G4endl;
    }
  fRunAction->FillPerEvent(fTotalEnergy);
  fHisto->FillHisto(fTotalEnergy);
  fHisto->FillNtuple(fTotalEnergy);
}
