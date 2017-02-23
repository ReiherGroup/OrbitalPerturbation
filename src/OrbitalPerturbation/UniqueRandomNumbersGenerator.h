#ifndef ORBITALPERTURBATION_UNIQUERANDOMNUMBERSGENERATOR_H
#define ORBITALPERTURBATION_UNIQUERANDOMNUMBERSGENERATOR_H

#include <random>
#include <vector>
#include <assert.h>

namespace OrbitalPerturbation {

/*
 * Class to generate several unique random numbers from a range of numbers.
 * Applies the Fisher-Yates algorithm.
 */
template<typename IntegerType>
class UniqueRandomNumbersGenerator {
 public:
  void setMin(IntegerType min);
  void setMax(IntegerType max);
  void setRange(IntegerType min, IntegerType max);

  std::vector<IntegerType> generate(unsigned N);
  template<typename Generator>
  std::vector<IntegerType> generate(Generator& generator, unsigned N);

 private:
  void generateArrayOfPossibleNumbers();
  template<typename Generator>
  IntegerType getNextRandomNumber(Generator& generator);

  std::vector<IntegerType> possibleNumbers_;
  IntegerType min_ = 0;
  IntegerType max_ = 0;
  unsigned currentMaxIndex_;
};

template<typename IntegerType>
void UniqueRandomNumbersGenerator<IntegerType>::setMin(IntegerType min) {
  min_ = min;
}

template<typename IntegerType>
void UniqueRandomNumbersGenerator<IntegerType>::setMax(IntegerType max) {
  max_ = max;
}

template<typename IntegerType>
void UniqueRandomNumbersGenerator<IntegerType>::setRange(IntegerType min, IntegerType max) {
  setMin(min);
  setMax(max);
}

template<typename IntegerType>
std::vector<IntegerType> UniqueRandomNumbersGenerator<IntegerType>::generate(unsigned N) {
  std::mt19937 generator;
  return generate(generator, N);
}

template<typename IntegerType>
template<typename Generator>
std::vector<IntegerType> UniqueRandomNumbersGenerator<IntegerType>::generate(Generator& generator, unsigned N) {
  assert(min_ + static_cast<int>(N) < max_ + 2 && "Not enough numbers to select from.");

  generateArrayOfPossibleNumbers();
  currentMaxIndex_ = static_cast<unsigned>(possibleNumbers_.size())-1;

  std::vector<IntegerType> randomNumbers;
  for (unsigned i = 0; i < N; ++i)
    randomNumbers.push_back(getNextRandomNumber(generator));

  return randomNumbers;
}

template<typename IntegerType>
template<typename Generator>
IntegerType UniqueRandomNumbersGenerator<IntegerType>::getNextRandomNumber(Generator& generator) {
  std::uniform_int_distribution<IntegerType> distr(0,currentMaxIndex_);
  int randomIndex = distr(generator);
  IntegerType randomNumber = possibleNumbers_[randomIndex];

  possibleNumbers_[randomIndex] = possibleNumbers_[currentMaxIndex_];
  --currentMaxIndex_;

  return randomNumber;
}

template<typename IntegerType>
void UniqueRandomNumbersGenerator<IntegerType>::generateArrayOfPossibleNumbers() {
  assert(min_ <= max_);
  possibleNumbers_.clear();
  for (IntegerType i = min_; i <= max_; ++i)
    possibleNumbers_.push_back(i);
}

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_UNIQUERANDOMNUMBERSGENERATOR_H