#pragma once

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "Material.hh"
static const G4double inch = 2.54 * cm;
class LayerGeometry
{
public:
    LayerGeometry(G4LogicalVolume* innerWorldLogical);
    ~LayerGeometry();

public:
    void ConstructLayerGeometry(G4double, G4double, G4double);
    void ConstructTubeAndChamber();
    void SetLayer1Thickness(G4double thickness);
    void SetLayer2Thickness(G4double thickness); 
    void SetLayer3Thickness(G4double thickness); 
    void SetLayer4Thickness(G4double thickness);
    void SetLayer5Thickness(G4double thickness);

private:
    void ConstructLayer1();
    void ConstructLayer2();
    void ConstructLayer3();
    void ConstructLayer4();
    void ConstructLayer5();
    void ConstructBeamTube();
    void ConstructHEELChamber();
    void UpdateGeometry();

private:
    G4LogicalVolume* finnerWorldLogical;
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
    G4double fTotalThickness = 4 * m;
    G4double fLayer1Thickness = 0.8 * m;
    G4double fLayer2Thickness = 0.8 * m;
    G4double fLayer3Thickness = 0.8 * m;
    G4double fLayer4Thickness = 0.8 * m;
    G4double fLayer5Thickness = 0.8 * m;

    //Defining world wall gap and wall thickness
    G4double fWallWorldGap = 1. * m;
    G4double fWallThickness = 1. * m;
    G4double fWorldYHalfSize = 10. * m;

    //Layer coordinates
    G4double fLayer1YCoord = fWorldYHalfSize - (fWallWorldGap + fWallThickness)- fLayer1Thickness / 2;
    G4double fLayer2YCoord = fLayer1YCoord - fLayer1Thickness / 2 - fLayer2Thickness / 2;
    G4double fLayer3YCoord = fLayer2YCoord - fLayer2Thickness / 2 - fLayer3Thickness / 2;
    G4double fLayer4YCoord = fLayer3YCoord - fLayer3Thickness / 2 - fLayer4Thickness / 2;
    G4double fLayer5YCoord = fLayer4YCoord - fLayer4Thickness / 2 - fLayer5Thickness / 2;

    G4double fLayerXCoord = 3. * m;
    G4double fLayerZCoord = 3. * m;

    
    G4ThreeVector fLayer1Coord = G4ThreeVector(fLayerXCoord, fLayer1YCoord, fLayerZCoord);
    G4ThreeVector fLayer2Coord = G4ThreeVector(fLayerXCoord, fLayer2YCoord, fLayerZCoord);
    G4ThreeVector fLayer3Coord = G4ThreeVector(fLayerXCoord, fLayer3YCoord, fLayerZCoord);
    G4ThreeVector fLayer4Coord = G4ThreeVector(fLayerXCoord, fLayer4YCoord, fLayerZCoord);
    G4ThreeVector fLayer5Coord = G4ThreeVector(fLayerXCoord, fLayer5YCoord, fLayerZCoord);

    //Layer cross section heigh and width
    G4double fLayerSizeX = (1 * 0.5) * m;
    G4double fLayerSizeZ = (1 * 0.5) * m;

    /*
    Beam Tube Parameters
    */
    G4double fBeamTubeThickness = 0.156 * inch;
    G4double fBeamTubeOuterRadius = 6. * inch;
    G4double fBeamTubeInnerRadius = fBeamTubeOuterRadius - fBeamTubeThickness;
    G4double fBeamTubeHalfLength = 4 * m;

    G4double fBeamTubeXCoord;
    G4double fBeamTubeYCoord;
    G4double fBeamTubeZCoord;


    /*
    HEEL Chamber Parameters
    */  
    G4double fChamberHeight = 1. * m; 
    G4double fChamberWidth = 1. * m; 
    G4double fChamberLength = 2. * m;
    G4double fChamberSideThickness = 1.25 * inch;
    G4double fChamberBottomThickness = 1.5 * inch;
    G4double fChamberTopThickness = 1. * inch;


};