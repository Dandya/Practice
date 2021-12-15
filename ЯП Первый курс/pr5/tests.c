#include "func.c"
#include "/home/alex/gtest/include/gtest/gtest.h"

TEST(TestMaxAndMin, Char)
{
    EXPECT_EQ(-128, getCharMin());
    EXPECT_EQ(127, getCharMax());
    EXPECT_EQ(255, getUnsignedCharMax());
    EXPECT_EQ(-128, getSignedCharMin());
    EXPECT_EQ(127, getSignedCharMax());
}

TEST(TestMaxAndMin, Int)
{
    EXPECT_EQ((short int)(32767+1), getShortIntMin());
    EXPECT_EQ(32767, getShortIntMax());
    EXPECT_EQ(65535, getUnsignedShortIntMax());
    EXPECT_EQ((int)(2147483647+1), getIntMin());
    EXPECT_EQ(2147483647, getIntMax());
    EXPECT_EQ(4294967295, getUnsignedIntMax());
    EXPECT_EQ((long long int)(9223372036854775807+1), getLongIntMin());
    EXPECT_EQ(9223372036854775807, getLongIntMax());
    EXPECT_EQ((unsigned long)18446744073709551615, getUnsignedLongIntMax());
    EXPECT_EQ((long long int)(9223372036854775807+1), getLongLongIntMin());
    EXPECT_EQ(9223372036854775807, getLongLongIntMax());
    EXPECT_EQ((unsigned long long)18446744073709551615, getUnsignedLongLongIntMax());
}

TEST(TestMaxAndMin, Float)
{
    ASSERT_FLOAT_EQ((float)(3,402823466e+38F), getFloatMax());
    //ASSERT_FLOAT_EQ((1,1754944e-38F), getFloatMin()); 
}

TEST(TestMaxAndMin, Double)
{
    ASSERT_DOUBLE_EQ((double)(1,7976931348623158e+308), getDoubleMax());
    //ASSERT_DOUBLE_EQ((double)(2,2250738585072014e-308), getDoubleMin());
    ASSERT_DOUBLE_EQ((double)(1,7976931348623158e+308), getLongDoubleMax());
    //ASSERT_DOUBLE_EQ((double)(2,2250738585072014e-308), getLongDoubleMin());
}

TEST(NumAndArrInsideInBits, Int)
{
    char* number;
    int a;
    //-----------
    a = getIntMax();
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_TYPE);
    EXPECT_STREQ("01111111111111111111111111111111", number);
    free(number);
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_MEMORY);
    EXPECT_STREQ("11111111111111111111111111111110", number);
    free(number);
    //-----------
    a = getIntMin();
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_TYPE);
    EXPECT_STREQ("10000000000000000000000000000000", number);
    free(number);
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_MEMORY);
    EXPECT_STREQ("00000000000000000000000000000001", number);
    free(number);
    //-----------
    a = 237;
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_TYPE);
    EXPECT_STREQ("00000000000000000000000011101101", number);
    free(number);
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_MEMORY);
    EXPECT_STREQ("10110111000000000000000000000000", number);
    free(number);
    //-----------
    a = 0;
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_TYPE);
    EXPECT_STREQ("00000000000000000000000000000000", number);
    free(number);
    number = seeNumOrArrInsideInBits(&a, sizeof(a), MODE_MEMORY);
    EXPECT_STREQ("00000000000000000000000000000000", number);
    free(number);
    //-----------
    long long b;
    //-----------
    b = getLongLongIntMax();
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_TYPE);
    EXPECT_STREQ("0111111111111111111111111111111111111111111111111111111111111111", number);
    free(number);
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_MEMORY);
    EXPECT_STREQ("1111111111111111111111111111111111111111111111111111111111111110", number);
    free(number);
    //-----------
    b = getLongLongIntMin();
    number = seeNumOrArrInsideInBits(&b , sizeof(b), MODE_TYPE);
    EXPECT_STREQ("1000000000000000000000000000000000000000000000000000000000000000", number);
    free(number);
    number = seeNumOrArrInsideInBits(&b , sizeof(b), MODE_MEMORY);
    EXPECT_STREQ("0000000000000000000000000000000000000000000000000000000000000001", number);
    free(number);
    //-----------
    b = 4890258201;
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_TYPE);
    EXPECT_STREQ("0000000000000000000000000000000100100011011110110110101100011001", number);
    free(number);
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_MEMORY);
    EXPECT_STREQ("1001100011010110110111101100010010000000000000000000000000000000", number);
    free(number);
    //-----------
    b = 0;
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_TYPE);
    EXPECT_STREQ("0000000000000000000000000000000000000000000000000000000000000000", number);
    free(number);
    number = seeNumOrArrInsideInBits(&b, sizeof(b), MODE_MEMORY);
    EXPECT_STREQ("0000000000000000000000000000000000000000000000000000000000000000", number);
    free(number);
}

TEST(NumAndArrInsideInBits, Arr)
{
    char arr[4] = {1,2,3,4};
    char* ptr; 
    ptr = seeNumOrArrInsideInBits(arr, sizeof(arr), MODE_TYPE);
    EXPECT_STREQ("00000100000000110000001000000001", ptr);
    free(ptr);
    ptr = seeNumOrArrInsideInBits(arr, sizeof(arr), MODE_MEMORY);
    EXPECT_STREQ("10000000010000001100000000100000", ptr);
    free(ptr);
    //-----------
    unsigned long long arrL [3] = {(unsigned long long)18446744073709551615, 0, 5};
    ptr = seeNumOrArrInsideInBits(arrL, sizeof(arrL), MODE_MEMORY);
    EXPECT_STREQ("111111111111111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000000000000001010000000000000000000000000000000000000000000000000000000000000", ptr);
    free(ptr);
}

TEST(NumOrArrInsideInBytes, numberInBytes)
{
    int a = 0x248;
    char* ptr; 
    ptr = seeNumOrArrInsideInBytes(&a, sizeof(a));
    EXPECT_EQ(ptr[0], 0x48);
    EXPECT_EQ(ptr[1], 0x02);
    EXPECT_EQ(ptr[2], 0x00);
    EXPECT_EQ(ptr[3], 0x00);
    free(ptr);
}

TEST(NumAndArrInside, Errors)
{
    char* ptr = seeNumOrArrInsideInBits(NULL, 2, MODE_MEMORY);
    ASSERT_TRUE(ptr == NULL);
    int a = 0;
    ptr = seeNumOrArrInsideInBits(&a, sizeof(a), 2);
    ASSERT_TRUE(ptr == NULL);
    ptr = seeNumOrArrInsideInBits(&a, -1, MODE_TYPE);
    ASSERT_TRUE(ptr == NULL);

    ptr = seeNumOrArrInsideInBytes(NULL, 2);
    ASSERT_TRUE(ptr == NULL);
    ptr = seeNumOrArrInsideInBytes(&a, -1);
    ASSERT_TRUE(ptr == NULL);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
