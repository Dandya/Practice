#include <iostream>
#include <fstream>
#include <random> 
#include <time.h>
#ifndef BULL_AND_COW_H
#define BULL_AND_COW_H
//*********Work with string************
/**
 * clearInputBuffer
 * * Function clears standart input buffer
 */

int clearInputBuffer() 
{
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
    return ch;
}
/**
 * inputWord
 * * Function returns input word it was written by user
 */
const std::string inputStr()
{
    std::cout << "->  ";
    std::string input;
    std::cin >> input;
    clearInputBuffer();
    return input;
}
//----------------------------------------------------------------
#define BULL 1
#define COW 0
//----------------------------------------------------------------
/**
 * searchBullOrCow
 * * Function compares char from word1 and str2 and returns bull or cow on EN language
 */
const int searchBullOrCow(char symbol,int indexSimbol, std::string str2)
{
    int cow {3}, bull {3};
    for(int index = 0; index < str2.length(); index++)
    {
        if(symbol == str2[index] && indexSimbol != index)
        {
            cow = COW;
        }    
        if(symbol == str2[index] && indexSimbol == index)
        {
            bull = BULL;
        }
    }
    if(bull == BULL)
    {
        return BULL;
    }
    else if(cow == COW)
    {
        return COW;
    }
    return -1;
} 
//----------------------------------------------------------------
/**
 * compareWords
 * * Function compares two words and changes count bulls and cows on EN language
 */
const void compareStr(std::string str1, std::string str2, 
        int* countBulls, int* countCows)
{
    int result;
    for(int index = 0; index < str1.length(); index++) // not look '\0'
    {
        result = searchBullOrCow(str1[index],index, str2);
        if (result == BULL)
        {
            (*countBulls)++;
        }
        else if (result == COW)
        {
            (*countCows)++;
        }
    }
}
//---------------------------------------------------------------
#define EASY 0
#define NORMAL 1
#define HARD 2
//---------------------------------------------------------------
/**
 * isTrueDifficultyLevel
 * * Fuction checks word is true for a difficulty level
 */
bool isTrueDifficultyLevel(int difficultyLevel, int lengthWord)
{
    switch(difficultyLevel)
    {
        case EASY: if(lengthWord <= 5 && lengthWord >= 4) return true; break;
        case NORMAL: if(lengthWord <= 7 && lengthWord >= 5) return true; break;
        case HARD: if(lengthWord <= 9 && lengthWord >= 5) return true; break;
    }
    return false;
}
//-------------------------------------------------------------
/**
 * compareSymbols
 * @param index = index of symbol in numStr + 1
 */
bool compareSymbols(char symbol, int index, std::string numStr)
{
    for(;index < numStr.length(); index++)
    {
        if(symbol == numStr[index])
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------
/**
 * isTrueVariousSimbols
 * * Function cheaks all simbols in string and returns true if all these simbols is various
 */
bool isTrueVariousSimbols(std::string numStr)
{
    //char masSymbols[numStr.length()] {0};
    // * run for all simbols in string and write unical simbol to massive
    for (int i {0}; i < numStr.length(); i++)
    {
        if(compareSymbols(numStr[i], i+1, numStr))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
//**************DIGITS*********************
/**
 * randomDigits
 * * Function returns a random digits in string format
 */
std::string randomDigits(int difficultyLevel)
{
    srand(time(0));
    std::string numStr;
    do
    {
        numStr = std::to_string(rand()%1000000000);
    } while (!isTrueDifficultyLevel(difficultyLevel, numStr.length()) || !isTrueVariousSimbols(numStr));
    return numStr;
}
//*************SIMPLE_GAME*****************
/**
 * simpleGame
 * * Function defines simple game by user
 * @param mode maybe will be LANGUAGE_RU, LANGUAGE_EN, DIGITS
 */
int simpleGame(int difficultyLevel)
{
    std::string numStr = randomDigits(difficultyLevel);
    int countBulls {0}, countCows {0};
    std::string answer;
    int round {0};
    //process of game
    std::cout << "Length: " << numStr.length() << std::endl;
    while(numStr.length() != countBulls)
    {
        round++;
        std::cout << "Round " << round << std::endl;
        answer = inputStr();
        if(answer == "exit")
        {
            return 2;
        }
        compareStr(answer, numStr, &countBulls, &countCows);
        std::cout << "Bulls: " << countBulls << std::endl; 
        std::cout << "Cows: " << countCows << std::endl;
        countBulls = 0; 
        countCows = 0;
    }
    std::cout << "You win!" << std::endl;
    return 0;
}
//*****************************************
#endif 