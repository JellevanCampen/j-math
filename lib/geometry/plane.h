#pragma once
#ifndef J_MATH_PLANE_H_
#define J_MATH_PLANE_H_

#include "point.h"
#include "vector.h"

namespace j {
namespace math {

// A three-dimensional plane. Represented by a contained point and a normal vector.
template<typename valuetype>
struct Plane {
  // Constructors
  Plane() : p_{ 0, 0, 0 }, n_{ 0, 0, 1 } { }
  Plane(const Plane&) = default;
  Plane(Point3D<valuetype> p, Vector3D<valuetype> n) : p_{ p }, n_{ n.Normalize() } { }
  ~Plane() = default;
  static Plane FromPointAndTwoVectors(Point3D<valuetype> p, Vector3D<valuetype> v1, Vector3D<valuetype> v2) {
    if (!v1.IsCollinear(v2)) { return Plane<valuetype>(p, v1.CrossProduct(v2)); }
    Vector3D<valuetype> v2_alt = (!Vector3D<valuetype>::Xn().IsCollinear(v1)) ? Vector3D<valuetype>::Xn() : Vector3D<valuetype>::Yn();
    return Plane<valuetype>(p, v1.CrossProduct(v2_alt).Normalize());
  }
  static Plane FromThreePoints(Point3D<valuetype> a, Point3D<valuetype> b, Point3D<valuetype> c) {
    return FromPointAndTwoVectors(a, a - b ,a - c);
  }

  // Operators
  Plane& operator=(const Plane& other) = default;
  bool operator==(const Plane<valuetype>& other) const { return(n_ == other.n_ && Contains(other.p_)); }
  bool operator!=(const Plane<valuetype>& other) const { return(n_ != other.n_ || !Contains(other.p_)); }
  Plane operator+(const Vector3D<valuetype>& vector) const { return Plane(p_ + vector, n_); }
  Plane operator-(const Vector3D<valuetype>& vector) const { return Plane(p_ - vector, n_); }
  void operator+=(const Vector3D<valuetype>& vector) { p_ += vector; }
  void operator-=(const Vector3D<valuetype>& vector) { p_ -= vector; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Plane<other_valuetype>() const { return Plane<other_valuetype>(other_valuetype(p_), other_valuetype(n_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Plane<valuetype>& plane) { return os << "Plane(p=" << plane.p_ << ", n=" << plane.n_ << ")"; }

  // Plane-specific operations
  Vector2D<valuetype> Normal() const { return n_; }
  void SetNormal(const Vector3D<valuetype>& v) { n_ = n_.Normalize(); }
  valuetype EvaluateImplicitEquation(const Point3D<valuetype>& p) const { return((p - p_).ScalarProduct(n_)); }
  bool IsOnSurface(const Point3D<valuetype>& p) const { return AreEqual(EvaluateImplicitEquation(p), valuetype(0)); }
  bool IsBelowPlane(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) < 0; }
  bool IsAbovePlane(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p) > 0; }
  valuetype SignedDistanceToSurface(const Point3D<valuetype>& p) const { return EvaluateImplicitEquation(p); }
  valuetype DistanceToSurface(const Point3D<valuetype>& p) const { valuetype d = SignedDistanceToCurve(p); return (d >= 0) ? d : -d; }
  Point2D<valuetype> EvaluateParametricSpecification(valuetype s) const { return(p_ + (v_ * s)); }
  Point3D<valuetype> FindNearestPoint(const Point3D<valuetype>& p) const { return(p - (p - p_).ScalarProduct(n_)); }

  Point3D<valuetype> p_;
private:
  Vector3D<valuetype> n_;
};

using Planei = Plane<int>;
using Planef = Plane<float>;
using Planed = Plane<double>;

} // namespace
} // namespace

#endif // J_MATH_PLANE_H_
