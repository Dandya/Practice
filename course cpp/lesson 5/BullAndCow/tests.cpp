#include "fuctions.h"
#include "/home/alex/gtest/include/gtest/gtest.h"

TEST(Main, SearchBullOrCowRU)
{
    std::u16string word = {'П','р','и','в','е','т','\0'};
    EXPECT_EQ(searchBullOrCowRU('и',2,word), 1);
    EXPECT_EQ(searchBullOrCowRU('р', 2, word), 0);
    EXPECT_EQ(searchBullOrCowRU('а', 3, word), -1);
}

TEST(Main, SearchBullOrCowEN)
{
    std::string word = "Hello";
    EXPECT_EQ(searchBullOrCowEN('e',1,word), 1);
    EXPECT_EQ(searchBullOrCowEN('H', 2, word), 0);
    EXPECT_EQ(searchBullOrCowEN('B', 3, word), -1);
}

TEST(Main, CompareWordsRU)
{
    std::u16string word1 =  {'П','р','и','в','е','т','\0'};
    std::u16string word2 =  {'П','и','л','о','т','ы','\0'};
    int countBulls{0}, countCows{0};
    compareWordsRU(word1, word2, &countBulls, &countCows);
    EXPECT_EQ(countCows, 2);
    EXPECT_EQ(countBulls, 1);
}

TEST(Main, CompareWordsEN)
{
    std::string word1 = "Hello";
    std::string word2 = "Henry";
    int countBulls{0}, countCows{0};
    compareWordsEN(word1, word2, &countBulls, &countCows);
    EXPECT_EQ(countCows, 0);
    EXPECT_EQ(countBulls, 2);
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
