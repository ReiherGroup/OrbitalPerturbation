#ifndef GAUSSIANORBITALFILEWRITER_H
#define GAUSSIANORBITALFILEWRITER_H

#include "MolecularOrbitals.h"
#include <fstream>

namespace Miscellaneous {

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

} // namespace Miscellaneous

#endif // GAUSSIANORBITALFILEWRITER_H
