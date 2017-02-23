#include "OrbitalPerturbation/GaussianOrbitalFileReader.h"
#include "OrbitalPerturbation/MolecularOrbitals.h"
#include "OrbitalPerturbation/GaussianOrbitalFileWriter.h"
#include "OrbitalPerturbation/Mixing.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  string current_exec_name = argv[0]; 
  string chkFileName;
  string newchkFileName;

  if (argc < 3) {
    cout << "Usage: <executable> <previous_checkpoint_file> <new_checkpoint_file>" << endl;
    return 1;
  }
  else {
    cout << "New calculation\n"
            "--------------------\n\n";
    chkFileName = argv[1];
    newchkFileName = argv[2];
  }

  cout << "Reading the structure from the file " << chkFileName << "." << endl;

  Miscellaneous::GaussianOrbitalFileReader gt(chkFileName);

  MolecularOrbitals mo = gt.getOrbitals();
  unsigned nAlpha = gt.getNumberAlphaElectrons();
  unsigned nBeta = gt.getNumberBetaElectrons();

  mixOrbitals(mo, nAlpha, nBeta);

  Miscellaneous::GaussianOrbitalFileWriter wt(mo, chkFileName, newchkFileName);
  wt.write();

  return 0;
}