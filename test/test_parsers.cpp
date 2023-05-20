#include <gtest/gtest.h>
#include "polynomial.h"
#include "parsers.h"

// Test parsing a polynomial with coefficient 1 and omitted exponent
TEST(PolynomialParserTest, Coeff1OmittedExponent) {
	std::string input = "p123 = xy^3z";
	auto poly_map = parse_polynomial(input);

	// Test polynomial map size
	EXPECT_EQ(poly_map.size(), 1);

	// Test polynomial name and monomial count
	EXPECT_EQ(poly_map.count("p123"), 1);
	EXPECT_EQ(poly_map["p123"].size(), 1);

	// Test monomial coefficient and exponents
	EXPECT_EQ(poly_map["p123"][0].coef, 1.0);
	EXPECT_EQ(poly_map["p123"][0].a, 1);
	EXPECT_EQ(poly_map["p123"][0].b, 3);
	EXPECT_EQ(poly_map["p123"][0].c, 1);
}

// Test parsing a polynomial with negative coefficient

TEST(PolynomialParserTest, ParseSingleMonomial) {

	polynomial p1 = parse_polynomial("p1 = x^2y^3z^1")["p1"];
	EXPECT_EQ(p1, polynomial({ monomial(1, 2, 3, 1) }));

	polynomial p2 = parse_polynomial("p2 = -x^2y^3z^1")["p2"];
	EXPECT_EQ(p2, polynomial({ monomial(-1, 2, 3, 1) }));

	polynomial p3 = parse_polynomial("p3 = 1.5x^2y^3z^1")["p3"];
	EXPECT_EQ(p3, polynomial({ monomial(1.5, 2, 3, 1) }));

	polynomial p4 = parse_polynomial("p4 = -1.5x^2y^3z^1")["p4"];
	EXPECT_EQ(p4, polynomial({ monomial(-1.5, 2, 3, 1) }));

	polynomial p5 = parse_polynomial("p5 = xy")["p5"];
	EXPECT_EQ(p5, polynomial({ monomial(1, 1, 1, 0) }));

	polynomial p6 = parse_polynomial("p6 = -xy")["p6"];
	EXPECT_EQ(p6, polynomial({ monomial(-1, 1, 1, 0) }));

	polynomial p7 = parse_polynomial("p7 = 1.0xy")["p7"];
	EXPECT_EQ(p7, polynomial({ monomial(1, 1, 1, 0) }));

	polynomial p8 = parse_polynomial("p8 = -1.0xy")["p8"];
	EXPECT_EQ(p8, polynomial({ monomial(-1, 1, 1, 0) }));

	polynomial p9 = parse_polynomial("p9 = -z")["p9"];
	EXPECT_EQ(p9, polynomial({ monomial(-1, 0, 0, 1) }));

	polynomial p10 = parse_polynomial("p10 = z")["p10"];
	EXPECT_EQ(p10, polynomial({ monomial(1, 0, 0, 1) }));
}

TEST(PolynomialParserTest, ParseMultipleMonomials) {
	polynomial p1 = parse_polynomial("p1 = 12x^2y^1z^3+ 9x^3y^3z^3 + x^2y^3 - z")["p1"];
	EXPECT_EQ(p1, polynomial({ monomial(9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(-1, 0, 0, 1) }));

	polynomial p2 = parse_polynomial("p2 = -12x^2y^1z^3-9x^3y^3z^3-x^2y^3+z")["p2"];
	EXPECT_EQ(p2, polynomial({ monomial(-9, 3, 3, 3), monomial(-1, 2, 3, 0), monomial(-12, 2, 1, 3), monomial(1, 0, 0, 1) }));

	polynomial p3 = parse_polynomial("p3 = 12x^2y^1z^3 - 9x^3y^3z^3 + x^2y^3 + z")["p3"];
	EXPECT_EQ(p3, polynomial({ monomial(-9, 3, 3, 3), monomial(1, 2, 3, 0), monomial(12, 2, 1, 3), monomial(1, 0, 0, 1) }));
}
TEST(PolynomialExpressionParserTest, ValidExpression) {
	std::map<std::string, polynomial> polynomials;
	polynomials["p1"] = parse_polynomial("p1 = 2x^2 + 3y")["p1"];
	polynomials["p2"] = parse_polynomial("p2 = 4z")["p2"];
	polynomials["p3"] = parse_polynomial("p3 = x + 2y")["p3"];
	polynomials["p4"] = parse_polynomial("p4 = x - y")["p4"];
	polynomial result = parse_expression("result = p1 * (p2 - p3) / p4", polynomials);
	polynomial expected = parse_polynomial("presult = 0")["presult"];
	EXPECT_EQ(result, expected);
}