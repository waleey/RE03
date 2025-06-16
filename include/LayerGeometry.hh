#pragma once

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "Material.hh"
#include "units.hh"

class LayerGeometry
{
public:
    LayerGeometry(G4LogicalVolume* innerWorldLogical);
    ~LayerGeometry();

public:
    void ConstructLayerGeometry(G4double, G4double, G4double);
    void SetLayer1Thickness(G4double thickness);
    void SetLayer2Thickness(G4double thickness); 
    void SetLayer3Thickness(G4double thickness); 
    void SetLayer4Thickness(G4double thickness);
    void SetLayer5Thickness(G4double thickness);
    G4double GetTotalLayerThickness() const;

private:
    void ConstructLayer1();
    void ConstructLayer2();
    void ConstructLayer3();
    void ConstructLayer4();
    void ConstructLayer5();
    void UpdateGeometry();

private:
    G4LogicalVolume* finnerWallLogical;
    Material* fMaterial;

    G4VPhysicalVolume* fLayer1Phys;
    G4VPhysicalVolume* fLayer2Phys;
    G4VPhysicalVolume* fLayer3Phys;
    G4VPhysicalVolume* fLayer4Phys;
    G4VPhysicalVolume* fLayer5Phys;
    /*
    Thickness of the layers
    are in y coordinate
    and in units of m.

    ****Important
    Total length of the room (inside inner wall)
    is 16.0 m. If room length changes, 
    you have to update the parameters here accordingly.
     */
    
    G4double fLayer1Thickness = 0. * m;
    G4double fLayer2Thickness = 0. * m;
    G4double fLayer3Thickness = 0.8 * m;
    G4double fLayer4Thickness = 0.8 * m;
    G4double fLayer5Thickness = 0.8 * m;
    G4double fTotalThickness = fLayer1Thickness + fLayer2Thickness + fLayer3Thickness + fLayer4Thickness + fLayer5Thickness;

    //Defining world wall gap and wall thickness
    G4double fInnerWallHalfSizeX;
    G4double fInnerWallHalfSizeY;
    G4double fInnerWallHalfSizeZ;

    //Layer cross section heigh and width
    G4double fLayerSizeX = (1 * 0.5) * m;
    G4double fLayerSizeZ = (1 * 0.5) * m;

    //Layer coordinates
    G4double fLayer1YCoord;
    G4double fLayer2YCoord;
    G4double fLayer3YCoord;
    G4double fLayer4YCoord;
    G4double fLayer5YCoord;

    G4ThreeVector fLayer1Coord;
    G4ThreeVector fLayer2Coord;
    G4ThreeVector fLayer3Coord;
    G4ThreeVector fLayer4Coord;
    G4ThreeVector fLayer5Coord;

    G4double fLayerXCoord;
    G4double fLayerZCoord;

};