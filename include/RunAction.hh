#pragma once

#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction 
{
public:
    RunAction();
    virtual ~RunAction() override = default;

    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;

};