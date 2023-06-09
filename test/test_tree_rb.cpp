#include "gtest/gtest.h"
#include "polynomial.h"
#include "tree_rb.h"

class TSearchTreeTab1eTest : public ::testing::Test {
protected:
    TSearchTreeTab1e<int, std::string> table;
};

TEST_F(TSearchTreeTab1eTest, DefaultConstructor) {
    ASSERT_EQ(nullptr, table.Find(0));
}

TEST_F(TSearchTreeTab1eTest, FindEmptyTree) {
    int key = 10;
    auto result = table.Find(key);
    ASSERT_EQ(nullptr, result);
}

TEST_F(TSearchTreeTab1eTest, InsertNodes) {
    int key1 = 10;
    std::string value1 = "Value 1";
    int key2 = 20;
    std::string value2 = "Value 2";
    table.Insert(key1, value1);
    ASSERT_EQ(value1, *(table.Find(key1)));
    table.Insert(key2, value2);
    ASSERT_EQ(value1, *(table.Find(key1)));
    ASSERT_EQ(value2, *(table.Find(key2)));
}

TEST_F(TSearchTreeTab1eTest, Insert_Find_Test) {
    table.Insert(5, "Value5");
    table.Insert(3, "Value3");
    table.Insert(7, "Value7");
    table.Insert(2, "Value2");
    EXPECT_EQ(*table.Find(5), "Value5"); 
    EXPECT_EQ(*table.Find(3), "Value3");
    EXPECT_EQ(*table.Find(7), "Value7");
    EXPECT_EQ(*table.Find(2), "Value2");
}

TEST_F(TSearchTreeTab1eTest, Insert_DuplicateKey_UpdatesValue) {
    table.Insert(2, "Two");
    table.Insert(2, "Updated Two");
    EXPECT_EQ("Updated Two", *(table.Find(2)));
}

class TSearchTreeTab1eTest1 : public ::testing::Test {
protected:
    void SetUp(){
        tree.Insert(10, "Value 10");
        tree.Insert(5, "Value 5");
        tree.Insert(15, "Value 15");
        tree.Insert(3, "Value 3");
        tree.Insert(7, "Value 7");
        tree.Insert(12, "Value 12");
        tree.Insert(18, "Value 18");
    }

    TSearchTreeTab1e<int, std::string> tree;
};

TEST_F(TSearchTreeTab1eTest1, DeleteKey) {
    tree.Delete(5);
    std::stringstream output = tree.InorderTraversal();
    std::string expectedOutput = "3 = Value 3\n7 = Value 7\n10 = Value 10\n12 = Value 12\n15 = Value 15\n18 = Value 18\n";
    EXPECT_EQ(output.str(), expectedOutput);
}