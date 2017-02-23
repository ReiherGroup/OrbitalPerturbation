#ifndef SCIENTIFICNUMBERFORMATTER_H
#define SCIENTIFICNUMBERFORMATTER_H

#include <string>

/*!
 * This class converts a double to a string in scientific notation.
 * It follows the following format:
 * - zero or more empty characters used to pad to the total length (which is 20 by default)
 * - 1 char for the sign (' ' or '-')
 * - 1 char for the digit before the dot
 * - 1 char for the dot
 * - a given number of char's for the digits after the dot (default: 13)
 * - 1 char for the exponent separator (by default, 'e')
 * - 3 chars for the exponent with the sign
 */
class ScientificNumberFormatter {
 public:
  explicit ScientificNumberFormatter();
  std::string convert(double number) const;

  void setLength(int length);
  void setNumberOfDigitsAfterDecimalPoint(int n);
  void setExponentSeparator(char c);

  static int defaultLength();
  static char defaultExponentSeparator();
  static int defaultNumberOfDigitsAfterDecimalPoint();

 private:
  static const int defaultLength_ = 20;
  static const char defaultSeparator_ = 'e';
  static const int defaultNumberOfDigitsAfterDecimalPoint_ = 13;

  int length_;
  int numberOfDigitsAfterDecimalPoint_;
  char exponentSeparator_;
};

inline int ScientificNumberFormatter::defaultLength() {
  return defaultLength_;
}

inline char ScientificNumberFormatter::defaultExponentSeparator() {
  return defaultSeparator_;
}

inline int ScientificNumberFormatter::defaultNumberOfDigitsAfterDecimalPoint() {
  return defaultNumberOfDigitsAfterDecimalPoint_;
}

#endif // SCIENTIFICNUMBERFORMATTER_H