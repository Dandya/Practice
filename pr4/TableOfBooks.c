#include <stdio.h>
#include <stdlib.h>
/**********************************************/
typedef struct
{
    char* nameBook;
    int countSimbolsInNameBook;
    char* author;
    int countSimbolsInAuthor;
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
char* readData(FILE* json);
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
void printStrWithoutSpaceInStart(FILE* file, int widthColumn, char* str, int lenStr);
void printNumber(FILE* file, int number, int width);
void sortArrOfBooksRating(book* arrOfBooks, int countBooks);
void sortArrOfBooksYear(book* arrOfBooks, int countBooks);
int* searchIndexesOfBooksByTitle(book* arrOfBooks, int countBooks, char* title);
int* searchIndexesOfBooksByAuthor(book* arrOfBooks, int countBooks, char* author);
int* searchIndexesOfBooksByPublisher(book* arrOfBooks, int countBooks, char* publisher);
int* searchIndexesOfBooksByYear(book* arrOfBooks, int countBooks, int year);
int* searchIndexesOfBooksByRating(book* arrOfBooks, int countBooks, int rating);
int clearInputBuffer(void);
/**********************************************/
int checkInputData(int argc, char** argv)
{
    if(argc == 3 || argc == 2)
    {
        int index = 0;
        while(argv[1][index] != '\0')
        {
            index++;
        }
        if(argv[1][index-5] == '.' &&  argv[1][index-4] == 'j' && argv[1][index-3] == 's' && argv[1][index-2] == 'o' && argv[1][index-1] == 'n')
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
/**********************************************/
book* createArrOfBooksFromJSON(char* nameFileJSON, int* countBooks)
{
    FILE *json = fopen(nameFileJSON, "r");
    
    if (json == NULL)
    {
        printf("error of open file .json\n");
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
        dictJSON(json, arrOfBooks, countBooks);
        *countBooks += 1;
    }
    else
    {
        printf("bad file\n");
        exit(14);
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
    char result = goToNextSignificantSymbol(json);
    int countKey = 0;
    while(result == '"') 
    {
        char* key = readData(json);
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
    if(result != '}' || countKey != 5)
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
    if (strFirst[index] == '\n' && strSecond[index] == '\0')
    {
        return 1;
    }
    //else
    return 0;
}
/**********************************************/
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar)
{ 
    //"Title"
    if(strEQ(key,"Title"))
    {
        if(lastReadChar == '"')  
        {
            structBook->nameBook = readData(json);
            structBook->countSimbolsInNameBook = strLen(structBook->nameBook);
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
    //"Author"
    else if(strEQ(key,"Author"))
    {
        if(lastReadChar == '"')  
        {
            structBook->author = readData(json);
            structBook->countSimbolsInAuthor = strLen(structBook->author);
        }
        else if( (((lastReadChar == 'n') && fgetc(json) == 'u') && fgetc(json) == 'l') && fgetc(json) == 'l' ) 
        {
            structBook->author = "unknown";
            structBook->countSimbolsInAuthor = 7;
        }
        else
        {
            printf("error of lastReadСhar read Author");
            exit(7);
        }
    }
    //"YearOfRelease"
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
            structBook->publishers[0] = readData(json);
            structBook->countSimbolsInStr[0] = strLen(structBook->publishers[0]);
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
    //"Rating"
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
    structBook->publishers[0] = readData(json); 
    structBook->countSimbolsInStr[0] = strLen(structBook->publishers[0]);
    while(goToNextSignificantSymbol(json) != ']')
    {
        if(index == 4)
        {
            continue;
        }
        index++;
        structBook->publishers[index] = readData(json);
        structBook->countSimbolsInStr[index] = strLen(structBook->publishers[index]);
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
char* readData(FILE* json)
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
    }   
    data[indexCharInData] = '\0';
    return data;
}
/**********************************************/
int* searchWidthOfAllColumn(book* arrOfBooks, int countBooks, int* lenTitle)
{
    int widthOfNumbers = searchWidthOfNumber(countBooks);
    widthOfNumbers = (widthOfNumbers >= lenTitle[0] ? widthOfNumbers : lenTitle[0]);
    int widthOfYears = lenTitle[3] >= 4 ? lenTitle[3] : 4;
    int widthOfRating = lenTitle[8];
    int widthOfPublishers [5] = {lenTitle[3], lenTitle[4], lenTitle[5], lenTitle[6], lenTitle[7]}; 

    int widthOfName = lenTitle[1]; //Title 
    for(int index = 0; index<countBooks; index++)
    {
        if(arrOfBooks[index].countSimbolsInNameBook > widthOfName)
        {
            widthOfName = arrOfBooks[index].countSimbolsInNameBook-1;
        }
        
    }
    
    int widthOfAuthor = lenTitle[2]; 
    for(int index = 0; index<countBooks; index++)
    {
        if(arrOfBooks[index].countSimbolsInAuthor > widthOfAuthor)
        {
            widthOfAuthor = arrOfBooks[index].countSimbolsInAuthor;
        }
        
    }

    int allCountSymbolsInStrsOnColumn[5] [countBooks]; 
    for(int indexColumn = 0, indexBook = 0 ; indexBook<countBooks; indexBook++)
    {
        allCountSymbolsInStrsOnColumn[indexColumn] [indexBook] = arrOfBooks[indexBook].countSimbolsInStr[indexColumn];
        if(indexBook+1 == countBooks && indexColumn != 4)
        {
            indexColumn++;
            indexBook = -1;
        }
    }

    int indexMaxElement = 0;
    int MaxElement = 0;
    for(int columnOfPublishers = 0; columnOfPublishers<5; columnOfPublishers++)
    {
        MaxElement = allCountSymbolsInStrsOnColumn [columnOfPublishers] [searchIndexMaxElementInt(allCountSymbolsInStrsOnColumn[columnOfPublishers], countBooks)];
        if(MaxElement > widthOfPublishers[columnOfPublishers])
        {
            widthOfPublishers[columnOfPublishers] = MaxElement;
        }
    }
    
    int* widthOfAllColumn = (int*)malloc(10*sizeof(int));
    if(widthOfAllColumn == NULL)
    {
        printf("error of malloc");
        exit(6);
    }

    widthOfAllColumn [0] = widthOfNumbers + 2;
    widthOfAllColumn [1] = widthOfName + 2;
    widthOfAllColumn [2] = widthOfAuthor + 2;
    widthOfAllColumn [3] = widthOfYears + 2;
    widthOfAllColumn [4] = widthOfPublishers [0] + 2;
    widthOfAllColumn [5] = widthOfPublishers [1] + 2;
    widthOfAllColumn [6] = widthOfPublishers [2] + 2;
    widthOfAllColumn [7] = widthOfPublishers [3] + 2;
    widthOfAllColumn [8] = widthOfPublishers [4] + 2;
    widthOfAllColumn [9] = widthOfRating + 2;
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
    for(int index = 0; index<10; index++)
    {
        sumAllWidth += widthOfAllColumn[index];
    }
    sumAllWidth += 12; // plus point
    char* head = makeHeadTable(widthOfAllColumn, sumAllWidth);
    FILE* file = fopen(fileName, "w");
    fprintf(file, "%s\n\n", head);
    printHeadlines(file, headlines, lenTitle , 10,widthOfAllColumn);
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
    char* head = (char*)malloc((sumAllWidth)*sizeof(char));
    if (head == NULL)
    {
        printf("error of malloc\n");
        exit(6);
    }
    int indexArrInt = 0;
    int indexLastPlus = 0;
    int indexStr =1;
    head[0] = '+';
    while(indexArrInt != 10)
    {
        head[indexStr] = '-';
        indexStr++;
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
        printStr(file, widthOfAllColumn[index], headlines[index], lenStr[index]);
    }
    fputc('|', file);
}
/*********************************************/
int strLen(char* str)
{
    if(str == NULL)
    {
        return -1;
    }
    int index = 0;
    int len = 0;
    while(str[index] != '\0')
    {
        if(!((int)str[index] == -48 && (int)str[index+1] >= -80 && (int)str[index+1] <= -65 || (int)str[index] == -47 && (int)str[index+1] >= -128 && (int)str[index+1] <= -111 && (int)str[index+1] != -112 || (int)str[index] == -48 && (int)str[index+1] >= -112 && (int)str[index+1] <= -81 || (int)str[index] == -48 && (int)str[index+1] == -127 || (int)str[index] == -30 && (int)str[index+1] == -124 || (int)str[index] == -124 && (int)str[index+1] == -106)) //two byte rus lang :^)
        {
           len++; 
        }
        index++;
    }
    return len;
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
    //print numberOfData
    fputc('|',file);
    printNumber(file, numberOfData, widthOfAllColumn[0]);
    //print Title
    fputc('|',file);
    printStrWithoutSpaceInStart(file, widthOfAllColumn[1], Struct.nameBook, Struct.countSimbolsInNameBook);
    //print Author
    fputc('|',file);
    printStrWithoutSpaceInStart(file, widthOfAllColumn[2], Struct.author, Struct.countSimbolsInAuthor);
    //print YearOfRelise
    fputc('|',file);
    printNumber(file, Struct.yearOfRelise, widthOfAllColumn[3]);
    //print Publishers
    for(int index = 0; index < 5; index++)
    {
        fputc('|',file);
        printStrWithoutSpaceInStart(file, widthOfAllColumn[4 + index], Struct.publishers[index], Struct.countSimbolsInStr[index]);
    }
    //print rating
    fputc('|',file);
    printNumber(file, Struct.rating, widthOfAllColumn[9]);
    fputc('|', file);
}
/*********************************************/
void printStr(FILE* file, int widthColumn, char* str, int lenStr)
{
    int countALLSpace = widthColumn-lenStr;
    printSpase(file ,countALLSpace/2);
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
void printStrWithoutSpaceInStart(FILE* file, int widthColumn, char* str, int lenStr)
{
    int countALLSpace = widthColumn-lenStr;
    fputc(' ', file);
    countALLSpace -= 1;
    if(str[0] != '\0')
    {
        fprintf(file, "%s", str);
    }
    else
    {
        fputc(' ', file);
    }
    printSpase(file ,countALLSpace);
}
/*********************************************/
void printNumber(FILE* file, int number, int width)
{
    int widthNumber = searchWidthOfNumber(number); 
    fprintf(file, "%*d",(width-widthNumber)/2 + widthNumber, number);
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
}
/*********************************************/
void sortArrOfBooksRating(book* arrOfBooks, int countBooks)
{
    int compliteTransposal  = 0;
    for(int index = 0; index<countBooks-1; index++)
    {
        if(arrOfBooks[index].rating > arrOfBooks[index+1].rating)
        {
            book tmp = arrOfBooks[index];
            arrOfBooks[index] = arrOfBooks[index+1];
            arrOfBooks[index+1] = tmp;
            compliteTransposal = 1;
        }
        if(compliteTransposal != 0 && index == countBooks-2)
        {
            compliteTransposal = 0;
            index = -1;
        }
    }
}
/*********************************************/
void sortArrOfBooksYear(book* arrOfBooks, int countBooks)
{
    int compliteTransposal  = 0;
    for(int index = 0; index<countBooks-1; index++)
    {
        if(arrOfBooks[index].yearOfRelise > arrOfBooks[index+1].yearOfRelise)
        {
            book tmp = arrOfBooks[index];
            arrOfBooks[index] = arrOfBooks[index+1];
            arrOfBooks[index+1] = tmp;
            compliteTransposal = 1;
        }
        if(compliteTransposal != 0 && index == countBooks-2)
        {
            compliteTransposal = 0;
            index = -1;
        }
    }
}
/*********************************************/
int* searchIndexesOfBooksByTitle(book* arrOfBooks, int countBooks, char* title)
{
    int* indexesOfFoundBooks = (int*)malloc(countBooks*sizeof(int));
    int indexFoundBooks = 0;  
    for(int index = 0; index < countBooks; index++)
    {
        if(strEQ(arrOfBooks[index].nameBook, title))
        {
            indexesOfFoundBooks[indexFoundBooks] = index;
            indexFoundBooks++;
        }
    }
    indexesOfFoundBooks[indexFoundBooks] = -1;
    return indexesOfFoundBooks; 
}
/*********************************************/
int* searchIndexesOfBooksByAuthor(book* arrOfBooks, int countBooks, char* author)
{
    int* indexesOfFoundBooks = (int*)malloc(countBooks*sizeof(int));
    int indexFoundBooks = 0;  
    for(int index = 0; index < countBooks; index++)
    {
        if(strEQ(arrOfBooks[index].author, author))
        {
            indexesOfFoundBooks[indexFoundBooks] = index;
            indexFoundBooks++;
        }
    }
    indexesOfFoundBooks[indexFoundBooks] = -1;
    return indexesOfFoundBooks; 
}
/*********************************************/
int* searchIndexesOfBooksByPublisher(book* arrOfBooks, int countBooks, char* publisher)
{
    int* indexesOfFoundBooks = (int*)malloc(countBooks*sizeof(int));
    int indexFoundBooks = 0;  
    for(int indexPublisher = 0 ,index = 0; index < countBooks; index++)
    {
        if(strEQ(arrOfBooks[index].publishers[indexPublisher], publisher))
        {
            indexesOfFoundBooks[indexFoundBooks] = index;
            indexFoundBooks++;
            indexPublisher = 0;
        }
        else if( indexPublisher != 4 )
        {
            index--;
            indexPublisher++;
        }
        else
        {
            indexPublisher = 0;
        }
    }
    indexesOfFoundBooks[indexFoundBooks] = -1;
    return indexesOfFoundBooks; 
}
/*********************************************/
int* searchIndexesOfBooksByYear(book* arrOfBooks, int countBooks, int year)
{
    int* indexesOfFoundBooks = (int*)malloc(countBooks*sizeof(int));
    int indexFoundBooks = 0;  
    for(int index = 0; index < countBooks; index++)
    {
        if(arrOfBooks[index].yearOfRelise == year)
        {
            indexesOfFoundBooks[indexFoundBooks] = index;
            indexFoundBooks++;
        }
    }
    indexesOfFoundBooks[indexFoundBooks] = -1;
    return indexesOfFoundBooks; 
}
/*********************************************/
int* searchIndexesOfBooksByRating(book* arrOfBooks, int countBooks, int rating)
{
    int* indexesOfFoundBooks = (int*)malloc(countBooks*sizeof(int));
    int indexFoundBooks = 0;  
    for(int index = 0; index < countBooks; index++)
    {
        if(arrOfBooks[index].rating == rating)
        {
            indexesOfFoundBooks[indexFoundBooks] = index;
            indexFoundBooks++;
        }
    }
    indexesOfFoundBooks[indexFoundBooks] = -1;
    return indexesOfFoundBooks; 
}
/*********************************************/
int clearInputBuffer(void) {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
    return ch;
}
/*********************************************/
int main(int argc, char** argv)
{
    if ( ! checkInputData(argc, argv) )
    {
        printf("bad input data. Need 1 - json file, 2 - file for writing the table\n");
        return 1;
    }
    int countBooks = 0;
    book* arrOfBooks;
    int exit = 0;
    int* widthOfAllColumn;
    char* nameFile = (char*)malloc(257*sizeof(char));
    nameFile = argv[1];
    arrOfBooks = createArrOfBooksFromJSON(nameFile, &countBooks);
    printf("Sort books by rating(1) or years(2) of relise or no(3)?\n");
    int choose = 3;
    fflush(stdin);
    scanf("%d", &choose);
    while(choose<1&&choose>3)
    {
        fflush(stdin);
        scanf("%d", &choose);
    }
    if(choose == 1)
    {
        sortArrOfBooksRating(arrOfBooks, countBooks);
    }
    else if(choose == 2)
    {
        sortArrOfBooksYear(arrOfBooks, countBooks);
    }
    char* headlines [10] = {"№","Название","Автор","Год выпуска","Издатель 1", "Издатель 2", "Издатель 3", "Издатель 4", "Издатель 5", "Рейтинг"};
    int lenStr[10];
    for(int index = 0; index<10; index++)
    {
        lenStr[index] = strLen(headlines[index]);
    }
    widthOfAllColumn = searchWidthOfAllColumn(arrOfBooks, countBooks, lenStr);
    if(argc == 3)
    {
       nameFile = argv[2]; 
    }
    else
    {
        printf("Input name file for writing table: ");
        clearInputBuffer();
        gets(nameFile);
    } 
    printTableInFile(nameFile, arrOfBooks, countBooks, headlines, lenStr, widthOfAllColumn);
    while(!exit)
    {
        printf("Choose one of the actions:\n1) Search book\n2) Print table\n3) Exit\nInput digit: ");
        choose = 3;
        fflush(stdin);
        scanf("%d", &choose);
        while(choose<1&&choose>3)
        {
            fflush(stdin);
            scanf("%d", &choose);
        }
        if(choose == 1)
        {
            printf("Choose the parameter that will be used for the search:\n1) title\n2) author\n3) year of relise\n4) publisher\n5) rating\nInput digit: ");
            fflush(stdin);
            scanf("%d", &choose);
            int* indexesOfFoundBooks; 
            int i;
            switch(choose)
            {
                case 1: 
                    {
                    printf("Input title: \n");
                    char title[60];
                    clearInputBuffer();
                    gets(title);
                    printf("Input: %s", title);
                    indexesOfFoundBooks =  searchIndexesOfBooksByTitle(arrOfBooks, countBooks, title);
                    i = 0;
                    putc('\n', stdout);
                    while(indexesOfFoundBooks[i] != -1)
                    {
                        printData(stdout, arrOfBooks[indexesOfFoundBooks[i]],widthOfAllColumn, i+1 );
                        printf("\n");
                        i++;
                    }
                    free(indexesOfFoundBooks);
                    }
                    break;
                case 2:
                    {
                    printf("Input author: ");
                    char author[60];
                    clearInputBuffer();
                    gets(author);
                    printf("Input: %s", author);
                    indexesOfFoundBooks =  searchIndexesOfBooksByAuthor(arrOfBooks, countBooks, author);
                    i = 0;
                    putc('\n', stdout);
                    while(indexesOfFoundBooks[i] != -1)
                    {
                        printData(stdout, arrOfBooks[indexesOfFoundBooks[i]],widthOfAllColumn, i+1 );
                        printf("\n");
                        i++;
                    }
                    free(indexesOfFoundBooks);
                    }
                    break;
                case 3:
                    {
                    printf("Input year: ");
                    int year = 0;
                    fflush(stdin);
                    scanf("%d", &year);
                    indexesOfFoundBooks =  searchIndexesOfBooksByYear(arrOfBooks, countBooks, year);
                    i = 0;
                    putc('\n', stdout);
                    while(indexesOfFoundBooks[i] != -1)
                    {
                        printData(stdout, arrOfBooks[indexesOfFoundBooks[i]],widthOfAllColumn, i+1 );
                        printf("\n");
                        i++;
                    }
                    free(indexesOfFoundBooks);
                    }
                    break;
                case 4:
                    {
                    printf("Input publisher: ");
                    char publisher[60];
                    clearInputBuffer();
                    gets(publisher);
                    printf("Input: %s", publisher);
                    putc('\n', stdout);
                    indexesOfFoundBooks =  searchIndexesOfBooksByPublisher(arrOfBooks, countBooks, publisher);
                    i = 0;
                    while(indexesOfFoundBooks[i] != -1)
                    {
                        printData(stdout, arrOfBooks[indexesOfFoundBooks[i]],widthOfAllColumn, i+1 );
                        printf("\n");
                        i++;
                    }
                    free(indexesOfFoundBooks);
                    }
                    break;
                case 5:
                    {
                    printf("Input rating: ");
                    int rating = 0;
                    fflush(stdin);
                    scanf("%d", &rating);
                    indexesOfFoundBooks =  searchIndexesOfBooksByRating(arrOfBooks, countBooks, rating);
                    i = 0;
                    putc('\n', stdout);
                    while(indexesOfFoundBooks[i] != -1)
                    {
                        printData(stdout, arrOfBooks[indexesOfFoundBooks[i]],widthOfAllColumn, i+1 );
                        printf("\n");
                        i++;
                    }
                    free(indexesOfFoundBooks);
                    }
                    break;
                default:
                    {
                    printf("bad choose\n");
                    continue;
                    }
                    break;
                
            }
        }
        else if(choose == 2)
        {
            printf("Table:\n");
            FILE* table = fopen(nameFile, "r");
            char charInTable;
            while((charInTable = fgetc(table)) != EOF)
            {
                printf("%c", charInTable);
            }
        }
        else if(choose == 3)
        {
            break;
        }
        else
        {
            printf("bad choose\n");
            continue; 
        }
    }
    return 0;
}
/**********************************************/

