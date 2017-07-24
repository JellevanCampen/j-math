#pragma once
#ifndef J_MATH_PI_H_
#define J_MATH_PI_H_

namespace j {
namespace math {

// Clip a variable value between a lower and upper limit
template<typename T>
static float clamp(T i, T lower, T upper) {
  return (i < upper ? i : upper) > lower ? (i < upper ? i : upper) : lower;
}

} // namespace
} // namespace

#endif // J_MATH_PI_H_