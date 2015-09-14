// VT1 HistoMessenger implementation file
// By R.C. Alfredson

#include "VT1HistoMessenger.hh"
#include "VT1Histo.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

VT1HistoMessenger::VT1HistoMessenger(VT1Histo* histo)
  : fHisto(histo)
{
  fVT1Dir = new G4UIdirectory("/VT1/");
  fVT1Dir->SetGuidance("UI commands for VT1");

  fHistoDir = new G4UIdirectory("/VT1/histo/");
  fHistoDir->SetGuidance("Histogram initialization");

  fHistoTitleCmd = new G4UIcmdWithAString("/VT1/histo/setHistoTitle", this);
  fHistoTitleCmd->SetGuidance("Provide a title for the histogram");
  fHistoTitleCmd->SetParameterName("title", false);
  fHistoTitleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fLowerBoundCmd = new G4UIcmdWithADoubleAndUnit("/VT1/histo/setLowerBound", this);
  fLowerBoundCmd->SetGuidance("Set the lower bound of the histogram");
  fLowerBoundCmd->SetParameterName("lBound", false);
  fLowerBoundCmd->SetRange("lBound>=0.");
  fLowerBoundCmd->SetUnitCategory("Energy");
  fLowerBoundCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fUpperBoundCmd = new G4UIcmdWithADoubleAndUnit("/VT1/histo/setUpperBound",this);
  fUpperBoundCmd->SetGuidance("Set the upper bound of the histogram");
  fUpperBoundCmd->SetParameterName("uBound", false);
  fUpperBoundCmd->SetUnitCategory("Energy");
  fUpperBoundCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

VT1HistoMessenger::~VT1HistoMessenger()
{
  delete fVT1Dir;
  delete fHistoDir;
  delete fHistoTitleCmd;
  delete fLowerBoundCmd;
  delete fUpperBoundCmd;
}

void VT1HistoMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if ( command == fHistoTitleCmd )
    {
      fHisto->setHistoTitle(newValue);
    }
  if ( command == fLowerBoundCmd )
    {
      fHisto->setLowerBound(fLowerBoundCmd->GetNewDoubleValue(newValue));
    }
  if (command == fUpperBoundCmd)
    {
      fHisto->setUpperBound(fUpperBoundCmd->GetNewDoubleValue(newValue));
    }
}
