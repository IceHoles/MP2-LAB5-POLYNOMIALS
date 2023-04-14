#include "gtest/gtest.h"
#include "polynomial.h"
#include "ordered_table.h"

TEST(TOrderedTab1e, test_test) {
	using myType = TOrderedTab1e<std::string, polynomial>;
	ASSERT_NO_THROW(myType a);
}						 
