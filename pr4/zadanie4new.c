//ключи могут быть в произвольном порядке
//Если нет значения в ключе или в списке, то выводим ошибку
//работать должна с любым количеством словарей

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
void readNumber(FILE* json, char* strWithNumber);
void writeListOfPublishersInBook(FILE* json, book* structBook);
char* readData(FILE* json, int* PointerOnCountSymbols);
int searchWidthOfNumber(int number);
int searchIndexMaxElementInt(int* arr, int sizeArr);
void printTableInFile(char* fileName, book* arrOfBooks, int countBooks, char** headlines, int* widthOfAllColumn);
char* makeHeadTable(int* widthOfAllColumn, int sumAllWidth);
void printHeadlines(FILE* file, char** headlines);
void printData(FILE* file, book Struct, int* widthOfAllColumn, int numberOfData);
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
    
    while(charInJSON != ':' && charInJSON != '"' && charInJSON != '[' &&  charInJSON != ']' && charInJSON != '{' && charInJSON != '}' && !(charInJSON >= '0' && charInJSON <= '9'))
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
    
        if(lastReadChar >= '0' &&  lastReadChar <= '9')  
        {
            char* number = (char*)malloc(10*sizeof(char));
            if(number == NULL)
            {
                printf("error of malloc\n");
                exit(6);
            }
            readNumber(json, number);
            structBook->yearOfRelise = atoi(number);
            free(number);
            //goToNextSignificantSymbol(json);
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
        if(lastReadChar >= '0' &&  lastReadChar <= '9')  
        {
            char* number = (char*)malloc(10*sizeof(char));
            if(number == NULL)
            {
                printf("error of malloc\n");
                exit(6);
            }
            readNumber(json, number);
            structBook->rating = atoi(number);
            free(number);
            fseek(json, -1, SEEK_CUR);
        }
        else
        {
            printf("error of lastReadСhar");
            exit(7);
        }
    }
}
/**********************************************/
void readNumber(FILE* json, char* strWithNumber)
{
    fseek(json, -1, SEEK_CUR);
    char simbolInJSON = fgetc(json);
    int index = 0;
    while(simbolInJSON != ',' && simbolInJSON != '}')
    {
        if(simbolInJSON >= '0' && simbolInJSON <= '9')
        {
            strWithNumber[index] = simbolInJSON;
            index ++;
            printf("%c\n", simbolInJSON );
        }
        simbolInJSON = fgetc(json);
    }
    strWithNumber[index] = '\0';
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
    int widthOfYears = 10;
    int widthOfRating = 6;
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
        if(arrOfBooks[index].countSimbolsInNameBook-1 > widthOfName)
        {
            widthOfName = arrOfBooks[index].countSimbolsInNameBook-1;
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

    widthOfAllColumn [0] = widthOfNumbers + 2;
    widthOfAllColumn [1] = widthOfName + 2;
    widthOfAllColumn [2] = widthOfYears + 2;
    widthOfAllColumn [3] = widthOfPublishers [0] + 2;
    widthOfAllColumn [4] = widthOfPublishers [1] + 2;
    widthOfAllColumn [5] = widthOfPublishers [2] + 2;
    widthOfAllColumn [6] = widthOfPublishers [3] + 2;
    widthOfAllColumn [7] = widthOfPublishers [4] + 2;
    widthOfAllColumn [8] = widthOfRating + 2;
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
    return module;
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
void printTableInFile(char* fileName, book* arrOfBooks, int countBooks, char** headlines, int* widthOfAllColumn)
{
    int sumAllWidth = 0;
    for(int index = 0; index<9; index++)
    {
        sumAllWidth += widthOfAllColumn[index];
    }
    sumAllWidth += 12; // plus point
    char* head = makeHeadTable(widthOfAllColumn, sumAllWidth);
    FILE* file = fopen(fileName, "w");
    fprintf(file, "%s\n\n", head);
    printHeadlines(file, headlines);
    fprintf(file, "\n\n");
    fprintf(file, "%s\n\n", head);
    for(int index = 0; index<countBooks; index++)
    {
        printData(file, arrOfBooks[index], widthOfAllColumn, index+1);
        fprintf(file, "\n\n");
        fprintf(file, "%s\n\n", head);
    }
    free(head);
    fclose(file);
}
/*********************************************/
char* makeHeadTable(int* widthOfAllColumn, int sumAllWidth)
{
    char* head = (char*)malloc((sumAllWidth)*sizeof(char)); //with point
    printf("SumAllW %d\n", sumAllWidth);
    int indexArrInt = 0;
    int indexLastPlus = 0;
    int indexStr =1;
    head[0] = '+';
    while(indexArrInt != 9)
    {
        head[indexStr] = '-';
        indexStr++;
        printf("%d\n",indexStr);
        if(indexStr-indexLastPlus-1 == widthOfAllColumn[indexArrInt])
        {
            head[indexStr] = '+';
            indexLastPlus = indexStr;
            indexStr++;
            indexArrInt++;
            printf("app\n");
        }
        if(indexStr>sumAllWidth+1)
        {
            printf("error make head");
            head[indexStr] = '\0';
            return head;
        }
    }
    head[indexStr] = '\0';
    return head;
}
/*********************************************/
void printHeadlines(FILE* file, char** headlines)
{
    
    fprintf(file, "|%s",headlines[0]);
    fprintf(file, "|%s",headlines[1]);
    fprintf(file, "|%s",headlines[2]);
    fprintf(file, "|%s",headlines[3]);
    fprintf(file, "|%s",headlines[4]);
    fprintf(file, "|%s",headlines[5]);
    fprintf(file, "|%s",headlines[6]);
    fprintf(file, "|%s",headlines[7]);
    fprintf(file, "|%s|",headlines[8]);
}
/*********************************************/
void printData(FILE* file, book Struct, int* widthOfAllColumn, int numberOfData)
{
    fprintf(file, "|%*d",widthOfAllColumn[0], numberOfData);
    fprintf(file, "|%s",Struct.nameBook);
    fprintf(file, "|%*d",widthOfAllColumn[2], Struct.yearOfRelise );
    fprintf(file, "|%s",Struct.publishers[0]);
    fprintf(file, "|%s",Struct.publishers[1]);
    fprintf(file, "|%s",Struct.publishers[2]);
    fprintf(file, "|%s",Struct.publishers[3]);
    fprintf(file, "|%s",Struct.publishers[4]);
    fprintf(file, "|%*d|",widthOfAllColumn[8], Struct.rating);
}
/*********************************************/
int main(int argc, char** argv)
{
    int countBooks = 0;
    book* arrOfBooks = createArrOfBooksFromJSON("data.json", &countBooks);
    int* widthOfAllColumn = searchWidthOfAllColumn(arrOfBooks, countBooks);
    char* headlines [9] = {"Title","YearOfRelease","Publisher 1", "Publisher 2", "Publisher 3", "Publisher 4", "Publisher 5", "Rating"};
    printTableInFile("a.txt", arrOfBooks, countBooks, headlines, widthOfAllColumn);
    
    
    /*for(int i = 0; i<3; i++){
        printf("cis - %d, %d, %d, %d, %d\n", arrOfBooks[i].countSimbolsInStr[0], arrOfBooks[i].countSimbolsInStr[1], arrOfBooks[i].countSimbolsInStr[2], arrOfBooks[i].countSimbolsInStr[3], arrOfBooks[i].countSimbolsInStr[4]);
    }
    for(int i = 0; i<9; i++)
    {
        printf("%d\n", widthOfAllColumn[i]);
    }
    for(int i = 0; i<3; i++){
        printf("%d , %d", arrOfBooks[0].yearOfRelise, arrOfBooks[1].yearOfRelise);
    }*/
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
