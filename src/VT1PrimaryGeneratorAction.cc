// VT1 PrimaryGeneratorAction implementation file
// By R. C. Alfredson

#include "VT1PrimaryGeneratorAction.hh"

// #include "G4Event.hh"
// #include "G4GeneralParticleSource.hh"
// #include "G4ParticleTable.hh"
// #include "G4ParticleDefinition.hh"
// #include "globals.hh"

// VT1PrimaryGeneratorAction::VT1PrimaryGeneratorAction()
//   : G4VUserPrimaryGeneratorAction(), fParticleSource(0)
// {
//   fParticleSource = new G4GeneralParticleSource();
// }

// VT1PrimaryGeneratorAction::~VT1PrimaryGeneratorAction()
// {
//   delete fParticleSource;
// }

// void VT1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
// {
//   fParticleSource->GeneratePrimaryVertex(anEvent);
// }
#include "VT1DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include <cmath>

VT1PrimaryGeneratorAction::VT1PrimaryGeneratorAction(VT1DetectorConstruction* detector)
  : G4VUserPrimaryGeneratorAction(),
    fRandPosCarte(0), fGlobalTranslate(0),
    fMyNavigator(0), fVolumeSample(0), fDetector(detector)
{
  G4int numParticles = 1;
  fParticleGun = new G4ParticleGun(numParticles);
}

VT1PrimaryGeneratorAction::~VT1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void VT1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double aziMin, aziMax, cosZenithMin, cosZenithMax, rMax;
  G4double azi, cosZenith, zenith, uni, r;
  G4double posX, posY, posZ;
  G4int atomicNumber, atomicMass;
  G4double excitEnergy;
  G4bool withinCryostat;

  aziMin = 0.0;
  aziMax = 2*pi;
  cosZenithMin = -1.0;
  cosZenithMax = 1.0;
  rMax = 2.5;

  fCo60 = G4IonTable::GetIonTable()->GetIon(atomicNumber = 27, atomicMass = 60, excitEnergy = 0.0*keV);
  fTl208 = G4IonTable::GetIonTable()->GetIon(atomicNumber = 81, atomicMass = 208, excitEnergy = 0.0*keV);
  fBi214 = G4IonTable::GetIonTable()->GetIon(atomicNumber = 83, atomicMass = 214, excitEnergy = 0.0*keV);
  fK40 = G4IonTable::GetIonTable()->GetIon(atomicNumber = 19, atomicMass = 40, excitEnergy = 0.0*keV);
  fPb210 = G4IonTable::GetIonTable()->GetIon(atomicNumber = 82, atomicMass = 210, excitEnergy = 0.0*keV);
  
  for (G4int i = 0; i<1000000; i++)
    {
      azi = aziMin + (aziMax - aziMin)*G4UniformRand();
      cosZenith = cosZenithMin + (cosZenithMax - cosZenithMin)*G4UniformRand();
      uni = G4UniformRand();
      zenith = acos(cosZenith);
      r = pow(uni, 0.333333333)*rMax;

      posX = r*sin(zenith)*cos(azi)*cm;
      posY = r*sin(zenith)*sin(azi)*cm;
      posZ = (r*cos(zenith))*cm;

      fGlobalTranslate = G4ThreeVector(0.0, 0.0, 20.6*cm);
      fRandPosCarte = G4ThreeVector(posX, posY, posZ) + fGlobalTranslate;
      
      withinCryostat = TestIfPointIsInVolume(fRandPosCarte);
      if (withinCryostat == 1)
	{
	  G4double ionCharge;
	  fParticleGun->SetParticlePosition(fRandPosCarte);
	  fParticleGun->SetParticleDefinition(fCo60);
	  fParticleGun->SetParticleEnergy(0.0);
	  fParticleGun->SetParticleCharge(ionCharge = 0.0*eplus);
	  fParticleGun->GeneratePrimaryVertex(anEvent);
	  break;
	}
    }
}

bool VT1PrimaryGeneratorAction::TestIfPointIsInVolume(G4ThreeVector position)
{
  fMyNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
  fMyNavigator->SetWorldVolume(fDetector->GetWorld());
  fVolumeSample = fMyNavigator->LocateGlobalPointAndSetup(position);
  return (fVolumeSample == fDetector->GetCo60Disk());
}
