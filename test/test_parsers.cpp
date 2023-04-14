#include <gtest/gtest.h>
#include "polynomial.h"
#include "parsers.h"

// Test parsing a polynomial with a single monomial
TEST(PolynomialParserTest, SingleMonomial) {
	std::string input = "p1 = -2x^2y^3z^1";
	auto poly_map = parse_equation(input);

	// Test polynomial map size
	EXPECT_EQ(poly_map.size(), 1);

	// Test polynomial name and monomial count
	EXPECT_EQ(poly_map.count("p1"), 1);
	EXPECT_EQ(poly_map["p1"].size(), 1);

	// Test monomial coefficient and exponents
	EXPECT_EQ(poly_map["p1"][0].coef, -2.0);
	EXPECT_EQ(poly_map["p1"][0].a, 2);
	EXPECT_EQ(poly_map["p1"][0].b, 3);
	EXPECT_EQ(poly_map["p1"][0].c, 1);
}

// Test parsing a polynomial with multiple monomials
TEST(PolynomialParserTest, MultipleMonomials) {
	std::string input = "p2 = 2x^2y^3z^1 - 3x^1y^1z^1 + 5x^3";
	auto poly_map = parse_equation(input);

	// Test polynomial map size
	EXPECT_EQ(poly_map.size(), 1);

	// Test polynomial name and monomial count
	EXPECT_EQ(poly_map.count("p2"), 1);
	EXPECT_EQ(poly_map["p2"].size(), 3);

	// Test monomial coefficients and exponents
	EXPECT_EQ(poly_map["p2"][0].coef, 2.0);
	EXPECT_EQ(poly_map["p2"][0].a, 2);
	EXPECT_EQ(poly_map["p2"][0].b, 3);
	EXPECT_EQ(poly_map["p2"][0].c, 1);

	EXPECT_EQ(poly_map["p2"][1].coef, -3.0);
	EXPECT_EQ(poly_map["p2"][1].a, 1);
	EXPECT_EQ(poly_map["p2"][1].b, 1);
	EXPECT_EQ(poly_map["p2"][1].c, 1);

	EXPECT_EQ(poly_map["p2"][2].coef, 5.0);
	EXPECT_EQ(poly_map["p2"][2].a, 3);
	EXPECT_EQ(poly_map["p2"][2].b, 0);
	EXPECT_EQ(poly_map["p2"][2].c, 0);
}

// Test parsing a polynomial with coefficient 1 and omitted exponent
TEST(PolynomialParserTest, Coeff1OmittedExponent) {
	std::string input = "p3 = xy^3z";
	auto poly_map = parse_equation(input);

	// Test polynomial map size
	EXPECT_EQ(poly_map.size(), 1);

	// Test polynomial name and monomial count
	EXPECT_EQ(poly_map.count("p3"), 1);
	EXPECT_EQ(poly_map["p3"].size(), 1);

	// Test monomial coefficient and exponents
	EXPECT_EQ(poly_map["p3"][0].coef, 1.0);
	EXPECT_EQ(poly_map["p3"][0].a, 1);
	EXPECT_EQ(poly_map["p3"][0].b, 3);
	EXPECT_EQ(poly_map["p3"][0].c, 1);
}

// Test parsing a polynomial with negative coefficient

TEST(PolynomialParserTest, ParseSingleMonomial) {

	polynomial p1 = parse_equation("p1 = x^2y^3z^1")["p1"];
	EXPECT_EQ(p1, polynomial({ monomial(1, 2, 3, 1) }));

	polynomial p2 = parse_equation("p2 = -x^2y^3z^1")["p2"];
	EXPECT_EQ(p2, polynomial({ monomial(-1, 2, 3, 1) }));

	polynomial p3 = parse_equation("p3 = 1.5x^2y^3z^1")["p3"];
	EXPECT_EQ(p3, polynomial({ monomial(1.5, 2, 3, 1) }));

	polynomial p4 = parse_equation("p4 = -1.5x^2y^3z^1")["p4"];
	EXPECT_EQ(p4, polynomial({ monomial(-1.5, 2, 3, 1) }));

	polynomial p5 = parse_equation("p5 = xy")["p5"];
	EXPECT_EQ(p5, polynomial({ monomial(1, 1, 1, 0) }));

	polynomial p6 = parse_equation("p6 = -xy")["p6"];
	EXPECT_EQ(p6, polynomial({ monomial(-1, 1, 1, 0) }));

	polynomial p7 = parse_equation("p7 = 1.0xy")["p7"];
	EXPECT_EQ(p7, polynomial({ monomial(1, 1, 1, 0) }));

	polynomial p8 = parse_equation("p8 = -1.0xy")["p8"];
	EXPECT_EQ(p8, polynomial({ monomial(-1, 1, 1, 0) }));

	polynomial p9 = parse_equation("p9 = -z")["p9"];
	EXPECT_EQ(p9, polynomial({ monomial(-1, 0, 0, 1) }));

	polynomial p10 = parse_equation("p10 = z")["p10"];
	EXPECT_EQ(p10, polynomial({ monomial(1, 0, 0, 1) }));
}

TEST(PolynomialParserTest, ParseMultipleMonomials) {
	polynomial p1 = parse_equation("p1 = 12x^2y^1z^3+ 9x^3y^3z^3 + x^2y^3 - z")["p1"];
	EXPECT_EQ(p1, polynomial({ monomial(9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(-1, 0, 0, 1) }));

	polynomial p2 = parse_equation("p2 = -12x^2y^1z^3-9x^3y^3z^3-x^2y^3+z")["p2"];
	EXPECT_EQ(p2, polynomial({ monomial(-9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(-12, 2, 1, 3), monomial(-1, 0, 0, 1) }));

	polynomial p3 = parse_equation("p3 = 12x^2y^1z^3 - 9x^3y^3z^3 + x^2y^3 + z")["p3"];
	EXPECT_EQ(p3, polynomial({ monomial(-9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(1, 0, 0, 1) }));
}