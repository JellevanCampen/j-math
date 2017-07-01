#pragma once
#ifndef J_MATH_SPHERE_H_
#define J_MATH_SPHERE_H_

#include "numeric_comparison.h"
#include "pi.h"
#include "point.h"
#include <cmath>

namespace j {
namespace math {

// A three-dimensional sphere. Represented by a center point and radius.
template<typename valuetype>
struct Sphere {
  // Constructors
  Sphere() : c_{ 0, 0, 0 }, r_{ valuetype(1) } { }
  Sphere(const Sphere&) = default;
  Sphere(Point3D<valuetype> center, valuetype radius) : c_{ center }, r_{ radius } { }
  Sphere(valuetype x, valuetype y, valuetype z, valuetype radius) : c_{ x, y, z }, r_{ radius } { }
  ~Sphere() = default;

  // Operators
  Sphere& operator=(const Sphere&) = default;
  bool operator== (const Sphere<valuetype>& other) const { return (AreEqual(r_, other.r_) && c_ == other.c_); }
  bool operator!= (const Sphere<valuetype>& other) const { return (!AreEqual(r_, other.r_) || c_ != other.c_); }
  Sphere operator+ (const Vector3D<valuetype>& vector) const { return Sphere(c_ + vector, r_); }
  Sphere operator- (const Vector3D<valuetype>& vector) const { return Sphere(c_ - vector, r_); }
  void operator+= (const Vector3D<valuetype>& vector) { c_ += vector; }
  void operator-= (const Vector3D<valuetype>& vector) { c_ -= vector; }
  // TODO: operator(float s, float t)

  // Cast to different valuetype
  template<typename other_valuetype> operator Sphere<other_valuetype>() const { return Sphere<other_valuetype>(other_valuetype(c_), other_valuetype(r_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Sphere<valuetype>& circle) { return os << "Sphere(c=" << circle.c_ << ", r=" << circle.r_ << ")"; }

  // Sphere-specific operations
  valuetype Area() const { return valuetype(r_ * r_ * valuetype(PI)); }
  valuetype EvaluateImplicitEquation(const Point3D<valuetype>& p) const { return( (p - c_).LengthSquared() - (r_ * r_)); }
  bool IsOnSurface(const Point3D<valuetype>& p) const { return AreEqual(EvaluateImplicitEquation(p), valuetype(0)); }
  bool IsInside(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) < 0; }
  bool IsOutside(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) > 0; }
  valuetype SignedDistanceToSurface(const Point3D<valuetype>& p) const { return((p - c_).Length() - r_); }
  valuetype DistanceToSurface(const Point3D<valuetype>& p) const { valuetype d = SignedDistanceToSurface(p); return (d >= 0) ? d : -d; }
  Point3D<valuetype> EvaluateParametricSpecification(valuetype theta, valuetype phi) const { return(c_ + Vector3D<valuetype>(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta), std::cos(theta)) * r_); }
  // TODO: valuetype FindNearestParameterValue(const Point2D<valuetype>& p) const {  }
  Point2D<valuetype> FindNearestPoint(const Point2D<valuetype>& p) const { return (c_ + (p-  c_).Normalize()); }
  Vector3D<valuetype> FindNearestNormal(const Point3D<valuetype>& p) const { return (p - c_).Normalize(); }

  Point3D<valuetype> c_;
  valuetype r_;
};
typedef Sphere<int> Spherei;
typedef Sphere<float> Spheref;
typedef Sphere<double> Sphered;

} // namespace
} // namespace

#endif // J_MATH_SPHERE_H_
