#include <sstream>
#include <gtest\gtest.h>
#include "..\src\vector.h"

using namespace j::math;

//
// Vector2DTests
//
TEST(Vector2DTests, Constructors) {
  vec2i vec_default;
  vec2i vec_xy(3, 5);
  vec2i vec_copy(vec_xy);
  EXPECT_EQ(vec_default, vec2i(0, 0)) << "Default constructor did not initialize to (0, 0). Values: " << vec_default;
  EXPECT_EQ(vec_xy, vec2i(3, 5)) << "Value-based constructor did not initialize to (3, 5). Values: " << vec_xy;
  EXPECT_EQ(vec_copy, vec2i(3, 5)) << "Copy constructor did not copy values (3, 5) correctly. Values: " << vec_copy;
}

TEST(Vector2DTests, TemplateTypes) {
  vec2d vec_d(2.5, 3.5);
  vec2i vec_i(2.5, 3.5);
  EXPECT_EQ(vec_d, vec2d(2.5, 3.5)) << "Vector of type double did not initialize to (2.5, 3.5) correctly. Values: " << vec_d;
  EXPECT_EQ(vec_i, vec2i(2, 3)) << "Vector of type int did not round down values to (2, 3) correctly. Values: " << vec_i;
}

TEST(Vector2DTests, TypeCasting) {
  vec2d vec_d(2.5, 3.5);
  vec2i vec_i = vec2i(vec_d);
  EXPECT_EQ(vec_d, vec2d(2.5, 3.5)) << "Vector of type double did not initialize to (2.5, 3.5) correctly. Values: " << vec_d;
  EXPECT_EQ(vec_i, vec2i(2, 3)) << "Vector of type double was not cast to int with values (2, 3) correctly. Values: " << vec_i;
}

TEST(Vector2DTests, CopyAssignment) {
  vec2d vec_d1(2.5, 3.5);
  vec2d vec_d2 = vec_d1;
  vec_d1 = vec2d(4.5, 6.5);
  EXPECT_EQ(vec_d1, vec2d(4.5, 6.5)) << "Vector values were not updated to (4.5, 6.5) correctly. Values: " << vec_d1;
  EXPECT_EQ(vec_d2, vec2d(2.5, 3.5)) << "Original vector values were modified (expected (2.5, 3.5)), meaning a shallow copy was made instead of a deep copy. Values: " << vec_d2;
}

TEST(Vector2DTests, ComparisonOperators) {
  vec2f vec_f1(2.5f, 3.5f);
  vec2f vec_f2(2.5f, 3.5f);
  vec2f vec_f3(4.5f, 6.5f);
  EXPECT_EQ(vec_f1, vec_f2) << "Two equal vectors were identified as non-equal. Values: " << vec_f1 << ", " << vec_f2;
  EXPECT_NE(vec_f2, vec_f3) << "Two non-equal vectors were identified as equal. Values: " << vec_f2 << ", " << vec_f3;
}

TEST(Vector2DTests, SubscriptOperator) {
  vec2f vec_f1(2.5f, 3.5f);
  EXPECT_EQ(vec_f1[0], 2.5f) << "Vector x value was not read correctly (expected: 2.5f). Value: " << vec_f1[0];
  EXPECT_EQ(vec_f1[1], 3.5f) << "Vector y value was not read correctly (expected: 3.5f). Value: " << vec_f1[1];
  vec_f1[0] = 4.5f;
  vec_f1[1] = 6.5f;
  EXPECT_EQ(vec_f1[0], 4.5f) << "Vector x value was not written correctly. Subscript operator possibly returned deep copy of x instead of reference to x (expected: 4.5f). Value: " << vec_f1[0];
  EXPECT_EQ(vec_f1[1], 6.5f) << "Vector y value was not written correctly. Subscript operator possibly returned deep copy of y instead of reference to y (expected: 6.5f). Value: " << vec_f1[1];
}

