#include "TurbomoleOrbitalsMetaInformation.h"

namespace OrbitalPerturbation {

void TurbomoleOrbitalsMetaInformation::setHeader(std::string h1, std::string h2, std::string h3) {
  header1_ = std::move(h1);
  header2_ = std::move(h2);
  header3_ = std::move(h3);
}

void TurbomoleOrbitalsMetaInformation::addOrbitalInformation(std::string orbitalInformation) {
  orbitalInformation_.push_back(std::move(orbitalInformation));
}

const std::string& TurbomoleOrbitalsMetaInformation::getFirstHeaderLine() const {
  return header1_;
}

const std::string& TurbomoleOrbitalsMetaInformation::getSecondHeaderLine() const {
  return header2_;
}

const std::string& TurbomoleOrbitalsMetaInformation::getThirdHeaderLine() const {
  return header3_;
}

const std::string& TurbomoleOrbitalsMetaInformation::getFooter() const {
  return footer_;
}

const std::string& TurbomoleOrbitalsMetaInformation::getOrbitalInformation(unsigned index) const {
  return orbitalInformation_[index];
}

void TurbomoleOrbitalsMetaInformation::setFooter(std::string footer) {
  footer_ = std::move(footer);
}

} // namespace OrbitalPerturbation
