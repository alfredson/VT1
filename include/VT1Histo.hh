// VT1 Histo header file
// By R. C. Alfredson

#ifndef VT1Histo_h
#define VT1Histo_h 1

#include "globals.hh"
#include "TH1.h"

class TTree;
class TFile;
class TH1D;

class VT1HistoMessenger;

class VT1Histo
{
public:
  VT1Histo();
  ~VT1Histo();

  void book();
  void save();
  void PrintStatistic();

  void setHistoTitle(G4String);
  void setLowerBound(G4double);
  void setUpperBound(G4double);

  G4String getHistoTitle()
  {
    return fHistoTitle;
  };
  G4double getLowerBound()
  {
    return fLowerBound;
  }
  G4double getUpperBound()
  {
    return fUpperBound;
  }


  void FillHisto(G4double bin, G4double weight = 1.0);
  void Normalize(G4double fac);
  void FillNtuple(G4double totalEnergy);

private:
  TFile* fRootFile;
  TH1D* fHisto;
  TTree* fNtuple;

  VT1HistoMessenger* fHistoMessenger;

  G4double fTotalEnergy;

  G4String fHistoTitle;
  G4double fLowerBound;
  G4double fUpperBound;
};

#endif
