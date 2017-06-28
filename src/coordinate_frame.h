#pragma once
#ifndef J_MATH_COORDINATEFRAME_H_
#define J_MATH_COORDINATEFRAME_H_

#include <iostream>
#include "vector.h"
#include "point.h"

namespace j {
namespace math {

// A coordinate frame in three-dimensional space. Defined by an origin point (p) and three base vectors (u, v, w).  
template<typename valuetype>
struct CoordinateFrame3D {
public:
  // Constructors
  CoordinateFrame3D(const CoordinateFrame3D&) = default;
  CoordinateFrame3D(Point3D<valuetype> p, Vector3D<valuetype> u, Vector3D<valuetype> v, Vector3D<valuetype> w) : p_(p), u_(u), v_(v), w_(w) { }
  ~CoordinateFrame3D() = default;
  static CoordinateFrame3D CarthesianCanonicalOrthonormal() { return CoordinateFrame3D(Point3D<valuetype>(0, 0, 0), Vector3D<valuetype>(1, 0, 0), Vector3D<valuetype>(0, 1, 0), Vector3D<valuetype>(0, 0, 1)); }
  static CoordinateFrame3D FromOneVector(Point3D<valuetype> p, Vector3D<valuetype> a) {
    Vector3D<valuetype> w = a.Normalize();
    Vector3D<valuetype> t(w);
    int i_smallest = 0;
    valuetype smallest = std::fabs(t.x_);
    if (std::fabs(t.y_) < smallest) { i_smallest = 1; smallest = std::fabs(t.y_); }
    if (std::fabs(t.z_) < smallest) { i_smallest = 2; smallest = std::fabs(t.z_); }
    t[i_smallest] = AreEqual(t[i_smallest], valuetype(1)) ? valuetype(2) : valuetype(1);
    Vector3D<valuetype> u = t.CrossProduct(w).Normalize();
    Vector3D<valuetype> v = w.CrossProduct(u);
    return CoordinateFrame3D(p, u, v, w);
  }
  static CoordinateFrame3D FromTwoVectors(Point3D<valuetype> p, Vector3D<valuetype> a, Vector3D<valuetype> b) {
    if (a.IsCollinear(b)) { return FromOneVector(a); }
    Vector3D<valuetype> w = a.Normalize();
    Vector3D<valuetype> u = b.CrossProduct(w).Normalize();
    Vector3D<valuetype> v = w.CrossProduct(u);
    return CoordinateFrame3D(p, u, v, w);
  }

  // Operators
  CoordinateFrame3D::operator=(const CoordinateFrame3D&) = default;
  inline bool operator== (const CoordinateFrame3D& other) const { return (p_ == other.p_ && u_ == other.u_ && v_ == other.v_ && w_ == other.w_); }
  inline bool operator!= (const CoordinateFrame3D& other) const { return (p_ != other.p_ || u_ != other.u_ || v_ != other.v_ || w_ != other.w_); }

  // Cast to different valuetype
  template<typename other_valuetype> operator CoordinateFrame3D<other_valuetype>() const { return CoordinateFrame3D<other_valuetype>(other_valuetype(p_), other_valuetype(u_), other_valuetype(v_), other_valuetype(w_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const CoordinateFrame3D& cf) { return os << "frame(" << cf.p_ << ", " << cf.u_ << ", " << cf.v_ << ", " << cf.w_ << ")"; }

  // Coordinate frame specific functions
  inline bool IsOrthonormal() const { return (u_.IsNormalized() && v_.IsNormalized() && w_.IsNormalized() && u_.IsOrthogonal(v_) && v_.IsOrthogonal(w_) && w_.IsOrthogonal(u_)); }
  inline bool IsRightHandedOrthonormal() const { return (IsOrthonormal() && u_.CrossProduct(v_) == w_); }
  inline void Reorthonormalize() { CoordinateFrame3D cf = FromTwoVectors(p_, w_, v_); operator=(cf); }
  inline Vector3D CoordinateFrameToCanonicalCoordinates(const Vector3D& vector) const { return (vector.x_ * u_) + (vector.y_ * v_) + (vector.z_ * w_); }
  inline Vector3D CanonicalCoordinatesToCoordinateFrame(const Vector3D& vector) const { return Vector3D(u_ * vector, v_ * vector, w_ * vector); }

  Point3D<valuetype> p_;
  Vector3D<valuetype> u_, v_, w_;
};
typedef CoordinateFrame3D<int> cf3i;
typedef CoordinateFrame3D<float> cf3f;
typedef CoordinateFrame3D<double> cf3d;

} // namespace
} // namespace

#endif // J_MATH_COORDINATEFRAME_H_