#include <gtest\gtest.h>
#include "..\src\numeric_comparison.h"

using namespace j::math;

//
// NumericComparisonTests
//
TEST(NumericComparisonTests, Constructors) {
  float f1 = 0.12345678910f;
  float f2 = 0.12345678910f;
  float f3 = -0.12345678910f;
  float f4 = 0.12345678765f;
  float f5 = 0.12343210123f;
  float f6 = -0.12343210123f;
  EXPECT_TRUE(AreEqual(f1, f2)) << "Two identical floats were considered non-equal: " << f1 << " and " << f2;
  EXPECT_FALSE(AreEqual(f1, f3)) << "Two opposite floats were considered equal: " << f1 << " and " << f3;
  EXPECT_TRUE(AreEqual(f1, f4)) << "Two near-identical floats were considered non-equal: " << f1 << " and " << f4;
  EXPECT_FALSE(AreEqual(f1, f5)) << "Two slightly different floats were considered equal: " << f1 << " and " << f5;
  EXPECT_FALSE(AreEqual(f1, f6)) << "Two slightly different and opposite floats were considered equal: " << f1 << " and " << f6;
}