TEST(Vector2DTests, MathematicalOperators) {
  vec2i vec1(2, 3);
  vec2i vec2(9, 6);
  vec2i plus_vec1 = +vec1;
  vec2i minus_vec1 = -vec1;
  EXPECT_EQ(plus_vec1, vec2i(2, 3)) << "Unary plus operator returned incorrect result (expected (2, 3)). Values: " << plus_vec1;
  EXPECT_EQ(minus_vec1, vec2i(-2, -3)) << "Unary minus operator returned incorrect result (expected (-2, -3)). Values: " << minus_vec1;
  vec2i sum = vec1 + vec2;
  vec2i difference = vec2 - vec1;
  EXPECT_EQ(sum, vec2i(11, 9)) << "Binary sum operator returned incorrect result (expected (11, 9)). Values: " << sum;
  EXPECT_EQ(difference, vec2i(7, 3)) << "Binary difference operator returned incorrect result (expected (7, 3)). Values: " << difference;
  int s = 3;
  vec2i product = vec1 * s;
  vec2i division = vec2 / s;
  EXPECT_EQ(product, vec2i(6, 9)) << "Binary multiplication operator returned incorrect result (expected (6, 9)). Values: " << product;
  EXPECT_EQ(division, vec2i(3, 2)) << "Binary division operator returned incorrect result (expected (3, 2)). Values: " << division;
}

TEST(Vector2DTests, CompoundAssignmentOperators) {
  vec2i vec(2, 3);
  vec += vec2i(5, 3);
  EXPECT_EQ(vec, vec2i(7, 6)) << "Sum assignment operator returned incorrect result (expected (7, 6)). Values: " << vec;
  vec -= vec2i(4, 1);
  EXPECT_EQ(vec, vec2i(3, 5)) << "Difference assignment operator returned incorrect result (expected (3, 5)). Values: " << vec;
  vec *= 2;
  EXPECT_EQ(vec, vec2i(6, 10)) << "Multiplication assignment operator returned incorrect result (expected (6, 10)). Values: " << vec;
  vec /= 2;
  EXPECT_EQ(vec, vec2i(3, 5)) << "Division assignment operator returned incorrect result (expected (3, 5)). Values: " << vec;
}

TEST(Vector2DTests, StringConversion) {
  vec2i vec(2, 3);
  std::stringstream ss;
  ss << vec;
  std::string s = ss.str();
  EXPECT_EQ(s.compare("Vector2D(2, 3)"), 0) << "String conversion returned incorrect string (expected \"v(7, 6)\"). String: \"" << vec << "\"";
}

TEST(Vector2DTests, ScalarProduct) {
  vec2i vec1(2, 3);
  vec2i vec2(4, 6);
  EXPECT_EQ(vec1.ScalarProduct(vec2), 2*4 + 3*6) << "Scalar product is incorrect (expected (26)). Value: " << vec1.ScalarProduct(vec2);
  EXPECT_EQ(vec1 * vec2, 2 * 4 + 3 * 6) << "Scalar product is incorrect (expected (26)). Value: " << vec1 * vec2;
}

TEST(Vector2DTests, NormalVector) {
  vec2i vec(2, 3);
  EXPECT_EQ(vec.Normal(), vec2i(-3, 2)) << "Normal vector is incorrect (expected (-3, 2)). Value: " << vec.Normal();
  EXPECT_EQ(vec * vec.Normal(), 0) << "Scalar product of vector with its normal should be 0 due to orthogonality. Value: " << vec * vec.Normal();
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
  EXPECT_FALSE(vec1.IsOrthogonal(vec2)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o1)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o2)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o3)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl1)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl2)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl3)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsCollinear(vec2)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o1)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o2)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o3)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl1)) << "Two collinear vectors falsely identified as being non-collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl2)) << "Two collinear vectors falsely identified as being non-collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl3)) << "Two collinear vectors falsely identified as being non-collinear.";
}

