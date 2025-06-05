#pragma once

#include "G4UserSteppingAction.hh"
#include "G4Types.hh"
#include "G4String.hh"

#include <set>
class SteppingAction : public G4UserSteppingAction 
{
public:
    SteppingAction();
    virtual ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step* step) override;

private:
    G4int fTrackID;          // Track ID of the current step
    G4String fParticleType;  // Type of the particle in the current step
    G4double fEnergy;        // Energy of the particle in the current step
    G4String fPhantomName;   // Name of the phantom in the current step
    std::set<std::string> allowedParticles = {"e-", "proton", "neutron", "alpha", "mu+", "mu-", "gamma"};

};