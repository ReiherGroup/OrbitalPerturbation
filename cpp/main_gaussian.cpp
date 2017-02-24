#include "OrbitalPerturbation/GaussianOrbitalFileReader.h"
#include "OrbitalPerturbation/MolecularOrbitals.h"
#include "OrbitalPerturbation/GaussianOrbitalFileWriter.h"
#include "OrbitalPerturbation/Mixing.h"
#include <iostream>

/*!
 * Executable to mix the orbitals of Gaussian formatted checkpoint files.
 * It reads a random seed from the file "seed" and then writes back to it to avoid generating the same random mixes between successive executions.
 * Usage: [executable] [original formatted checkpoint file] [perturbed formatted checkpoint file]
 *  f.i.: ./turbomoleOrbitalMixer checkpoint_original.fchk checkpoint_perturbed.fchk
 */
int main(int argc, char *argv[]) {
  std::string current_exec_name = argv[0];
  std::string chkFileName;
  std::string newchkFileName;

  if (argc < 3) {
    std::cout << "Usage: <executable> <original_checkpoint_file> <perturbed_checkpoint_file>" << std::endl;
    return 1;
  }
  else {
    chkFileName = argv[1];
    newchkFileName = argv[2];
  }

  OrbitalPerturbation::GaussianOrbitalFileReader gt(chkFileName);

  auto mo = gt.getOrbitals();
  unsigned nAlpha = gt.getNumberAlphaElectrons();
  unsigned nBeta = gt.getNumberBetaElectrons();

  mixOrbitals(mo, nAlpha, nBeta);

  OrbitalPerturbation::GaussianOrbitalFileWriter wt(mo, chkFileName, newchkFileName);
  wt.write();

  return 0;
}