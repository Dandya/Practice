#include <limits.h>
#include <float.h>
#include <malloc.h>

#define MODE_TYPE 1
#define MODE_MEMORY 0

//Functions to return maximum and minimum values
/************************char*****************************/
char getCharMax()
{
	return (char)CHAR_MAX;
}
/*********************************************************/
char getCharMin()
{
	return (char)CHAR_MIN;
}
/*********************************************************/
signed char getSignedCharMax()
{
	return (signed char)SCHAR_MAX;
}
/*********************************************************/
signed char getSignedCharMin()
{
	return (signed char)SCHAR_MIN;
}
/*********************************************************/
unsigned char getUnsignedCharMax()
{
	return (unsigned char)UCHAR_MAX;
}
/*************************int*****************************/
short getShortIntMax()
{
	return (short)SHRT_MAX;
}
/*********************************************************/
short getShortIntMin()
{
	return (short)SHRT_MIN;
}
/*********************************************************/
unsigned short getUnsignedShortIntMax()
{
	return (unsigned short)USHRT_MAX;
}
/*********************************************************/
int getIntMax()
{
	return (int)INT_MAX;
}
/*********************************************************/
int getIntMin()
{
	return (int)INT_MIN;
}
/*********************************************************/
unsigned int getUnsignedIntMax()
{
	return (unsigned int)UINT_MAX;
}
/*********************************************************/
long getLongIntMax()
{
	return (long)LONG_MAX;
}
/*********************************************************/
long getLongIntMin()
{
	return (long)LONG_MIN;
}
/*********************************************************/
unsigned long getUnsignedLongIntMax()
{
	return (unsigned long)ULONG_MAX;
}
/*********************************************************/
long long getLongLongIntMax()
{
	return (long long)LLONG_MAX;
}
/*********************************************************/
long long getLongLongIntMin()
{
	return (long long)LLONG_MIN;
}
/*********************************************************/
unsigned long long getUnsignedLongLongIntMax()
{
	return (unsigned long long )ULLONG_MAX;
}
/************************float****************************/
float getFloatMax()
{
	return (float)FLT_MAX;
}
/*********************************************************/
float getFloatMin()
{
	return (float)FLT_MIN;
}
/*********************************************************/
double getDoubleMax()
{
	return  (double)DBL_MAX;
}
/*********************************************************/
double getDoubleMin()
{
	return  (double)DBL_MIN;
}
/*********************************************************/
long double getLongDoubleMax()
{
	return  (long double)LDBL_MAX;
}
/*********************************************************/
long double getLongDoubleMin()
{
	return  (long double)LDBL_MIN;
}
/****Function to return bit representation of a number****/
char* seeNumOrArrInsideInBits(void* ptrOnNumberOrArr, int sizeInBytes, int mode) //MODE_TYPE = 1 MODE_MEMORY = 0 
{
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
    else
    {
        return NULL;
    }
    insideView[sizeInBits] = '\0';
    return insideView;
}
/****Function to return byte representation of a number****/
char* seeNumOrArrInsideInBytes(void* ptrOnNumberOrArr, int sizeInBytes)
{
    char* insideView = (char*)malloc((sizeInBytes+1)*sizeof(char));
    if(insideView == NULL)
    {
        return NULL;
    }
    char* ptr = (char*)ptrOnNumberOrArr;
    for(int iteration = 0; iteration<sizeInBytes; iteration++)
    {
        insideView[iteration] = *(ptr + iteration);
    }
    insideView[sizeInBytes] = '\0';
    return insideView;
}
/*********************************************************/

