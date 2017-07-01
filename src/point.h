#pragma once
#ifndef J_MATH_POINT_H_
#define J_MATH_POINT_H_

#include <iostream>
#include "numeric_comparison.h"
#include "vector.h"

namespace j {
namespace math {

// A point in two-dimensional space. Represents a position.
template<typename valuetype>
struct Point2D {
public:
  // Constructors
  Point2D() { }
  Point2D(const Point2D&) = default;
  Point2D(valuetype x, valuetype y) : x_(x), y_(y) { }
  ~Point2D() = default;

  // Operators
  Point2D& operator=(const Point2D&) = default;
  bool operator== (const Point2D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_)); }
  bool operator!= (const Point2D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_)); }
  Point2D operator+ (const Vector2D<valuetype>& vector) const { return Point2D(x_ + vector.x_, y_ + vector.y_); }
  Point2D operator- (const Vector2D<valuetype>& vector) const { return Point2D(x_ - vector.x_, y_ - vector.y_); }
  Vector2D<valuetype> operator- (const Point2D<valuetype>& other) const { return Vector2D<valuetype>(other.x_ - x_, other.y_ - y_); }
  void operator+= (const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
  void operator-= (const Vector2D<valuetype>& vector) { x_ -= vector.x_; y_ -= vector.y_; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Point2D<other_valuetype>() const { return Point2D<other_valuetype>(other_valuetype(x_), other_valuetype(y_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Point2D& point) { return os << "p(" << point.x_ << ", " << point.y_ << ")"; }

  // Point-specific functions
  float Distance(const Point2D& other) const { return operator-(other).Length(); }

  valuetype x_, y_;
};
typedef Point2D<int> Point2Di, p2Di;
typedef Point2D<float> Point2Df, p2Df;
typedef Point2D<double> Point2Dd, p2Dd;

// A point in three-dimensional space. Represents a position.
template<typename valuetype>
struct Point3D {
public:
    // Constructors
  Point3D() { }
  Point3D(const Point3D&) = default;
  Point3D(valuetype x, valuetype y, valuetype z) : x_(x), y_(y), z_(z) { }
  ~Point3D() = default;

  // Operators
  Point3D& operator=(const Point3D&) = default;
  bool operator== (const Point3D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_) && AreEqual(z_, other.z_)); }
  bool operator!= (const Point3D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_) || !AreEqual(z_, other.z_)); }
  Point3D operator+ (const Vector3D<valuetype>& vector) const { return Point3D(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_); }
  Point3D operator- (const Vector3D<valuetype>& vector) const { return Point3D(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_); }
  Vector3D<valuetype> operator- (const Point3D<valuetype>& other) const { return Vector3D<valuetype>(other.x_ - x_, other.y_ - y_, other.z_ - z_); }
  void operator+= (const Vector3D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; z_ += vector.z_; }
  void operator-= (const Vector3D<valuetype>& vector) { x_ -= vector.x_; y_ -= vector.y_; z_ -= vector.z_; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Point3D<other_valuetype>() const { return Point3D<other_valuetype>(other_valuetype(x_), other_valuetype(y_), other_valuetype(z_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Point3D& point) { return os << "p(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")"; }

  // Point-specific functions
  float Distance(const Point3D& other) const { return operator-(other).Length(); }

  valuetype x_, y_, z_;
};
typedef Point3D<int> p3i;
typedef Point3D<float> p3f;
typedef Point3D<double> p3d;

} // namespace
} // namespace

#endif // J_MATH_POINT_H_