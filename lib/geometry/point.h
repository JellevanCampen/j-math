#pragma once
#ifndef J_MATH_POINT_H_
#define J_MATH_POINT_H_

#include "..\utility\numeric_comparison.h"
#include "vector.h"

namespace j {
namespace math {

// A point in two-dimensional space. Represents a position.
template<typename valuetype>
struct Point2D {
  // Constructors
  Point2D() : x_(valuetype(0)), y_(valuetype(0)) { }
  Point2D(const Point2D&) = default;
  Point2D(valuetype x, valuetype y) : x_(x), y_(y) { }
  ~Point2D() = default;

  // Operators
  Point2D& operator=(const Point2D&) = default;
  bool operator== (const Point2D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_)); }
  bool operator!= (const Point2D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_)); }
  const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; default: return x_; } }
  valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; default: return x_; } }
  Point2D operator+ (const Vector2D<valuetype>& vector) const { return Point2D(x_ + vector.x_, y_ + vector.y_); }
  Point2D operator- (const Vector2D<valuetype>& vector) const { return Point2D(x_ - vector.x_, y_ - vector.y_); }
  Vector2D<valuetype> operator- (const Point2D<valuetype>& other) const { return Vector2D<valuetype>(other.x_ - x_, other.y_ - y_); }
  void operator+= (const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
  void operator-= (const Vector2D<valuetype>& vector) { x_ -= vector.x_; y_ -= vector.y_; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Point2D<other_valuetype>() const { return Point2D<other_valuetype>(other_valuetype(x_), other_valuetype(y_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Point2D& point) { return os << "Point2D(" << point.x_ << ", " << point.y_ << ")"; }

  // Point-specific functions
  float Distance(const Point2D& other) const { return operator-(other).Length(); }

  valuetype x_, y_;
};
typedef Point2D<int> Point2Di, p2i;
typedef Point2D<float> Point2Df, p2f;
typedef Point2D<double> Point2Dd, p2d;

// A point in three-dimensional space. Represents a position.
template<typename valuetype>
struct Point3D {
    // Constructors
  Point3D() : x_(valuetype(0)), y_(valuetype(0)), z_(valuetype(0)) { }
  Point3D(const Point3D&) = default;
  Point3D(valuetype x, valuetype y, valuetype z) : x_(x), y_(y), z_(z) { }
  ~Point3D() = default;

  // Operators
  Point3D& operator=(const Point3D&) = default;
  bool operator== (const Point3D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_) && AreEqual(z_, other.z_)); }
  bool operator!= (const Point3D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_) || !AreEqual(z_, other.z_)); }
  const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; default: return x_; } }
  valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; default: return x_; } }
  Point3D operator+ (const Vector3D<valuetype>& vector) const { return Point3D(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_); }
  Point3D operator- (const Vector3D<valuetype>& vector) const { return Point3D(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_); }
  Vector3D<valuetype> operator- (const Point3D<valuetype>& other) const {
    Vector3D<valuetype> temp(other.x_ - x_, other.y_ - y_, other.z_ - z_);
    return Vector3D<valuetype>(other.x_ - x_, other.y_ - y_, other.z_ - z_);
  }
  void operator+= (const Vector3D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; z_ += vector.z_; }
  void operator-= (const Vector3D<valuetype>& vector) { x_ -= vector.x_; y_ -= vector.y_; z_ -= vector.z_; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Point3D<other_valuetype>() const { return Point3D<other_valuetype>(other_valuetype(x_), other_valuetype(y_), other_valuetype(z_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Point3D& point) { return os << "Point3D(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")"; }

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