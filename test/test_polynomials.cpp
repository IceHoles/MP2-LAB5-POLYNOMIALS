#include "gtest/gtest.h"
#include "polynomial.h"

TEST(polynomial, constructor_test) {
	ASSERT_NO_THROW(polynomial a);
}

TEST(polynomial, test_monomial_constructor) {
	ASSERT_NO_THROW(monomial a);
}

TEST(polynomial, test_monomial_diff) {
	monomial a(5, 3, 2, 1);
	monomial ar = a.diff('x');
	monomial resa(15, 2, 2, 1);

	monomial b;
	monomial br = b.diff('y');
	monomial resb(0, 0, 0, 0);

	monomial c(0, 2, 3, 4);
	monomial cr = c.diff('z');
	monomial resc(0, 2, 3, 3);
	EXPECT_EQ(true, ar == resa);
	EXPECT_EQ(true, br == resb);
	EXPECT_EQ(true, cr == resc);
}

TEST(polynomial, test_monomial_integ) {
	monomial a(5, 3, 2, 1);
	monomial ar = a.integ('x');
	monomial resa(5.0/4, 4, 2, 1);

	monomial b;
	monomial br = b.integ('y');
	monomial resb(1, 0, 1, 0);

	monomial c(0, 2, 3, 4);
	monomial cr = c.integ('z');
	monomial resc(0, 2, 3, 5);
	EXPECT_EQ(true, ar == resa);
	EXPECT_EQ(true, br == resb);
	EXPECT_EQ(true, cr == resc);
}

TEST(polynomial, test_monomial_multiplication) {
	monomial a(5, 3, 2, 1);
	monomial b;
	monomial c = a * b;
	monomial res(5, 3, 2, 1);

	monomial a1(5, 3, 2, 1);
	monomial b1(3, 2, 4, 6);
	monomial c1 = a1 * b1;
	monomial res1(15, 5, 6, 7);

	monomial a2(0, 0, 0, 0);
	monomial b2;
	monomial c2 = a2 * b2;
	monomial res2(0, 0, 0, 0);

	monomial a3(5, 3, 2, 1);
	monomial c3 = a3 * 2;
	monomial res3(10, 3, 2, 1);
	EXPECT_EQ(true, c1 == res1);
	EXPECT_EQ(true, c == res);
	EXPECT_EQ(true, c2 == res2);
	EXPECT_EQ(true, c3 == res3);
}

TEST(polynomial, test_polynomial_diff) {
	polynomial p{ monomial(9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(-1, 0, 0, 1) };
	p.diff('x');
	polynomial res{ monomial(27, 2, 3, 3), monomial(2, 1, 3, 0), monomial(24, 1, 1, 3) };
}

TEST(polynomial, test_polynomial_integ) {
	polynomial p{ monomial(9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(-1, 0, 0, 1) };
	p.integ('x');
	polynomial res{ monomial(2.25, 4, 3, 3), monomial(1/3, 3, 3, 0), monomial(4, 3, 1, 3),  monomial(-1, 1, 0, 1) };
}

TEST(polynomial, test_polynomial_add) {
	polynomial p1{ monomial(9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(-1, 0, 0, 1) };
	polynomial p2{ monomial(5, 3, 3, 3), monomial(-2, 2, 3, 0), monomial(4, 2, 1, 3), monomial(3, 1, 2, 1) };
	polynomial expected{ monomial(14, 3, 3, 3), monomial(-1, 2, 3, 0), monomial(16, 2, 1, 3), monomial(3, 1, 2, 1), monomial(-1, 0, 0, 1) };
	polynomial result = p1 + p2;
	EXPECT_EQ(result, expected);
}

TEST(polynomial, test_polynomial_mult) {
	polynomial p1{ monomial(2, 2, 0, 0), monomial(-3, 1, 0, 0), monomial(1, 0, 0, 0) };
	polynomial p2{ monomial(1, 1, 0, 0), monomial(2, 0, 0, 0) };
	polynomial expected{ monomial(2, 3, 0, 0), monomial(1, 2, 0, 0), monomial(-5, 1, 0, 0), monomial(2, 0, 0, 0) };
	polynomial result = p1 * p2;
	EXPECT_EQ(result, expected);
}

TEST(polynomial, test_polynomial_div) {
	polynomial dividend{ monomial(2, 2, 0, 0), monomial(-3, 1, 0, 0), monomial(1, 0, 0, 0) };
	polynomial divisor{ monomial(1, 1, 0, 0), monomial(2, 0, 0, 0) };
	polynomial expected{ monomial(2, 1, 0, 0), monomial(-7, 0, 0, 0) };
	polynomial result = dividend / divisor;
	EXPECT_EQ(result, expected);
}
