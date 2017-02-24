#include "Mixing.h"
#include "MolecularOrbitals.h"
#include "RandomOrbitalMixer.h"
#include <iostream>

namespace OrbitalPerturbation {

void Mixing::mixOrbitals(MolecularOrbitals& mo, unsigned nAlpha, unsigned nBeta) {
  OrbitalPerturbation::RandomOrbitalMixer mixer(mo, nAlpha, nBeta);
  mixer.setMaximalMixAngle(1.57);
  mixer.setNumberMixes(10);
  mixer.considerOnlyOrbitalsCloseToFrontierOrbitals(15);
  mixer.mix();
}

} // namespace OrbitalPerturbation
