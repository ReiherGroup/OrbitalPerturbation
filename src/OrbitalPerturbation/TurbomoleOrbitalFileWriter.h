#ifndef ORBITALPERTURBATION_TURBOMOLEORBITALFILEWRITER_H
#define ORBITALPERTURBATION_TURBOMOLEORBITALFILEWRITER_H

#include <Eigen/Core>
#include <fstream>

namespace OrbitalPerturbation {
class TurbomoleOrbitalsMetaInformation;

/*!
 * Class to write into a single Turbomole molecular orbital file (for instance alpha, beta, mo, ...).
 * For this, it needs a matrix and an instance of TurbomoleOrbitalsMetaInformation.
 */
class TurbomoleOrbitalFileWriter {
 public:
  TurbomoleOrbitalFileWriter(const Eigen::MatrixXd& coefficientMatrix, const TurbomoleOrbitalsMetaInformation& metaInformation);
  void writeToFile(const std::string& file);

 private:
  void writeHeader();
  void writeOrbitals();
  void writeOneOrbital();
  void writeFooter();

  const Eigen::MatrixXd& coefficientMatrix_;
  const TurbomoleOrbitalsMetaInformation& metaInformation_;
  const unsigned nOrbitals_;

  unsigned currentOrbital_ = 0;
  std::ofstream moFile_;
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_TURBOMOLEORBITALFILEWRITER_H