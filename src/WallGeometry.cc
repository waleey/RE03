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
    ConstructEastPolyWallGeometry();
    ConstructNorthPolyWallGeometry();
    G4cout << "Wall geometry is successfully constructed" << G4endl;
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
    new G4PVPlacement(0, G4ThreeVector(-fChangeOffset * 0.5, 0, 0), fInnerWallLogical, "InnerWall", fOuterWallLogical,
                                      false, 0);
    fInnerWallLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
}
void WallGeometry::ConstructEastPolyWallGeometry()
{
    G4double xHalfSize = 1.5 * foot;
    G4double yHalfSize = 3. * m;
    G4double zHalfSize = 4 * foot;

    G4double xCoord = 8.28675 * m + 6 * foot;
    G4double yCoord = fInnerWallHalfSizeY - yHalfSize;
    G4double zCoord = - (fInnerWallHalfSizeZ - zHalfSize);

    G4VSolid* eastPolyWallSolid = new G4Box("EastPolyWall", xHalfSize, yHalfSize, zHalfSize);
    G4LogicalVolume* eastPolyWallLogical = new G4LogicalVolume(eastPolyWallSolid, fMaterial->GetHDPE(), "EastPolyWall");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), eastPolyWallLogical, "EastPolyWall", fInnerWallLogical,
                                      false, 0);
    eastPolyWallLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
}
void WallGeometry::ConstructNorthPolyWallGeometry()
{
    //north wall is placed a meter left of the dump
    
    G4double xHalfSize = 3. * m;
    G4double yHalfSize = 1.5 * foot;
    G4double zHalfSize = 4 * foot;

    G4double xCoord = fInnerWallHalfSizeX - (9 * foot + 10.5 * inch) - 1 * m - xHalfSize;
    G4double yCoord = fInnerWallHalfSizeY - yHalfSize;
    G4double zCoord = - (fInnerWallHalfSizeZ - zHalfSize);

    G4VSolid* northPolyWallSolid = new G4Box("NorthPolyWall", xHalfSize, yHalfSize, zHalfSize);
    G4LogicalVolume* northPolyWallLogical = new G4LogicalVolume(northPolyWallSolid, fMaterial->GetHDPE(), "NorthPolyWall");
    new G4PVPlacement(0, G4ThreeVector(xCoord, yCoord, zCoord), northPolyWallLogical, "NorthPolyWall", fInnerWallLogical,
                                      false, 0);
    northPolyWallLogical->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
}