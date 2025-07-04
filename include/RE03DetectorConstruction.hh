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
/// \file runAndEvent/RE03/include/RE03DetectorConstruction.hh
/// \brief Definition of the RE03DetectorConstruction class
//
//

#ifndef RE03DetectorConstruction_h
#define RE03DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "Material.hh"
#include <cmath>

class G4VPhysicalVolume;
class G4Material;

class RE03DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    RE03DetectorConstruction();
    virtual ~RE03DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetWorldSize(G4double x, G4double y, G4double z);

  private:
    void DefineMaterials();
    void ConstructWorldGeometry();
    //void ConstructOuterWallGeometry();
    //void ConstructInnerWallGeometry();
    //void UpdateGeometry();


  private:
    Material* fMaterial; 

    G4VPhysicalVolume* fWorldPhys;
    G4LogicalVolume* fWorldLogical;
    G4bool fConstructed;


    G4double fWorldHalfSizeX = 15. * m;
    G4double fWorldHalfSizeY = 20. * m;
    G4double fWorldHalfSizeZ = 5. * m;

    G4double fWallWorldGap = 1.0 * m;
    G4double fWallThickness = 1.0 * m;


};

#endif
