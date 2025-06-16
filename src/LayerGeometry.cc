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


LayerGeometry::LayerGeometry(G4LogicalVolume* innerWallLogical)
    : finnerWallLogical(innerWallLogical)
{
    fMaterial = new Material();
}

LayerGeometry::~LayerGeometry()
{
;
}

void LayerGeometry::ConstructLayerGeometry(G4double innerWallHalfSizeX, G4double innerWallHalfSizeY, G4double innerWallHalfSizeZ)
{
    fInnerWallHalfSizeX = innerWallHalfSizeX;
    fInnerWallHalfSizeY = innerWallHalfSizeY;
    fInnerWallHalfSizeZ = innerWallHalfSizeZ;

    fLayerXCoord = fInnerWallHalfSizeX - (9 * foot + 10.5 * inch);

    fLayer1YCoord = fInnerWallHalfSizeY - fLayer1Thickness* 0.5;
    fLayer2YCoord = fLayer1YCoord - fLayer1Thickness * 0.5 - fLayer2Thickness * 0.5;
    fLayer3YCoord = fLayer2YCoord - fLayer2Thickness * 0.5 - fLayer3Thickness * 0.5;
    fLayer4YCoord = fLayer3YCoord - fLayer3Thickness * 0.5 - fLayer4Thickness * 0.5;
    fLayer5YCoord = fLayer4YCoord - fLayer4Thickness * 0.5 - fLayer5Thickness * 0.5;

    fLayerZCoord = -fInnerWallHalfSizeZ + 3 * foot + (4 + 0.875) * inch;

    fLayer1Coord = G4ThreeVector(fLayerXCoord, fLayer1YCoord, fLayerZCoord);
    fLayer2Coord = G4ThreeVector(fLayerXCoord, fLayer2YCoord, fLayerZCoord);
    fLayer3Coord = G4ThreeVector(fLayerXCoord, fLayer3YCoord, fLayerZCoord);
    fLayer4Coord = G4ThreeVector(fLayerXCoord, fLayer4YCoord, fLayerZCoord);
    fLayer5Coord = G4ThreeVector(fLayerXCoord, fLayer5YCoord, fLayerZCoord);

    //Updating layer x and z sizes
    fLayerSizeX = (1 * 0.5) * m;
    fLayerSizeZ = (1 * 0.5) * m;
    
    //ConstructLayer1();
    //ConstructLayer2();
    ConstructLayer3();
    ConstructLayer4();
    ConstructLayer5();
}
void LayerGeometry::ConstructLayer1()
{
    G4VSolid* layer1Solid = new G4Box("Layer1", fLayerSizeX, fLayer1Thickness * 0.5, fLayerSizeZ);
    G4LogicalVolume* layer1Logical = new G4LogicalVolume(layer1Solid, fMaterial -> GetHDConcrete(), "Layer1");
    fLayer1Phys = new G4PVPlacement(0, fLayer1Coord, layer1Logical, "Layer1Phys",
                                                  finnerWallLogical, false, 0, true);
    layer1Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
}
void LayerGeometry::ConstructLayer2()
{
    G4VSolid* layer2Solid = new G4Box("Layer2", fLayerSizeX, fLayer2Thickness * 0.5, fLayerSizeZ);
    G4LogicalVolume* layer2Logical = new G4LogicalVolume(layer2Solid, fMaterial -> GetIron(), "Layer2");
    fLayer2Phys = new G4PVPlacement(0, fLayer2Coord, layer2Logical, "Layer2Phys",
                                                  finnerWallLogical, false, 0, true);
    layer2Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
}
void LayerGeometry::ConstructLayer3()
{
    G4VSolid* layer3Solid = new G4Box("Layer3", fLayerSizeX, fLayer3Thickness * 0.5, fLayerSizeZ);
    G4LogicalVolume* layer3Logical = new G4LogicalVolume(layer3Solid, fMaterial -> GetHDConcrete(), "Layer3");
    fLayer3Phys = new G4PVPlacement(0, fLayer3Coord, layer3Logical, "Layer3Phys",
                                                  finnerWallLogical, false, 0, true);
    layer3Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
}
void LayerGeometry::ConstructLayer4()
{
    G4VSolid* layer4Solid = new G4Box("Layer4", fLayerSizeX, fLayer4Thickness * 0.5, fLayerSizeZ);
    G4LogicalVolume* layer4Logical = new G4LogicalVolume(layer4Solid, fMaterial -> GetIron(), "Layer4");
    fLayer4Phys = new G4PVPlacement(0, fLayer4Coord, layer4Logical, "Layer4Phys",
                                                  finnerWallLogical, false, 0, true);
    layer4Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
}
void LayerGeometry::ConstructLayer5()
{
    G4VSolid* layer5Solid = new G4Box("Layer5", fLayerSizeX, fLayer5Thickness * 0.5, fLayerSizeZ);
    G4LogicalVolume* layer5Logical = new G4LogicalVolume(layer5Solid, fMaterial -> GetHDConcrete(), "Layer5");
    fLayer5Phys = new G4PVPlacement(0, fLayer5Coord, layer5Logical, "Layer5Phys",
                                                  finnerWallLogical, false, 0, true);
    layer5Logical->SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
}
void LayerGeometry::UpdateGeometry()
{
    fLayer1YCoord = fInnerWallHalfSizeY - fLayer1Thickness * 0.5;
    fLayer2YCoord = fLayer1YCoord - fLayer1Thickness * 0.5 - fLayer2Thickness * 0.5;
    fLayer3YCoord = fLayer2YCoord - fLayer2Thickness * 0.5 - fLayer3Thickness * 0.5;
    fLayer4YCoord = fLayer3YCoord - fLayer3Thickness * 0.5 - fLayer4Thickness * 0.5;
    fLayer5YCoord = fLayer4YCoord - fLayer4Thickness * 0.5 - fLayer5Thickness * 0.5;

    fLayerXCoord = 3. * m;
    fLayerZCoord = 0. * m;

    fLayer1Coord = G4ThreeVector(fLayerXCoord, fLayer1YCoord, fLayerZCoord);
    fLayer2Coord = G4ThreeVector(fLayerXCoord, fLayer2YCoord, fLayerZCoord);
    fLayer3Coord = G4ThreeVector(fLayerXCoord, fLayer3YCoord, fLayerZCoord);
    fLayer4Coord = G4ThreeVector(fLayerXCoord, fLayer4YCoord, fLayerZCoord);
    fLayer5Coord = G4ThreeVector(fLayerXCoord, fLayer5YCoord, fLayerZCoord);

    if(fLayer1Phys){
        fLayer1Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer1", fLayerSizeX, fLayer1Thickness * 0.5, fLayerSizeZ));
    }
    if(fLayer2Phys){
        fLayer2Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer2", fLayerSizeX, fLayer2Thickness * 0.5, fLayerSizeZ));
    }
    if(fLayer3Phys){
        fLayer3Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer3", fLayerSizeX, fLayer3Thickness * 0.5, fLayerSizeZ));
    }
    if(fLayer4Phys){
        fLayer4Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer4", fLayerSizeX, fLayer4Thickness * 0.5, fLayerSizeZ));
    }
    if(fLayer5Phys){
        fLayer5Phys->GetLogicalVolume()->SetSolid(new G4Box("Layer5", fLayerSizeX, fLayer5Thickness * 0.5, fLayerSizeZ));
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

G4double LayerGeometry::GetTotalLayerThickness() const
{
    return fLayer1Thickness + fLayer2Thickness + fLayer3Thickness + fLayer4Thickness + fLayer5Thickness;
}
