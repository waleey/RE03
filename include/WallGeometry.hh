#pragma once

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "units.hh"
#include "Material.hh"


class WallGeometry
{
public:
    WallGeometry(G4LogicalVolume* innerWorldLogical);
    ~WallGeometry();

public:
    void ConstructWallGeometry();
    G4LogicalVolume* GetInnerWallLogical() const { return fInnerWallLogical; }

    G4double GetInnerWallHalfSizeX() const { return fInnerWallHalfSizeX; }
    G4double GetInnerWallHalfSizeY() const { return fInnerWallHalfSizeY; }
    G4double GetInnerWallHalfSizeZ() const { return fInnerWallHalfSizeZ; }
    G4double GetOuterWallHalfSizeX() const { return fOuterWallHalfSizeX; }
    G4double GetOuterWallHalfSizeY() const { return fOuterWallHalfSizeY; }
    G4double GetOuterWallHalfSizeZ() const { return fOuterWallHalfSizeZ; }


private:
    void ConstructOuterWallGeometry();
    void ConstructInnerWallGeometry();
    void ConstructEastPolyWallGeometry();
    void ConstructNorthPolyWallGeometry();

private:
    G4LogicalVolume* fInnerWorldLogical;
    G4LogicalVolume* fOuterWallLogical;
    G4LogicalVolume* fInnerWallLogical;

    Material* fMaterial;

     /**
      * Geometry parameters based on
      * David's design
      */

    G4double fXWallThickness = 6 * foot;
    G4double fYWallThickness = 6 * foot;
    G4double fZWallThickness = 3 * foot + 6 * inch;

    G4double fChangeOffset = 3 * foot;

    G4double fInnerWallHalfSizeX = (9 * foot + 10.5 * inch + 67 * foot + 3 * inch) * 0.5;
    G4double fInnerWallHalfSizeY = (27 * foot + (9 + 0.5625) * inch + 60 * foot + (2 + 0.4375) * inch) * 0.5;
    G4double fInnerWallHalfSizeZ = (10 * foot + 6 * inch) * 0.5;

    G4double fOuterWallHalfSizeX = fInnerWallHalfSizeX + fXWallThickness - fChangeOffset * 0.5;
    G4double fOuterWallHalfSizeY = fInnerWallHalfSizeY + fYWallThickness;
    G4double fOuterWallHalfSizeZ = fInnerWallHalfSizeZ + fZWallThickness;
    
};