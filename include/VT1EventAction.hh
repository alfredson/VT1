// VT1 EventAction header file
// By R. C. Alfredson

#ifndef VT1EventAction_h
#define VT1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class VT1RunAction;
class VT1Histo;

class VT1EventAction : public G4UserEventAction
{
public:
  VT1EventAction(VT1RunAction*, VT1Histo*);
  virtual ~VT1EventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

  void AddEdep(G4double dE) {fTotalEnergy += dE;};

  private:
  VT1RunAction* fRunAction;
  VT1Histo* fHisto;
  
  G4double  fTotalEnergy;
  G4int fEventModulo;
};

#endif
