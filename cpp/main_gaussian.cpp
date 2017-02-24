#include "OrbitalPerturbation/GaussianOrbitalFileReader.h"
#include "OrbitalPerturbation/MolecularOrbitals.h"
#include "OrbitalPerturbation/GaussianOrbitalFileWriter.h"
#include "OrbitalPerturbation/Mixing.h"
#include "OrbitalPerturbation/RandomSeed.h"
#include <iostream>

using namespace OrbitalPerturbation;

/*!
 * Executable to mix the orbitals of Gaussian formatted checkpoint files.
 * It reads a random seed from the file "seed" and then writes back to it to avoid generating the same random mixes between successive executions.
 * Usage: [executable] [original formatted checkpoint file] [perturbed formatted checkpoint file]
 *  f.i.: ./turbomoleOrbitalMixer checkpoint_original.fchk checkpoint_perturbed.fchk
 */
int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: <executable> <original_checkpoint_file> <perturbed_checkpoint_file>" << std::endl;
    return 1;
  }

  std::string chkFileName = argv[1];
  std::string newChkFileName = argv[2];

  std::string seedFile;
  bool seedProvided = (argc > 3);
  if (seedProvided)
    seedFile = argv[3];

  GaussianOrbitalFileReader gt(chkFileName);

  auto mo = gt.getOrbitals();
  unsigned nAlpha = gt.getNumberAlphaElectrons();
  unsigned nBeta = gt.getNumberBetaElectrons();

  if (seedProvided)
    RandomSeed::readSeed(seedFile);
  Mixing::mixOrbitals(mo, nAlpha, nBeta);
  if (seedProvided)
    RandomSeed::writeSeed(seedFile);

  GaussianOrbitalFileWriter wt(mo, chkFileName, newChkFileName);
  wt.write();
}