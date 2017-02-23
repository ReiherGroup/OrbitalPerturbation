#include "GaussianOrbitalFileReader.h"
#include <iostream>

namespace OrbitalPerturbation {

GaussianOrbitalFileReader::GaussianOrbitalFileReader(const std::string& file) {
  openFile(file);
  readOrbitals();
}

void GaussianOrbitalFileReader::openFile(const std::string& file) {
  chkFile_.open(file);
  if (chkFile_.fail() | chkFile_.bad())
    throw std::runtime_error("Could not open" + file);
}

void GaussianOrbitalFileReader::closeFile() {
  chkFile_.close();
}

void GaussianOrbitalFileReader::readOrbitals() {
  std::string line;
  while (std::getline(chkFile_, line)) {
    checkNumberOrbitalsLine(line);
    checkNumberAlphaElectronsLine(line);
    checkNumberBetaElectronsLine(line);
    checkAlphaOrbitals(line);
    checkBetaOrbitals(line);
  }
  createMolecularOrbitals();
}

void GaussianOrbitalFileReader::checkNumberOrbitalsLine(const std::string& line) {
  std::string pattern = "Number of basis functions";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    std::stringstream ss(line.substr(pattern.length()));
    char c; // 'I'
    ss >> c >> nOrbitals_;
  }
}

void GaussianOrbitalFileReader::checkNumberAlphaElectronsLine(const std::string& line) {
  std::string pattern = "Number of alpha electrons";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    std::stringstream ss(line.substr(pattern.length()));
    char c; // 'I'
    ss >> c >> nAlpha_;
  }
}

void GaussianOrbitalFileReader::checkNumberBetaElectronsLine(const std::string& line) {
  std::string pattern = "Number of beta electrons";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    std::stringstream ss(line.substr(pattern.length()));
    char c; // 'I'
    ss >> c >> nBeta_;
  }
}

void GaussianOrbitalFileReader::checkAlphaOrbitals(const std::string& line) {
  std::string pattern = "Alpha MO coefficients";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    fillCoefficients(alphaCoefficients_);
  }
}

void GaussianOrbitalFileReader::checkBetaOrbitals(const std::string& line) {
  std::string pattern = "Beta MO coefficients";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    fillCoefficients(betaCoefficients_);
  }
}

void GaussianOrbitalFileReader::fillCoefficients(std::vector<double>& coefficients) {
  auto numberCoefficients = nOrbitals_ * nOrbitals_;
  unsigned numberValuesPerLine = 5;
  coefficients.resize(numberCoefficients);
  for (unsigned i = 0; i < numberCoefficients; i += numberValuesPerLine) {
    std::string line;
    std::getline(chkFile_, line);
    std::stringstream lineStream(line);
    for (unsigned j = i; j < i + numberValuesPerLine && j < numberCoefficients; ++j) {
      lineStream >> coefficients[j];
    }
  }
}

void GaussianOrbitalFileReader::createMolecularOrbitals() {
  auto numberCoefficients = nOrbitals_ * nOrbitals_;
  bool foundNumberOrbitals = nOrbitals_ != 0;
  bool foundOrbitalCoefficients = alphaCoefficients_.size() == numberCoefficients &&
                                  betaCoefficients_.size() == numberCoefficients;
  if (!(foundNumberOrbitals && foundOrbitalCoefficients)) {
    throw std::runtime_error("Parse unsuccessful");
  }

  Eigen::Map<Eigen::MatrixXd> Ca(alphaCoefficients_.data(), nOrbitals_, nOrbitals_);
  Eigen::Map<Eigen::MatrixXd> Cb(betaCoefficients_.data(), nOrbitals_, nOrbitals_);

  orbitals_ = MolecularOrbitals::createFromUnrestrictedCoefficients(Ca, Cb);
}

unsigned GaussianOrbitalFileReader::getNumberOrbitals() const {
  return nOrbitals_;
}

unsigned GaussianOrbitalFileReader::getNumberAlphaElectrons() const {
  return nAlpha_;
}

unsigned GaussianOrbitalFileReader::getNumberBetaElectrons() const {
  return nBeta_;
}

const MolecularOrbitals& GaussianOrbitalFileReader::getOrbitals() const {
  return orbitals_;
}

} // namespace OrbitalPerturbation