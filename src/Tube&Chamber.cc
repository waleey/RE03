#include "Tube&Chamber.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4ios.hh"

TubeAndChamber::TubeAndChamber(G4LogicalVolume* innerWallLogical)
    : finnerWallLogical(innerWallLogical)
{
    fMaterial = new Material();
}
TubeAndChamber::~TubeAndChamber()
{
    ;
}
void TubeAndChamber::ConstructTubeAndChamber(G4double innerWallHalfSizeX,
                                             G4double innerWallHalfSizeY,
                                             G4double innerWallHalfSizeZ, 
                                             G4double layerThickness)
{
    fInnerWallHalfSizeX = innerWallHalfSizeX;
    fInnerWallHalfSizeY = innerWallHalfSizeY;
    fInnerWallHalfSizeZ = innerWallHalfSizeZ;
    fLayerTotalThickness = layerThickness;

    ConstructHEELChamber();
    ConstructBeamTube();
}
void TubeAndChamber::ConstructBeamTube()
{
    //Beam Tube Parameters for quick change
    fBeamTubeThickness = 0.156 * inch;
    fBeamTubeInnerRadius = 6. * inch;
    fBeamTubeOuterRadius = fBeamTubeInnerRadius + fBeamTubeThickness;
    /**
     * Calculating tube length
     */
    G4double capThickness = fChamberSideThickness;
    G4double tubeLength = (fInnerWallHalfSizeY - fLayerTotalThickness - capThickness) - (fChamberYCoord + fChamberHalfSizeY);

    //Beam Tube Coordinate
    fBeamTubeXCoord = fChamberXCoord + fHoleXCoord;
    fBeamTubeYCoord = fInnerWallHalfSizeY - fLayerTotalThickness - tubeLength / 2;
    fBeamTubeZCoord = fChamberZCoord;
/*
    G4cout << "Beam Tube Coordinates: "
           << "X: " << (fBeamTubeXCoord - 1.5 * foot) / m << " m, "
           << "Y: " << fBeamTubeYCoord / m << " m, "
           << "Z: " << fBeamTubeZCoord / m << " m" << G4endl;
    
    exit(0);
*/
    //Rotating the tube about the x axis
    G4RotationMatrix* beamTubeRotation = new G4RotationMatrix();
    beamTubeRotation->rotateX(90. * deg);

    //Creating outer wall of beam tube 
    G4VSolid* beamTubeOuterSolid = new G4Tubs("BeamOuterTube", 0., fBeamTubeOuterRadius, tubeLength / 2, 0., 360. * deg);
    G4LogicalVolume* beamTubeOuterLogical = new G4LogicalVolume(beamTubeOuterSolid, fMaterial -> GetStainlessSteel(), "BeamOuterTube");
    new G4PVPlacement(beamTubeRotation, G4ThreeVector(fBeamTubeXCoord, fBeamTubeYCoord, fBeamTubeZCoord), beamTubeOuterLogical, "BeamTubeOuterPhys", finnerWallLogical, false, 0);
    beamTubeOuterLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

    //Creating inner wall of beam tube
    /*
    Inner tube uses the local coordinate
    of the Outer Tube.
    */
    G4VSolid* beamTubeInnerSolid = new G4Tubs("BeamInnerTube", 0., fBeamTubeInnerRadius, tubeLength / 2, 0., 360. * deg);
    G4LogicalVolume* beamTubeInnerLogical = new G4LogicalVolume(beamTubeInnerSolid, fMaterial -> GetVacuum(), "BeamInnerTube");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), beamTubeInnerLogical, "BeamTubeInnerPhys", beamTubeOuterLogical, false, 0);

    beamTubeInnerLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));

    //Creating the beam tube cap
    /*
    Cap is defined in the Inner Wall Geometry
    */
    G4double capXCoord = fBeamTubeXCoord;
    G4double capYCoord = fInnerWallHalfSizeY - fLayerTotalThickness  - capThickness / 2;
    G4double capZCoord = fBeamTubeZCoord;

    G4VSolid* capSolid = new G4Tubs("BeamTubeCap", 0., fBeamTubeOuterRadius, capThickness / 2, 0., 360. * deg);
    G4LogicalVolume* capLogical = new G4LogicalVolume(capSolid, fMaterial -> GetPexiGlass(), "BeamTubeCap");
    new G4PVPlacement(beamTubeRotation, G4ThreeVector(capXCoord, capYCoord, capZCoord), capLogical, "BeamTubeCapPhys", finnerWallLogical, false, 0);
    capLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
