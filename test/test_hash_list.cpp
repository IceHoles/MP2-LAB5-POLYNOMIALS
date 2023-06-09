#include "gtest/gtest.h"
#include "polynomial.h"
#include "hash_list.h"

TEST(THashTab1e, TTest_test) {
	using myType = THashTab1e<std::string, double>;
	ASSERT_NO_THROW(myType a);
}

TEST(THashTab1e, DefaultConstructor) {
    THashTab1e<int, std::string> table;
    EXPECT_EQ(0, table.getSize());
}

TEST(THashTab1e, SizeConstructor) {
    THashTab1e<int, std::string> table(10);
    EXPECT_EQ(0, table.getSize());
    EXPECT_EQ(10, table.getCapacity());
}

TEST(THashTab1e, insert_and_operator_brackets) {
    THashTab1e<int, std::string> hashTable;

    // Вставка элементов в хеш-таблицу
    hashTable.insert(1, "one");
    hashTable.insert(2, "two");
    hashTable.insert(3, "three");

    // Проверка получения значений по ключу
    EXPECT_EQ(hashTable[1], "one");
    EXPECT_EQ(hashTable[2], "two");
    EXPECT_EQ(hashTable[3], "three");
}

TEST(THashTab1e, erase) {
    THashTab1e<int, std::string> table(10);
    table.insert(1, "value1");
    table.insert(2, "value2");
    table.insert(3, "value3");
    EXPECT_EQ(table.getSize(), 3);
    EXPECT_EQ(table[2], "value2");
    table.erase(2);
    EXPECT_EQ(table.getSize(), 2);
    EXPECT_ANY_THROW(table[2], "value2");
    EXPECT_EQ(table[1], "value1");
    EXPECT_EQ(table[3], "value3");
}

TEST(THashTab1e, getSize) {
    THashTab1e<int, std::string> hashTable;
    EXPECT_EQ(hashTable.getSize(), 0);
    hashTable.insert(1, "one");
    EXPECT_EQ(hashTable.getSize(), 1);
    hashTable.erase(1);
    EXPECT_EQ(hashTable.getSize(), 0);
}

class THashTable : public ::testing::Test {
protected:
    THashTab1e<int, std::string> hashTable;
    void SetUp() override {
        for (int i = 0; i < 96; ++i) {
            hashTable.insert(i, std::to_string(i));
        }
    }
};

TEST_F(THashTable, InsertAndRehash) {   
    size_t capacity = hashTable.getCapacity();
    size_t size = hashTable.getSize();
    hashTable.insert(96, "96");
    EXPECT_GT(hashTable.getCapacity(), capacity);
    EXPECT_EQ(hashTable.getSize(), size + 1);
    EXPECT_EQ(hashTable[96], "96");
    EXPECT_EQ(hashTable[14], "14");
}

