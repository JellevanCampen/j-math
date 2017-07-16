#pragma once
#ifndef J_MATH_VECTOR_H_
#define J_MATH_VECTOR_H_

#include <cmath>
#include "..\utility\numeric_comparison.h"

namespace j {
namespace math {

// A two-dimensional vector. Represents a direction and magnitude in two-dimensional space.
template<typename valuetype>
struct Vector2D {
  // Constructors
  Vector2D(): x_(valuetype(0)), y_(valuetype(0)) { }
  Vector2D(const Vector2D&) = default;
  Vector2D(valuetype x, valuetype y) : x_(x), y_(y) { }
  ~Vector2D() = default;
  static Vector2D Xn() { return Vector2D<valuetype>(1, 0); }
  static Vector2D Yn() { return Vector2D<valuetype>(0, 1); }

  // Operators
  Vector2D& operator=(const Vector2D&) = default;
  bool operator== (const Vector2D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_)); }
  bool operator!= (const Vector2D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_)); }
  const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; default: return x_; }}
  valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; default: return x_; }}
  Vector2D operator+ () const { return Vector2D(*this); }
  Vector2D operator- () const { return Vector2D(-x_, -y_); }
  Vector2D operator+ (const Vector2D& other) const { return Vector2D(x_ + other.x_, y_ + other.y_); }
  Vector2D operator- (const Vector2D& other) const { return Vector2D(x_ - other.x_, y_ - other.y_); }
  Vector2D operator* (valuetype scalar) const { return Vector2D(x_ * scalar, y_ * scalar); }
  valuetype operator* (const Vector2D& other) const { return x_ * other.x_ + y_ * other.y_; }
  Vector2D operator/ (valuetype scalar) const { return Vector2D(x_ / scalar, y_ / scalar); }
  void operator+= (const Vector2D& other) { x_ += other.x_; y_ += other.y_; }
  void operator-= (const Vector2D& other) { x_ -= other.x_; y_ -= other.y_; }
  void operator*= (const valuetype& scalar) { x_ *= scalar; y_ *= scalar; }
  void operator/= (const valuetype& scalar) { x_ /= scalar; y_ /= scalar; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Vector2D<other_valuetype>() const { return Vector2D<other_valuetype>(other_valuetype(x_), other_valuetype(y_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Vector2D& vector) { return os << "Vector2D(" << vector.x_ << ", " << vector.y_ << ")"; }

  // Vector-specific functions
  valuetype ScalarProduct(const Vector2D& other) const { return operator*(other); }
  Vector2D Normal() const { return Vector2D(-y_, x_); }
  bool IsOrthogonal(const Vector2D& other) const { return AreEqual(ScalarProduct(other), valuetype(0)); }
  bool IsCollinear(const Vector2D& other) const { return AreEqual(valuetype(pow(ScalarProduct(other), 2)), (LengthSquared() * other.LengthSquared())); }
  valuetype LengthSquared() const { return ScalarProduct(*this); }
  valuetype Length() const { return valuetype(std::sqrtf(LengthSquared())); }
  Vector2D Normalize() const { return operator/(Length()); }
  bool IsNormalized() const { return AreEqual(Length(), valuetype(1)); }
  Vector2D ProjectOnto(const Vector2D& other) const { return other * (operator*(other) / other.LengthSquared()); }

  // inline Vector2D Reflect(const Vector2D& normal) const { return (*this) - (ProjectOnto(normal) * valuetype(2.0)); }
  // inline Vector2D Rotate(float angle_radians) const { return Vector2D(valuetype(float(x_) * std::cosf(angle_radians) - float(y_) * std::sinf(angle_radians)), valuetype(float(x_) * std::sinf(angle_radians) + float(y_) * std::cosf(angle_radians))); }

  valuetype x_, y_;
};

using vec2i = Vector2D<int>;
using vec2f = Vector2D<float>;
using vec2d = Vector2D<double>;

// A three-dimensional vector. Represents a direction and magnitude in three-dimensional space.
template<typename valuetype>
struct Vector3D {
  // Constructors
  Vector3D() : x_(valuetype(0)), y_(valuetype(0)), z_(valuetype(0)) { }
  Vector3D(const Vector3D&) = default;
  Vector3D(valuetype x, valuetype y, valuetype z) : x_(x), y_(y), z_(z) { }
  ~Vector3D() = default;
  static Vector3D Xn() { return Vector3D<valuetype>(1, 0, 0); }
  static Vector3D Yn() { return Vector3D<valuetype>(0, 1, 0); }
  static Vector3D Zn() { return Vector3D<valuetype>(0, 0, 1); }

  // Operators
  Vector3D& operator=(const Vector3D&) = default;
  bool operator== (const Vector3D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_) && AreEqual(z_, other.z_)); }
  bool operator!= (const Vector3D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_) || !AreEqual(z_, other.z_)); }
  const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; default: return x_; }}
  valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; default: return x_; }}
  Vector3D operator+ () const { return Vector3D(*this); }
  Vector3D operator- () const { return Vector3D(-x_, -y_, -z_); }
  Vector3D operator+ (const Vector3D& other) const { return Vector3D(x_ + other.x_, y_ + other.y_, z_ + other.z_); }
  Vector3D operator- (const Vector3D& other) const { return Vector3D(x_ - other.x_, y_ - other.y_, z_ - other.z_); }
  Vector3D operator* (valuetype scalar) const { return Vector3D(x_ * scalar, y_ * scalar, z_ * scalar); }
  valuetype operator* (const Vector3D& other) const { return x_ * other.x_ + y_ * other.y_ + z_ * other.z_; }
  Vector3D operator/ (valuetype scalar) const { return Vector3D(x_ / scalar, y_ / scalar, z_ / scalar); }
  void operator+= (const Vector3D& other) { x_ += other.x_; y_ += other.y_; z_ += other.z_; }
  void operator-= (const Vector3D& other) { x_ -= other.x_; y_ -= other.y_; z_ -= other.z_; }
  void operator*= (const valuetype& scalar) { x_ *= scalar; y_ *= scalar; z_ *= scalar; }
  void operator/= (const valuetype& scalar) { x_ /= scalar; y_ /= scalar; z_ /= scalar; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Vector3D<other_valuetype>() const { return Vector3D<other_valuetype>(other_valuetype(x_), other_valuetype(y_), other_valuetype(z_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Vector3D& vector) { return os << "Vector3D(" << vector.x_ << ", " << vector.y_ << ", " << vector.z_ << ")"; }

  // Vector-specific functions
  valuetype ScalarProduct(const Vector3D& other) const { return operator*(other); }
  Vector3D CrossProduct(const Vector3D& other) const { return Vector3D(y_ * other.z_ - z_ * other.y_, z_ * other.x_ - x_ * other.z_, x_ * other.y_ - y_ * other.x_); }
  bool IsOrthogonal(const Vector3D& other) const { return AreEqual(ScalarProduct(other), valuetype(0)); }
  bool IsCollinear(const Vector3D& other) const { return AreEqual(valuetype(pow(ScalarProduct(other), 2)), (LengthSquared() * other.LengthSquared())); }
  valuetype LengthSquared() const { return ScalarProduct(*this); }
  valuetype Length() const { return valuetype(std::sqrtf(LengthSquared())); }
  Vector3D Normalize() const { return operator/(Length()); }
  bool IsNormalized() const { return AreEqual(Length(), valuetype(1)); }
  Vector3D Project(const Vector3D& other) const { return other * (operator*(other) / other.LengthSquared()); }

  // inline Vector3D Reflect(const Vector3D& normal) const { return (*this) - (ProjectOnto(normal) * valuetype(2.0)); }
  // inline Vector3D Rotate(float angle_radians) const { return Vector3D(valuetype(float(x_) * std::cosf(angle_radians) - float(y_) * std::sinf(angle_radians)), valuetype(float(x_) * std::sinf(angle_radians) + float(y_) * std::cosf(angle_radians))); }

  valuetype x_, y_, z_;
};

using vec3i = Vector3D<int>;
using vec3f = Vector3D<float>;
using vec3d = Vector3D<double>;

} // namespace
} // namespace

#endif // J_MATH_VECTOR_H_