TEST(Vector2DTests, LengthCalculation) {
  vec2i vec_i(2, 3);
  EXPECT_EQ(vec_i.LengthSquared(), 13) << "Squared length is incorrect (expected (13)). Value: " << vec_i.LengthSquared();
  EXPECT_EQ(vec_i.Length(), 3) << "Length is incorrect (expected (3)). Value: " << vec_i.Length();
  vec2f vec_f(2.0, 3.0);
  EXPECT_EQ(vec_f.LengthSquared(), 13.f) << "Squared length is incorrect (expected (13.f)). Value: " << vec_f.LengthSquared();;
  EXPECT_EQ(vec_f.Length(), 3.605551275f) << "Length is incorrect (expected (3.605551275f)). Value: " << vec_f.Length();
}

TEST(Vector2DTests, Normalization) {
  vec2f vec(2.f, 3.f);
  vec2f vec_n = vec.Normalize();
  vec2f vec_n_neg = (-vec).Normalize();
  EXPECT_EQ(vec_n, vec2f(0.5547001962f, 0.83205029434f)) << "Normalized vector is incorrect (expected (0.5547001962f, 0.83205029434f)). Value: " << vec_n;
  EXPECT_EQ(vec_n.Length(), 1.f) << "Length of a normalized vector should be 1. Value: " << vec_n.Length();
  EXPECT_EQ(vec_n_neg, vec2f(-0.5547001962f, -0.83205029434f)) << "Normalized vector is incorrect (expected (-0.5547001962f, -0.83205029434f)). Possible error with negative component values. Value: " << vec_n_neg;
  EXPECT_EQ(vec_n_neg.Length(), 1.f) << "Length of a normalized vector should be 1. Possible error with negative component values. Value: " << vec_n_neg.Length();
}

TEST(Vector2DTests, Projection) {
  vec2f vec(2.f, 3.f);
  vec2f vec_x(1.f, 0.f);
  vec2f vec_neg_y(0.f, -1.f);
  EXPECT_EQ(vec.ProjectOnto(vec_x), vec2f(2.f, 0.f)) << "Vector projection onto x-axis is incorrect (expected (2.f, 0.f)). Value: " << vec.ProjectOnto(vec_x);
  EXPECT_EQ(vec.ProjectOnto(vec_neg_y), vec2f(0.f, 3.f)) << "Vector projection onto negative y-axis is incorrect (expected (0.f, 3.f)). Possible error with negative components in projection vectors. Value: " << vec.ProjectOnto(vec_neg_y);
  EXPECT_EQ(vec.ProjectOnto(vec_x * 2), vec2f(2.f, 0.f)) << "Vector projection onto non-normalized x-axis is incorrect (expected (2.f, 0.f)). Possible error with non-unit projection vectors. Value: " << vec.ProjectOnto(vec_x * 2);
  EXPECT_EQ(vec.ProjectOnto(vec), vec2f(2.f, 3.f)) << "Vector projection onto self should result in identity operation (expected (2.f, 3.f)). Value: " << vec.ProjectOnto(vec);
}



//
// Vector3DTests
//
TEST(Vector3DTests, Constructors) {
  vec3i vec_default;
  vec3i vec_xyz(3, 5, 8);
  vec3i vec_copy(vec_xyz);
  EXPECT_EQ(vec_default, vec3i(0, 0, 0)) << "Default constructor did not initialize to (0, 0, 0). Values: " << vec_default;
  EXPECT_EQ(vec_xyz, vec3i(3, 5, 8)) << "Value-based constructor did not initialize to (3, 5, 8). Values: " << vec_xyz;
  EXPECT_EQ(vec_copy, vec3i(3, 5, 8)) << "Copy constructor did not copy values (3, 5, 8) correctly. Values: " << vec_copy;
}

TEST(Vector3DTests, TemplateTypes) {
  vec3d vec_d(2.5, 3.5, 8.5);
  vec3i vec_i(2.5, 3.5, 8.5);
  EXPECT_EQ(vec_d, vec3d(2.5, 3.5, 8.5)) << "Vector of type double did not initialize to (2.5, 3.5, 8.5) correctly. Values: " << vec_d;
  EXPECT_EQ(vec_i, vec3i(2, 3, 8)) << "Vector of type int did not round down values to (2, 3, 8) correctly. Values: " << vec_i;
}

