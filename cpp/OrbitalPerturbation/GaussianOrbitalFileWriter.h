#ifndef ORBITALPERTURBATION_GAUSSIANORBITALFILEWRITER_H
#define ORBITALPERTURBATION_GAUSSIANORBITALFILEWRITER_H

#include "MolecularOrbitals.h"
#include <fstream>

namespace OrbitalPerturbation {

/*!
 * Class to read a formatted Gaussian checkpoint file and extract the orbitals
 */
class GaussianOrbitalFileWriter {
 public:
  GaussianOrbitalFileWriter(const MolecularOrbitals& orbitals, const std::string& inFile, const std::string& outFile);
  void write();

 private:
  void openInFile(const std::string& file);
  void openOutFile(const std::string& file);
  void checkAlphaOrbitals(const std::string& line);
  void checkBetaOrbitals(const std::string& line);
  void ignoreInputLines();
  void writeCoefficients(const Eigen::MatrixXd& c);

  const MolecularOrbitals& orbitals_;
  std::ifstream fin_;
  std::ofstream fout_;
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_GAUSSIANORBITALFILEWRITER_H
