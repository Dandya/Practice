#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**********************************************/
typedef struct
{
    char* nameBook = NULL;
    short int yearOfRelise = 0;
    char** publishers;
    short int rating = 0;
}book;
/**********************************************/
int readJSON(FILE* json, char** keys,char* indexKey, void** pointerOnArrOfStructs,\
        int* pointerOnIndexReadbleStruct, char** arrOfStr, int*  pointerOnIndexStr)
{
    /*
     * Функция читает фаил расширения .json
     * и при встречи символа начала list, dict или key 
     * отправляет данные для чтения этих типов в функции
     * readListJSON, readDictJSON, readKeyAndDataJSON 
     * соответственно. Возвращает 0 в случае успеха.
     * */

    char charInJSON = '\0';
    int resultFunc = 0;
    while((charInJSON = fgetc(json)) != EOF)
    {
        switch(charInJSON) //change cases!!!!
        {
            case '[': 
                resultFunc = ListJSON(json, keys, pointerOnArrOfStructs,\
                    pointerOnIndexReadbleStruct, arrOfStr, pointerOnIndexStr); 
                break;
            case ']':
                return -1;
            case '{':
                resultFunc = DictJSON(json, keys, pointerOnArrOfStructs,\
                    pointerOnIndexReadbleStruct);
                break;
            case '}':
                return -2;
            case '"':
                resultFunc = KeyAndDataJSON(json, keys, pointerOnArrOfStructs,\
                    pointerOnIndexReadbleStruct, countStructs);
                break;
        }
    }
    return 0;    
}
/**********************************************/
int ListJSON(FILE* json, char** keys, void** pointerOnArrOfStructs,\ 
        int* pointerOnIndexRecordedStruct, char** arrOfStr,\ 
        int*  pointerOnIndexStr) 
{
    /*
     * Функция читает тип list, и если ей встречается 
     * вложенный list или dict, то функция вызывает рекурсивно
     * себя в первом случае или readDictJSON во втором.
     * При встречи ']' заканчивает работу и возвращает 0.
     * */
    
     // our struct    
    
    if(arrOfStr != NULL)
    {
        int resultReadJSON = 0;
        while(resultReadJSON != -1)
        {
            resultReadJSON = readJSON(json, keys, NULL,  NULL,\
                    pointerOnIndexReadbleStruct, arrOfStr, pointerOnIndexStr);
        }
    }
    else if (*pointerOnArrOfStructs != NULL)
    {
        int resultReadJSON = 0;
        while(resultReadJSON != -1)
        {
            resultReadJSON = readJSON(json, keys, NULL,  pointerOnArrOfStructs, pointerOnIndexReadbleStruct, NULL, NULL);
        }
    }
    else
    {
        printf("error of pointers in readListJSON");
        exit(3);    
    }
    
    return 0;
}
/**********************************************/
int DictJSON(FILE* json, char** keys, void** pointerOnArrOfStructs,\ 
        int* pointerOnIndexReadbleStruct)
{
    /* 
     * Функция читает тип dict, и если ей встречается 
     * вложенный list или dict, то функция вызывает рекурсивно
     * себя во втором случае или readListJSON в первом.
     * При встречи '}' возвращает указатель на 
     * массив структур book.
     * */
    
    char indexKey = 0;
    int resultReadJSON = 0;

    while(resultReadJSON != -2)
    {
        resultReadJSON = readJSON(json, keys, &indexKey,  pointerOnArrOfStructs, pointerOnIndexReadbleStruct, NULL, NULL);
    }
    
    
    *pointerOnIndexReadbleStruct += 1;
    if(*pointerOnIndexReadbleStruct%30 == 0)
    {
         (book*)*pointerOnArrOfStructs = (book*)realloc((book*)*pointerOnArrOfStructs, (*pointerOnIndexReadbleStruct+30)*sizeof(book));
         if(*pointerOnArrOfStructs == NULL)
         {
             printf("error of pointer on array of structs\n");
             exit(4);
         }
    }

    return 0;

}
/**********************************************/
int KeyAndDataJSON(FILE* json, char** keys, char* indexKey, void** pointerOnArrOfStructs,\ 
        int* pointerOnIndexReadbleStruct, char** arrOfStr, int*  pointerOnIndexStr)
{
    
    
    if(*pointerOnArrOfStructs != NULL)
    {
        //read key
        char* key = (char*)malloc(20*sizeof(char));
        int indexCharInKey = 0;
        key[indexCharInKey] = fgetc(json);
        while(key[indexCharInKey] != '"')
        {
            indexCharInKey++;
            if (indexCharInKey%20 == 0)
            {
                key = (char*)realloc(key,(indexCharInKey+20)*sizeof(char));
            }
            key[indexCharInKey] = fgetc(json);
        }   
        key[indexCharInKey] = '\0';
        //end read key
        //seach index 
        for(int i = 0; i<4; i++)
        {
            int result = 
        }
    }
    else if(arrOfStr != NULL)
    {
        
    }
    else
    {
        printf("error of pointers in KeyAndDataJSON");
        exit(5);
    }

}
/**********************************************/

int main(int argc, char** argv)
{
    /* 
     * На вход может подаваться название фаила с расширением .json 
     * (всегда идёт первым, после имени программы) и название фаила 
     * с расширением, куда будет записан результат, либо только 
     * название фаила с расширением .json, а результат будет записан 
     * в фаил result.txt
     * */

//input validation
    if(argc == 2 || argc == 3)
    {
        FILE* json = open(argv[1], "r"); 
    } 
    else
    {
        printf("non-current input\n");
        return 1;
    }

    if (json == NULL)
    {
        printf("error of open file .json");
        return 2;
    }
//end input validation


    char* keys [] = { "Title","YearOfRelease","Publishers","Rating" };
    book* arrOfBooks = (book*)malloc(30*sizeof(book));
    int indexOfReadableBook = 0;

//start read
    int result = readJSON(json, keys, NULL, &arrOfBooks, &indexOfReadableBook, NULL, NULL);
//end read 
    
    //...
    fclose(json);
    free(arrOfBooks);
    return 0;
}
