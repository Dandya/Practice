#include "/home/student/googletest/include/gtest/gtest.h"

TEST(FactorialTest,Negative)
{
	EXPECT_EQ(1, 1);
	ASSERT_EQ(2, sizeof(char));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
