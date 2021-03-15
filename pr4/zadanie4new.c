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
int strEQ(char* strFirst,char * strSecond);
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar);
void readNumber(FILE* json, char* strWithNumber);
void writeListOfPublishersInBook(FILE* json, book* structBook);
char* readData(FILE* json, int* PointerOnCountSymbols);
int* searchWidthOfAllColumn(book* arrOfBooks, int countBooks, int* lenTitle);
int searchWidthOfNumber(int number);
int searchIndexMaxElementInt(int* arr, int sizeArr);
void printTableInFile(char* fileName, book* arrOfBooks, int countBooks, char** headlines, int* lenTitle, int* widthOfAllColumn);
char* makeHeadTable(int* widthOfAllColumn, int sumAllWidth);
void printHeadlines(FILE* file, char** headlines, int* lenStr, int countHeadlines, int* widthOfAllColumn);
int strLen(char* str);
void printSpase(FILE* file, int countSpase);
void printData(FILE* file, book Struct, int* widthOfAllColumn, int numberOfData);
void printStr(FILE* file, int widthColumn, char* str, int lenStr);
void printNumber(FILE* file, int number, int width);
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
    
    while(charInJSON != ':' && charInJSON != '"' && charInJSON != '[' &&  charInJSON != ']' && charInJSON != '{' && charInJSON != '}' && !(charInJSON >= '0' && charInJSON <= '9') && charInJSON != 'n')
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
    char result = goToNextSignificantSymbol(json
    int countKey = 0;
    while(result == '"') 
    {
        char* key = readData(json, NULL);
        result = goToNextSignificantSymbol(json);
        if(result == ':')
        {
            result = goToNextSignificantSymbol(json);
            saveValueInKeyJSON(json, key, arrOfBooks + *pointerOnIndexRecordedBook, result);
            countKey++;
            fseek(json, -1, SEEK_CUR);
            if((result = fgetc(json)) == '}')
            {
                break;
            }
            result = goToNextSignificantSymbol(json);
        }
        else
        {
            printf("error: strange things\n");
            exit(8);
        }
    }
    if(result != '}' || countKey != 4)
    {
        printf("error of dictJSON");
        exit(9);
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
        }
        else if( (((lastReadChar == 'n') && fgetc(json) == 'u') && fgetc(json) == 'l') && fgetc(json) == 'l' ) 
        {
            structBook->nameBook = "untitled";
            structBook->countSimbolsInNameBook = 8;
        }
        else
        {
            printf("error of lastReadСhar read Title");
            exit(7);
        }
    }
    //"YearOfRelease" and "Rating"
    else if(strEQ(key, "YearOfRelease"))
    {
        if(lastReadChar >= '0' &&  lastReadChar <= '9' || lastReadChar == '"')  
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
        else if((((lastReadChar == 'n') && fgetc(json) == 'u') && fgetc(json) == 'l') && fgetc(json) == 'l')
        {
            structBook->yearOfRelise = 0;
        }
        else
        {
            printf("error of lastReadСhar read YearOfRelease");
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
        else if((((lastReadChar == 'n') && fgetc(json) == 'u') && fgetc(json) == 'l') && fgetc(json) == 'l')
        {
            int index = 0;
            while(index != 5)
            {
                if((structBook->publishers[index] = (char*)malloc(1*sizeof(char))) == NULL)
                {
                    printf("error malloc\n");
                    exit(6);
                }
                *(structBook->publishers[index]) = '\0';
                structBook->countSimbolsInStr[index] = 1;
                index++;
            }
        }
        else
        {
            printf("error of lastReadСhar read Publishers ");
            exit(7);
        }
    }
    else if (strEQ(key, "Rating"))
    {
        if(lastReadChar >= '0' &&  lastReadChar <= '9' || lastReadChar == '"')  
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
            //goToNextSignificantSymbol(json);
        }
        else if((((lastReadChar == 'n') && fgetc(json) == 'u') && fgetc(json) == 'l') && fgetc(json) == 'l')
        {
            structBook->rating = 0;
        }
        else
        {
            printf("error of lastReadСhar read YearOfRelease");
            exit(7);
        }
    } 
    else
    {
        printf("error: unknown key\n");
        exit(12);
    }
}
/**********************************************/
void readNumber(FILE* json, char* strWithNumber)
{
    fseek(json, -1, SEEK_CUR);
    char simbolInJSON = fgetc(json);
    if(simbolInJSON == '"')
    {
        simbolInJSON = fgetc(json);
    }
    int index = 0;
    while(simbolInJSON != ',' && simbolInJSON != '}' && simbolInJSON != '"')
    {
        if(simbolInJSON >= '0' && simbolInJSON <= '9')
        {
            strWithNumber[index] = simbolInJSON;
            index ++;
            //printf("%c\n", simbolInJSON );
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
int* searchWidthOfAllColumn(book* arrOfBooks, int countBooks, int* lenTitle)
{
    int widthOfNumbers = searchWidthOfNumber(countBooks);
    widthOfNumbers = (widthOfNumbers >= lenTitle[0] ? widthOfNumbers : lenTitle[0])  + 2;
    int widthOfYears = lenTitle[2];
    int widthOfRating = lenTitle[8];
    int widthOfPublishers [5] = {lenTitle[3], lenTitle[4], lenTitle[5], lenTitle[6], lenTitle[7]}; //Publisher #

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
    int degree = 0;
    while(number/module >= 10)
    {
        module *= 10;
        degree++;
    }
    return degree+1;
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
void printTableInFile(char* fileName, book* arrOfBooks, int countBooks, char** headlines, int* lenTitle, int* widthOfAllColumn)
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
    printHeadlines(file, headlines, lenTitle , 9,widthOfAllColumn);
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
void printHeadlines(FILE* file, char** headlines, int* lenStr, int countHeadlines, int* widthOfAllColumn)
{
    for(int index = 0; index<countHeadlines; index++)
    {
        fputc('|',file);
        int countALLSpace = widthOfAllColumn[index]-lenStr[index];
        printf("countALLSpace %d = %d, lenStr = %d\n", index, countALLSpace, lenStr[index]);
        printSpase(file ,countALLSpace/2);
        fprintf(file, "%s", headlines[index]);
        printSpase(file ,countALLSpace%2==0?countALLSpace/2:countALLSpace/2+1);
    }
    fputc('|', file);
    /*fprintf(file, "|%s",headlines[0]);
    fprintf(file, "|%s",headlines[1]);
    fprintf(file, "|%s",headlines[2]);
    fprintf(file, "|%s",headlines[3]);
    fprintf(file, "|%s",headlines[4]);
    fprintf(file, "|%s",headlines[5]);
    fprintf(file, "|%s",headlines[6]);
    fprintf(file, "|%s",headlines[7]);
    fprintf(file, "|%s|",headlines[8]);*/
}
/*********************************************/
int strLen(char* str)
{
    if(str == NULL)
    {
        return -1;
    }
    int index = 0;
    while(str[index] != '\0')
    {
        index++;
    }
    return index;
}
/*********************************************/
void printSpase(FILE* file, int countSpase)
{
    for(int i = 1; i<=countSpase; i++)
    {
        fprintf(file, " ");
    }
}
/*********************************************/
void printData(FILE* file, book Struct, int* widthOfAllColumn, int numberOfData)
{
    //print first colomn
    printNumber(file, numberOfData, widthOfAllColumn[0]);
    //print title
    printStr(file, widthOfAllColumn[1], Struct.nameBook, Struct.countSimbolsInNameBook);
    //print YearOfRelise
    printNumber(file, Struct.yearOfRelise, widthOfAllColumn[2]);
    //print Publishers
    for(int index = 0; index < 5; index++)
    {
        printStr(file, widthOfAllColumn[3 + index], Struct.publishers[index], Struct.countSimbolsInStr[index]);
    }
    //print rating
    printNumber(file, Struct.rating, widthOfAllColumn[8]);
    fputc('|', file);
}
/*********************************************/
void printStr(FILE* file, int widthColumn, char* str, int lenStr)
{
        fputc('|',file);
        int countALLSpace = widthColumn-lenStr;
        printSpase(file ,countALLSpace/2);
        printf("%ld", str);
        if(str[0] != '\0')
        {
            fprintf(file, "%s", str);
        }
        else
        {
            fputc(' ', file);
        }
        printSpase(file ,countALLSpace%2==0?countALLSpace/2:countALLSpace/2+1);
}
/*********************************************/
void printNumber(FILE* file, int number, int width)
{
    int widthNumber = searchWidthOfNumber(number); 
    fprintf(file, "|%*d",(width-widthNumber)/2 + widthNumber, number);
    printf(" wN = %d, number = %d\n", widthNumber, number);
    if(width%2==1 && widthNumber%2 == 1)
    {
        printSpase(file, (width-widthNumber)/2);
    }
    else if(width%2 == 0 && widthNumber%2 == 0)
    {
        printSpase(file, (width-widthNumber)/2);
    }
    else if(width%2 == 1 && widthNumber%2 == 0)
    {
        printSpase(file, (width-widthNumber)/2+1);
    }
    else if(width%2 == 0 && widthNumber%2 == 1)
    {
        printSpase(file, (width-widthNumber)/2 + 1);
    }
   // printSpase(file ,((width-widthNumber)/2)%2 == 0?(width-widthNumber)/2:(width-widthNumber)/2);
}
/*********************************************/
int main(int argc, char** argv)
{
    int countBooks = 0;
    book* arrOfBooks = createArrOfBooksFromJSON("data.json", &countBooks);
    char* headlines [9] = {"N","Title","YearOfRelise","Publisher 1", "Publisher 2", "Publisher 3", "Publisher 4", "Publisher 5", "Rating"};
    int lenStr[9];
    for(int index = 0; index<9; index++)
    {
        lenStr[index] = strLen(headlines[index]);
    }

    int* widthOfAllColumn = searchWidthOfAllColumn(arrOfBooks, countBooks, lenStr);
    printTableInFile("a.txt", arrOfBooks, countBooks, headlines, lenStr, widthOfAllColumn);
    
    
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
