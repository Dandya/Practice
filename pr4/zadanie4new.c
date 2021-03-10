#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**********************************************/
typedef struct
{
    char* nameBook;
    int countSimbolsInNameBook;
    int yearOfRelise;
    char* publishers [5];
    int countSimbolsInStr [5];
    int rating;
}book;
/**********************************************/
book* createArrOfBooksFromJSON(char* nameFileJSON, int* countBooks);
book* beginReadJSON(FILE* json, book* arrOfBooks, int* countBooks);
char goToNextSignificantSymbol(FILE* json);
book* listOfDictJSON(FILE* json, book* arrOfBooks, int* countBooks);
void dictJSON(FILE* json, book* arrOfBooks, int* pointerOnIndexRecordedBook);
void readKey(FILE* json, book* ArrOfBooks, int* pointerOnIndexRecordedBook);
int strEQ(char* strFirst,char * strSecond);
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar);
void writeListOfPublishersInBook(FILE* json, book* structBook);
char* readData(FILE* json, int* PointerOnCountSymbols);
int searchWidthOfNumber(int number);
int searchIndexMaxElementInt(int* arr, int sizeArr);
/**********************************************/
book* createArrOfBooksFromJSON(char* nameFileJSON, int* countBooks)
{
    FILE *json = fopen(nameFileJSON, "r");
    
    if (json == NULL)
    {
        printf("error of open file .json");
        exit(2);
    }
    
    book* arrOfBooks;
    if((arrOfBooks = (book*)malloc(30*sizeof(book))) == NULL)
    {
        printf("error malloc\n");
        exit(6);
    }

    arrOfBooks =  beginReadJSON(json, arrOfBooks, countBooks);
    
    fclose(json);

    return arrOfBooks;
}
/**********************************************/
book* beginReadJSON(FILE* json, book* arrOfBooks, int* countBooks)
{
    char result = goToNextSignificantSymbol(json);
    if(result == '[')
    {
        return listOfDictJSON(json, arrOfBooks, countBooks);
    }
    else if(result == '{')
    {
        dictJSON(json, arrOfBooks, 0);
        *countBooks++;
    }
     
    return arrOfBooks;
}
/**********************************************/
char goToNextSignificantSymbol(FILE* json)
{   
    char charInJSON = fgetc(json);
    
    while(charInJSON != ':' && charInJSON != '"' && charInJSON != '[' &&  charInJSON != ']' && charInJSON != '{' && charInJSON != '}')
    {
        charInJSON = fgetc(json);
    }

    return charInJSON;
}
/**********************************************/
book* listOfDictJSON(FILE* json, book* arrOfBooks, int* countBooks)
{
    int index = 0;
    char result = goToNextSignificantSymbol(json);
    while(result != ']')
    {
        dictJSON(json, arrOfBooks, &index);
        index++;
        if(index%30 == 0)
        {
            if((arrOfBooks = (book*)realloc(arrOfBooks,(index+30)*sizeof(book))) == NULL)
            {
                printf("error of realloc");
                exit(10);
            }
        }
        result = goToNextSignificantSymbol(json);
    }
    *countBooks = index;
    return arrOfBooks;
}
/**********************************************/
void dictJSON(FILE* json, book* arrOfBooks, int* pointerOnIndexRecordedBook)
{
    char result = goToNextSignificantSymbol(json);
    while(result == '"') //dungerous
    {
        readKey(json, arrOfBooks,pointerOnIndexRecordedBook);
        result = goToNextSignificantSymbol(json);
        printf("char - %c\n", result);
    }
    if(result != '}')
    {
        printf("error of dictJSON");
        exit(9);
    }
}
/**********************************************/
void readKey(FILE* json, book* ArrOfBooks, int* pointerOnIndexRecordedBook)
{
    char* key = readData(json, NULL);
    char result = goToNextSignificantSymbol(json);
    if(result == ':')
    {
        result = goToNextSignificantSymbol(json);
        saveValueInKeyJSON(json, key, ArrOfBooks + *pointerOnIndexRecordedBook, result);
    }
    else
    {
        printf("error: strange things\n");
        exit(8);
    }
}
/**********************************************/
int strEQ(char* strFirst,char * strSecond)
{
    int index = 0;
    while(strFirst[index] == strSecond[index])
    {
        if(strFirst[index] == '\0')
        {
            return 1;
        }
        index++;
    }
    //else
    return 0;
}
/**********************************************/

