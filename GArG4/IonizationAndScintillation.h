////////////////////////////////////////////////////////////////////////
/// \file  IonizationAndScintillation.h
/// \brief Singleton to access a unified treatment of ionization and 
///        scintillation in LAr
///
/// \author  brebel@fnal.gov
////////////////////////////////////////////////////////////////////////
#ifndef GARG4IONIZATIONANDSCINTILLATION_H
#define GARG4IONIZATIONANDSCINTILLATION_H

#include <cstring>

#include "GArG4/ISCalculation.h"

#include "Geant4/G4Step.hh"

#include "TH1.h"
#include "TH2.h"

namespace CLHEP { class HepRandomEngine; }

namespace gar {
  namespace garg4 {
    
    // The Ionization and Scintillation singleton
    class IonizationAndScintillation
    {
    public:
      
      static IonizationAndScintillation* CreateInstance(CLHEP::HepRandomEngine& engine);
      static IonizationAndScintillation* Instance();
      
      // Method to reset the internal variables held in the ISCalculation
      // This method should be called at the start of any G4Step
      void Reset(const G4Step* step);
      
      double EnergyDeposit()              const { return fISCalc->EnergyDeposit();              }
      int    NumberIonizationElectrons()  const { return fISCalc->NumberIonizationElectrons();  }
      int    NumberScintillationPhotons() const { return fISCalc->NumberScintillationPhotons(); }
      double StepSizeLimit()              const { return fISCalc->StepSizeLimit();              }
      
    private:
      
      IonizationAndScintillation(CLHEP::HepRandomEngine& engine);
      ~IonizationAndScintillation();
      
      garg4::ISCalculation* fISCalc;             ///< object to calculate ionization and scintillation
                                                 ///< produced by an energy deposition
      std::string           fISCalculator;       ///< name of calculator to use, NEST or Separate
      G4Step const*         fStep;               ///< pointer to the current G4 step
      int                   fStepNumber;         ///< last StepNumber checked
      int                   fTrkID;              ///< last TrkID checked
      
      TH1F*                 fElectronsPerStep;   ///< histogram of electrons per step
      TH1F*                 fStepSize;           ///< histogram of the step sizes
      TH1F*                 fPhotonsPerStep;     ///< histogram of the photons per step
      TH1F*                 fEnergyPerStep;      ///< histogram of the energy deposited per step
      TH1F*                 fElectronsPerLength; ///< histogram of electrons per cm
      TH1F*                 fPhotonsPerLength;   ///< histogram of photons per cm
      TH1F*                 fElectronsPerEDep;   ///< histogram of electrons per MeV deposited
      TH1F*                 fPhotonsPerEDep;     ///< histogram of photons per MeV deposited
      TH2F*                 fElectronsVsPhotons; ///< histogram of electrons vs photons per step
      CLHEP::HepRandomEngine& fEngine;           ///< random engine
    };
    
  } // namespace garg4
  
} // gar

#endif // GARG4IONIZATIONANDSCINTILLATION