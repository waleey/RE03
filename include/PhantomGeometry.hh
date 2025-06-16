#pragma once

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "units.hh"

class PhantomGeometry
{
public:
    PhantomGeometry(G4LogicalVolume* innerWorldLogical);
    ~PhantomGeometry();
    void ConstructPhantomGeometry(G4double, G4double, G4double, G4double, G4double, G4double);
private:
    void ConstructPhantom1();
    void ConstructPhantom2();
    void ConstructPhantom3();
    void ConstructPhantom4();
    void ConstructPhantom5();
    void ConstructPhantom6();
    void ConstructPhantom7();

private:
    G4LogicalVolume* fInnerWorldLogical;
    G4Material* fMaterial;

    G4double fInnerWallHalfSizeX;
    G4double fInnerWallHalfSizeY;
    G4double fInnerWallHalfSizeZ;
    G4double fOuterWallHalfSizeX;
    G4double fOuterWallHalfSizeY;
    G4double fOuterWallHalfSizeZ;

    G4double fHumanRadius = 12 * 2 * 1.5 * cm;
    G4double fHumanHalfHeight = 85 * 2 * cm;
};