TEST(Vector3DTests, TypeCasting) {
  vec3d vec_d(2.5, 3.5, 8.5);
  vec3i vec_i = vec3i(vec_d);
  EXPECT_EQ(vec_d, vec3d(2.5, 3.5, 8.5)) << "Vector of type double did not initialize to (2.5, 3.5, 8.5) correctly. Values: " << vec_d;
  EXPECT_EQ(vec_i, vec3i(2, 3, 8)) << "Vector of type double was not cast to int with values (2, 3) correctly. Values: " << vec_i;
}

TEST(Vector3DTests, CopyAssignment) {
  vec3d vec_d1(2.5, 3.5, 8.5);
  vec3d vec_d2 = vec_d1;
  vec_d1 = vec3d(4.5, 6.5, 7.5);
  EXPECT_EQ(vec_d1, vec3d(4.5, 6.5, 7.5)) << "Vector values were not updated to (4.5, 6.5, 7.5) correctly. Values: " << vec_d1;
  EXPECT_EQ(vec_d2, vec3d(2.5, 3.5, 8.5)) << "Original vector values were modified (expected (2.5, 3.5, 8.5)), meaning a shallow copy was made instead of a deep copy. Values: " << vec_d2;
}

TEST(Vector3DTests, ComparisonOperators) {
  vec3f vec_f1(2.5f, 3.5f, 8.5f);
  vec3f vec_f2(2.5f, 3.5f, 8.5f);
  vec3f vec_f3(4.5f, 6.5f, 7.5f);
  EXPECT_EQ(vec_f1, vec_f2) << "Two equal vectors were identified as non-equal. Values: " << vec_f1 << ", " << vec_f2;
  EXPECT_NE(vec_f2, vec_f3) << "Two non-equal vectors were identified as equal. Values: " << vec_f2 << ", " << vec_f3;
}

TEST(Vector3DTests, SubscriptOperator) {
  vec3f vec_f1(2.5f, 3.5f, 8.5f);
  EXPECT_EQ(vec_f1[0], 2.5f) << "Vector x value was not read correctly (expected: 2.5f). Value: " << vec_f1[0];
  EXPECT_EQ(vec_f1[1], 3.5f) << "Vector y value was not read correctly (expected: 3.5f). Value: " << vec_f1[1];
  EXPECT_EQ(vec_f1[2], 8.5f) << "Vector z value was not read correctly (expected: 8.5f). Value: " << vec_f1[2];
  vec_f1[0] = 4.5f;
  vec_f1[1] = 6.5f;
  vec_f1[2] = 7.5f;
  EXPECT_EQ(vec_f1[0], 4.5f) << "Vector x value was not written correctly. Subscript operator possibly returned deep copy of x instead of reference to x (expected: 4.5f). Value: " << vec_f1[0];
  EXPECT_EQ(vec_f1[1], 6.5f) << "Vector y value was not written correctly. Subscript operator possibly returned deep copy of y instead of reference to y (expected: 6.5f). Value: " << vec_f1[1];
  EXPECT_EQ(vec_f1[2], 7.5f) << "Vector z value was not written correctly. Subscript operator possibly returned deep copy of z instead of reference to z (expected: 7.5f). Value: " << vec_f1[2];
}