void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar)
{ 
    //"Title","YearOfRelease","Publishers","Rating"
    if(strEQ(key,"Title"))
    {
        if(lastReadChar == '"')  
        {
            structBook->nameBook = readData(json, &structBook->countSimbolsInNameBook);
            printf("c s - %d\n", structBook->countSimbolsInNameBook );
        }
        else
        {
            printf("error of lastReadСhar");
            exit(7);
        }
    }
    //"YearOfRelease"
    else if(strEQ(key, "YearOfRelease"))
    {
        
        if(lastReadChar == '"')  
        {
            structBook->yearOfRelise = atoi(readData(json, NULL));
        }
        else
        {
            printf("error of lastReadСhar");
            exit(7);
        }
    }
    //"Publishers""
    else if(strEQ(key, "Publishers"))
    {
        if(lastReadChar == '[')
        {
            writeListOfPublishersInBook(json, structBook);    
        }
        else if(lastReadChar == '"')
        {
            structBook->publishers[0] = readData(json, structBook->countSimbolsInStr);
            int index = 0;
            while(index != 4)
            {
                index++;
                if((structBook->publishers[index] = (char*)malloc(1*sizeof(char))) == NULL)
                {
                    printf("error malloc\n");
                    exit(6);
                }
                *(structBook->publishers[index]) = '\0';
                structBook->countSimbolsInStr[index] = 1;
            }

        }
        else
        {
            printf("error of lastReadСhar");
            exit(7);
        }
    }
    //"Rating"
    else if(strEQ(key, "Rating"))
    {
        if(lastReadChar == '"')  
        {
            structBook->rating = atoi(readData(json, NULL));
        }
        else
        {
            printf("error of lastReadСhar");
            exit(7);
        }
    }
}
/**********************************************/
void writeListOfPublishersInBook(FILE* json, book* structBook)
{
    goToNextSignificantSymbol(json);

    int index = 0;    
    structBook->publishers[0] = readData(json, structBook->countSimbolsInStr ); 
    
    while(goToNextSignificantSymbol(json) != ']')
    {
        if(index == 4)
        {
            continue;
        }

        index++;
        structBook->publishers[index] = readData(json, structBook->countSimbolsInStr+index );
    }

    while(index != 4)
    {
        index++;
        if((structBook->publishers[index] = (char*)malloc(1*sizeof(char))) == NULL)
        {
            printf("error malloc\n");
            exit(6);
        }
        structBook->publishers[index][0] = '\0';
        structBook->countSimbolsInStr[index] = 1;
    }
}
/**********************************************/
char* readData(FILE* json, int* PointerOnCountSymbols)
{
    char* data = (char*)malloc(20*sizeof(char));
    if(data == NULL)
    {
         printf("error malloc in readData\n");
         exit(6);
    }
    int indexCharInData = 0;
    data[indexCharInData] = fgetc(json);
    while(data[indexCharInData] != '"')
    {
        indexCharInData++;
        if (indexCharInData%20 == 0)
        {
            data = (char*)realloc(data, (indexCharInData+20)*sizeof(char));
            if(data == NULL)
            {
                printf("error malloc\n");
                exit(6);
            }
        }
        data[indexCharInData] = fgetc(json);
        printf("%c , %d", data[indexCharInData], indexCharInData );
    }   
    data[indexCharInData] = '\0';
    if (PointerOnCountSymbols != NULL)
    {
        *PointerOnCountSymbols = indexCharInData;
    }
    return data;
}
/**********************************************/
int* searchWidthOfAllColumn(book* arrOfBooks, int countBooks)
{
    int widthOfNumbers = searchWidthOfNumber(countBooks) + 2;
    int widthOfYears = 16;
    int widthOfRating = 8;
    int widthOfPublishers [5] = {13, 13, 13, 13, 13}; //Publisher #

    int allCountSymbolsInStrsOnColumn[5] [countBooks];
    for(int indexColumn = 0, indexBook = 0 ; indexBook<countBooks; indexBook++)
    {
        allCountSymbolsInStrsOnColumn[indexColumn] [indexBook] = arrOfBooks[indexBook].countSimbolsInStr[indexColumn];
        printf("indexColumn = %d, indexBook = %d\n", indexColumn, indexBook);
        if(indexBook+1 == countBooks && indexColumn != 4)
        {
            indexColumn++;
            indexBook = -1;
        }
    }
    
    for(int i = 0; i<5; i++)
        printf("aCsISOC - %d, %d, %d, %d, %d\n",allCountSymbolsInStrsOnColumn[i][0], allCountSymbolsInStrsOnColumn[i][1], allCountSymbolsInStrsOnColumn[i][2], allCountSymbolsInStrsOnColumn[i][3], allCountSymbolsInStrsOnColumn[i][4]); 

    int widthOfName = 7; //Title
    int indexMaxElement = 0;
    int MaxElement = 0;
    for(int index = 0; index<countBooks; index++)
    {
        if(arrOfBooks[index].countSimbolsInNameBook > widthOfName)
        {
            widthOfName = arrOfBooks[index].countSimbolsInNameBook;
        }
        
    }
    
    for(int columnOfPublishers = 0; columnOfPublishers<5; columnOfPublishers++)
    {
        MaxElement = allCountSymbolsInStrsOnColumn [columnOfPublishers] [searchIndexMaxElementInt(allCountSymbolsInStrsOnColumn[columnOfPublishers], countBooks)];
        if(MaxElement > widthOfPublishers[columnOfPublishers])
        {
            widthOfPublishers[columnOfPublishers] = MaxElement;
            printf("wOP-%d\n",widthOfPublishers[columnOfPublishers]);
        }
    }
    
    int* widthOfAllColumn = (int*)malloc(9*sizeof(int));
    if(widthOfAllColumn == NULL)
    {
        printf("error of malloc");
        exit(6);
    }

    widthOfAllColumn [0] = widthOfNumbers;
    widthOfAllColumn [1] = widthOfName;
    widthOfAllColumn [2] = widthOfYears;
    widthOfAllColumn [3] = widthOfPublishers [0];
    widthOfAllColumn [4] = widthOfPublishers [1];
    widthOfAllColumn [5] = widthOfPublishers [2];
    widthOfAllColumn [6] = widthOfPublishers [3];
    widthOfAllColumn [7] = widthOfPublishers [4];
    widthOfAllColumn [8] = widthOfRating;
    return widthOfAllColumn;
}
/**********************************************/
int searchWidthOfNumber(int number)
{
    int module = 1;
    while(number/module >= 10)
    {
        module *= 10;
    }
    return number/module;
}
/**********************************************/
int searchIndexMaxElementInt(int* arr, int sizeArr)
{
    if(sizeArr <= 0)
    {   
        printf("error of size\n");
        exit(10);
    }
    if(arr == NULL)
    {
        printf("error of pointer\n");
        exit(11);
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
/*********************************************/
void printTableInFile(char* fileName, char** headlines, int* widthOfAllColumn)
{
    int sumAllWidth = 0;
    for(int index = 0; index < 9; index++)
    {
        sumAllWidth += widthOfAllColumn[index];
    }
    char* head = (char*)malloc((sumAllWidth + 12)*sizeof(char));


}
/*********************************************/

int main(int argc, char** argv)
{
    int countBooks = 0;
    book* arrOfBooks = createArrOfBooksFromJSON("data.json", &countBooks);
    int* widthOfAllColumn = searchWidthOfAllColumn(arrOfBooks, countBooks);
    for(int i = 0; i<3; i++){
        printf("cis - %d, %d, %d, %d, %d\n", arrOfBooks[i].countSimbolsInStr[0], arrOfBooks[i].countSimbolsInStr[1], arrOfBooks[i].countSimbolsInStr[2], arrOfBooks[i].countSimbolsInStr[3], arrOfBooks[i].countSimbolsInStr[4]);
    }
    for(int i = 0; i<9; i++)
    {
        printf("%d\n", widthOfAllColumn[i]);
    }
    return 0;
}
/**********************************************/
/*char* makeOneStringWithCommaAndSpace(char** arrOfStr, int countStr, int* ArrOfCountSymbolsInStr)
{
    char* resultStr = (char*)malloc((ArrOfCountSymbolsInStr[0]+ArrOfCountSymbolsInStr[1]+ArrOfCountSymbolsInStr[2]+ArrOfCountSymbolsInStr[3]+ArrOfCountSymbolsInStr[4]+8)*sizeof(char));
    int indexStr = 0;
    int indexCharInAddStr = 0;
    int countIndexesWritedStrs = 0;
    while(indexStr<countStr)
    {
        /if(countIndexesWritedStrs%100 >= 70&&countIndexesWritedStrs%100 <= 99)
        {
            resultStr =  (char*)realloc(result, (countIndexesWritedStrs+100)*sizeof(char));
            if(resultStr == NULL)
            {
                printf("error malloc\n");
                exit(6);
            }
        }/
        resultStr[countIndexesWritedStrs+indexCharInAddStr] = arrOfStr[indexStr] [indexCharInAddStr]; 
        indexCharInAddStr++;
        if(arrOfStr[indexStr] [indexCharInAddStr] == '\0')
        {
            if(indexStr != countStr - 1){
                resultStr[countIndexesWritedStrs+indexCharInAddStr] = ',';
                resultStr[countIndexesWritedStrs+indexCharInAddStr+1] = ' ';
            }
            countIndexesWritedStrs += indexCharInAddStr+1; 
            indexCharInAddStr = 0;
            indexStr++;
        }
    }
    resultStr[countWritedChar-1] = '\0';
    return resultStr;
}*/   
/**********************************************/
