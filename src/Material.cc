#include "Material.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"
Material::Material() : 
  fHDConcrete(nullptr),
  fBoronPolyethylene(nullptr),
  fLead(nullptr),
  fIron(nullptr),
  fAluminium(nullptr),
  fStainlessSteel(nullptr),
  fAir(nullptr)
{
  
}
Material::~Material()
{
  ;
}
void Material::ConstructHDConcrete()
{
  G4double density = 2.4 * g / cm3;
  G4double fractionmass;
  G4int ncomponents = 11;
  fHDConcrete = new G4Material("HDConcrete", density, ncomponents);
  
  fHDConcrete->AddElement(elH, fractionmass = 0.58 / 100);
  fHDConcrete->AddElement(elC, fractionmass = 7.42 / 100);
  fHDConcrete->AddElement(elO, fractionmass = 46.03 / 100);
  fHDConcrete->AddElement(elNa, fractionmass = 0.04 /100);
  fHDConcrete->AddElement(elMg, fractionmass = 1.44 / 100);
  fHDConcrete->AddElement(elAl, fractionmass = 0.55 / 100);
  fHDConcrete->AddElement(elSi, fractionmass = 3.09 / 100);
  fHDConcrete->AddElement(elS, fractionmass = 0.18 / 100);
  fHDConcrete->AddElement(elK, fractionmass = 0.10 / 100);
  fHDConcrete->AddElement(elCa, fractionmass = 29.47 / 100);
  fHDConcrete->AddElement(elFe, fractionmass = 11.1 / 100);
}
void Material::ConstructBoronPolyethylene()
{
  G4double density = 0.969 * g / cm3;
  G4double fractionmass;
  G4int ncomponents = 3;
  fBoronPolyethylene = new G4Material("BoronPolyethylene", density, ncomponents);
  
  fBoronPolyethylene->AddElement(elH, fractionmass = 13.45);
  fBoronPolyethylene->AddElement(elB, fractionmass = 5.00);
  fBoronPolyethylene->AddElement(elC, fractionmass = 81.55);
}
void Material::ConstructLead()
{
  G4double density = 11.35 * g / cm3;
  G4int ncomponents = 1;
  fLead = new G4Material("Lead", density, ncomponents);
  
  fLead->AddElement(elPb, 100 * perCent);
}
void Material::ConstructIron()
{
  G4double density = 7.87 * g / cm3;
  G4int ncomponents = 1;
  fIron = new G4Material("Iron", density, ncomponents);
  
  fIron->AddElement(elFe, 100 * perCent);
}
void Material::ConstructAluminium()
{
  G4double density = 2.70 * g / cm3;
  G4int ncomponents = 1;
  fAluminium = new G4Material("Aluminium", density, ncomponents);
  
  fAluminium->AddElement(elAl, 100 * perCent);
}
void Material::ConstructStainlessSteel()
{
  G4double density = 8.02 * g / cm3;
  G4int ncomponents = 5;
  fStainlessSteel = new G4Material("Stainless Steel", density, ncomponents);
  
  fStainlessSteel->AddElement(elMn, 0.02);
  fStainlessSteel->AddElement(elSi, 0.01);
  fStainlessSteel->AddElement(elCr, 0.19);
  fStainlessSteel->AddElement(elNi, 0.10);
  fStainlessSteel->AddElement(elFe, 0.68);
}
void Material::ConstructAir()
{
  G4double density = 1.29 * mg / cm3;
  G4int ncomponents = 2;
  fAir = new G4Material("Air", density, ncomponents);
  
  fAir->AddElement(elN, 70.0 * perCent);
  fAir->AddElement(elO, 30.0 * perCent);
}
void Material::ConstructVacuum()
{
  G4double density     = 1.e-25*g/cm3;                //from PhysicalConstants.h
  G4double pressure    = 1.e-6*133 * pascal;
  G4double temperature = 0.1*kelvin;
  G4double Z = 1; 
  G4double A = 1.01 * g / mole;
  fVacuum = new G4Material("Vacuul", Z, A, density,
                   kStateGas, temperature, pressure);
  
  fVacuum->AddElement(elH, 100 * perCent);
}
G4Material* Material::GetHDConcrete() 
{
  ConstructHDConcrete();
  G4cout << "HDConcrete is successfully constructed" << G4endl;
  return fHDConcrete;
}
G4Material* Material::GetBoronPolyethylene() 
{
  ConstructBoronPolyethylene();
  G4cout << "BoronPolyethylene is successfully constructed" << G4endl;
  return fBoronPolyethylene;
}
G4Material* Material::GetLead() 
{
  ConstructLead();
  G4cout << "Lead is successfully constructed" << G4endl;
  return fLead;
}
G4Material* Material::GetIron() 
{
  ConstructIron();
  G4cout << "Iron is successfully constructed" << G4endl;
  return fIron;
}
G4Material* Material::GetAluminium() 
{
  ConstructAluminium();
  G4cout << "Aluminium is successfully constructed" << G4endl;
  return fAluminium;
}
G4Material* Material::GetStainlessSteel() 
{
  ConstructStainlessSteel();
  G4cout << "StainlessSteel is successfully constructed" << G4endl;
  return fStainlessSteel;
}
G4Material* Material::GetAir() 
{
  ConstructAir();
  G4cout << "Air is successfully constructed" << G4endl;
  return fAir;
}
G4Material* Material::GetVacuum() 
{
  ConstructVacuum();
  G4cout << "Vacuum is successfully constructed" << G4endl;
  return fVacuum;
}