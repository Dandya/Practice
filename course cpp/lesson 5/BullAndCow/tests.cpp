#include "/home/aleksandr/gtest/include/gtest/gtest.h"
#include "functions.h"
/*
TEST(Main, SearchBullOrCowRU)
{
    std::string word = "Привет";
    std::string letters = "ират";
    EXPECT_EQ(searchBullOrCowRU(letters[0], letters[1], 4, word), 1);
    EXPECT_EQ(searchBullOrCowRU(letters[2], letters[3], 5, word), 0);
    EXPECT_EQ(searchBullOrCowRU(letters[6], letters[7], 5, word), 0);
    EXPECT_EQ(searchBullOrCowRU(letters[4], letters[5], 3, word), -1);
}

TEST(Main, SearchBullOrCowEN)
{
    std::string word = "Hello";
    EXPECT_EQ(searchBullOrCowEN('e',1,word), 1);
    EXPECT_EQ(searchBullOrCowEN('H', 2, word), 0);
    EXPECT_EQ(searchBullOrCowEN('B', 3, word), -1);
}

TEST(Main, CompareStrRU)
{
    std::string word1 = "Привет";
    std::string word2 =  "Пилоты";
    int countBulls{0}, countCows{0};
    compareStr(word1, word2, &countBulls, &countCows, LANGUAGE_RU);
    EXPECT_EQ(countCows, 2);
    EXPECT_EQ(countBulls, 1);
}

TEST(Main, CompareStrEN)
{
    std::string word1 = "Hello";
    std::string word2 = "Henry";
    int countBulls{0}, countCows{0};
    compareStr(word1, word2, &countBulls, &countCows, LANGUAGE_EN);
    EXPECT_EQ(countCows, 0);
    EXPECT_EQ(countBulls, 2);
}

TEST(Main, RandomWordsEN)
{
    std::string word = randomWord(EASY, LANGUAGE_EN);
    std::cout << word << std::endl;
    word = randomWord(NORMAL, LANGUAGE_EN);
    std::cout << word << std::endl;
    word = randomWord(HARD, LANGUAGE_EN);
    std::cout << word << std::endl;
}

TEST(Main, RandomWordsRU)
{
    std::string word = randomWord(EASY, LANGUAGE_RU);
    std::cout << word << std::endl;
    word = randomWord(NORMAL, LANGUAGE_RU);
    std::cout << word << std::endl;
    word = randomWord(HARD, LANGUAGE_RU);
    std::cout << word << std::endl;
}*/
TEST(Main, isTrue)
{
    EXPECT_EQ(true, isTrueDifficultyLevel(EASY, 4));
    EXPECT_EQ(false, isTrueDifficultyLevel(EASY, 6));
    EXPECT_EQ(true, isTrueVariousSimbols("1234"));
    EXPECT_EQ(false, isTrueVariousSimbols("1224"));
    EXPECT_EQ(false, isTrueVariousSimbols("1214"));
    EXPECT_EQ(false, isTrueVariousSimbols("1212"));
    EXPECT_EQ(false, isTrueVariousSimbols("1233"));

}

TEST(Main, RandomDigits)
{
    std::cout << randomDigits(EASY) << std::endl;
    std::cout << randomDigits(NORMAL) << std::endl;
    std::cout << randomDigits(HARD) << std::endl;
}

TEST(Main, SearchBullOrCow)
{
    std::string num1 = "1234";
    EXPECT_EQ(searchBullOrCow('1', 0, num1), BULL);
    EXPECT_EQ(searchBullOrCow('4', 3, num1), BULL);
    EXPECT_EQ(searchBullOrCow('2', 2, num1), COW);
}

TEST(Main, CompareStr)
{
    std::string word1 = "1234";
    std::string word2 = "1325";
    int countBulls{0}, countCows{0};
    compareStr(word1, word2, &countBulls, &countCows);
    EXPECT_EQ(countCows, 2);
    EXPECT_EQ(countBulls, 1);
}



int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
