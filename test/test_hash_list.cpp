#include "gtest/gtest.h"
#include "polynomial.h"
#include "hash_list.h"

TEST(THashTab1e, TTest_test) {
	using myType = THashTab1e<std::string, double>;
	ASSERT_NO_THROW(myType a);
}
