#include "WallGeometry.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

WallGeometry::WallGeometry(G4LogicalVolume* innerWorldLogical)
    : fInnerWorldLogical(innerWorldLogical),
      fOuterWallLogical(nullptr),
      fInnerWallLogical(nullptr)
{
    fMaterial = new Material();
}
WallGeometry::~WallGeometry()
{
    // Destructor implementation
}
void WallGeometry::ConstructWallGeometry()
{
    ConstructOuterWallGeometry();
    ConstructInnerWallGeometry();
}
void WallGeometry::ConstructOuterWallGeometry()
{
    G4VSolid* outerWallSolid = new G4Box("OuterWall", fOuterWallHalfSizeX, fOuterWallHalfSizeY, fOuterWallHalfSizeZ);
    fOuterWallLogical = new G4LogicalVolume(outerWallSolid, fMaterial->GetConcrete(), "OuterWall");
    new G4PVPlacement(0, G4ThreeVector(), fOuterWallLogical, "OuterWall", fInnerWorldLogical,
                                      false, 0);
    fOuterWallLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
}
void WallGeometry::ConstructInnerWallGeometry()
{
    G4VSolid* innerWallSolid = new G4Box("InnerWall", fInnerWallHalfSizeX, fInnerWallHalfSizeY, fInnerWallHalfSizeZ);
    fInnerWallLogical = new G4LogicalVolume(innerWallSolid, fMaterial->GetAir(), "InnerWall");
    new G4PVPlacement(0, G4ThreeVector(), fInnerWallLogical, "InnerWall", fOuterWallLogical,
                                      false, 0);
    fInnerWallLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
}
