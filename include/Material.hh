#pragma once

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "G4Element.hh"


class Material
{
public:
  Material();
  ~Material();

public:
  G4Material* GetHDConcrete();
  G4Material* GetBoronPolyethylene();
  G4Material* GetLead();
  G4Material* GetIron();
  G4Material* GetAluminium();
  G4Material* GetStainlessSteel();
  G4Material* GetAir();
  G4Material* GetVacuum();
  G4Material* GetTissue();

private:
  void ConstructHDConcrete();
  void ConstructBoronPolyethylene();
  void ConstructLead();
  void ConstructIron();
  void ConstructAluminium();
  void ConstructStainlessSteel();
  void ConstructAir();
  void ConstructVacuum();
  void Constructtissue();
private:
  G4Material* fHDConcrete;
  G4Material* fBoronPolyethylene;
  G4Material* fLead;
  G4Material* fIron;
  G4Material* fAluminium;
  G4Material* fStainlessSteel;
  G4Material* fAir;
  G4Material* fVacuum;
  G4Material* fTissue;

  /*
  Defining general elements here
  */
  G4double A;  // atomic mass
  G4double Z;  // atomic number
  G4double d;  // density
     
  // General elements
     
  G4Element* elH = new G4Element ("Hydrogen","H",Z = 1.,A = 1.01*g/mole);

  G4Element* elB = new G4Element("Boron","B",Z = 5.,A = 10.811*g/mole);

  G4Element* elC = new G4Element("Carbon","C",Z = 6.,A = 12.011*g/mole);
  
  G4Element* elN = new G4Element("Nitrogen","N",Z = 7.,A = 14.01*g/mole);

  G4Element* elO = new G4Element("Oxygen","O",Z = 8.,A = 16.00*g/mole);

  G4Element* elNa = new G4Element("Sodium","Na",Z = 11.,A = 22.99*g/mole);
  
  G4Element* elMg = new G4Element("Magnesium","Mg",Z = 12.,A = 24.305*g/mole);

  G4Element* elAl = new G4Element("Aluminum","Al", Z = 13.,A = 26.98*g/mole);

  G4Element* elSi  = new G4Element("Silicon","Si",Z = 14.,A = 28.09*g/mole);

  G4Element* elP = new G4Element("Phosphorus","P",Z = 15.,A = 30.974*g/mole);
  
  G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A = 32.06*g/mole);
  
  G4Element* elCl = new G4Element("Chlorine","Cl",Z = 17.,A = 35.453*g/mole);
  
  G4Element* elK = new G4Element("Potassium","K",Z = 19.,A = 39.098*g/mole);

  G4Element* elCa = new G4Element("Calcium","Ca",Z = 20.,A = 40.08*g/mole);

  G4Element* elCr  = new G4Element("Chromium","Cr",Z = 24.,A = 52.00*g/mole);

  G4Element* elMn   =  new G4Element("Manganese","Mn",Z = 25.,A = 54.94*g/mole);

  G4Element* elFe  = new G4Element("Iron","Fe",Z = 26.,A = 55.85*g/mole);

  G4Element* elNi  = new G4Element("Nickel","Ni",Z = 28.,A = 58.70*g/mole);
  
  G4Element* elZn = new G4Element("Zinc","Zn",Z = 30.,A = 65.38*g/mole); 

  G4Element* elPb = new G4Element("Lead", "Pb", Z = 82., A = 207.20*g/mole);

};