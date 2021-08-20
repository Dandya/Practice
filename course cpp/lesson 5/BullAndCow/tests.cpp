#include "fuctions.h"
#include "/home/alex/gtest/include/gtest/gtest.h"

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

TEST(Main, CompareWordsRU)
{
    std::string word1 = "Привет";
    std::string word2 =  "Пилоты";
    int countBulls{0}, countCows{0};
    compareWords(word1, word2, &countBulls, &countCows, LANGUAGE_RU);
    EXPECT_EQ(countCows, 2);
    EXPECT_EQ(countBulls, 1);
}

TEST(Main, CompareWordsEN)
{
    std::string word1 = "Hello";
    std::string word2 = "Henry";
    int countBulls{0}, countCows{0};
    compareWords(word1, word2, &countBulls, &countCows, LANGUAGE_EN);
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
}

/*TEST(Main, PROSTO)
{
    std::u16string word;
    std::cout << "Input word: ";
    std::cin >> word;
    for(int index = 0; index < word.length(); index++)
    {
        std::cout << word[index] << std::endl;
    }
}*/

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