TEST(Vector3DTests, MathematicalOperators) {
  vec3i vec1(2, 3, 8);
  vec3i vec2(9, 6, 5);
  vec3i plus_vec1 = +vec1;
  vec3i minus_vec1 = -vec1;
  EXPECT_EQ(plus_vec1, vec3i(2, 3, 8)) << "Unary plus operator returned incorrect result (expected (2, 3, 8)). Values: " << plus_vec1;
  EXPECT_EQ(minus_vec1, vec3i(-2, -3, -8)) << "Unary minus operator returned incorrect result (expected (-2, -3, -8)). Values: " << minus_vec1;
  vec3i sum = vec1 + vec2;
  vec3i difference = vec2 - vec1;
  EXPECT_EQ(sum, vec3i(11, 9, 13)) << "Binary sum operator returned incorrect result (expected (11, 9, 13)). Values: " << sum;
  EXPECT_EQ(difference, vec3i(7, 3, -3)) << "Binary difference operator returned incorrect result (expected (7, 3, -3)). Values: " << difference;
  int s = 3;
  vec3i product = vec1 * s;
  vec3i division = vec2 / s;
  EXPECT_EQ(product, vec3i(6, 9, 24)) << "Binary multiplication operator returned incorrect result (expected (6, 9, 24)). Values: " << product;
  EXPECT_EQ(division, vec3i(3, 2, 1)) << "Binary division operator returned incorrect result (expected (3, 2, 1)). Values: " << division;
}

TEST(Vector3DTests, CompoundAssignmentOperators) {
  vec3i vec(2, 3, 8);
  vec += vec3i(5, 3, 1);
  EXPECT_EQ(vec, vec3i(7, 6, 9)) << "Sum assignment operator returned incorrect result (expected (7, 6, 9)). Values: " << vec;
  vec -= vec3i(4, 1, 5);
  EXPECT_EQ(vec, vec3i(3, 5, 4)) << "Difference assignment operator returned incorrect result (expected (3, 5, 4)). Values: " << vec;
  vec *= 2;
  EXPECT_EQ(vec, vec3i(6, 10, 8)) << "Multiplication assignment operator returned incorrect result (expected (6, 10, 8)). Values: " << vec;
  vec /= 2;
  EXPECT_EQ(vec, vec3i(3, 5, 4)) << "Division assignment operator returned incorrect result (expected (3, 5, 4)). Values: " << vec;
}

TEST(Vector3DTests, StringConversion) {
  vec3i vec(2, 3, 8);
  std::stringstream ss;
  ss << vec;
  std::string s = ss.str();
  EXPECT_STREQ(s.c_str(), "Vector3D(2, 3, 8)") << "String conversion returned incorrect string (expected \"v(2, 3, 8)\"). String: \"" << vec << "\"";
}

TEST(Vector3DTests, ScalarProduct) {
  vec3i vec1(2, 3, 8);
  vec3i vec2(4, 6, 7);
  EXPECT_EQ(vec1.ScalarProduct(vec2), 2 * 4 + 3 * 6 + 8 * 7) << "Scalar product is incorrect (expected (82)). Value: " << vec1.ScalarProduct(vec2);
  EXPECT_EQ(vec1 * vec2, 2 * 4 + 3 * 6 + 8 * 7) << "Scalar product is incorrect (expected (82)). Value: " << vec1 * vec2;
}

TEST(Vector3DTests, CrossProduct) {
  vec3i vec1(2, 3, 8);
  vec3i vec2(4, 6, 7);
  vec3i vec_cp = vec1.CrossProduct(vec2);
  EXPECT_EQ(vec_cp, vec3i(-27, 18, 0)) << "Cross product is incorrect (expected (-27, 18, 0)). Value: " << vec_cp;
  EXPECT_EQ(vec1 * vec_cp, 0) << "A cross product is orthogonal to its forming vectors. The scalar product should thus be 0. Value: " << vec1 * vec_cp;
  EXPECT_EQ(vec2 * vec_cp, 0) << "A cross product is orthogonal to its forming vectors. The scalar product should thus be 0. Value: " << vec2 * vec_cp;
}

