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
book* createArrOfBooksFromJSON(char* nameFileJSON, int* countBooks)
{
    FILE *json = open(nameFileJSON, "r");
    
    if (json == NULL)
    {
        printf("error of open file .json");
        exit(2);
    }
    
    book* arrOfBooks = (book*)malloc(30*sizeof(book));
    
    arrOfBooks =  beginReadJSON(json, arrOfBooks, countBooks);

    return arrOfBooks;
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
            data = (char*)realloc(data, (indexCharInValue+20)*sizeof(char));
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
void saveValueInKeyJSON(FILE* json, char* key, book* structBook, char lastReadСhar)
{ 
    //"Title","YearOfRelease","Publishers","Rating"
    if(strEQ(key,"Title"))
    {
        if(lastReadСhar == '"')  
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
        
        if(lastReadСhar == '"')  
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
        if(lastReadСhar == '[')
        {
            writeListOfPublishersInBook(json, structBook);    
        }
        else if(lastReadСhar == '"')
        {
            
            if((structBook->publishers[0] = (char*)malloc(50*sizeof(char))) == NULL)
            {
                 printf("error malloc\n");
                 return 0;
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
        if(lastReadСhar == '"')  
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
        index++;
        if((structBook->publishers[index] = (char*)malloc(50*sizeof(char))) == NULL)
        {
            printf("error malloc\n");
            return 0;
        }
        structBook->publishers[index] = readData(json);
    }
}
/**********************************************/
char goToNextSignificantSymbol(FILE* json)
{   
    char charInJSON = fgetc(json);
    
    while(charInJSON != ':' || charInJSON != '"' ||  charInJSON != '[' ||  charInJSON != ']'\ 
            || charInJSON != '{' || charInJSON != '}')
    {
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
        readKey(json, arrOfBooks,pointerOnIndexRecordedBook);
        result = goToNextSignificantSymbol(json);
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
    while(result == '{')
    {
        dictJSON(json, arrOfBooks, &index);
        index++;
        if(index%30 == 0)
        {
            if((arrOfBooks = (book*)realloc((index+30)*sizeof(book))) == NULL)
            {
                printf("error of realloc");
                exit(10);
            }
        }
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
    book* arrOfBooks = createArrOfBooksFromJSON(argv[1], &countBooks); 
    
    return 0;
}
