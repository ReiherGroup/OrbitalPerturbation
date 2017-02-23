#ifndef ORBITALPERTURBATION_SEEDIO_H
#define ORBITALPERTURBATION_SEEDIO_H

#include <string>

namespace OrbitalPerturbation {

void readSeed(const std::string& filename);
void writeSeed(const std::string& filename);

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_SEEDIO_H