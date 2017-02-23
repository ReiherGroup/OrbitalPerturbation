#include "ScientificNumberFormatter.h"
#include "GaussianOrbitalFileWriter.h"

namespace OrbitalPerturbation {

GaussianOrbitalFileWriter::GaussianOrbitalFileWriter(const MolecularOrbitals& orbitals,
                                                     const std::string& inFile,
                                                     const std::string& outFile)
  : orbitals_(orbitals) {
  openInFile(inFile);
  openOutFile(outFile);
}

void GaussianOrbitalFileWriter::openInFile(const std::string& file) {
  fin_.open(file);
  if (fin_.fail() | fin_.bad())
    throw std::runtime_error("Could not open" + file);
}

void GaussianOrbitalFileWriter::openOutFile(const std::string& file) {
  fout_.open(file);
  if (fout_.fail() | fout_.bad())
    throw std::runtime_error("Could not open" + file);
}

void GaussianOrbitalFileWriter::write() {
  std::string line;
  while (std::getline(fin_, line)) {
    fout_ << line << std::endl;
    checkAlphaOrbitals(line);
    checkBetaOrbitals(line);
  }
}

void GaussianOrbitalFileWriter::checkAlphaOrbitals(const std::string& line) {
  std::string pattern = "Alpha MO coefficients";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    ignoreInputLines();
    writeCoefficients(orbitals_.alphaMatrix());
  }
}

void GaussianOrbitalFileWriter::checkBetaOrbitals(const std::string& line) {
  std::string pattern = "Beta MO coefficients";
  int cmp = line.compare(0, pattern.length(), pattern);
  if (cmp == 0) {
    ignoreInputLines();
    writeCoefficients(orbitals_.betaMatrix());
  }
}

void GaussianOrbitalFileWriter::ignoreInputLines() {
  auto numberCoefficients = orbitals_.numberOrbitals() * orbitals_.numberOrbitals();
  unsigned numberValuesPerLine = 5;
  for (unsigned i = 0; i < numberCoefficients; i += numberValuesPerLine) {
    std::string lineToIgnore;
    std::getline(fin_, lineToIgnore);
  }
}

void GaussianOrbitalFileWriter::writeCoefficients(const Eigen::MatrixXd& c) {
  auto numberCoefficients = orbitals_.numberOrbitals() * orbitals_.numberOrbitals();
  Eigen::Map<const Eigen::VectorXd> data(c.data(), numberCoefficients);
  unsigned numberValuesPerLine = 5;
  ScientificNumberFormatter formatter;
  formatter.setLength(16);
  formatter.setExponentSeparator('E');
  formatter.setNumberOfDigitsAfterDecimalPoint(8);
  for (unsigned i = 0; i < numberCoefficients; i += numberValuesPerLine) {
    for (unsigned j = i; j < i + numberValuesPerLine && j < numberCoefficients; ++j) {
      fout_ << formatter.convert(data[j]);
    }
    fout_ << std::endl;
  }
}

} // namespace OrbitalPerturbation