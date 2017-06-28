#pragma once
#ifndef J_MATH_VECTOR_H_
#define J_MATH_VECTOR_H_

#include <cmath>
#include <iostream>
#include "numeric_comparison.h" 

namespace j {
namespace math {

// A two-dimensional vector. Represents a direction and magnitude in two-dimensional space. 
template<typename valuetype>
struct Vector2D {
public:
  // Constructors
  Vector2D(): x_(valuetype(0)), y_(valuetype(0)) { }
  Vector2D(const Vector2D&) = default;
  Vector2D(valuetype x, valuetype y) : x_(x), y_(y) { }
  ~Vector2D() = default;

  // Operators
  inline Vector2D& operator=(const Vector2D&) = default;
  inline bool operator== (const Vector2D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_)); }
  inline bool operator!= (const Vector2D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_)); }
  inline const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; } return x_; }
  inline valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; } return x_; }
  inline Vector2D operator+ () const { return Vector2D(*this); }
  inline Vector2D operator- () const { return Vector2D(-x_, -y_); }
  inline Vector2D operator+ (const Vector2D& other) const { return Vector2D(x_ + other.x_, y_ + other.y_); }
  inline Vector2D operator- (const Vector2D& other) const { return Vector2D(x_ - other.x_, y_ - other.y_); }
  inline Vector2D operator* (valuetype scalar) const { return Vector2D(x_ * scalar, y_ * scalar); }
  inline valuetype operator* (const Vector2D& other) const { return x_ * other.x_ + y_ * other.y_; }
  inline Vector2D operator/ (valuetype scalar) const { return Vector2D(x_ / scalar, y_ / scalar); }
  inline void operator+= (const Vector2D& other) { x_ += other.x_; y_ += other.y_; }
  inline void operator-= (const Vector2D& other) { x_ -= other.x_; y_ -= other.y_; }
  inline void operator*= (const valuetype& scalar) { x_ *= scalar; y_ *= scalar; }
  inline void operator/= (const valuetype& scalar) { x_ /= scalar; y_ /= scalar; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Vector2D<other_valuetype>() const { return Vector2D<other_valuetype>(other_valuetype(x_), other_valuetype(y_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Vector2D& vector) { return os << "v(" << vector.x_ << ", " << vector.y_ << ")"; }

  // Vector-specific functions
  inline valuetype ScalarProduct(const Vector2D& other) const { return operator*(other); }
  inline Vector2D Normal() const { return Vector2D(-y_, x_); }
  inline bool IsOrthogonal(const Vector2D& other) const { return AreEqual(ScalarProduct(other), valuetype(0)); }
  inline bool IsCollinear(const Vector2D& other) const { return AreEqual(valuetype(pow(ScalarProduct(other), 2)), (LengthSquared() * other.LengthSquared())); }
  inline valuetype LengthSquared() const { return ScalarProduct(*this); }
  inline valuetype Length() const { return valuetype(std::sqrtf(LengthSquared())); }
  inline Vector2D Normalize() const { return operator/(Length()); }
  inline bool IsNormalized() const { return AreEqual(Length(), valuetype(1)); }
  inline Vector2D Project(const Vector2D& other) const { return other * (operator*(other) / other.LengthSquared()); }
  
  // inline Vector2D Reflect(const Vector2D& normal) const { return (*this) - (Project(normal) * valuetype(2.0)); }
  // inline Vector2D Rotate(float angle_radians) const { return Vector2D(valuetype(float(x_) * std::cosf(angle_radians) - float(y_) * std::sinf(angle_radians)), valuetype(float(x_) * std::sinf(angle_radians) + float(y_) * std::cosf(angle_radians))); }

  valuetype x_, y_;
};
typedef Vector2D<int> vec2i;
typedef Vector2D<float> vec2f;
typedef Vector2D<double> vec2d;

// A three-dimensional vector. Represents a direction and magnitude in three-dimensional space. 
template<typename valuetype>
struct Vector3D {
public:
  // Constructors
  Vector3D() : x_(valuetype(0)), y_(valuetype(0)), z_(valuetype(0)) { }
  Vector3D(const Vector3D&) = default;
  Vector3D(valuetype x, valuetype y, valuetype z) : x_(x), y_(y), z_(z) { }
  ~Vector3D() = default;

  // Operators
  inline Vector3D& operator=(const Vector3D&) = default;
  inline bool operator== (const Vector3D& other) const { return (AreEqual(x_, other.x_) && AreEqual(y_, other.y_) && AreEqual(z_, other.z_)); }
  inline bool operator!= (const Vector3D& other) const { return (!AreEqual(x_, other.x_) || !AreEqual(y_, other.y_) || !AreEqual(z_, other.z_)); }
  inline const valuetype& operator[](const int& i) const { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; } return x_; }
  inline valuetype& operator[](const int& i) { switch (i) { case 0: return x_; case 1: return y_; case 2: return z_; } return x_; }
  inline Vector3D operator+ () const { return Vector3D(*this); }
  inline Vector3D operator- () const { return Vector3D(-x_, -y_, -z_); }
  inline Vector3D operator+ (const Vector3D& other) const { return Vector3D(x_ + other.x_, y_ + other.y_, z_ + other.z_); }
  inline Vector3D operator- (const Vector3D& other) const { return Vector3D(x_ - other.x_, y_ - other.y_, z_ - other.z_); }
  inline Vector3D operator* (valuetype scalar) const { return Vector3D(x_ * scalar, y_ * scalar, z_ * scalar); }
  inline valuetype operator* (const Vector3D& other) const { return x_ * other.x_ + y_ * other.y_ + z_ * other.z_; }
  inline Vector3D operator/ (valuetype scalar) const { return Vector3D(x_ / scalar, y_ / scalar, z_ / scalar); }
  inline void operator+= (const Vector3D& other) { x_ += other.x_; y_ += other.y_; z_ += other.z_; }
  inline void operator-= (const Vector3D& other) { x_ -= other.x_; y_ -= other.y_; z_ -= other.z_; }
  inline void operator*= (const valuetype& scalar) { x_ *= scalar; y_ *= scalar; z_ *= scalar; }
  inline void operator/= (const valuetype& scalar) { x_ /= scalar; y_ /= scalar; z_ /= scalar; }

  // Cast to different valuetype
  template<typename other_valuetype> operator Vector3D<other_valuetype>() const { return Vector3D<other_valuetype>(other_valuetype(x_), other_valuetype(y_), other_valuetype(z_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Vector3D& vector) { return os << "v(" << vector.x_ << ", " << vector.y_ << ", " << vector.z_ << ")"; }

  // Vector-specific functions
  inline valuetype ScalarProduct(const Vector3D& other) const { return operator*(other); }
  inline Vector3D CrossProduct(const Vector3D& other) const { return Vector3D(y_ * other.z_ - z_ * other.y_, z_ * other.x_ - x_ * other.z_, x_ * other.y_ - y_ * other.x_); }
  inline bool IsOrthogonal(const Vector3D& other) const { return AreEqual(ScalarProduct(other), valuetype(0)); }
  inline bool IsCollinear(const Vector2D& other) const { return AreEqual(valuetype(pow(ScalarProduct(other), 2)), (LengthSquared() * other.LengthSquared())); }
  inline valuetype LengthSquared() const { return ScalarProduct(*this); }
  inline valuetype Length() const { return valuetype(std::sqrtf(LengthSquared())); }
  inline Vector3D Normalize() const { return operator/(Length()); }
  inline bool IsNormalized() const { return AreEqual(Length(), valuetype(1)); }
  inline Vector3D Project(const Vector3D& other) const { return other * (operator*(other) / other.LengthSquared()); }

  // inline Vector3D Reflect(const Vector3D& normal) const { return (*this) - (Project(normal) * valuetype(2.0)); }
  // inline Vector3D Rotate(float angle_radians) const { return Vector3D(valuetype(float(x_) * std::cosf(angle_radians) - float(y_) * std::sinf(angle_radians)), valuetype(float(x_) * std::sinf(angle_radians) + float(y_) * std::cosf(angle_radians))); }

  valuetype x_, y_, z_;
};
typedef Vector3D<int> vec3i;
typedef Vector3D<float> vec3f;
typedef Vector3D<double> vec3d;

} // namespace
} // namespace

#endif // J_MATH_VECTOR_H_