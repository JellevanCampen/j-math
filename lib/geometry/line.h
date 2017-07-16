#pragma once
#ifndef J_MATH_LINE_H_
#define J_MATH_LINE_H_

#include "point.h"
#include "vector.h"

namespace j {
namespace math {

// A two-dimensional line. Represented by a point and a vector.
template<typename valuetype>
struct Line2D {
  // Constructors
  Line2D() : p_{ 0, 0 }, v_{ Vector2D<valuetype>(1, 1).Normalize() } { }
  Line2D(const Line2D&) = default;
  Line2D(Point2D<valuetype> p, Vector2D<valuetype> v) : p_{ p }, v_{ v.Normalize() } { }
  Line2D(Point2D<valuetype> p1, Point2D<valuetype> p2) : p_{ p1 }, v_{ (p2 - p1).Normalize() } { }
  Line2D(valuetype x1, valuetype y1, valuetype x2, valuetype y2) : Line2D(Point2D<valuetype>(x1, y1), Point2D<valuetype>(x2, y2)) { }
  ~Line2D() = default;

  // Operators
  Line2D& operator=(const Line2D& other) = default;
  bool operator==(const Line2D<valuetype>& other) const { return(v_.IsCollinear(other.v_) && IsOnCurve(other.p_)); }
  bool operator!=(const Line2D<valuetype>& other) const { return(!IsOnCurve(other.p_) || !v_.IsCollinear(other.v_)); }
  Line2D operator+(const Vector2D<valuetype>& vector) const { return Line2D(p_ + vector, v_); }
  Line2D operator-(const Vector2D<valuetype>& vector) const { return Line2D(p_ - vector, v_); }
  void operator+=(const Vector2D<valuetype>& vector) { p_ += vector; }
  void operator-=(const Vector2D<valuetype>& vector) { p_ -= vector; }
  Point2D<valuetype> operator()(valuetype s) const { return GetPoint(s); }

  // Cast to different valuetype
  template<typename other_valuetype> operator Line2D<other_valuetype>() const { return Line2D<other_valuetype>(other_valuetype(p_), other_valuetype(v_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Line2D<valuetype>& line) { return os << "Line2D(p=" << line.p_ << ", v=" << line.v_ << ")"; }

  // Line-specific operations
  Vector2D<valuetype> GetDirection() const { return v_; }
  void SetDirection(const Vector2D<valuetype>& v) { v_ = v.Normalize(); }
  valuetype EvaluateImplicitEquation(const Point2D<valuetype>& p) const { return(v_.Normal() * (p - p_)); }
  bool IsOnCurve(const Point2D<valuetype>& p) const { return AreEqual(EvaluateImplicitEquation(p), valuetype(0)); }
  bool IsOnLeftSideOfLine(const Point2D<valuetype>& p) const { return EvaluateImplicitEquation(p) < 0; }
  bool IsOnRightSideOfLine(const Point2D<valuetype>& p) const { return EvaluateImplicitEquation(p) > 0; }
  valuetype SignedDistanceToCurve(const Point2D<valuetype>& p) const { return EvaluateImplicitEquation(p); }
  valuetype DistanceToCurve(const Point2D<valuetype>& p) const { valuetype d = SignedDistanceToCurve(p); return (d >= 0)? d : -d; }
  Point2D<valuetype> EvaluateParametricSpecification(valuetype s) const { return(p_ + (v_ * s)); }
  valuetype FindNearestParameterValue(const Point2D<valuetype>& p) const { return (p - p_).ScalarProduct(v_); }
  Point2D<valuetype> FindNearestPoint(const Point2D<valuetype>& p) const { return EvaluateParametricSpecification(FindNearestParameterValue(p)); }
  Vector2D<valuetype> Normal() const { return v_.Normal(); }

  Point2D<valuetype> p_;
private:
  Vector2D<valuetype> v_; // Only accessible via getter and setter to keep it a unit vector to simplify calculations
};
typedef Line2D<int> Line2i;
typedef Line2D<float> Line2f;
typedef Line2D<double> Line2d;

// A three-dimensional line. Represented by a point and a vector.
template<typename valuetype>
struct Line3D {
  // Constructors
  Line3D() : p_{ 0, 0, 0 }, v_{ Vector3D<valuetype>(1, 1, 1).Normalize() } { }
  Line3D(const Line3D&) = default;
  Line3D(Point3D<valuetype> p, Vector3D<valuetype> v) : p_{ p }, v_{ v.Normalize() } { }
  Line3D(Point3D<valuetype> p1, Point3D<valuetype> p2) : p_{ p1 }, v_{ (p2 - p1).Normalize() } { }
  Line3D(valuetype x1, valuetype y1, valuetype z1, valuetype x2, valuetype y2, valuetype z2) : Line3D(Point3D<valuetype>(x1, y1, z1), Point3D<valuetype>(x2, y2, z2)) { }
  ~Line3D() = default;

  // Operators
  Line3D& operator=(const Line3D& other) = default;
  bool operator==(const Line3D<valuetype>& other) const { return(v_.IsCollinear(other.v_) && IsOnCurve(other.p_)); }
  bool operator!=(const Line3D<valuetype>& other) const { return(!IsOnCurve(other.p_) || !v_.IsCollinear(other.v_)); }
  Line3D operator+(const Vector3D<valuetype>& vector) const { return Line3D(p_ + vector, v_); }
  Line3D operator-(const Vector3D<valuetype>& vector) const { return Line3D(p_ - vector, v_); }
  void operator+=(const Vector3D<valuetype>& vector) { p_ += vector; }
  void operator-=(const Vector3D<valuetype>& vector) { p_ -= vector; }
  Point3D<valuetype> operator()(valuetype s) const { return GetPoint(s); }

  // Cast to different valuetype
  template<typename other_valuetype> operator Line3D<other_valuetype>() const { return Line3D<other_valuetype>(other_valuetype(p_), other_valuetype(v_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Line3D<valuetype>& line) { return os << "Line3D(p=" << line.p_ << ", v=" << line.v_ << ")"; }

  // Line-specific operations
  Vector3D<valuetype> GetDirection() const { return v_; }
  void SetDirection(const Vector3D<valuetype>& v) { v_ = v.Normalize(); }
  Point3D<valuetype> GetPoint(valuetype s) const { return(p_ + (v_ * s)); }
  bool IsOnCurve(const Point3D<valuetype>& p) const { return ((p_ == p) || v_.IsCollinear(p - p_)); }
  // TODO: valuetype DistanceTo(const Point3D<valuetype>& p) const {  }
  Point3D<valuetype> EvaluateParametricSpecification(valuetype s) const { return(p_ + (v_ * s)); }
  valuetype FindNearestParameterValue(const Point3D<valuetype>& p) const { return (p - p_).ScalarProduct(v_); }
  Point3D<valuetype> FindNearestPoint(const Point3D<valuetype>& p) const { return EvaluateParametricSpecification(FindNearestParameterValue(p)); }

  Point3D<valuetype> p_;
private:
  Vector3D<valuetype> v_; // Only accessible via getter and setter to keep it a unit vector to simplify calculations
};
typedef Line3D<int> Line3i;
typedef Line3D<float> Line3f;
typedef Line3D<double> Line3d;

} // namespace
} // namespace

#endif // J_MATH_LINE_H_
