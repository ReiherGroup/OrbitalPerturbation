#ifndef ORBITALPERTURBATION_RANDOMSEED_H
#define ORBITALPERTURBATION_RANDOMSEED_H

#include <string>

namespace OrbitalPerturbation {

class RandomSeed {
 public:
  static void readSeed(const std::string& filename);
  static void writeSeed(const std::string& filename);
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_RANDOMSEED_H