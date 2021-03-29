#include <limits.h>
#include <float.h>
#include <malloc.h>

#define MODE_TYPE 1
#define MODE_MEMORY 0

//Functions to return maximum and minimum values
/************************char*****************************/
char getCharMax()
{
	return CHAR_MAX;
}
/*********************************************************/
char getCharMin()
{
	return CHAR_MIN;
}
/*********************************************************/
signed char getSignedCharMax()
{
	return SCHAR_MAX;
}
/*********************************************************/
signed char getSignedCharMin()
{
	return SCHAR_MIN;
}
/*********************************************************/
unsigned char getUnsignedCharMax()
{
	return UCHAR_MAX;
}
/*************************int*****************************/
short getShortIntMax()
{
	return SHRT_MAX;
}
/*********************************************************/
short getShortIntMin()
{
	return SHRT_MIN;
}
/*********************************************************/
unsigned short getUnsignedShortIntMax()
{
	return USHRT_MAX;
}
/*********************************************************/
int getIntMax()
{
	return INT_MAX;
}
/*********************************************************/
int getIntMin()
{
	return INT_MIN;
}
/*********************************************************/
unsigned int getUnsignedIntMax()
{
	return UINT_MAX;
}
/*********************************************************/
long getLongIntMax()
{
	return LONG_MAX;
}
/*********************************************************/
long getLongIntMin()
{
	return LONG_MIN;
}
/*********************************************************/
unsigned long getUnsignedLongIntMax()
{
	return ULONG_MAX;
}
/*********************************************************/
long long getLongLongIntMax()
{
	return LLONG_MAX;
}
/*********************************************************/
long long getLongLongIntMin()
{
	return LLONG_MIN;
}
/*********************************************************/
unsigned long long getUnsignedLongLongIntMax()
{
	return ULLONG_MAX;
}
/************************float****************************/
float getFloatMax()
{
	return FLT_MAX;
}
/*********************************************************/
float getFloatMin()
{
	return FLT_MIN;
}
/*********************************************************/
double getDoubleMax()
{
	return DBL_MAX;
}
/*********************************************************/
double getDoubleMin()
{
	return DBL_MIN;
}
/*********************************************************/
long double getLongDoubleMax()
{
	return LDBL_MAX;
}
/*********************************************************/
long double getLongDoubleMin()
{
	return LDBL_MIN;
}
/****Function to return bit representation of a number****/
char* seeNumOrArrInsideInBits(void* ptrOnNumberOrArr, int sizeInBytes, int mode) 
{
    if(ptrOnNumberOrArr == NULL || sizeInBytes < 0 || mode != MODE_TYPE && mode != MODE_MEMORY)
    {
        return NULL;
    }
    int sizeInBits = sizeInBytes*CHAR_BIT;
    char* insideView = (char*)malloc((sizeInBits+1)*sizeof(char));
    if(insideView == NULL)
    { 
        return NULL;
    }
	if(mode == MODE_TYPE)
    {
        char* oneByteInNumber = (char*)ptrOnNumberOrArr - 1; // plus 1 in start for 
        for(int iteration = 0; iteration < sizeInBits; iteration++)
	    {
            if(iteration%CHAR_BIT == 0)
            {
                oneByteInNumber += 1;
            }
		    insideView[sizeInBits-1-iteration] = (((*oneByteInNumber)&(1<<(iteration%CHAR_BIT)))>>(iteration%CHAR_BIT)) + '0';
	    }
    }
    else if(mode == MODE_MEMORY)
    {
        char* oneByteInNumber = (char*)ptrOnNumberOrArr - 1; // plus 1 in start for 
        for(int iteration = 0; iteration < sizeInBits; iteration++)
	    {
            if(iteration%CHAR_BIT == 0)
            {
                oneByteInNumber += 1;
            }
		    insideView[iteration] = (((*oneByteInNumber)&(1<<(iteration%CHAR_BIT)))>>(iteration%CHAR_BIT))  + '0';
	    }
    }
    insideView[sizeInBits] = '\0';
    return insideView;
}
/****Function to return byte representation of a number****/
char* seeNumOrArrInsideInBytes(void* ptrOnNumberOrArr, int sizeInBytes)
{
    if(ptrOnNumberOrArr == NULL || sizeInBytes < 0)
    {
        return NULL;
    }
    char* insideView = (char*)malloc((sizeInBytes)*sizeof(char));
    if(insideView == NULL)
    {
        return NULL;
    }
    char* ptr = (char*)ptrOnNumberOrArr;
    for(int iteration = 0; iteration<sizeInBytes; iteration++)
    {
        insideView[iteration] = *(ptr + iteration);
    }
    return insideView;
}
/*********************************************************/
