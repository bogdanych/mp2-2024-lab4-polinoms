#include <gtest.h>
#include "Polynoms.h"

TEST(Polynoms, default_polynomial) {
    Polynom<int> a, b("0");
    ASSERT_EQ(a == b, 1);
}

TEST(Polynoms, pol_like_const) {
    Polynom<int> a("67");
    ASSERT_EQ(a.to_string(), "67");
}

TEST(Polynoms, use_other_letters) {
    ASSERT_ANY_THROW(Polynom<int>("u"));
}

TEST(Polynoms, correct_initialize) {
    Polynom<int> p1("xyz");
    List<int> lst;
    lst.push_back(1, 111);
    Polynom<int> p2(lst);
    ASSERT_EQ(p1 == p2, 1);
}

TEST(Polynoms, correct_initialize_with_degrees) {
    Polynom<int> p1("x^1y^2z^3");
    List<int> lst;
    lst.push_back(1, 123);
    Polynom<int> p2(lst);
    ASSERT_EQ(p1 == p2, 1);
}

TEST(Polynoms, incorrect_degree) {
    ASSERT_ANY_THROW(Polynom<int>("x^10"));
}

TEST(Polynoms, simple_polynom_like_sum) {
    Polynom<int> p1("xyz + 10xyz");
    Polynom<int> p2("11xyz");
    ASSERT_EQ(p1 == p2, 1);
}

TEST(Polynoms, sort) {
    Polynom<int> p("xyz + xy + xz + yz + x + y + z + 1");
    ASSERT_EQ(p.to_string(), "1 + z + y + yz + x + xz + xy + xyz");
}

TEST(Polynoms, sum_other_polynoms) {
    Polynom<int> p1("xyz");
    Polynom<int> p2("xz");
    ASSERT_EQ((p1 + p2).to_string(), "xz + xyz");
}

TEST(Polynoms, mul_to_const) {
    Polynom<int> p("x");
    ASSERT_EQ((p * 5).to_string(), "5x");
}

TEST(Polynoms, get_zero_by_sub) {
    Polynom<int> p("xyz - xyz");
    ASSERT_EQ(p.to_string(), "0");
}

TEST(Polynoms, get_zero_by_mul_to_pol) {
    Polynom<int> p1("6787x^9y^9z^9");
    Polynom<int> p2("0");
    ASSERT_EQ((p1*p2).to_string(), "0");
}

TEST(Polynoms, inverse_polynomials_sum) {
    Polynom<int> p1("2 + xyz");
    Polynom<int> p2("- 2 - xyz");
    ASSERT_EQ((p1 + p2).to_string(), "0");
}

TEST(Polynoms, polynomial_mul) {
    Polynom<int> p1("5xyz");
    Polynom<int> p2("5xyz");
    ASSERT_EQ((p1 * p2).to_string(), "25x^2y^2z^2");
}

TEST(Polynoms, mul_to_polynom_const) {
    Polynom<int> p1("5");
    Polynom<int> p2("xyz");

    ASSERT_EQ((p1 * p2).to_string(), "5xyz");
}


TEST(Polynoms, pol_to_power) {
    Polynom<int> p("x + 1");
    ASSERT_EQ((p * p).to_string(), "1 + 2x + x^2");
    ASSERT_EQ((p * p * p).to_string(), "1 + 3x + 3x^2 + x^3");
    ASSERT_EQ((p * p * p * p).to_string(), "1 + 4x + 6x^2 + 4x^3 + x^4");
}

TEST(Polynoms, cannot_multiply_with_overflow) {
    Polynom<int> p1("x^5");
    Polynom<int> p2("x^5 - z^3");
    ASSERT_ANY_THROW(p1 * p2);
    
} 