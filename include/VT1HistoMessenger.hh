// VT1 HistoMessenger header file
// By R. C. Alfredson
#ifndef VT1HistoMessenger_h
#define VT1HistoMessenger_h 1

#include "globals.hh"
#include "G4UIMessenger.hh"

class VT1Histo;

class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

class VT1HistoMessenger : public G4UImessenger
{
public:
  VT1HistoMessenger(VT1Histo*);
  ~VT1HistoMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  VT1Histo* fHisto;

  G4UIdirectory* fVT1Dir;
  G4UIdirectory* fHistoDir;
  G4UIcmdWithAString* fHistoTitleCmd;
  G4UIcmdWithADoubleAndUnit* fLowerBoundCmd;
  G4UIcmdWithADoubleAndUnit* fUpperBoundCmd;
};
#endif
