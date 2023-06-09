#include "gtest/gtest.h"
#include "polynomial.h"
#include "ordered_table.h"

TEST(TOrderedTab1e, test_test) {
	using myType = TOrderedTab1e<std::string, polynomial>;
	ASSERT_NO_THROW(myType a);
}						 

TEST(TOrderedTab1e, Empty) {
    TOrderedTab1e<int, double> table;
    EXPECT_EQ(table.size(), 0);
}

TEST(TOrderedTab1e, OperatorBracket) {
    TOrderedTab1e<std::string, int> table;

    // Insert key-value pairs
    table.Insert("One", 1);
    table.Insert("Two", 2);
    table.Insert("Three", 3);

    // Access existing key
    EXPECT_EQ(*table["Two"], 2);

    // Access non-existing key
    EXPECT_EQ(table["Four"], nullptr);
}

TEST(TOrderedTab1e, Insert) {
    TOrderedTab1e<int, std::string> table;

    // Insert key-value pairs
    table.Insert(2, "Two");
    table.Insert(1, "One");
    table.Insert(3, "Three");

    // Verify the size of the table
    EXPECT_EQ(table.size(), 3);

    // Verify the inserted values
    EXPECT_EQ(*table[1], "One");
    EXPECT_EQ(*table[2], "Two");
    EXPECT_EQ(*table[3], "Three");

    // Insert an existing key should change the table
    table.Insert(2, "New Two");
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(*table[2], "New Two");

    // Insert a new key-value pair
    table.Insert(4, "Four");
    EXPECT_EQ(table.size(), 4);
    EXPECT_EQ(*table[4], "Four");
}

TEST(TOrderedTab1e, Delete) {
    TOrderedTab1e<int, std::string> table;

    // Insert key-value pairs
    table.Insert(1, "One");
    table.Insert(2, "Two");
    table.Insert(3, "Three");

    // Verify the initial size of the table
    EXPECT_EQ(table.size(), 3);

    // Delete an existing key
    table.Delete(2);
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table[2], nullptr);  // Verify key no longer exists

    // Delete a non-existing key should not change the table
    table.Delete(4);
    EXPECT_EQ(table.size(), 2);

    // Delete another existing key
    table.Delete(1);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table[1], nullptr);  // Verify key no longer exists
}

