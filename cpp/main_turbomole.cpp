#include "OrbitalPerturbation/TurbomoleNumberStringConverter.h"
#include "OrbitalPerturbation/TurbomoleOrbitalFileReader.h"
#include "OrbitalPerturbation/TurbomoleOrbitalFileWriter.h"
#include "OrbitalPerturbation/RandomSeed.h"
#include "OrbitalPerturbation/Mixing.h"
#include "OrbitalPerturbation/MolecularOrbitals.h"

using namespace std;
using namespace OrbitalPerturbation;

/*!
 * Executable to mix alpha and beta orbitals of turbomole files.
 * It creates the new orbital files alpha_mixed and beta_mixed.
 * It reads a random seed from the file "seed" and then writes back to it to avoid generating the same random mixes between successive executions.
 * Usage: [executable] [number of orbitals] [number of alpha electrons] [number of beta electrons]
 *  f.i.: ./turbomoleOrbitalMixer alpha beta 88 19 16
 */
int main(int argc, char *argv[]) {
  string current_exec_name = argv[0];

  if (argc < 5) {
    cout << "Usage: [executable] [alpha_filename] [beta_filename] [number of orbitals] [number of alpha electrons] [number of beta electrons]" << endl;
    return 1;
  }
  string alpha_file = argv[1];
  string beta_file = argv[2];
  string nOrbitalsString = argv[3];
  string nAlphaString = argv[4];
  string nBetaString = argv[5];
  auto nOrbitals = static_cast<unsigned>(stoi(nOrbitalsString));
  auto nAlpha = static_cast<unsigned>(stoi(nAlphaString));
  auto nBeta = static_cast<unsigned>(stoi(nBetaString));


  TurbomoleOrbitalFileReader ta(alpha_file, nOrbitals);
  TurbomoleOrbitalFileReader tb(beta_file, nOrbitals);

  MolecularOrbitals mo = MolecularOrbitals::createFromUnrestrictedCoefficients(ta.getCoefficientMatrix(), tb.getCoefficientMatrix());

  RandomSeed::readSeed("seed");
  Mixing::mixOrbitals(mo, nAlpha, nBeta);
  RandomSeed::writeSeed("seed");

  TurbomoleOrbitalFileWriter wa(mo.alphaMatrix(), ta.getMetaInformation());
  TurbomoleOrbitalFileWriter wb(mo.betaMatrix(), tb.getMetaInformation());
  wa.writeToFile(alpha_file);
  wb.writeToFile(beta_file);
}