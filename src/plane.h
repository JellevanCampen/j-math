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

  Point3D<valuetype> p_;
  Vector3D<valuetype> n_;
};

using Planei = Plane<int>;
using Planef = Plane<float>;
using Planed = Plane<double>;

} // namespace
} // namespace

#endif // J_MATH_PLANE_H_
