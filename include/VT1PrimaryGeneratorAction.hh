// VT1 PrimaryGeneratorAction header file
// By R. C. Alfredson

#ifndef VT1PrimaryGeneratorAction_h
#define VT1PrimaryGeneratorAction_h 1

// #include "G4VUserPrimaryGeneratorAction.hh"

// class G4GeneralParticleSource;
// class G4Event;

// class VT1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
// {
//   public:
//   VT1PrimaryGeneratorAction();
//   virtual ~VT1PrimaryGeneratorAction();

//   virtual void GeneratePrimaries(G4Event*);
  
//   private:
//   G4GeneralParticleSource* fParticleSource;
// };
// #endif

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"

class G4Navigator;
class G4ParticleGun;
class G4Event;
class VT1DetectorConstruction;

class VT1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
  VT1PrimaryGeneratorAction(VT1DetectorConstruction*);
  virtual ~VT1PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
  virtual bool TestIfPointIsInVolume(G4ThreeVector);
  
  private:
  G4ParticleGun*  fParticleGun;
  G4ParticleDefinition* fCo60;
  G4ParticleDefinition* fTl208;
  G4ParticleDefinition* fBi214;
  G4ParticleDefinition* fK40;
  G4ParticleDefinition* fPb210;
  G4ThreeVector fRandPosCarte;
  G4ThreeVector fGlobalTranslate;
  G4Navigator* fMyNavigator;
  G4VPhysicalVolume* fVolumeSample;
  VT1DetectorConstruction* fDetector;
};
#endif
