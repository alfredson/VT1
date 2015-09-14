// VT1 RunAction header file
// By R. C. Alfredson

#ifndef VT1RunAction_h
#define VT1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class VT1Histo;

class VT1RunAction : public G4UserRunAction
{
public:
  VT1RunAction(VT1Histo*);
  virtual ~VT1RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

  void FillPerEvent(G4double);

private:
  VT1Histo* fHisto;

  G4double fSumTotalEnergy;
};

#endif
