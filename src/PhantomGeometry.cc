#include "PhantomGeometry.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4Colour.hh"


PhantomGeometry::PhantomGeometry(G4LogicalVolume* innerWorldLogical)
    : fInnerWorldLogical(innerWorldLogical)
{

}
PhantomGeometry::~PhantomGeometry()
{
    // Destructor implementation
}
void PhantomGeometry::ConstructPhantomGeometry(G4double innerWallHalfSizeX, 
                                               G4double innerWallHalfSizeY, 
                                               G4double innerWallHalfSizeZ, 
                                               G4double outerWallHalfSizeX, 
                                               G4double outerWallHalfSizeY, 
                                               G4double outerWallHalfSizeZ)
{
    fInnerWallHalfSizeX = innerWallHalfSizeX;
    fInnerWallHalfSizeY = innerWallHalfSizeY;
    fInnerWallHalfSizeZ = innerWallHalfSizeZ;
    fOuterWallHalfSizeX = outerWallHalfSizeX;
    fOuterWallHalfSizeY = outerWallHalfSizeY;
    fOuterWallHalfSizeZ = outerWallHalfSizeZ;

    G4NistManager* NISTman = G4NistManager::Instance();
    fMaterial = NISTman->FindOrBuildMaterial("G4_WATER");
    
    ConstructPhantom1();
    ConstructPhantom2();
    ConstructPhantom3();
    ConstructPhantom4();
    ConstructPhantom5();
}
void PhantomGeometry::ConstructPhantom1()
{
    G4double xCoord = fInnerWallHalfSizeX - 9 * foot - 10.5 * inch;
    G4double yCoord = fOuterWallHalfSizeY + 3 * foot + fHumanRadius;
    G4double zCoord = -fInnerWallHalfSizeZ + fHumanHalfHeight;

    G4VSolid* phantom1Solid = new G4Tubs("Phantom1Solid", 0, fHumanRadius, fHumanHalfHeight, 0, 360 * deg);
    G4LogicalVolume* phantom1Logical = new G4LogicalVolume(phantom1Solid, fMaterial, "Phantom1Logical");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), phantom1Logical, "Phantom1", fInnerWorldLogical,
                      false, 0);
    phantom1Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void PhantomGeometry::ConstructPhantom2()
{
    G4double xCoord = fOuterWallHalfSizeX + 1.5 * foot + fHumanRadius;
    G4double yCoord = fInnerWallHalfSizeY -10 * cm - fHumanRadius;
    G4double zCoord = fInnerWallHalfSizeZ - fHumanHalfHeight;

    G4VSolid* phantom2Solid = new G4Tubs("Phantom2Solid", 0, fHumanRadius, fHumanHalfHeight, 0, 360 * deg);
    G4LogicalVolume* phantom2Logical = new G4LogicalVolume(phantom2Solid, fMaterial, "Phantom2Logical");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), phantom2Logical, "Phantom2", fInnerWorldLogical,
                      false, 0);
    phantom2Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void PhantomGeometry::ConstructPhantom3()
{
    G4double xCoord = -fOuterWallHalfSizeX - 1.5 * foot - fHumanRadius;
    G4double yCoord = fInnerWallHalfSizeY - 10 * cm - fHumanRadius;
    G4double zCoord = fInnerWallHalfSizeZ - fHumanHalfHeight;

    G4VSolid* phantom3Solid = new G4Tubs("Phantom3Solid", 0, fHumanRadius, fHumanHalfHeight, 0, 360 * deg);
    G4LogicalVolume* phantom3Logical = new G4LogicalVolume(phantom3Solid, fMaterial, "Phantom3Logical");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), phantom3Logical, "Phantom3", fInnerWorldLogical,
                      false, 0);
    phantom3Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void PhantomGeometry::ConstructPhantom4()
{
    G4double xCoord = -fOuterWallHalfSizeX - 1.5 * foot - fHumanRadius;
    G4double yCoord = -fInnerWallHalfSizeY + 3 * foot + fHumanRadius;
    G4double zCoord = fInnerWallHalfSizeZ - fHumanHalfHeight;

    G4VSolid* phantom4Solid = new G4Tubs("Phantom4Solid", 0, fHumanRadius, fHumanHalfHeight, 0, 360 * deg);
    G4LogicalVolume* phantom4Logical = new G4LogicalVolume(phantom4Solid, fMaterial, "Phantom4Logical");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), phantom4Logical, "Phantom4", fInnerWorldLogical,
                      false, 0);
    phantom4Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void PhantomGeometry::ConstructPhantom5()
{
    G4double xCoord = fInnerWallHalfSizeX - 22 * foot - 1.5 * m;
    G4double yCoord = 2 * m;
    G4double zCoord = fInnerWallHalfSizeZ - fHumanHalfHeight;

    G4VSolid* phantom5Solid = new G4Tubs("Phantom5Solid", 0, fHumanRadius, fHumanHalfHeight, 0, 360 * deg);
    G4LogicalVolume* phantom5Logical = new G4LogicalVolume(phantom5Solid, fMaterial, "Phantom5Logical");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), phantom5Logical, "Phantom5", fInnerWorldLogical,
                      false, 0);
    phantom5Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
