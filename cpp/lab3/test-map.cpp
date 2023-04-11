#include "map.h"
#include <gtest/gtest.h>
#include <random>

std::vector<std::string> keys1 = {"1" , "2", "3"};
std::vector<int> values1 = {1, 2, 3};

TEST(MAP, Create_Copy_Delete) {
    map<std::string, int> test_map1;
    EXPECT_TRUE(test_map1.empty());
    
    map<std::string, int> test_map2(keys1, values1);
    EXPECT_TRUE(!test_map2.empty());
    
    test_map1 = test_map2;
    EXPECT_TRUE(!test_map1.empty());
    
    test_map2.deleteAll();
    EXPECT_TRUE(test_map2.empty());
}

TEST(MAP, Balance) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    map<int, int> test_map;                

    for (int i = 0; i < 100000; ++i) {
        test_map.add(gen(), gen());  
    }

    EXPECT_TRUE(test_map.isBalanced());
}

TEST(MAP, Search_Write) { 
    map<std::string, int> test_map(keys1, values1);                

    EXPECT_TRUE(test_map.searchKey("1"));
    EXPECT_EQ(1, test_map["1"]);
    test_map["1"] = 2;
    EXPECT_EQ(2, test_map["1"]);
    try {
        EXPECT_EQ(2, test_map["10"]);
    } catch (std::invalid_argument e) {
        EXPECT_TRUE(true);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}