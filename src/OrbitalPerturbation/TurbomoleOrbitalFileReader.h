#ifndef TURBOMOLEORBITALFILEREADER_H
#define TURBOMOLEORBITALFILEREADER_H

#include "TurbomoleOrbitalsMetaInformation.h"
#include <Eigen/Core>
#include <iostream>
#include <fstream>

namespace Miscellaneous {

/*!
 * Class to read a single Turbomole molecular orbital file (for instance alpha, beta, mo, ...).
 * The contents of the file are then available as a matrix and an instance of TurbomoleOrbitalsMetaInformation.
 */
class TurbomoleOrbitalFileReader {
 public:
  TurbomoleOrbitalFileReader(const std::string& file, unsigned nOrbitals);

  const Eigen::MatrixXd& getCoefficientMatrix() const;
  const TurbomoleOrbitalsMetaInformation& getMetaInformation() const;

 private:
  void openFile(const std::string& file);
  void closeFile();
  void readOrbitals();
  void readOneMolecularOrbital();
  void readHeader();
  void readFooter();

  const unsigned nOrbitals_;
  unsigned currentOrbital_ = 0;
  std::ifstream moFile_;
  Eigen::MatrixXd coefficientMatrix_;
  TurbomoleOrbitalsMetaInformation metaInformation_;
};

} // namespace Miscellaneous

#endif // TURBOMOLEORBITALFILEREADER_H