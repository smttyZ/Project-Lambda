// NumbersTests.cpp
// Project Lambda - Unit tests for numeric helper types

#include <gtest/gtest.h>

#include "math/Numbers.hpp"

namespace lambda::math {

TEST(Numbers_Real, BasicArithmetic) {
    const Real a{1.5};
    const Real b{2.25};

    EXPECT_DOUBLE_EQ(static_cast<double>((a + b).value), 3.75);
    EXPECT_DOUBLE_EQ(static_cast<double>((a - b).value), -0.75);
    EXPECT_DOUBLE_EQ(static_cast<double>((a * b).value), 3.375);
    EXPECT_DOUBLE_EQ(static_cast<double>((b / a).value), 1.5);
}

TEST(Numbers_Integer, ModulusAndConversion) {
    const Integer lhs{10};
    const Integer rhs{3};
    EXPECT_EQ((lhs % rhs).value, 1);

    const Real converted = static_cast<Real>(lhs);
    EXPECT_DOUBLE_EQ(converted.value, 10.0);
}

TEST(Numbers_Rational, NormalizesAndAdds) {
    const Rational value{ Integer{-2}, Integer{-4} };
    EXPECT_EQ(value.numerator.value, 1);
    EXPECT_EQ(value.denominator.value, 2);

    const Rational lhs{ Integer{1}, Integer{3} };
    const Rational rhs{ Integer{1}, Integer{6} };
    const Rational sum = lhs + rhs;
    EXPECT_EQ(sum.numerator.value, 1);
    EXPECT_EQ(sum.denominator.value, 2);
}

TEST(Numbers_Rational, DivisionByZeroThrows) {
    const Rational lhs{ Integer{1}, Integer{2} };
    const Rational zero{ Integer{0} };
    EXPECT_THROW(lhs / zero, std::runtime_error);
}

TEST(Numbers_Complex, MultiplicationAndDivision) {
    const Complex lhs{ Real{1.0}, Real{2.0} };
    const Complex rhs{ Real{3.0}, Real{-1.0} };

    const Complex product = lhs * rhs;
    EXPECT_DOUBLE_EQ(product.real.value, 5.0);
    EXPECT_DOUBLE_EQ(product.imaginary.value, 5.0);

    const Complex quotient = product / rhs;
    EXPECT_NEAR(quotient.real.value, lhs.real.value, 1e-12);
    EXPECT_NEAR(quotient.imaginary.value, lhs.imaginary.value, 1e-12);
}

} // namespace lambda::math
