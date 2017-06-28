#include <sstream>
#include "gtest/gtest.h"
#include "../src/vector.h"

using namespace j::math;

TEST(Vector2DTests, Constructors) {
  vec2i vec_default;
  vec2i vec_xy(3, 5);
  vec2i vec_copy(vec_xy);
  EXPECT_EQ(vec_default.x_, 0);
  EXPECT_EQ(vec_default.y_, 0);
  EXPECT_EQ(vec_xy.x_, 3);
  EXPECT_EQ(vec_xy.y_, 5);
  EXPECT_EQ(vec_copy.x_, 3);
  EXPECT_EQ(vec_copy.y_, 5);
}

TEST(Vector2DTests, TemplateTypes) {
  vec2d vec_d(2.5, 3.5);
  vec2i vec_i(2.5, 3.5);
  EXPECT_EQ(vec_d.x_, 2.5);
  EXPECT_EQ(vec_d.y_, 3.5);
  EXPECT_EQ(vec_i.x_, 2);
  EXPECT_EQ(vec_i.y_, 3);
}

TEST(Vector2DTests, TypeCasting) {
  vec2d vec_d(2.5, 3.5);
  vec2i vec_i = vec2i(vec_d);
  EXPECT_EQ(vec_d.x_, 2.5);
  EXPECT_EQ(vec_d.y_, 3.5);
  EXPECT_EQ(vec_i.x_, 2);
  EXPECT_EQ(vec_i.y_, 3);
}

TEST(Vector2DTests, CopyAssignment) {
  vec2d vec_d1(2.5, 3.5);
  vec2d vec_d2 = vec_d1;
  vec_d1 = vec2d(4.5, 6.5);
  EXPECT_EQ(vec_d1.x_, 4.5);
  EXPECT_EQ(vec_d1.y_, 6.5);
  EXPECT_EQ(vec_d2.x_, 2.5);
  EXPECT_EQ(vec_d2.y_, 3.5);
}

TEST(Vector2DTests, ComparisonOperators) {
  vec2f vec_f1(2.5f, 3.5f);
  vec2f vec_f2(2.5f, 3.5f);
  vec2f vec_f3(4.5f, 6.5f);
  EXPECT_EQ(vec_f1, vec_f2);
  EXPECT_NE(vec_f2, vec_f3);
}

TEST(Vector2DTests, SubscriptOperator) {
  vec2f vec_f1(2.5f, 3.5f);
  EXPECT_EQ(vec_f1[0], 2.5f);
  EXPECT_EQ(vec_f1[1], 3.5f);
  vec_f1[0] = 4.5f;
  vec_f1[1] = 6.5f;
  EXPECT_EQ(vec_f1[0], 4.5f);
  EXPECT_EQ(vec_f1[1], 6.5f);
}

TEST(Vector2DTests, MathematicalOperators) {
  vec2i vec1(2, 3);
  vec2i vec2(9, 6);
  vec2i plus_vec1 = +vec1;
  vec2i minus_vec1 = -vec1;
  EXPECT_EQ(plus_vec1.x_, 2);
  EXPECT_EQ(plus_vec1.y_, 3);
  EXPECT_EQ(minus_vec1.x_, -2);
  EXPECT_EQ(minus_vec1.y_, -3);
  vec2i sum = vec1 + vec2;
  vec2i difference = vec2 - vec1;
  EXPECT_EQ(sum.x_, 11);
  EXPECT_EQ(sum.y_, 9);
  EXPECT_EQ(difference.x_, 7);
  EXPECT_EQ(difference.y_, 3);
  int s = 3;
  vec2i product = vec1 * s;
  vec2i division = vec2 / s;
  EXPECT_EQ(product.x_, 6);
  EXPECT_EQ(product.y_, 9);
  EXPECT_EQ(division.x_, 3);
  EXPECT_EQ(division.y_, 2);
}

TEST(Vector2DTests, CompoundAssignmentOperators) {
  vec2i vec(2, 3);
  vec += vec2i(5, 3);
  EXPECT_EQ(vec.x_, 7);
  EXPECT_EQ(vec.y_, 6);
  vec -= vec2i(4, 1);
  EXPECT_EQ(vec.x_, 3);
  EXPECT_EQ(vec.y_, 5);
  vec *= 2;
  EXPECT_EQ(vec.x_, 6);
  EXPECT_EQ(vec.y_, 10);
  vec /= 2;
  EXPECT_EQ(vec.x_, 3);
  EXPECT_EQ(vec.y_, 5);
}

TEST(Vector2DTests, StringConversion) {
  vec2i vec(2, 3);
  std::stringstream ss; 
  ss << vec;
  std::string s = ss.str();
  EXPECT_EQ(s.compare("v(2, 3)"), 0);
}

TEST(Vector2DTests, ScalarProduct) {
  vec2i vec1(2, 3);
  vec2i vec2(4, 6);
  EXPECT_EQ(vec1.ScalarProduct(vec2), 2*4 + 3*6);
  EXPECT_EQ(vec1 * vec2, 2 * 4 + 3 * 6);
}

TEST(Vector2DTests, NormalVector) {
  vec2i vec(2, 3);
  EXPECT_EQ(vec.Normal(), vec2i(-3, 2));
  EXPECT_EQ(vec * vec.Normal(), 0);
}

TEST(Vector2DTests, OrthogonalityCollinearity) {
  vec2i vec1(2, 3);
  vec2i vec2(3, 2);
  vec2i vec1_o1 = vec2i(-3, 2);
  vec2i vec1_o2 = vec2i(3, -2);
  vec2i vec1_o3 = vec2i(6, -4);
  vec2i vec1_cl1 = vec2i(2, 3);
  vec2i vec1_cl2 = vec2i(-2, -3);
  vec2i vec1_cl3 = vec2i(-4, -6);
  EXPECT_FALSE(vec1.IsOrthogonal(vec2));
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o1));
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o2));
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o3));
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl1));
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl2));
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl3));  
  EXPECT_FALSE(vec1.IsCollinear(vec2));
  EXPECT_FALSE(vec1.IsCollinear(vec1_o1));
  EXPECT_FALSE(vec1.IsCollinear(vec1_o2));
  EXPECT_FALSE(vec1.IsCollinear(vec1_o3));
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl1));
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl2));
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl3));
}

TEST(Vector2DTests, LengthCalculation) {
  vec2i vec_i(2, 3);
  EXPECT_EQ(vec_i.LengthSquared(), 13);
  EXPECT_EQ(vec_i.Length(), 3);
  vec2f vec_f(2.0, 3.0);
  EXPECT_EQ(vec_f.LengthSquared(), 13.f);
  EXPECT_EQ(vec_f.Length(), 3.605551275f);
}

TEST(Vector2DTests, Normalization) {
  vec2f vec(2.f, 3.f);
  vec2f vec_n = vec.Normalize();
  EXPECT_EQ(vec_n, vec2f(0.5547001962f, 0.83205029434f));
  EXPECT_EQ(vec_n.Length(), 1.f);
}

TEST(Vector2DTests, Projection) {
  vec2f vec(2.f, 3.f);
  vec2f vec_x(1.f, 0.f);
  vec2f vec_neg_y(0.f, -1.f);
  EXPECT_EQ(vec.Project(vec_x), vec2f(2.f, 0.f));
  EXPECT_EQ(vec.Project(vec_neg_y), vec2f(0.f, 3.f));
  EXPECT_EQ(vec.Project(vec), vec2f(2.f, 3.f));
}