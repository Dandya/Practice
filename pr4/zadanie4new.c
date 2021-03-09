#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**********************************************/
typedef struct
{
    char* nameBook;
    int yearOfRelise;
    char* publishers [5];
    int rating;
}book;
/**********************************************/
book* createArrOfBooksFromJSON(char* nameFileJSON, int* countBooks);
int strEQ(char* strFirst,char * strSecond);
char* readData(FILE* json);
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar);
void writeListOfPublishersInBook(FILE* json, book* structBook);
char goToNextSignificantSymbol(FILE* json);
void readKey(FILE* json, book* ArrOfBooks, int* pointerOnIndexRecordedBook);
void dictJSON(FILE* json, book* arrOfBooks, int* pointerOnIndexRecordedBook);
book* listOfDictJSON(FILE* json, book* arrOfBooks, int* countBooks);
book* beginReadJSON(FILE* json, book* arrOfBooks, int* countBooks);
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

    return arrOfBooks;
}
/**********************************************/
int strEQ(char* strFirst,char * strSecond)
{
    int index = 0;
    while(strFirst[index] == strSecond[index])
    {
        printf("sEQ\n");
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
        printf("rd\n");
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
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadChar)
{ 
    //"Title","YearOfRelease","Publishers","Rating"
    if(strEQ(key,"Title"))
    {
        if(lastReadChar == '"')  
        {
            structBook->nameBook = readData(json);
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
            structBook->yearOfRelise = atoi(readData(json));
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
            
            if((structBook->publishers[0] = (char*)malloc(50*sizeof(char))) == NULL)
            {
                 printf("error malloc\n");
                 exit(6);
            }
        
            structBook->publishers[0] = readData(json);
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
            structBook->rating = atoi(readData(json));
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
        
    if((structBook->publishers[0] = (char*)malloc(50*sizeof(char))) == NULL)
    {
        printf("error malloc\n");
        exit(6);
    }
        
    structBook->publishers[0] = readData(json); 
    
    while(goToNextSignificantSymbol(json) != ']')
    {
        printf("wlopib\n");
        index++;
        if((structBook->publishers[index] = (char*)malloc(50*sizeof(char))) == NULL)
        {
            printf("error malloc\n");
            exit(6);
        }
        structBook->publishers[index] = readData(json);
    }
}
/**********************************************/
char goToNextSignificantSymbol(FILE* json)
{   
    char charInJSON = fgetc(json);
    
    while(charInJSON != ':' && charInJSON != '"' && charInJSON != '[' &&  charInJSON != ']' && charInJSON != '{' && charInJSON != '}')
    {
        printf("gtnss\n");
        charInJSON = fgetc(json);
    }

    return charInJSON;
}
/**********************************************/
void readKey(FILE* json, book* ArrOfBooks, int* pointerOnIndexRecordedBook)
{
    char* key = readData(json);
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
void dictJSON(FILE* json, book* arrOfBooks, int* pointerOnIndexRecordedBook)
{
    char result = goToNextSignificantSymbol(json);
    while(result == '"') //dungerous
    {
        printf("ds\n");
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
book* listOfDictJSON(FILE* json, book* arrOfBooks, int* countBooks)
{
    int index = 0;
    char result = goToNextSignificantSymbol(json);
    while(result != ']')
    {
        printf("lods\n");
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
    *countBooks = index + 1;
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
int main(int argc, char** argv)
{
    int countBooks = 0;
    book* arrOfBooks = createArrOfBooksFromJSON("data.json", &countBooks);
    printf("\n%s - %d\n%s\n%d\n",arrOfBooks[0].nameBook, arrOfBooks[0].yearOfRelise, arrOfBooks[0].publishers[0], arrOfBooks[0].rating);
    printf("\n%s - %d\n%s, %s\n%d\n",arrOfBooks[1].nameBook, arrOfBooks[1].yearOfRelise, arrOfBooks[1].publishers[0], arrOfBooks[1].publishers[1], arrOfBooks[1].rating); 
    printf("\n%s - %d\n%s, %s, %s\n%d\n",arrOfBooks[2].nameBook, arrOfBooks[2].yearOfRelise, arrOfBooks[2].publishers[0], arrOfBooks[2].publishers[1],arrOfBooks[2].publishers[2], arrOfBooks[2].rating);
    return 0;
}
