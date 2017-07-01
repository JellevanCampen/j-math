#pragma once
#ifndef ENGINE_COMMON_DATATYPES_SHAPETYPES_H_
#define ENGINE_COMMON_DATATYPES_SHAPETYPES_H_

#include <string>

namespace engine {

// Represents a line segment in 2D space. 
template<typename valuetype>
struct Line2D {
public:
  // Constructors
  Line2D() { }
  Line2D(Point2D<valuetype> p1, Point2D<valuetype> p2) : p1_(p1), p2_(p2) { }
  Line2D(valuetype x1, valuetype y1, valuetype x2, valuetype y2) : p1_(Point2D<valuetype>(x1, y1)), p2_(Point2D<valuetype>(x2, y2)) { }

  // Operators
  inline bool operator== (const Point2D<valuetype>& other) const { return (p1_ == other.p1_ && p2_ == other.p2_) || (p1_ == other.p2_ && p2_ == other.p1_); }
  inline bool operator!= (const Point2D<valuetype>& other) const { return !((*this) == other); }
  inline Line2D operator+ (const Vector2D<valuetype>& vector) const { return Line2D(p1_ + vector, p2_ + vector); }
  inline Line2D operator- (const Vector2D<valuetype>& vector) const { return Line2D(p1_ - vector, p2_ - vector); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  inline Point2D<valuetype> operator[] (float s) const { return PointOn(s); }
  friend std::ostream& operator<<(std::ostream &os, const Line2D<valuetype>& line) { return os << "l(" << line.p1_ << ", " << line.p2_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
  inline valuetype Length() const { return p1_.Distance(p2_); }
  inline Vector2D<valuetype> Direction() const { return (p2_ - p1_); }
  inline Vector2D<valuetype> Normal() const { return (p2_ - p1_).Normal(); }
  inline Point2D<valuetype> PointOn(float s) const { return p1_.Interpolate(p2_, s); }
  bool Contains(Point2D<valuetype> point) const { 
    bool on_line{ FloatComparison::AreEqual((p1_.x_ - p2_.x_) / (p1_.x_ - point.x_), (p1_.y_ - p2_.y_) / (p1_.y_ - point.y_)) };
    bool on_line_segment_x{ p1_.x_ <= p2_.x_ ? (p1_.x_ <= point.x_ && point.x_ <= p2_.x_) : (p2_.x_ <= point.x_ && point.x_ <= p1_.x_) };
    bool on_line_segment_y{ p1_.y_ <= p2_.y_ ? (p1_.y_ <= point.y_ && point.y_ <= p2_.y_) : (p2_.y_ <= point.y_ && point.y_ <= p1_.y_) };
    return on_line && on_line_segment_x && on_line_segment_y;
  }

  Point2D<valuetype> p1_, p2_;
};
typedef Line2D<int> Line2Di, l2Di;
typedef Line2D<float> Line2Df, l2Df;
typedef Line2D<double> Line2Dd, l2Dd;

// Represents an axis-aligned rectangle in 2D space. 
template<typename valuetype>
struct Rectangle2D {
public:
  // Constructors
  Rectangle2D() { }
  Rectangle2D(Point2D<valuetype> p1, Point2D<valuetype> p2) : p1_(p1), p2_(p2) { }
  Rectangle2D(valuetype x1, valuetype y1, valuetype x2, valuetype y2) : p1_(Point2D<valuetype>(x1, y1)), p2_(Point2D<valuetype>(x2, y2)) { }
  Rectangle2D(Line2D<valuetype> line) : p1_(line.p1_), p2_(line.p2_) { }

  // Operators
  inline bool operator== (const Rectangle2D<valuetype>& other) const { return (p1_ == other.p1_ && p2_ == other.p2_) || (p1_ == other.p2_ && p2_ == other.p1_); }
  inline bool operator!= (const Rectangle2D<valuetype>& other) const { return !((*this) == other); }
  inline Rectangle2D operator+ (const Vector2D<valuetype>& vector) const { return Rectangle2D(p1_ + vector, p2_ + vector); }
  inline Rectangle2D operator- (const Vector2D<valuetype>& vector) const { return Rectangle2D(p1_ - vector, p2_ - vector); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  inline Line2D<valuetype> operator[] (float s) const { return LineOn(s); }
  friend std::ostream& operator<<(std::ostream &os, const Rectangle2D<valuetype>& rectangle) { return os << "r(" << rectangle.p1_ << ", " << rectangle.p2_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { p1_ += vector; p2_ += vector; }
  inline Rectangle2D ReorderPoints() const {
    Point2D<valuetype> p1, p2;
    if (p1_.x_ <= p2_.x_) { p1.x_ = p1_.x_; p2.x_ = p2_.x_; }
    else { p1.x_ = p2_.x_; p2.x_ = p1_.x_; }
    if (p1_.y_ <= p2_.y_) { p1.y_ = p1_.y_; p2.y_ = p2_.y_; }
    else { p1.y_ = p2_.y_; p2.y_ = p1_.y_; }
    return Rectangle2D(p1, p2);
  }
  inline Vector2D<valuetype> Size() const { return Vector2D<valuetype>(valuetype(p1_.x_ <= p2_x_ ? p2_.x_ - p1.x_ : p1_.x_ - p2_.x_), valuetype(p1_.y_ <= p2_y_ ? p2_.y_ - p1.y_ : p1_.y_ - p2_.y_)); }
  inline valuetype Area() const { Vector2D<valuetype> size{ Size() }; return size.x_ * size.y_; }
  inline Line2D<valuetype> LineOn(float s) const {
    Rectangle2D r{ ReorderPoints() }; 
    valuetype x = r.p1_.x_ * (1.0f - s) + r.p2_.x_ * s;
    return Line2D<valuetype>(x, p1_.y_, x, p2_.y_); }
  inline Point2D<valuetype> PointOn(float s, float t) const { 
    Rectangle2D r{ ReorderPoints() }; 
    return Point2D<valuetype>(r.p1_.x_ * (1.0f - s) + r.p2_.x_ * s, r.p1_.t_ * (1.0f - t) + r.p2_.y_ * t); 
  }
  bool Contains(Point2D<valuetype> point) const {
    bool contains_x{ p1_.x_ <= p2_.x_ ? (p1_.x_ <= point.x_ && point.x_ <= p2_.x_) : (p2_.x_ <= point.x_ && point.x_ <= p1_.x_) };
    bool contains_y{ p1_.y_ <= p2_.y_ ? (p1_.y_ <= point.y_ && point.y_ <= p2_.y_) : (p2_.y_ <= point.y_ && point.y_ <= p1_.y_) };
    return contains_x && contains_y;
  }
  inline bool Contains(Line2D<valuetype> line) const { return Contains(line.p1_) && Contains(line.p2_); }

  Point2D<valuetype> p1_, p2_;
};
typedef Rectangle2D<int> Rectangle2Di, r2Di;
typedef Rectangle2D<float> Rectangle2Df, r2Df;
typedef Rectangle2D<double> Rectangle2Dd, r2Dd;

} // namespace

#endif // ENGINE_COMMON_DATATYPES_SHAPETYPES_H_