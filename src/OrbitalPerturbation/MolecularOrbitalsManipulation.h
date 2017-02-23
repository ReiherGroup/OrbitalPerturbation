#ifndef MOLECULARORBITALSORBITALSMANIPULATION_H
#define MOLECULARORBITALSORBITALSMANIPULATION_H

#include <Eigen/Core>
#include <vector>
class MolecularOrbitals;
namespace LcaoUtil {

/*!
 * Class for transformations on molecular orbitals.
 */
class MolecularOrbitalsManipulation {
 public:
  /*! Struct to specify swaps.
   * Given two orbitals, they will be switched for the generation of the density matrix.
   * Thereby, lowLyingOrbitalNotToFill is going to be -1 (HOMO), -2, -3, -4, ...
   * and highLyingOrbitalToFill is going to be +1 (LUMO), +2, +3, +4, ... */
  struct DeprecatedSwap {
    int lowLyingOrbitalNotToFill_, highLyingOrbitalToFill_;
    DeprecatedSwap(int lowLyingOrbitalNotToFill, int highLyingOrbitalToFill) : lowLyingOrbitalNotToFill_(lowLyingOrbitalNotToFill), highLyingOrbitalToFill_(highLyingOrbitalToFill) {}
  };
  /*! Struct to specify Mixing.
   * Given two orbitals, they will be mixed for the generation of the density matrix.
   * Thereby, lowLyingOrbitalNotToFill is going to be -1 (HOMO), -2, -3, -4, ...
   * and highLyingOrbitalToFill is going to be +1 (LUMO), +2, +3, +4, ...
   * angleInRad_ specifies the angle with which they will be mixed (0 doesn't do anything, pi/2 swaps them). */
  struct DeprecatedMix {
    int lowLyingOrbitalNotToFill_, highLyingOrbitalToFill_;
    double angleInRad_;
    DeprecatedMix(int lowLyingOrbitalNotToFill, int highLyingOrbitalToFill, double angleInrad) : lowLyingOrbitalNotToFill_(lowLyingOrbitalNotToFill), highLyingOrbitalToFill_(highLyingOrbitalToFill), angleInRad_(angleInrad) {}
  };
  /*! Struct to specify swaps.
   * Given two orbitals, they will be swapped. */
  struct Swap {
    int orbital1_, orbital2_;
    Swap(int orbital1, int orbital2) : orbital1_(orbital1), orbital2_(orbital2) {}
  };
  /*! Struct to specify Mixing.
   * Given two orbitals, they will be mixed.
   * angleInRad_ specifies the angle with which they will be mixed (0 doesn't do anything, pi/2 swaps them). */
  struct Mix {
    int orbital1_, orbital2_;
    double angleInRad_;
    Mix(int orbital1, int orbital2, double angleInrad) : orbital1_(orbital1), orbital2_(orbital2), angleInRad_(angleInrad) {}
  };

  static void swapRestricted(MolecularOrbitals& orbitals, const std::vector<Swap>& swaps);
  static void swapUnrestricted(MolecularOrbitals& orbitals, const std::vector<Swap>& alphaSwaps, const std::vector<Swap>& betaSwaps);
  static void mixRestricted(MolecularOrbitals& orbitals, const std::vector<Mix>& mixes);
  static void mixUnrestricted(MolecularOrbitals& orbitals, const std::vector<Mix>& alphaMixes, const std::vector<Mix>& betaMixes);

  static MolecularOrbitals createRestrictedWithSwaps(const MolecularOrbitals& orbitals, const std::vector<Swap>& swaps);
  static MolecularOrbitals createUnrestrictedWithSwaps(const MolecularOrbitals& orbitals, const std::vector<Swap>& alphaSwaps, const std::vector<Swap>& betaSwaps);
  static MolecularOrbitals createRestrictedWithMixes(const MolecularOrbitals& orbitals, const std::vector<Mix>& mixes);
  static MolecularOrbitals createUnrestrictedWithMixes(const MolecularOrbitals& orbitals, const std::vector<Mix>& alphaMixes, const std::vector<Mix>& betaMixes);

 private:
  static void swapOrbitalCoefficients(Eigen::MatrixXd& coefficientMatrix, const std::vector<Swap>& swaps);
  static void mixOrbitalCoefficients(Eigen::MatrixXd& coefficientMatrix, const std::vector<Mix>& mixes);
};

} // namespace LcaoUtil

#endif // MOLECULARORBITALSORBITALSMANIPULATION_H