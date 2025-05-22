//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file runAndEvent/RE03/src/RE03DetectorConstruction.cc
/// \brief Implementation of the RE03DetectorConstruction class
//
//

#include "RE03DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4NistManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSNofStep.hh"
#include "G4PSTrackLength.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SDParticleFilter.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

#include "LayerGeometry.hh"
#include "Material.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RE03DetectorConstruction::RE03DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fWorldPhys(0),
    fOuterWallPhys(0),
    fInnerWallPhys(0),
    fWorldLogical(0),
    fOuterWallLogical(0),
    fInnerWallLogical(0),
    fConstructed(false)
{
  ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RE03DetectorConstruction::~RE03DetectorConstruction()
{
  delete fMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* RE03DetectorConstruction::Construct()
{
  if (!fConstructed) {
    fConstructed = true;
    DefineMaterials();
    ConstructWorldGeometry();
    ConstructOuterWallGeometry();
    ConstructInnerWallGeometry();
    LayerGeometry* layerGeometry = new LayerGeometry(fInnerWallLogical);
    layerGeometry->ConstructLayerGeometry(fWorldSizeY, fWallWorldGap, fWallThickness);
    layerGeometry->ConstructTubeAndChamber();
  }
  return fWorldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RE03DetectorConstruction::DefineMaterials()
{
  fMaterial = new Material();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RE03DetectorConstruction::ConstructWorldGeometry()
{
  G4VSolid* worldSolid = new G4Box("World", fWorldSizeX, fWorldSizeY, fWorldSizeZ);
  fWorldLogical = new G4LogicalVolume(worldSolid, fMaterial -> GetAir(), "World");
  fWorldPhys = new G4PVPlacement(0, G4ThreeVector(), fWorldLogical, "World", 0, false, 0);
}

void RE03DetectorConstruction::ConstructOuterWallGeometry()
{
  G4VSolid* outerWallSolid = new G4Box("OuterWall", OuterWallSizeX, OuterWallSizeY, OuterWallSizeZ);
  fOuterWallLogical = new G4LogicalVolume(outerWallSolid, fMaterial -> GetIron(), "OuterWall");
  fOuterWallPhys = new G4PVPlacement(0, G4ThreeVector(), fOuterWallLogical, "OuterWall", fWorldLogical,
                                     false, 0);
  fOuterWallLogical -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
}

void RE03DetectorConstruction::ConstructInnerWallGeometry()
{
  G4VSolid* innerWallSolid = new G4Box("InnerWall", InnerWallSizeX, InnerWallSizeY, InnerWallSizeZ);
  fInnerWallLogical = new G4LogicalVolume(innerWallSolid, fMaterial -> GetAir(), "InnerWall");
  fInnerWallPhys = new G4PVPlacement(0, G4ThreeVector(), fInnerWallLogical, "InnerWall",
                                     fOuterWallLogical, false, 0);
  fInnerWallLogical -> SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
}
void RE03DetectorConstruction::UpdateGeometry()
{ 
  OuterWallSizeX = fWorldSizeX - 2 * fWallWorldGap;
  OuterWallSizeY = fWorldSizeY - 2 * fWallWorldGap;
  OuterWallSizeZ = fWorldSizeZ - 2 * fWallWorldGap;

  InnerWallSizeX = OuterWallSizeX - 2 * fWallThickness;
  InnerWallSizeY = OuterWallSizeY - 2 * fWallThickness;
  InnerWallSizeZ = OuterWallSizeZ - 2 * fWallThickness;
  if (fWorldPhys) {
    fWorldPhys->GetLogicalVolume()->SetSolid(new G4Box("World", fWorldSizeX, fWorldSizeY, fWorldSizeZ));
  }
  if (fOuterWallPhys) {
    fOuterWallPhys->GetLogicalVolume()->SetSolid(new G4Box("OuterWall", OuterWallSizeX, OuterWallSizeY,
                                                           OuterWallSizeZ));
  }
  if (fInnerWallPhys) {
    fInnerWallPhys->GetLogicalVolume()->SetSolid(new G4Box("InnerWall", InnerWallSizeX, InnerWallSizeY,
                                                           InnerWallSizeZ));
  }
}
void RE03DetectorConstruction::SetWorldSize(G4double x, G4double y, G4double z)
{
  fWorldSizeX = x;
  fWorldSizeY = y;
  fWorldSizeZ = z;
  UpdateGeometry();
}
void RE03DetectorConstruction::SetWallThickness(G4double t)
{
  fWallThickness = t;
  UpdateGeometry();
}
void RE03DetectorConstruction::ConstructSDandField()
{
  ;
}
