#include "SteppingAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction()
    : G4UserSteppingAction(), fTrackID(0), fParticleType(""), fEnergy(0.0), fPhantomName("")
{
    // Constructor implementation
}
void SteppingAction::UserSteppingAction(const G4Step* step)
{
    /**
     * Analysis only begins if the particle
     * on the phantom boundary. Otherwise, 
     * the analysis is not performed.
     */
    auto analysisManager = G4AnalysisManager::Instance();
    if(step)
    {
        if(step -> GetPostStepPoint() -> GetStepStatus() == fGeomBoundary)
        {
            G4String volName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();
            G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
            if ((volName == "Phantom1" || volName == "Phantom2" || volName == "Phantom3" ||
                volName == "Phantom4" || volName == "Phantom5") &&
                allowedParticles.count(particleName))
            {   
                fPhantomName = volName;
                fTrackID = step->GetTrack()->GetTrackID();
                fParticleType = particleName;
                fEnergy = step->GetTrack()->GetTotalEnergy() / MeV;

                analysisManager->FillNtupleIColumn(0, fTrackID);
                analysisManager->FillNtupleSColumn(1, fParticleType);
                analysisManager->FillNtupleDColumn(2, fEnergy);
                analysisManager->FillNtupleSColumn(3, fPhantomName);
                analysisManager->AddNtupleRow();
            }

        }
        
    } 
    
    
}