TEST(Vector3DTests, OrthogonalityCollinearity) {
  vec3i vec1(2, 3, 8);
  vec3i vec2(4, 6, 7);
  vec3i vec1_o1 = vec3i(-27, 18, 0);
  vec3i vec1_o2 = vec3i(27, -18, 0);
  vec3i vec1_o3 = vec3i(-54, 36, 0);
  vec3i vec1_cl1 = vec3i(2, 3, 8);
  vec3i vec1_cl2 = vec3i(-2, -3, -8);
  vec3i vec1_cl3 = vec3i(4, 6, 16);
  EXPECT_FALSE(vec1.IsOrthogonal(vec2)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o1)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o2)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_TRUE(vec1.IsOrthogonal(vec1_o3)) << "Two orthogonal vectors falsely identified as being non-orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl1)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl2)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsOrthogonal(vec1_cl3)) << "Two non-orthogonal vectors falsely identified as being orthogonal.";
  EXPECT_FALSE(vec1.IsCollinear(vec2)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o1)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o2)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_FALSE(vec1.IsCollinear(vec1_o3)) << "Two non-collinear vectors falsely identified as being collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl1)) << "Two collinear vectors falsely identified as being non-collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl2)) << "Two collinear vectors falsely identified as being non-collinear.";
  EXPECT_TRUE(vec1.IsCollinear(vec1_cl3)) << "Two collinear vectors falsely identified as being non-collinear.";
}

TEST(Vector3DTests, LengthCalculation) {
  vec3i vec_i(2, 3, 8);
  EXPECT_EQ(vec_i.LengthSquared(), 77) << "Squared length is incorrect (expected (77)). Value: " << vec_i.LengthSquared();
  EXPECT_EQ(vec_i.Length(), 8) << "Length is incorrect (expected (8)). Value: " << vec_i.Length();
  vec3f vec_f(2., 3.f, 8.f);
  EXPECT_EQ(vec_f.LengthSquared(), 77.f) << "Squared length is incorrect (expected (77.f)). Value: " << vec_f.LengthSquared();;
  EXPECT_EQ(vec_f.Length(), 8.77496438739f) << "Length is incorrect (expected (8.77496438739f)). Value: " << vec_f.Length();
}

TEST(Vector3DTests, Normalization) {
  vec3f vec(2.f, 3.f, 8.f);
  vec3f vec_n = vec.Normalize();
  vec3f vec_n_neg = (-vec).Normalize();
  EXPECT_EQ(vec_n, vec3f(0.2279211529f, 0.34188172938f, 0.91168461168f)) << "Normalized vector is incorrect (expected (0.2279211529f, 0.34188172938f, 0.91168461168f)). Value: " << vec_n;
  EXPECT_EQ(vec_n.Length(), 1.f) << "Length of a normalized vector should be 1. Value: " << vec_n.Length();
  EXPECT_EQ(vec_n_neg, vec3f(-0.2279211529f, -0.34188172938f, -0.91168461168f)) << "Normalized vector is incorrect (expected (-0.2279211529f, -0.34188172938f, -0.91168461168f)). Possible error with negative component values. Value: " << vec_n_neg;
  EXPECT_EQ(vec_n_neg.Length(), 1.f) << "Length of a normalized vector should be 1. Possible error with negative component values. Value: " << vec_n_neg.Length();
}

TEST(Vector3DTests, Projection) {
  vec3f vec(2.f, 3.f, 8.f);
  vec3f vec_x(1.f, 0.f, 0.f);
  vec3f vec_neg_y(0.f, -1.f, 0.f);
  EXPECT_EQ(vec.Project(vec_x), vec3f(2.f, 0.f, 0.f)) << "Vector projection onto x-axis is incorrect (expected (2.f, 0.f, 0.f)). Value: " << vec.Project(vec_x);
  EXPECT_EQ(vec.Project(vec_neg_y), vec3f(0.f, 3.f, 0.f)) << "Vector projection onto negative y-axis is incorrect (expected (0.f, 3.f, 0.f)). Possible error with negative components in projection vectors. Value: " << vec.Project(vec_neg_y);
  EXPECT_EQ(vec.Project(vec_x * 2), vec3f(2.f, 0.f, 0.f)) << "Vector projection onto non-normalized x-axis is incorrect (expected (2.f, 0.f, 0.f)). Possible error with non-unit projection vectors. Value: " << vec.Project(vec_x * 2);
  EXPECT_EQ(vec.Project(vec), vec3f(2.f, 3.f, 8.f)) << "Vector projection onto self should result in identity operation (expected (2.f, 3.f. 8.f)). Value: " << vec.Project(vec);
}