#ifndef ORBITALPERTURBATION_TURBOMOLENUMBERSTRINGCONVERTER_H
#define ORBITALPERTURBATION_TURBOMOLENUMBERSTRINGCONVERTER_H

#include <string>

namespace OrbitalPerturbation {

/*!
 * This class converts turbomole-formatted number strings to doubles and inversely.
 * Turbomole-formatted numbers are 20 characters long and indicate scientific notation with a "D".
 * They all are in the form "{-/0}.XXXXXXXXXXXXXXD{+/-}XX".
 * For example:
 * * -.88469659014018D-04
 * * 0.56207535803040D-05
 * * -.21671512754719D-03
 * * 0.12838735639707D+00
 * TODO: improve: highest number supported is now 1e14
 */

class TurbomoleNumberStringConverter {
 public:
  static double toDouble(const std::string& numberString);
  static double toDouble(const char* numberString);

  static std::string toString(double number);

 private:
  static std::string getPrefix(double number);
  static std::string getNumberPart(double number);
  static std::string getExponentPart(int exponent);
};

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_TURBOMOLENUMBERSTRINGCONVERTER_H