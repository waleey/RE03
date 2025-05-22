#include "LayerGeometry.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"


LayerGeometry::LayerGeometry(G4LogicalVolume* innerWorldLogical)
    : finnerWorldLogical(innerWorldLogical)
{
    /*
    Building a dummy mateiral
    will be changed to real material
    later.
    */
    fMaterial = new Material();
}

LayerGeometry::~LayerGeometry()
{
;
}

void LayerGeometry::ConstructLayerGeometry(G4double WorldYHalfSize, G4double wallWorldGap, G4double wallThickness)
{
    //Updating Layer Coordinates
    fWorldYHalfSize = WorldYHalfSize;
    fWallWorldGap = wallWorldGap;
    fWallThickness = wallThickness;
    
    
    fLayer1YCoord = fWorldYHalfSize - (fWallWorldGap + fWallThickness)- fLayer1Thickness / 2;
    fLayer2YCoord = fLayer1YCoord - fLayer1Thickness / 2 - fLayer2Thickness / 2;
    fLayer3YCoord = fLayer2YCoord - fLayer2Thickness / 2 - fLayer3Thickness / 2;
    fLayer4YCoord = fLayer3YCoord - fLayer3Thickness / 2 - fLayer4Thickness / 2;
    fLayer5YCoord = fLayer4YCoord - fLayer4Thickness / 2 - fLayer5Thickness / 2;

    fLayerXCoord = 3. * m;
    fLayerZCoord = 0. * m;

    fLayer1Coord = G4ThreeVector(fLayerXCoord, fLayer1YCoord, fLayerZCoord);
    fLayer2Coord = G4ThreeVector(fLayerXCoord, fLayer2YCoord, fLayerZCoord);
    fLayer3Coord = G4ThreeVector(fLayerXCoord, fLayer3YCoord, fLayerZCoord);
    fLayer4Coord = G4ThreeVector(fLayerXCoord, fLayer4YCoord, fLayerZCoord);
    fLayer5Coord = G4ThreeVector(fLayerXCoord, fLayer5YCoord, fLayerZCoord);

    //Updating layer x and z sizes
    fLayerSizeX = (1 * 0.5) * m;
    fLayerSizeZ = (1 * 0.5) * m;
    
    
    ConstructLayer1();
    ConstructLayer2();
    ConstructLayer3();
    ConstructLayer4();
    ConstructLayer5();
}
void LayerGeometry::ConstructTubeAndChamber()
{
    ConstructBeamTube();
    ConstructHEELChamber();
}
void LayerGeometry::ConstructLayer1()
{
    G4VSolid* layer1Solid = new G4Box("Layer1", fLayerSizeX, fLayer1Thickness / 2, fLayerSizeZ);
    G4LogicalVolume* layer1Logical = new G4LogicalVolume(layer1Solid, fMaterial -> GetHDConcrete(), "Layer1");
    fLayer1Phys = new G4PVPlacement(0, fLayer1Coord, layer1Logical, "Layer1Phys",
                                                  finnerWorldLogical, false, 0);
    layer1Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void LayerGeometry::ConstructLayer2()
{
    G4VSolid* layer2Solid = new G4Box("Layer2", fLayerSizeX, fLayer2Thickness / 2, fLayerSizeZ);
    G4LogicalVolume* layer2Logical = new G4LogicalVolume(layer2Solid, fMaterial -> GetIron(), "Layer2");
    fLayer2Phys = new G4PVPlacement(0, fLayer2Coord, layer2Logical, "Layer2Phys",
                                                  finnerWorldLogical, false, 0);
    layer2Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
}
void LayerGeometry::ConstructLayer3()
{
    G4VSolid* layer3Solid = new G4Box("Layer3", fLayerSizeX, fLayer3Thickness / 2, fLayerSizeZ);
    G4LogicalVolume* layer3Logical = new G4LogicalVolume(layer3Solid, fMaterial -> GetHDConcrete(), "Layer3");
    fLayer3Phys = new G4PVPlacement(0, fLayer3Coord, layer3Logical, "Layer3Phys",
                                                  finnerWorldLogical, false, 0);
    layer3Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
}
void LayerGeometry::ConstructLayer4()
{
    G4VSolid* layer4Solid = new G4Box("Layer4", fLayerSizeX, fLayer4Thickness / 2, fLayerSizeZ);
    G4LogicalVolume* layer4Logical = new G4LogicalVolume(layer4Solid, fMaterial -> GetIron(), "Layer4");
    fLayer4Phys = new G4PVPlacement(0, fLayer4Coord, layer4Logical, "Layer4Phys",
                                                  finnerWorldLogical, false, 0);
    layer4Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
}
void LayerGeometry::ConstructLayer5()
{
    G4VSolid* layer5Solid = new G4Box("Layer5", fLayerSizeX, fLayer5Thickness / 2, fLayerSizeZ);
    G4LogicalVolume* layer5Logical = new G4LogicalVolume(layer5Solid, fMaterial -> GetHDConcrete(), "Layer5");
    fLayer5Phys = new G4PVPlacement(0, fLayer5Coord, layer5Logical, "Layer5Phys",
                                                  finnerWorldLogical, false, 0);
    layer5Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
}
void LayerGeometry::ConstructBeamTube()
{
    //Beam Tube Parameters for quick change
    fBeamTubeThickness = 0.156 * inch;
    fBeamTubeOuterRadius = 6. * inch;
    fBeamTubeInnerRadius = fBeamTubeOuterRadius - fBeamTubeThickness;
    fBeamTubeHalfLength = 4 * m;

    G4double totalLayerThickness = fLayer1Thickness + fLayer2Thickness + fLayer3Thickness + fLayer4Thickness + fLayer5Thickness;
    //Beam Tube Coordinate
    fBeamTubeXCoord = 3. * m;
    fBeamTubeYCoord = fWorldYHalfSize - (fWallWorldGap + fWallThickness) - totalLayerThickness - fBeamTubeHalfLength;
    fBeamTubeZCoord = 0. * m;

    //Rotating the tube about the x axis
    G4RotationMatrix* beamTubeRotation = new G4RotationMatrix();
    beamTubeRotation->rotateX(90. * deg);

    //Creating outer wall of beam tube 
    G4VSolid* beamTubeOuterSolid = new G4Tubs("BeamOuterTube", 0., fBeamTubeOuterRadius, fBeamTubeHalfLength, 0., 360. * deg);
    G4LogicalVolume* beamTubeOuterLogical = new G4LogicalVolume(beamTubeOuterSolid, fMaterial -> GetStainlessSteel(), "BeamOuterTube");
    new G4PVPlacement(beamTubeRotation, G4ThreeVector(fBeamTubeXCoord, fBeamTubeYCoord, fBeamTubeZCoord), beamTubeOuterLogical, "BeamTubeOuterPhys", finnerWorldLogical, false, 0);
    beamTubeOuterLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

    //Creating inner wall of beam tube
    /*
    Inner tube uses the local coordinate
    of the Outer Tube.
    */
    G4VSolid* beamTubeInnerSolid = new G4Tubs("BeamInnerTube", 0., fBeamTubeInnerRadius, fBeamTubeHalfLength, 0., 360. * deg);
    G4LogicalVolume* beamTubeInnerLogical = new G4LogicalVolume(beamTubeInnerSolid, fMaterial -> GetAir(), "BeamInnerTube");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), beamTubeInnerLogical, "BeamTubeInnerPhys", beamTubeOuterLogical, false, 0);

    beamTubeInnerLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
    
    G4cout << "Beam Tube Successfully Constructed" << G4endl;
}
void LayerGeometry::ConstructHEELChamber()
{
    //Updating HEEL Chamber Parameters
    fChamberHeight = 1. * m; 
    fChamberWidth = 1. * m; 
    fChamberLength = 2. * m;
    fChamberSideThickness = 1.25 * inch;
    fChamberBottomThickness = 1.5 * inch;
    fChamberTopThickness = 1. * inch;

    //Chamber Coordinate
    G4double chamberXCoord = 3. * m;
    G4double chamberYCoord = fBeamTubeYCoord - fBeamTubeHalfLength - fChamberLength / 2;
    G4double chamberZCoord = 0. * m;
    G4RotationMatrix* chamberRotation = new G4RotationMatrix();
    chamberRotation->rotateY(90. * deg);
    //Creating the chamber
    G4VSolid* chamberSolid = new G4Box("Chamber", fChamberWidth / 2, fChamberLength / 2, fChamberHeight / 2);
    G4LogicalVolume* chamberLogical = new G4LogicalVolume(chamberSolid, fMaterial -> GetAluminium(), "Chamber");
    new G4PVPlacement(chamberRotation, G4ThreeVector(chamberXCoord, chamberYCoord, chamberZCoord), chamberLogical, "ChamberPhys",
                                                  finnerWorldLogical, false, 0);
    chamberLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));

    /*
    Creating the inner chamber
    The inner chamber is placed in the center of the chamber
    and has the same rotation as the chamber.
     */
    
    G4double innerChamberHeight = fChamberHeight - fChamberBottomThickness - fChamberTopThickness; //chamber top along z
    G4double innerChamberLength = fChamberLength - fChamberSideThickness * 2;
    G4double innerChamberWidth = fChamberWidth - fChamberSideThickness * 2;

    //Creating the inner chamber
    G4VSolid* innerChamberSolid = new G4Box("InnerChamber", innerChamberWidth / 2, innerChamberLength / 2, innerChamberHeight / 2);
    G4LogicalVolume* innerChamberLogical = new G4LogicalVolume(innerChamberSolid, fMaterial -> GetAir(), "InnerChamber");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), innerChamberLogical, "InnerChamberPhys",
                                                  chamberLogical, false, 0);
    innerChamberLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));

    /*
    Creating the circular hole in the chamber
    The hole connects the chamber to the beam tube
    */
    G4double holeRadius = fBeamTubeInnerRadius;
    G4double holeHalfLength = fChamberSideThickness / 2;

    //hole coordinate
    G4double holeXCoord = 0. * m;
    G4double holeYCoord = fChamberLength / 2 - fChamberSideThickness / 2;
    G4double holeZCoord = 0. * m;
    G4RotationMatrix* holeRotation = new G4RotationMatrix();
    holeRotation->rotateY(90. * deg);
    holeRotation->rotateX(90. * deg);
    //Creating the hole
    G4VSolid* holeSolid = new G4Tubs("Hole", 0., holeRadius, holeHalfLength, 0., 360. * deg);
    G4LogicalVolume* holeLogical = new G4LogicalVolume(holeSolid, fMaterial -> GetAir(), "Hole");
    new G4PVPlacement(holeRotation, G4ThreeVector(holeXCoord, holeYCoord, holeZCoord), holeLogical, "HolePhys",
                                                  chamberLogical, false, 0);
    holeLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));

    G4cout << "HEEL Chamber Successfully Constructed" << G4endl;
}
void LayerGeometry::UpdateGeometry()
{
    fLayer1YCoord = fWorldYHalfSize - (fWallWorldGap + fWallThickness)- fLayer1Thickness / 2;
    fLayer2YCoord = fLayer1YCoord - fLayer1Thickness / 2 - fLayer2Thickness / 2;
    fLayer3YCoord = fLayer2YCoord - fLayer2Thickness / 2 - fLayer3Thickness / 2;
    fLayer4YCoord = fLayer3YCoord - fLayer3Thickness / 2 - fLayer4Thickness / 2;
    fLayer5YCoord = fLayer4YCoord - fLayer4Thickness / 2 - fLayer5Thickness / 2;

    fLayerXCoord = 3. * m;
    fLayerZCoord = 0. * m;

    fLayer1Coord = G4ThreeVector(fLayerXCoord, fLayer1YCoord, fLayerZCoord);
    fLayer2Coord = G4ThreeVector(fLayerXCoord, fLayer2YCoord, fLayerZCoord);
    fLayer3Coord = G4ThreeVector(fLayerXCoord, fLayer3YCoord, fLayerZCoord);
    fLayer4Coord = G4ThreeVector(fLayerXCoord, fLayer4YCoord, fLayerZCoord);
    fLayer5Coord = G4ThreeVector(fLayerXCoord, fLayer5YCoord, fLayerZCoord);

    if(fLayer1Phys){
        fLayer1Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer1", fLayerSizeX, fLayer1Thickness / 2, fLayerSizeZ));
    }
    if(fLayer2Phys){
        fLayer2Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer2", fLayerSizeX, fLayer2Thickness / 2, fLayerSizeZ));
    }
    if(fLayer3Phys){
        fLayer3Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer3", fLayerSizeX, fLayer3Thickness / 2, fLayerSizeZ));
    }
    if(fLayer4Phys){
        fLayer4Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer4", fLayerSizeX, fLayer4Thickness / 2, fLayerSizeZ));
    }
    if(fLayer5Phys){
        fLayer5Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer5", fLayerSizeX, fLayer5Thickness / 2, fLayerSizeZ));
    }

}
void LayerGeometry::SetLayer1Thickness(G4double thickness)
{
    fLayer1Thickness = thickness;
    UpdateGeometry();
}
void LayerGeometry::SetLayer2Thickness(G4double thickness)
{
    fLayer2Thickness = thickness;
    UpdateGeometry();
}
void LayerGeometry::SetLayer3Thickness(G4double thickness)
{
    fLayer3Thickness = thickness;
    UpdateGeometry();
}
void LayerGeometry::SetLayer4Thickness(G4double thickness)
{
    fLayer4Thickness = thickness;
    UpdateGeometry();
}
void LayerGeometry::SetLayer5Thickness(G4double thickness)
{
    fLayer5Thickness = thickness;
    UpdateGeometry();
}
