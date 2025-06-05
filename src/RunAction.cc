#include "RunAction.hh"

#include "G4AnalysisManager.hh"

RunAction::RunAction()
{
    // Creating an instance of the analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager -> SetVerboseLevel(1);
    analysisManager -> SetNtupleMerging(false);

    analysisManager -> CreateNtuple("RE03", "RE03 Ntuple");
    analysisManager -> CreateNtupleIColumn("trackID");
    analysisManager -> CreateNtupleSColumn("particleType");
    analysisManager -> CreateNtupleDColumn("energy");
    analysisManager -> CreateNtupleSColumn("phantomName");
    analysisManager -> FinishNtuple();

}
void RunAction::BeginOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    G4String fileName = "SpectrumExtraction.root";
    analysisManager->OpenFile(fileName);
    G4cout << "Using: " << analysisManager -> GetType() << G4endl;
}
void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    if (analysisManager->IsOpenFile()) {
        //analysisManager->Write();
        analysisManager->CloseFile();
    } else {
        G4cerr << "Error: Analysis file is not open!" << G4endl;
        G4cout << "Aborting run action." << G4endl;
        G4Exception("RunAction::EndOfRunAction", "AnalysisError", FatalException, "Analysis file is not open.");
    }
}
