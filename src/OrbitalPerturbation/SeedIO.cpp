#include "SeedIO.h"
#include "RandomOrbitalMixer.h"
#include <fstream>
#include <iostream>

using namespace std;

void readSeed(const std::string& filename) {
  ifstream seedFile;
  seedFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    seedFile.open(filename);
    seedFile >> MultipleScfSolutions::RandomOrbitalMixer::getRandomNumberGenerator();
  }
  catch (...) {
    cout << "The seed file does not exist." << endl;
  }
}

void writeSeed(const std::string& filename) {
  ofstream seedFile;
  seedFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    seedFile.open(filename);
    seedFile << MultipleScfSolutions::RandomOrbitalMixer::getRandomNumberGenerator();
  }
  catch (...) {
    cout << "Error when writing the seed file" << endl;
  }
}

