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
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    map<int, int> test_map;                

    int key;
    for (int i = 0; i < 10000; ++i) {
        key = gen();
        test_map.add(key, gen());
        if(!test_map.searchKey(key)) {
            EXPECT_EQ(0, 1);
            return;
        }
        EXPECT_EQ(true, test_map.searchKey(key));  
    }

    test_map[key] = 0;
    EXPECT_EQ(0, test_map[key]);
    
    // map<std::string, int> test_map(keys1, values1);                

    // EXPECT_TRUE(test_map.searchKey("1"));
    // EXPECT_EQ(1, test_map["1"]);
    // test_map["1"] = 2;
    // EXPECT_EQ(2, test_map["1"]);
    // try {
    //     EXPECT_EQ(2, test_map["10"]);
    // } catch (std::invalid_argument e) {
    //     EXPECT_TRUE(true);
    // }
}

TEST(MAP, Delete_Key) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    map<int, int> test_map;                
    std::vector<int> keys;
    int key;
    for (int i = 0; i < 100; ++i) {
        key = gen();
        test_map.add(key, gen());
        keys.push_back(key);  
    }

    while(keys.size() != 1) {
        std::uniform_int_distribution<int> dist(0, keys.size()-1);
        try {
            int index = dist(gen);
            test_map.del(keys[index]);
            EXPECT_TRUE(test_map.isBalanced());
            keys.erase(keys.begin() + index);
        } catch(std::invalid_argument e) {
            EXPECT_TRUE(false);
        }
    }
    EXPECT_EQ(keys.size(), test_map.size());
}

TEST(MAP, Iterator_Next) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 20);
    map<int, int> test_map;                
    std::vector<int> keys;
    int key;
    for (int i = 0; i < 100; ++i) {
        key = dist(gen);
        test_map.add(key, key);
        keys.push_back(key);  
    }

    std::sort(keys.begin(), keys.end());
    for(size_t i = 0; i <  keys.size(); i++) {
        EXPECT_EQ(keys[i], *(test_map.begin()+i));
    }
}

TEST(MAP, Iterator_Back) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 20);
    map<int, int> test_map;                
    std::vector<int> keys;
    int key;
    for (int i = 0; i < 100; ++i) {
        key = dist(gen);
        test_map.add(key, key);
        keys.push_back(key);  
    }

    std::sort(keys.begin(), keys.end());
    for(int i = keys.size()-1; i >= 0; i--) {
        EXPECT_EQ(keys[i], *(test_map.begin()+i));
    }
}

TEST(MAP, Delete_Iterator) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    map<int, int> test_map;                
    std::vector<int> keys;
    int key;
    for (int i = 0; i < 100; ++i) {
        key = gen();
        test_map.add(key, gen());
        keys.push_back(key);  
    }

    std::sort(keys.begin(), keys.end());

    while(keys.size() != 1) {
        std::uniform_int_distribution<int> dist(0, keys.size()-1);
        try {
            int index = dist(gen);
            test_map.del(test_map.begin()+index);
            EXPECT_TRUE(test_map.isBalanced());
            keys.erase(keys.begin() + index);
        } catch(std::invalid_argument e) {
            EXPECT_TRUE(false);
        }
    }
    EXPECT_EQ(keys.size(), test_map.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}