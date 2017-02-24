#include "RandomSeed.h"
#include "RandomOrbitalMixer.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace OrbitalPerturbation {

void RandomSeed::readSeed(const std::string& filename) {
  ifstream seedFile;
  seedFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    seedFile.open(filename);
    unsigned long seed;
    seedFile >> seed;
    OrbitalPerturbation::RandomOrbitalMixer::getRandomNumberGenerator().seed(seed);
  }
  catch (...) {
    cout << "The seed file does not exist." << endl;
  }
}

void RandomSeed::writeSeed(const std::string& filename) {
  ofstream seedFile;
  seedFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    seedFile.open(filename);
    seedFile << OrbitalPerturbation::RandomOrbitalMixer::getRandomNumberGenerator()();
  }
  catch (...) {
    cout << "Error when writing the seed file" << endl;
  }
}

} // namespace OrbitalPerturbation
