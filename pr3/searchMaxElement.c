#include <stdio.h>  
#include "/storage/emulated/0/CodingC/googletest/include/gtest/gtest.h"
/*************************************/
int searchIndexMaxElementInt(int* arr, int sizeArr)
{
    if(sizeArr <= 0)
    {   
        printf("error of size\n");
        return -1;
    }
    if(arr == NULL)
    {
        printf("error of pointer\n");
        return -2;
    }
    int indexMaxElement = 0;
    for(int index = 1; index < sizeArr; index++)
    {
        if(arr[index] > arr[indexMaxElement])
        {
            indexMaxElement = index;
        }
    }
    return indexMaxElement;
}
/*************************************/
int searchIndexMaxElementChar(char* arr, int sizeArr)
{
    if(sizeArr <= 0)
    {   
        printf("error of size\n");
        return -1;
    }
    if(arr == NULL)
    {
        printf("error of pointer\n");
        return -2;
    }
    int indexMaxElement = 0;
    for(int index = 1; index < sizeArr; index++)
    {
        if(arr[index] > arr[indexMaxElement])
        {
            indexMaxElement = index;
        }
    }
    return indexMaxElement;
}
/*************************************/
int searchIndexMaxElementDouble(double* arr, int sizeArr)
{
    if(sizeArr <= 0)
    {   
        printf("error of size\n");
        return -1;
    }
    if(arr == NULL)
    {
        printf("error of pointer\n");
        return -2;
    }
    int indexMaxElement = 0;
    for(int index = 1; index < sizeArr; index++)
    {
        if(arr[index] > arr[indexMaxElement])
        {
            indexMaxElement = index;
        }
    }
    return indexMaxElement;
}
/*************************************/
TEST(indexTest, intTest)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    int* pointerNull = NULL;
    EXPECT_EQ(4,searchIndexMaxElementInt(numbers, 8));
    EXPECT_EQ(-1,searchIndexMaxElementInt(numbers, -2));
    EXPECT_EQ(-1,searchIndexMaxElementInt(numbers, 0));
    EXPECT_EQ(-2,searchIndexMaxElementInt(pointerNull, 8));
}
/*************************************/
TEST(indexTest, charTest)
{
    char numbers[] = { '5', 'a', 'S', 'F', '8', '\0', 'b', 'z', '-'};
    char* pointerNull = NULL;
    EXPECT_EQ(7,searchIndexMaxElementChar(numbers, 9));
    EXPECT_EQ(-1,searchIndexMaxElementChar(numbers, 0));
    EXPECT_EQ(-1,searchIndexMaxElementChar(numbers, -3));
    EXPECT_EQ(-2,searchIndexMaxElementChar(pointerNull, 9));
}
/*************************************/
TEST(indexTest, doubleTest)
{
    double numbers[] = { 1., 95., 50., 7., 68., 81., 6., 90.};
    double* pointerNull = NULL;
    EXPECT_EQ(1,searchIndexMaxElementDouble(numbers, 8));
    EXPECT_EQ(-1,searchIndexMaxElementDouble(numbers, 0));
    EXPECT_EQ(-1,searchIndexMaxElementDouble(numbers, -8));
    EXPECT_EQ(-2,searchIndexMaxElementDouble(pointerNull, 8));
}
/*************************************/
TEST(sizeType, sizeInt)
{
    EXPECT_EQ(4,sizeof(int));
}
/*************************************/
TEST(sizeType, sizeChar)
{
    EXPECT_EQ(1,sizeof(char));
}
/*************************************/
TEST(sizeType, sizeDouble)
{
    EXPECT_EQ(8,sizeof(double));
}
/*************************************/
TEST(sizeType, sizeUnsignedLongLong)
{
    EXPECT_EQ(8,sizeof(unsigned long long));
}
/*************************************/
TEST(sizeType, sizeUnsignedlong)
{
    EXPECT_EQ(8,sizeof(unsigned long));
}
/*************************************/
TEST(sizeType, sizeFloat)
{
    EXPECT_EQ(4,sizeof(float));
}
/*************************************/
TEST(sizeType, sizeLongLong)
{
    EXPECT_EQ(8,sizeof(long long));
}
/*************************************/
TEST(sizeType, size_t)
{
    EXPECT_EQ(8,sizeof(size_t));
}
/*************************************/
TEST(sizeType, sizeUnsignedInt)
{
    EXPECT_EQ(4,sizeof(unsigned int));
}
/*************************************/
TEST(sizeType, sizeShort)
{
    EXPECT_EQ(2,sizeof(short));
}
/*************************************/
TEST(sizeType, sizeUnsignedChar)
{
    EXPECT_EQ(1,sizeof(unsigned char));
}
/*************************************/
TEST(sizeType, sizeIntPointer)
{
    EXPECT_EQ(8,sizeof(int*));
}
/*************************************/
TEST(sizeType, sizeCharPointer)
{
    EXPECT_EQ(8,sizeof(char*));
}
/*************************************/
TEST(sizeType, sizeDoublePointer)
{
    EXPECT_EQ(8,sizeof(double*));
}
/*************************************/
TEST(sizeType, sizeVoidPointer)
{
    EXPECT_EQ(8,sizeof(void*));
}
/*************************************/
TEST(sizeType, sizeIntPointerPointer)
{
    EXPECT_EQ(8,sizeof(int**));
}
/*************************************/
TEST(sizeType, sizeCharPointerPointer)
{
    EXPECT_EQ(8,sizeof(char**));
}
/*************************************/
TEST(sizeType, sizeDoublePointerPointer)
{
    EXPECT_EQ(8,sizeof(double**));
}
/*************************************/
TEST(arrTest, sizeArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    EXPECT_EQ(32,sizeof(numbers));
}
/*************************************/
TEST(arrTest, sizeFirstElement)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    EXPECT_EQ(4,sizeof(numbers[0]));
}
/*************************************/
TEST(arrTest, countElementsInArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    EXPECT_EQ(8,sizeof(numbers)/4);
}
/*************************************/
TEST(arrTest, equalSizePointerAndArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    int* pointerOnArr = numbers;
    ASSERT_EQ(sizeof(numbers), sizeof(pointerOnArr));
    ASSERT_NE(sizeof(numbers), sizeof(pointerOnArr));
}
/*************************************/
TEST(arrTest, firstTestEqualPointerOnArrAndPointerOnFirstItemAndArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    int* pointerOnArr = numbers;
    EXPECT_TRUE(numbers == pointerOnArr && pointerOnArr == &numbers[0]);
}
/*************************************/
TEST(arrTest, secondTestEqualPointerOnArrAndPointerOnFirstItemAndArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    int* pointerOnArr = numbers;
    EXPECT_TRUE(&pointerOnArr[1] == pointerOnArr+1 && pointerOnArr+1 == &numbers[1]);
}
/*************************************/
TEST(arrTest, ThirdTestEqualPointerOnArrAndPointerOnFirstItemAndArr)
{
    int numbers[] = { 1, 2, 5, 7, 65, 8, 6, 65};
    int* pointerOnArr = numbers;
    ASSERT_TRUE(numbers[1] == *(pointerOnArr+1) && *(pointerOnArr+1) == pointerOnArr[1] && pointerOnArr[1]==1[pointerOnArr]);
}
/*************************************/
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
/*************************************/