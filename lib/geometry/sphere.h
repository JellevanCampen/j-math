#pragma once
#ifndef J_MATH_SPHERE_H_
#define J_MATH_SPHERE_H_

#include "..\utility\numeric_comparison.h"
#include "..\utility\pi.h"
#include "point.h"
#include <cmath>

namespace j {
namespace math {

// A two-dimensional circle. Represented by a center point and radius.
template<typename valuetype>
struct Circle {
  // Constructors
  Circle() : c_{ 0, 0 }, r_{ valuetype(1) } { }
  Circle(const Circle&) = default;
  Circle(Point2D<valuetype> center, valuetype radius) : c_{ center }, r_{ radius } { }
  Circle(valuetype x, valuetype y, valuetype radius) : c_{ x, y }, r_{ radius } { }
  ~Circle() = default;

  // Operators
  Circle& operator=(const Circle&) = default;
  bool operator== (const Circle<valuetype>& other) const { return (AreEqual(r_, other.r_) && c_ == other.c_); }
  bool operator!= (const Circle<valuetype>& other) const { return (!AreEqual(r_, other.r_) || c_ != other.c_); }
  Circle operator+ (const Vector2D<valuetype>& vector) const { return Circle(c_ + vector, r_); }
  Circle operator- (const Vector2D<valuetype>& vector) const { return Circle(c_ - vector, r_); }
  void operator+= (const Vector2D<valuetype>& vector) { c_ += vector; }
  void operator-= (const Vector2D<valuetype>& vector) { c_ -= vector; }
  Point2D<valuetype> operator()(valuetype theta) const { return GetPoint(theta); }

  // Cast to different valuetype
  template<typename other_valuetype> operator Circle<other_valuetype>() const { return Circle<other_valuetype>(other_valuetype(c_), other_valuetype(r_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Circle<valuetype>& circle) { return os << "Circle(c=" << circle.c_ << ", r=" << circle.r_ << ")"; }

  // Circle-specific operations
  valuetype Area() const { return valuetype(r_ * r_ * valuetype(PI)); }
  valuetype EvaluateImplicitEquation(const Point2D<valuetype>& p) const { return((p - c_).LengthSquared() - (r_ * r_)); }
  bool IsOnCurve(const Point2D<valuetype>& p) const { return AreEqual(EvaluateImplicitEquation(p), valuetype(0)); }
  bool IsInside(const Point2D<valuetype>& p) const { return EvaluateImplicitEquation(p) < 0; }
  bool IsOutside(const Point2D<valuetype>& p) const { return EvaluateImplicitEquation(p) > 0; }
  valuetype SignedDistanceToSurface(const Point3D<valuetype>& p) const { return((p - c_).Length() - r_); }
  valuetype DistanceToSurface(const Point3D<valuetype>& p) const { valuetype d = SignedDistanceToSurface(p); return (d >= 0) ? d : -d; }
  Point2D<valuetype> EvaluateParametricSpecification(valuetype theta) const { return(c_ + Vector2D<valuetype>(std::cos(theta) * r_, std::sin(theta) * r_)); }
  // valuetype FindNearestParameterValue(const Point2D<valuetype>& p) const { Vector2D<valuetype> p_c = c_ - p; return valuetype(std::atan2(p_c.x_, p_c.y_)); }
  Point2D<valuetype> FindNearestPoint(const Point2D<valuetype>& p) const { return (c_ + (p - c_).Normalize() * r_); }
  Vector2D<valuetype> FindNearestNormal(const Point2D<valuetype>& p) const { return (p - c_).Normalize(); }

  Point2D<valuetype> c_;
  valuetype r_;
};
typedef Circle<int> Circlei;
typedef Circle<float> Circlef;
typedef Circle<double> Circled;

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
  Point3D<valuetype> operator()(valuetype theta, valuetype phi) const { return GetPoint(theta, phi); }

  // Cast to different valuetype
  template<typename other_valuetype> operator Sphere<other_valuetype>() const { return Sphere<other_valuetype>(other_valuetype(c_), other_valuetype(r_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Sphere<valuetype>& circle) { return os << "Sphere(c=" << circle.c_ << ", r=" << circle.r_ << ")"; }

  // Sphere-specific operations
  valuetype Area() const { return valuetype(4.0 * r_ * r_ * valuetype(PI)); }
  valuetype Volume() const { return valuetype((4.0 / 3.0) * r_ * r_ * r_ * valuetype(PI)); }
  valuetype EvaluateImplicitEquation(const Point3D<valuetype>& p) const { return( (p - c_).LengthSquared() - (r_ * r_)); }
  bool IsOnSurface(const Point3D<valuetype>& p) const { return AreEqual(EvaluateImplicitEquation(p), valuetype(0)); }
  bool IsInside(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) < 0; }
  bool IsOutside(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) > 0; }
  valuetype SignedDistanceToSurface(const Point3D<valuetype>& p) const { return((p - c_).Length() - r_); }
  valuetype DistanceToSurface(const Point3D<valuetype>& p) const { valuetype d = SignedDistanceToSurface(p); return (d >= 0) ? d : -d; }
  Point3D<valuetype> EvaluateParametricSpecification(valuetype theta, valuetype phi) const { return(c_ + Vector3D<valuetype>(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta), std::cos(theta)) * r_); }
  // TODO: valuetype FindNearestParameterValue(const Point2D<valuetype>& p) const {  }
  Point2D<valuetype> FindNearestPoint(const Point2D<valuetype>& p) const { return (c_ + (p-  c_).Normalize() * r_); }
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
