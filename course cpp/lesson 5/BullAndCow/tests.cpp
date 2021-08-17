#include "fuctions.h"
#include "/home/alex/gtest/include/gtest/gtest.h"

TEST(Main, InputWord)
{
    std::string word = inputWord();
    std::cout << word << "-" << word.length() << std::endl;

    std::cout <<"All ok? (1 - yes, 0 - no)"<< std::endl;
    int answer = 0;
    std::cin >> answer;
    EXPECT_EQ(answer, 1);
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
    testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
