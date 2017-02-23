#include "ScientificNumberFormatter.h"
#include <iomanip>
#include <sstream>
#include <assert.h>

namespace OrbitalPerturbation {

ScientificNumberFormatter::ScientificNumberFormatter()
  : length_(defaultLength_),
    numberOfDigitsAfterDecimalPoint_(defaultNumberOfDigitsAfterDecimalPoint_),
    exponentSeparator_(defaultSeparator_) {
}

void ScientificNumberFormatter::setLength(int length) {
  assert(length >= 0);
  length_ = length;
}

void ScientificNumberFormatter::setNumberOfDigitsAfterDecimalPoint(int n) {
  assert(n >= 1);
  numberOfDigitsAfterDecimalPoint_ = n;
}

void ScientificNumberFormatter::setExponentSeparator(char c) {
  exponentSeparator_ = c;
}

std::string ScientificNumberFormatter::convert(double number) const {
  assert(length_ - numberOfDigitsAfterDecimalPoint_ >= 7
         && "Length of number not long enough for the number of digits specified.");
  using namespace std;
  std::stringstream ss;
  ss.imbue(std::locale("C"));
  ss << scientific
     << setprecision(numberOfDigitsAfterDecimalPoint_)
     << setw(length_)
     << number;

  std::string numberString = ss.str();
  numberString[numberString.size() - 4] = exponentSeparator_;

  return numberString;
}

} // namespace OrbitalPerturbation
