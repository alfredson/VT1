// VT1 SteppingAction header file
// By R. C. Alfredson

#ifndef VT1SteppingAction_h
#define VT1SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class VT1EventAction;
class VT1DetectorConstruction;

class VT1SteppingAction : public G4UserSteppingAction
{
public:
  VT1SteppingAction(VT1DetectorConstruction*, VT1EventAction*);
  virtual ~VT1SteppingAction();

  virtual void UserSteppingAction(const G4Step*);

private:
  VT1EventAction*  fEventAction;
  VT1DetectorConstruction* fDetector;
};

#endif
