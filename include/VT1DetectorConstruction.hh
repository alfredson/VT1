// VT1 DetectorConstruction header file
// By R. C. Alfredson

#ifndef VT1DetectorConstruction_h
#define VT1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;


class VT1DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  VT1DetectorConstruction();
  virtual ~VT1DetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  const G4VPhysicalVolume* GetGermaniumCyl() {return fPhysCrystal;};
  //G4VPhysicalVolume* GetOuterSphere() {return fPhysOuterSphere;};
  //G4VPhysicalVolume* GetInnerVolume() {return fPhysInnerVolume;};
  G4VPhysicalVolume* GetLeadShield() {return fPhysLeadShield;};
  G4VPhysicalVolume* GetCopperLayer() {return fPhysCopperLayer;};
  G4VPhysicalVolume* GetCryostat() {return fPhysCryostat;};
  G4VPhysicalVolume* GetCryostatCavity() {return fPhysCryostatCavity;};
  G4VPhysicalVolume* GetMountCupWall() {return fPhysMountCupWall;};
  G4VPhysicalVolume* GetIRShield() {return fPhysIRShield;};
  G4VPhysicalVolume* GetMountCupBase() {return fPhysMountCupBase;};
  G4VPhysicalVolume* GetColdFinger() {return fPhysColdFinger;};
  G4VPhysicalVolume* GetCopperPlate() {return fPhysCopperPlate;};
  G4VPhysicalVolume* GetAlCylinder() {return fPhysAlCylinder;};
  G4VPhysicalVolume* GetAlMount() {return fPhysAlMount;};
  G4VPhysicalVolume* GetCopperRod() {return fPhysCopperRod;};
  G4VPhysicalVolume* GetCryostatCopperRod() {return fPhysCryostatCopperRod;};
  G4VPhysicalVolume* GetColdFingerCopperRod() {return fPhysColdFingerCopperRod;};
  G4VPhysicalVolume* GetCo60Disk() {return fPhysCo60Disk;};
  G4VPhysicalVolume* GetWorld() {return fPhysWorld;};

private:
  G4VPhysicalVolume* fPhysCrystal;
  //G4VPhysicalVolume* fPhysOuterSphere;
  //G4VPhysicalVolume* fPhysInnerVolume;
  G4VPhysicalVolume* fPhysLeadShield;
  G4VPhysicalVolume* fPhysCopperLayer;
  G4VPhysicalVolume* fPhysCryostat;
  G4VPhysicalVolume* fPhysCryostatCavity;
  G4VPhysicalVolume* fPhysMountCupWall;
  G4VPhysicalVolume* fPhysIRShield;
  G4VPhysicalVolume* fPhysMountCupBase;
  G4VPhysicalVolume* fPhysColdFinger;
  G4VPhysicalVolume* fPhysCopperPlate;
  G4VPhysicalVolume* fPhysAlCylinder;
  G4VPhysicalVolume* fPhysAlMount;
  G4VPhysicalVolume* fPhysCopperRod;
  G4VPhysicalVolume* fPhysCryostatCopperRod;
  G4VPhysicalVolume* fPhysColdFingerCopperRod;
  G4VPhysicalVolume* fPhysCo60Disk;
  G4VPhysicalVolume* fPhysWorld;
};

#endif
