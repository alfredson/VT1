// DSIM main() file
// By R. C. Alfredson

#include "VT1DetectorConstruction.hh"
#include "VT1PrimaryGeneratorAction.hh"
#include "VT1RunAction.hh"
#include "VT1EventAction.hh"
#include "VT1SteppingAction.hh"
#include "VT1Histo.hh"

#include "G4UIManager.hh"
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "Shielding.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "time.h"

int main(int argc, char** argv)
{
  G4RunManager* runManager = new G4RunManager;

  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time(NULL);
  G4Random::setTheSeed(seed);

  VT1DetectorConstruction* detector = new VT1DetectorConstruction;
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* shielding = new Shielding;
  runManager->SetUserInitialization(shielding);

  VT1Histo* histo = new VT1Histo();

  VT1PrimaryGeneratorAction* generatorAction = new VT1PrimaryGeneratorAction;
  runManager->SetUserAction(generatorAction);

  VT1RunAction* runAction = new VT1RunAction(histo);
  runManager->SetUserAction(runAction);

  VT1EventAction* eventAction = new VT1EventAction(runAction, histo);
  runManager->SetUserAction(eventAction);

  VT1SteppingAction* steppingAction = new VT1SteppingAction(detector, eventAction);
  runManager->SetUserAction(steppingAction);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();


  G4UImanager* UIManager = G4UImanager::GetUIpointer();
  if (argc != 1)
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UIManager->ApplyCommand(command+fileName);
    }
  
  delete runManager;
  delete visManager;
  
  return 0;
}
