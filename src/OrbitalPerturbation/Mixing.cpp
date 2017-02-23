#include "Mixing.h"
#include "MolecularOrbitals.h"
#include "RandomOrbitalMixer.h"
#include <iostream>

void mixOrbitals(MolecularOrbitals& mo, unsigned nAlpha, unsigned nBeta) {
  std::cout << "Number alpha els: " << nAlpha << std::endl;
  std::cout << "Number beta  els: " << nBeta << std::endl;

  std::cout << "Alpha:\n" << mo.alphaMatrix() << std::endl;
  std::cout << "Beta:\n" << mo.alphaMatrix() << std::endl;

  MultipleScfSolutions::RandomOrbitalMixer mixer(mo, nAlpha, nBeta);
  mixer.setMaximalMixAngle(1.57);
  mixer.setNumberMixes(10);
  mixer.considerOnlyOrbitalsCloseToFrontierOrbitals(15);
  mixer.mix();
}
