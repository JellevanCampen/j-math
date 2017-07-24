#pragma once
#ifndef J_MATH_SEQUENCE_H_
#define J_MATH_SEQUENCE_H_

#include <vector>
#include <sstream>
#include "..\utility\clamp.h"

namespace j {
namespace math {

// Method of indexing
enum class IndexType {
  CLAMP, 
  WRAP
};

// One-dimensional sequence of values.
template<typename valuetype>
struct Sequence1D {
  // Constructors
  Sequence1D() : data_{ std::vector<valuetype>() } { }
  Sequence1D(const Sequence1D&) = default;
  Sequence1D(const std::vector<valuetype>& data) : data_{ data } { }
  ~Sequence1D() = default;

  // Operators
  Sequence1D& operator=(const Sequence1D& other) = default;
  bool operator==(const Sequence1D<valuetype>& other) const { return data_ == other.data_; }
  bool operator!=(const Sequence1D<valuetype>& other) const { return data_ != other.data_; }
  // Sequence1D operator+(const Sequence1D<valuetype>& vector) const { return Line2D(p_ + vector, v_); }
  // Sequence1D operator-(const Sequence1D<valuetype>& vector) const { return Line2D(p_ - vector, v_); }
  // void operator+=(const Vector2D<valuetype>& vector) { p_ += vector; }
  // void operator-=(const Vector2D<valuetype>& vector) { p_ -= vector; }
  valuetype operator()(const size_t& i) const { return Get(i); }

  // Cast to different valuetype
  template<typename other_valuetype> operator Sequence1D<other_valuetype>() const { return Sequence1D<other_valuetype>(other_valuetype(data_)); }

  // String conversion
  friend std::ostream& operator<<(std::ostream &os, const Sequence1D<valuetype>& sequence) { 
    std::stringstream ss;
    ss << "Sequence1D(";
    for (valuetype d : data_) { ss << d << ", "; }
    ss.unget();
    ss.unget();
    ss << ")";
    std::string result = ss.str();
    return os << result; 
  }

  // Sequence-specific operations
  void Add(const valuetype& data) { data_.push_back(data); }
  valuetype Get(const size_t& index, IndexType index_type = IndexType::CLAMP) const { return data_[(ConvertIndex(index, index_type))]; }
  void Set(const size_t& index, const valuetype& data, IndexType index_type = IndexType::CLAMP) const { data_[(ConvertIndex(index, index_type))] = data; }
  valuetype* Ptr() { return &data_[0]; }
  size_t Length() const { return data_.size(); }
  valuetype Sum() const { valuetype s{ 0 }; for (auto d : data_) { s += d; } return s; }
  valuetype SumOfSquares() const { valuetype s{ 0 }; for (auto d : data_) { s += d * d; } return s; }
  valuetype Average() const { valuetype s{ 0 }; for (auto d : data_) { s += d; } return s / Length(); }

private:
  static size_t ConvertIndex(const size_t& i, IndexType index_type) {
    switch(index_type) {
    case IndexType::CLAMP:
		  return j::math::clamp(i, 0, data_.size());
    case IndexType::WRAP:
      return i % data_.size();
    default: 
      return 0;
    }
  }

  std::vector<valuetype> data_;
};

using seq1i = Sequence1D<int>;
using seq1f = Sequence1D<float>;
using seq1d = Sequence1D<double>;

} // namespace
} // namespace

#endif // J_MATH_SEQUENCE_H_
