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

	EXPECT_EQ(true, c1 == res1);
	EXPECT_EQ(true, c == res);
	EXPECT_EQ(true, c2 == res2);
}

TEST(polynomial, test_polynomial_diff) {
	
}

//template <class T>
//class Table_with_same_types : public ::testing::Test {
//	static T _shared;
//	T value_;
//};
//
//using MyTypes = ::testing::Types<unsigned int, int, char, polynomial, long>;
