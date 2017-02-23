#ifndef ORBITALPERTURBATION_GAUSSIANORBITALFILEREADER_H
#define ORBITALPERTURBATION_GAUSSIANORBITALFILEREADER_H

#include "MolecularOrbitals.h"
#include <fstream>
#include <vector>

namespace OrbitalPerturbation {

/*!
 * Class to read a formatted Gaussian checkpoint file and extract the orbitals
 */
class GaussianOrbitalFileReader {
 public:
  GaussianOrbitalFileReader(const std::string& file);

  unsigned getNumberOrbitals() const;
  unsigned getNumberAlphaElectrons() const;
  unsigned getNumberBetaElectrons() const;
  const MolecularOrbitals& getOrbitals() const;

 private:
  void openFile(const std::string& file);
  void closeFile();
  void readOrbitals();
  void checkNumberOrbitalsLine(const std::string& line);
  void checkNumberAlphaElectronsLine(const std::string& line);
  void checkNumberBetaElectronsLine(const std::string& line);
  void checkAlphaOrbitals(const std::string& line);
  void checkBetaOrbitals(const std::string& line);
  void fillCoefficients(std::vector<double>& coefficients);
  void createMolecularOrbitals();

  std::ifstream chkFile_;
  MolecularOrbitals orbitals_;
  unsigned nOrbitals_ = 0;
  unsigned nAlpha_ = 0;
  unsigned nBeta_ = 0;
  std::vector<double> alphaCoefficients_;
  std::vector<double> betaCoefficients_;
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_GAUSSIANORBITALFILEREADER_H