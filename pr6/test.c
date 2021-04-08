#include "pr6.c"
#include "/home/student/googletest/include/gtest/gtest.h" //your path to gtest.h
/*********************************************************/
TEST(GoodWork, oneBrackets)
{
	char str[] = "Hello{Me - I}, [World], (break!)\n";
	ASSERT_EQ(correctBrackets(str), 1);
}
/*********************************************************/
TEST(GoodWork, moreBrackets)
{
	char str[] = "Hello{{Me - I}}, ({[World]}), ([{(break!)}])\n";
	ASSERT_EQ(correctBrackets(str), 1);
}
/*********************************************************/
TEST(ErrorWork, BracketsBegin)
{
        char str[] = "Hello[{Me - I}, [World], (break!)\n";
	ASSERT_EQ(correctBrackets(str), 0);
}
/*********************************************************/
TEST(ErrorWork, BracketsEnd)
{
	char str[] = "Hello{Me - I}, [World], (break!)}\n";
	ASSERT_EQ(correctBrackets(str), 0);
}
/*********************************************************/
TEST(ErrorWork, BracketsBetweenBegin)
{
        char str[] = "Hello[{Me - I}, [{World], (break!)\n";
	ASSERT_EQ(correctBrackets(str), 0);
}
/*********************************************************/
TEST(ErrorWork, BracketsBetweenEnd)
{
        char str[] = "Hello[{Me - I}, [World)], (break!)\n";
        ASSERT_EQ(correctBrackets(str), 0);
}
/*********************************************************/
TEST(ErrorWork, BracketsBetweenDifferent)
{
	char str[] = "Hello[{Me - I}, [{World)], (break!)\n";
	ASSERT_EQ(correctBrackets(str), 0);
}
/*********************************************************/
TEST(ErrorProgramm, NullStr)
{
	ASSERT_EQ(correctBrackets(NULL), -1);
}
/*********************************************************/
int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
/*********************************************************/
