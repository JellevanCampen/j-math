#include <gtest\gtest.h>
#include "..\src\point.h"

using namespace j::math;

//
// Point2DTests
//
TEST(Point2DTests, Constructors) {
  p2i p_default;
  p2i p_xy(3, 5);
  p2i p_copy(p_xy);
  EXPECT_EQ(p_default, p2i(0, 0)) << "Default constructor did not initialize to origin.";
  EXPECT_EQ(p_xy, p2i(3, 5)) << "Value-based constructor did not initialize correctly.";
  EXPECT_EQ(p_copy, p2i(3, 5)) << "Copy constructor did not copy values correctly.";
}

TEST(Point2DTests, TemplateTypes) {
  p2d p_d(2.5, 3.5);
  p2i p_i(2.5, 3.5);
  EXPECT_EQ(p_d, p2d(2.5, 3.5)) << "Point of type double did not initialize correctly.";
  EXPECT_EQ(p_i, p2i(2, 3)) << "Point of type int did not truncate values correctly.";
}

TEST(Point2DTests, TypeCasting) {
  p2d p_d(2.5, 3.5);
  p2i p_i = p2i(p_d);
  EXPECT_EQ(p_i, p2i(2, 3)) << "Point of type double was not cast to int with values correctly.";
}

TEST(Point2DTests, CopyAssignment) {
  p2d p_d1(2.5, 3.5);
  p2d p_d2 = p_d1;
  p_d1 = p2d(4.5, 6.5);
  EXPECT_EQ(p_d1, p2d(4.5, 6.5)) << "Point values were not updated correctly.";
  EXPECT_EQ(p_d2, p2d(2.5, 3.5)) << "Original point values were modified, meaning a shallow copy was made instead of a deep copy.";
}

TEST(Point2DTests, ComparisonOperators) {
  p2f p_f1(2.5f, 3.5f);
  p2f p_f2(2.5f, 3.5f);
  p2f p_f3(4.5f, 6.5f);
  EXPECT_EQ(p_f1, p_f2) << "Two equal points were identified as non-equal.";
  EXPECT_NE(p_f2, p_f3) << "Two non-equal points were identified as equal.";
}

TEST(Point2DTests, SubscriptOperator) {
  p2f p_f1(2.5f, 3.5f);
  EXPECT_EQ(p_f1[0], 2.5f) << "Point x value was not read correctly.";
  EXPECT_EQ(p_f1[1], 3.5f) << "Point y value was not read correctly.";
  p_f1[0] = 4.5f;
  p_f1[1] = 6.5f;
  EXPECT_EQ(p_f1[0], 4.5f) << "Point x value was not written correctly. Subscript operator possibly returned deep copy of x instead of reference to x.";
  EXPECT_EQ(p_f1[1], 6.5f) << "Point y value was not written correctly. Subscript operator possibly returned deep copy of y instead of reference to y.";
}

TEST(Point2DTests, VectorTranslations) {
  p2i p(2, 3);
  vec2i vec(9, 6);
  p2i sum = p + vec;
  p2i difference = p - vec;
  EXPECT_EQ(sum, p2i(11, 9)) << "Sum with vector returned incorrect result.";
  EXPECT_EQ(difference, p2i(-7, -3)) << "Difference with vector returned incorrect result.";
}

TEST(Point2DTests, PointDifference) {
  p2i p1(2, 3);
  p2i p2(7, 6);
  vec2i vec = p2 - p1;
  EXPECT_EQ(vec, vec2i(5, 3)) << "Difference between points returned incorrect vector.";
}

TEST(Point2DTests, CompoundAssignmentOperators) {
  p2i p(2, 3);
  vec2i vec(9, 6);
  p += vec;
  EXPECT_EQ(p, p2i(11, 9)) << "Sum assignment operator returned incorrect result.";
  p -= vec;
  EXPECT_EQ(p, p2i(2, 3)) << "Difference assignment operator returned incorrect result.";
}

TEST(Point2DTests, StringConversion) {
  p2i p(2, 3);
  std::stringstream ss;
  ss << p;
  std::string s = ss.str();
  EXPECT_STREQ(s.c_str(), "Point2D(2, 3)") << "String conversion returned incorrect result.";
}

TEST(Point2DTests, Distance) {
  p2f p1(2.f, 3.f);
  p2f p2(4.f, 8.f);
  p2f p3(-3.f, 5.f);
  p2f p4(-3.f, -5.f);
  EXPECT_EQ(p1.Distance(p2), 5.38516480713450f) << "Distance between two points with all positive components is incorrect.";
  EXPECT_EQ(p1.Distance(p3), 5.38516480713450f) << "Distance between two points with some negative components is incorrect.";
  EXPECT_EQ(p1.Distance(p4), 9.43398113205660f) << "Distance between two points with all positive and all negative components is incorrect.";
}

//
// Point3DTests
//