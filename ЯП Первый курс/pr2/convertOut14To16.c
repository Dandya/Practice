#include <stdio.h>
#include <malloc.h>
/***************************************/
int searchCountWholeDigit(char* numberInStr);
double conversionFromFourteenToTenSys(char* numberInStr,int degree);
double Pow(double number, int degree);
/***************************************/
int main()
{
//input number
    char* numberInFourteenSys = (char*)malloc(20*sizeof(char));
    printf("Input number: \n");
    fgets(numberInFourteenSys, 20, stdin);
//end input number

    int countWholeDigit = searchCountWholeDigit(numberInFourteenSys); //search index point

//conversion
    int degreeMax = countWholeDigit-1;
    double numberInTenSys = conversionFromFourteenToTenSys(numberInFourteenSys, degreeMax);
    if(numberInTenSys==-1.)
        return -1;
//end conversion

    printf("%lf\n", numberInTenSys);
    return 0;
} 
/***************************************/
int searchCountWholeDigit(char* numberInStr)
{
/*
	 Функция ищет индекс точки в строке, если же 
	 точки в строке нет, то возращает индекс признака
	 конца строки '\0' или '\n'.
*/
    int indexEnd = 0;
    int indexPoint = -1;
    while(numberInStr[indexEnd]!='\0'&&numberInStr[indexEnd]!='\n')
    {
        if(numberInStr[indexEnd]=='.')
            return indexEnd;
        indexEnd++;
    }
    if(indexPoint==-1)
        indexPoint=indexEnd;
    return indexPoint;
}
/***************************************/
double conversionFromFourteenToTenSys(char* numberInStr,int degree)
{
/*
    Функция посимвольно конвертирует число из четырнадцатиричной
    системы в десятичную. на вход принимает указатель на строку с числом
    в четырнадцатиричной системе и максимальную степень числа 14.
*/
    int index = 0;
    double numberInTenSys = 0.0;
    while(numberInStr[index]!='\0'&&numberInStr[index]!='\n')
    {
        if(numberInStr[index]>='0'&&numberInStr[index]<='9')
        {
            numberInTenSys+=(numberInStr[index]-48)*Pow(14. , degree);
            degree--; 
        }
        else if(numberInStr[index]>='A'&&numberInStr[index]<='D')
        {
            numberInTenSys+=(numberInStr[index]-55)*Pow(14. , degree);
            degree--; 
        }
        else if(numberInStr[index]>='a'&&numberInStr[index]<='d')
        {
            numberInTenSys+=(numberInStr[index]-87)*Pow(14. , degree);
            degree--; 
        }
        else if(numberInStr[index]!='.')
        {
            printf("uncorrect input");
            return -1.;
        }
        index++;
    }
    return numberInTenSys;
}
/***************************************/
double Pow(double number, int degree)
{
/*
    Функция возведения вещественного числа number
    в целую степень degree.
*/
    if(degree>=0)
    {
        double result = 1.;
        while(degree)
        {
            if(degree&1)
            {
                result *= number;
            }
            number *= number;
            degree>>=1;
        }
        return result;
    }
    else
    {
        double result = Pow(number, (-1)*degree);
        return 1/result;
    }
}
/***************************************/
