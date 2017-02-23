#ifndef MULTIPLESCFSOLUTIONS_ORBITALMIXER_H
#define MULTIPLESCFSOLUTIONS_ORBITALMIXER_H

#include "MolecularOrbitalsManipulation.h"
#include <random>
#include <assert.h>
class MolecularOrbitals;
namespace MultipleScfSolutions {

/*!
 * Class to randomly mix randomly chosen molecular orbitals.
 * In the restricted case, the alphaHomo_ and betaHomo_ are both holding the value for restrictedHomo_.
 */
class RandomOrbitalMixer {
 public:
  /*! Constructor for the restricted case. */
  RandomOrbitalMixer(MolecularOrbitals& orbitals, int nRestrictedElectrons);
  /*! Constructor for the unrestricted case. */
  RandomOrbitalMixer(MolecularOrbitals& orbitals, int nAlphaElectrons, int nBetaElectrons);
  void mix();
  void setNumberMixes(int numberMixes);
  void setMaximalMixAngle(double maxAngle);
  void setMinimalMixAngle(double minAngle);
  /*! \par numberToConsider Will be the same both for occupied and virtual orbitals. */
  void considerOnlyOrbitalsCloseToFrontierOrbitals(int numberToConsider);
  void considerAllOrbitals();
  static std::mt19937& getRandomNumberGenerator();

 private:
  void checkValidNumberOfMixes();
  std::vector<LcaoUtil::MolecularOrbitalsManipulation::Mix> calculateMixes(int homoIndex) const;
  std::vector<int> getRandomOccupiedOrbitals(int homoIndex) const;
  std::vector<int> getRandomVirtualOrbitals(int homoIndex) const;
  std::vector<int> selectUniqueRandomNumbers(int min, int max) const;
  std::vector<LcaoUtil::MolecularOrbitalsManipulation::Mix>
  createMixes(const std::vector<int>& occ, const std::vector<int>& virt) const;
  int calculateMaximalVirtualIndex(int homoIndex) const;
  int calculateMinimalOccupiedIndex(int homoIndex) const;
  bool invalidMolecularOrbitals(const MolecularOrbitals& mo) const;

  static std::mt19937 rdGen_; // NB: if non-static, the same orbital mixes will always be generated.
  MolecularOrbitals& orbitals_;
  const int alphaHomo_;
  const int betaHomo_;
  const int nOrbitals_;
  double minAngle_ = 0;
  double maxAngle_ = 0.02;
  int numberMixes_ = 10;
  bool considerAllOrbitals_ = true;
  int numberOrbitalsToConsider_ = 0;
};

inline void RandomOrbitalMixer::setNumberMixes(int numberMixes) {
  assert(numberMixes >= 0);
  numberMixes_ = numberMixes;
}

inline void RandomOrbitalMixer::setMaximalMixAngle(double maxAngle) {
  maxAngle_ = maxAngle;
}

inline void RandomOrbitalMixer::setMinimalMixAngle(double minAngle) {
  minAngle_ = minAngle;
}

inline std::mt19937& RandomOrbitalMixer::getRandomNumberGenerator() {
  return rdGen_;
}

} // namespace MultipleScfSolutions

#endif // MULTIPLESCFSOLUTIONS_ORBITALMIXER_H