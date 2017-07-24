#pragma once
#ifndef J_MATH_ANALYSIS_INTERPOLATION_H_
#define J_MATH_ANALYSIS_INTERPOLATION_H_

#include <cmath>
#include "sequence.h"

namespace j {
  namespace math {

    // Interpolation of discrete sequences.
    class Interpolation {
      template<typename valuetype> valuetype NearestNeighborInterpolation(const Sequence1D<valuetype>& sequence, const float& x) { return sequence(std::round(x)); }
      template<typename valuetype> valuetype LinearInterpolation(const Sequence1D<valuetype>& sequence, const float& x) {
        size_t x1{ std::floor(x) };
        size_t x2{ x1 + 1.0f };
        valuetype y1{ sequence(x1) };
        valuetype y2{ sequence(x2) };
        return ((x2 - x) * y1) + ((x - x1) * y2);
      }
    };

  } // namespace
} // namespace

#endif // J_MATH_ANALYSIS_INTERPOLATION_H_
