#ifndef ORBITALPERTURBATION_MIXING_H
#define ORBITALPERTURBATION_MIXING_H

namespace OrbitalPerturbation {
class MolecularOrbitals;

class Mixing {
 public:
  static void mixOrbitals(MolecularOrbitals& mo, unsigned nAlpha, unsigned nBeta);
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_MIXING_H