/*
    G4double beamSourceXCoord = fBeamTubeXCoord;
    G4double beamSourceYCoord = -fInnerWallHalfSizeY + 27 * foot + (9 + 0.5625 )* inch;
    G4double beamSourceZCoord = fBeamTubeZCoord;

    G4cout << "Beam Source Coordinates: "
           << "X: " << beamSourceXCoord / m << " m, "
           << "Y: " << beamSourceYCoord / m << " m, "
           << "Z: " << beamSourceZCoord / m << " m" << G4endl;
    exit(0);
*/    
    G4cout << "Beam Tube Successfully Constructed" << G4endl;
}
void TubeAndChamber::ConstructHEELChamber()
{
    //Updating HEEL Chamber Parameters
    /**
     * Asusmed top and bottom thicknesses
     * are the same for simplicity
     */
    fChamberSideThickness = 1.25 * inch;
    fChamberBottomThickness = 1. * inch;
    fChamberTopThickness = 1. * inch;

    //Chamber Coordinate
    fChamberXCoord = fInnerWallHalfSizeX - fChamberXDistWall - fChamberHalfSizeX;
    fChamberYCoord = -fInnerWallHalfSizeY + fChamberYDistWall + fChamberHalfSizeY;
    fChamberZCoord = -fInnerWallHalfSizeZ + fChamberHalfSizeZ;
    G4RotationMatrix* chamberRotation = new G4RotationMatrix();
    //chamberRotation->rotateY(90. * deg);
    
    //Creating the chamber
    G4VSolid* chamberSolid = new G4Box("Chamber", fChamberHalfSizeX, fChamberHalfSizeY, fChamberHalfSizeZ);
    G4LogicalVolume* chamberLogical = new G4LogicalVolume(chamberSolid, fMaterial -> GetAluminium(), "Chamber");
    new G4PVPlacement(chamberRotation, G4ThreeVector(fChamberXCoord, fChamberYCoord, fChamberZCoord), chamberLogical, "ChamberPhys",
                                                  finnerWallLogical, false, 0);
    chamberLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));

    /*
    Creating the inner chamber
    The inner chamber is placed in the center of the chamber
    and has the same rotation as the chamber.
     */
    
    G4double innerChamberHalfSizeZ = fChamberHalfSizeZ - fChamberBottomThickness;
    G4double innerChamberHalfSizeY = fChamberHalfSizeY - fChamberSideThickness;
    G4double innerChamberHalfSizeX = fChamberHalfSizeX - fChamberSideThickness;

    //Creating the inner chamber
    G4VSolid* innerChamberSolid = new G4Box("InnerChamber", innerChamberHalfSizeX, innerChamberHalfSizeY, innerChamberHalfSizeZ);
    G4LogicalVolume* innerChamberLogical = new G4LogicalVolume(innerChamberSolid, fMaterial -> GetVacuum(), "InnerChamber");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), innerChamberLogical, "InnerChamberPhys",
                                                  chamberLogical, false, 0);
    innerChamberLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));

    /*
    Creating the circular hole in the chamber
    The hole connects the chamber to the beam tube
    */
    G4double holeRadius = fBeamTubeInnerRadius;
    G4double holeHalfLength = fChamberSideThickness * 0.5;

    //hole coordinate
    fHoleXCoord = (0.3333) * fChamberHalfSizeX;
    fHoleYCoord = fChamberHalfSizeY - fChamberSideThickness * 0.5;
    fHoleZCoord = 0. * m;
    G4RotationMatrix* holeRotation = new G4RotationMatrix();
    holeRotation->rotateY(90. * deg);
    holeRotation->rotateX(90. * deg);
    //Creating the hole
    G4VSolid* holeSolid = new G4Tubs("Hole", 0., holeRadius, holeHalfLength, 0., 360. * deg);
    G4LogicalVolume* holeLogical = new G4LogicalVolume(holeSolid, fMaterial -> GetAir(), "Hole");
    new G4PVPlacement(holeRotation, G4ThreeVector(fHoleXCoord, fHoleYCoord, fHoleZCoord), holeLogical, "HolePhys",
                                                  chamberLogical, false, 0);
    holeLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));

    G4cout << "HEEL Chamber Successfully Constructed" << G4endl;
}