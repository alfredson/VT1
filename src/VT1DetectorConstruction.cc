// VT1 DetectorConstruction implementation
// By R. C. Alfredson

#include "VT1DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include <cmath>

VT1DetectorConstruction::VT1DetectorConstruction()
  : G4VUserDetectorConstruction(), fPhysCrystal(0), //fPhysOuterSphere(0),
    //fPhysInnerVolume(0),
    fPhysLeadShield(0), fPhysCopperLayer(0),
    fPhysCryostat(0), fPhysCryostatCavity(0), fPhysMountCupWall(0),
    fPhysIRShield(0), fPhysMountCupBase(0), fPhysColdFinger(0),
    fPhysCopperPlate(0), fPhysAlCylinder(0), fPhysAlMount(0),
    fPhysCopperRod(0), fPhysCryostatCopperRod(0),
    fPhysColdFingerCopperRod(0), fPhysCo60Disk(0),
    fPhysWorld(0)
{
}

VT1DetectorConstruction::~VT1DetectorConstruction()
{
}

G4VPhysicalVolume* VT1DetectorConstruction::Construct()
{  
  G4double a, z, density, temperature, pressure, fractionMass;
  G4int numComponents;
  G4NistManager* nist = G4NistManager::Instance();
  
  G4double phiStart = 0.0*deg;
  G4double phiTotal = 360.0*deg;

  G4RotationMatrix* rotationAboutY = new G4RotationMatrix;
  rotationAboutY->rotateY(90.*deg);
  G4RotationMatrix* nullRotation = new G4RotationMatrix;
  nullRotation->rotateY(0.0*deg);

  G4Element* elN = new G4Element("Nitrogen", "H", z = 7., a = 14.01*g/mole);
  G4Element* elO = new G4Element("Oxygen", "O", z = 8., a = 16.00*g/mole);
  G4Material* air = new G4Material("Air", density = 1.290*mg/cm3, numComponents = 2);
  air->AddElement(elN, fractionMass = 70*perCent);
  air->AddElement(elO, fractionMass = 30*perCent);
  G4Material* vacuum = new G4Material("Vacuum", z = 1., a = 1.01*g/mole,
				      density = universe_mean_density, kStateGas,
				      temperature = 0.1*kelvin, pressure = 1e-19*pascal);
  G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* Mg = nist->FindOrBuildMaterial("G4_Mg");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Co = nist->FindOrBuildMaterial("G4_Co");
  G4Material* Ge = new G4Material("PureGermanium", z = 32., a = 72.630*g/mole, density = 5.323*g/cm3);
  G4Material* Cu = new G4Material("PureCopper", z = 29., a = 63.546*g/mole, density = 8.96*g/cm3);

  G4double world_hx = 6.0*m;
  G4double world_hy = 6.0*m;
  G4double world_hz = 6.0*m;
  G4Box* solidWorld = new G4Box("World", world_hx, world_hy, world_hz);


  // Inner volume (all that remains are reference dimensions)
  G4double innerVolume_rMax = 13.97*cm;
  G4double innerVolume_length = 40.64*cm;

  // Cryostat
  G4double cryostat_rMin = 0.0;
  G4double cryostat_rMax = 3.5*cm;
  G4double cryostat_length = 16.2*cm;
  G4Tubs* solidCryostat = new G4Tubs("Cryostat", cryostat_rMin, cryostat_rMax, cryostat_length/2,
				     phiStart, phiTotal);

  // Copper layer
  G4double copperLayer_thickness = 0.29464*cm;
  G4double copperLayer_rMin = cryostat_rMax + 0.01*cm;
  G4double copperLayer_rMax = innerVolume_rMax + copperLayer_thickness;
  G4double copperLayer_halfLength = (innerVolume_length/2) + copperLayer_thickness;
  G4Tubs* solidCopperLayer = new G4Tubs("CopperLayer", copperLayer_rMin, copperLayer_rMax,
					copperLayer_halfLength, phiStart, phiTotal);

  // Cobalt-60 calibration source
  G4double Co60Disk_rMin = 0.0;
  G4double Co60Disk_rMax = 0.75*cm;
  G4double Co60Disk_halfLength = 2*mm;
  G4Tubs* solidCo60Disk = new G4Tubs("Co60Disk", Co60Disk_rMin, Co60Disk_rMax,
  				     Co60Disk_halfLength, phiStart, phiTotal);

  // Lead shield
  G4double leadShield_thickness = 10.16*cm;
  G4double leadShield_rMin = copperLayer_rMax + 0.01*cm;
  G4double leadShield_rMax = innerVolume_rMax + copperLayer_thickness + leadShield_thickness + 0.01*cm;
  G4double leadShield_length = innerVolume_length + 2*copperLayer_thickness + 2*leadShield_thickness + 0.01*cm;
  // G4double leadShieldCavity_rMin = 0.0;
  // G4double leadShieldCavity_rMax = 0.80*cm;
  // G4double leadShieldCavity_halfLength = 2.5*mm;
  G4Tubs* solidLeadShield = new G4Tubs("LeadShield", leadShield_rMin, leadShield_rMax, leadShield_length/2,
				       phiStart, phiTotal);
  // G4Tubs* solidLeadShieldCavity = new G4Tubs("LeadShieldCavity", leadShieldCavity_rMin, leadShieldCavity_rMax,
  // 					     leadShieldCavity_halfLength, phiStart, phiTotal);
  // G4SubtractionSolid* solidLeadShield = new G4SubtractionSolid("LeadShield", solidLeadShieldPreCavity, solidLeadShieldCavity,
  // 							       0, G4ThreeVector(0.0,0.0, copperLayer_halfLength + 2.5*mm));
					     

  // Cryostat cavity
  G4double MgPlate_thickness = 1.0*mm;
  G4double cryostat_thickness = 1.3*mm;
  G4double cryostatCavity_rMin = 0.0;
  G4double cryostatCavity_rMax = cryostat_rMax - cryostat_thickness;
  G4double cryostatCavity_halfLength = (cryostat_length/2) - MgPlate_thickness;
  G4Tubs* solidCryostatCavity = new G4Tubs("CryostatCavity", cryostatCavity_rMin, cryostatCavity_rMax,
					   cryostatCavity_halfLength, phiStart, phiTotal);

  // Note: for the moment, the crystal is simulated as a simple germanium cylinder
  G4double crystal_rMin = 0.0;
  G4double crystal_rMax = (55.8/2)*mm;
  G4double crystal_length = 75.7*mm;
  G4Tubs* solidCrystal = new G4Tubs("Crystal", crystal_rMin, crystal_rMax, crystal_length/2, phiStart, phiTotal);

  // IR shield and mount-cup wall (their dimensions share common references)
  G4double mountCup_rMin = crystal_rMax + 0.02*cm;
  G4double mountCupWall_thickness = 0.76*mm;
  G4double mountCupBase_thickness = 3.2*mm;
  G4double mountCupAssembly_length = 94*mm;
  G4double mountCup_rMax = mountCup_rMin + mountCupWall_thickness;
  G4double irShield_rMin = 0.0;
  G4double irShield_rMax = mountCup_rMin - 0.01*cm;
  G4double irShield_thickness = 0.06*mm;
  G4double mountCupWall_length = mountCupAssembly_length - irShield_thickness - mountCupBase_thickness;
  G4Tubs* solidMountCupWall = new G4Tubs("MountCupWall", mountCup_rMin, mountCup_rMax, mountCupWall_length/2,
					 phiStart, phiTotal);
  G4Tubs* solidIRShield = new G4Tubs("IRShield", irShield_rMin, irShield_rMax, irShield_thickness/2,
				     phiStart, phiTotal);

  // Mount cup base (note: its parameters are already specified above)
  G4Tubs* solidMountCupBase = new G4Tubs("MountCupBase", 0.0, mountCup_rMax, mountCupBase_thickness/2,
					 phiStart, phiTotal);

  // Cold finger
  G4double coldFinger_rMin = 0.9525*cm; // equals 0.375 in
  G4double coldFinger_rMax = 1.5875*cm;
  G4double coldFinger_length = 10.16*cm;
  G4double coldFinger_effHalfLength = (coldFinger_length/2) - 0.01*cm;
  G4Tubs* solidColdFinger = new G4Tubs("ColdFinger", coldFinger_rMin, coldFinger_rMax,
				       coldFinger_effHalfLength, phiStart, phiTotal);

  // Copper plate
  G4double copperPlate_rMin = coldFinger_rMax + 0.0254*cm;
  G4double copperPlate_rMax = 2.54*cm;
  G4double copperPlate_thickness = 1.905*cm;
  G4Tubs* solidCopperPlate = new G4Tubs("CopperPlate", copperPlate_rMin, copperPlate_rMax,
					copperPlate_thickness/2, phiStart, phiTotal);

  // Aluminum cylinder
  G4double AlCylinder_rMin = coldFinger_rMin + 0.0254*cm;
  G4double AlCylinder_rMax = cryostat_rMax;
  G4double AlCylinder_length = 5.715*cm;
  G4double AlCylinder_effHalfLength = (AlCylinder_length/2) - 0.01*cm;
  G4Tubs* solidAlCylinder = new G4Tubs("AlCylinder", AlCylinder_rMin, AlCylinder_rMax,
				       AlCylinder_effHalfLength, phiStart, phiTotal);

  // Aluminum mount
  G4double AlMount_rMin = AlCylinder_rMin;
  G4double AlMount_rMax = coldFinger_rMax;
  G4double AlMount_length = 8.255*cm;
  G4Tubs* solidAlMount = new G4Tubs("AlMount", AlMount_rMin, AlMount_rMax,
				    AlMount_length/2, phiStart, phiTotal);

  // Copper rod
  G4double copperRod_rMin = 0.0;
  G4double copperRod_rMax = coldFinger_rMin;
  G4double copperRod_length = 13.97*cm;
  G4Tubs* solidCopperRod = new G4Tubs("CopperRod", copperRod_rMin, copperRod_rMax,
				      copperRod_length/2, phiStart, phiTotal);

  // Cryostat's copper rod
  G4double cryostatCopperRod_rMin = 0.0;
  G4double cryostatCopperRod_rMax = 0.9525*cm;
  G4double cryostatCopperRod_length = 6.4*cm;
  G4Tubs* solidCryostatCopperRod = new G4Tubs("CryostatCopperRod", cryostatCopperRod_rMin,
					      cryostatCopperRod_rMax, cryostatCopperRod_length/2,
					      phiStart, phiTotal);

  // Cold finger's copper rod
  G4double coldFingerCopperRod_rMin = 0.0;
  G4double coldFingerCopperRod_rMax = 0.9525*cm;
  G4double coldFingerCopperRod_length = 10.16*cm;
  G4double coldFingerCopperRod_effHalfLength = (coldFingerCopperRod_length/2) - 0.01*cm;
  G4Tubs* solidColdFingerCopperRod = new G4Tubs("ColdFingerCopperRod", coldFingerCopperRod_rMin,
						coldFingerCopperRod_rMax, coldFingerCopperRod_effHalfLength,
						phiStart, phiTotal);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
  //G4LogicalVolume* logicOuterSphere = new G4LogicalVolume(solidOuterSphere, air, "OuterSphere");
  //G4LogicalVolume* logicInnerVolume = new G4LogicalVolume(solidInnerVolume, air, "InnerVolume");
  G4LogicalVolume* logicCopperLayer = new G4LogicalVolume(solidCopperLayer, Cu, "CopperLayer");
  G4LogicalVolume* logicCo60Disk = new G4LogicalVolume(solidCo60Disk, Co, "Co60Disk");
  G4LogicalVolume* logicLeadShield = new G4LogicalVolume(solidLeadShield, Pb, "LeadShield");
  G4LogicalVolume* logicCryostat = new G4LogicalVolume(solidCryostat, Mg, "Cryostat");
  G4LogicalVolume* logicCryostatCavity = new G4LogicalVolume(solidCryostatCavity, vacuum, "CryostatCavity");
  G4LogicalVolume* logicCrystal = new G4LogicalVolume(solidCrystal, Ge, "Crystal");
  G4LogicalVolume* logicMountCupWall = new G4LogicalVolume(solidMountCupWall, Cu, "MountCupWall");
  G4LogicalVolume* logicIRShield = new G4LogicalVolume(solidIRShield, Al, "IRShield");
  G4LogicalVolume* logicMountCupBase = new G4LogicalVolume(solidMountCupBase, Cu, "MountCupBase");
  G4LogicalVolume* logicColdFinger = new G4LogicalVolume(solidColdFinger, Al, "ColdFinger");
  G4LogicalVolume* logicCopperPlate = new G4LogicalVolume(solidCopperPlate, Cu, "CopperPlate");
  G4LogicalVolume* logicAlCylinder = new G4LogicalVolume(solidAlCylinder, Al, "AlCylinder");
  G4LogicalVolume* logicAlMount = new G4LogicalVolume(solidAlMount, Al, "AlMount");
  G4LogicalVolume* logicCopperRod = new G4LogicalVolume(solidCopperRod, Cu, "CopperRod");
  G4LogicalVolume* logicCryostatCopperRod = new G4LogicalVolume(solidCryostatCopperRod, Cu, "CryostatCopperRod");
  G4LogicalVolume* logicColdFingerCopperRod = new G4LogicalVolume(solidColdFingerCopperRod, Cu, "ColdFingerCopperRod");

  // Components and vectors for placement of physical volumes
  G4double cavity_height = cryostat_length - (2*MgPlate_thickness);
  G4double crystal_offset = 4*mm;
  G4double cryostat_offset = -10.16*cm;
  G4double AlCylinder_offset = 1*cm;
  G4double Co60Disk_offset = (innerVolume_length/2) + copperLayer_thickness;
  G4double crystal_zPos = (cavity_height/2) - (crystal_length/2) - crystal_offset;
  G4double mountCupWall_zPos = (cavity_height/2) - (mountCupWall_length/2) - crystal_offset
    + (irShield_thickness/2) + 0.01*cm;
  G4double mountCupBase_zPos = (cavity_height/2) - mountCupWall_length - (mountCupBase_thickness/2)
    - crystal_offset - (irShield_thickness/2) - 0.01*cm;
  G4double copperPlate_zPos = mountCupBase_zPos - (copperPlate_thickness/2);
  G4double irShield_zPos = (cavity_height/2) - crystal_offset + 0.01*cm;
  G4double coldFinger_xPos = -cryostat_rMax - (coldFinger_length/2) - 0.01*cm;
  G4double coldFinger_zPos = (-AlCylinder_length/2) - AlMount_length - (coldFinger_rMax/2)
    - cryostat_offset - cryostat_length - 0.01*cm + AlCylinder_offset;
  G4double AlCylinder_zPos = -cryostat_offset - cryostat_length - AlMount_length
    - (AlCylinder_length/2) + AlCylinder_offset;
  G4double AlMount_zPos = -cryostat_offset - cryostat_length - (AlMount_length/2)
    + AlCylinder_offset;
  G4double cryostat_zPos = (-cryostat_length/2) - cryostat_offset + AlCylinder_offset;
  G4double copperRod_zPos = -cryostat_offset - cryostat_length - (copperRod_length/2)
    + AlCylinder_offset;
  G4double cryostatCopperRod_zPos = mountCupBase_zPos - (mountCupBase_thickness/2)
    - (cryostatCopperRod_length/2);

  G4ThreeVector crystalPlacement(0,0,crystal_zPos);
  G4ThreeVector cryostatPlacement(0,0,cryostat_zPos);
  G4ThreeVector mountCupWallPlacement(0,0,mountCupWall_zPos);
  G4ThreeVector irShieldPlacement(0,0,irShield_zPos);
  G4ThreeVector mountCupBasePlacement(0,0,mountCupBase_zPos);
  G4ThreeVector copperPlatePlacement(0,0,copperPlate_zPos);
  G4ThreeVector coldFingerPlacement(coldFinger_xPos,
				    0,coldFinger_zPos);
  G4ThreeVector AlCylinderPlacement(0,0,AlCylinder_zPos);
  G4ThreeVector AlMountPlacement(0,0,AlMount_zPos);
  G4ThreeVector copperRodPlacement(0,0,copperRod_zPos);
  G4ThreeVector cryostatCopperRodPlacement(0,0,cryostatCopperRod_zPos);
  G4ThreeVector Co60DiskPlacement(0,0,Co60Disk_offset);

  G4RotationMatrix* yRot = new G4RotationMatrix;
  yRot->rotateY(CLHEP::pi/2.*rad);

  // Placement of physical volumes  
  fPhysWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);
  fPhysLeadShield = new G4PVPlacement(0, G4ThreeVector(), logicLeadShield, "LeadShield", logicWorld, false, 0, true);
  fPhysCopperLayer = new G4PVPlacement(0, copperPlatePlacement, logicCopperLayer, "CopperLayer", logicWorld, false, 0, true);
  fPhysCo60Disk = new G4PVPlacement(0, Co60DiskPlacement, logicCo60Disk, "Co60Disk", logicWorld, false, 0, true);
  fPhysCryostat = new G4PVPlacement(0, cryostatPlacement, logicCryostat, "Cryostat", logicWorld, false, 0, true);
  fPhysCryostatCavity = new G4PVPlacement(0, G4ThreeVector(), logicCryostatCavity, "CryostatCavity", logicCryostat, false, 0, true);
  fPhysCrystal = new G4PVPlacement(0, crystalPlacement, logicCrystal, "Crystal", logicCryostatCavity, false, 0, true);
  fPhysMountCupWall = new G4PVPlacement(0, mountCupWallPlacement, logicMountCupWall, "MountCupWall", logicCryostatCavity, false, 0, true);
  fPhysIRShield = new G4PVPlacement(0, irShieldPlacement, logicIRShield, "IRShield", logicCryostatCavity, false, 0, true);
  fPhysMountCupBase = new G4PVPlacement(0, mountCupBasePlacement, logicMountCupBase, "MountCupBase", logicCryostatCavity, false, 0, true);
  fPhysColdFinger = new G4PVPlacement(yRot, coldFingerPlacement, logicColdFinger, "ColdFinger", logicWorld, false, 0, true);
  fPhysCopperPlate = new G4PVPlacement(0, copperPlatePlacement, logicCopperPlate, "CopperPlate", logicCryostatCavity, false, 0, true);
  fPhysAlCylinder = new G4PVPlacement(0, AlCylinderPlacement, logicAlCylinder, "AlCylinder", logicWorld, false, 0, true);
  fPhysAlMount = new G4PVPlacement(0, AlMountPlacement, logicAlMount, "AlMount", logicWorld, false, 0, true);
  fPhysCopperRod = new G4PVPlacement(0, copperRodPlacement, logicCopperRod, "CopperRod", logicWorld, false, 0, true);
  fPhysCryostatCopperRod = new G4PVPlacement(0, cryostatCopperRodPlacement, logicCryostatCopperRod, "CryostatCopperRod", logicCryostatCavity,
					     false, 0, true);
  fPhysColdFingerCopperRod = new G4PVPlacement(yRot, coldFingerPlacement, logicColdFingerCopperRod, "ColdFingerCopperRod", logicWorld,
					       false, 0, true);
  return fPhysWorld;
}
