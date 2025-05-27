#pragma once

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "units.hh"
#include "Material.hh"

class TubeAndChamber
{
public:
    TubeAndChamber(G4LogicalVolume* innerWallLogical);
    ~TubeAndChamber();
    void ConstructTubeAndChamber(G4double innerWallHalfSizeX,
                                 G4double innerWallHalfSizeY,
                                 G4double innerWallHalfSizeZ, 
                                 G4double layerThickness);

private:
    void ConstructBeamTube();
    void ConstructHEELChamber();


private:

    G4LogicalVolume* finnerWallLogical;
    Material* fMaterial;
    /*
     * Temporaraily needs this information
     * to construct the beam tube and chamber
     * Will remove later @@@
    */

    G4double fLayerTotalThickness;

    G4double fInnerWallHalfSizeX;
    G4double fInnerWallHalfSizeY;
    G4double fInnerWallHalfSizeZ;
    
    //Beam Tube Parameters
    G4double fBeamTubeThickness = 0.156 * inch;
    G4double fBeamTubeInnerRadius = 6. * inch;
    G4double fBeamTubeOuterRadius = fBeamTubeInnerRadius + fBeamTubeThickness;

    G4double fBeamTubeXCoord;
    G4double fBeamTubeYCoord;
    G4double fBeamTubeZCoord;

    /**
     * @brief Chamber parameters
     * Chamber refers to the outer layer
     * Inner layer of the chamber is referred to as inner chamber.
     * Chamber thickness are taken from Jess's email
     * Chamber measurments are from David's design
     */ 
    G4double fChamberSideThickness = 1.25 * inch;
    G4double fChamberBottomThickness = 1.5 * inch;
    G4double fChamberTopThickness = 1. * inch;

    G4double fChamberHalfSizeX = (10 * foot + 10 * inch) * 0.5;
    G4double fChamberHalfSizeY = (25 * foot) * 0.5;
    G4double fChamberHalfSizeZ = 3 * foot + (4 + 0.875) * inch;

    G4double fChamberXDistWall = 9 * foot + 10.5 * inch - (0.6667) * fChamberHalfSizeX;
    G4double fChamberYDistWall = 27 * foot + (9 + 0.5625) * inch - 25 * foot;
    G4double fChamberZDistWall = 0;

    G4double fChamberXCoord;
    G4double fChamberYCoord;
    G4double fChamberZCoord;

    G4double fHoleXCoord;
    G4double fHoleYCoord;
    G4double fHoleZCoord;

};