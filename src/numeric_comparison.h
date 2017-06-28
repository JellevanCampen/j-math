#pragma once
#ifndef J_MATH_NUMERICCOMPARISON_H_
#define J_MATH_NUMERICCOMPARISON_H_

#include <climits>
#include <cmath>

namespace j {
namespace math {

// Test whether two float values are equal based on an error margin
template<typename T>
static bool AreEqual(T f1, T f2) { 
  return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(fabs(f1), fabs(f2)));
}

// Use exact equality testing for integers
template<> static bool inline AreEqual<char>(char c1, char c2) { return c1 == c2; }
template<> static bool inline AreEqual<signed char>(signed char c1, signed char c2) { return c1 == c2; }
template<> static bool inline AreEqual<unsigned char>(unsigned char c1, unsigned char c2) { return c1 == c2; }
template<> static bool inline AreEqual<signed short int>(signed short int i1, signed short int i2) { return i1 == i2; }
template<> static bool inline AreEqual<unsigned short int>(unsigned short int i1, unsigned short int i2) { return i1 == i2; }
template<> static bool inline AreEqual<signed int>(signed int i1, signed int i2) { return i1 == i2; }
template<> static bool inline AreEqual<unsigned int>(unsigned int i1, unsigned int i2) { return i1 == i2; }
template<> static bool inline AreEqual<signed long int>(signed long int i1, signed long int i2) { return i1 == i2; }
template<> static bool inline AreEqual<unsigned long int>(unsigned long int i1, unsigned long int i2) { return i1 == i2; }
template<> static bool inline AreEqual<signed long long int>(signed long long int i1, signed long long int i2) { return i1 == i2; }
template<> static bool inline AreEqual<unsigned long long int>(unsigned long long int i1, unsigned long long int i2) { return i1 == i2; }


} // namespace
} // namespace

#endif // J_MATH_FLOATCOMPARISON_H_